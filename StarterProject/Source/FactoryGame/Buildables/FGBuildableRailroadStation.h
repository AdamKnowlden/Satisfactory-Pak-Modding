// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Buildables/FGBuildableFactory.h"
#include "FGRailroadInterface.h"
#include "FGBuildableRailroadTrack.h"
#include "FGBuildableRailroadStation.generated.h"

/**
 * Base class for rail road stations. Not to be confused railroad docking stations.
 */
UCLASS()
class FACTORYGAME_API AFGBuildableRailroadStation : public AFGBuildableFactory, public IFGRailroadInterface
{
	GENERATED_BODY()
public:
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type endPlayReason ) override;

	/** Set the name of this station. */
	UFUNCTION( BlueprintCallable, Category = "Station" )
	void SetName( const FText& name );

	/** Get the name of this station. */
	UFUNCTION( BlueprintPure, Category = "Station" )
	const FText& GetName() const { return mName; }

	// Begin IFGRailroadInterface
	virtual void RegisteredOnTrack_Implementation( const FRailroadTrackPosition& position ) override;
	virtual void UnregisteredFromTrack_Implementation() override;
	virtual FRailroadTrackPosition GetTrackPosition_Implementation() const override;
	// End IFGRailroadInterface

protected:
	/** Called when the name of the station has changed. */
	UFUNCTION( BlueprintImplementableEvent, Category = "Station" )
	void OnNameChanged();

private:
	UFUNCTION()
	void OnRep_Name() { OnNameChanged(); }

public:
	/** Where on the track is this station located. */
	UPROPERTY( SaveGame, Meta = (NoAutoJson = true) )
	FRailroadTrackPosition mTrackPosition;

	/** The user set name for the train station. */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_Name, Meta = (NoAutoJson = true) )
	FText mName;
};
