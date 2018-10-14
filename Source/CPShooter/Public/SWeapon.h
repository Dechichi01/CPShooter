// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SWeapon.generated.h"

UCLASS()
class CPSHOOTER_API ASWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASWeapon();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USkeletalMeshComponent* SkeletalMeshComp;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon Parms")
	float Damage;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon Params")
	TSubclassOf<class UDamageType> DamageType;

	UPROPERTY(EditAnywhere, Category = "Shot Params")
	float RayTraceDistance;

	UPROPERTY(EditDefaultsOnly, Category = "Shot Params")
	TEnumAsByte<ECollisionChannel> CollisionChannel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FX")
	class UParticleSystem* MuzzleFx;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "FX")
	FName MuzzleSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FX")
	UParticleSystem* HitFx;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FX")
	UParticleSystem* ShotTraceFx;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "FX")
	FName ShotTraceTargetName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FX")
	TSubclassOf<class UCameraShake> FireCameraShakeParams;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void Fire();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
