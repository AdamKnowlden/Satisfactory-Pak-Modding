// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Resources/FGBuildDescriptor.h"
#include "FGVehicleDescriptor.generated.h"

/**
 * Descriptor for vehicles.
 */
UCLASS()
class FACTORYGAME_API UFGVehicleDescriptor : public UFGBuildDescriptor
{
	GENERATED_BODY()
	
public:
	/** Ctor */
	UFGVehicleDescriptor();

	//~ Begin UObject Interface
	virtual void PostLoad() override;
	//~ End UObject Interface

	/** Get the vehicle class for this descriptor. */
	UFUNCTION( BlueprintPure, Category = "Item|Vehicle" )
	static TSubclassOf< class AFGVehicle > GetVehicleClass( TSubclassOf< UFGVehicleDescriptor > inClass );

protected:
	/** @copydoc UFGBuildingDescriptor::GetItemNameInternal */
	virtual FText GetItemNameInternal() const override;

	/** @copydoc UFGBuildingDescriptor::GetItemNameInternal */
	virtual FText GetItemDescriptionInternal() const override;

#if WITH_EDITOR
	/** @copydoc UFGItemDescriptor::SetupStage */
	virtual void SetupStage() override;

	/** @copydoc UFGItemDescriptor::GetCenterOfCollision */
	virtual FVector GetCenterOfCollision() override;
#endif
public:
	/** Value to display instead of display name and description. */
	static FText mOverrideDisplayNameAndDescription;

	/** The vehicle this descriptor describes. */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	TSubclassOf< class AFGVehicle > mVehicleClass;
};
