// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGCharacterAnimInstance.h"
#include "FGAnimPlayer.generated.h"

UENUM( BlueprintType )
enum class EArmEquipment : uint8
{
	AE_None,
	AE_ChainSaw,
	AE_RebarGun,
	AE_BuildGun,
	AE_Nobelisk,
	AE_ResourceScanner,
	AE_Rifle,
	AE_ColorGun,
	AE_OneHandEquipment,
	AE_Consumables,
	AE_ObjectScanner,
	AE_PortableMiner,
	AE_StunSpear,
	AE_ShockShank,
	AE_ResourceCollector	
};

UENUM( BlueprintType )
enum class EBackEquipment : uint8
{
	BE_None,
	BE_Jetpack
};

USTRUCT( BlueprintType )
struct FArmEquipmentData
{
	GENERATED_BODY()

	/**  */
	UPROPERTY( EditDefaultsOnly, Category = "Anim Player" )
	TSubclassOf< class AFGEquipment > EquipmentClass;

	/** */
	UPROPERTY( EditDefaultsOnly, Category = "Anim Player" )
	TSubclassOf< class AFGEquipmentAttachment > AttachmentClass;

	/** */
	UPROPERTY( EditDefaultsOnly, Category = "Anim Player" )
	EArmEquipment ArmEnum;
};


USTRUCT( BlueprintType )
struct FBackEquipmentData
{
	GENERATED_BODY()

	/**  */
	UPROPERTY( EditDefaultsOnly, Category = "Anim Player" )
	TSubclassOf< class AFGEquipment > EquipmentClass;

	/** */
	UPROPERTY( EditDefaultsOnly, Category = "Anim Player" )
	TSubclassOf< class AFGEquipmentAttachment > AttachmentClass;

	/** */
	UPROPERTY( EditDefaultsOnly, Category = "Anim Player" )
	EBackEquipment BackEnum;
};

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGAnimPlayer : public UFGCharacterAnimInstance
{
	GENERATED_BODY()
public:	
	/** Caching stuff */
	virtual void NativeUpdateAnimation( float DeltaSeconds ) override;

	/** Sets value for arm slot */
	void GetArmSlotData();

	/** Sets value for back slot */
	void GetBackSlotData();
public: 
	/** Is first or third person mesh? */
	UPROPERTY( EditDefaultsOnly, Category = "Anim Player" )
	bool mIsFirstPerson; 

	/** Saved value of arm equipment */
	UPROPERTY( BlueprintReadOnly, Category = "Anim Player" )
	EArmEquipment mArmSlotType; 

	/** Saved value of back equipment */
	UPROPERTY( BlueprintReadOnly, Category = "Anim Player" )
	EBackEquipment mBacklotType;

	/** Character this anim belongs to */
	UPROPERTY( BlueprintReadOnly, Category = "Anim Player" )
	class AFGCharacterPlayer* mCharacter;
	
	/** Array to fill with data about arm slots */
	UPROPERTY( EditDefaultsOnly, Category = "Anim Player" )
	TArray< FArmEquipmentData > mArmSlotData;

	/** Array to fill with data about back slots */
	UPROPERTY( EditDefaultsOnly, Category = "Anim Player" )
	TArray< FBackEquipmentData > mBackSlotData;
};
