// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGVehicle.h"
#include "Buildables/FGBuildableRailroadTrack.h"
#include "FGRailroadVehicle.generated.h"


/**
 * Type of connections in the game.
 */
UENUM()
enum class ERailroadVehicleCoupler : uint8
{
	RVC_FRONT = 0	UMETA( DisplayName = "Front" ),
	RVC_BACK = 1	UMETA( DisplayName = "Back" )
};

/**
 * Base vehicle for all railroad vehicles. E.g. locomotives, wagons etc.
 */
UCLASS()
class FACTORYGAME_API AFGRailroadVehicle : public AFGVehicle
{
	GENERATED_BODY()
public:
	/** Replication */
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual bool IsNetRelevantFor( const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation ) const override;
	bool IsVehicleNetRelevantFor( const class AFGRailroadVehicle* vehicle, const FVector& SrcLocation ) const;

	/** Ctor */
	AFGRailroadVehicle();

	// Begin AActor interface
	virtual void Serialize( FArchive& ar ) override;
	// End AActor interface

	// Begin IFGSaveInterface
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	// End IFSaveInterface

	//~ Begin IFGDismantleInterface
	virtual bool CanDismantle_Implementation() const override;
	//~ End IFGDismantleInterface

	/** Update the animations for this vehicle, this is called after the whole train has been moved. */
	void UpdateAnimation();

	/** Get the railroad movement for this vehicle. */
	UFUNCTION( BlueprintPure, Category = "Vehicle|Railroad" )
	virtual class UFGRailroadVehicleMovementComponent* GetRailroadVehicleMovementComponent() const;

	/**
	 * Get the train ID for this vehicle.
	 */
	UFUNCTION( BlueprintPure, Category = "Vehicle|Railroad" )
	FORCEINLINE int32 GetTrainID() const { return mTrainID; }

	/**
	 * Get the master locomotive for the train this vehicle is part of.
	 * @return Can be nullptr if MU is disabled (no driver) or if client replication is slow.
	 */
	FORCEINLINE class AFGLocomotive* GetMultipleUnitMaster() const { return mMultipleUnitMaster; }

	/**
	 * Set the master locomotive for the train this vehicle is part of.
	 * @param locomotive The new master, can be nullptr.
	 */
	void SetMultipleUnitMaster( class AFGLocomotive* locomotive );

	/**
	 * @return The length of this vehicle.
	 */
	UFUNCTION( BlueprintPure, Category = "Vehicle|Railroad" )
	FORCEINLINE float GetLength() const { return mLength; }

	/**
	 * If this vehicles orientation is reversed in the train formation.
	 * @return true if forward for this vehicle is not the same as the trains forward.
	 */
	UFUNCTION( BlueprintPure, Category = "Vehicle|Railroad" )
	FORCEINLINE bool IsOrientationReversed() const { return mIsOrientationReversed; }

	/**
	 * @param at Coupler, valid values are 0 (front) and 1 (back).
	 * @return the vehicle coupled at index.
	 */
	UFUNCTION( BlueprintPure, Category = "Vehicle|Railroad" )
	FORCEINLINE bool IsCoupledAt( ERailroadVehicleCoupler coupler ) const { return mCoupledVehicles[ ( uint8 )coupler ].IsValid(); }

	/**
	 * @param at Coupler, valid values are 0 (front) and 1 (back).
	 * @return the vehicle coupled at index.
	 */
	UFUNCTION( BlueprintPure, Category = "Vehicle|Railroad" )
	FORCEINLINE AFGRailroadVehicle* GetCoupledVehicleAt( ERailroadVehicleCoupler coupler ) const { return mCoupledVehicles[ ( uint8 )coupler ].Get(); }
	
	/**
	 * Get the track position for this vehicle.
	 */
	UFUNCTION( BlueprintPure, Category = "Vehicle|Railroad" )
	FORCEINLINE FRailroadTrackPosition GetTrackPosition() const { return mTrackPosition; }

	/**
	 * Set the track position for this vehicle, be careful cause the actor and any coupled vehicles will not get moved.
	 */
	FORCEINLINE void SetTrackPosition( const FRailroadTrackPosition& position ) { mTrackPosition = position; }

	/** Debug */
	virtual void DisplayDebug( class UCanvas* canvas, const class FDebugDisplayInfo& debugDisplay, float& YL, float& YPos ) override;

protected:
	// Begin AFGVehicle interface
	virtual void DestroyVehicle() override;
	// End AFGVehicle interface

private:
	/**
	 * @param at Coupler to connect to.
	 */
	void CoupleVehicleAt( AFGRailroadVehicle* vehicle, ERailroadVehicleCoupler coupler );

	/**
	 * @param at Coupler to connect to.
	 */
	void DecoupleVehicleAt( ERailroadVehicleCoupler coupler );

protected:
	/** How long is this vehicle. */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle|Railroad" )
	float mLength;

private:
	/** These need access to the vehicles internals. */
	friend class AFGRailroadSubsystem;
	friend class TTrainIterator;

	/** The train this vehicle is part of. */
	UPROPERTY( SaveGame )
	int32 mTrainID;

	/** Used when MUing multiple engines together. Indicates which locomotive is the master. */
	UPROPERTY( Replicated )
	class AFGLocomotive* mMultipleUnitMaster;

	/**
	 * A train is a doubly linked list of AFGRailroadVehicles.
	 * Use TTrainIterator to iterate over a train (in any direction).
	 */

	/**
	 * Vehicles coupled to this vehicle.
	 * Use ERailroadVehicleCoupler to access this.
	 */
	UPROPERTY()
	TWeakObjectPtr< AFGRailroadVehicle > mCoupledVehicles[ 2 ];

	/** If this vehicle is reversed in the train formation. */
	UPROPERTY( SaveGame )
	bool mIsOrientationReversed;

	/** Where along the track is the train. */
	UPROPERTY( SaveGame )
	FRailroadTrackPosition mTrackPosition;
};
