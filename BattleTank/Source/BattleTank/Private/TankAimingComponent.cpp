// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"


void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	if (!BarrelToSet) { return; }
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
	if (!TurretToSet) { return; }
	Turret = TurretToSet;
}

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; // TODO Should this really tick ?

	// ...
}




////// Called when the game starts
////void UTankAimingComponent::BeginPlay()
////{
////	Super::BeginPlay();
////
////	// ...
////
////}
////
////
////// Called every frame
////void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
////{
////	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
////
////	// ...
////}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	/*auto OurTankName =GetOwner()->GetName();
	auto BarrelLocation = Barrel->GetComponentLocation().ToString();
	UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s"), *OurTankName, *HitLocation.ToString(), *BarrelLocation);*/

	if (!Barrel) { return; }

	FVector OutLaunchVelocity = FVector(0.f, 0.f, 0.f);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OUT OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0.f,
		0.f
		,ESuggestProjVelocityTraceOption::DoNotTrace // comment this line to produce bug
		/*FCollisionResponseParams::DefaultResponseParam,
		TArray<AActor*>(),
		true*/
	);

	//Calculate the OutLunchVelocity
	if (bHaveAimSolution)
	{

		auto AimDirection = OutLaunchVelocity.GetSafeNormal();

		MoveBarrelTowards(AimDirection);

		auto Time = GetWorld()->GetTimeSeconds();

		UE_LOG(LogTemp, Warning, TEXT("%f : Aim Solution found"), Time);

		/*UE_LOG(LogTemp, Warning, TEXT("Aiming at %s"), *AimDirection.ToString());*/
		
		/*auto TankName = GetOwner()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"),*TankName, *AimDirection.ToString());*/
	}
	else
	{
		auto Time = GetWorld()->GetTimeSeconds();

		UE_LOG(LogTemp, Warning, TEXT("%f : No aim solve found"), Time);
	}

	// if no solution found do nothing
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// Work-out difference between current barrel rotation, and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	UE_LOG(LogTemp, Warning, TEXT("DeltaRotator: %s"), *DeltaRotator.ToString());

	Barrel->Elevate(DeltaRotator.Pitch);

}