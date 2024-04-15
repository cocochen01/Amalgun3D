// Base Character Class

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"

// No includes after generated.h
#include "CharacterBase.generated.h"

class AGameHUD;
class UInputMappingContext;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;
class UArrowComponent;
class UCombatComponent;
class UStaticMeshComponent;
class AItem;
class IInteractionInterface;

USTRUCT()
struct FInteractionData
{
	GENERATED_USTRUCT_BODY()
	FInteractionData() : CurrentInteractable(nullptr), LastInteractionCheckTime(.0f) {};
	UPROPERTY()
	AItem* CurrentInteractable;
	UPROPERTY()
	float LastInteractionCheckTime;
};

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
	UPROPERTY()
	AGameHUD* HUD;
	UPROPERTY(EditAnywhere, Category = "Character | Input")
	UInputMappingContext* CharacterContext;
	UPROPERTY(EditAnywhere, Category = "Character | Input")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, Category = "Character | Input")
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, Category = "Character | Input")
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, Category = "Character | Input")
	UInputAction* I_KeyAction;
	UPROPERTY(EditAnywhere, Category = "Character | Input")
	UInputAction* E_KeyAction;
	UPROPERTY(EditAnywhere, Category = "Character | Input")
	UInputAction* Esc_KeyAction;
	UPROPERTY(VisibleAnywhere, Category = "Character | Interaction")
	TScriptInterface<IInteractionInterface> TargetInteractable;
	UPROPERTY(VisibleAnywhere)
	float InteractionCheckFrequency;
	UPROPERTY(VisibleAnywhere)
	FTimerHandle TimerHandle_Interaction;
	UPROPERTY(VisibleAnywhere)
	FInteractionData InteractionData;
	UPROPERTY(VisibleAnywhere)
	AItem* NearestItem;
	UPROPERTY(VisibleAnywhere)
	TArray<AItem*> ItemsInRange;

	/////// Functions ///////
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void IKey();
	void EKey_Started();
	void EKey_Completed();
	void EscKey();
	void FindNearestInteractable();
	void FoundInteractable();
	void NoInteractableFound();
	void BeginInteract();
	void EndInteract();
	void Interact();

private:
	/////// Variables ///////
	APlayerController* PlayerControl;
	AActor* OtherCamera;
	bool bInMenu = false;
	bool bIsMoving = false;
	FRotator TargetRotation;
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


	/////// Functions ///////
	void UpdateRotation(float);
};
