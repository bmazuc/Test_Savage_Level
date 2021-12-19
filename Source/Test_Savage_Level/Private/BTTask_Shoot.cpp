// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "AIController.h"
#include "Characters/Enemies/Enemy.h"

UBTTask_Shoot::UBTTask_Shoot(const FObjectInitializer& ObjectInitializer)
{
	NodeName = "Shoot";
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemy* controlledPawn = Cast<AEnemy>(OwnerComp.GetAIOwner()->GetPawn());

	if (!controlledPawn)
		return EBTNodeResult::Failed;

	controlledPawn->FireShoot();

	return EBTNodeResult::Succeeded;
}

FString UBTTask_Shoot::GetStaticDescription() const
{
	return FString::Printf(TEXT("Shoot"));
}