// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Buildables/FGBuildableGeneratorFuel.h"
#include "FGBuildableGeneratorNuclear.generated.h"

/**
 * A generator that runs on nuclear fuel and produces waste.
 */
UCLASS()
class FACTORYGAME_API AFGBuildableGeneratorNuclear : public AFGBuildableGeneratorFuel
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

protected:
	// Begin AFGBuildableGeneratorFuel
	virtual void LoadFuel() override;
	// End AFGBuildableGeneratorFuel

private:
	/** Spent fuel rods goes here. */
	UPROPERTY()
	class UFGInventoryComponent* mOutputInventory;
};
