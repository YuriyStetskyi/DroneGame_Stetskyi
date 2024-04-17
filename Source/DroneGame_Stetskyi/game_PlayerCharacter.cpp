// Fill out your copyright notice in the Description page of Project Settings.


#include "game_PlayerCharacter.h"

Agame_PlayerCharacter::Agame_PlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->GravityScale = 0.0f; // our drone is flying so dont apply gravity

	//components
	capsuleCollider = FindComponentByClass<UCapsuleComponent>();
	if (capsuleCollider)
	{
		SetRootComponent(capsuleCollider);
		camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
		camera->SetupAttachment(capsuleCollider);
		gun = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gun"));
		gun->SetupAttachment(camera);
		gun->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	}
	entityType = EEntity::PLAYER;
	
}

void Agame_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	gunMuzzle = FindGunMuzzle();

	/*if (GetWorld())
	{
		gunMuzzle = GetWorld()->SpawnActor<Agame_ProjectileSpawner>();
	}*/

	if (gunMuzzle)
	{
		gunMuzzle->spawnerMesh->AddWorldOffset(FVector(100, 0, 0));
		gunMuzzle->AttachToComponent(gun, FAttachmentTransformRules::SnapToTargetIncludingScale);
	}
}

void Agame_PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	cameraForwVector = camera->GetForwardVector();
}

void Agame_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

Agame_ProjectileSpawner* Agame_PlayerCharacter::FindGunMuzzle()
{
	TArray<AActor*> projectileSpawners;
	UGameplayStatics::GetAllActorsOfClass(this, Agame_ProjectileSpawner::StaticClass(), projectileSpawners);
	if (!projectileSpawners.IsEmpty())
	{
		return (Agame_ProjectileSpawner*)projectileSpawners[0];
	}
	else
	{
		return nullptr;
	}
}

