// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "game_PlayerController.h"
#include "game_PlayerController.h"
#include "game_ProjectileSpawner.h"
#include "game_Projectile.h"
#include "Utility/game_enums.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "game_EnemyCharacter.generated.h"

UCLASS()
class DRONEGAME_STETSKYI_API Agame_EnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	Agame_EnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Main enemy body mesh */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "cpp_Components")
	UStaticMeshComponent* bodyMesh;

	/** Indicator that displays if enemy sees a player mesh */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "cpp_Components")
	UStaticMeshComponent* playerDetectionIndicatorMesh;

	/** Enemies gun mesh */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "cpp_Components")
	UStaticMeshComponent* gunMesh;

	/** Enemies guns muzzle mesh */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "cpp_Components")
	UStaticMeshComponent* muzzleMesh;

	/** Actor placed on top of muzzle that spawns projectiles (BLUEPRINT) */
	UPROPERTY(EditAnywhere, Category = "cpp_Components")
	TSubclassOf<Agame_ProjectileSpawner> BP_projectileSpawner;

	/** Reference to Blueprint actor that spawns projectiles */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "cpp_Components")
	Agame_ProjectileSpawner* projectileSpawner;

	/** Mostly responsible for collision with player and projectiles */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "cpp_Components")
	UCapsuleComponent* capsuleCollider;

	/* Can be subscribed to OnComponentOverlap event
	   Handles all required information when component
	   starts overlapping with some other actor */
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/** Amount of damage to be dealt to player if he crashes into enemy */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "cpp_Other")
	int onCrashDamage;

	/** Declares entity type responsible for how
	 *	it will interact with other entities */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "cpp_EntityType")
	EEntity entityType;

	int health;

	int lastFrameDamage;

	void DieOn0HP();

};
