// Fill out your copyright notice in the Description page of Project Settings.

#include "SCharacter.h"
#include "Components/InputComponent.h"

static const FName IB_AXIS_MOVE_FORWARD = "MoveForward";
static const FName IB_AXIS_MOVE_RIGHT = "MoveRight";
static const FName IB_AXIS_LOOK_UP = "LookUp";
static const FName IB_AXIS_TURN = "Turn";
static const FName IB_ACTION_CROUCH = "Crouch";
static const FName IB_ACTION_JUMP = "Jump";

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
}

