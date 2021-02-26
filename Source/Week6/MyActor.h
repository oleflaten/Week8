// Ole EF

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class WEEK6_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//The visual mesh of the Actor - set inside the Editor
	UPROPERTY(EditAnywhere);
	UStaticMeshComponent* OurVisibleComponent{ nullptr };
	
	//Rotation and movement-speed can be changed from the Editor
	UPROPERTY(EditAnywhere, Category = "Speed")
	float RotateSpeed{ 50.f };
	UPROPERTY(EditAnywhere, Category = "Speed")
	float MoveSpeed{ 50.f };

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//This is a function that the bullet can call to inform this actor
	//Then we can calculate health or other stuff needed(health not implemented yet)
	void ImHit();

};
