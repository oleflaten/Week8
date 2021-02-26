// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

UCLASS()
class WEEK6_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	int Direction{ 0 };		//0 = forward, 1 = left, 2 = forward, 3 = right

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//The mesh - assigned inside Unreal Editor
	UPROPERTY(EditAnywhere, Category = "Setup");
	USceneComponent* OurVisibleComponent{ nullptr };

	//The type we will use as Eneies - assigned inside Unreal Editor
	UPROPERTY(EditAnywhere, Category = "Setup");
	TSubclassOf<class AMyEnemy> EnemyBlueprint{nullptr};

	UPROPERTY(EditAnywhere, Category = "Setup");
	int EnemiesToSpawn{ 5 };

	UPROPERTY(EditAnywhere, Category = "Setup");
	float TimeBetweenSpawns{ 2.f };

	UPROPERTY(EditAnywhere, Category = "Setup");
	float DistanceBetweenEnemies{ 100.f };

private:	
	void SpawnEnemies();

	float TimeGone{ 0.f };

};
