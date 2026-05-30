// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"

#include "Components/BoxComponent.h"


// Sets default values
ABullet::ABullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// GetComponent<>()
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	RootComponent = BoxComp;
	
	BodyMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMeshComp"));
	BodyMeshComp->SetupAttachment(BoxComp);
	
	// BodyMesh에 CubeStaticMesh 데이터 로드해서 할당.
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	
	if (tempMesh.Succeeded() /*tempMesh != nullptr*/)
	{
		BodyMeshComp->SetStaticMesh(tempMesh.Object);
	}
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto dir = FVector::UpVector * speed;
	
	SetActorLocation(GetActorLocation() + dir * DeltaTime);
}

