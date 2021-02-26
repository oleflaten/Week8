// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEnemy.h"
#include "Components/SphereComponent.h"
#include "Spawner.h"


// Sets default values
AMyEnemy::AMyEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a dummy root component we can attach things to.
	OurCollider = CreateDefaultSubobject<USphereComponent>(TEXT("MyCollider"));
	RootComponent = OurCollider;

	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	OurVisibleComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMyEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Movement each tick - scaled with DeltaTime
	FVector CurrentLocation = GetActorLocation();
	int temp = SpawnerPtr->Direction;
	switch (temp)
	{
	case 0:
		CurrentLocation += GetActorForwardVector() * MoveSpeed * DeltaTime;
		break;
	case 1:
		CurrentLocation += GetActorRightVector() * MoveSpeed * DeltaTime;
		break;
	case 2:
		CurrentLocation += GetActorForwardVector() * MoveSpeed * DeltaTime;
		break;
	case 3:
		CurrentLocation -= GetActorRightVector() * MoveSpeed * DeltaTime;
		break;

	default:
		break;
	}
	SetActorLocation(CurrentLocation);
}

