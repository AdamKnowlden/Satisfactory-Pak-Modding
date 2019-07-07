// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGBuildableHologram.h"
#include "FSplinePointData.h"
#include "Components/SplineComponent.h"
#include "FGRailroadTrackHologram.generated.h"


/**
 * Hologram used to place train tracks.
 */
UCLASS()
class FACTORYGAME_API AFGRailroadTrackHologram : public AFGBuildableHologram
{
	GENERATED_BODY()
	
public:
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	AFGRailroadTrackHologram();

	virtual void BeginPlay() override;

	// Begin AFGHologram interface
	virtual class USceneComponent* SetupComponent( USceneComponent* attachParent, UActorComponent* componentTemplate, const FName& componentName ) override;
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	virtual bool MultiStepPlacement() override;
	virtual TArray< FItemAmount > GetCost( bool includeChildren ) const override;
	// End AFGHologram interface

	// Begin AFGBuildableHologram interface
	virtual void ConfigureActor( class AFGBuildable* inBuildable ) const override;
	virtual void ConfigureComponents( class AFGBuildable* inBuildable ) const override;
	// End AFGBuildableHologram interface

protected:
	// Begin AFGHologram interface
	virtual void SetMaterial( class UMaterialInterface* material ) override;
	// End AFGHologram interface

	// Begin AFGBuildableHologram interface
	virtual void CheckValidFloor() override;
	virtual void CheckClearance() override;
	// End AFGBuildableHologram interface

private:
	UFUNCTION()
	void OnRep_SplineData();

	/** Check for nearby snapping connections. */
	class UFGRailroadTrackConnectionComponent* FindOverlappingConnectionComponent( const FVector& location, float radius, class UFGRailroadTrackConnectionComponent* ignoredConnection, bool ignoreIsConnected ) const;

private:
	//@todotrains
	/** This is the minimum bend radius allowed when building train tracks. */
	float mMinBendRadius;

	/** From how far away we should snap to another track. */
	float mSnapDistance;

	/** The spline component we're placing. */
	UPROPERTY()
	class UFGSplineComponent* mSplineComponent;

	/** This is the data needed to create the spline component (local space). */
	UPROPERTY( ReplicatedUsing = OnRep_SplineData )
	TArray< FSplinePointData > mSplineData;

	/** This is an additional floor data for the spline data (local space). */
	TArray< FVector > mFloorData;

	/** Index of the currently moved point. */
	int32 mCurrentConnection;

	/** The track connections we have. */
	UPROPERTY()
	class UFGRailroadTrackConnectionComponent* mConnectionComponents[ 2 ];

	/** The track connection we snap when building the track. */
	UPROPERTY()
	class UFGRailroadTrackConnectionComponent* mSnappedConnectionComponents[ 2 ];
};
