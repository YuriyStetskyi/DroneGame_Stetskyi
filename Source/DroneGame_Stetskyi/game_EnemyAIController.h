// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "game_EnemyCharacter.h"
#include "game_EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class DRONEGAME_STETSKYI_API Agame_EnemyAIController : public AAIController
{
	GENERATED_BODY()




	/** Shoots a projectile */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void ShootAtDirection(FVector shootDirection);
	
};
