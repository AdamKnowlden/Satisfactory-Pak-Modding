// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "UObject/Interface.h"
#include "FGRadiationInterface.generated.h"


UINTERFACE( Blueprintable )
class UFGRadiationInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * @brief Interface for all actors that can take damage by radiation.
 */
class IFGRadiationInterface
{
	GENERATED_IINTERFACE_BODY()

	/**
	 * @param amount		How much radiation we're exposed to. [units/s]
	 * @param duration		For how long we've been exposed. [s]
	 * @param damageType	The type of damage you take from this radiation.
	 */
	UFUNCTION( BlueprintNativeEvent, Category = "Radioactivity" )
	void ReceiveRadiation( float amount, float duration, TSubclassOf< class UFGDamageType > damageType );
};
