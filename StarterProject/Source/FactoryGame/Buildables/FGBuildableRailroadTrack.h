// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGBuildable.h"
#include "FSplinePointData.h"
#include "Components/SplineComponent.h"
#include "FGSplineComponent.h"
#include "FGBuildableRailroadTrack.generated.h"


/**
 * This is a way to represent a position on the railroad.
 */
USTRUCT(BlueprintType)
struct FRailroadTrackPosition
{
	GENERATED_BODY()
public:
	/** A null track position. */
	static const FRailroadTrackPosition InvalidTrackPosition;

	FRailroadTrackPosition();
	FRailroadTrackPosition( class AFGBuildableRailroadTrack* track, float offset, float forward );
	FRailroadTrackPosition( const FRailroadTrackPosition& position );
	~FRailroadTrackPosition();

	/** Function called when serializing this struct to a FArchive. */
	bool Serialize( FArchive& ar );
	friend FArchive& operator<<( FArchive& ar, FRailroadTrackPosition& item );

	/** Is this a valid track position. */
	FORCEINLINE bool IsValid() const { return Track.IsValid(); }

	/** Get the world location and direction of this track position. Does nothing if Track is not valid. */
	void GetWorldLocationAndDirection( FVector& out_location, FVector& out_direction ) const;

	/**
	 * Get the world location.
	 * @return World location if valid; otherwise a zero vector.
	 */ 
	FVector GetWorldLocation() const;

	/**
	 * Get the world direction.
	 * @return World direction if valid; otherwise a zero vector.
	 */
	FVector GetWorldDirection() const;

	/** @return Offset from the beginning of the track in the forward direction. It's up to the caller to check the validity of the track. */
	float GetForwardOffset() const;

	/** @return Offset from the end of the track in the reverse direction. It's up to the caller to check the validity of the track. */
	float GetReverseOffset() const;

public:
	/**
	 * This is the track segment this position is on.
	 * If null then this is not a valid position.
	 */
	UPROPERTY()
	TWeakObjectPtr< class AFGBuildableRailroadTrack > Track;

	/** Offset along the track. */
	UPROPERTY()
	float Offset;

	/**
	 * How are we rotated on this segment.
	 *  1: We travel forward by increasing the offset (Along the spline).
	 * -1: We travel forward by decreasing the offset (Against the spine).
	 */
	UPROPERTY()
	float Forward;

	/** @todotrains The block id, for signals later, a long wagon can possibly be on 2 or more blocks at once. */
	//int32 Block;
};

/** Enable custom serialization of FRailroadTrackPosition */
template<>
struct TStructOpsTypeTraits< FRailroadTrackPosition > : public TStructOpsTypeTraitsBase2< FRailroadTrackPosition >
{
	enum
	{
		WithSerializer = true
	};
};


/**
 * A piece of train track, it has a spline and to ends.
 */
UCLASS( Abstract )
class FACTORYGAME_API AFGBuildableRailroadTrack : public AFGBuildable
{
	GENERATED_BODY()
public:
	/** Replication */
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	/** Ctor */
	AFGBuildableRailroadTrack();

	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface

	// Begin IFGDismantleInterface
	virtual void Dismantle_Implementation() override;
	// End IFGDismantleInterface

	/**
	 * Get the track location closest to the given world location.
	 */
	FRailroadTrackPosition FindTrackPositionClosestToWorldLocation( const FVector& worldLocation );

	/**
	 * Get a location and rotation given a train position.
	 */
	void GetWorldLocationAndDirectionAtPosition( const struct FRailroadTrackPosition& position, FVector& out_location, FVector& out_direction ) const;

	/** Get the length of this track. */
	FORCEINLINE float GetLength() const { return mSplineComponent->GetSplineLength(); }

	/**
	 * Get the connection at offset.
	 *
	 * @param offset     May have the following values:
	 *                   0: Beginning of track, spline offset 0.
	 *                   1: End of the track segment.
	 *
	 * @return The connection; nullptr if offset is invalid.
	 */
	FORCEINLINE class UFGRailroadTrackConnectionComponent* GetConnection( int32 offset ) const
	{
		check( offset == 0 || offset == 1 );
		return mConnections[ offset ];
	}

	/**
	 * Registers an object on the track, it can be a stop, signal, speed sign etc.
	 *
	 * @param object The object to register on this track.
	 */
	void RegisterRailroadInterface( UObject* object, const FRailroadTrackPosition& position );

	/**
	 * Unregisters an object from the track, it can be a stop, signal, speed sign etc.
	 *
	 * @param object The object to register on this track.
	 */
	void UnregisterRailroadInterface( UObject* object );

	/** @return The track graph this track belongs to. */
	FORCEINLINE int32 GetTrackGraphID() const { return mTrackGraphID; }

private:
	void SetTrackGraphID( int32 trackGraphID );

private:
	friend class AFGRailroadTrackHologram;
	friend class AFGRailroadSubsystem;

	/** The spline component for this train track. */
	UPROPERTY( VisibleAnywhere, Category = "Spline" )
	class UFGSplineComponent* mSplineComponent;

	/** Spline data saved in a compact form for saving and replicating. All the vectors are in local space. */
	UPROPERTY( SaveGame, Replicated, Meta = (NoAutoJson = true) )
	TArray< FSplinePointData > mSplineData;

	/** This tracks connection component. */
	UPROPERTY( SaveGame )
	class UFGRailroadTrackConnectionComponent* mConnections[ 2 ];

	/** The graph this track belongs to. */
	int32 mTrackGraphID;

	/** Objects registered on this track in the order they're placed on the track beginning from the start, offset 0. */
	UPROPERTY()
	TArray< UObject* > mRailroadInterfaces;
};
