// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/CoreNet.h"
#include "Array.h"
#include "UnrealString.h"
#include "GameFramework/Actor.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "../FGFactoryConnectionComponent.h"
#include "FGBuildable.h"
#include "../FGRemoteCallObject.h"
#include "FGBuildableConveyorBase.generated.h"


using FG_ConveyorItemRepKeyType = int16;
using FG_ConveyorVersionType = int8;



UCLASS()
class UFGConveyorRemoteCallObject : public UFGRemoteCallObject
{
	GENERATED_BODY()
	public:
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	/** Compact representation of mSplineComponent, used for replication and save game */
	UPROPERTY( Replicated, Meta = ( NoAutoJson ) )
	bool mForceNetField_UFGConveyorRemoteCallObject = false;

	UFUNCTION( Reliable, Server, WithValidation, Category = "Use" )
	void Server_OnUse( class AFGBuildableConveyorBelt* target, class AFGCharacterPlayer* byCharacter, int32 itemIndex, int8 repVersion );


	//UFUNCTION( Reliable, Server, WithValidation, Category = "Sync" )
	//void Server_RequestCleanSync( class AFGBuildableConveyorBelt* target );
};


/**
* Holds data for an item traveling on the conveyor.
*
* @note This item must not contain any object references as they will not get replicated correctly.
* @note We do not yet support changes to variables, only initial replication will be done.
* @note We only support adds at the end of the array, no inserts allowed!
*
* @see FConveyorBeltItems::NetDeltaSerialize for more comments about the features supported and not.
*/
USTRUCT()
struct FConveyorBeltItem
{
	GENERATED_BODY()

	/** Ctor */
		FConveyorBeltItem() :
		Item(),
		Offset( 0.0f )
	{
	}

	/** Ctor */
	explicit FConveyorBeltItem( const FInventoryItem& item ) :
		FConveyorBeltItem()
	{
		Item = item;
	}

	/** The type of this item. */
	UPROPERTY()
	FInventoryItem Item;

	/**
	* The offset of this item along the conveyor belt in range [0,LENGTH].
	* @todo This only need to replicate when the item is added to the conveyor as it is simulated locally on the client after that.
	*       Having this replicated always works for now because we never mark an item as dirty after adding it.
	*       I.e. we only do one replication per item.
	*/
	UPROPERTY()
	float Offset;
	bool Removed = false;
	bool AnimateRemove = false; //@TODO:[DavalliusA:Tue/11-06-2019] not really used any more? MAke sure that is the case and if so, fix it.

	//Sets to a rep key value of the current version on the client when sending a pickup command. 
	//When receiving a package building on this state, it will be reset to INDEX_NONE, if it's a non INDEX_NONE value it will on the client be handled like if it's removed. 
	//Making things more responsive, and in 99% of the cases a remove should go through without an issue, meaning this should be a very accurate prediction. However, only remove it visually. Let the item movement and so on not take this into account. Let that be in sync with the server.
	FG_ConveyorVersionType PredictedRemoveRepVersion = INDEX_NONE; 
private:
	friend struct FConveyorBeltItems;

	friend class AFGBuildableConveyorBelt; //[DavalliusA:Mon/03-06-2019] for debugging only for now

	FG_ConveyorItemRepKeyType ReplicationID = INDEX_NONE;

	FG_ConveyorItemRepKeyType ReplicationKey = INDEX_NONE;
};


/** Custom INetDeltaBaseState used by our custom NetDeltaSerialize. Representing a snapshot of the state, enough to calculate a delta between this state and another.*/
class FConveyorBeltItemsBaseState : public INetDeltaBaseState
{
public:

	FConveyorBeltItemsBaseState()
	{
	}

	FConveyorBeltItemsBaseState( const FConveyorBeltItemsBaseState& other )
	{
		TypeToBitIDMap = other.TypeToBitIDMap;
		ItemList = other.ItemList;
		ArrayReplicationKey = other.ArrayReplicationKey;
		lastSentSpacing = other.lastSentSpacing;
		NewestItemID = other.NewestItemID;
		NextToMoveOutItemID = other.NextToMoveOutItemID;
		ArrayReplicationKeyLoopCounter = other.ArrayReplicationKeyLoopCounter;
	}

	FConveyorBeltItemsBaseState( FConveyorBeltItemsBaseState&& other )
	{
		TypeToBitIDMap = other.TypeToBitIDMap;
		ItemList = other.ItemList;
		ArrayReplicationKey = other.ArrayReplicationKey;
		lastSentSpacing = other.lastSentSpacing;
		NewestItemID = other.NewestItemID;
		NextToMoveOutItemID = other.NextToMoveOutItemID;
		ArrayReplicationKeyLoopCounter = other.ArrayReplicationKeyLoopCounter;
	}

	//virtual ~FConveyorBeltItemsBaseState();

	const FConveyorBeltItemsBaseState& operator=( const FConveyorBeltItemsBaseState& other )
	{
		TypeToBitIDMap = other.TypeToBitIDMap;
		ItemList = other.ItemList;
		ArrayReplicationKey = other.ArrayReplicationKey;
		lastSentSpacing = other.lastSentSpacing;
		NewestItemID = other.NewestItemID;
		NextToMoveOutItemID = other.NextToMoveOutItemID;
		ArrayReplicationKeyLoopCounter = other.ArrayReplicationKeyLoopCounter;
	}

	const FConveyorBeltItemsBaseState& operator=( FConveyorBeltItemsBaseState&& other )
	{
		TypeToBitIDMap = other.TypeToBitIDMap;
		ItemList = other.ItemList;
		ArrayReplicationKey = other.ArrayReplicationKey;
		lastSentSpacing = other.lastSentSpacing;

		NewestItemID = other.NewestItemID;
		NextToMoveOutItemID = other.NextToMoveOutItemID;
		ArrayReplicationKeyLoopCounter = other.ArrayReplicationKeyLoopCounter;

	}

	virtual bool IsStateEqual( INetDeltaBaseState* otherState ) override
	{
		FConveyorBeltItemsBaseState* other = static_cast< FConveyorBeltItemsBaseState* >( otherState );
		if( ItemList.Num() != other->ItemList.Num() )
		{	
			return false;
		}
		if( lastSentSpacing != other->lastSentSpacing )
		{	
			return false;
		}
		for( int32 i = 0; i < ItemList.Num(); ++i )
		{
			if( ItemList[ i ] != other->ItemList[ i ] )
			{
				return false;
			}
		}
		for( auto it = TypeToBitIDMap.CreateIterator(); it; ++it )
		{
			auto ptr = other->TypeToBitIDMap.Find( it.Key() );
			if( !ptr || *ptr != it.Value() )
			{
				return false;
			}
		}
		return true;
	}


	//virtual void DebugPrintWhenRevertingFromNAKTo() override;
	//virtual void DebugPrintWhenRevertingFromNAKFrom() override;
	//virtual void DebugPrintWhenDeletingDueToOtherRevertingFromNAK() override;
	//virtual void DebugPrintWhenACK() override;
	//virtual FString GetDeltaIDDebugString() override;

	/**Trasnaltion of class type to an int id, so we can minimize each send size. Nb elements will be used to find a sed*/

	TMap< TSubclassOf< class UFGItemDescriptor >, uint8 > TypeToBitIDMap;
	/** This maps ReplicationID to our last known replication key. */
	//TMap< int16, int16 > ItemKeyMap;
	struct ItemHolder
	{
		ItemHolder( FG_ConveyorItemRepKeyType _id, bool _removed, float _offset ) : RepID( _id ), Removed( _removed ), Offset(_offset){}
		FG_ConveyorItemRepKeyType RepID;
		bool Removed = false;
		//@TODO:[DavalliusA:Tue/11-06-2019] remove this? We probably don't need this. But actually, we probably don't need this whole list. Just holding first and last IDs should be enough. Reconsider this implementation to save memory.
		float Offset; //[DavalliusA:Tue/14-05-2019] used to store a position, so we can accurately predict what item to remove when getting a pickup event from a client.
		//@TODO:[DavalliusA:Tue/14-05-2019] consider how to handle pickups happening on the edge of a conveyor, but it should be an no issue once we merge?
		inline bool operator!=( const ItemHolder& B ) const
		{
			return B.RepID != RepID || B.Removed != Removed;
		}
		inline bool operator==( const ItemHolder& B ) const
		{
			return B.RepID == RepID && B.Removed == Removed;
		}
	};

	

	float lastSentSpacing = -100; //used to know if we need to send a new spacing or if we can use the default state
	TArray<ItemHolder> ItemList; //[DavalliusA:Thu/11-04-2019] see if we can move this to a static size, or templateify the size, so we can keep it in one memory chunk for each history entry.

	FG_ConveyorItemRepKeyType NewestItemID = INDEX_NONE;
	FG_ConveyorItemRepKeyType NextToMoveOutItemID = INDEX_NONE + 1; //oldest item. If the conveyor is empty, this value will be NewestItemID+1

																	/** The replication key from the array this state was created for. */

	FG_ConveyorVersionType ArrayReplicationKey = INDEX_NONE;
	uint8	ArrayReplicationKeyLoopCounter = 0;
	struct FConveyorBeltItems* ObjectDebugPtr = nullptr;
};

/**
* Struct to help replicate the conveyor belt items array.
* It's a lean version of fast TArray replication that guarantee the same order of the elements on server and client.
* It lacks support for:
*   - Item changes (initial replication only) there is a todo in the source file on how this can be added if needed.
*   - Mapping of object references (objects that are replicated that is). Look at fast TArray replication on how to implement this if needed.
*/
USTRUCT()
struct FConveyorBeltItems
{
	static const uint8 NUM_HISTORY_VERSION = 27; //[DavalliusA:Thu/16-05-2019] should be enough to get about 2 sec back with 3 other clients connected and we were to send at max speed for each client separately 3*3*2

	struct ItemHolderHistory //[DavalliusA:Tue/14-05-2019] used to store a history list on the server, with a looping array of version, to be be able to jump back in time for interactions sent from clients (picking up items and such)
	{
		FG_ConveyorVersionType ArrayReplicationKey = INDEX_NONE;
		TArray<FConveyorBeltItemsBaseState::ItemHolder> ItemList;
	};

	GENERATED_BODY()

	/** Ctor */
		FConveyorBeltItems();

	FORCEINLINE int16 Num() const
	{
		return ( int16 )Items.Num();
	}

	FORCEINLINE bool IsValidIndex( int16 index ) const
	{
		return Items.IsValidIndex( index );
	}

	FORCEINLINE void Add( const FConveyorBeltItem& item )
	{
		Items.Add( item );
		Items.Last().ReplicationID = INDEX_NONE;
		MarkItemDirty( Items.Last() );
		if( Items.Num() > 1 )
		{
			//@todomissmatch checkf( Items.Last().ReplicationID == Items[ Items.Num() - 2 ].ReplicationID + 1, TEXT( "Make sure the items build in ID numbers like intended. Otherwise other math will fail later. New item: %d, item before: %d" ), Items.Last().ReplicationID, Items[ Items.Num() - 2 ].ReplicationID );
		}
		NewestItemID = Items.Last().ReplicationID; //[DavalliusA:Mon/06-05-2019] make sure this is always up to date
	}

	//Enforce a good number sequence of items and set counter values to be in sync. Should only be used post load, before network serialization.
	void PostLoadResetAllItemIDs()
	{
		if( Items.Num() > 0 )
		{
			IDCounter = Items[ 0 ].ReplicationID;
			for( auto itm : Items )
			{
				itm.ReplicationID = IDCounter++;
				if( IDCounter == INDEX_NONE )
				{
					++IDCounter;
				}
			}
			NewestItemID = Items.Last().ReplicationID; //[DavalliusA:Mon/06-05-2019] make sure this is always up to date
		}
		else
		{
			NewestItemID = IDCounter - 1;
		}
	}


	FORCEINLINE void RemoveItemFromListAt( int16 index )
	{
		Items.RemoveAt( index );

		MarkArrayDirty();
	}

	FORCEINLINE bool IsRemovedAt( int16 index )
	{
		return Items[ index ].Removed || !Items[index].Item.IsValid();
	}

	FORCEINLINE void FlagForRemoveAt( int16 index )
	{
		Items[ index ].Removed = true;
	}

	FORCEINLINE FConveyorBeltItem& operator[]( int16 index )
	{
		return Items[ index ];
	}

	FORCEINLINE const FConveyorBeltItem& operator[]( int16 index ) const
	{
		return Items[ index ];
	}


	int32 GetIndexForItemByRepKey( FG_ConveyorItemRepKeyType itemID );

	FG_ConveyorVersionType GetRepKey() const
	{
		return ArrayReplicationKey;
	}

	FG_ConveyorVersionType GetRepKeyRecived() const
	{
		return ArrayReplicationKeyLastSerialized;
	}
	/** Custom delta serialization. */
	bool NetDeltaSerialize( FNetDeltaSerializeInfo& parms );

	/** Mark the array dirty. */
	void MarkArrayDirty();

	void UpdateLastestIDFromState();

	/** Custom serialization of all items. */
	friend FArchive& operator<<( FArchive& ar, FConveyorBeltItems& items );


	void SetOwner( class AFGBuildableConveyorBase* _owner )
	{
		Owner = _owner;
	}

	int16 GetCombinedDirtyKey()
	{
		return ArrayReplicationKey + ArrayReplicationKeyLastSerialized;
	}

	float ConsumeAndUpdateConveyorOffsetDept( float dt );

	ItemHolderHistory* GetHistoryVersion( FG_ConveyorVersionType version );
	ItemHolderHistory* AddAndGetHistoryVersion( FG_ConveyorVersionType version )
	{
		if( !VersionHistoryStateList )
		{
			VersionHistoryStateList = new ItemHolderHistory[ NUM_HISTORY_VERSION ];
		}
		
		for( int32 i = 0; i < NUM_HISTORY_VERSION; ++i )
		{
			if( VersionHistoryStateList[ i ].ArrayReplicationKey == version )
			{
				return &(VersionHistoryStateList[ i ]);
			}
		}
		
		++VersionHistoryStateListWriteHead;
		if( VersionHistoryStateListWriteHead >= NUM_HISTORY_VERSION )
			VersionHistoryStateListWriteHead = 0;
		VersionHistoryStateList[ VersionHistoryStateListWriteHead ].ArrayReplicationKey = version;
		VersionHistoryStateList[ VersionHistoryStateListWriteHead ].ItemList.Reset();
		return &( VersionHistoryStateList[ VersionHistoryStateListWriteHead ] );
	}

	TArray< FConveyorBeltItem >& AnimRemoveList()
	{
		return AnimRemoveItems;
	}
	bool IsDesynced()
	{
		return bIsDesynced;
	}
	float& GetDesyncedNotifyTimer()
	{
		return DescynNotifyTimer;
	}

	float ConveyorLength; //[DavalliusA:Fri/26-04-2019] only used for improving appearance on belts that have gotten completely de-synced from the delta
	int16 DebugID = INDEX_NONE;
private:
	/** Mark a single item dirty. */
	void MarkItemDirty( FConveyorBeltItem& item );

private:
	/** Counter for assigning new replication IDs. */
	int16 IDCounter; //@TODO:[DavalliusA:Tue/11-06-2019] Seems to not be used. Check and remove.

	TMap< TSubclassOf< class UFGItemDescriptor >, uint8 > TypeToBitIDMap;

	ItemHolderHistory* VersionHistoryStateList = nullptr;
	int8 VersionHistoryStateListWriteHead = NUM_HISTORY_VERSION;

	TArray< FConveyorBeltItem > Items; //0 = first added item (item to be removed/move out next), max/end/n = newest item/item added most recently.
	TArray< FConveyorBeltItem > AnimRemoveItems; //holding items we should no longer include in logics, and are just removing animation wise
	FG_ConveyorItemRepKeyType NewestItemID = INDEX_NONE;

	//@TODO:[DavalliusA:Fri/12-04-2019]  consider moving this to an object we allocate only on clients?
	struct DeltaLogStruct
	{
		struct Delta
		{
			FG_ConveyorVersionType BasedOnKey = INDEX_NONE - 1; //[DavalliusA:Thu/25-04-2019] make sure it's not a key that is same as the default replicationKey, so we can end up in infinite loops when traversing them 
			FG_ConveyorVersionType ReplicationKey = INDEX_NONE;
			uint8 NumToDelete = 0;
			uint8 NumToAdd = 0;
			int16 NumItems = 0;
		};
		static const uint8 LOG_SIZE = 32;
		uint8 WriteHead = 0;
		Delta Deltas[ LOG_SIZE ];


		/**0 = latest default, 1 = the delta before that. Taking the looping buffer into account*/
		inline Delta& GetDelta( uint8 stepsBack )
		{
			++stepsBack; //as 0 = the one before the write head, do minus one extra
			uint8 i = WriteHead;
			if( i < stepsBack )
			{
				i += LOG_SIZE - stepsBack;
			}
			else
			{
				i -= stepsBack;
			}
			return Deltas[ i ];
		}
		//@TODO:[DavalliusA:Tue/16-04-2019] make so we start searching from the current write head, as we are likely to only look for the most recent entries anyway
		inline Delta* FindRepKey( FG_ConveyorVersionType repKey )
		{
			for( auto & d : Deltas )
			{
				if( d.ReplicationKey == repKey )
				{
					return &d;
				}
			}
			return nullptr;
		}
		//@TODO:[DavalliusA:Tue/16-04-2019] make so we start searching from the current write head, as we are likely to only look for the most recent entries anyway
		inline Delta* FindBaseKey( FG_ConveyorVersionType baseKey )
		{
			for( auto & d : Deltas )
			{
				if( d.BasedOnKey == baseKey )
				{
					return &d;
				}
			}
			return nullptr;
		}

		void AddDelta( FG_ConveyorVersionType basedOnKey, FG_ConveyorVersionType replicationKey, uint8 numDeleted, uint8 numAdded, int16 numItems )
		{
			Deltas[ WriteHead ].BasedOnKey = basedOnKey;
			Deltas[ WriteHead ].ReplicationKey = replicationKey;
			Deltas[ WriteHead ].NumToDelete = numDeleted;
			Deltas[ WriteHead ].NumToAdd = numAdded;
			Deltas[ WriteHead ].NumItems = numItems;
			++WriteHead;
			if( WriteHead >= LOG_SIZE )
				WriteHead = 0;
		}
		void EnterAndSetupResetState()
		{
			for( auto & d : Deltas )
			{
				d.BasedOnKey = INDEX_NONE - 1;
				d.ReplicationKey = INDEX_NONE;
				d.NumToAdd = 0;
				d.NumToDelete = 0;
				d.NumItems = 0;
			}
		}
	};
	DeltaLogStruct DeltaLog;

	/** Like a dirty flag. */

	FG_ConveyorVersionType ArrayReplicationKey = 0;

	FG_ConveyorVersionType ArrayReplicationKeyLastSerialized = INDEX_NONE; //[DavalliusA:Wed/17-04-2019] we might not be able to use the regular one, as client simulation might accidentally call make dirty and increase our version then

	FG_ConveyorVersionType BaseReplicationKey = INDEX_NONE;

	float lastRecivedSpacing = 0; //we should not need to store this in the delta history, as a new spacing should be sent if any of them are irregular enough to need a new spacing.
	float ConveyorOffsetDept = 0; //used to adjust for removes and adds that were received with bad timing
	float DeltaSinceLastNetUpdate = 0; //@TODO:[DavalliusA:Tue/11-06-2019] store a time in the delta log, so we can know the time since for the individual deltas? This can get arbitary quickly...
	float DescynNotifyTimer = -100;

	uint8	ArrayReplicationKeyLoopCounter = 0;
	uint8	NumPotentialDriftingSends = 0;

	bool bIsDesynced = false;
	bool bIsInResetState = false; //this means we we've gotten a reset signal from the server and will treat all history events till the next real event differently.

	class AFGBuildableConveyorBase* Owner = nullptr;

	friend FConveyorBeltItemsBaseState;
	friend class AFGBuildableConveyorBelt;
};


/** Enable custom net delta serialization for the above struct. */
template<>
struct TStructOpsTypeTraits< FConveyorBeltItems > : public TStructOpsTypeTraitsBase2< FConveyorBeltItems >
{
	enum
	{
		WithNetDeltaSerializer = true
	};
};


/**
 * Shared base for conveyor belts and lifts.
 * Responsible for common logic such as the factory ticking, replication, interactions etc.
 */
UCLASS(Abstract)
class FACTORYGAME_API AFGBuildableConveyorBase : public AFGBuildable
{
	GENERATED_BODY()
public:
	AFGBuildableConveyorBase();

	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type endPlayReason ) override;
	virtual void Serialize( FArchive& ar ) override;
	virtual void Tick( float dt ) override;
	// End AActor interface

	// Begin IFGSaveInterface
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	// End IFGSaveInterface

	// Begin AFGBuildableFactory interface
	virtual uint8 MaxNumGrab( float dt ) const override;
	// End AFGBuildableFactory interface

	FORCEINLINE float GetLength() const { return mLength; }
	FORCEINLINE float GetSpeed() const { return mSpeed; }

	/** @return The connection, safe to assume its always valid. */
	FORCEINLINE class UFGFactoryConnectionComponent* GetConnection0() const { return mConnection0; }
	FORCEINLINE class UFGFactoryConnectionComponent* GetConnection1() const { return mConnection1; }

	/** Map a world location to an offset along the conveyor. */
	virtual float FindOffsetClosestToLocation( const FVector& location ) const PURE_VIRTUAL( , return 0.0f; );
	/** Get the location and direction of the conveyor at the given offset. */
	virtual void GetLocationAndDirectionAtOffset( float offset, FVector& out_location, FVector& out_direction ) const PURE_VIRTUAL( , );


	virtual void PreReplication( IRepChangedPropertyTracker& ChangedPropertyTracker ) override;

protected:
	// Begin Factory_ interface
	virtual void Factory_Tick( float deltaTime ) override;
	virtual bool Factory_PeekOutput_Implementation( const class UFGFactoryConnectionComponent* connection, TArray< FInventoryItem >& out_items, TSubclassOf< UFGItemDescriptor > type ) const override;
	virtual bool Factory_GrabOutput_Implementation( class UFGFactoryConnectionComponent* connection, FInventoryItem& out_item, float& out_OffsetBeyond, TSubclassOf< UFGItemDescriptor > type ) override;
	// End Factory_ interface

	// Begin AFGBuildable interface
	virtual void GetDismantleInventoryReturns( TArray< FInventoryStack >& out_returns ) const override;
	// End AFGBuildable interface

	void MarkItemTransformsDirty() { mPendingUpdateItemTransforms = true; }

	/** Called when the visuals, radiation etc need to be updated. */
	virtual void TickItemTransforms( float dt ) PURE_VIRTUAL(,);

	//@todonow These can possibly be moved to private once Belt::OnUse has been moved to base.
	/** Find the item closest to the given location. */
	int32 FindItemClosestToLocation( const FVector& location ) const;

	/** Checks if there is an item at index. */
	bool Factory_HasItemAt( int32 index ) const;
	/** Lets you know what type of item is on a specific index. */
	const FConveyorBeltItem& Factory_PeekItemAt( int32 index ) const;
	/** Remove an item from the belt at index. */
	void Factory_RemoveItemAt( int32 index );

private:
	/** Take the first element on the belt. */
	void Factory_DequeueItem();
	/** Put a new item onto the belt. */
	void Factory_EnqueueItem( const FInventoryItem& item, float initialOffset );

	/**
	 * @param out_availableSpace - amount of space until next item
	 *
	 * @return true if there is enough room for an item of size itemSize
	 */
	bool HasRoomOnBelt( float& out_availableSpace ) const;

public:
	/** Default height above ground for conveyors. */
	static constexpr float DEFAULT_CONVEYOR_HEIGHT = 100.f;

	/** Spacing between each conveyor item, from origo to origo. */
	static constexpr float ITEM_SPACING = 120.0f;

protected:

	/** Speed of this conveyor. */
	UPROPERTY( EditDefaultsOnly, Category = "Conveyor" )
	float mSpeed;

	/** Length of the conveyor. */
	float mLength;

	/** All the locally simulated resource offsets on the conveyor belt. */
	UPROPERTY( Replicated, Meta = ( NoAutoJson ) )
	FConveyorBeltItems mItems;

	/** First connection on conveyor belt, Connections are always in the same order, mConnection0 is the input, mConnection1 is the output. */
	UPROPERTY( VisibleAnywhere, Category = "Conveyor" )
	class UFGFactoryConnectionComponent* mConnection0;
	/** Second connection on conveyor belt */
	UPROPERTY( VisibleAnywhere, Category = "Conveyor" )
	class UFGFactoryConnectionComponent* mConnection1;

private:
	int16 mLastItemsDirtyKey = -2;
	bool mPendingUpdateItemTransforms;
};
