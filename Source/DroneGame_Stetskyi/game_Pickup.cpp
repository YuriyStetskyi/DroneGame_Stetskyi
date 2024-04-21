// Fill out your copyright notice in the Description page of Project Settings.


#include "game_Pickup.h"

// Sets default values
Agame_Pickup::Agame_Pickup()
	:replenishAmount_AMMO(25),
	replenishAmount_HEALTH(50)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	pickupType = EPickup::DEFAULT;
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pickup Mesh"));
	SetRootComponent(mesh);
	entityType = EEntity::PICKUP;
}

// Called when the game starts or when spawned
void Agame_Pickup::BeginPlay()
{
	Super::BeginPlay();

	mesh->OnComponentBeginOverlap.AddDynamic(this, &Agame_Pickup::OnOverlapBegin);
	
}

// Called every frame
void Agame_Pickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void Agame_Pickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (((Agame_PlayerCharacter*)OtherActor)->entityType == EEntity::PLAYER)
	{
		Agame_PlayerCharacter* player = ((Agame_PlayerCharacter*)OtherActor);
		
		switch (pickupType)
		{
		case EPickup::AMMO:
		{
			if (ReplenishAmmo(player, replenishAmount_AMMO))
			{
				this->Destroy();
			}
			break;
		}
		case EPickup::HEALTH:
		{
			if (ReplenishHealth(player, replenishAmount_HEALTH))
			{
				this->Destroy();
			}
			break;
		}
		default:
		{
			//do nothing, pickup wasnt specified
			this->Destroy();
			break;
		}
		}


	}
}

bool Agame_Pickup::ReplenishAmmo(Agame_PlayerCharacter* player, int amount)
{
	return ((Agame_PlayerController*)player->GetController())->plState->ReplenishAmmo(amount);
}

bool Agame_Pickup::ReplenishHealth(Agame_PlayerCharacter* player, int amount)
{
	return ((Agame_PlayerController*)player->GetController())->plState->ReplenishHealth(amount);
}

