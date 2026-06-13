#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "BossEnemy.generated.h"

class UUserWidget;
class ABossBullet;
class UBossHPWidget;

UCLASS()
class SHOOTER1943_CPP_API ABossEnemy : public AActor
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> WinWidgetClass;

	
private:
	FVector StartLocation;
	float MoveTime = 0.f;
	float FireTimer = 0.f;
public:
	UFUNCTION(BlueprintCallable)
	float GetHPPercent() const;
	
	UPROPERTY()
	UBossHPWidget* BossHPWidget;
	ABossEnemy();
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABossBullet> BossBulletClass;
	
protected:
	virtual void BeginPlay() override;
public:
	void Fire();

	virtual void Tick(float DeltaTime) override;

	// 보스 체력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss")
	int32 MaxHP = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss")
	int32 CurrentHP = 100;

	// 보스 메쉬
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Boss")
	UStaticMeshComponent* Mesh;

	// 보스 HP UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> BossHPWidgetClass;


	// 데미지 처리
	void TakeDamage(int32 Damage);

	// 총알 충돌
	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);
};
