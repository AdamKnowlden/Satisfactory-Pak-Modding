#pragma once

#include "GameFramework/GameUserSettings.h"
#include "GameFramework/PlayerInput.h"
#include "FGInputLibrary.h"
#include "FGGameUserSettings.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FArachnophobiaModeChangedDelegate, bool, isArachnophobiaMode );

/**
 * Name and value combination for the options with audio
 */
USTRUCT()
struct FAudioVolumeMap
{
	GENERATED_BODY()
	
	/** Name of the RTPC that this maps to */
	UPROPERTY()
	FString Name;

	/** The stored value of the RTPC */
	UPROPERTY()
	float Value;
};

UCLASS(BlueprintType)
class UFGGameUserSettings : public UGameUserSettings
{
	GENERATED_BODY()
public:

	//~Begin GameUserSettings interface
	virtual void ApplyNonResolutionSettings() override;
	virtual void SetToDefaults() override; // Only video settings
	virtual void ResetToCurrentSettings() override; // Only video settings
	//~End GameUserSettings interfaces

	/** Reset audio settings to default settings */
	UFUNCTION( BlueprintCallable, Category = Settings )
	virtual void SetAudioToDefaults();

	/** Reset audio settings to current settings */
	UFUNCTION( BlueprintCallable, Category = Settings )
	virtual void ResetAudioToCurrentSettings();

	/** Returns the game local machine settings (resolution, windowing mode, scalability settings, etc...) */
	UFUNCTION( BlueprintCallable, Category = Settings )
	static UFGGameUserSettings* GetFGGameUserSettings();

	/** Set the audio volume for a specified channel */
	UFUNCTION(BlueprintCallable,Category="Settings")
	void SetAudioVolume( FString name, float value );

	/** Gets the audio volumes for all channels */
	UFUNCTION( BlueprintPure, Category = "Settings" )
	float GetAudioVolume( FString name );

	/** Set Arachnophobia Mode */
	UFUNCTION( BlueprintCallable, Category = "Settings" )
	void SetArachnophobiaMode( bool newArachnophobiaMode );

	/** Get Arachnophobia Mode */
	UFUNCTION( BlueprintPure, Category = "Settings" )
	FORCEINLINE bool GetArachnophobiaMode() { return mIsArachnophobiaMode; }

	/** Set Inverty Y mode */
	UFUNCTION( BlueprintCallable, Category = "Settings" )
	void SetInvertedLook( bool newInvertLook );

	/** Get Inverty Y mode */
	UFUNCTION( BlueprintPure, Category = "Settings" )
	FORCEINLINE bool GetInvertedLook() { return mInvertY; }

	/** Set HoldToSprint */
	UFUNCTION( BlueprintCallable, Category = "Settings" )
	void SetHoldToSprint( bool newHoldToSprint );

	/** Get HoldToSprint */
	UFUNCTION( BlueprintPure, Category = "Settings" )
	FORCEINLINE bool GetHoldToSprint() { return mHoldToSprint; }

	/** Set AutoSortInventory */
	UFUNCTION( BlueprintCallable, Category = "Settings" )
	void SetAutoSortInventory( bool shouldAutoSort );

	/** Get whether inventory should auto sort */
	UFUNCTION( BlueprintPure, Category = "Settings" )
	FORCEINLINE bool GetAutoSortInventory() { return mAutoSortInventory; }

	/** Set FOV */
	UFUNCTION( BlueprintCallable, Category = "Settings" )
	void SetFOV( int32 newFOV );

	/** Get FOV */
	UFUNCTION( BlueprintPure, Category = "Settings" )
	FORCEINLINE int32 GetFOV() { return mFOV; }

	/** Sets the user setting for motion blur */
	UFUNCTION( BlueprintCallable, Category = "Settings" )
	void SetMotionBlurEnabled( bool enable );

	/** Returns the user setting for motion blur */
	UFUNCTION( BlueprintPure, Category = "Settings" )
	bool IsMotionBlurEnabled();

	/** Checks if the motion blur user setting is different from current system setting */
	UFUNCTION( BlueprintPure, Category = "Settings" )
	bool IsMotionBlurDirty() const;

	/** Returns the default quality setting value */
	UFUNCTION( BlueprintPure, Category = "Settings" )
	int32 GetDefaultQualitySetting( FString settingName );

	/** Sets the user setting for network quality */
	UFUNCTION( BlueprintCallable, Category = "Settings" )
	void SetNeworkQuality( int32 newNetworkQuality );

	/** Returns the user setting for network quality */
	UFUNCTION( BlueprintPure, Category = "Settings" )
	FORCEINLINE int32 GetNeworkQuality() { return mNetworkQuality;  }

	/** Update network values in config files */
	void RefreshNetworkQualityValues();

	/** Is the provided setting using a custom quality setting  */
	UFUNCTION( BlueprintPure, Category = "Settings" )
	bool IsUsingCustomQualitySetting( FString settingName );

	/** Is post process using a custom setting  */
	UFUNCTION( BlueprintPure, Category = "Settings" )
	bool IsPostProcessUsingCustomSettings();

	// MODDING EDIT: Does not override error
	//virtual void SetPostProcessingQuality( int32 Value ) override;

	/** Update the custom post process settings like motion blur etc. */
	UFUNCTION( BlueprintCallable, Category = "Settings" )
	void UpdatePostProcessSettings();

	/** Get custom bindings */
	UFUNCTION( BlueprintPure, Category = "Settings" )
	FORCEINLINE TArray< struct FFGKeyMapping > GetKeyMappings() { return mCustomKeyMappings; }

	/** Add a new custom mapping */
	void AddCustomActionMapping( FFGKeyMapping newMapping );

	/** Clears array of custom mappings */
	void RemoveAllCustomActionMappings();

	/** Get mHeadBobScale */
	UFUNCTION( BlueprintPure, Category = "Settings" )
	FORCEINLINE float GetHeadBobScale() { return mHeadBobScale; }

	/** Set mHeadBobScale */
	UFUNCTION( BlueprintCallable, Category = "Settings" )
	void SetHeadBobScale( float newHeadBobScale );

	UFUNCTION(BlueprintPure, Category = "Settings")
	FORCEINLINE bool GetAnalyticsDisabled() { return mAnalyticsDisabled; }

	// MODDING EDIT
	///** Updates the GameUserSettings for analytics and updates the analytics to respond to this change. */
	//UFUNCTION( BlueprintCallable, Category = "Settings" )
	//void SetAnalyticsDisabled( bool isDisabled, UAnalyticsService* analyticsService );

private:
	void UpdateFoliageQualityChanges();
public:
	/** Called when arachnophobia mode is changed */
	UPROPERTY( BlueprintAssignable, Category = "Arachnophobia", DisplayName = "OnArachnophobiaModeChanged" )
	FArachnophobiaModeChangedDelegate OnArachnophobiaModeChangedDelegate;

protected:
	/** Audio volumes for the options */
	UPROPERTY(Config)
	TArray<FAudioVolumeMap> mAudioVolumes;

	/** When true, arachnid-like creatures are replaced with cats. */
	UPROPERTY(Config)
	bool mIsArachnophobiaMode;

	/** Sets the Look-axis to inverted */
	UPROPERTY( Config ) 
	bool mInvertY;

	/** Sets Field of View */
	UPROPERTY( Config )
	int32 mFOV;

	/** Motion blur quality. 0 = off */
	UPROPERTY( Config )
	int32 mMotionBlurQuality;

	/** True means old-school hold down key to sprint, false = toggle sprint by pressing */
	UPROPERTY( Config )
	bool mHoldToSprint;

	UPROPERTY( Config )
	bool mAutoSortInventory;

	/** List of remapped key Mappings */
	UPROPERTY( config, EditAnywhere, Category = "Bindings" )
	TArray< FFGKeyMapping > mCustomKeyMappings;

	/**Scale of headbobbing */
	UPROPERTY( Config )
	float mHeadBobScale;

	/** Whether the user has opted out of analytics or not */
	UPROPERTY( Config )
	bool mAnalyticsDisabled;

	/** The current network quality setting */
	UPROPERTY( Config )
	int32 mNetworkQuality;

private:
	static const FString MOTION_BLUR_QUALITY;
	static const TMap<FString, int32> NETWORK_QUALITY_CONFIG_MAPPINGS;
};
