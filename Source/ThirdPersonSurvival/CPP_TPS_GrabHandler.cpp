#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "CPP_TPS_GrabHandler.h"

#define OUT

UCPP_TPS_GrabHandler::UCPP_TPS_GrabHandler()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UCPP_TPS_GrabHandler::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandle();
	SetupInputComponent();
}

// Called every frame
void UCPP_TPS_GrabHandler::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{	
	// If an object is grabbed, move it
	if (!PhysicsHandle) {return;}
	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(GetPlayerInteractPoint());
	}
}

// Check for physics handle component
void UCPP_TPS_GrabHandler::FindPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("No physics handle on %s!"), *GetOwner()->GetName());
	}
}

// Check for input component and bind input mappings
void UCPP_TPS_GrabHandler::SetupInputComponent()
{
	Input = GetOwner()->FindComponentByClass<UInputComponent>();
	if (Input)
	{
		Input->BindAction("Interact", IE_Pressed, this, &UCPP_TPS_GrabHandler::Grab); // Grab
		Input->BindAction("Interact", IE_Released, this, &UCPP_TPS_GrabHandler::Release); // Release
	}
}

// Returns line trace end
FVector UCPP_TPS_GrabHandler::GetPlayerInteractPoint() const
{
	FVector PlayerViewpointLocation;
	FRotator PlayerViewpointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewpointLocation,
		OUT PlayerViewpointRotation
	);

	FVector LineTraceEnd = PlayerViewpointLocation + FVector(PlayerViewpointRotation.Vector() * Reach);

	return LineTraceEnd;
}

// Returns player viewpoint world position
FVector UCPP_TPS_GrabHandler::GetPlayerViewPos() const
{
	FVector PlayerViewpointLocation;
	FRotator PlayerViewpointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewpointLocation,
		OUT PlayerViewpointRotation
	);

	return PlayerViewpointLocation;
}

// Returns physics body hit by line trace
FHitResult UCPP_TPS_GrabHandler::GetFirstPhysicsBodyInReach() const
{
	FHitResult Hit;

	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		GetPlayerViewPos(),
		GetPlayerInteractPoint(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	return Hit;
}

// Grab hit physics body
void UCPP_TPS_GrabHandler::Grab()
{
	FHitResult HitResult =  GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* GrabbedComponent = HitResult.GetComponent();

	// If hit something, attach physics handle
	if(HitResult.GetActor())
	{
		if (!PhysicsHandle) {return;}
		PhysicsHandle->GrabComponentAtLocation(
			GrabbedComponent,
			NAME_None,
			GetPlayerInteractPoint()
		);
	}
}

// Release grabbed physics body
void UCPP_TPS_GrabHandler::Release()
{
	if (!PhysicsHandle) {return;}
	PhysicsHandle->ReleaseComponent();
}