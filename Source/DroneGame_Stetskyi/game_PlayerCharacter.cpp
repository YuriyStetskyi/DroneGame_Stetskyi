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
		bodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
		bodyMesh->SetupAttachment(capsuleCollider);
		gun = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gun"));
		gun->SetupAttachment(camera);
		gun->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		muzzleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Muzzle"));
		muzzleMesh->SetupAttachment(gun);
	}
	entityType = EEntity::PLAYER;
	
	lastFrameDamage = 0;
	
}

void Agame_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld())
	{
		projectileSpawner = GetWorld()->SpawnActor<Agame_ProjectileSpawner>(BP_projectileSpawner);
		projectileSpawner->AttachToComponent(muzzleMesh, FAttachmentTransformRules::SnapToTargetIncludingScale);
	}
	capsuleCollider->OnComponentBeginOverlap.AddDynamic(this, &Agame_PlayerCharacter::OnOverlapBegin);
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

void Agame_PlayerCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (((Agame_Projectile*)OtherActor)->projectileType == EProjectileType::ENEMYPROJECTILE)
	{
		lastFrameDamage = ((Agame_Projectile*)OtherActor)->projectileDamage;
	}
}
