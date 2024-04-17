// Fill out your copyright notice in the Description page of Project Settings.

#include "game_Projectile.h"

// Sets default values
Agame_Projectile::Agame_Projectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	projectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("projectileMesh"));
	SetRootComponent(projectileMesh);
	projectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("projectileMovement"));
	projectileMovement->InitialSpeed = 2500.0f;
	projectileMovement->MaxSpeed = 3000.0f;
	projectileMovement->ProjectileGravityScale = 0.0f;
	projectileMovement->bInitialVelocityInLocalSpace = false;
	projectileMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap); //just set it in BP
}

// Called when the game starts or when spawned
void Agame_Projectile::BeginPlay()
{
	Super::BeginPlay();

	projectileMesh->OnComponentBeginOverlap.AddDynamic(this, &Agame_Projectile::Detector_OnOverlapBegin);
}

// Called every frame
void Agame_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void Agame_Projectile::SetMovementDirection(FVector movementDirection)
{
	if (projectileMovement)
	{
		projectileMovement->Velocity = movementDirection;
	}
}

void Agame_Projectile::Detector_OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	this->Destroy();
}

