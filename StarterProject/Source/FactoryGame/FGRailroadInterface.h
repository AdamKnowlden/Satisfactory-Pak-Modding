#pragma once

#include "Buildables/FGBuildableRailroadTrack.h"
#include "UObject/Interface.h"
#include "FGRailroadInterface.generated.h"

/**
* For blueprint support of the interface, we will never add anything to it, just use it to have a UCLASS to be able to access.
*/
UINTERFACE( Blueprintable )
class UFGRailroadInterface : public UInterface
{
	GENERATED_BODY()
};

/**
* @brief Interface for all buildables that can be placed on the railroad track.
*/
class IFGRailroadInterface
{
	GENERATED_IINTERFACE_BODY()

	/** When this is registered on a track. */
	UFUNCTION( BlueprintNativeEvent, Category = "Railroad" )
	void RegisteredOnTrack( const FRailroadTrackPosition& position );

	/** When this is unregistered from a track, e.g. the track is dismantled. */
	UFUNCTION( BlueprintNativeEvent, Category = "Railroad" )
	void UnregisteredFromTrack();

	/** Get the track location. */
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "Railroad" )
	FRailroadTrackPosition GetTrackPosition() const;
};
