//Base Character Class

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"

//No includes after generated.h
#include "CharacterBase.generated.h"

class UInputMappingContext;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;
class UArrowComponent;

UCLASS()
class AMALGUN_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Movement")
	float TurnSpeed = 10.f;
	UPROPERTY(BlueprintReadOnly, Category = Input)
	bool bIsMovingBackward = false;
	/////// Functions ///////
	ACharacterBase();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void SetCameraView(AActor* CameraActor);
	void ResetCameraView();

protected:
	virtual void BeginPlay() override;
	//Input
	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* CharacterContext;
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* I_KeyAction;
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* Esc_KeyAction;
	/////// Functions ///////
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void I_Key();
	void Esc_Key();

private:
	APlayerController* PlayerControl;
	AActor* OtherCamera;
	bool bInMenu = false;
	bool bIsMoving = false;
	FRotator TargetRotation;
	//Components
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* SkeletalMeshComponent;
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* ViewCamera;
	UPROPERTY(VisibleAnywhere)
	UArrowComponent* HandComponent;
	/////// Functions ///////
	void UpdateRotation(float);
};
