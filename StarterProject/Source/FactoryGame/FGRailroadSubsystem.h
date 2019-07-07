// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGSubsystem.h"
#include "FGSaveInterface.h"
#include "FGRailroadVehicle.h"
#include "Buildables/FGBuildableRailroadTrack.h"
#include "GraphAStar.h"
#include "RailroadNavigation.h"
#include "FGRailroadSubsystem.generated.h"

/**
 * Constant data about the train.
 * Changes only when a trains composition is changed.
 */
USTRUCT(BlueprintType)
struct FTrainData
{
	GENERATED_BODY()
public:
	/** Mass off the train including payload. [kg] */
	UPROPERTY( BlueprintReadOnly )
	float Mass;

	/** Length of the train between the first and last buffer. [cm] */
	UPROPERTY( BlueprintReadOnly )
	float Length;

	/** How much the brakes decelerate the train. [cm/s^2] */
	UPROPERTY( BlueprintReadOnly )
	float BrakeDeceleration;
};

/**
 * Struct representing a train.
 */
USTRUCT()
struct FTrain
{
	GENERATED_BODY()
public:
	FTrain();
	~FTrain();

	/** Custom train serialization. */
	friend FArchive& operator<<( FArchive& ar, FTrain& train );

public:
	/** The id used to identify this train. */
	UPROPERTY()
	int32 TrainID;

	/** Train are a doubly linked list, use TTrainIterator to iterate over a train. */
	UPROPERTY()
	class AFGRailroadVehicle* FirstVehicle;
	UPROPERTY()
	class AFGRailroadVehicle* LastVehicle;

	/** This is the master locomotives that sends its input (throttle/brake/etc) to all other locomotives in the train. */
	UPROPERTY()
	class AFGLocomotive* MultipleUnitMaster;

	/** Is this train self driving */
	bool IsSelfDrivingEnabled;

	/** This trains time table. */
	UPROPERTY()
	class UFGRailroadTimeTable* TimeTable;

	/** Constant data about this train such as length, mass etc. */
	FTrainData TrainData;

	/** Trains momentum. */
	float Momentum;

	/** Trains velocity. */
	float Velocity;

	/** Some values for debugging purposes. */
	float Traction;
	float Resistance;
	float Braking;
};

/**
 * Struct representing a set of interconnected tracks.
 */
USTRUCT()
struct FTrackGraph
{
	GENERATED_BODY()
public:
	FTrackGraph();

public:
	/** All the tracks that are connected (nodes in the graph) */
	UPROPERTY()
	TArray< class AFGBuildableRailroadTrack* > Tracks;

	/** Do this track graph need to be rebuilt, e.g. tracks have been removed. */
	UPROPERTY( NotReplicated )
	uint8 NeedFullRebuild:1;

	/** Has this track graph changed, tracks connected, rolling stock added or removed. */
	UPROPERTY( NotReplicated )
	uint8 HasChanged:1;
};

/**
 * Actor for handling the railroad network and the trains on it.
 */
UCLASS( abstract, Blueprintable, hidecategories = ( Actor, Input, Replication, Rendering, "Actor Tick" ) )
class FACTORYGAME_API AFGRailroadSubsystem : public AFGSubsystem, public IFGSaveInterface
{
	GENERATED_BODY()
public:
	/** Replication. */
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	// Begin AActor interface
	virtual void Serialize( FArchive& ar ) override;
	virtual void BeginPlay() override;
	virtual void Tick( float dt ) override;
	virtual void DisplayDebug( class UCanvas* canvas, const class FDebugDisplayInfo& debugDisplay, float& YL, float& YPos ) override;
	// End AActor interface

	/** Ctor */
	AFGRailroadSubsystem();

	/** Get the railroad subsystem, this should always return something unless you call it really early. */
	static AFGRailroadSubsystem* Get( UWorld* world );

	/** Get the railroad subsystem from a world context, this should always return something unless you call it really early. */
	UFUNCTION( BlueprintPure, Category = "Railroad", DisplayName = "GetRailroadSubsystem", Meta = ( DefaultToSelf = "worldContext" ) )
	static AFGRailroadSubsystem* Get( UObject* worldContext );



	/***************************************************************************************************
	 * Functions to handle Trains
	 */

	/**
	 * Spawn a new vehicle at the given location and register it as a train.
	 * @param vehicleClass		Class to spawn.
	 * @param trackPosition		Where on the track to spawn it, must be valid!
	 * @param coupleTo			(optional) Couple the new vehicle to an existing one.
	 * @return The spawned train; nullptr on failure.
	 */
	class AFGRailroadVehicle* SpawnTrain( TSubclassOf< class AFGRailroadVehicle > vehicleClass,
										  const struct FRailroadTrackPosition& trackPosition,
										  class AFGRailroadVehicle* coupleTo );

	/**
	 * Destroy the given train, handles decoupling from other wagons as well.
	 */
	void DestroyTrain( class AFGRailroadVehicle* vehicle );

	/**
	 * Couples two trains together.
	 * @param parentVehicle		This is the attach parent, this is not moved during the snap.
	 * @param otherVehicle		This train is nudged and attached to parent. @note This may be a newly spawned unregistered vehicle.
	 */
	void CoupleTrains( AFGRailroadVehicle* parentVehicle, AFGRailroadVehicle* otherVehicle );

	/**
	 * De-couples two vehicles in a train.
	 * To decouple a vehicle completely you need to run this for booth ends of the vehicle.
	 */
	void DecoupleTrains( AFGRailroadVehicle* firstVehicle, AFGRailroadVehicle* secondVehicle );

	/**
	 * Get the distance between two train vehicles.
	 */
	FORCEINLINE static float GetCouplingDistance( float firstVehicleLength, float secondVehicleLength )
	{
		return firstVehicleLength * 0.5f + secondVehicleLength * 0.5f;
	}

	/**
	 * @return true if a train with ID exists; false otherwise, INDEX_NONE is always false.
	 */
	FORCEINLINE bool IsValidTrain( int32 trainID ) const { return mTrains.Contains( trainID ); }

	/**
	 * Get the train data for the given train ID.
	 * @return true on success; false if train does not exists.
	 */
	UFUNCTION( BlueprintCallable, Category = "Railroad" )
	bool GetTrainData( int32 trainID, FTrainData& out_trainData );

	/**
	 * Get the vehicle order for the given train, first and last.
	 * @param index		The trains ID, if invalid then the out pointers will be null.
	 */
	UFUNCTION( BlueprintCallable, Category = "Railroad" )
	void GetTrainOrder( int32 trainID, class AFGRailroadVehicle*& out_firstVehicle, class AFGRailroadVehicle*& out_lastVehicle );



	/***************************************************************************************************
	 * Functions to handle Self Driving and Train Controls
	 */

	/**
	 * Find the train table for the given train.
	 */
	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "Railroad" )
	class UFGRailroadTimeTable* FindTimeTable( int32 trainID ) const;

	/**
	 * Adds a time table to the train if it does not exist already.
	 */
	UFUNCTION( BlueprintCallable, Category = "Railroad" )
	class UFGRailroadTimeTable* FindOrAddTimeTable( int32 trainID );

	/**
	 * Enable/disable the autopilot on a train, does nothing if invalid train id passed or enabled/disabled twice.
	 */
	void SetTrainSelfDrivingEnabled( int32 trainID, bool isEnabled );

	/**
	 * @return true if the given train has autopilot enabled; false if invalid train id passed.
	 */
	bool IsTrainSelfDrivingEnabled( int32 trainID ) const;

	/**
	 * Finds a path for the given locomotive to the given stop.
	 *
	 * @param locomotive The locomotive to find a path for, note that a locomotive can not reverse.
	 * @param stop The stop the train should find a path to.
	 *
	 * @return Result of the pathfinding; Status code indicate if a path was found or not or if an error occured, e.g. bad params.
	 */
	UFUNCTION( BlueprintCallable, Category = "Railroad" )
	FRailroadPathFindingResult FindPathSync( class AFGLocomotive* locomotive, class AFGBuildableRailroadStation* stop );

	/**
	 * @return The master locomotive in the train; nullptr if MU is disabled or if invalid train ID passed.
	 */
	class AFGLocomotive* GetTrainMultipleUnitMaster( int32 trainID ) const;

	/**
	 * Set the new master locomotive in the train.
	 * @param trainID The trains ID, if invalid this function does nothing.
	 * @param locomotive The new master or nullptr to disable MU.
	 * @param if true the new master is forced; if false the new master will only be set if MU is disabled (current master is nullptr).
	 * @return true a new master was set or forced; false if not set or invalid trainID.
	 */
	bool SetTrainMultipleUnitMaster( int32 trainID, class AFGLocomotive* locomotive, bool force );

	/**
	 * @return true if we can set the multiple unit master on locomotive without forcing; false if we cannot.
	 */
	bool CanSetTrainMultipleUnitMaster( int32 trainID, const class AFGLocomotive* locomotive ) const;



	/***************************************************************************************************
	 * Functions to handle Train Stops
	 */

	/** Generates a new name to be used for train stops. */
	FText GenerateTrainStopName() const;

	/** @return If the stop name is available; false if another stop with this name already exists. */
	bool IsTrainStopNameAvailable( const FString& name ) const;

	/** Add a new train stop, call this when a stop is built, makes it available for use in the time tables. */
	void AddTrainStop( class AFGBuildableRailroadStation* stop );

	/** Remove a train stop, call this when a stop is dismantled. */
	void RemoveTrainStop( class AFGBuildableRailroadStation* stop );

	/** Get all available train stops for use in a time table. */
	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "Railroad" )
	void GetTrainStops( TArray< class AFGBuildableRailroadStation* >& out_stops ) const;



	/***************************************************************************************************
	 * Functions to keep track of the Tracks.
	 */

	/**
	 * Move a position along a track, leaving the current segment and entering a new if needed.
	 * @return Distance moved; may be less than delta, e.g. if the track ends.
	 */
	static float MoveTrackPosition( struct FRailroadTrackPosition& position, float delta );

	/**
	 * Add a new track segment.
	 * @note Track must have its connections set up.
	 */
	void AddTrack( class AFGBuildableRailroadTrack* track );

	/** Remove a track segment. Called on dismantle. */
	void RemoveTrack( class AFGBuildableRailroadTrack* track );



	/***************************************************************************************************
	 * Iterator for train sets.
	 * Used to iterate over all the vehicles in a train
	 *
	 * @usage    for( TTrainIterator it( FirstVehicle ); it; ++it )
	 */
	class TTrainIterator
	{
	public:
		/** Ctor */
		TTrainIterator( class AFGRailroadVehicle* vehicle ) :
			mCurrentVehicle( vehicle )
		{
		}

		/** Advances iterator to the next vehicle in the train. */
		FORCEINLINE TTrainIterator& operator++()
		{
			if( LIKELY( mCurrentVehicle ) )
			{
				mCurrentVehicle = mCurrentVehicle->GetCoupledVehicleAt( mCurrentVehicle->IsOrientationReversed() ? ERailroadVehicleCoupler::RVC_FRONT :  ERailroadVehicleCoupler::RVC_BACK );
			}
			return *this;
		}

		/** Moves iterator to the previous vehicle in the train. */
		FORCEINLINE TTrainIterator& operator--()
		{
			if( LIKELY( mCurrentVehicle ) )
			{
				mCurrentVehicle = mCurrentVehicle->GetCoupledVehicleAt( mCurrentVehicle->IsOrientationReversed() ? ERailroadVehicleCoupler::RVC_BACK :  ERailroadVehicleCoupler::RVC_FRONT );
			}
			return *this;
		}

		/** Compare if two iterator points to the same vehicle. */
		FORCEINLINE friend bool operator==( const TTrainIterator& lhs, const TTrainIterator& rhs )
		{
			return lhs.mCurrentVehicle == rhs.mCurrentVehicle;
		}
		FORCEINLINE friend bool operator!=( const TTrainIterator& lhs, const TTrainIterator& rhs )
		{
			return lhs.mCurrentVehicle != rhs.mCurrentVehicle;
		}

		/** Conversion to "bool" returning true if the iterator is valid. */
		FORCEINLINE explicit operator bool() const
		{
			return !!mCurrentVehicle;
		}

		/** inverse of the "bool" operator */
		FORCEINLINE bool operator !() const
		{
			return !( bool )*this;
		}

		/** Vehicle access */
		FORCEINLINE class AFGRailroadVehicle* operator*() const
		{
			return mCurrentVehicle;
		}
		FORCEINLINE class AFGRailroadVehicle* operator->() const
		{
			return mCurrentVehicle;
		}

	private:
		/** Current vehicle */
		UPROPERTY()
		class AFGRailroadVehicle* mCurrentVehicle;
	};

	/**
	 * Const version of the above.
	 */
	class TConstTrainIterator
	{
	public:
		/** Ctor */
		TConstTrainIterator( const class AFGRailroadVehicle* vehicle ) :
			mCurrentVehicle( vehicle )
		{
		}

		/** Advances iterator to the next vehicle in the train. */
		FORCEINLINE TConstTrainIterator& operator++()
		{
			if( LIKELY( mCurrentVehicle ) )
			{
				mCurrentVehicle = mCurrentVehicle->GetCoupledVehicleAt( mCurrentVehicle->IsOrientationReversed() ? ERailroadVehicleCoupler::RVC_FRONT : ERailroadVehicleCoupler::RVC_BACK );
			}
			return *this;
		}

		/** Moves iterator to the previous vehicle in the train. */
		FORCEINLINE TConstTrainIterator& operator--()
		{
			if( LIKELY( mCurrentVehicle ) )
			{
				mCurrentVehicle = mCurrentVehicle->GetCoupledVehicleAt( mCurrentVehicle->IsOrientationReversed() ? ERailroadVehicleCoupler::RVC_BACK : ERailroadVehicleCoupler::RVC_FRONT );
			}
			return *this;
		}

		/** Compare if two iterator points to the same vehicle. */
		FORCEINLINE friend bool operator==( const TConstTrainIterator& lhs, const TConstTrainIterator& rhs )
		{
			return lhs.mCurrentVehicle == rhs.mCurrentVehicle;
		}
		FORCEINLINE friend bool operator!=( const TConstTrainIterator& lhs, const TConstTrainIterator& rhs )
		{
			return lhs.mCurrentVehicle != rhs.mCurrentVehicle;
		}

		/** Conversion to "bool" returning true if the iterator is valid. */
		FORCEINLINE explicit operator bool() const
		{
			return !!mCurrentVehicle;
		}

		/** inverse of the "bool" operator */
		FORCEINLINE bool operator !() const
		{
			return !( bool )*this;
		}

		/** Vehicle access */
		FORCEINLINE const class AFGRailroadVehicle* operator*() const
		{
			return mCurrentVehicle;
		}
		FORCEINLINE const class AFGRailroadVehicle* operator->() const
		{
			return mCurrentVehicle;
		}

	private:
		/** Current vehicle */
		UPROPERTY()
		const class AFGRailroadVehicle* mCurrentVehicle;
	};

private:
	void TickTrains( float dt );
	void TickTrackGraphs( float dt );

	/** Initializes all auto generated station names. */
	void InitializeStationNames();

	/** Spawns a train, does not register it or make any connections. */
	class AFGRailroadVehicle* SpawnTrainInternal( TSubclassOf< class AFGRailroadVehicle > vehicleClass, const struct FRailroadTrackPosition& trackPosition );

	/**
	 * Registers a new train and it's first vehicle. More can be coupled on later.
	 */
	int32 RegisterTrain( class AFGRailroadVehicle* vehicle );

	/** Get a new UID for a train. */
	int32 GenerateUniqueTrainID();

	/**
	 * Finds a path from one railroad position to another.
	 * @note The path consists of the track connections between start and goal, it does not contain an actual goal actor.
	 *
	 * @param start           Position to pathfind from.
	 * @param end             Place to pathfind to.
	 * @param out_pathPoints  The resulting path, empty on error.
	 *
	 * @return Result of the pathfinding. I.e. if a path was found, goal is unreachable or if an error occurred, e.g. bad params.
	 */
	EGraphAStarResult FindPathSyncInternal( const FRailroadTrackPosition& start,
											const FRailroadTrackPosition& end,
											TArray< FRailroadGraphAStarPathPoint >& out_pathPoints ) const;

	/**
	 * @todotrains FPhysScene callbacks
	 *             PhysScene->OnPhysScenePreTick
	 *             PhysScene->OnPhysSceneStep
	 *             These should be called from the physics using the physics delta time, see FPhysXVehicleManager::PreTick and ::Update.
	 */
	//void PreTickPhysics( FPhysScene* PhysScene, uint32 SceneType, float DeltaTime );
	//void UpdatePhysics( FPhysScene* PhysScene, uint32 SceneType, float DeltaTime );

	/** Called when the vehicles in a train changes, i.e. rolling stock is (de)coupled. */
	void OnTrainOrderChanged( int32 trainID );

	/** Creates the sound component for the whole train, this is only needed on one vehicle in the train. */
	class UFGRailroadVehicleSoundComponent* CreateSoundComponentFor( class AFGRailroadVehicle* vehicle );

	/** Called when the multiple unit master is changed on a train. */
	void OnMultipleUnitChanged( int32 trainID );

	/** Merge two track graphs to one. */
	void MergeTrackGraphs( int32 first, int32 second );

	/** Create a new track graph. */
	int32 CreateTrackGraph();

	/** Remove track graph. */
	void RemoveTrackGraph( int graphID );

	/** Adds a track to a graph, performs a merge if the track is connected to another graph. */
	void AddTrackToGraph( class AFGBuildableRailroadTrack* track, int32 graphID );

	/** Get a new UID for a track graph. */
	int32 GenerateUniqueTrackGraphID();

public:
	/**
	 * How far apart can trains connect to each other.
	 * Can be used as the actor distance or track distance.
	 * (note that the track distance will be slightly longer than the actor distance in curved sections)
	 */
	UPROPERTY( EditDefaultsOnly )
	float mConnectDistance;

	/** Default switch control to place when building switches. */
	UPROPERTY( EditDefaultsOnly )
	TSubclassOf< class AFGBuildableRailroadSwitchControl > mSwitchControlClass;

	/** This is sound component used to play sounds on trains. */
	UPROPERTY( EditDefaultsOnly )
	TSubclassOf< class UFGRailroadVehicleSoundComponent > mVehicleSoundComponentClass;

private:
	/** Counters for generating UIDs. */
	int32 mTrainIDCounter;
	int32 mTrackGraphIDCounter;

	/** All the trains in the world! */
	UPROPERTY()
	TMap< int32, FTrain > mTrains;

	/** All the train stops in the game. */
	UPROPERTY( Replicated )
	TArray< class AFGBuildableRailroadStation* > mTrainStops;

	/** A random name is picked from here when placing a stop. */
	UPROPERTY()
	TArray< FString > mStationNames;

	/** All the train tracks in the world, separated by connectivity. */
	UPROPERTY()
	TMap< int32, FTrackGraph > mTrackGraphs;
};
