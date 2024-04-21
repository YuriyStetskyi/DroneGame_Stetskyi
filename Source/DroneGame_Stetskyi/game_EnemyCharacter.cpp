// Fill out your copyright notice in the Description page of Project Settings.


#include "game_EnemyCharacter.h"

// Sets default values
Agame_EnemyCharacter::Agame_EnemyCharacter()
	:onCrashDamage(25)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	capsuleCollider = FindComponentByClass<UCapsuleComponent>();
	if (capsuleCollider)
	{
		SetRootComponent(capsuleCollider);
		bodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body Mesh"));
		bodyMesh->SetupAttachment(capsuleCollider);
		playerDetectionIndicatorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Player Detection Indicator"));
		playerDetectionIndicatorMesh->SetupAttachment(bodyMesh);
		gunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gun Mesh"));
		gunMesh->SetupAttachment(bodyMesh);
		muzzleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Muzzle Mesh"));
		muzzleMesh->SetupAttachment(gunMesh);
	}

	entityType = EEntity::ENEMY;
	health = 100;
}

// Called when the game starts or when spawned
void Agame_EnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	capsuleCollider->OnComponentBeginOverlap.AddDynamic(this, &Agame_EnemyCharacter::OnOverlapBegin);
	gunMesh->OnComponentBeginOverlap.AddDynamic(this, &Agame_EnemyCharacter::OnOverlapBegin);
	muzzleMesh->OnComponentBeginOverlap.AddDynamic(this, &Agame_EnemyCharacter::OnOverlapBegin);


	if (GetWorld())
	{
		projectileSpawner = GetWorld()->SpawnActor<Agame_ProjectileSpawner>(BP_projectileSpawner);
		projectileSpawner->AttachToComponent(muzzleMesh, FAttachmentTransformRules::SnapToTargetIncludingScale);
	}
}

// Called every frame
void Agame_EnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DieOn0HP();
}

// Called to bind functionality to input
void Agame_EnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void Agame_EnemyCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (((Agame_Projectile*)OtherActor)->projectileType == EProjectileType::PLAYERPROJECTILE)
	{
		lastFrameDamage = ((Agame_Projectile*)OtherActor)->projectileDamage;
		health -= lastFrameDamage;
	}

}

void Agame_EnemyCharacter::DieOn0HP()
{
	if (health <= 0)
	{
		this->Destroy();
	}
}
