// Fill out your copyright notice in the Description page of Project Settings.


#include "game_EnemyAIController.h"




void Agame_EnemyAIController::ShootAtDirection(FVector shootDirection)
{
	if (shootDirection != FVector::ZeroVector)
	{
		((Agame_EnemyCharacter*)GetPawn())->projectileSpawner->Spawn(shootDirection);
	}
}