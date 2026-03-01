#include "RogueExplosiveBarrel.h"

#include "NiagaraComponent.h"
#include "Components/AudioComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/RadialForceComponent.h"


ARogueExplosiveBarrel::ARogueExplosiveBarrel()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComponent->SetSimulatePhysics(true);

	MeshComponent->SetCollisionProfileName("PhysicsActor");
	RootComponent = MeshComponent;

	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComp"));
	RadialForceComponent->SetupAttachment(MeshComponent);

	RadialForceComponent->ImpulseStrength = 150000.0f;
	RadialForceComponent->Radius = 750.f;

	RadialForceComponent->bAutoActivate = false;
	RadialForceComponent->bIgnoreOwningActor = true;
}

float ARogueExplosiveBarrel::TakeDamage(const float DamageAmount, const struct FDamageEvent& DamageEvent,
                                        class AController* EventInstigator, AActor* DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (bExploded || GetWorldTimerManager().TimerExists(ExplosionTimerHandle))
	{
		return ActualDamage;
	}

	ActiveBurningEffectComp = UNiagaraFunctionLibrary::SpawnSystemAttached(BurningEffect, MeshComponent, NAME_None,
	                                                                       FVector::ZeroVector, FRotator::ZeroRotator,
	                                                                       EAttachLocation::Type::SnapToTarget, true);

	ActiveBurningSoundComp = UGameplayStatics::SpawnSoundAttached(BurningSound, MeshComponent);

	GetWorldTimerManager().SetTimer(ExplosionTimerHandle, this, &ARogueExplosiveBarrel::Explode, ExplosionDelay);

	return ActualDamage;
}

void ARogueExplosiveBarrel::Explode()
{
	bExploded = true;

	ActiveBurningEffectComp->Deactivate();
	ActiveBurningSoundComp->Stop();

	RadialForceComponent->FireImpulse();

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ExplosionEffect, GetActorLocation(), GetActorRotation());

	UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetActorLocation(), FRotator::ZeroRotator);
}
