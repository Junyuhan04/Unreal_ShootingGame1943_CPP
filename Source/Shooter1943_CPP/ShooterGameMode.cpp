// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterGameMode.h"

#include "Blueprint/UserWidget.h"
#include "BossEnemy.h"
#include "Engine/Engine.h"

void AShooterGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (ScoreWidgetClass)
	{
		ScoreWidget =
			CreateWidget<UScoreWidget>(
				GetWorld(),
				ScoreWidgetClass
			);

		if (ScoreWidget)
		{
			ScoreWidget->AddToViewport();
		}
	}
}

void AShooterGameMode::AddScore(int32 Value)
{
	Score += Value;

	if (ScoreWidget)
	{
		ScoreWidget->UpdateScore(Score);
	}
	
	if (Score >= 1000 && !bBossSpawned)
	{
		SpawnBoss();
	}
}

void AShooterGameMode::SpawnBoss()
{
	bBossSpawned = true;
	GetWorld()->SpawnActor<ABossEnemy>(BossClass,FVector(1000, 0, 100),FRotator::ZeroRotator);
}
