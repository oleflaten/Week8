// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyBullet.generated.h"

UCLASS()
class WEEK6_API AMyBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyBullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    //Speed of bullet when it gets spawned
    UPROPERTY(EditAnywhere, Category = "Setup")
    float Speed{ 400.f };

    //Time the bullet can live before we destroy it
    UPROPERTY(EditAnywhere, Category = "Setup")
    float TimeBeforeDestroy{ 5.f };

    //The time this exact bullet have lived
    float TimeLived{ 0.f };

    //The collider of the bullet
    //Size can be changed inside Editor
    UPROPERTY(EditAnywhere, Category = "Setup");
    class USphereComponent* OurCollider{ nullptr };

    //The visual mesh of the Actor - set inside the Editor
    UPROPERTY(EditAnywhere, Category = "Setup");
    class UStaticMeshComponent* OurVisibleComponent{ nullptr };

    //This is the function that gets called when the collider of this object 
    //overlaps another object in the world.
    //Both objects have to have the "Generate Overlap Events" set for this to work!!!!
    //This function must be a UFUNCTION
    UFUNCTION()
    void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
            UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
            bool bFromSweep, const FHitResult& SweepResult);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
