#pragma once

#include "Online.h"
#include "FGInputLibrary.h"
#include "GameFramework/PlayerController.h"
#include "FGPlayerControllerBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnInputChanged );

UCLASS()
class AFGPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()
public:
	/** Ctor */
	AFGPlayerControllerBase();

	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	// End AActor interface

	// Begin APlayerController interface
	virtual void ClientRestart_Implementation( APawn* newPawn ) override;
	// End APlayerController interface

	UFUNCTION( BlueprintPure, Category = "Input" )
	FORCEINLINE bool GetIsUsingGamepad(){ return mIsUsingGamepad; }

	UFUNCTION( BlueprintCallable, Category = "Input" )
	void SetIsUsingGamepad( bool newIsUsingGamepad );

	/**
	 * Called on Server and Owning client when the character we controlled died
	 * 
	 * @param character - the character that died
	 **/ 
	virtual void OnControlledCharacterDied( class AFGCharacterBase* character );

	/**
	* Called on Server and Owning client when the character we controlled has been revived
	*
	* @param character - the character that was revived
	**/
	virtual void OnControlledCharacterRevived( class AFGCharacterBase* character );

	/** Called when we rebind any key */
	UPROPERTY( BlueprintAssignable )
	FOnInputChanged OnInputChanged;

	/** Exposing flushPressedKeys to BP */
	UFUNCTION( BlueprintCallable, Category = "Input" )
	void FlushPressedKeys();

	/** Used for rebinding keys */
	UFUNCTION( BlueprintCallable, Category = "Input" )
	bool RebindActionKey( FFGKeyMapping newKeyMapping );

	/** Removes custom bindings and restores to default */
	UFUNCTION( BlueprintCallable, Category = "Input" )
	void ResetInputBindings();

	/** Inject the input that was rebinded and remove old default */
	void UpdatePlayerInput();

	/** Sets mouse sensitivity */
	UFUNCTION( BlueprintCallable, Category = "Input" )
	void SetMouseSensitivity( float newSense );

	/** Get current sensitivity */
	UFUNCTION( BlueprintPure, Category = "Input" )
	float GetMouseSensitivity();

	/** Get default value for mouse sensitivity */
	UFUNCTION( BlueprintPure, Category = "Input" )
	float GetDefaultMouseSensitivity();

	/** Returns readable name for an action */
	UFUNCTION( BlueprintPure, Category = "Input" )
	FText GetKeyNameForAction( FName inAction, bool getGamepadKey );

	UFUNCTION( BlueprintNativeEvent, Category="Online|Presence") 
	FString GetPresenceString() const;

	/** Set CurrentNetSpeed to the lower of its current value and Cap, can update during the game to the new value if server updates it's bandwith due to options */
	UFUNCTION(Reliable, Client)
	void Client_UpdateCappedBandwidth(int32 cap);

	/** Set CurrentNetSpeed to the lower of its current value and Cap, can update during the game to the new value if client updates it's bandwidth */
	UFUNCTION(Reliable, Server, WithValidation)
	void Server_UpdateCappedBandwidth(int32 cap);

	// DEBUG FUNCTIONS TO BE REMOVED AFTER https://questions.satisfactorygame.com/6612/frame-drops-every-few-minutes-constant-freezes?show=17767#c17767 is closed
	UFUNCTION( exec )
	void SetPresenceEnabled( bool enabled );

	UFUNCTION( exec )
	void SetSessionEnabled( bool enabled );
	// END DEBUG FUNCTIONS

protected:
	/** Used to discard any input when we are dead */
	UFUNCTION()
	void DiscardInput();

private:
	/** 
	 * Enables or disables the input for all ActionBindings except for the ones specified in mAllowedInputWhenDead.
	 * Does nothing if the state doesn't change
	 *
	 * @note Call on owning client only
	 *
	 * @param enable - if true, then we enable our input, false we disable it
	 */
	void EnablePlayerInput( bool enable );
private:
	/** Setup the input component that filters out the input that's used when dead */
	void InitDeathInput();

private:
	/** The input component used when we want to disable our input */
	UPROPERTY()
	class UInputComponent* mDisableInputComponent;

	/** The input component used when we want to enable our input */
	UPROPERTY()
	class UInputComponent* mEnableInputComponent;

	/** Input that's allowed when you are dead */
	UPROPERTY( EditDefaultsOnly, Category = "Input" )
	TArray<FName> mAllowedInputWhenDead;

	/** If true, the our input is enabled */
	uint8 mInputEnabled:1;

	/** Are we using gamepad? */
	bool mIsUsingGamepad;
};
