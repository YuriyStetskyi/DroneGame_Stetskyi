// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class DRONEGAME_STETSKYI_API game_Enums
{
public:
	game_Enums();
	~game_Enums();
};

UENUM(BlueprintType)
enum class EPickup : uint8
{
	DEFAULT UMETA(DisplayName = "DEFAULT"),
	HEALTH	UMETA(DisplayName = "HEALTH"),
	AMMO	UMETA(DisplayName = "AMMO")
};

UENUM(BlueprintType)
enum class EProjectile : uint8
{
	DEFAULT UMETA(DisplayName = "DEFAULT"),
	ENEMY	UMETA(DisplayName = "ENEMY"),
	PLAYER	UMETA(DisplayName = "PLAYER")
};

UENUM(BlueprintType)
enum class EEntity : uint8
{
	DEFAULT UMETA(DisplayName = "DEFAULT"),
	ENEMY	UMETA(DisplayName = "ENEMY"),
	PLAYER	UMETA(DisplayName = "PLAYER"),
	PICKUP  UMETA(DIsplayName = "PICKUP")
};

UENUM(BlueprintType)
enum class EProjectileType : uint8
{
	DEFAULT				UMETA(DisplayName = "DEFAULT"),
	ENEMYPROJECTILE		UMETA(DisplayName = "ENEMY"),
	PLAYERPROJECTILE	UMETA(DisplayName = "PLAYER")
};