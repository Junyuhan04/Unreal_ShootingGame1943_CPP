// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"

#include "ShooterGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Bullet.h"
#include "PlayerPawn.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetGenerateOverlapEvents(true);
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorWorldOffset(
		FVector(-MoveSpeed * DeltaTime, 0.f, 0.f)
	);
}

void AEnemy::OnOverlapBegin(
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
		AShooterGameMode* GM =
			Cast<AShooterGameMode>(
				UGameplayStatics::GetGameMode(this)
			);

		if (GM)
		{
			GM->AddScore(100);
		}

		OtherActor->Destroy();
		Destroy();
	}
	if (APlayerPawn* Player =
	Cast<APlayerPawn>(OtherActor))
	{
		Player->TakeDamage(1);

		Destroy();
	}
}
