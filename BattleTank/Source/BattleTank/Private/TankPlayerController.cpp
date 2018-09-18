// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
//#include "Tank.h"
#include "TankAimingComponent.h"
#include "BattleTank.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	FoundAimingComponent(AimingComponent);

}


void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}



//ATank* ATankPlayerController::GetControlledTank() const
//{
//	return GetPawn();
//}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; }
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	auto Time = GetWorld()->GetTimeSeconds();

	FVector HitLocation; //Out parameter
	bool bGotHitLocation = GetSightRayHitLocation(HitLocation);
	//UE_LOG(LogTemp, Warning, TEXT("bGotHitLocation: %i"), bGotHitLocation);
	if (bGotHitLocation) // Has side-effect , is going to line trace
	{
		

		AimingComponent->AimAt(HitLocation);

		// TODO Tell controlled tank to aim at this point
	}
}

// Get world location  of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{


	//Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	

	// "De-project" the screen position of the crosshair to world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{

		// Line-trace along that LookDirection, and see what we hit (up to max range)
		// GetLookVectorHitLocation();
		return GetLookVectorHitLocation(LookDirection, HitLocation);

		
	}


	return false;
}


bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility))// Line trace succeeds
	{
		// Set hit location
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0, 0, 0);
	return false;
}


bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{

	FVector CameraWorldLocation; // To be discarded

	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);

}