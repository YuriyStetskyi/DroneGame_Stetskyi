// Fill out your copyright notice in the Description page of Project Settings.


#include "game_PlayerState.h"

Agame_PlayerState::Agame_PlayerState()
	:playerHealth(200),
	minHealth(0),
	maxHealth(200),
	playerAmmo(100),
	minAmmo(0),
	maxAmmo(100)
{
	PrimaryActorTick.bCanEverTick = true;

	isAlive = true;
}

void Agame_PlayerState::BeginPlay()
{
	Super::BeginPlay();

}

void Agame_PlayerState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void Agame_PlayerState::DepleteAmmo(int amount)
{
	if (playerAmmo > minAmmo)
	{
		playerAmmo -= amount;
		playerAmmo = FMath::Clamp(playerAmmo, minAmmo, maxAmmo);
	}
}

bool Agame_PlayerState::ReplenishAmmo(int amount)
{
	if(playerAmmo < maxAmmo)
	{
		playerAmmo += amount;
		playerAmmo = FMath::Clamp(playerAmmo, minAmmo, maxAmmo);
		return true;
	}
	else
	{
		return false;
	}
}

bool Agame_PlayerState::HasAmmo()
{
	if (playerAmmo > minAmmo)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Agame_PlayerState::DepleteHealth(int amount)
{
	if (playerHealth > minHealth)
	{
		playerHealth -= amount;
		playerHealth = FMath::Clamp(playerHealth, minHealth, maxHealth);
	}
}

bool Agame_PlayerState::ReplenishHealth(int amount)
{
	if (playerHealth < maxHealth)
	{
		playerHealth += amount;
		playerHealth = FMath::Clamp(playerHealth, minHealth, maxHealth);
		return true;
	}
	else
	{
		return false;
	}
}

void Agame_PlayerState::SetRespawnLocation(FVector location, FRotator rotation)
{
	spawnLocation = FTransform(rotation, location);
}
