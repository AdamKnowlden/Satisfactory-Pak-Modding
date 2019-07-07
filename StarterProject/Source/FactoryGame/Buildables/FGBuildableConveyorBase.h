// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGBuildable.h"
#include "FGBuildableConveyorBase.generated.h"


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
		Offset( 0.0f ),
		ReplicationID( INDEX_NONE ),
		ReplicationKey( INDEX_NONE )
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

private:
	friend struct FConveyorBeltItems;

	UPROPERTY( NotReplicated )
	int32 ReplicationID;

	UPROPERTY( NotReplicated )
	int32 ReplicationKey;
};
FORCEINLINE bool IsValidForLoad( const FConveyorBeltItem& element ){ return element.Item.ItemClass != nullptr; }

/** Custom INetDeltaBaseState used by our custom NetDeltaSerialize. */
class FConveyorBeltItemsBaseState : public INetDeltaBaseState
{
public:

	FConveyorBeltItemsBaseState() :
		ArrayReplicationKey( INDEX_NONE )
	{
	}

	virtual bool IsStateEqual( INetDeltaBaseState* otherState )
	{
		FConveyorBeltItemsBaseState* other = static_cast< FConveyorBeltItemsBaseState* >(otherState);
		for( auto it = ItemKeyMap.CreateIterator(); it; ++it )
		{
			auto ptr = other->ItemKeyMap.Find( it.Key() );
			if( !ptr || *ptr != it.Value() )
			{
				return false;
			}
		}
		return true;
	}

	/** This maps ReplicationID to our last known replication key. */
	TMap< int32, int32 > ItemKeyMap;
	/** The replication key from the array this state was created for. */
	int32 ArrayReplicationKey;
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
	GENERATED_BODY()

	/** Ctor */
	FConveyorBeltItems() :
		IDCounter( 0 ),
		ArrayReplicationKey( INDEX_NONE )
	{
	}

	FORCEINLINE int32 Num() const
	{
		return Items.Num();
	}

	FORCEINLINE bool IsValidIndex( int32 index ) const
	{
		return Items.IsValidIndex( index );
	}

	FORCEINLINE void Add( const FConveyorBeltItem& item )
	{
		Items.Add( item );

		MarkItemDirty( Items.Last() );
	}

	FORCEINLINE void RemoveAt( int32 index )
	{
		Items.RemoveAt( index );

		MarkArrayDirty();
	}

	FORCEINLINE FConveyorBeltItem& operator[]( int32 index )
	{
		return Items[ index ];
	}

	FORCEINLINE const FConveyorBeltItem& operator[]( int32 index ) const
	{
		return Items[ index ];
	}

	/** Custom delta serialization. */
	bool NetDeltaSerialize( FNetDeltaSerializeInfo& parms );

	/** Mark the array dirty. */
	void MarkArrayDirty();

	/** Custom serialization of all items. */
	friend FArchive& operator<<( FArchive& ar, FConveyorBeltItems& items );

private:
	/** Mark a single item dirty. */
	void MarkItemDirty( FConveyorBeltItem& item );

private:
	/** Counter for assigning new replication IDs. */
	UPROPERTY( NotReplicated )
	int32 IDCounter;

	/** This maps ReplicationID to our local index into the Items array */
	UPROPERTY( NotReplicated )
	TMap< int32, int32 > ItemMap;

	/** The items on the conveyor belt. */
	UPROPERTY()
	TArray< FConveyorBeltItem > Items;

	/** Like a dirty flag. */
	UPROPERTY( NotReplicated )
	int32 ArrayReplicationKey;
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
	FORCEINLINE float GeSpeed() const { return mSpeed; }

	/** @return The connection, safe to assume its always valid. */
	FORCEINLINE class UFGFactoryConnectionComponent* GetConnection0() const { return mConnection0; }
	FORCEINLINE class UFGFactoryConnectionComponent* GetConnection1() const { return mConnection1; }

	/** Map a world location to an offset along the conveyor. */
	virtual float FindOffsetClosestToLocation( const FVector& location ) const PURE_VIRTUAL( , return 0.0f; );
	/** Get the location and direction of the conveyor at the given offset. */
	virtual void GetLocationAndDirectionAtOffset( float offset, FVector& out_location, FVector& out_direction ) const PURE_VIRTUAL( , );

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
	FInventoryItem Factory_PeekItemAt( int32 index ) const;
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
	bool mPendingUpdateItemTransforms;
};
