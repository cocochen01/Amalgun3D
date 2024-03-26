//Header File
#include "Character/CharacterBase.h"
#include "AmalgunPlayerController.h"
//Enhanced Input
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
//Components
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CombatComponent.h"
////////////////////////////////////////
ACharacterBase::ACharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	HandComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("HandComponent"));
	HandComponent->SetupAttachment(GetRootComponent());

	HandMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HandMeshComponent"));
	HandMeshComponent->SetupAttachment(HandComponent);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 200.f;

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CharacterCamera"));
	ViewCamera->SetupAttachment(SpringArm);

	GetCharacterMovement()->JumpZVelocity = 2000.f;
	GetCharacterMovement()->GravityScale = 5.f;
	GetCharacterMovement()->AirControl = 1.f;
	GetCharacterMovement()->GroundFriction = 50.f;
	GetCharacterMovement()->MaxAcceleration = 10000.f;

	Combat = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComponent"));
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	//Controller and Input
	PlayerControl = Cast<APlayerController>(GetController());
	if (PlayerControl)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerControl->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(CharacterContext, 0);
		}
		if (PlayerControl->PlayerCameraManager)
		{
			PlayerControl->PlayerCameraManager->ViewPitchMin = -30.0;
			PlayerControl->PlayerCameraManager->ViewPitchMax = 45.0;
		}
	}
	//Get Bone from Skeleton
	if (GetMesh())
	{
		FName BoneName = FName(TEXT("spine_003"));

		if (int8 boneIndex = GetMesh()->GetBoneIndex(BoneName))
		{
			// Get the bone name and convert it to a string.
			FString BoneNameString = BoneName.ToString();

			// Log the bone name.
			UE_LOG(LogTemp, Warning, TEXT("Bone Index: %d"), boneIndex);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Bone does not exist: %s"), *BoneName.ToString());
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("CharacterSkeletalMesh is not valid."));
	}
}

void ACharacterBase::Move(const FInputActionValue& Value)
{
	if (bInMenu)
	{
		
	}
	else
	{
		const FVector2D MovementVector = Value.Get<FVector2D>();
		bIsMovingBackward = MovementVector.Y < 0.f;
		//Movement
		const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(ForwardDirection, MovementVector.Y);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ACharacterBase::Look(const FInputActionValue& Value)
{
	if (bInMenu)
	{

	}
	else
	{
		const FVector2D LookingVector = Value.Get<FVector2D>();
		if (GetController())
		{
			AddControllerYawInput(LookingVector.X);
			AddControllerPitchInput(-LookingVector.Y);
		}
	}
}

void ACharacterBase::I_Key()
{
	if(GEngine)
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Pressed I"));
	//if (!OtherCamera) return;
	if (bInMenu)
	{
		PlayerControl->SetViewTargetWithBlend(this, 0.5f, EViewTargetBlendFunction::VTBlend_Linear, 0.2f, false);
		bInMenu = false;
	}
	else if(OtherCamera)
	{
		PlayerControl->SetViewTargetWithBlend(OtherCamera, 0.5f, EViewTargetBlendFunction::VTBlend_Linear, 0.2f, false);
		bInMenu = true;
	}
}

void ACharacterBase::E_Key()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Pressed E"));
}

void ACharacterBase::Esc_Key()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Pressed Esc"));
	if (bInMenu)
	{
		PlayerControl->SetViewTargetWithBlend(this, 0.5f, EViewTargetBlendFunction::VTBlend_Linear, 0.2f, false);
		bInMenu = false;
	}
	else
		TogglePauseMenu();
}

void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACharacterBase::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACharacterBase::Look);
		EnhancedInputComponent->BindAction(I_KeyAction, ETriggerEvent::Started, this, &ACharacterBase::I_Key);
		EnhancedInputComponent->BindAction(E_KeyAction, ETriggerEvent::Started, this, &ACharacterBase::E_Key);
		EnhancedInputComponent->BindAction(Esc_KeyAction, ETriggerEvent::Started, this, &ACharacterBase::Esc_Key);
		//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacterBase::Jump);
	}
}

void ACharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (Combat)
	{
		Combat->Character = this;
	}
}

void ACharacterBase::UpdateRotation(float DeltaTime)
{
	if (bIsMoving)
	{

	}
	else
	{
		//rotate character body
		TargetRotation = FRotator(0.f, GetControlRotation().Yaw, 0.f);
		SetActorRotation(FMath::RInterpTo(GetActorRotation(), TargetRotation, DeltaTime, TurnSpeed));
		//rotate hands
		HandComponent->SetRelativeRotation(FMath::RInterpTo(HandComponent->GetRelativeRotation(), FRotator(GetControlRotation().Pitch, 0.f, 0.f), DeltaTime, TurnSpeed));

	}
}

void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateRotation(DeltaTime);
}

void ACharacterBase::SetCameraView(AActor* CameraActor)
{
	OtherCamera = CameraActor;
}

void ACharacterBase::ResetCameraView()
{
	PlayerControl->SetViewTarget(this);
}

void ACharacterBase::TogglePauseMenu()
{
	if (PlayerControl)
	{
		AAmalgunPlayerController* PC = Cast<AAmalgunPlayerController>(PlayerControl);
		if (PC)
		{
			PC->TogglePauseMenu();
		}
	}
}
