// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "game_PlayerCharacter.h"
#include "game_PlayerState.h"
#include "Utility/game_enums.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Components/ActorComponent.h"
#include "game_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DRONEGAME_STETSKYI_API Agame_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
	void BeginPlay();
public:

	Agame_PlayerController();

	void Tick(float DeltaTime);

	/*  Called to bind functionality to input */
	virtual void SetupInputComponent() override;

	// POSESSED PAWN ////////////////////////////////////////////



	/** Main player actor to posess */
	UPROPERTY (EditAnywhere, BlueprintReadWrite, Category = "cpp_PlayerCharacter")
	Agame_PlayerCharacter* playerCharacter;

	/** Main player actor to posess */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "cpp_PlayerCharacter")
	TSubclassOf<Agame_PlayerCharacter> BP_playerCharacter;

	/** Finds player actor to posess*/
	Agame_PlayerCharacter* FindPlayerCharacter();



	// MOVEMENT /////////////////////////////////////////////

	/** Updated via keyboard/controller input */
	UPROPERTY(VisibleAnywhere, Category = "cpp_Movement")
	float forwardInput;

	/** Updated via keyboard/controller input */
	UPROPERTY(VisibleAnywhere, Category = "cpp_Movement")
	float rightInput;

	/** If input < threshold - ignore input */
	float inputThreshold;

	/** Changes value of forwardInput depending on player input */
	void MoveForward(float value);

	/** Changes value of rightInput depending on player input */
	void MoveRight(float value);

	/** Handles player character movement
		@param fInput - forward input read from keyboard/controller (W key/ S key)
		@param rInput - right input read from keyboard/controller (D key/ A key) */
	void MoveOnInput(Agame_PlayerCharacter* character, float fInput, float rInput, float uInput, float DeltaTime);

	/** Current player movement direction */
	UPROPERTY(VisibleAnywhere, Category = "cpp_Movement")
	FVector movementDirection;

	/** Current player velocity */
	FVector currentVelocity;

	/** Current max speed player can achieve */
	UPROPERTY(VisibleAnywhere, Category = "cpp_Movement")
	float maxSpeed;

	/** Current player acceleration */
	UPROPERTY(VisibleAnywhere, Category = "cpp_Movement")
	float acceleration;



	// CAMERA MOVEMENT //////////////////////////////////////

	/** Camera sensitivity (speed) */
	UPROPERTY(VisibleAnywhere, Category = "cpp_Camera")
	float cameraSensitivity;

	/** Updated via mouse/controller input */
	UPROPERTY(VisibleAnywhere, Category = "cpp_Camera")
	float cameraPitch;

	/** Updated via mouse/controller input */
	UPROPERTY(VisibleAnywhere, Category = "cpp_Camera")
	float cameraYaw;

	/** Changes cameraPitch variable depending on Mouse/Controller input */
	void LookUp(float value);

	/** Changes cameraYaw variable depending on Mouse/Controller input */
	void LookRight(float value);

	/** Handles player camera movement */
	void RotateCameraOnInput(Agame_PlayerCharacter* character, float pitch, float yaw, float DeltaTime);

	

	// FLYING MOVEMENT /////////////////////////////////////

	/** Updated via keyboard/controller input */
	UPROPERTY(VisibleAnywhere, Category = "cpp_Movement")
	float upInput;

	/** Changes value of forwardInput depending on player input */
	void MoveUp(float value);



	// COMBAT ///////////////////////////////////////////

	/** Shoots a projectile */
	void Shoot();

	/** Returns vector representing where the guns projectile should fly */
	FVector GetFlightTrajectory();

	/** Flight trajectory from a gun to a position pointed at by crosshair */
	FVector projectileFlightTrajectory;



	// STATES /////////////////////////////////////////////

	/** Stores the data connected to the player: health, ammo, current weapon etc. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "cpp_States")
	Agame_PlayerState* plState;



	// HEALTH SYSTEM //////////////////////////////////////

	/** If damage taken last frame != 0 - subtract that amount from health */
	void GetDamagedOnHit(Agame_PlayerCharacter* character);

	/** If health = 0 - destroy players pawn */
	void DieOn0HP();

	/** Handles player pawn's respawning */
	UFUNCTION (BlueprintCallable)
	void Respawn();
};
