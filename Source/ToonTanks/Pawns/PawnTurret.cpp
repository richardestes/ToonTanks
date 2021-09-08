// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"

// Called when the game starts or when spawned
void APawnTurret::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);
	// GetWorldTimerManager(); // same thing
	
	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this,0)); //finds Pawn at 0 index (Player 1)
}

void APawnTurret::HandleDestruction() 
{
	// Call PawnBase class HandleDestruction to play effects
	Super::HandleDestruction();
	Destroy();
}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!PlayerPawn || ReturnDistanceToPlayer() > FireRange)
	{
		return;
	}
	
	RotateTurret(PlayerPawn->GetActorLocation());

}


void APawnTurret::CheckFireCondition() 
{
	// If Player == null || is Dead THEN BAIL!!
	if (!PlayerPawn || !PlayerPawn->GetIsPlayerAlive())
	{
		return;
	}
	// If Player IS in range THEN FIRE!!
	if (ReturnDistanceToPlayer() <= FireRange)
	{
		Fire();
	}
}

float APawnTurret::ReturnDistanceToPlayer() 
{
	if (!PlayerPawn)
	{
		return 0.0f;
	}
	
	return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation()); // gets distance vector between two location vectors
}
