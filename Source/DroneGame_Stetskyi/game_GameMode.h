// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "game_PlayerController.h"
#include "game_PlayerState.h"
#include "game_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class DRONEGAME_STETSKYI_API Agame_GameMode : public AGameModeBase
{
	GENERATED_BODY()
	
	Agame_GameMode();
	void BeginPlay();
	void Tick(float DeltaTime);
};
