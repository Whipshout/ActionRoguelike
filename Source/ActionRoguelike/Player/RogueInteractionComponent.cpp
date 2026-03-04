#include "RogueInteractionComponent.h"

#include "Core/RogueInteractionInterface.h"
#include "Engine/OverlapResult.h"

URogueInteractionComponent::URogueInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void URogueInteractionComponent::Interact()
{
	if (IRogueInteractionInterface* InteractInterface = Cast<IRogueInteractionInterface>(SelectedActor))
	{
		InteractInterface->Interact();
	}
}

void URogueInteractionComponent::TickComponent(const float DeltaTime, const ELevelTick TickType,
                                               FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	const APlayerController* PC = CastChecked<APlayerController>(GetOwner());

	const FVector Center = PC->GetPawn()->GetActorLocation();

	constexpr ECollisionChannel CollisionChannel = ECC_Visibility;

	FCollisionShape Shape;
	Shape.SetSphere(InteractionRadius);

	TArray<FOverlapResult> Overlaps;

	GetWorld()->OverlapMultiByChannel(Overlaps, Center, FQuat::Identity, CollisionChannel, Shape);

	AActor* BestActor = nullptr;
	float HighestDotResult = -1.f;

	for (FOverlapResult& Overlap : Overlaps)
	{
		FVector OverlapLocation = Overlap.GetActor()->GetActorLocation();

		FVector OverlapDirection = (OverlapLocation - Center).GetSafeNormal();

		const float DotResult = FVector::DotProduct(OverlapDirection, PC->GetControlRotation().Vector());

		if (DotResult > HighestDotResult)
		{
			BestActor = Overlap.GetActor();
			HighestDotResult = DotResult;
		}

		DrawDebugBox(GetWorld(), OverlapLocation, FVector(50.f), FColor::Red);
		FString DebugString = FString::Printf(TEXT("Dot: %f"), DotResult);
		DrawDebugString(GetWorld(), OverlapLocation, DebugString, nullptr, FColor::White, 0.f, true);
	}

	SelectedActor = BestActor;

	if (BestActor)
	{
		DrawDebugBox(GetWorld(), BestActor->GetActorLocation(), FVector(60.f), FColor::Green);
	}

	DrawDebugSphere(GetWorld(), Center, InteractionRadius, 32.f, FColor::White);
}
