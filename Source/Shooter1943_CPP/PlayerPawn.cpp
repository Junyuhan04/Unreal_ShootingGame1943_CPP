#include "PlayerPawn.h"
#include "PlayerHPWidget.h"
#include "Bullet.h"
#include "Components/InputComponent.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "ShooterGameInstance.h"

APlayerPawn::APlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetGenerateOverlapEvents(true);
}

void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();


	if (PlayerHPWidgetClass)
	{
		PlayerHPWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHPWidgetClass);

		if (PlayerHPWidget)
		{
			PlayerHPWidget->AddToViewport();
		}
	}

	UShooterGameInstance* GI = Cast<UShooterGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (GI)
	{
		UMaterialInstanceDynamic* Mat = Mesh->CreateAndSetMaterialInstanceDynamic(0);
		if (Mat)
		{
			Mat->SetVectorParameterValue(FName("Color"), GI->SelectedColor);
		}
	}
	if (PlayerHPWidget)
	{
		if (UPlayerHPWidget* HPWidget = Cast<UPlayerHPWidget>(PlayerHPWidget))
		{
			HPWidget->UpdateHP(CurrentHP);
		}
	}
}

void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorWorldOffset(MoveInput * MoveSpeed * DeltaTime, true);
	FVector Location = GetActorLocation();

	Location.X = FMath::Clamp(Location.X, -700.f, 700.f);
	Location.Y = FMath::Clamp(Location.Y, -850.f, 850.f);

	SetActorLocation(Location);
}

void APlayerPawn::MoveForward(float Value)
{
	MoveInput.X = Value;
}

void APlayerPawn::MoveRight(float Value)
{
	MoveInput.Y = Value;
}

void APlayerPawn::Fire()
{
	if (BulletClass)
	{
		FVector SpawnLocation = GetActorLocation() + FVector(100.f, 0.f, 0.f);
		GetWorld()->SpawnActor<ABullet>(BulletClass, SpawnLocation, FRotator::ZeroRotator);
	}
}

void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerPawn::MoveForward);

	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerPawn::MoveRight);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerPawn::Fire);
}

void APlayerPawn::TakeDamage(int32 Damage)
{
	CurrentHP -= Damage;
	if (PlayerHPWidget)
	{
		if (UPlayerHPWidget* HPWidget = Cast<UPlayerHPWidget>(PlayerHPWidget))
		{
			HPWidget->UpdateHP(CurrentHP);
		}
	}

	if (CurrentHP <= 0)
	{
		if (LoseWidgetClass)
		{
			UUserWidget* LoseUI = CreateWidget<UUserWidget>(GetWorld(), LoseWidgetClass);
			if (LoseUI)
			{
				LoseUI->AddToViewport();

				APlayerController* PC = GetWorld()->GetFirstPlayerController();

				if (PC)
				{
					PC->bShowMouseCursor = true;

					FInputModeUIOnly InputMode;
					PC->SetInputMode(InputMode);
				}
			}
		}

		UGameplayStatics::SetGamePaused(GetWorld(),true);
		Destroy();
	}
}
void APlayerPawn::ApplyColor(FLinearColor NewColor)
{
	UMaterialInstanceDynamic* Mat =	Mesh->CreateAndSetMaterialInstanceDynamic(0);

	if (Mat)
	{
		Mat->SetVectorParameterValue(TEXT("Color"),NewColor);
	}
}