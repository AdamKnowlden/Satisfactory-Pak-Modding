// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "FGCreatureController.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGCreatureController : public AAIController
{
	GENERATED_BODY()
public:	
	/** ctor */
	AFGCreatureController( const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get() );

	/** toggles if the ai should be active  */
	UFUNCTION( BlueprintCallable, Category = "AI|Optimization" )
	void SetEnabled( bool enabled );

	/** Started panicking for some reason */
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "AI" )
	void StartPanic();

	virtual void StartPanic_Implementation();

	/** now chilling tha grill */
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "AI" )
	void StopPanic();

	UFUNCTION()
	virtual void OnTargetPerceptionUpdated(  AActor* inActor,  struct FAIStimulus Stimulus );
};
