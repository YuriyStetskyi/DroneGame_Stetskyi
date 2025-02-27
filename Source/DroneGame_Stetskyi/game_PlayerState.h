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



	// HEALTH ///////////////////////////////////////////////////////////

	/** Players current health */
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, category = "cpp_State")
	int playerHealth;

	/** Players minimum health */
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, category = "cpp_State")
	int minHealth;

	/** Players maximum health */
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, category = "cpp_State")
	int maxHealth;

	/** Depletes ammo on damaged */
	void DepleteHealth(int amount);

	/** Replenish Health with specified amount, but not more than max health
	*	@return Returns true if replenished health successfully */
	bool ReplenishHealth(int amount);

	/** True if player is currently alive */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, category = "cpp_State")
	bool isAlive;



	// AMMO /////////////////////////////////////////////////////////////

	/** Players current ammo */
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, category = "cpp_State")
	int playerAmmo;
	
	/** Players minimum ammo */
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, category = "cpp_State")
	int minAmmo;

	/** Players maximum ammo */
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, category = "cpp_State")
	int maxAmmo;

	/** Depletes ammo on "Shoot" */
	void DepleteAmmo(int amount);

	/** Replenish ammo with specified amount, but not more than max ammo
	*	@return Returns true if replenished ammo successfully */
	bool ReplenishAmmo(int amount);

	/** Retruns true if plState has ammo */
	bool HasAmmo();

	

	// RESPAWN LOCATION /////////////////////////////////////////////////

	/** Sets players future respawn location */ 
	void SetRespawnLocation(FVector location, FRotator rotation);
	
	/** Player pawn's spawn location */
	FTransform spawnLocation;
};
