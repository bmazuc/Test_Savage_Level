// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_ChasePlayer.h"
#include "AIController.h"
#include "Character/Enemy.h"

UBTTask_ChasePlayer::UBTTask_ChasePlayer(const FObjectInitializer& ObjectInitializer)
{
	NodeName = "Chase Player";
}

EBTNodeResult::Type UBTTask_ChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemy* controlledPawn = Cast<AEnemy>(OwnerComp.GetAIOwner()->GetPawn());

	if (!controlledPawn)
		return EBTNodeResult::Failed;

	controlledPawn->UpdateWalkSpeed(ChaseSpeed);

	return EBTNodeResult::Succeeded;
}

FString UBTTask_ChasePlayer::GetStaticDescription() const
{
	return FString::Printf(TEXT("Chase Player"));
}