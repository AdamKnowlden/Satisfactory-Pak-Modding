// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGBuildableFactory.h"
#include "FGBuildableStorage.generated.h"

/**
 * Base class for all storage boxes, large and small. May have an arbitrary number of inputs and outputs.
 */
UCLASS( Abstract )
class FACTORYGAME_API AFGBuildableStorage : public AFGBuildableFactory
{
	GENERATED_BODY()
public:
	/** Decide on what properties to replicate */
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	/** Constructor */
	AFGBuildableStorage();

	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface

	/** Get the storage inventory from this storage box. */
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	FORCEINLINE UFGInventoryComponent* GetStorageInventory() { return mStorageInventory; }

protected:
	// Begin Factory_ interface
	virtual void Factory_CollectInput_Implementation() override;
	// End Factory_ interface

public:
	/** How far apart in Z do multiple storages stack. */
	UPROPERTY( EditDefaultsOnly, Category = "Storage" )
	float mStackingHeight;

	/** Default resources in a storage @todo Why this special case here, add the stuff in blueprint instead first time we're being built... I guess this is only used for the tutorial? */
	UPROPERTY( EditDefaultsOnly, Category = "Inventory", Meta = (NoAutoJson = true) )
	TArray< FItemAmount > mDefaultResources;

	/** The size of the inventory for this storage. */
	UPROPERTY( EditDefaultsOnly, Category = "Inventory" )
	int32 mInventorySizeX;
	
	/** The size of the inventory for this storage. */
	UPROPERTY( EditDefaultsOnly, Category = "Inventory" )
	int32 mInventorySizeY;

private:
	/** The inventory to store everything in. */
	UPROPERTY( SaveGame, Replicated )
	class UFGInventoryComponent* mStorageInventory;

	/** Cached input connections (No need for UPROPERTY as they are referenced in component array) */
	TArray<class UFGFactoryConnectionComponent*> mCachedInputConnections;
};
