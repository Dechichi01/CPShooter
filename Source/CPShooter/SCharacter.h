// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

UCLASS()
class CPSHOOTER_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASCharacter();

protected:
	
	UPROPERTY()
	class UCameraComponent* CameraComp;
	class USpringArmComponent* SpringArmComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FORCEINLINE void MoveForward(const float Axis) { AddMovementInput(GetActorForwardVector()*Axis); }
	FORCEINLINE void MoveRight(const float Axis) { AddMovementInput(GetActorRightVector()*Axis); };
	FORCEINLINE void LookUp(const float Axis) { AddControllerPitchInput(Axis); };
	FORCEINLINE void Turn(const float Axis) { AddControllerYawInput(Axis); }

	FORCEINLINE void CrouchAction() { Crouch(); }
	FORCEINLINE void UnCrouchAction() { UnCrouch(); }
	FORCEINLINE void JumpAction() { Jump(); };

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
