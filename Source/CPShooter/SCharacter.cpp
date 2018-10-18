// Fill out your copyright notice in the Description page of Project Settings.

#include "SCharacter.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Debug/Debug.h"
#include "CPShooter.h"
#include "Net/UnrealNetwork.h"

static const FName IB_AXIS_MOVE_FORWARD = "MoveForward";
static const FName IB_AXIS_MOVE_RIGHT = "MoveRight";
static const FName IB_AXIS_LOOK_UP = "LookUp";
static const FName IB_AXIS_TURN = "Turn";
static const FName IB_ACTION_CROUCH = "Crouch";
static const FName IB_ACTION_JUMP = "Jump";

static const FName IB_ACTION_AIM = "Aim";

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp);

	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;//messy
	GetCapsuleComponent()->SetCollisionResponseToChannel(COLLISION_WEAPON, ECR_Ignore);

	AimFov = 60.f;

	USaveGame
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();

	DefaultFov = CameraComp->FieldOfView;
	TargetFov = DefaultFov;
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CameraComp->FieldOfView = FMath::FInterpTo(CameraComp->FieldOfView, TargetFov, DeltaTime, AimSpeed);
}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(IB_AXIS_MOVE_FORWARD, this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis(IB_AXIS_MOVE_RIGHT, this, &ASCharacter::MoveRight);
	PlayerInputComponent->BindAxis(IB_AXIS_LOOK_UP, this, &ASCharacter::LookUp);
	PlayerInputComponent->BindAxis(IB_AXIS_TURN, this, &ASCharacter::Turn);
	PlayerInputComponent->BindAction(IB_ACTION_CROUCH, IE_Pressed, this, &ASCharacter::CrouchAction);
	PlayerInputComponent->BindAction(IB_ACTION_CROUCH, IE_Released, this, &ASCharacter::UnCrouchAction);
	PlayerInputComponent->BindAction(IB_ACTION_JUMP, IE_Pressed, this, &ASCharacter::JumpAction);

	PlayerInputComponent->BindAction(IB_ACTION_AIM, IE_Pressed, this, &ASCharacter::Aim);
	PlayerInputComponent->BindAction(IB_ACTION_AIM, IE_Released, this, &ASCharacter::EndAim);
}

FVector ASCharacter::GetPawnViewLocation() const
{
	if (ENSURE(CameraComp))
	{
		return CameraComp->GetComponentLocation();
	}

	return Super::GetPawnViewLocation();
}

void ASCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//DOREPLIFETIME(ASCharacter, CurrentWeapon);
}

