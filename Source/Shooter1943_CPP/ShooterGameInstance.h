#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ShooterGameInstance.generated.h"

UCLASS()
class SHOOTER1943_CPP_API UShooterGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FLinearColor SelectedColor =FLinearColor::Red;
	
};