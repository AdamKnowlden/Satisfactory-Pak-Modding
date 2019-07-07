// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Buildables/FGBuildableGenerator.h"
#include "FGBuildableGeneratorFuel.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGBuildableGeneratorFuel : public AFGBuildableGenerator
{
	GENERATED_BODY()
public:
	AFGBuildableGeneratorFuel();

	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void PreReplication( IRepChangedPropertyTracker& ChangedPropertyTracker ) override;
	virtual void BeginPlay() override;
	// End AACtor interface

	// Begin UObject interface
	virtual void PostLoad() override;
	// End UObject interface

	// Begin Factory_ interface
	virtual void Factory_Tick( float dt ) override;
	// End Factory_ interface

	/**
	 * Check if a resource is valid as fuel for this generator.
	 * @param resource - Resource class to check.
	 * @return - true if resource valid as fuel; false if not valid or if generator does not run on fuel.
	 */
	UFUNCTION( BlueprintPure, Category = "Power" )
	bool IsValidFuel( TSubclassOf< class UFGItemDescriptor > resource ) const;

	/**
	 * @return a valid pointer to the inventory if this machine runs on fuel
	 */
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	FORCEINLINE class UFGInventoryComponent* GetFuelInventory() const { return mFuelInventory; };

	/**
	 * Check if this generator has fuel.
	 * @return - true if this generator has fuel; false if it has no fuel.
	 */
	UFUNCTION( BlueprintPure, Category = "Power" )
	bool HasFuel() const;

	/**
	 * How much of the fuel have we burned? In range [0,1].
	 */
	UFUNCTION( BlueprintPure, Category = "Power" )
	float GetFuelAmount() const;

	/** We want to change the potential instantly on generators ? */
	virtual void SetPendingPotential( float newPendingPotential ) override;

protected:
	/** Try to collect fuel from an input. */
	void Factory_CollectFuel();

	/** Try load fuel into the burner. */
	virtual void LoadFuel();

	// Begin AFGBuildableGenerator interface
	virtual bool CanStartPowerProduction_Implementation() const override;
	virtual void Factory_StartPowerProduction_Implementation() override;
	virtual void Factory_StopPowerProduction_Implementation() override;
	virtual void Factory_TickPowerProduction_Implementation( float dt ) override;
	// End AFGBuildableGenerator interface

private:
	/**
	 * Filter out what we consider as fuel for our fuel inventory.
	 * @see IsValidFuel
	 */
	UFUNCTION()
	bool FilterFuelClasses( TSubclassOf< UObject > object, int32 idx ) const;

	/** Set up the fuel inventory when replicated */
	UFUNCTION()
	void OnRep_FuelInventory();

protected:
	/** Fuel classes this machine can run on. Leave empty if it does not run on fuel. */
	UPROPERTY()
	TArray< TSubclassOf< class UFGItemDescriptor > > mFuelClasses_DEPRECATED;

	/** Fuel classes this machine can run on. Leave empty if it does not run on fuel. */
	UPROPERTY( EditDefaultsOnly, Category = "Power", meta = ( MustImplement = "FGInventoryInterface" ) )
	TArray< TSoftClassPtr< class UFGItemDescriptor > > mDefaultFuelClasses;

	/** Current fuel classes of the generator, useful for runtime adding of fuel classes */
	UPROPERTY( Replicated )
	TArray< TSubclassOf< class UFGItemDescriptor > > mAvailableFuelClasses;

	/** @todo: Cleanup, this shouldn't need to be replicated, clients should be able to fetch this anyway. Static index of fuel slot? */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_FuelInventory )
	class UFGInventoryComponent* mFuelInventory;

	/** Cached input connections (No need for UPROPERTY as they are referenced in component array) */
	TArray<class UFGFactoryConnectionComponent*> mCachedInputConnections;

	/** Amount left of the currently burned piece of fuel. In megawatt seconds (MWs). */
	UPROPERTY( SaveGame, Replicated, Meta = (NoAutoJson = true) )
	float mCurrentFuelAmount;

	/** Type of the currently burned piece of fuel. */
	UPROPERTY( SaveGame, Meta = (NoAutoJson = true) )
	TSubclassOf< class UFGItemDescriptor > mCurrentFuelClass;
};
