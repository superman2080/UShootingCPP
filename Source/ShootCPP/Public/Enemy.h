// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CPlayer.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

UCLASS()
class SHOOTCPP_API AEnemy : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stat")
	float speed = 500;
	
	UPROPERTY(VisibleAnywhere, Category="ShootComponent")
	class UBoxComponent* BoxComp;
	UPROPERTY(VisibleAnywhere, Category="ShootComponent")
	class UStaticMeshComponent* BodyMeshComp;
	UPROPERTY(EditAnywhere)
	UMaterialInterface* SurfaceMaterial;
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, 
		const FHitResult & SweepResult);
	
	UPROPERTY(EditAnywhere)
	ACPlayer* player;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sound")
	USoundBase* destroySound;
};
