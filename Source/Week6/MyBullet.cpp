// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBullet.h"
#include "Components/SphereComponent.h"
#include "MyEnemy.h"

// Sets default values
AMyBullet::AMyBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Collision object and RootObject
	//We want to get hold of the parameters in this component - so we have to make it
	//with UPROPERTY in the header file and set RootComponent to it here
	OurCollider = CreateDefaultSubobject<USphereComponent>(TEXT("MyCollider"));	
	RootComponent = OurCollider;

	//Explicit setting this to true, since we definitely need it for this component
	//Should be true as default, but just to make sure:
	OurCollider->SetGenerateOverlapEvents(true);

	//Attaching the visual mesh
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	OurVisibleComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMyBullet::BeginPlay()
{
	Super::BeginPlay();

	//Connecting the Overlap-event from the engine to a function in this object
	//(Some have more luck having this in BeginPlay, but a lot of tutorials have it in the constructor)
	Cast<USphereComponent>(RootComponent)->OnComponentBeginOverlap.AddDynamic(this, &AMyBullet::OnOverlap);
}

// Called every frame
void AMyBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Calculates the age of the bullet
	TimeLived += DeltaTime;
	//if to old, we destroy it.
	if (TimeLived > TimeBeforeDestroy)
	{
		this->Destroy();
		UE_LOG(LogTemp, Warning, TEXT("Destroied"))
	}
	else   //all good - move bullet
	{
		FVector NewLocation = GetActorLocation();
		NewLocation += GetActorForwardVector() * Speed * DeltaTime;
		SetActorLocation(NewLocation);
	}
}

//The function that handles Overlap Events
//The function name can be whatever, but the function signature (the parameter list)
//has to be exactly like this!
void AMyBullet::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	//OtherActor holds the object we overlapped with
	UE_LOG(LogTemp, Warning, TEXT("Bullet Overlap %s"), *OtherActor->GetName());

	//if other actor is of a type we are interested in (eg. the enemy)
	if (OtherActor->IsA(AMyEnemy::StaticClass()))
	{
		//Enemy hit - we destroy it
		OtherActor->Destroy();
		//Alternatively we can tell the other actor that it is hit
		//so it can take some damage or do other stuff needed
		//Doing this thru a function in that other class like this:
		// Cast<AMyActor>(OtherActor)->ImHit();	
						
		//Destroy Bullet because we hit something:
		Destroy();
	}
	/* Alternative tests:
	if (OtherActor->IsA(AMyBullet::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("I hit MySelf or some of my kind"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Bullet hit something so it self destructs!"))
		Destroy();
	}*/
}
