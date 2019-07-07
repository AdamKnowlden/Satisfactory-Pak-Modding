// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Resources/FGBuildDescriptor.h"
#include "FGBuildingDescriptor.generated.h"


UCLASS( Abstract )
class FACTORYGAME_API UFGBuildingDescriptor : public UFGBuildDescriptor
{
	GENERATED_BODY()
public:
	/** Ctor */
	UFGBuildingDescriptor();

	//~ Begin UObject Interface
	virtual void PostLoad() override;
	//~ End UObject Interface

	/** Get the buildable class for this building descriptor. */
	UFUNCTION( BlueprintPure, Category = "Item|Building" )
	static TSubclassOf< class AFGBuildable > GetBuildableClass( TSubclassOf< UFGBuildingDescriptor > inClass );

	/** Get the the power consumption of buildable. */
	UFUNCTION( BlueprintPure, Category = "Item|Building" )
	static float GetPowerConsumption( TSubclassOf< UFGBuildingDescriptor > inClass );

	/** Get the the power production of buildable, 0 for non-producers. */
	UFUNCTION( BlueprintPure, Category = "Item|Building" )
	static float GetPowerProduction( TSubclassOf< UFGBuildingDescriptor > inClass );

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

protected:
	/** Value to display instead of display name and description. */
	static FText mOverrideDisplayNameAndDescription;

	/** The class to build. */
	UPROPERTY( EditDefaultsOnly, Category = "Building" )
	TSubclassOf< class AFGBuildable > mBuildableClass;
};
