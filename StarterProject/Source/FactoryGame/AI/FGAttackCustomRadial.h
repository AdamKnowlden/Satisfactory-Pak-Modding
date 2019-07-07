// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AI/FGAttack.h"
#include "FGAttackCustomRadial.generated.h"

/**
 * 
 */
UCLASS( Blueprintable )
class FACTORYGAME_API UFGAttackCustomRadial : public UFGAttack
{
	GENERATED_BODY()
public:
	virtual void PerformAttack( TScriptInterface< IFGAggroTargetInterface >	aggroTarget, class AFGEnemy* sourceActor ) override;
};
