// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ScoreWidget.h"
#include "ShooterGameMode.generated.h"

class UUserWidget;

UCLASS()
class SHOOTER1943_CPP_API AShooterGameMode : public AGameModeBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABossEnemy> BossClass;
	bool bBossSpawned = false;

	void SpawnBoss();
	
public:

	// 점수 UI 클래스
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> ScoreWidgetClass;

	// 생성된 점수 UI
	UPROPERTY()
	UScoreWidget* ScoreWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Score = 0;

	virtual void BeginPlay() override;

	void AddScore(int32 Value);
	
	
};


