// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "SignificanceManager.h"
#include "FGSignificanceManager.generated.h"

enum class EFGSignificanceType : uint8
{
	Creature,
	AudioVolume,
	GenericTickHelper,
	ConveyorBelt,
	Factory,
	LowDistanceGainSignificance,
	MidDistanceGainSignificance,
	HighDistanceGainSignificance,
	AmbientSoundSpline,
	CustomDistanceGainSignificance,
	ParticleSignificance,
	MAX
};

USTRUCT() 
struct FGainSignificanceData
{
	GENERATED_BODY()
	EFGSignificanceType SignificanceType; 
	int32				GainSignificanceDistance;
};

/**
 * 
 */
UCLASS( Blueprintable )
class FACTORYGAME_API UFGSignificanceManager : public USignificanceManager
{
	GENERATED_BODY()
public:
	UFGSignificanceManager(); 


	//This is the function that users call as a replacement for the virtual RegisterObject which exposes only the significance type so it can be looked up
	void RegisterSignificanceObject( UObject* Object, EFGSignificanceType SignificanceType );

	virtual void Update( TArrayView<const FTransform> Viewpoints ) override;

	FGainSignificanceData GetClosestGainSignificanceData( UObject* inObject, float desiredDistance );

	/** Is the manager enabled */
	UPROPERTY( EditAnywhere, Category = "SignificanceManager" )
	bool mIsEnabled;

	/** caching delta time before doing Update() */
	float mCachedDT;
protected:
	/** Keeps the list of conveyor belts sorted and sets the closest ones to significant */
	void UpdateConveyorBelts();

	/** Keeps the list of factories sorted and sets the closest ones to significant */
	void UpdateFactories();
private:
	static FName GetTagFromTagEnum( EFGSignificanceType InType );

	static void OnComponentActivationChange( UParticleSystemComponent* PSC, bool bActivated );

	//Generic Significance functions
	static float GenericTickSignificance( FManagedObjectInfo* Object, const FTransform& Viewpoint );
	static void GenericTickPostSignificance( FManagedObjectInfo* ObjectInfo, float OldSignificance, float NewSignificance, bool bFinal );

	//Generic Significance functions
	static float ParticleTickSignificance( FManagedObjectInfo* Object, const FTransform& Viewpoint );
	static void ParticleTickPostSignificance( FManagedObjectInfo* ObjectInfo, float OldSignificance, float NewSignificance, bool bFinal );

	//Factory Significance functions
	static float FactorySignificance( FManagedObjectInfo* Object, const FTransform& Viewpoint );
	static void FactoryPostSignificance( FManagedObjectInfo* ObjectInfo, float OldSignificance, float NewSignificance, bool bFinal );

	//ConveyorBelt Significance functions
	static float ConveyorBeltSignificance( FManagedObjectInfo* Object, const FTransform& Viewpoint );
	static void ConveyorBeltPostSignificance( FManagedObjectInfo* ObjectInfo, float OldSignificance, float NewSignificance, bool bFinal );

	//Gain Significance on low distance functions
	static float LowDistanceSignificance( FManagedObjectInfo* Object, const FTransform& Viewpoint );

	//Gain Significance on mid distance functions
	static float MidDistanceSignificance( FManagedObjectInfo* Object, const FTransform& Viewpoint );

	//Gain Significance on high distance functions
	static float HighDistanceSignificance( FManagedObjectInfo* Object, const FTransform& Viewpoint );

	//Gain Significance on custom distance functions
	static float CustomDistanceSignificance( FManagedObjectInfo* Object, const FTransform& Viewpoint );

	/** Either call gain or lose significance based on value */
	static void GainSignificanceOnDistancePostSignificance( FManagedObjectInfo* ObjectInfo, float OldSignificance, float NewSignificance, bool bFinal );

	//Ambient volume functions
	static float AudioVolumeSignificance( FManagedObjectInfo* Object, const FTransform& Viewpoint );
	static void AudioVolumePostSignificance( FManagedObjectInfo* ObjectInfo, float OldSignificance, float NewSignificance, bool bFinal );

	//Ambient sound spline functions
	static float AmbientSoundSplineSignificance( FManagedObjectInfo* Object, const FTransform& Viewpoint );
	static void AmbientSoundSplinePostSignificance( FManagedObjectInfo* ObjectInfo, float OldSignificance, float NewSignificance, bool bFinal );

	/** Helper functions for getting location and setting tick rates */
	FORCEINLINE static FVector GetObjectLocation( FManagedObjectInfo* objInfo ){ return GetObjectLocation( objInfo->GetObject() ); }
	static FVector GetObjectLocation( UObject* obj );
	FORCEINLINE static void SetObjectTickRate( FManagedObjectInfo* objInfo, float newTickRate ){ SetObjectTickRate( objInfo->GetObject(), newTickRate ); }
	static void SetObjectTickRate( UObject* obj, float newTickRate );
	FORCEINLINE static void SetObjectTicks( FManagedObjectInfo* objInfo, bool newTicks ){ SetObjectTicks( objInfo->GetObject(), newTicks ); }
	static void SetObjectTicks( UObject* obj, bool newTicks );

	/* Data about the different distance levels */
	TArray< FGainSignificanceData > mGainSignificanceData;

	/** List of factories that were significant last time we checked */
	UPROPERTY()
	TArray< class AFGBuildableFactory* > mPreviousSignificantFactories;

	/** List of conveyor belts that were significant last time we checked */
	UPROPERTY()
	TArray< class AFGBuildableConveyorBelt* > mPreviousSignificantConveyorBelts;

	/** How often we should sort the factories/conveyors */
	float mSortTimerTime;

	/** Current value of sorting timer */
	float mSortTimer;
};
