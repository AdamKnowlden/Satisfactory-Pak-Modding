// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGSubsystem.h"
#include "BuildableColorSlotBase.h"
#include "FGSaveInterface.h"
#include "FGBuildingColorSlotStruct.h"
#include "Materials/Material.h"
#include "FGBuildableSubsystem.generated.h"

class UFGProductionIndicatorInstanceManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnBuildableConstructedGlobal, AFGBuildable*, buildable );

/** Distances where we switch tick rate */
USTRUCT( BlueprintType )
struct FDistanceBasedTickRate
{
	GENERATED_BODY()

	UPROPERTY( EditDefaultsOnly, Category = "Factory" )
	float Distance;
	
	UPROPERTY( EditDefaultsOnly, Category = "Factory" )
	float TickRate;
};

/**
 * Subsystem responsible for spawning and maintaining buildables.
 * This enables and disables ticks on the buildable.
 */
UCLASS()
class FACTORYGAME_API AFGBuildableSubsystem : public AFGSubsystem, public IFGSaveInterface
{
	GENERATED_BODY()
public:
	AFGBuildableSubsystem();

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
	virtual void BeginPlay() override;
	virtual void Tick( float dt ) override;
	// End AActor interface

	/** Get the buildable subsystem in the current world, can be nullptr, e.g. on game ending (destroy) or game startup. */
	static AFGBuildableSubsystem* Get( UWorld* world );

	/** Get the buildable subsystem in the current world, can be nullptr, e.g. on game ending (destroy) or game startup. */
	UFUNCTION( BlueprintPure, Category = "Buildable Subsystem", DisplayName = "GetBuildableSubsystem", meta = ( DefaultToSelf = "WorldContext" ) )
	static AFGBuildableSubsystem* Get( UObject* worldContext );

	/**
	 * Spawn a buildable at a specified location, you need to call FinishSpawning on the buildable after this to finalize the spawning.
	 *
	 * @param inClass - The class we want to spawn (need to be valid).
	 * @param inTransform - where we want to spawn the buildable.
	 */
	class AFGBuildable* BeginSpawnBuildable( TSubclassOf< class AFGBuildable > inClass, const FTransform& inTransform );

	/** Adds a buildable to the buildable array. */
	void AddBuildable( class AFGBuildable* buildable );
	/** Remove the buildable from the subsystem, this is called by the buildable when destroyed. */
	void RemoveBuildable( class AFGBuildable* buildable );

	/** Get all buildables of the supplied type. */
	UFUNCTION( BlueprintCallable, Category = "Buildable Subsystem" )
	void GetTypedBuildable( TSubclassOf< class AFGBuildable > inClass, TArray< class AFGBuildable* >& out_buildables ) const;

	/** Get all buildables of the supplied type. */
	template< typename T >
	void GetTypedBuildable( TArray< T* >& out_buildables ) const;

	/** Starts replaying of build effects in the build order of the buildings. */
	UFUNCTION()
	void ReplayBuildingEffects();

	/** Debug */
	virtual void DisplayDebug( class UCanvas* canvas, const class FDebugDisplayInfo& debugDisplay, float& YL, float& YPos ) override;
	void DebugEnableInstancing( bool enabled );
	void DebugGetFactoryActors( TArray< AActor* >& out_actors );

protected:
	// Find and return a local player
	class AFGPlayerController* GetLocalPlayerController() const;

	/** Distance from a location to closest point of buildables AABB */
	float GetDistanceSqToBoundingBox( const FVector& point,  class AFGBuildable* buildable ) const;
private:
	void UpdateReplayEffects( float dt );

	void AddBuildableMeshInstances( class AFGBuildable* buildable );

public:
	/** Distance used when calculating if a location is near a base */
	UPROPERTY( EditDefaultsOnly, Category = "Factory" )
	float mDistanceConsideredClose;

	/** How many factories need to be within the close range for it to count as if a given location is near a base */
	UPROPERTY( EditDefaultsOnly, Category = "Factory" )
	int32 mNumFactoriesNeededForCloseCheck;

	/** Broadcast when a buildable or decor has been constructed. Regardless of who built it */
	UPROPERTY( BlueprintAssignable, Category = "Build", DisplayName = "OnBuildableConstructedGlobal" )
	FOnBuildableConstructedGlobal BuildableConstructedGlobalDelegate;

	UFUNCTION( BlueprintCallable, Category = "Customization" )
	void setColorSlotPrimary( uint8 index, FColor color );
	UFUNCTION( BlueprintCallable, Category = "Customization" )
	void setColorSlotSecondary( uint8 index, FColor color );

	UFUNCTION( BlueprintCallable, Category = "Customization" )
	FColor getColorSlotPrimary( uint8 index );
	UFUNCTION( BlueprintCallable, Category = "Customization" )
	FColor getColorSlotSecondary( uint8 index );

	UFUNCTION( BlueprintCallable, Category = "Customization" )
	FLinearColor getColorSlotPrimaryLinear( uint8 index );
	UFUNCTION( BlueprintCallable, Category = "Customization" )
	FLinearColor getColorSlotSecondaryLinear( uint8 index );


	UMaterial* GetFactoryDefaultMaterial()
	{
		return mDefaultFactoryMaterial;
	}

	/**
	 * Used by UFGColoredInstanceMeshProxy to get an instance if it's not already been assigned
	 */
	class UFGColoredInstanceManager* GetColoredInstanceManager( class UFGColoredInstanceMeshProxy* proxy );

private:
	/** List of all buildables. */
	UPROPERTY()
	TArray< class AFGBuildable* > mBuildables;

	/** Hierarchical instances for the factory buildings. */
	UPROPERTY()
	AActor* mBuildableInstancesActor;
	// MODDING EDIT
	//UPROPERTY()
	//TMap< class UStaticMesh*, class UProxyHierarchicalInstancedStaticMeshComponent* > mBuildableMeshInstances;

	/**/
	UPROPERTY()
	UFGProductionIndicatorInstanceManager* mProductionIndicatorInstanceManager = nullptr;

	/**/
	UPROPERTY()
	TMap< class UStaticMesh*, class UFGColoredInstanceManager* > mColoredInstances;


	bool mColorSlotsAreDirty = false;
	UPROPERTY( SaveGame, EditDefaultsOnly, Category = "Customization" )
	FColor mColorSlotsPrimary[ BUILDABLE_COLORS_MAX_SLOTS ];

	UPROPERTY( SaveGame, EditDefaultsOnly,  Category = "Customization" )
	FColor mColorSlotsSecondary[ BUILDABLE_COLORS_MAX_SLOTS ];

	uint8 mColorSlotDirty[ BUILDABLE_COLORS_MAX_SLOTS ];




	/** Maximum number of buildables that we consider their optimization level during the same frame */
	int32 mMaxConsideredBuildables;

	/** Last buildable that was considered */
	int32 mLastConsideredBuildableIdx;

	/** Distance we disable buildables ticking on */
	float mDisabledBuildableTickDistance;

	/** Information about what distances we change the tick rate on */
	UPROPERTY( EditDefaultsOnly, Category = "Factory" )
	TArray< FDistanceBasedTickRate > mDistanceBasedTickRate;

	/** Is factory optimization ( tick control ) active */
	UPROPERTY( EditDefaultsOnly, Category = "Factory" )
	bool mFactoryOptimizationEnabled;

	/** How much time can differ between each build effect */
	UPROPERTY( EditDefaultsOnly, Category = "Replay" )
	float mReplayEffecTimeDilation;

	/** How much time between each build effect when replaying the whole factory */
	UPROPERTY( EditDefaultsOnly, Category = "Replay" )
	float mReplayEffectTimerDefault;

	/** Timer used for the replay effect */
	float mReplayEffectTimer;

	/** Array with all the buildings that should replay their effect */
	TArray< AFGBuildable* > mReplayEffectArray;

	/**used for comparing and finding materials of factory meshes*/
	UPROPERTY( EditDefaultsOnly )
	UMaterial* mDefaultFactoryMaterial;


	enum class EPropagateColorState : uint8
	{
		SettingTransitionColor,
		SettingHalfRealColor,
		SettingRealColor,
		SettingColorOnly,
		Done
	};

	EPropagateColorState mColorPropState = EPropagateColorState::Done;
	int32 mColorPropagationProgressIndex = 0;
	float mColorPropagationTimer = 0;
	/** Array with all the buildings that should replay their effect */
	TArray< AFGBuildable* > mColorPropagationArray;
	bool IsBasedOn( const UMaterialInterface* instance, const UMaterial* base );
public:
};

template< typename T >
void AFGBuildableSubsystem::GetTypedBuildable( TArray< T* >& out_buildables ) const
{
	for( auto buildable : mBuildables )
	{
		T* specificBuildable = Cast< T >( buildable );
		if( IsValid( specificBuildable ) )
		{
			out_buildables.Add( specificBuildable );
		}
	}
}
