// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"



void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	//auto PlayerTank = GetPlayerTank();
	//if (!PlayerTank)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("AIController cant find player tank"));
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("AIController found player: %s"), *(PlayerTank->GetName()));
	//}

}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank =Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank  = Cast<ATank>(GetPawn());

	//if (GetPlayerTank())
	if (PlayerTank)
	{
		// TODO Move towards the player

		// Aim towards the player
		
		ControlledTank->AimAt(PlayerTank->GetActorLocation());
		//GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
		

		// Fire if ready
		//GetControlledTank()->Fire();
		ControlledTank->Fire(); // TODO limit firing rate
	}
}

//ATank* ATankAIController::GetControlledTank() const
//{
//	return Cast<ATank>(GetPawn());
//}


//ATank * ATankAIController::GetPlayerTank() const
//{
//	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
//	if (!PlayerPawn) { return nullptr; }
//	return Cast<ATank>(PlayerPawn);
//}