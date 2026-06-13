#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Blueprint/UserWidget.h"
#include "PlayerPawn.generated.h"

class UUserWidget;
UCLASS()
class SHOOTER1943_CPP_API APlayerPawn : public APawn
{
    GENERATED_BODY()
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* Mesh;
    
public:
    APlayerPawn();

    UFUNCTION(BlueprintCallable)
    void ApplyColor(FLinearColor NewColor);
    
    UPROPERTY(VisibleAnywhere)
    USceneComponent* Root;

    UPROPERTY(EditAnywhere)
    TSubclassOf<UUserWidget> PlayerHPWidgetClass;
    
    UPROPERTY()
    UUserWidget* PlayerHPWidget;
    
protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
    void MoveForward(float Value);
    void MoveRight(float Value);
    void Fire();
    FVector MoveInput;

public:

    void TakeDamage(int32 Damage);
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MoveSpeed = 600.f;

    UPROPERTY(EditAnywhere)
    TSubclassOf<class ABullet> BulletClass;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MaxHP = 3;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 CurrentHP = 3;
    
    UPROPERTY(EditAnywhere)
    TSubclassOf<UUserWidget> LoseWidgetClass;
};

