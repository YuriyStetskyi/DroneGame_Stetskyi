// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Utility/game_enums.h"
#include "game_ProjectileSpawner.h"
#include "game_component_gunMuzzle.h"
#include "game_PlayerCharacter.generated.h"

UCLASS()
class DRONEGAME_STETSKYI_API Agame_PlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	Agame_PlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Players capsule collider */
	UPROPERTY(EditAnywhere, Category = "cpp_Components")
	UCapsuleComponent* capsuleCollider;

	/** Players camera */
	UPROPERTY(EditAnywhere, Category = "cpp_Components")
	UCameraComponent* camera;

	/** Mesh of players drone body */
	UPROPERTY(EditAnywhere, Category = "cpp_Components")
	UStaticMeshComponent* bodyMesh;

	/** Guns muzzle that spawns projectiles */
	UPROPERTY(EditAnywhere, Category = "cpp_Components")
	UStaticMeshComponent* muzzleMesh;

	/** Actor placed on top of muzzle that spawns projectiles (BLUEPRINT) */
	UPROPERTY(EditAnywhere, Category = "cpp_Components")
	TSubclassOf<Agame_ProjectileSpawner> BP_projectileSpawner;

	/** Reference to Blueprint actor that spawns projectiles */
	UPROPERTY(EditAnywhere, Category = "cpp_Components")
	Agame_ProjectileSpawner* projectileSpawner;

	/** Players gun */
	UPROPERTY(EditAnywhere, Category = "cpp_Components")
	UStaticMeshComponent* gun;

	/** Declares entity type responsible for how 
	 *	it will interact with other entities */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "cpp_EntityType")
	EEntity entityType;

	UPROPERTY(EditAnywhere, Category = "cpp_Testing")
	FVector cameraForwVector;

	/* Can be subscribed to OnComponentOverlap event
	   Handles all required information when component
	   starts overlapping with some other actor */
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	int lastFrameDamage;
};
