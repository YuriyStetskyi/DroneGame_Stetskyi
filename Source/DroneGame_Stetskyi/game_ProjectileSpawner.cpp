// Fill out your copyright notice in the Description page of Project Settings.


#include "game_ProjectileSpawner.h"

// Sets default values
Agame_ProjectileSpawner::Agame_ProjectileSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	spawnerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("spawnerMesh"));
	if (spawnerMesh)
	{
		SetRootComponent(spawnerMesh);
		spawnerMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore); //so dont interrupt spawned projectiles
	}
	
} 

// Called when the game starts or when spawned
void Agame_ProjectileSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	//Spawn(FVector(0, 1, 0));
}

// Called every frame
void Agame_ProjectileSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void Agame_ProjectileSpawner::Spawn(FVector movementDirection)
{
	//projectile = TSubclassOf<Agame_Projectile>().GetDefaultObject()->StaticClass();
	projectile.GetDefaultObject()->SetMovementDirection(movementDirection);
	GetWorld()->SpawnActor<Agame_Projectile>(projectile, GetActorLocation(), GetActorRotation());
	//bullet->GetDefaultObject()->SetMovementDirection(movementDirection);
	//bullet->SetMovementDirection(movementDirection);
}

