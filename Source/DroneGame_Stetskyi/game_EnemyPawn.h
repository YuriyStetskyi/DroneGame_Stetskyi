// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "game_PlayerController.h"
#include "game_PlayerController.h"
#include "game_EnemyPawn.generated.h"

UCLASS()
class DRONEGAME_STETSKYI_API Agame_EnemyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	Agame_EnemyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Main enemy body mesh */
	UPROPERTY(EditAnywhere, Category = "cpp_Components")
	UStaticMeshComponent* bodyMesh;


	/* Can be subscribed to OnComponentOverlap event
	   Handles all required information when component
	   starts overlapping with some other actor */
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/** Amount of damage to be dealt to player if he crashes into enemy */
	int onCrashDamage;
};
