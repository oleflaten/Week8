// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyEnemy.generated.h"

UCLASS()
class WEEK6_API AMyEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyEnemy();

	class ASpawner* SpawnerPtr{ nullptr };

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//The visual mesh of the Actor - set inside the Editor
	UPROPERTY(EditAnywhere);
	UStaticMeshComponent* OurVisibleComponent{ nullptr };

	UPROPERTY(EditAnywhere, Category = "Setup")
	float MoveSpeed{ 50.f };

	UPROPERTY(EditAnywhere, Category = "Setup");
	class USphereComponent* OurCollider{ nullptr };

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
