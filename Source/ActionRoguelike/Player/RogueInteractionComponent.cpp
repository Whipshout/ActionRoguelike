#include "RogueInteractionComponent.h"

URogueInteractionComponent::URogueInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void URogueInteractionComponent::TickComponent(const float DeltaTime, const ELevelTick TickType,
                                               FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	const APlayerController* PC = CastChecked<APlayerController>(GetOwner());

	const FVector Center = PC->GetPawn()->GetActorLocation();

	DrawDebugBox(GetWorld(), Center, FVector(20.f), FColor::Red);
}
