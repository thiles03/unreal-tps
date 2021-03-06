#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "CPP_TPS_GrabHandler.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class THIRDPERSONSURVIVAL_API UCPP_TPS_GrabHandler : public UActorComponent
{
	GENERATED_BODY()

public:
	UCPP_TPS_GrabHandler();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

private:
	// COMPONENTS
	UPhysicsHandleComponent *PhysicsHandle = nullptr;

	UInputComponent *Input = nullptr;

	// VARIABLES
	UPROPERTY(EditAnywhere)
	float Reach = 100.f;

	// FUNCTIONS
	void Grab();

	void Release();

	void FindPhysicsHandle();

	void SetupInputComponent();

	FHitResult GetFirstPhysicsBodyInReach() const;

	FVector GetPlayerInteractPoint() const;

	FVector GetPlayerViewPos() const;
};
