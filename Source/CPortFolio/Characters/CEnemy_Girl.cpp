// Fill out your copyright notice in the Description page of Project Settings.


#include "CEnemy_Girl.h"

// Sets default values
ACEnemy_Girl::ACEnemy_Girl()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACEnemy_Girl::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACEnemy_Girl::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACEnemy_Girl::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

