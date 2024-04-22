// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Utility/game_enums.h"
#include "game_PlayerController.h"
#include "game_PlayerCharacter.h"
#include "game_Pickup.generated.h"

UCLASS()
class DRONEGAME_STETSKYI_API Agame_Pickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Agame_Pickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



	// TYPE ////////////////////////////////////////////////////////////

	/** This determines what behaviour player will manifest on collision */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "cpp_PickupType")
	EPickup pickupType;

	/** Declares entity type responsible for how
	 *	it will interact with other entities */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "cpp_EntityType")
	EEntity entityType;

	/** Pickups mesh */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "cpp_PickupType")
	UStaticMeshComponent* mesh;

	/* Can be subscribed to OnComponentOverlap event
	   Handles all required information when component
	   starts overlapping with some other actor */
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);



	// PICKUP PARAMS //////////////////////////////////////////////////

	/** Replenish amount for ammo pickup */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "cpp_Other")
	int replenishAmount_AMMO;

	/** Replenish amount for health pickup */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "cpp_Other")
	int replenishAmount_HEALTH;

	/** Replenishes specified amount of ammo for a player 
	*	@return Returns true if replenished ammo successfully */
	UFUNCTION(BlueprintCallable)
	bool ReplenishAmmo(Agame_PlayerCharacter* player, int amount);

	/** Replenishes specified amount of health for a player 
	*	@return Returns true if replenished health successfully */
	UFUNCTION(BlueprintCallable)
	bool ReplenishHealth(Agame_PlayerCharacter* player, int amount);

};
