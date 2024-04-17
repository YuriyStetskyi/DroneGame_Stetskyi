// Fill out your copyright notice in the Description page of Project Settings.


#include "game_GameMode.h"

Agame_GameMode::Agame_GameMode()
{
	PrimaryActorTick.bCanEverTick = true;

	PlayerControllerClass = Agame_PlayerController::StaticClass();
	DefaultPawnClass = Agame_PlayerController::StaticClass();
	PlayerStateClass = Agame_PlayerState::StaticClass();
}

void Agame_GameMode::BeginPlay()
{
	Super::BeginPlay();

}

void Agame_GameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}