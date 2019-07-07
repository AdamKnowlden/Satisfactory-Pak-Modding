// This file has been automatically generated by the Unreal Header Implementation tool

#include "FGBuildableManufacturer.h"

void AFGBuildableManufacturer::GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const{ }
void AFGBuildableManufacturer::PreReplication( IRepChangedPropertyTracker& ChangedPropertyTracker ){ }
AFGBuildableManufacturer::AFGBuildableManufacturer(){ }
void AFGBuildableManufacturer::BeginPlay(){ }
void AFGBuildableManufacturer::EndPlay( const EEndPlayReason::Type EndPlayReason ){ }
bool AFGBuildableManufacturer::IsConfigured() const{ return bool(); }
float AFGBuildableManufacturer::GetProductionCycleTime() const{ return float(); }
float AFGBuildableManufacturer::GetDefaultProductionCycleTime() const{ return float(); }
float AFGBuildableManufacturer::GetProductionCycleTimeForRecipe( TSubclassOf< UFGRecipe > recipe ) const{ return float(); }
float AFGBuildableManufacturer::CalcProductionCycleTimeForPotential( float potential ) const{ return float(); }
bool AFGBuildableManufacturer::MoveOrDropInputInventory( AFGCharacterPlayer* pawn ){ return bool(); }
bool AFGBuildableManufacturer::MoveOrDropOutputInventory( AFGCharacterPlayer* pawn ){ return bool(); }
void AFGBuildableManufacturer::GetAvailableRecipes( TArray< TSubclassOf<  UFGRecipe > >& out_recipes ) const{ }
void AFGBuildableManufacturer::SetRecipe( TSubclassOf<  UFGRecipe > recipe ){ }
bool AFGBuildableManufacturer::CanProduce_Implementation() const{ return bool(); }
void AFGBuildableManufacturer::Factory_CollectInput_Implementation(){ }
void AFGBuildableManufacturer::Factory_TickProducing( float dt ){ }
void AFGBuildableManufacturer::CreateInventories(){ }
void AFGBuildableManufacturer::OnRep_CurrentRecipe(){ }
void AFGBuildableManufacturer::GetInputInventoryItems( TArray< FInventoryStack >& out_items ) const{ }
void AFGBuildableManufacturer::ClearInputInventoryItems(){ }
void AFGBuildableManufacturer::GetOutputInventoryItems( TArray< FInventoryStack >& out_items ){ }
void AFGBuildableManufacturer::ClearOutputInventoryItems(){ }
void AFGBuildableManufacturer::SetUpInventoryFilters(){ }
void AFGBuildableManufacturer::Factory_ConsumeIngredients(){ }
bool AFGBuildableManufacturer::HasRequiredIngredients() const{ return bool(); }
