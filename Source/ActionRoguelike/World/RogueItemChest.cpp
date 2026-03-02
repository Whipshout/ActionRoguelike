#include "RogueItemChest.h"

ARogueItemChest::ARogueItemChest()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ARogueItemChest::BeginPlay()
{
	Super::BeginPlay();
}

void ARogueItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
