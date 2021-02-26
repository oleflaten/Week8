// Ole EF

#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Attaching the visual mesh
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	OurVisibleComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Rotation each tick - scaled with DeltaTime
	FRotator CurrentRotation = GetActorRotation();
	CurrentRotation.Yaw += RotateSpeed * DeltaTime;
	SetActorRotation(CurrentRotation);

	//Movement each tick - scaled with DeltaTime
	FVector CurrentLocation = GetActorLocation();
	CurrentLocation += GetActorForwardVector() * MoveSpeed * DeltaTime;
	SetActorLocation(CurrentLocation);

	//You can alternatively use 
	//AddActorLocalOffset()
	//AddActorLocalRotation()
}

//Function that could be called from an OnOverlap - event
//For instance from the bullet-class
void AMyActor::ImHit()
{
	//Here we could calculate health, or other stuff (not implemented yet)
	UE_LOG(LogTemp, Warning, TEXT("I am actually hit!"))
}
