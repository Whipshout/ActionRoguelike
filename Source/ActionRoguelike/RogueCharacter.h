#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RogueCharacter.generated.h"

class UNiagaraSystem;
class ARogueProjectileMagic;
struct FInputActionInstance;
struct FInputActionValue;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;
class UAnimMontage;

UCLASS()
class ACTIONROGUELIKE_API ARogueCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ARogueCharacter();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "PrimaryAttack")
	TSubclassOf<ARogueProjectileMagic> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "PrimaryAttack")
	TObjectPtr<UNiagaraSystem> CastingEffect;

	UPROPERTY(EditDefaultsOnly, Category = "PrimaryAttack")
	TObjectPtr<USoundBase> CastingSound;

	UPROPERTY(VisibleAnywhere, Category = "PrimaryAttack")
	FName MuzzleSocketName;

	UPROPERTY(EditDefaultsOnly, Category = "PrimaryAttack")
	TObjectPtr<UAnimMontage> AttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_Move;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_Look;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_PrimaryAttack;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	virtual void BeginPlay() override;

	void Move(const FInputActionValue& InValue);

	void Look(const FInputActionInstance& InValue);

	void PrimaryAttack();

	void AttackTimerElapsed();

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
};
