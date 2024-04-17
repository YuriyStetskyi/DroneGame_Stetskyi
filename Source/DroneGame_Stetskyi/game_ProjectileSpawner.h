// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "game_Projectile.h"
#include "game_ProjectileSpawner.generated.h"

UCLASS()
class DRONEGAME_STETSKYI_API Agame_ProjectileSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Agame_ProjectileSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Projectile that will be spawnwed */
	UPROPERTY(EditAnywhere)
	TSubclassOf<class Agame_Projectile> projectile;

	/** Spawners mesh. Create to be able to move it around*/
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* spawnerMesh;

	/** Spawns a projectile that movies in given direction */
	void Spawn(FVector movementDirection);
};
