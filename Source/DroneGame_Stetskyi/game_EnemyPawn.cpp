// Fill out your copyright notice in the Description page of Project Settings.


#include "game_EnemyPawn.h"

// Sets default values
Agame_EnemyPawn::Agame_EnemyPawn()
	:onCrashDamage(50)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body Mesh"));
	if (bodyMesh)
	{
		SetRootComponent(bodyMesh);
	}

}

// Called when the game starts or when spawned
void Agame_EnemyPawn::BeginPlay()
{
	Super::BeginPlay();
	
	bodyMesh->OnComponentBeginOverlap.AddDynamic(this, &Agame_EnemyPawn::OnOverlapBegin);
}

// Called every frame
void Agame_EnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void Agame_EnemyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void Agame_EnemyPawn::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Agame_PlayerCharacter* player = (Agame_PlayerCharacter*)OtherActor;
	if (player->entityType == EEntity::PLAYER)
	{
		Agame_PlayerController* playerController = (Agame_PlayerController*)player->GetController();
		playerController->playerState->DepleteHealth(onCrashDamage);
	}

}

