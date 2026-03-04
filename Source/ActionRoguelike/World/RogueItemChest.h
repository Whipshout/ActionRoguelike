#pragma once

#include "CoreMinimal.h"
#include "Core/RogueInteractionInterface.h"
#include "GameFramework/Actor.h"
#include "RogueItemChest.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ARogueItemChest : public AActor, public IRogueInteractionInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> BaseMeshComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> LidMeshComponent;

	UPROPERTY(EditAnywhere, Category = "Animation")
	float AnimationSpeed = 50.f;

	UPROPERTY(EditAnywhere, Category = "Animation")
	float AnimationTargetPitch = 120.f;

	float CurrentAnimationPitch = 0.f;

public:
	virtual void Interact() override;

	virtual void Tick(float DeltaTime) override;

	ARogueItemChest();
};
