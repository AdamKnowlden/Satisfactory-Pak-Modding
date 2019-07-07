// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGRailroadVehicle.h"
#include "FGFreightWagon.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGFreightWagon : public AFGRailroadVehicle
{
	GENERATED_BODY()
	
public:
	/** Decide on what properties to replicate. */
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	/** Ctor */
	AFGFreightWagon();

	/** BP! */
	virtual void BeginPlay() override;

	// Begin Movement
	virtual class UPawnMovementComponent* GetMovementComponent() const override;
	virtual class UFGRailroadVehicleMovementComponent* GetRailroadVehicleMovementComponent() const override;
	// End Movement

	//~ Begin IFGUseableInterface
	virtual void OnUse_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual bool IsUseable_Implementation() const override;
	//~ End IFGUseableInterface

	//~ Begin IFGDockableInterface
	virtual bool CanDock_Implementation( EDockStationType atStation ) const override;
	virtual class UFGInventoryComponent* GetDockInventory_Implementation() const override;
	virtual class UFGInventoryComponent* GetDockFuelInventory_Implementation() const override;
	virtual void WasDocked_Implementation( class AFGBuildableDockingStation* atStation ) override;
	virtual void WasUndocked_Implementation() override;
	//~ End IFGDockableInterface

	/** Get the inventory where we store the cargo. */
	UFUNCTION( BlueprintCallable, Category = "FreightWagon" )
	class UFGInventoryComponent* GetFreightInventory() const;

	/** Debug */
	virtual void DisplayDebug( class UCanvas* canvas, const class FDebugDisplayInfo& debugDisplay, float& YL, float& YPos ) override;

public:
	/** Name of the VehicleMovement. Use this name if you want to use a different class (with ObjectInitializer.SetDefaultSubobjectClass). */
	static FName VehicleMovementComponentName;

private:
	/** vehicle simulation component */
	UPROPERTY( VisibleDefaultsOnly, BlueprintReadOnly, Category = Vehicle, meta = ( AllowPrivateAccess = "true" ) )
	class UFGRailroadVehicleMovementComponent* mVehicleMovement;

	/** Responsible for handling our inventory */
	UPROPERTY( SaveGame, Replicated )
	class UFGInventoryComponent* mStorageInventory;

	/** The size of the inventory for this wagon. */
	UPROPERTY( EditDefaultsOnly, Category = "Inventory" )
	int32 mInventorySize;
};
