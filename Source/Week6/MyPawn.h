// Ole EF

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

UCLASS()
class WEEK6_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Constructor
	AMyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//The mesh - assigned inside Unreal Editor
	UPROPERTY(EditAnywhere, Category = "Setup");
	USceneComponent* OurVisibleComponent{ nullptr };

	//Speed - can be changed inside Unreal Editor
	UPROPERTY(EditAnywhere, Category = "Setup");
	float MoveSpeed{ 150.f };

	//The static camera - assigned inside Unreal Editor
	UPROPERTY(EditAnywhere, Category = "Setup");
	ACameraActor* StaticCamera{ nullptr };

	//The type we will use as bullets - assigned inside Unreal Editor
	UPROPERTY(EditAnywhere, Category = "Setup");
	TSubclassOf<class AMyBullet> BulletBlueprint;

	//Offset from the position of this pawn - to make spawning in front
	//and up from the ground of the Pawn.
	//can be changed inside Unreal Editor
	UPROPERTY(EditAnywhere, Category = "Setup");
	FVector SpawnPoint{ 100.f, 0.f, 100.f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup");
	int Health{ 100 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup");
	int Ammo{ 100 };


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	//Functions for movement and shooting
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Shoot();

	//The movement that will be applied in the next Tick
	FVector CurrentVelocity{ 0.f };
};
