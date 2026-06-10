#pragma once

#include "CoreMinimal.h"
#include "IHPUser.h"
#include "TStateMachine.h"
#include "GameFramework/Actor.h"
#include "Boss.generated.h"

class ABossBullet;

enum class EBossState : uint8 { Move, Pattern1, Pattern2, Pattern3 };

UCLASS()
class SHOOTCPP_API ABoss : public AActor, public IHPUser
{
	GENERATED_BODY()

public:
	ABoss();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stat")
	float hp = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stat")
	float MoveSpeed = 400.f;

	// 보스가 이동할 목표 위치 (레벨 내부 지점)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stat")
	FVector TargetPosition = FVector(0.f, 0.f, 500.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Bullet")
	TSubclassOf<ABossBullet> BulletFactory;

	UPROPERTY(VisibleAnywhere, Category="Component")
	class UBoxComponent* BoxComp;
	UPROPERTY(VisibleAnywhere, Category="Component")
	class UStaticMeshComponent* MeshComp;

	void SpawnBullet(FVector Direction);

	virtual float GetHP() const override { return hp; }
	virtual void TakeDamage(float damage) override;

private:
	TStateMachine<EBossState> StateMachine;
};
