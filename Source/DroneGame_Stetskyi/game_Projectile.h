// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "game_Projectile.generated.h"

UCLASS()
class DRONEGAME_STETSKYI_API Agame_Projectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Agame_Projectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Mesh of the projectile (sphere) */
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* projectileMesh;
	
	/** Projectiles movement component */
	UPROPERTY(EditAnywhere)
	UProjectileMovementComponent* projectileMovement;

	/** Sets direction in which projectile will move */
	void SetMovementDirection(FVector movementDirection);

	/* Can be subscribed to OnComponentOverlap event
	   Handles all required information when component
	   starts overlapping with some other actor */
	UFUNCTION()
	void Detector_OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
