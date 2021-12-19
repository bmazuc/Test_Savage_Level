// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ChasePlayer.generated.h"

/**
 * 
 */
UCLASS()
class TEST_SAVAGE_LEVEL_API UBTTask_ChasePlayer : public UBTTaskNode
{
	GENERATED_BODY()
	
	UBTTask_ChasePlayer(const FObjectInitializer& ObjectInitializer);

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual FString GetStaticDescription() const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float ChaseSpeed = 500.f;
};
