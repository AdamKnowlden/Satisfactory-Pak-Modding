// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Resources/FGItemDescriptor.h"
#include "FGItemDescriptorNuclearFuel.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGItemDescriptorNuclearFuel : public UFGItemDescriptor
{
	GENERATED_BODY()
public:

	/** @return The descriptor to use when the fuel is removed from the reactor (waste). */
	UFUNCTION( BlueprintPure, Category = "Item" )
	static TSubclassOf< UFGItemDescriptor > GetSpentFuelClass( TSubclassOf< UFGItemDescriptorNuclearFuel > inClass );

private:
	/** The descriptor to use when the fuel is removed from the reactor (waste). */
	UPROPERTY( EditDefaultsOnly, Category = "Nuclear Fuel" )
	TSubclassOf< UFGItemDescriptor > mSpentFuelClass;
};
