// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bullet.h"
#include "IHPUser.h"
#include "GameFramework/Pawn.h"
#include "CPlayer.generated.h"

UCLASS()
class SHOOTCPP_API ACPlayer : public APawn, public IHPUser
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACPlayer();

	// 소멸자 필요 없음(메모리 관리 알아서 해줌)
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
public:
	// 인스펙터에서 보이게 하기 위한 UPROPERTY(UObject를 상속받아야함)
	// Category: [Header()] 어트리뷰트 느낌. "는 옵션
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stat")
	float hp = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stat")
	float speed = 500;
	
public:
	UPROPERTY(VisibleAnywhere, Category="ShootComponent")
	class UBoxComponent* BoxComp;
	UPROPERTY(VisibleAnywhere, Category="ShootComponent")
	class UStaticMeshComponent* BodyMeshComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	class UInputAction* ia_move;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	class UInputMappingContext* imc_shoot;
	void MovePlayer(const struct FInputActionValue& value);
	FVector dir;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	class UInputAction* ia_fire;
	void Fire(const struct FInputActionValue& value);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	TSubclassOf<ABullet> bulletFactory;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sound")
	USoundBase* fireSound;

	virtual float GetHP() const override { return hp; }
	virtual void TakeDamage(float damage) override;
};
