// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "MyEnemy.h"


// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	OurVisibleComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TimeGone += DeltaTime;

	if (TimeGone > TimeBetweenSpawns)
	{
		TimeGone = 0.f;
		UWorld* World = GetWorld();
		if (World && EnemyBlueprint)			//check if World is valid
		{
			 World->SpawnActor<AMyEnemy>(EnemyBlueprint, GetActorLocation(), GetActorRotation());
		}
	}
}
