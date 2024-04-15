// Fill out your copyright notice in the Description page of Project Settings.

//Header Files
#include "Items/Item.h"

#include "Character/CharacterBase.h"
//Components
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
////////////////////////////////////////

// Sets default values
AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = false;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	ItemMesh->SetupAttachment(RootComponent);
	SetRootComponent(ItemMesh);

	ItemMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	ItemMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	AreaSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AreaSphere"));
	AreaSphere->SetupAttachment(RootComponent);
	AreaSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	//AreaSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AreaSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	AreaSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	PickupWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("PickupWidget"));
	PickupWidget->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();

	if (PickupWidget)
		PickupWidget->SetVisibility(false);
	
	AreaSphere->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnBeginOverlap);
	AreaSphere->OnComponentEndOverlap.AddDynamic(this, &AItem::OnEndOverlap);

	InteractableData = InstanceInteractableData;
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}
void AItem::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacterBase* Character = Cast<ACharacterBase>(OtherActor);
	if (!Character)
		return;
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Begin Item Overlap"));
	//ShowWidget();
	Character->AddItem(this);
}

void AItem::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ACharacterBase* Character = Cast<ACharacterBase>(OtherActor);
	if (!Character)
		return;
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("End Item Overlap"));
	//HideWidget();
	Character->RemoveItem(this);
}
void AItem::ShowWidget()
{
	if(PickupWidget)
		PickupWidget->SetVisibility(true);
}
void AItem::HideWidget()
{
	if(PickupWidget)
		PickupWidget->SetVisibility(false);
}

void AItem::BeginFocus()
{
	if (ItemMesh)
	{
		ItemMesh->SetRenderCustomDepth(true);
	}
}
void AItem::EndFocus()
{
	if (ItemMesh)
	{
		ItemMesh->SetRenderCustomDepth(false);
	}
}
void AItem::BeginInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("Calling BeginInteract override on Item"));
}
void AItem::EndInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("Calling EndInteract override on Item"));
}
void AItem::Interact(ACharacterBase* PlayerCharacter)
{
	UE_LOG(LogTemp, Warning, TEXT("Calling Interact override on Item"));
}


