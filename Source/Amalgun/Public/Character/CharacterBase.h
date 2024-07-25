// Base Character Class

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"

// No includes after generated.h
#include "CharacterBase.generated.h"

class UInputMappingContext;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;
class UArrowComponent;
class UCombatComponent;
class UStaticMeshComponent;
class AItem;
class IInteractionInterface;
/*
USTRUCT()
struct FInteractionData
{
	GENERATED_USTRUCT_BODY()
	
	FInteractionData() :
		CurrentInteractable(nullptr),
		LastInteractionCheckTime(.0f)
	{};

	UPROPERTY()
	//AActor* CurrentInteractable;
	AItem* CurrentInteractable;
	UPROPERTY()
	float LastInteractionCheckTime;
};*/

UCLASS()
class AMALGUN_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	/////// Variables ///////
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character | Movement")
	float TurnSpeed = 10.f;
	UPROPERTY(BlueprintReadOnly, Category = "Character | Input")
	bool bIsMovingBackward = false;

	/////// Functions ///////
	ACharacterBase();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;
	void SetCameraView(AActor* CameraActor);
	void ResetCameraView();
	void TogglePauseMenu();
	void AddItem(AItem*);
	void RemoveItem(AItem*);
	FORCEINLINE bool IsInteracting() const { return GetWorldTimerManager().IsTimerActive(TimerHandle_Interaction); };

protected:
	virtual void BeginPlay() override;
	/////// Variables ///////
	UPROPERTY(EditAnywhere, Category = "Character | Input")
	UInputMappingContext* CharacterContext;
	UPROPERTY(EditAnywhere, Category = "Character | Input")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, Category = "Character | Input")
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, Category = "Character | Input")
	UInputAction* SpaceBarAction;
	UPROPERTY(EditAnywhere, Category = "Character | Input")
	UInputAction* IKeyAction;
	UPROPERTY(EditAnywhere, Category = "Character | Input")
	UInputAction* EKeyAction;
	UPROPERTY(EditAnywhere, Category = "Character | Input")
	UInputAction* EscKeyAction;
	UPROPERTY(EditAnywhere, Category = "Character | Input")
	UInputAction* LMBAction;

	UPROPERTY(VisibleAnywhere, Category = "Character | Interaction")

	TScriptInterface<IInteractionInterface> TargetInteractable;

	UPROPERTY(VisibleAnywhere)
	TArray<AItem*> ItemsInRange;
	UPROPERTY()
	AItem* CurrentInteractable;
	UPROPERTY(VisibleAnywhere)
	AItem* NearestItem;

	UPROPERTY(VisibleAnywhere)
	float InteractionCheckFrequency;
	UPROPERTY(VisibleAnywhere)
	FTimerHandle TimerHandle_Interaction;
	UPROPERTY()
	float LastInteractionCheckTime;
	//UPROPERTY(VisibleAnywhere)
	//FInteractionData InteractionData;

	/////// Functions ///////
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void SpaceBar();
	void IKey();
	void EKey_Started();
	void EKey_Completed();
	void EscKey();
	void LMB_Started();
	void LMB_Triggered();
	void LMB_Completed();

	void FindNearestInteractable();
	void FoundInteractable();
	void NoInteractableFound();
	void BeginInteract();
	void EndInteract();
	void Interact();

private:
	/////// Variables ///////
	UPROPERTY(VisibleAnywhere)
	APlayerController* PlayerControl;
	UPROPERTY(VisibleAnywhere)
	AActor* OtherCamera;
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* SkeletalMeshComponent;
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* ViewCamera;
	UPROPERTY(VisibleAnywhere)
	UArrowComponent* HandComponent;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* HandMeshComponent;
	UPROPERTY(VisibleAnywhere)
	UCombatComponent* Combat;
	UPROPERTY(VisibleAnywhere)
	AItem* HeldItem;

	bool bSwappedCamera = false;
	bool bIsMoving = false;
	FRotator TargetRotation;
	bool bIsHoldingItem;


	/////// Functions ///////
	void UpdateRotation(float);
};
