// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGSignificanceInterface.h"
#include "Buildables/FGBuildable.h"
#include "FGBuildableStandaloneSign.generated.h"

/**
 * Class for the creating of placeable signs with modifiable hologram mesh icon and text
 */


USTRUCT( BlueprintType )
struct FStandaloneSignData
{
	GENERATED_BODY()

	FStandaloneSignData() :
		TextColorIndex( 0 ),
		BackgroundColorIndex( 2 ),
		SignText( "SIGN TEXT" ),
		TextMeshScale( 1.f ),
		TextOffsetZ( 0.f )
	{}
	
	/** Index of the selected color for the text from the FGSignSettings color data array  */
	UPROPERTY( SaveGame, BlueprintReadWrite, Category = "StandaloneSign" )
	int32 TextColorIndex;

	/** Index of the selected color for the background from the FGSignSettings color data array  */
	UPROPERTY( SaveGame, BlueprintReadWrite, Category = "StandaloneSign" )
	int32 BackgroundColorIndex;

	/** Text to be displayed on the sign */
	UPROPERTY( SaveGame, BlueprintReadWrite, Category = "StandaloneSign" )
	FString SignText;

	/** Scale of the text mesh */
	UPROPERTY( SaveGame, BlueprintReadWrite, Category = "StandaloneSign" )
	float TextMeshScale;

	UPROPERTY( SaveGame, BlueprintReadWrite, Category = "StandaloneSign" )
	float TextOffsetZ;

};

UCLASS( Abstract )
class FACTORYGAME_API AFGBuildableStandaloneSign : public AFGBuildable, public IFGSignificanceInterface
{
	GENERATED_BODY()
	
public:
	AFGBuildableStandaloneSign();

	// Replication
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	// Begin Actor Interface 
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason );
	// End Actor Interface

	// Begin Significance Interface Implementation
	virtual void GainedSignificance_Implementation() override;
	virtual void LostSignificance_Implementation() override;
	// End  Significance Interface Implementation

	// Called by server or client to update sign data
	UFUNCTION( BlueprintCallable, Category = "StandaloneSign" )
	void SetSignData( FStandaloneSignData signData, bool bUpdate = true );


	/** Updates all sign elements with currently set sign data */
	void UpdateSignElements();

	/** Updates background material on static mesh instance */
	void UpdateBackgroundMaterial();

	/** Force an update on the text render component */
	void UpdateSignText();

	UFUNCTION( BlueprintPure, Category = "StandaloneSign" )
	const FStandaloneSignData& GetSignData();

	// Begin Widget Getter Functions
	UFUNCTION( BlueprintPure, Category = "StandaloneSign" )
	FORCEINLINE float GetMinTextScale() const { return mMinTextScale; }

	UFUNCTION( BlueprintPure, Category = "StandaloneSign" )
	FORCEINLINE float GetMaxTextScale() const { return mMaxTextScale; }

	UFUNCTION( BlueprintPure, Category = "StandaloneSign" )
	FORCEINLINE float GetMinTextOffsetZ() const { return mMinTextOffsetZ; }

	UFUNCTION( BlueprintPure, Category = "StandaloneSign" )
	FORCEINLINE float GetMaxTextOffsetZ() const { return mMaxTextOffsetZ; }

	UFUNCTION( BlueprintPure, Category = "StandaloneSign" )
	FORCEINLINE float GetTextOffsetZ() const { return mSignData.TextOffsetZ; }

	UFUNCTION( BlueprintPure, Category = "StandaloneSign" )
	float GetCurrentNormalizedTextScale( );

	UFUNCTION( BlueprintPure, Category = "StandaloneSign" )
	float GetCurrentNormalizedTextOffsetZ();

	UFUNCTION( BlueprintPure, Category = "StandaloneSign" )
	float GetTextScaleFromNormalizedValue( float value );
	// End Widget Getter Functions

protected:
	/** Update sign components on replication */
	UFUNCTION()
	void OnRep_SignData();


protected:
	/** Root Component that holds all the sign elements, text, mesh etc. */
	UPROPERTY( VisibleAnywhere, Category = "StandaloneSign" )
	USceneComponent* mSignDisplayRoot;

	/** Root component that parents the text objects */
	UPROPERTY( VisibleAnywhere, Category = "StandaloneSign" )
	USceneComponent* mTextDisplayRoot;

	UPROPERTY( VisibleAnywhere, Category = "StandaloneSign" )
	class UFGColoredInstanceMeshProxy* mMeshComponentProxy;

	/** Front text render component*/
	UPROPERTY( VisibleAnywhere,  Category = "StandaloneSign" )
	class UTextRenderComponent* mTextRenderComponentFront;

	/** Back text render component */
	UPROPERTY( VisibleAnywhere, Category = "StandaloneSign" )
	class UTextRenderComponent* mTextRenderComponentBack;

	/** Particle system visual */
	UPROPERTY( VisibleAnywhere,  Category = "StandaloneSign" )
	class UParticleSystemComponent* mHologramParticleComponent;

	/** Distance at which to gain significance */
	UPROPERTY( EditDefaultsOnly, Category = "Significance" )
	float mGainSignificanceDistance;

	/** Minimum Text Z offset */
	UPROPERTY( EditDefaultsOnly, Category = "StandaloneSign" )
	float mMinTextOffsetZ;

	/** Maximum Text Z offset*/
	UPROPERTY( EditDefaultsOnly, Category = "StandaloneSign" )
	float mMaxTextOffsetZ;

	/** Minimum Text scale multiplier */
	UPROPERTY( EditDefaultsOnly, Category = "StandaloneSign" )
	float mMinTextScale;

	/** MAximum text scale multiplier*/
	UPROPERTY( EditDefaultsOnly, Category = "StandaloneSign" )
	float mMaxTextScale;

private:
	UPROPERTY( SaveGame, ReplicatedUsing=OnRep_SignData )
	FStandaloneSignData mSignData;
	
};
