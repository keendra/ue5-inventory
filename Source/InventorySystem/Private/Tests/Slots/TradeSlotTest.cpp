/*#include "../../../Public/Slots/TradeSlot.h"
#include "../../../Public/InventoryFunctionLibrary.h"
#include "../../../Public/Items/BaseItem.h"
#include "../../../Public/Slots/BaseSlot.h"
#include "../../../Public/Inventory.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
//#include "GameplayStatics.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Classes/GameFramework/Actor.h"
#include "EngineUtils.h"
#include "UObject/ConstructorHelpers.h"

#include "Misc/AutomationTest.h"

#define LOCTEXT_NAMESPACE "UTradeSlotTests"

UClass* UTradeSlotTestClass = nullptr;

IMPLEMENT_SIMPLE_AUTOMATION_TEST(UTradeSlotTest, "Tests.InventorySystem.Slots.TradeSlot.Test", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool UTradeSlotTest::RunTest(const FString& Parameters)
{
	UWorld* World = GEngine->GetWorldContexts()[0].World();

	// Get UBaseItem class
	ConstructorHelpers::FClassFinder<UBaseItem> ItemBPClass(TEXT("/Game/BaseItemBP"));
	if (!ItemBPClass.Class)
	{
		AddError(FString::Printf(TEXT("Failed to find class /Game/BaseItemBP")));
		return false;
	}

	// Get UBaseSlot class
	ConstructorHelpers::FClassFinder<UBaseSlot> SlotBPClass(TEXT("/Game/BaseSlotBP"));
	if (!SlotBPClass.Class)
	{
		AddError(FString::Printf(TEXT("Failed to find class /Game/BaseSlotBP")));
		return false;
	}

	// Create Owner actor
	AActor* Owner = World->SpawnActor<AActor>();
	UInventory* InventoryComponent = NewObject<UInventory>(Owner, UInventory::StaticClass());
	Owner->AddInstanceComponent(InventoryComponent);

	// Create OtherOwner actor
	/*AActor* OtherOwner = World->SpawnActor<AActor>();
	OtherOwner->AddInstanceComponent(ItemBPClass.Class);
	OtherOwner->AddInstanceComponent(SlotBPClass.Class);

	// Create a UBaseItem
	UBaseItem* Item = NewObject<UBaseItem>(Owner, ItemBPClass.Class);

	// Create a UBaseSlot for the Owner
	UBaseSlot* SourceSlot = NewObject<UBaseSlot>(Owner, SlotBPClass.Class);
	SourceSlot->SetSlot(Item, 1);

	// Create a UTradeSlot for the OtherOwner
	UTradeSlot* DestinationSlot = NewObject<UTradeSlot>(OtherOwner, UTradeSlotTestClass);
	DestinationSlot->SetSlot(Item, 1);*/
//}

	// Test if ValidateCost returns true when the buyer has sufficient amount of the required item
	/*{
		Item->BasePrice.Add(TTuple<UBaseItem*, int>(Item, 1));
		ETransferErrorCodes Error;
		bool Result = DestinationSlot->ValidateCost(SourceSlot,*/
