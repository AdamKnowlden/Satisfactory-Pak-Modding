// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Hologram/FGBuildableHologram.h"
#include "Components/SplineComponent.h"
#include "FSplinePointData.h"
#include "FGSplineHologram.generated.h"

//@todo This is only used by the roads for now, use this for the conveyors/tracks as well.
/**
 * Base hologram for all spline type holograms.
 */
UCLASS()
class FACTORYGAME_API AFGSplineHologram : public AFGBuildableHologram
{
	GENERATED_BODY()
public:
	AFGSplineHologram();

	// Begin AActor Interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	// End AActor Interface

	// Begin AFGHologram Interface
	virtual TArray< FItemAmount > GetCost( bool includeChildren ) const override;
	// End AFGHologram Interface

protected:
	/** Update the spline on the client. */
	UFUNCTION()
	virtual void OnRep_SplineData();

	/** Override this to return how many segments to pay for. Defaults to 1. */
	virtual int32 GetNumCostSections() const;

protected:
	/** The spline component we're placing. */
	UPROPERTY()
	class USplineComponent* mSplineComponent;

	/** This is the data needed to create the spline component (local space). */
	UPROPERTY( ReplicatedUsing = OnRep_SplineData )
	TArray< FSplinePointData > mSplineData;

	/** What is the maximum length of the spline. */
	UPROPERTY( EditDefaultsOnly, Category = "Spline" )
	float mMaxLength;
	/** What is the minimum length of the spline. */
	UPROPERTY( EditDefaultsOnly, Category = "Spline" )
	float mMinLength;

	/** What is the minimum radius of an arc on this spline. */
	UPROPERTY( EditDefaultsOnly, Category = "Spline" )
	float mMinBendRadius;

	/** What is the maximum incline of the spline (degrees). */
	UPROPERTY( EditDefaultsOnly, Category = "Spline" )
	float mMaxIncline;
};
