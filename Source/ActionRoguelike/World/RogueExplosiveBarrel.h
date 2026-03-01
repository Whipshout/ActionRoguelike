#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RogueExplosiveBarrel.generated.h"

class URadialForceComponent;
class UNiagaraComponent;
class UNiagaraSystem;
class USoundBase;
class UStaticMeshComponent;

UCLASS(Abstract)
class ACTIONROGUELIKE_API ARogueExplosiveBarrel : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category= "Explosive Barrel")
	float ExplosionDelay = 3.0f;

	UPROPERTY(EditDefaultsOnly, Category= "Explosive Barrel")
	TObjectPtr<UNiagaraSystem> ExplosionEffect;

	UPROPERTY(EditDefaultsOnly, Category= "Explosive Barrel")
	TObjectPtr<USoundBase> ExplosionSound;

	UPROPERTY(EditDefaultsOnly, Category= "Explosive Barrel")
	TObjectPtr<UNiagaraSystem> BurningEffect;

	UPROPERTY(EditDefaultsOnly, Category= "Explosive Barrel")
	TObjectPtr<USoundBase> BurningSound;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<URadialForceComponent> RadialForceComponent;

	void Explode();

	bool bExploded = false;

	FTimerHandle ExplosionTimerHandle;

	UPROPERTY()
	TObjectPtr<UNiagaraComponent> ActiveBurningEffectComp = nullptr;

	UPROPERTY()
	TObjectPtr<UAudioComponent> ActiveBurningSoundComp = nullptr;

public:
	virtual float TakeDamage(float DamageAmount, const struct FDamageEvent& DamageEvent,
	                         class AController* EventInstigator, AActor* DamageCauser) override;

	ARogueExplosiveBarrel();
};
