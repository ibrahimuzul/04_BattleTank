// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"


void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet)
{
	Barrel = BarrelToSet;
}

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}




// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	/*auto OurTankName =GetOwner()->GetName();
	auto BarrelLocation = Barrel->GetComponentLocation().ToString();
	UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s"), *OurTankName, *HitLocation.ToString(), *BarrelLocation);*/

	if (!Barrel) { return; }

	FVector OutLaunchVelocity = FVector(0.f, 0.f, 0.f);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));


	//Calculate the OutLunchVelocity
	if (UGameplayStatics::SuggestProjectileVelocity(
		this,
		OUT OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0.f,
		0.f,
		ESuggestProjVelocityTraceOption::DoNotTrace
		/*FCollisionResponseParams::DefaultResponseParam,
		TArray<AActor*>(),
		true*/
	))
	{

		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		auto TankName = GetOwner()->GetName();

		UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"),*TankName, *AimDirection.ToString());
	}

	// if no solution found do nothing
}

