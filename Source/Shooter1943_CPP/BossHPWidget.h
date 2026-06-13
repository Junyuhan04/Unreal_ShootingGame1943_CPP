#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BossHPWidget.generated.h"

class UProgressBar;

UCLASS()
class SHOOTER1943_CPP_API UBossHPWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateHP(float Percent);
};