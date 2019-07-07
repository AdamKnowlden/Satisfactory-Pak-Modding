// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once

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
	//These are for the add-on update functionality
	typedef TFunction<void( UFGSignificanceManager* )> FPreUpdateFunction;
	typedef TFunction<void( UFGSignificanceManager* )> FPostUpdateFunction;
	struct FSignificanceTypeInfo
	{
		FName Tag;
		EPostSignificanceType PostSignificanceType = EPostSignificanceType::None;

		FSignificanceFunction SignificanceFunction;
		FPostSignificanceFunction PostSignificanceFunction;
	};

	UFGSignificanceManager(); 

	//This is the function that users call as a replacement for the virtual RegisterObject which exposes only the significance type so it can be looked up
	void RegisterSignificanceObject( UObject* Object, EFGSignificanceType SignificanceType );

	virtual void Update( TArrayView<const FTransform> Viewpoints ) override;

	FGainSignificanceData GetClosestGainSignificanceData( UObject* inObject, float desiredDistance );

	/** Is the manager enabled */
	UPROPERTY( EditAnywhere, Category = "SignificanceManager" )
	bool mIsEnabled;
private:
	//Generic Significance functions
	static float GenericTickSignificance( UObject* Object, const FTransform& Viewpoint );
	static void GenericTickPostSignificance( UObject* ObjectInfo, float OldSignificance, float NewSignificance, bool bFinal );

	//Factory Significance functions
	static float FactorySignificance( UObject* Object, const FTransform& Viewpoint );
	static void FactoryPostSignificance( UObject* ObjectInfo, float OldSignificance, float NewSignificance, bool bFinal );

	//ConveyorBelt Significance functions
	static float ConveyorBeltSignificance( UObject* Object, const FTransform& Viewpoint );
	static void ConveyorBeltPostSignificance( UObject* ObjectInfo, float OldSignificance, float NewSignificance, bool bFinal );

	//Gain Significance on low distance functions
	static float LowDistanceSignificance( UObject* Object, const FTransform& Viewpoint );

	//Gain Significance on mid distance functions
	static float MidDistanceSignificance( UObject* Object, const FTransform& Viewpoint );

	//Gain Significance on high distance functions
	static float HighDistanceSignificance( UObject* Object, const FTransform& Viewpoint );

	//Gain Significance on custom distance functions
	static float CustomDistanceSignificance( UObject* Object, const FTransform& Viewpoint );

	/** Either call gain or lose significance based on value */
	static void GainSignificanceOnDistancePostSignificance( UObject* ObjectInfo, float OldSignificance, float NewSignificance, bool bFinal );

	//Ambient volume functions
	static float AudioVolumeSignificance( UObject* Object, const FTransform& Viewpoint );
	static void AudioVolumePostSignificance( UObject* ObjectInfo, float OldSignificance, float NewSignificance, bool bFinal );

	//Ambient sound spline functions
	static float AmbientSoundSplineSignificance( UObject* Object, const FTransform& Viewpoint );
	static void AmbientSoundSplinePostSignificance( UObject* ObjectInfo, float OldSignificance, float NewSignificance, bool bFinal );

	/** Helper functions for getting location and setting tick rates */
	static FVector GetObjectLocation( UObject* obj );
	static void SetObjectTickRate( UObject* obj, float NewTickRate );
	static void SetObjectTicks( UObject* obj, bool NewTicks );

	//static storage of all the significance handling data
	FSignificanceTypeInfo SignificanceTypeInfo[ ( uint8 )EFGSignificanceType::MAX ];

	/* Data about the different distance levels */
	TArray< FGainSignificanceData > mGainSignificanceData;

	/** List of factories that were significant last time we checked */
	UPROPERTY()
	TArray< class AFGBuildableFactory* > mPreviousSignificantFactories;

	/** List of conveyor belts that were significant last time we checked */
	UPROPERTY()
	TArray< class AFGBuildableConveyorBelt* > mPreviousSignificantConveyorBelts;
};
