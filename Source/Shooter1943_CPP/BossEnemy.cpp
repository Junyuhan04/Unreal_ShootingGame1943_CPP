// Fill out your copyright notice in the Description page of Project Settings.
#include "BossEnemy.h"

#include "Blueprint/UserWidget.h"
#include "BossBullet.h"
#include "Engine/Engine.h"
#include "Bullet.h"
#include "BossHPWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
// Sets default values
ABossEnemy::ABossEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetGenerateOverlapEvents(true);

	Mesh->OnComponentBeginOverlap.AddDynamic(
		this,
		&ABossEnemy::OnOverlapBegin
	);
}

// Called when the game starts or when spawned
void ABossEnemy::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();
	
	if (BossHPWidgetClass)
	{
		BossHPWidget =
	CreateWidget<UBossHPWidget>(
		GetWorld(),
		BossHPWidgetClass
	);

		if (BossHPWidget)
		{
			BossHPWidget->AddToViewport();
		}
	}
}

// Called every frame
void ABossEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	MoveTime += DeltaTime;

	FVector NewLocation = StartLocation;

	NewLocation.Y =
		StartLocation.Y +
		FMath::Sin(MoveTime * 2.f) * 300.f;

	SetActorLocation(NewLocation);

	FireTimer += DeltaTime;

	if (FireTimer >= 3.f)
	{
		FireTimer = 0.f;

		Fire();
	}
}
void ABossEnemy::TakeDamage(int32 Damage)
{
	CurrentHP -= Damage;

	float HPPercent =
		(float)CurrentHP / (float)MaxHP;

	if (BossHPWidget)
	{
		BossHPWidget->UpdateHP(HPPercent);
	}

	if(CurrentHP <= 0)
	{
		if (WinWidgetClass)
		{
			UUserWidget* WinUI =
				CreateWidget<UUserWidget>(
					GetWorld(),
					WinWidgetClass
				);

			if (WinUI)
			{
				WinUI->AddToViewport();

				APlayerController* PC =
					GetWorld()->GetFirstPlayerController();

				if (PC)
				{
					PC->bShowMouseCursor = true;

					FInputModeUIOnly InputMode;
					PC->SetInputMode(InputMode);
				}
			}
		}

		UGameplayStatics::SetGamePaused(
			GetWorld(),
			true
		);

		Destroy();
	}
}
void ABossEnemy::OnOverlapBegin(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	if (Cast<ABullet>(OtherActor))
	{
		TakeDamage(10);

		OtherActor->Destroy();
	}
}
float ABossEnemy::GetHPPercent() const
{
	return (float)CurrentHP / (float)MaxHP;
}
void ABossEnemy::Fire()
{
	if (!BossBulletClass)
	{
		return;
	}

	FVector Location = GetActorLocation();

	GetWorld()->SpawnActor<ABossBullet>(BossBulletClass,Location + FVector(-100.f, 0.f, 0.f),FRotator::ZeroRotator);
	GetWorld()->SpawnActor<ABossBullet>(BossBulletClass,Location + FVector(-100.f, 100.f, 0.f),	FRotator::ZeroRotator);
	GetWorld()->SpawnActor<ABossBullet>(BossBulletClass,Location + FVector(-100.f, -100.f, 0.f),FRotator::ZeroRotator);
}