// This file has been automatically generated by the Unreal Header Implementation tool

#include "FGConveyorBeltHologram.h"

AFGConveyorBeltHologram::AFGConveyorBeltHologram(){ }
void AFGConveyorBeltHologram::GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const{ }
void AFGConveyorBeltHologram::BeginPlay(){ }
bool AFGConveyorBeltHologram::TryUpgrade( const FHitResult& hitResult ){ return bool(); }
void AFGConveyorBeltHologram::SetHologramLocationAndRotation( const FHitResult& hitResult ){ }
bool AFGConveyorBeltHologram::MultiStepPlacement(){ return bool(); }
TArray< FItemAmount > AFGConveyorBeltHologram::GetCost( bool includeChildren ) const{ return TArray<FItemAmount>(); }
AActor* AFGConveyorBeltHologram::GetUpgradedActor() const{ return nullptr; }
void AFGConveyorBeltHologram::SpawnChildren(  UFGBuildGunStateBuild* state ){ }
TArray<AFGBuildable*> AFGConveyorBeltHologram::GetAnyConnectedBuildables(){ return TArray<AFGBuildable*>(); }
void AFGConveyorBeltHologram::ConfigureActor(  AFGBuildable* inBuildable ) const{ }
void AFGConveyorBeltHologram::ConfigureComponents(  AFGBuildable* inBuildable ) const{ }
void AFGConveyorBeltHologram::CheckValidFloor(){ }
void AFGConveyorBeltHologram::CheckClearance(){ }
void AFGConveyorBeltHologram::CheckValidPlacement(){ }
void AFGConveyorBeltHologram::SetMaterial(  UMaterialInterface* material ){ }
void AFGConveyorBeltHologram::SetupClearanceDetector(){ }
int32 AFGConveyorBeltHologram::GetNumSections() const{ return int32(); }
void AFGConveyorBeltHologram::OnRep_SplineData(){ }
void AFGConveyorBeltHologram::OnRep_ConnectionArrowComponentDirection(){ }
void AFGConveyorBeltHologram::AutoRouteSpline( const FVector& connectionPos, const FVector& connectionNormal, const float& connectionClearance ){ }
bool AFGConveyorBeltHologram::ValidateIncline(){ return bool(); }
bool AFGConveyorBeltHologram::ValidateLength(){ return bool(); }
