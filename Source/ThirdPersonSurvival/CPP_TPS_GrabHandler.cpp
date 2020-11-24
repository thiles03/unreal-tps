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
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	GetFirstPhysicsBodyInReach(); // Remove after testing
}

void UCPP_TPS_GrabHandler::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("grab"));
	GetFirstPhysicsBodyInReach();
	// If hit something, attach physics handle
}

void UCPP_TPS_GrabHandler::Drop()
{
	UE_LOG(LogTemp, Warning, TEXT("drop"));
	// Remove physics handle
}

void UCPP_TPS_GrabHandler::FindPhysicsHandle()
{
	// Check for physics handle component
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{
		// Handle found
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No physics handle on %s!"), *GetOwner()->GetName());
	}
}

void UCPP_TPS_GrabHandler::SetupInputComponent()
{
	Input = GetOwner()->FindComponentByClass<UInputComponent>();
	if (Input)
	{
		Input->BindAction("Interact", IE_Pressed, this, &UCPP_TPS_GrabHandler::Grab);
		Input->BindAction("Interact", IE_Released, this, &UCPP_TPS_GrabHandler::Drop);
	}
}

FHitResult UCPP_TPS_GrabHandler::GetFirstPhysicsBodyInReach() const
{
	FVector PlayerViewpointLocation;
	FRotator PlayerViewpointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewpointLocation,
		OUT PlayerViewpointRotation
	);

	FVector LineTraceEnd = PlayerViewpointLocation + FVector(PlayerViewpointRotation.Vector() * Reach);

	DrawDebugLine(
		GetWorld(),
		PlayerViewpointLocation,
		LineTraceEnd,
		FColor(0, 255 , 0),
		false,
		0.f,
		0,
		5.f
	);

	FHitResult Hit;

	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewpointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	AActor* ActorHit = Hit.GetActor();

	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *ActorHit->GetName());
	}

	return Hit;
}