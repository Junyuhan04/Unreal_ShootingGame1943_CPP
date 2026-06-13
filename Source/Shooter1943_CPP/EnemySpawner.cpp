// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "Enemy.h"
#include "TimerManager.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(
		SpawnTimer,
		this,
		&AEnemySpawner::SpawnEnemy,
		SpawnInterval,
		true
	);
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AEnemySpawner::SpawnEnemy()
{
	if (EnemyClass)
	{
		GetWorld()->SpawnActor<AEnemy>(
			EnemyClass,
			GetActorLocation(),
			FRotator::ZeroRotator
		);
	}
}

