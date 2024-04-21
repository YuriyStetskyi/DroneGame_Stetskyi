// Fill out your copyright notice in the Description page of Project Settings.


#include "game_PlayerController.h"

Agame_PlayerController::Agame_PlayerController()
	:forwardInput(0.0f),
	rightInput(0.0f),
	inputThreshold(0.2f),
	maxSpeed(1200.0f),
	acceleration(3.0f),
	cameraSensitivity(50),
	cameraPitch(0.0f),
	cameraYaw(0.0f)
{
	PrimaryActorTick.bCanEverTick = true;
	movementDirection = FVector::ZeroVector;
	currentVelocity = FVector::ZeroVector;
	projectileFlightTrajectory = FVector::ZeroVector;
}

void Agame_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	playerCharacter = FindPlayerCharacter();
	Possess(playerCharacter);
	plState = GetPlayerState<Agame_PlayerState>();
	plState->SetRespawnLocation(playerCharacter->GetActorLocation(), playerCharacter->GetActorRotation());
}

void Agame_PlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (plState->isAlive)
	{
		MoveOnInput(playerCharacter, forwardInput, rightInput, upInput, DeltaTime);
		RotateCameraOnInput(playerCharacter, cameraPitch, cameraYaw, DeltaTime);
		GetDamagedOnHit(playerCharacter);
		DieOn0HP();
	}
}

void Agame_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &Agame_PlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &Agame_PlayerController::MoveRight);
	InputComponent->BindAxis("MoveUp", this, &Agame_PlayerController::MoveUp);
	InputComponent->BindAxis("LookUp", this, &Agame_PlayerController::LookUp);
	InputComponent->BindAxis("LookRight", this, &Agame_PlayerController::LookRight);

	InputComponent->BindAction("Shoot", IE_Pressed, this, &Agame_PlayerController::Shoot);
}

Agame_PlayerCharacter* Agame_PlayerController::FindPlayerCharacter()
{
	TArray<AActor*> players;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), Agame_PlayerCharacter::StaticClass(), players);
	TSubclassOf<Agame_PlayerController>* plr = (TSubclassOf<Agame_PlayerController>*)players[0];
	return (Agame_PlayerCharacter*)players[0];
}

void Agame_PlayerController::MoveForward(float value)
{
	if (value)
	{
		if (FMath::Abs(value) > inputThreshold)
		{
			forwardInput = value;
		}
	}
	else
	{
		forwardInput = 0.0f;
	}
}

void Agame_PlayerController::MoveRight(float value)
{
	if (value)  
	{
		if (FMath::Abs(value) > inputThreshold)
		{
			rightInput = value;
		}
	}
	else
	{
		rightInput = 0.0f;
	}
}

void Agame_PlayerController::MoveOnInput(Agame_PlayerCharacter* character, float fInput, float rInput, float uInput, float DeltaTime)
{
	if (character)
	{
		FVector horizontalForward = character->camera->GetForwardVector();
		FVector horizontalRight = character->camera->GetRightVector();
		FVector horizontalUp = character->camera->GetUpVector();

		horizontalForward.Z = 0;
		horizontalRight.Z = 0;
		horizontalUp.X = 0;
		horizontalUp.Y = 0;

		movementDirection = horizontalForward * fInput
							+ horizontalRight * rInput
							+ horizontalUp * uInput;
		//movementDirection.Z = 0;
		movementDirection.Normalize();

		FVector targetVelocity = movementDirection * maxSpeed;
		currentVelocity = FMath::Lerp(currentVelocity, targetVelocity, acceleration * DeltaTime);

		FVector newLocation = character->GetActorLocation() + (currentVelocity * DeltaTime);
		character->SetActorLocation(newLocation, true);
	}
	

}

void Agame_PlayerController::LookUp(float value)
{
	if (value)
	{
		cameraPitch = value;
	}
	else
	{
		cameraPitch = 0.0f;
	}
}

void Agame_PlayerController::LookRight(float value)
{
	if (value)
	{
		cameraYaw = value;
	}
	else
	{
		cameraYaw = 0.0f;
	}
}

void Agame_PlayerController::RotateCameraOnInput(Agame_PlayerCharacter* character, float pitch, float yaw, float DeltaTime)
{
	if (pitch)
	{
		float result = character->camera->GetRelativeRotation().Pitch + pitch;
		if (result <= 90 && result >= -90)
		{
			character->camera->AddLocalRotation(FRotator(pitch, 0, 0));	//move camera. not whole obeject. otherwise wont work
		}
	}

	if (yaw)
	{
		character->camera->AddWorldRotation(FRotator(0, yaw, 0));
	}
}

void Agame_PlayerController::MoveUp(float value)
{
	if (value)
	{
		if (FMath::Abs(value) >= inputThreshold)
		{
			upInput = value;
		}
	}
	else
	{
		upInput = 0;
	}
}

void Agame_PlayerController::Shoot()
{
	if (plState->HasAmmo() && plState->isAlive)
	{
		projectileFlightTrajectory = GetFlightTrajectory();
		if (projectileFlightTrajectory != FVector::ZeroVector)
		{
			playerCharacter->projectileSpawner->Spawn(projectileFlightTrajectory);
		}
		plState->DepleteAmmo(1);
	}
}

FVector Agame_PlayerController::GetFlightTrajectory()
{
	FVector start = playerCharacter->camera->GetRelativeLocation() + playerCharacter->GetActorLocation();
	FVector forward = playerCharacter->camera->GetForwardVector();
	start = FVector(start.X + (forward.X * 100), start.Y + (forward.Y * 100), start.Z + (forward.Z * 100));
	FVector end = start + (forward * 10000);
	FHitResult hit;

	if (GetWorld())
	{
		FVector gunLocation = playerCharacter->gun->GetComponentTransform().GetLocation();
		bool actorHit = GetWorld()->LineTraceSingleByChannel(hit, start, end, ECC_Camera, FCollisionQueryParams(), FCollisionResponseParams());
		if (actorHit)
		{
			//DrawDebugLine(GetWorld(), gunLocation, hit.Location, FColor::Green, false, 5.0f, 0.0f, 3.0f);
			return hit.Location - gunLocation;
		}
		else
		{
			//DrawDebugLine(GetWorld(), gunLocation, end, FColor::Red, false, 5.0f, 0.0f, 3.0f);
			return end - gunLocation;
		}
	}
	return FVector::ZeroVector;
}

void Agame_PlayerController::GetDamagedOnHit(Agame_PlayerCharacter* character)
{
	if (character->lastFrameDamage != 0)
	{
		plState->DepleteHealth(character->lastFrameDamage);
		character->lastFrameDamage = 0;
	}
}

void Agame_PlayerController::DieOn0HP()
{
	if (plState->playerHealth <= 0)
	{
		plState->isAlive = false;
		playerCharacter->Destroy();
	}
}

void Agame_PlayerController::Respawn()
{
	//FTransform SpawnTransform = FTransform(FRotator::ZeroRotator, FVector(500.0f, 500.0f, 500.0f));

	playerCharacter = GetWorld()->SpawnActor<Agame_PlayerCharacter>(BP_playerCharacter, plState->spawnLocation);
	Possess(playerCharacter);
	plState->isAlive = true;
	plState->playerHealth = plState->maxHealth;
	plState->playerAmmo = plState->maxAmmo;

}

