#pragma once

#include "FGEquipmentDescriptor.h"
#include "FGConsumableDescriptor.generated.h"

UCLASS()
class UFGConsumableDescriptor : public UFGEquipmentDescriptor
{
	GENERATED_BODY()
public:
	/** ctor */
	UFGConsumableDescriptor();

	/**
	 * NEVER EVER change any state of this object in this function, it's the default object.
	 *
	 * @param player - the player consuming the consumeable
	 */
	UFUNCTION(BlueprintImplementableEvent,Category="Consumeable")
	void ConsumedBy( class AFGCharacterPlayer* player ) const;
	
	/** Sound played when consuming */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Sound" )
	class UAkAudioEvent* mConsumeEvent;

	/** The skeletal mesh we want for representing the resource when they are in the production line.
	* @return The items mesh; a default mesh if the item has no mesh specified, nullptr if inClass is nullptr. */
	UFUNCTION( BlueprintPure, Category = "Item" )
	static class USkeletalMesh* GetFPOverrideMesh( TSubclassOf< UFGConsumableDescriptor > inClass );

	/** The static mesh we want for representing the item when viewed as thir person.
	* @return The items mesh; a default mesh if the item has no mesh specified, nullptr if inClass is nullptr. */
	UFUNCTION( BlueprintPure, Category = "Item" )
	static class UStaticMesh* GetTPOverrideMesh( TSubclassOf< UFGConsumableDescriptor > inClass );
protected:
	/** Custom scale of mesh in hands */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Consumeable" )
	float mCustomHandsMeshScale;

	/** Custom local rotaion of mesh in hands */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Consumeable" )
	FRotator mCustomRotation;

	/** Custom local location of mesh in hands */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Consumeable" )
	FVector mCustomLocation;

	/** The skeletal  mesh we want for representing the resource when it is in first person. */
	UPROPERTY( EditDefaultsOnly, Category = "Consumeable" )
	class USkeletalMesh* mFPOverrideMesh;

	/** The static mesh we want for representing the resource when it is in third person. */
	UPROPERTY( EditDefaultsOnly, Category = "Consumeable" )
	class UStaticMesh* mTPOverrideMesh;
};
