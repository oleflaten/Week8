// Ole EF

#include "MyPawn.h"
#include "Camera/CameraActor.h"
#include "MyBullet.h"
#include "Components/SphereComponent.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a dummy root component we can attach things to.
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	OurVisibleComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();

	//Adding the camera to the Player. This has to be made and assigned  
	//inside Unreal Editor else this will crash!
	// GetFirstPlayerController == Player0
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->SetViewTarget(StaticCamera);
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Positioin of Player is updated every tick by the size of CurrentVelocity
	//If CurrentVelocity == 0 no movement will happen
	FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
	SetActorLocation(NewLocation);
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Setting functions to run when Axis and Action events are triggered:
	PlayerInputComponent->BindAxis("Forward", this, &AMyPawn::MoveForward);
	PlayerInputComponent->BindAxis("Right", this, &AMyPawn::MoveRight);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AMyPawn::Shoot);
}

void AMyPawn::MoveForward(float Value)
{
	//Clamp can be necessary if you use several input types at the same time!
	CurrentVelocity.X = FMath::Clamp(Value, -1.f, 1.f) * MoveSpeed;
}

void AMyPawn::MoveRight(float Value)
{
	//Clamp can be necessary if you use several input types at the same time!
	CurrentVelocity.Y = FMath::Clamp(Value, -1.f, 1.f) * MoveSpeed;
}

void AMyPawn::Shoot()
{
	//Here next weeks code will come - spawn bullets
	UE_LOG(LogTemp, Warning, TEXT("Bang!"));

	//The spawn function belongs to the World object
	//Get the pointer it because we use it several times here.
	UWorld* World = GetWorld();		

	if (World && Ammo > 0)			//check if World is valid
	{
		//Spawns bullet at Player location + SpawnPoint 
		World->SpawnActor<AMyBullet>(BulletBlueprint, GetActorLocation() + SpawnPoint, GetActorRotation());
		Ammo--;
		Health--;
	}
}