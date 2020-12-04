#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPP_TPS_PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class THIRDPERSONSURVIVAL_API ACPP_TPS_PlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ACPP_TPS_PlayerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:
	// COMPONENTS
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent *SpringArm = nullptr;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent *Camera = nullptr;

	// VARIABLES
	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = "States", meta = (AllowPrivateAccess = "true"))
	bool IsFiring = false;

	// FUNCTIONS
	void Fire();
	
	void CheckFire();
};
