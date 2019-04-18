// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPawn.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Classes/Camera/CameraComponent.h"
#include "TPPlayerMovementComponent.h"
#include "SnapToGridComponent.h"
#include "Components/InputComponent.h"


// Sets default values
ATPPawn::ATPPawn(const FObjectInitializer &ObjectInitializer)
	: Super(ObjectInitializer)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Our root component will be a sphere that reacts to physics
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	SphereCollision->SetCollisionProfileName(TEXT("BlockAll")); //?
	//SphereCollision->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	//SphereCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	RootComponent = SphereCollision;

	// Create and position a mesh component so we can see where our sphere is
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereVisualRepresentation"));
	MeshComponent->SetupAttachment(RootComponent);
	MeshComponent->SetCollisionProfileName(TEXT("OverlapAll"));
	//MeshComponent->SetCollisionObjectType(ECollisionChannel::ECC_Visibility);
	//MeshComponent->BodyInstance.SetResponseToChannel(ECC_Pawn, ECR_Overlap);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraMain"));
	CameraComponent->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 400.0f), FRotator(-90.0f, 0.0f, 0.0f));
	CameraComponent->SetupAttachment(RootComponent);

	// Create an instance of our movement component, and tell it to update the root.
	MovementComponent = CreateDefaultSubobject<UTPPlayerMovementComponent>(TEXT("CustomMovementComponent"));
	MovementComponent->UpdatedComponent = RootComponent;

	// Take control of the default player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//Create Snap Component
	SnapComponent = CreateDefaultSubobject<USnapToGridComponent>(TEXT("SnapComponent"));
}

// Called when the game starts or when spawned
void ATPPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATPPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATPPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATPPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATPPawn::MoveRight);

}

UPawnMovementComponent* ATPPawn::GetMovementComponent() const
{
	return MovementComponent;
}

void ATPPawn::MoveForward(float AxisValue)
{
	if (MovementComponent && (MovementComponent->UpdatedComponent == RootComponent))
	{
		MovementComponent->AddInputVector(GetActorForwardVector() * AxisValue);
	}
}

void ATPPawn::MoveRight(float AxisValue)
{
	if (MovementComponent && (MovementComponent->UpdatedComponent == RootComponent))
	{
		MovementComponent->AddInputVector(GetActorRightVector() * AxisValue);
	}
}

void ATPPawn::OnConstruction(const FTransform & Transform) {
	//Snap to grid cells
	SnapComponent->Snap();

	//Set Collision size according to the mesh
	SphereCollision->SetSphereRadius(MeshComponent->Bounds.SphereRadius);

	//Set mesh location according to collision
	MeshComponent->SetRelativeLocation(FVector(0., 0., -MeshComponent->Bounds.Origin.Z/ 2.));

}
