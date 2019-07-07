// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "GameFramework/PawnMovementComponent.h"
#include "WheeledVehicleMovementComponent.h"
#include "FGRailroadVehicle.h"
#include "UObject/Interface.h"
#include "FGRailroadVehicleMovementComponent.generated.h"

/**
 * Vehicle-specific setup for wheelsets and bogies.
 */
USTRUCT()
struct FACTORYGAME_API FWheelsetSetup
{
	GENERATED_USTRUCT_BODY()

	FWheelsetSetup();

	/** Bone name on mesh where the wheelset/bogie is located. */
	UPROPERTY( EditAnywhere, Category = "WheelsetSetup" )
	FName BoneName;

	/** Is this wheel set a bogie. */
	UPROPERTY( EditAnywhere, Category = "WheelsetSetup" )
	bool CanSwivel;

	/** Where the axle/swivel center is along the vehicles X axis relative to the root. Calculated from the mesh. */
	float Offset;
};

/**
 * Vehicle-specific setup for couplers.
 */
USTRUCT()
struct FACTORYGAME_API FCouplerSetup
{
	GENERATED_USTRUCT_BODY()

	FCouplerSetup();

	/** Bone name on mesh where the coupler's base is attached. */
	UPROPERTY( EditAnywhere, Category = "CouplerSetup" )
	FName BoneName;

	/** How long is the couplers arm, from the bone to the point where is attaches to the other coupler. */
	UPROPERTY( EditAnywhere, Category = "CouplerSetup" )
	float Length;

	/** Where the coupler's base is along the vehicles X axis relative to the root. Calculated from the mesh. */
	float Offset;
};

/**
 * Some helper functions for converting units
 * Useful for converting units, e.g. [kg m/s^2] to [kg cm/s^2], without making the code unreadable.
 */
inline float CmToM( float cm )
{
	return cm / 100.0f;
}

inline float MToCm( float m )
{
	return m * 100.0f;
}

inline float kNToN( float kN )
{
	return kN * 1000.0f;
}

inline float RadiansToGrade( float rad )
{
	const float clamped = FMath::Min( FMath::Abs( rad ), PI / 4.0f );
	return FMath::Tan( clamped ) * 100.0f;
}

/**
 * Base class for all types of rolling stock on the railroad.
 * This is where the physics happen.
 */
UCLASS()
class FACTORYGAME_API UFGRailroadVehicleMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()

public:
	/** Get the owning railroad vehicle. */
	class AFGRailroadVehicle* GetOwningRailroadVehicle() const;

	/** When vehicle is created we want to precompute some helper data. */
	virtual void ComputeConstants();

	/** Get the mesh this vehicle is tied to */
	class USkinnedMeshComponent* GetMesh() const;

	/** Skeletal mesh needs some special handling in the vehicle case */
	virtual void FixupSkeletalMesh();

	/** Updates the user input. */
	virtual void PreTick( float dt );

	/** Tick the traction and friction forces acting upon this vehicle. */
	virtual void TickTractionAndFriction( float dt );

	/**
	 * Move the train along the track.
	 * @param delta - How much to move the vehicle in the vehicles direction.
	 */
	virtual float MoveVehicle( float moveDelta );

	/** Updates the coupler rotation and length, called after move vehicle has been called on the whole train. */
	void UpdateCouplerRotationAndLength();

	/** Get the total mass of this vehicle, tare + payload. [kg] */
	UFUNCTION( BlueprintPure, Category = "Game|Components|RailroadVehicleMovement" )
	virtual float GetMass() const;

	/** If this vehicle is moving. Within a small threshold. */
	UFUNCTION( BlueprintPure, Category = "Game|Components|RailroadVehicleMovement" )
	FORCEINLINE bool IsMoving() const { return !FMath::IsNearlyZero( mVelocity, mZeroForwardVelocityTolerance ); }

	/** Speed of this vehicle along the track. In the direction of the train. [cm/s] */
	UFUNCTION( BlueprintPure, Category = "Game|Components|RailroadVehicleMovement" )
	FORCEINLINE float GetForwardSpeed() const { return mVelocity; }

	/** Speed of this vehicle in relative to it's orientation. [cm/s] */
	UFUNCTION( BlueprintPure, Category = "Game|Components|RailroadVehicleMovement" )
	FORCEINLINE float GetRelativeForwardSpeed() const
	{
		return GetOwningRailroadVehicle()->IsOrientationReversed() ? -mVelocity : mVelocity;
	}

	/** Arbitrary maximum speed of this vehicle along the track. [cm/s] */
	UFUNCTION( BlueprintPure, Category = "Game|Components|RailroadVehicleMovement" )
	FORCEINLINE float GetMaxForwardSpeed() const { return KmHToCmS( mMaxVelocity ); }

	/** Update the speed of this vehicle to be used in calculations. [cm/s] */
	FORCEINLINE void SetForwardSpeed( float velocity ) { mVelocity = velocity; }

	/** Get the tractive force for this vehicle, this have a direction. [N] [kg cm/s^2] */
	UFUNCTION( BlueprintPure, Category = "Game|Components|RailroadVehicleMovement" )
	FORCEINLINE float GetTractiveForce() const { return mTractiveForce; }

	/** Get the tractive force for this vehicle, this has no direction. [N] [kg cm/s^2] */
	FORCEINLINE float GetResistiveForce() const { return mAirResistance + mRollingResistance + mCurvatureResistance; }

	/** Get the force added by the slope. [N] [kg cm/s^2] */
	FORCEINLINE float GetGradientForce() const { return mGradientResistance; }

	/** Get the force by the dynamic + air brakes, this has no direction. [N] [kg cm/s^2] */
	FORCEINLINE float GetBrakingForce() const { return mDynamicBrakingForce + mAirBrakingForce; }

	/** Get dynamic braking force. [N] [kg cm/s^2] */
	UFUNCTION( BlueprintPure, Category = "Game|Components|RailroadVehicleMovement" )
	FORCEINLINE float GetDynamicBrakingForce() const { return mDynamicBrakingForce; }

	/** Get air braking force. [N] [kg cm/s^2] */
	UFUNCTION( BlueprintPure, Category = "Game|Components|RailroadVehicleMovement" )
	FORCEINLINE float GetAirBrakingForce() const { return mAirBrakingForce; }

	/** Get max air braking force. [N] [kg cm/s^2] */
	UFUNCTION( BlueprintPure, Category = "Game|Components|RailroadVehicleMovement" )
	FORCEINLINE float GetMaxAirBrakingEffort() const { return kNToN( MToCm( mMaxAirBrakingEffort ) ) ; }

	/** An estimated braking force that the vehicle can apply in it's operational speed range. [N] [kg cm/s^2] */
	FORCEINLINE float GetMinBrakingEffort() const { return mMinBrakingEffort; }

	/** Get the current payload mass for vehicle. [kg] */
	UFUNCTION( BlueprintPure, Category = "Game|Components|RailroadVehicleMovement" )
	FORCEINLINE float GetPayloadMass() const { return mPayloadMass; }

	/** Set the current payload mass for vehicle. [kg] */
	UFUNCTION( BlueprintCallable, Category = "Game|Components|RailroadVehicleMovement" )
	void SetPayloadMass( float payload ) { mPayloadMass = payload; }

	/** Slope of the track. [radians] */
	UFUNCTION( BlueprintPure, Category = "Game|Components|RailroadVehicleMovement" )
	FORCEINLINE float GetTrackGrade() const { return mTrackGrade; }

	/**
	 * Expressed as degree of curvature over 30 m. [radians]
	 * 5 degrees means the forward direction (of the track) changes by 5 degrees over 30 m.
	 */
	UFUNCTION( BlueprintPure, Category = "Game|Components|RailroadVehicleMovement" )
	FORCEINLINE float GetTrackCurvature() const { return mTrackCurvature; }

	/** Helper functions to get some vehicle force data. */
	FORCEINLINE float GetRollingResistance() const { return mRollingResistance; }
	FORCEINLINE float GetCurvatureResistance() const { return mCurvatureResistance; }
	FORCEINLINE float GetAirResistance() const { return mAirResistance; }
	FORCEINLINE float GetGradientResistance() const { return mGradientResistance; }

	// Begin UActorComponent Interface
	virtual void OnCreatePhysicsState() override;
	virtual void OnDestroyPhysicsState() override;
	virtual bool ShouldCreatePhysicsState() const override;
	virtual bool HasValidPhysicsState() const override;
	// End UActorComponent Interface

	/** Get number of wheel sets */
	UFUNCTION( BlueprintPure, Category = "Game|Components|RailroadVehicleMovement" )
	int32 GetNumWheelsets() const { return mWheelsetSetups.Num(); };

	/** Get the rotation for a wheelset. */
	UFUNCTION( BlueprintPure, Category = "Game|Components|RailroadVehicleMovement" )
	FVector GetWheelsetRotation( int32 index ) const;

	/** Get the offset for a wheelset relative to the root bone along the forward (X) axis. */
	UFUNCTION( BlueprintPure, Category = "Game|Components|RailroadVehicleMovement" )
	float GetWheelsetOffset( int32 index ) const;

	/** Get the couplers rotation for a coupler. */
	UFUNCTION( BlueprintPure, Category = "Game|Components|RailroadVehicleMovement" )
	FVector GetCouplerRotationAndExtention( int32 index, UPARAM( DisplayName="Extention" ) float& out_extention ) const;

protected:
	/** Get the movement component for the vehicle coupled at the given coupler. */
	UFGRailroadVehicleMovementComponent* GetCoupledMovementAt( ERailroadVehicleCoupler coupler ) const;

	/** Get the drag area for this vehicle. */
	FORCEINLINE float GetDragArea() const { return mChassisHeight * mChassisWidth; }

private:
	/**
	 * Helper to position the couplers.
	 * @return The distance to the other coupler in local space.
	 */
	FVector CalcCouplerDistance( ERailroadVehicleCoupler coupler ) const;

public:
	/** Threshold for when a train is considered moving */
	const float mZeroForwardVelocityTolerance = 0.01f;

protected:
	/** Wheelsets for this train. Front is 0 and back is 1. */
	UPROPERTY( EditAnywhere, Category = "VehicleSetup" )
	TArray< FWheelsetSetup > mWheelsetSetups;

	/** Couplers for this train. Front is 0 and back is 1. */
	UPROPERTY( EditAnywhere, Category = "VehicleSetup" )
	TArray< FCouplerSetup > mCouplerSetups;

	/** If we have a bogie that swivel then this is its rotation. */
	TArray< FVector > mWheelsetRotation;

	/** If we have a coupler then this is its target rotation and length. */
	TArray< FVector > mCouplerRotation;
	TArray< float > mCouplerExtention;

	/**
	 * Mass to set the vehicle chassis to. It's much easier to tweak vehicle settings when
	 * the mass doesn't change due to tweaks with the physics asset. [kg]
	 */
	UPROPERTY( EditAnywhere, Category = "VehicleSetup", meta = ( ClampMin = "0.01", UIMin = "0.01" ) )
	float mMass;

	/**
	 * Rated maximum velocity for this vehicle, actual velocity can be higher or lower, use this for cosmetic calculations, sounds, particles etc. [km/h]
	 */
	UPROPERTY( EditAnywhere, Category = "VehicleSetup", meta = ( ClampMin = "0.01", UIMin = "0.01" ) )
	float mMaxVelocity;

	/**
	 * How much cargo, fuel or other extra weight do we have.
	 */
	UPROPERTY( EditAnywhere, Category = "VehicleSetup", meta = ( ClampMin = "0.0", UIMin = "0.0" ) )
	float mPayloadMass;

	/** DragCoefficient of the vehicle chassis. Good values [0.4, 0.8]. */
	UPROPERTY( EditAnywhere, Category = "VehicleSetup" )
	float mDragCoefficient;

	/** Chassis width used for drag force computation. [cm] */
	UPROPERTY( EditAnywhere, Category = "VehicleSetup", meta = ( ClampMin = "0.01", UIMin = "0.01" ) )
	float mChassisWidth;

	/** Chassis height used for drag force computation. [cm] */
	UPROPERTY( EditAnywhere, Category = "VehicleSetup", meta = ( ClampMin = "0.01", UIMin = "0.01" ) )
	float mChassisHeight;

	/** The rolling resistance coefficient for rolling the wheels along the track. Good values [0.0010, 0.0024]. */
	UPROPERTY( EditAnywhere, Category = "VehicleSetup", meta = ( ClampMin = "0.0", UIMin = "0.0" ) )
	float mRollingResistanceCoefficient;

	/** The rolling resistance coefficient for rolling the wheels along a curved track. Good values [0.0001, 0.0004]. */
	UPROPERTY( EditAnywhere, Category = "VehicleSetup", meta = ( ClampMin = "0.0", UIMin = "0.0" ) )
	float mCurvatureResistanceCoefficient;

	/** The maximum air braking force that can be delivered. [kN] [kg m/s^2 * 1000] */
	UPROPERTY( EditAnywhere, Category = "VehicleSetup", meta = ( ClampMin = "0.0", UIMin = "0.0" ) )
	float mMaxAirBrakingEffort;

	/** An estimated braking force that the vehicle can apply in it's operational speed range. [N] [kg cm/s^2] */
	float mMinBrakingEffort;

	/**
	 * Velocity of this vehicle. [cm/s]
	 */
	float mVelocity;

	/**
	 * Slope of the track. [radians]
	 * This is an approximation.
	 */
	float mTrackGrade;

	/**
	 * Expressed as degree of curvature over 30 m. [radians]
	 * 5 degrees means the forward direction (of the track) changes by 5 degrees over 30 m.
	 * This is an approximation.
	 */
	float mTrackCurvature;

	/**
	 * The traction force for this vehicle, used for the engines. [N], [kg cm/s^2]
	 */
	float mTractiveForce;

	/**
	 * The dynamic braking force that is applied.
	 */
	float mDynamicBrakingForce;

	/**
	 * The air braking force that is applied.
	 */
	float mAirBrakingForce;

	/**
	 * Air resistance at the current speed.
	 */
	float mAirResistance;

	/**
	 * Rolling resistance or rolling friction for this vehicle. [N], [kg cm/s^2]
	 */
	float mRollingResistance;

	/**
	 * Additional rolling friction on curved parts of the track. [N], [kg cm/s^2]
	 */
	float mCurvatureResistance;

	/**
	 * Force added by tracks gradient, i.e. gravity.
	 */
	float mGradientResistance;
};
