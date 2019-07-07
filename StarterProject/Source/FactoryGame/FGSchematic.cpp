// This file has been automatically generated by the Unreal Header Implementation tool

#include "FGSchematic.h"

#if WITH_EDITOR
void UFGSchematic::PreSave( const ITargetPlatform* targetPlatform ){ Super::PreSave(targetPlatform); }
#endif 
#if WITH_EDITOR
#endif 
#if WITH_EDITOR
void UFGSchematic::UpdateAssetBundleData(){ }
#endif 
UFGSchematic::UFGSchematic(){ }
ESchematicType UFGSchematic::GetType( TSubclassOf< UFGSchematic > inClass ){ return ESchematicType(); }
FText UFGSchematic::GetSchematicDisplayName( TSubclassOf< UFGSchematic > inClass ){ return FText(); }
ESchematicCategory UFGSchematic::GetSchematicCategory( TSubclassOf< UFGSchematic > inClass ){ return ESchematicCategory(); }
TArray< FItemAmount > UFGSchematic::GetCost( TSubclassOf< UFGSchematic > inClass ){ return TArray<FItemAmount>(); }
TArray< TSubclassOf< class UFGRecipe > > UFGSchematic::GetRecipes( TSubclassOf< UFGSchematic > inClass ){ return TArray<TSubclassOf<class UFGRecipe> >(); }
int32 UFGSchematic::GetTechTier( TSubclassOf< UFGSchematic > inClass ){ return int32(); }
float UFGSchematic::GetShipTravelTimeAfterPurchase( TSubclassOf< UFGSchematic > inClass ){ return float(); }
TArray< TSubclassOf< class UFGResourceDescriptor > > UFGSchematic::GetResourceToAddToScanner( TSubclassOf< UFGSchematic > inClass ){ return TArray<TSubclassOf<class UFGResourceDescriptor> >(); }
bool UFGSchematic::GetUnlocksMap( TSubclassOf< UFGSchematic > inClass ){ return bool(); }
bool UFGSchematic::GetUnlocksInventorySlots( TSubclassOf< UFGSchematic > inClass ){ return bool(); }
int32 UFGSchematic::GetNumInventorySlotsUnlocked( TSubclassOf< UFGSchematic > inClass ){ return int32(); }
bool UFGSchematic::GetUnlocksArmEquipmentSlots( TSubclassOf< UFGSchematic > inClass ){ return bool(); }
int32 UFGSchematic::GetNumArmEquipmentSlotsUnlocked( TSubclassOf< UFGSchematic > inClass ){ return int32(); }
bool UFGSchematic::GetUnlocksBuildEfficiencyDisplay( TSubclassOf< UFGSchematic > inClass ){ return bool(); }
bool UFGSchematic::GetUnlocksBuildOverclock( TSubclassOf< UFGSchematic > inClass ){ return bool(); }
FSlateBrush UFGSchematic::GetItemIcon( TSubclassOf< UFGSchematic > inClass ){ return FSlateBrush(); }
TSubclassOf< UFGSchematic > UFGSchematic::GetDependentOnSchematic( TSubclassOf< UFGSchematic > inClass ){ return TSubclassOf<UFGSchematic>(); }
TArray< TSubclassOf< UFGSchematic > > UFGSchematic::GetAdditionalSchematicDependencies( TSubclassOf< UFGSchematic > inClass ){ return TArray<TSubclassOf<UFGSchematic> >(); }
bool UFGSchematic::IsIncludedInBuild( TSubclassOf< UFGSchematic > inClass ){ return bool(); }
void UFGSchematic::PostLoad(){ Super::PostLoad(); }
void UFGSchematic::Serialize(FArchive& ar){ Super::Serialize(ar); }
FPrimaryAssetId UFGSchematic::GetPrimaryAssetId() const{ return FPrimaryAssetId(); }
