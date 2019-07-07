#pragma once

#include "UObject/Interface.h"
#include "FGAggroTargetInterface.generated.h"

/**
* For blueprint support of the interface, we will never add anything to it, just use it to
* have a UCLASS to be able to access
*/
UINTERFACE( Blueprintable )
class UFGAggroTargetInterface : public UInterface
{
	GENERATED_BODY()
};

/**
* @brief Interface for everything that can be in the inventory
*/
class IFGAggroTargetInterface
{
	GENERATED_IINTERFACE_BODY()

	UFUNCTION( BlueprintNativeEvent, Category = "Aggro" )
	bool ShouldAutoregisterAsTargetable() const;

	UFUNCTION(BlueprintNativeEvent,Category="Aggro")
	void RegisterIncomingAttacker( class AFGEnemyController* forController );

	UFUNCTION( BlueprintNativeEvent, Category = "Aggro" )
	void UnregisterAttacker( class AFGEnemyController* forController );

	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "Aggro" )
	AActor* GetActor();

	/**
	 * Primitive component that we will try to attack
	 */
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "Aggro" )
	class UPrimitiveComponent* GetTargetComponent();

	UFUNCTION( BlueprintNativeEvent, Category = "Aggro" )
	float GetEnemyTargetDesirability( class AFGEnemyController* forController );

	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "Aggro" )
	bool IsAlive() const;

	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "Aggro" )
	FVector GetAttackLocation() const;


	/*virtual float GettAttackRangeOffset() = 0;

	UFUNCTION()
	virtual void RegisterAttacker( class AFGEnemyController* forController ) = 0;

	UFUNCTION()
	virtual void UnregisterIncomingAttacker( class AFGEnemyController* forController ) = 0;

	virtual bool IsDynamic() = 0;*/
};
