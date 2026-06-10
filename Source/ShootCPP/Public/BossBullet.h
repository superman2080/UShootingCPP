#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BossBullet.generated.h"

UCLASS()
class SHOOTCPP_API ABossBullet : public AActor
{
	GENERATED_BODY()

public:
	ABossBullet();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stat")
	float Speed = 500.f;

	FVector Direction = FVector(0.f, 0.f, -1.f);

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxComp;
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* MeshComp;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

private:
	float LifeTime = 0.f;
	static constexpr float MaxLifeTime = 8.f;
};
