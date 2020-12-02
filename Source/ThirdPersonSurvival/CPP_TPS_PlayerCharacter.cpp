#include "CPP_TPS_PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ACPP_TPS_PlayerCharacter::ACPP_TPS_PlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void ACPP_TPS_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void ACPP_TPS_PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACPP_TPS_PlayerCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("FireWeapon", IE_Pressed, this, &ACPP_TPS_PlayerCharacter::Fire);
	PlayerInputComponent->BindAction("FireWeapon", IE_Released, this, &ACPP_TPS_PlayerCharacter::CheckFire);
}

void ACPP_TPS_PlayerCharacter::Fire() 
{
	UE_LOG(LogTemp, Warning, TEXT("fire"));
	IsFiring = true;
}

void ACPP_TPS_PlayerCharacter::CheckFire() 
{
	UE_LOG(LogTemp, Warning, TEXT("check fire"));
	IsFiring = false;
}
