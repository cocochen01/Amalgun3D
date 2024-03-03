// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterAnimInstance.generated.h"

class ACharacterBase;
class UCharacterMovementComponent;
class UInputAction;

UCLASS()
class AMALGUN_API UCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	ACharacterBase* Character;
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	UCharacterMovementComponent* CharacterMovement;
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	float GroundSpeed;
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	bool bIsBackward = false;

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float) override;

	//UPROPERTY(BlueprintReadOnly, Category = Movement)
	//bool bIsFalling = false;

};