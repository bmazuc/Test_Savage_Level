// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EnemyAIController.h"
#include "Character/PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

AEnemyAIController::AEnemyAIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception Component"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	AIPerceptionComponent->ConfigureSense(*SightConfig);
	AIPerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::UpdateTargetPerception);
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	TimerManager = &(GetWorld()->GetTimerManager());

	if (BehaviorTree && BlackboardData)
	{
		UseBlackboard(BlackboardData, BlackboardComponent);
		RunBehaviorTree(BehaviorTree);
	}
}

void AEnemyAIController::UpdateTargetPerception(AActor* Actor, FAIStimulus Stimulus)
{
	if (Actor->ActorHasTag("Enemy"))
		return;

	if (PlayerCharacter && PlayerCharacter->GetCurrentState() == EPlayerCharacterState::Dead)
	{
		if (EnemyTimerHandle.IsValid())
			TimerManager->ClearTimer(EnemyTimerHandle);

		LoseTrackOfPlayer();
		PlayerCharacter = nullptr;
		return;
	}

	if (Actor->ActorHasTag("Player") && Stimulus.WasSuccessfullySensed())
	{
		PlayerCharacter = Cast<APlayerCharacter>(Actor);

		if (PlayerCharacter && PlayerCharacter->GetCurrentState() == EPlayerCharacterState::Dead)
		{
			PlayerCharacter = nullptr;
			return;
		}

		if (EnemyTimerHandle.IsValid())
			TimerManager->ClearTimer(EnemyTimerHandle);

		BlackboardComponent->SetValueAsBool(HasLineOfSight, true);
		BlackboardComponent->SetValueAsObject(PlayerActor, Actor);
	}
	else
	{
		BlackboardComponent->SetValueAsBool(HasLineOfSight, false);
		if (ChaseTimer > 0.f)
			TimerManager->SetTimer(EnemyTimerHandle, this, &AEnemyAIController::LoseTrackOfPlayer, ChaseTimer, false);
		else
			LoseTrackOfPlayer();
	}
}

void AEnemyAIController::LoseTrackOfPlayer()
{
	BlackboardComponent->SetValueAsObject(PlayerActor, nullptr);
}