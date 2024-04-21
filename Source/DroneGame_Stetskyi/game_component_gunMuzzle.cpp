// Fill out your copyright notice in the Description page of Project Settings.


#include "game_component_gunMuzzle.h"

// Sets default values for this component's properties
Ugame_component_gunMuzzle::Ugame_component_gunMuzzle()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	AActor* parent = GetOwner();
}


// Called when the game starts
void Ugame_component_gunMuzzle::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void Ugame_component_gunMuzzle::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

