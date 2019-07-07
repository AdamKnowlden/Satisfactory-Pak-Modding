// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Buildables/FGBuildable.h"

#include "FGBuildableHubTerminal.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGBuildableHubTerminal : public AFGBuildable
{
	GENERATED_BODY()
public:
	/** Get the trading post */
	UFUNCTION( BlueprintPure, Category = "Hub Terminal" )
	FORCEINLINE class AFGBuildableTradingPost* GetTradingPost() { return mTradingPost; }
public:
	UPROPERTY()
	class AFGBuildableTradingPost* mTradingPost;
	
};
