// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Creature/Enemy/FGEnemy.h"
#include "FGCrabHatcher.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGCrabHatcher : public AFGEnemy
{
	GENERATED_BODY()
public:
	// Begin AActor Interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	virtual void Tick( float deltaTime ) override;
	// End AActor Interface
	
	/** Get for mThreatNearby */
	UFUNCTION( BlueprintPure, Category = "Crab Hatcher" )
	FORCEINLINE bool GetThreatNearby() { return mThreatNearby; }

	/** Set for mThreatNearby */
	UFUNCTION( BlueprintCallable, Category = "Crab Hatcher" )
	void SetThreatNearby( bool inNearby ) { mThreatNearby = inNearby; }

	/** Set for mDidSpawnCrabs */
	UFUNCTION( BlueprintCallable, Category = "Crab Hatcher" )
	void SetDidSpawnCrabs( bool inDidSPawn ) { mDidSpawnCrabs = inDidSPawn; }

	/** Set for mAnimationLength */
	UFUNCTION( BlueprintCallable, Category = "Crab Hatcher" )
	void SetAnimationLength( float animLength ) { mAnimationLength = animLength; }

	/** Call to BP to spawn the crab babies */
	UFUNCTION( BlueprintCallable, BlueprintImplementableEvent, Category = "Crab Hatcher" )
	void SpawnCrabs();

	/** Call to BP when expansion starts */
	UFUNCTION( BlueprintImplementableEvent, Category = "Crab Hatcher" )
	void StartExpanding();
protected:
	/** Indicates if a threat is nearby */
	UPROPERTY( Replicated )
	bool mThreatNearby;

	/** Have crabs been spawned? */
	UPROPERTY( Replicated )
	bool mDidSpawnCrabs;

	/** Time enemy has been under threat */
	UPROPERTY( Replicated )
	float mThreatTimer;

	/** Time when timer reach it's end */
	UPROPERTY( EditDefaultsOnly, Category = "Crab Hatcher" )
	float mThreatTimerMax;

	/** Length of the animation to play */
	float mAnimationLength;

	bool mDidStartExpanding;
	
};
