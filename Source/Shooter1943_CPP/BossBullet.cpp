#include "BossBullet.h"

#include "PlayerPawn.h"

ABossBullet::ABossBullet()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh =
		CreateDefaultSubobject<UStaticMeshComponent>(
			TEXT("Mesh")
		);

	RootComponent = Mesh;

	Mesh->SetCollisionEnabled(
		ECollisionEnabled::QueryAndPhysics
	);

	Mesh->SetGenerateOverlapEvents(true);

	Mesh->OnComponentBeginOverlap.AddDynamic(
		this,
		&ABossBullet::OnOverlapBegin
	);
}

void ABossBullet::BeginPlay()
{
	Super::BeginPlay();
}

void ABossBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorWorldOffset(
		FVector(-Speed * DeltaTime, 0.f, 0.f)
	);

	if (GetActorLocation().X < -2000.f)
	{
		Destroy();
	}
}

void ABossBullet::OnOverlapBegin(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	if (APlayerPawn* Player =
		Cast<APlayerPawn>(OtherActor))
	{
		Player->TakeDamage(1);

		Destroy();
	}
}