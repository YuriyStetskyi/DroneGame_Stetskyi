// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "game_ProjectileSpawner.h"
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

	/** Guns muzzle that spawns projectiles */
	UPROPERTY(EditAnywhere, Category = "cpp_Components")
	Agame_ProjectileSpawner* gunMuzzle;

	/** Players gun */
	UPROPERTY(EditAnywhere, Category = "cpp_Components")
	UStaticMeshComponent* gun;

	/** Finds gun muzzle in scene */
	Agame_ProjectileSpawner* FindGunMuzzle();

	UPROPERTY(EditAnywhere, Category = "cpp_Testing")
	FVector cameraForwVector;

};
