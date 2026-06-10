// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Boss.h"
#include "Enemy.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"


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
	
	ConstructorHelpers::FObjectFinder<UMaterial> mat(TEXT("/Game/Materials/M_Bullet.M_Bullet"));
	if (mat.Succeeded())
	{
		BodyMeshComp->SetMaterial(0, mat.Object);
	}
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	BoxComp->SetCollisionProfileName(TEXT("OverlapAll"));
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnHit);
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto dir = FVector::UpVector * speed;
	SetActorLocation(GetActorLocation() + dir * DeltaTime);
}

void ABullet::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	if (AEnemy* Enemy = Cast<AEnemy>(OtherActor))
	{
		Enemy->TakeDamage(1.f);
		Destroy();
	}
	else if (ABoss* Boss = Cast<ABoss>(OtherActor))
	{
		Boss->TakeDamage(1.f);
		Destroy();
	}
}

