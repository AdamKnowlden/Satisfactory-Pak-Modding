// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGBuildableFactory.h"
#include "FGBuildableManufacturer.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnNewRecipeDelegate, TSubclassOf< class UFGRecipe >, newRecipe );


/**
 * Base class for all buildings that are producing something out of something, i.e. constructors, smelters, refinery etc.
 */
UCLASS( Abstract )
class FACTORYGAME_API AFGBuildableManufacturer : public AFGBuildableFactory, public IFGRecipeProducerInterface
{
	GENERATED_BODY()
public:
	// Replication
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void PreReplication( IRepChangedPropertyTracker& ChangedPropertyTracker ) override;

	/** Constructor */
	AFGBuildableManufacturer();

	// Begin AActor interface
	virtual void BeginPlay() override; 
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason );
	// End AActor interface

	// Begin AFGBuildableFactory interface
	virtual bool IsConfigured() const override;
	virtual float GetProductionCycleTime() const override;
	virtual float GetDefaultProductionCycleTime() const override;
	virtual float GetProductionCycleTimeForRecipe( TSubclassOf< UFGRecipe > recipe ) const override;
	virtual float CalcProductionCycleTimeForPotential( float potential ) const override;
	// End AFGBuildableFactory interface

	/**
	 * Move all items in the input inventory to the given inventory.
	 * @return true if successful; false if the given inventory is full or does not support the given type of item.
	 */
	UFUNCTION( BlueprintCallable, Category = "Recipe" )
	virtual bool MoveOrDropInputInventory( AFGCharacterPlayer* pawn );

	/**
	 * Move all items in the input output to the given inventory.
	 * @return true if successful; false if the given inventory is full or does not support the given type of item.
	 */
	UFUNCTION( BlueprintCallable, Category = "Recipe" )
	virtual bool MoveOrDropOutputInventory( AFGCharacterPlayer* pawn );

	/**
	 * Get the progress of the current production.
	 * @return - Percent in range [0,1] of the current production progress.
	 */	
	virtual float GetProductionProgress() const override { return mCurrentManufacturingProgress; }

	/**
	 * Gets all the recipes that can be produced.
	 * @note This is an expensive operation so cache the result.
	 * @param out_recipes Returns all recipes available to this machine.
	 */
	UFUNCTION( BlueprintCallable, Category = "Recipe" )
	void GetAvailableRecipes( TArray< TSubclassOf< class UFGRecipe > >& out_recipes ) const;

	/** Returns the speed of which this building manufacture recipes */
	UFUNCTION(BlueprintPure, Category="Production")
	FORCEINLINE float GetManufacturingSpeed() const{ return mManufacturingSpeed; }

	/** Get the input inventory from this manufacturer. */
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	FORCEINLINE class UFGInventoryComponent* GetInputInventory() { return mInputInventory; }

	/** Get the output inventory from this manufacturer. */
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	FORCEINLINE class UFGInventoryComponent* GetOutputInventory() { return mOutputInventory; }


	/** Get the current recipe for manufacturing. */
	UFUNCTION( BlueprintPure, Category = "Recipe" )
	FORCEINLINE TSubclassOf< class UFGRecipe > GetCurrentRecipe() const{ return mCurrentRecipe; }

	/**
	 * Set the current recipe for manufacturing.
	 * @note It is up to the caller to make sure input and output inventories are empty before changing recipe.
	 *       This is so the case when players inventory is full can be handled correctly.
	 * @param recipe - The new recipe.
	 */
	UFUNCTION( BlueprintCallable, Category = "Recipe" )
	void SetRecipe( TSubclassOf< class UFGRecipe > recipe );

protected:
	// Begin AFGBuildableFactory interface
	virtual bool CanProduce_Implementation() const override;
	virtual void Factory_CollectInput_Implementation() override;
	virtual void Factory_TickProducing( float dt ) override;
	// End AFGBuildableFactory interface

	/** Creates inventories needed for the manufacturer */
	virtual void CreateInventories();

	/** Called when NewRecipe is replicated */
	UFUNCTION()
	void OnRep_CurrentRecipe();

	/** Read the items in the input inventory. */
	void GetInputInventoryItems( TArray< FInventoryStack >& out_items ) const;

	/** Clear the items in the input inventory. */
	void ClearInputInventoryItems();

	/** Read the items in the Output inventory. */
	void GetOutputInventoryItems( TArray< FInventoryStack >& out_items );

	/** Clear the items in the Output inventory. */
	void ClearOutputInventoryItems();

	/** This function sets the filters on the input output inventories. */
	virtual void SetUpInventoryFilters();

	/** 
	 * Helper function that actually removes ingredients from the manufacturers input. 
	 * This can differ between buildings (eg. Converters), so override if you need something special. 
	 * @note this function assumes the available ingredients are there and have been checked with CanProduce()
	 */
	virtual void Factory_ConsumeIngredients();

	/**
	 * Returns true if the required ingredients are in the input slots.
	 * How this is checked can differ between buildings (eg. Converters), so override if you need something special. 
	 */
	virtual bool HasRequiredIngredients() const;

protected:
	/** Called when a new recipe has been set. */
	UPROPERTY( BlueprintAssignable, Category = "Recipe" )
	FOnNewRecipeDelegate mCurrentRecipeChanged;

	/** The speed of which this building manufacture recipes, this is a multiplier to the recipe speed */
	UPROPERTY( EditDefaultsOnly, Category = "Production" )
	float mManufacturingSpeed;

	/** Manufacturing progress in range [0,1]. @todoreplication: Only replicate this if someone has this manufacturer open */
	UPROPERTY( SaveGame, Replicated, Meta = (NoAutoJson = true) )
	float mCurrentManufacturingProgress;

	/** Our input inventory, shared for all input connections. */
	UPROPERTY( SaveGame, Replicated )
	class UFGInventoryComponent* mInputInventory;

	/** Cached input connections (No need for UPROPERTY as they are referenced in component array) */
	TArray<class UFGFactoryConnectionComponent*> mInputConnections;

	/** Our output inventory, shared for all output connections. */
	UPROPERTY( SaveGame, Replicated )
	class UFGInventoryComponent* mOutputInventory;

	/** The recipe we're currently running. */
	UPROPERTY( SaveGame, Replicated, ReplicatedUsing = OnRep_CurrentRecipe, Meta = (NoAutoJson = true) )
	TSubclassOf< class UFGRecipe > mCurrentRecipe;
};
