// This file has been automatically generated by the Unreal Header Implementation tool

#include "FGRecipe.h"

FText UFGRecipe::GetRecipeName( TSubclassOf< UFGRecipe > inClass ){ return FText(); }
TArray< FItemAmount > UFGRecipe::GetIngredients( TSubclassOf< UFGRecipe > inClass ){ return TArray<FItemAmount>(); }
TArray< FItemAmount > UFGRecipe::GetProducts( TSubclassOf< UFGRecipe > inClass, bool allowChildRecipes ){ return TArray<FItemAmount>(); }
float UFGRecipe::GetManufacturingDuration( TSubclassOf< UFGRecipe > inClass ){ return float(); }
TArray< TSubclassOf< UObject > > UFGRecipe::GetProducedIn( TSubclassOf< UFGRecipe > inClass ){ return TArray<TSubclassOf<UObject> >(); }
void UFGRecipe::SortByName( UPARAM(ref) TArray< TSubclassOf< UFGRecipe > >& recipes ){ }
void UFGRecipe::GetProducedIn( TArray< TSubclassOf< UObject > >& out_producedIn ) const{ }
FText UFGRecipe::GetDisplayName() const{ return FText(); }
