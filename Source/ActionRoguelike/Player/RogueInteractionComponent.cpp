#include "RogueInteractionComponent.h"

#include "Engine/OverlapResult.h"

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

	constexpr ECollisionChannel CollisionChannel = ECC_Visibility;

	FCollisionShape Shape;
	Shape.SetSphere(InteractionRadius);

	TArray<FOverlapResult> Overlaps;

	GetWorld()->OverlapMultiByChannel(Overlaps, Center, FQuat::Identity, CollisionChannel, Shape);

	DrawDebugSphere(GetWorld(), Center, InteractionRadius, 32.f, FColor::White);

	const AActor* BestActor = nullptr;
	float HighestDotResult = -1.f;

	for (FOverlapResult& Overlap : Overlaps)
	{
		FVector OverlapLocation = Overlap.GetActor()->GetActorLocation();

		DrawDebugBox(GetWorld(), OverlapLocation, FVector(50.f), FColor::Red);

		FVector OverlapDirection = (OverlapLocation - Center).GetSafeNormal();

		const float DotResult = FVector::DotProduct(OverlapDirection, PC->GetControlRotation().Vector());

		FString DebugString = FString::Printf(TEXT("Dot: %f"), DotResult);

		DrawDebugString(GetWorld(), OverlapLocation, DebugString, nullptr, FColor::White, 0.f, true);

		if (DotResult > HighestDotResult)
		{
			BestActor = Overlap.GetActor();
			HighestDotResult = DotResult;
		}
	}

	if (BestActor)
	{
		DrawDebugBox(GetWorld(), BestActor->GetActorLocation(), FVector(60.f), FColor::Green);
	}
}
