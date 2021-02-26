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

	SpawnEnemies();
}

void ASpawner::SpawnEnemies()
{
	UWorld* World = GetWorld();
	if (World && EnemyBlueprint)			//check if World is valid
	{
		FVector Offset{ 0.f };
		AMyEnemy* tempPtr{nullptr};
		for (int i{0}; i < EnemiesToSpawn; i++)
		{	
			//Spawns bullet at Player location + SpawnPoint 
			Offset.Y += DistanceBetweenEnemies;
			tempPtr = World->SpawnActor<AMyEnemy>(EnemyBlueprint, GetActorLocation() + Offset, GetActorRotation());
			if(tempPtr) // <-this is actually necessary! Why ??? :-)
				tempPtr->SpawnerPtr = this;
		}
	}
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TimeGone += DeltaTime;

	if (TimeGone > TimeBetweenSpawns)
	{
		TimeGone = 0.f;
		if(Direction == 0 || Direction == 2)
			SpawnEnemies();
	
		(Direction == 3) ? Direction = 0 : Direction++;
		UE_LOG(LogTemp, Warning, TEXT("Direction: %d"), Direction)
	}
}
