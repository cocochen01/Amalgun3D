// Header Files
#include "Character/CharacterBase.h"

#include "AmalgunPlayerController.h"
#include "Items/Item.h"
#include "Interfaces/InteractionInterface.h"
// Enhanced Input
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
// Components
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

	InteractionCheckFrequency = .1f;
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	// Controller and Input
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
	// Get Bone from Skeleton
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

void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateRotation(DeltaTime);
	if(GetWorld()->TimeSince(LastInteractionCheckTime) > InteractionCheckFrequency)
		FindNearestInteractable();
}

void ACharacterBase::Move(const FInputActionValue& Value)
{
	if (bSwappedCamera)
	{
		
	}
	else
	{
		const FVector2D MovementVector = Value.Get<FVector2D>();
		bIsMovingBackward = MovementVector.Y < 0.f;
		// Movement
		const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(ForwardDirection, MovementVector.Y);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ACharacterBase::Look(const FInputActionValue& Value)
{
	if (bSwappedCamera)
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

void ACharacterBase::SpaceBar()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Pressed Space Bar"));
}

void ACharacterBase::IKey()
{
	if(GEngine)
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Pressed I"));
	// if (!OtherCamera) return;
	if (bSwappedCamera)
	{
		PlayerControl->SetViewTargetWithBlend(this, 0.5f, EViewTargetBlendFunction::VTBlend_Linear, 0.2f, false);
		PlayerControl->bShowMouseCursor = false;
		bSwappedCamera = false;
	}
	else if(OtherCamera)
	{
		PlayerControl->SetViewTargetWithBlend(OtherCamera, 0.5f, EViewTargetBlendFunction::VTBlend_Linear, 0.2f, false);
		int32 ViewportX, ViewportY;
		PlayerControl->GetViewportSize(ViewportX, ViewportY);
		PlayerControl->SetMouseLocation(ViewportX / 2, ViewportY / 2);
		PlayerControl->bShowMouseCursor = true;
		bSwappedCamera = true;
	}
}

void ACharacterBase::EKey_Started()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Pressed E"));
	BeginInteract();
}
void ACharacterBase::EKey_Completed()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Released E"));
	EndInteract();
}

void ACharacterBase::EscKey()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Pressed Esc"));
	if (bSwappedCamera)
	{
		PlayerControl->SetViewTargetWithBlend(this, 0.5f, EViewTargetBlendFunction::VTBlend_Linear, 0.2f, false);
		PlayerControl->bShowMouseCursor = false;
		bSwappedCamera = false;
	}
	else
		TogglePauseMenu();
}

void ACharacterBase::LMB_Triggered()
{
	if (bSwappedCamera)
	{
		if (!PlayerControl)
			return;
		float CursorX, CursorY;
		PlayerControl->GetMousePosition(CursorX, CursorY);
	
		FVector WorldLocation, WorldDirection;
		PlayerControl->DeprojectScreenPositionToWorld(CursorX, CursorY, WorldLocation, WorldDirection);

		FVector TraceStart = WorldLocation;
		FVector TraceEnd = TraceStart + (WorldDirection * 500.0f);

		FHitResult HitResult;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);

		if (GetWorld() && GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, Params))
		{
			if (HeldItem && bIsHoldingItem)
			{
				FVector ItemCurrentLocation = HeldItem->GetActorLocation();
				float Distance = FVector::Dist(TraceStart, ItemCurrentLocation);
				HeldItem->SetActorLocation(TraceStart + (WorldDirection * Distance));
			}
			else
			{
				AActor* HitActor = HitResult.GetActor();
				if (HitActor)
				{
					AItem* HitItem = Cast<AItem>(HitActor);
					if (HitItem)
					{
						HeldItem = HitItem;
						bIsHoldingItem = true;
					}
				}
			}
		}

		DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Green, false, 2.0f, 0, 0.5f);
	}
}

void ACharacterBase::LMB_Completed()
{
	if (bSwappedCamera)
	{
		HeldItem = nullptr;
		bIsHoldingItem = false;
	}
}

void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACharacterBase::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACharacterBase::Look);
		EnhancedInputComponent->BindAction(SpaceBarAction, ETriggerEvent::Started, this, &ACharacterBase::SpaceBar);
		EnhancedInputComponent->BindAction(IKeyAction, ETriggerEvent::Started, this, &ACharacterBase::IKey);
		EnhancedInputComponent->BindAction(EKeyAction, ETriggerEvent::Started, this, &ACharacterBase::EKey_Started);
		EnhancedInputComponent->BindAction(EKeyAction, ETriggerEvent::Completed, this, &ACharacterBase::EKey_Completed);
		EnhancedInputComponent->BindAction(EscKeyAction, ETriggerEvent::Started, this, &ACharacterBase::EscKey);
		EnhancedInputComponent->BindAction(LMBAction, ETriggerEvent::Triggered, this, &ACharacterBase::LMB_Triggered);
		EnhancedInputComponent->BindAction(LMBAction, ETriggerEvent::Completed, this, &ACharacterBase::LMB_Completed);
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
		// rotate character body
		TargetRotation = FRotator(0.f, GetControlRotation().Yaw, 0.f);
		SetActorRotation(FMath::RInterpTo(GetActorRotation(), TargetRotation, DeltaTime, TurnSpeed));
		// rotate hands
		HandComponent->SetRelativeRotation(FMath::RInterpTo(HandComponent->GetRelativeRotation(), FRotator(GetControlRotation().Pitch, 0.f, 0.f), DeltaTime, TurnSpeed));

	}
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

void ACharacterBase::AddItem(AItem* item)
{
	if (!item)
		return;
	ItemsInRange.AddUnique(item);
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Item Added"));

}

void ACharacterBase::RemoveItem(AItem* item)
{
	if (!item)
		return;
	ItemsInRange.Remove(item);
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Item Removed"));
}


void ACharacterBase::FindNearestInteractable()
{
	LastInteractionCheckTime = GetWorld()->GetTimeSeconds();

	if (ItemsInRange.IsEmpty())
	{
		NoInteractableFound();
		return;
	}
	NearestItem = nullptr;
	float Closest = MAX_FLT;
	for (AItem* Item : ItemsInRange)
	{
		float DistanceSquared = FVector::DistSquared(GetActorLocation(), Item->GetActorLocation());
		if (DistanceSquared < Closest)
		{
			Closest = DistanceSquared;
			NearestItem = Item;
		}
	}
	if (NearestItem != CurrentInteractable)
		FoundInteractable();
	else
		return;
}

void ACharacterBase::FoundInteractable()
{
	if (IsInteracting())
		EndInteract();
	if (CurrentInteractable)
	{
		TargetInteractable = CurrentInteractable;
		TargetInteractable->EndFocus();
	}
	CurrentInteractable = NearestItem;
	TargetInteractable = NearestItem;

	TargetInteractable->BeginFocus();
}

void ACharacterBase::NoInteractableFound()
{
	if (IsInteracting())
	{
		GetWorldTimerManager().ClearTimer(TimerHandle_Interaction);
	}

	if (CurrentInteractable)
	{
		if (IsValid(TargetInteractable.GetObject()))
		{
			TargetInteractable->EndFocus();
		}
		// Hide Widget
		CurrentInteractable->HideWidget();

		CurrentInteractable = nullptr;
		TargetInteractable = nullptr;
	}
}

void ACharacterBase::BeginInteract()
{
	FindNearestInteractable();
	if (CurrentInteractable)
	{
		if (IsValid(TargetInteractable.GetObject()))
		{
			TargetInteractable->BeginInteract();
			// If there is a valid delay above the error tolerance, start timer, then interact
			if (FMath::IsNearlyZero(TargetInteractable->InteractableData.InteractionDuration, 0.1f))
			{
				Interact();
			}
			else
			{
				GetWorldTimerManager().SetTimer(TimerHandle_Interaction, this, &ACharacterBase::Interact, TargetInteractable->InteractableData.InteractionDuration, false);
			}
		}
	}
}

void ACharacterBase::EndInteract()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_Interaction);

	if (IsValid(TargetInteractable.GetObject()))
	{
		TargetInteractable->EndInteract();
	}
}

void ACharacterBase::Interact()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_Interaction);

	if (IsValid(TargetInteractable.GetObject()))
	{
		TargetInteractable->Interact(this);
	}
}