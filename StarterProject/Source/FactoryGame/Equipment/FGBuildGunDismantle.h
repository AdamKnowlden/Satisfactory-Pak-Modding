// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Equipment/FGBuildGun.h"
#include "FGInventoryComponent.h"
#include "FGBuildGunDismantle.generated.h"


/**
 * Build guns dismantle state.
 */
UCLASS()
class FACTORYGAME_API UFGBuildGunStateDismantle : public UFGBuildGunState
{
	GENERATED_BODY()

public:
	// Begin UFGBuildGunState
	virtual void BeginState_Implementation() override;
	virtual void EndState_Implementation() override;
	virtual void TickState_Implementation( float deltaTime ) override;
	virtual void PrimaryFire_Implementation() override;
	virtual void SecondaryFire_Implementation() override;
	// End UFGBuildGunState

	/** Gets the selected actor; null if none selected. */
	UFUNCTION( BlueprintPure, Category = "BuildGunState|Dismantle" )
	class AActor* GetSelectedActor() const;

	/** Can the selected actor be dismantled (Only call this on the server). */
	UFUNCTION( BlueprintPure, Category = "BuildGunState|Dismantle" )
	bool CanDismantle() const;

	/** What do we get by dismantling the actor (Only call this on the server). */
	UFUNCTION( BlueprintCallable, Category = "BuildGunState|Dismantle" )
	TArray< FInventoryStack > GetDismantleRefund() const;

	/** returns true if build gun delay is ok to start */
	virtual bool CanBeginBuildGunDelay() const override;

	/** Overriden for feedback purposes */	
	virtual void BeginBuildGunDelay() override;

	/** Overriden for feedback purposes */
	virtual void ResetBuildGunDelay() override;

	/** Give blueprint a chance to do effect when stopping dismantle */
	UFUNCTION( BlueprintImplementableEvent,Category = "BuildGunState" )
	void OnStopDismantle();

	/** Give blueprint a chance to do effect when starting dismantle */
	UFUNCTION( BlueprintImplementableEvent, Category = "BuildGunState" )
	void OnStartDismantle();

private:
	/** Set the selected actor (Simulated on client). */
	void SetSelectedActor( class AActor* selected );

	/** Client selects actor, then tells the server what to dismantle. This function does that! */
	UFUNCTION( Server, Reliable, WithValidation )
	void Server_DismantleActor( class AActor* actorToDismantle );

private:
	/** The actor to dismantle (simulated locally on client). */
	UPROPERTY()
	class AActor* mSelectedActor;
};
