// This file has been automatically generated by the Unreal Header Implementation tool

#include "FGHologram.h"

AFGHologram::AFGHologram(){ }
void AFGHologram::GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const{ }
void AFGHologram::SetRecipe( TSubclassOf<  UFGRecipe > recipe ){ }
TSubclassOf< class UFGItemDescriptor > AFGHologram::GetItemDescriptor() const{ return TSubclassOf<class UFGItemDescriptor>(); }
void AFGHologram::BeginPlay(){ }
void AFGHologram::Destroyed(){ }
void AFGHologram::SetActorHiddenInGame( bool newHidden ){ }
bool AFGHologram::IsValidHitResult( const FHitResult& hitResult ) const{ return bool(); }
bool AFGHologram::TryUpgrade( const FHitResult& hitResult ){ return bool(); }
void AFGHologram::AdjustForGround( const FHitResult& hitResult, FVector& out_adjustedLocation, FRotator& out_adjustedRotation ){ }
bool AFGHologram::TrySnapToActor( const FHitResult& hitResult ){ return bool(); }
void AFGHologram::SetHologramLocationAndRotation( const FHitResult& hitResult ){ }
void AFGHologram::OnInvalidHitResult(){ }
void AFGHologram::ValidatePlacementAndCost(  UFGInventoryComponent* inventory ){ }
bool AFGHologram::MultiStepPlacement(){ return bool(); }
void AFGHologram::Scroll( int32 delta ){ }
void AFGHologram::ScrollRotate( int32 delta, int32 step ){ }
void AFGHologram::SetInitialScrollValue( EHologramScrollMode scrollMode, int32 scrollValue ){ }
int32 AFGHologram::GetScrollValue( EHologramScrollMode scrollMode ) const{ return int32(); }
void AFGHologram::SetScrollMode( EHologramScrollMode mode ){ }
EHologramScrollMode AFGHologram::GetScrollMode() const{ return EHologramScrollMode(); }
bool AFGHologram::IsScrollModeSupported( EHologramScrollMode mode ) const{ return bool(); }
void AFGHologram::GetSupportedScrollModes( TArray< EHologramScrollMode >* out_modes ) const{ }
void AFGHologram::SetSnapToGuideLines( bool isEnabled ){ }
void AFGHologram::Server_SetSnapToGuideLines_Implementation( bool isEnabled ){ }
bool AFGHologram::Server_SetSnapToGuideLines_Validate( bool isEnabled ){ return bool(); }
void AFGHologram::SetPlacementMaterial( bool material ){ }
bool AFGHologram::IsChanged() const{ return bool(); }
AActor* AFGHologram::GetUpgradedActor() const{ return nullptr; }
bool AFGHologram::CanConstruct() const{ return bool(); }
AActor* AFGHologram::Construct( TArray< AActor* >& out_children ){ return nullptr; }
TArray< FItemAmount > AFGHologram::GetBaseCost() const{ return TArray<FItemAmount>(); }
TArray< FItemAmount > AFGHologram::GetCost( bool includeChildren ) const{ return TArray<FItemAmount>(); }
void AFGHologram::SetDisabled( bool disabled  ){ }
bool AFGHologram::IsDisabled() const{ return bool(); }
void AFGHologram::SpawnChildren(  UFGBuildGunStateBuild* state ){ }
void AFGHologram::AddChild( AFGHologram* child ){ }
void AFGHologram::AddConstructDisqualifier( TSubclassOf<  UFGConstructDisqualifier > disqualifier ){ }
void AFGHologram::GetConstructDisqualifiers( TArray< TSubclassOf<  UFGConstructDisqualifier > >& out_constructResults ) const{ }
void AFGHologram::ResetConstructDisqualifiers(){ }
void AFGHologram::SetupClearance(  UBoxComponent* boxComponent ){ }
void AFGHologram::CheckValidPlacement(){ }
void AFGHologram::CheckCanAfford(  UFGInventoryComponent* inventory ){ }
void AFGHologram::OnSnap(){ }
void AFGHologram::OnRep_PlacementMaterial(){ }
void AFGHologram::SetMaterial(  UMaterialInterface* material ){ }
TSubclassOf< AActor > AFGHologram::GetActorClass() const{ return TSubclassOf<AActor>(); }
USceneComponent* AFGHologram::SetupComponent( USceneComponent* attachParent, UActorComponent* componentTemplate, const FName& componentName ){ return nullptr; }
void AFGHologram::SetupDepthMeshComponent( USceneComponent* attachParent, UMeshComponent* componentTemplate ){ }
void AFGHologram::SetIsChanged(){ }
bool AFGHologram::IsLocalHologram() const{ return bool(); }
bool AFGHologram::IsValidHitActor( AActor* hitActor ) const{ return bool(); }
int32 AFGHologram::GetRotationStep() const{ return int32(); }
float AFGHologram::ApplyScrollRotationTo( float base, bool onlyUseBaseForAlignment ) const{ return float(); }
void AFGHologram::SetupComponents(){ }
void AFGHologram::Client_PlaySnapSound_Implementation(){ }
void AFGHologram::OnRep_InitialScrollModeValue(){ }
