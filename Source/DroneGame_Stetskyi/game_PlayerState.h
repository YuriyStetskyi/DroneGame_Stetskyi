// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "game_PlayerState.generated.h"

/**
 * 
 */
UCLASS()
class DRONEGAME_STETSKYI_API Agame_PlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	Agame_PlayerState();
	void BeginPlay();
	void Tick(float DeltaTime);

	/** Players current health */
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, category = "cpp_State")
	int playerHealth;

	/** Players minimum health */
	int minHealth;

	/** Players maximum health */
	int maxHealth;

	/** Players current ammo */
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, category = "cpp_State")
	int playerAmmo;
	
	/** Players minimum ammo */
	int minAmmo;

	/** Players maximum ammo */
	int maxAmmo;

	/** Depletes ammo on "Shoot" */
	void DepleteAmmo(int amount);

	/** Replenish ammo with specified amount, but not more than max ammo
	*	@return Returns true if replenished ammo successfully */
	bool ReplenishAmmo(int amount);

	/** Retruns true if playerState has ammo */
	bool HasAmmo();

	/** Depletes ammo on damaged */
	void DepleteHealth(int amount);

	/** Replenish Health with specified amount, but not more than max health
	*	@return Returns true if replenished health successfully */
	bool ReplenishHealth(int amount);
};
