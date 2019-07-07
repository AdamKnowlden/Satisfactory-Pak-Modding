// This file has been automatically generated by the Unreal Header Implementation tool

#include "FGHealthComponent.h"

#if WITH_EDITOR
void UFGHealthComponent::PostEditChangeProperty( FPropertyChangedEvent& PropertyChangedEvent ){ }
#endif 
void UFGHealthComponent::BeginPlay(){ }
void UFGHealthComponent::PostLoad(){ Super::PostLoad(); }
void UFGHealthComponent::PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ){ }
void UFGHealthComponent::PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ){ }
void UFGHealthComponent::PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ){ }
void UFGHealthComponent::PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ){ }
void UFGHealthComponent::GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ){ }
bool UFGHealthComponent::NeedTransform_Implementation(){ return bool(); }
bool UFGHealthComponent::ShouldSave_Implementation() const{ return bool(); }
void UFGHealthComponent::TakeDamage( AActor* damagedActor, float damageAmount, const  UDamageType* damageType,  AController* instigatedBy, AActor* damageCauser ){ }
void UFGHealthComponent::TakePointDamage( AActor* damagedActor, float damage,  AController* instigatedBy, FVector hitLocation,  UPrimitiveComponent* hitComponent, FName boneName, FVector shotFromDirection, const  UDamageType* damageType, AActor* damageCauser ){ }
void UFGHealthComponent::TakeRadialDamage( AActor* damagedActor, float damage, const  UDamageType* damageType, FVector hitLocation, FHitResult hitInfo,  AController* instigatedBy, AActor* damageCauser ){ }
void UFGHealthComponent::SetMaxHealth( float NewMaxHealth ){ }
float UFGHealthComponent::GetCurrentHealth() const{ return float(); }
float UFGHealthComponent::GetMaxHealth() const{ return float(); }
void UFGHealthComponent::Client_TakeDamage_Implementation( AActor* damagedActor, float damageAmount, const  UDamageType* damageType,  AController* instigatedBy, AActor* damageCauser ){ }
void UFGHealthComponent::Client_TakePointDamage_Implementation( AActor* damagedActor, float damage,  AController* instigatedBy, FVector hitLocation,  UPrimitiveComponent* hitComponent, FName boneName, FVector shotFromDirection, const  UDamageType* damageType, AActor* damageCauser ){ }
void UFGHealthComponent::Client_TakeRadialDamage_Implementation( AActor* damagedActor, float damage, const  UDamageType* damageType, FVector hitLocation, FHitResult hitInfo,  AController* instigatedBy, AActor* damageCauser ){ }
void UFGHealthComponent::Client_Died_Implementation( AActor* deadActor ){ }
void UFGHealthComponent::Client_Heal_Implementation( float amount ){ }
void UFGHealthComponent::Heal( float healAmount ){ }
void UFGHealthComponent::ResetHealth(){ }
void UFGHealthComponent::ResetHealthFromDeath(){ }
void UFGHealthComponent::ReviveResetHealth(){ }
void UFGHealthComponent::Kill(){ }
void UFGHealthComponent::AddAdjustDamageListener( FAdjustDamageDelegate adjustDamage ){ }
void UFGHealthComponent::RemoveAdjustDamageListener( FAdjustDamageDelegate adjustDamage ){ }
void UFGHealthComponent::SetReplicateDamageEvents( bool setReplicates ){ }
void UFGHealthComponent::SetReplicateDeathEvents( bool setReplicates ){ }
float UFGHealthComponent::AdjustDamage( AActor* damagedActor, float damageAmount, const  UDamageType* damageType,  AController* instigatedBy, AActor* damageCauser ){ return float(); }
void UFGHealthComponent::Died( bool forceNotifies ){ }
void UFGHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
}
