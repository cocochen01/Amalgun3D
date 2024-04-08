// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractionInterface.generated.h"

class ACharacterBase;

UENUM()
enum class EInteractableType : uint8
{
	Pickup UMETA(DisplayName = "Pickup"),
	NonPlayerCharacter UMETA(DisplayName = "NonPlayerCharacter"),
	Interactable UMETA(DisplayName = "Interactable")
};

USTRUCT()
struct FInteractableData
{
	GENERATED_USTRUCT_BODY()

	FInteractableData() : InteractableType(EInteractableType::Pickup), Name(FText::GetEmpty()), Action(FText::GetEmpty()), InteractionDuration(0.f) {};

	UPROPERTY(EditInstanceOnly)
	EInteractableType InteractableType;
	UPROPERTY(EditInstanceOnly)
	FText Name;
	UPROPERTY(EditInstanceOnly)
	FText Action;
	//UPROPERTY(EditInstanceOnly)
	//int8 Quantity;
	UPROPERTY(EditInstanceOnly)
	float InteractionDuration; // For hold-to-interact
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AMALGUN_API IInteractionInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void BeginFocus();
	virtual void EndFocus();
	virtual void BeginInteract();
	virtual void EndInteract();
	virtual void Interact(ACharacterBase* PlayerCharacter);

	FInteractableData InteractableData;
};
