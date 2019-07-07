// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "AI/FGAttack.h"
#include "FGAttackRanged.generated.h"

/**
 * 
 */
UCLASS( Blueprintable )
class FACTORYGAME_API UFGAttackRanged : public UFGAttack
{
	GENERATED_BODY()
public:
	/**
	/ Handles the attack logic, differs depending on type of attack ( ex melee, ranged etc )
	*/
	virtual void PerformAttack( TScriptInterface< IFGAggroTargetInterface >	aggroTarget, class AFGEnemy* sourceActor ) override;

	/** Has the actual logic for spawning projectiles ( so that we can override in blueprint */
	UFUNCTION( BlueprintNativeEvent, Category = "Projectile" ) 
	void SpawnProjectile( AActor* targetActor, class AFGEnemy* sourceActor );
public:
	UPROPERTY( EditDefaultsOnly, Category = "Projectile" )
	TSubclassOf< class AFGProjectile > mProjectileClass;
};
