// Fill out your copyright notice in the Description page of Project Settings.

#include "SWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Debug/Debug.h"
#include "DrawDebugHelpers.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/Pawn.h"

static const char* MUZZLE_SOCKET_NAME = "MuzzleSocket";
static const char* TRACE_TARGET_NAME = "BeamTarget";
// Sets default values
ASWeapon::ASWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	RootComponent = SkeletalMeshComp;

	RayTraceDistance = 10000.f;
	CollisionChannel = ECC_Visibility;

	MuzzleSocketName = MUZZLE_SOCKET_NAME;
	ShotTraceTargetName = TRACE_TARGET_NAME;
}

// Called when the game starts or when spawned
void ASWeapon::BeginPlay()
{
	Super::BeginPlay();

}

void ASWeapon::Fire()
{
	AActor* Owner = GetOwner();

	if (ENSURE(Owner))
	{
		FVector EyeLocation;
		FRotator EyeRotation;
		Owner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

		FVector EndTrace = EyeLocation + EyeRotation.Vector()*RayTraceDistance;

		FCollisionQueryParams Query;
		Query.AddIgnoredActor(Owner);
		Query.AddIgnoredActor(this);
		Query.bTraceComplex = true;
		
		FHitResult HitResult;

		if (GetWorld()->LineTraceSingleByChannel(HitResult, EyeLocation, EndTrace, CollisionChannel, Query))
		{
			AActor* HitActor = HitResult.GetActor();
			EndTrace = HitResult.Location;
			UGameplayStatics::ApplyPointDamage(HitActor, Damage, HitResult.ImpactNormal, HitResult, Owner->GetInstigatorController(), this, DamageType);

			if (HitFx)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitFx, EndTrace, HitResult.ImpactNormal.Rotation());
			}
		}

		DrawDebugLine(GetWorld(), EyeLocation, EndTrace, FColor::Red, false, 1.f);

		if (MuzzleFx)
		{
			UGameplayStatics::SpawnEmitterAttached(MuzzleFx, RootComponent, MuzzleSocketName);
		}

		if (ShotTraceFx)
		{
			FVector MuzzleLocation = SkeletalMeshComp->GetSocketLocation(MuzzleSocketName);
			UParticleSystemComponent* TraceParticle = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ShotTraceFx, MuzzleLocation);

			if (ENSURE(TraceParticle))
			{
				TraceParticle->SetVectorParameter(ShotTraceTargetName, EndTrace);
			}
		}

		APawn* Pawn = Cast<APawn>(Owner);
		if (ENSURE(Pawn))
		{
			APlayerController* PlayerController = Cast<APlayerController>(Pawn->GetController());
			if (ENSURE(PlayerController))
			{
				PlayerController->ClientPlayCameraShake(FireCameraShakeParams);
			}
		}
	}
}

// Called every frame
void ASWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

