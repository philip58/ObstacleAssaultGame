// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	StartLocation = GetActorLocation();

}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	//Move Plaform
	//Get location
	FVector CurrentLocation = GetActorLocation();
	//Add vector to location 
	CurrentLocation+=(PlatformVelocity * DeltaTime);

	//Set location
	SetActorLocation(CurrentLocation);

	//check distance moved
	float DistanceMoved = FVector::Distance(StartLocation, CurrentLocation);

	//reverse if gone too far 
	if(DistanceMoved > MoveDistance)
	{
		//Get object name and overshoot then Log it to output log
		FString Name = GetName();

		UE_LOG(LogTemp, Display, TEXT("Here's My Platform: %s"), *Name);

		float OverShoot = DistanceMoved - MoveDistance;

		UE_LOG(LogTemp, Display, TEXT("Platform overshot by %f"),OverShoot);

		//reverse moving object
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();

		StartLocation += MoveDirection * MoveDistance;

		SetActorLocation(StartLocation);

		PlatformVelocity = -PlatformVelocity;

	}

}


