// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

class AWeapon;
class ACharacterBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AMALGUN_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	/////// Functions ///////
	UCombatComponent();
	friend class ACharacterBase;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void EquipWeapon(AWeapon* WeaponToEquip);

protected:
	virtual void BeginPlay() override;

private:
	/////// Variables ///////
	ACharacterBase* Character;
	AWeapon* EquippedWeapon;

		
};
