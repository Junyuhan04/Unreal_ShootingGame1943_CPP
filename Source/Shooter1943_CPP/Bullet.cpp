#include "Bullet.h"
#include "Components/StaticMeshComponent.h"

ABullet::ABullet()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetGenerateOverlapEvents(true);
}

void ABullet::BeginPlay()
{
	Super::BeginPlay();
}

void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorWorldOffset(
		FVector(500.f * DeltaTime, 0.f, 0.f)
	);
}