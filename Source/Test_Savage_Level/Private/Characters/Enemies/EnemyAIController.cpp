// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/EnemyAIController.h"
//#include "Perception/AIPerceptionComponent.h"
#include "PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

AEnemyAIController::AEnemyAIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception Component"));
	sightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	AIPerceptionComponent->ConfigureSense(*sightConfig);
	AIPerceptionComponent->SetDominantSense(sightConfig->GetSenseImplementation());
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

void AEnemyAIController::UpdateTargetPerception(AActor* actor, FAIStimulus stimulus)
{
	if (actor->ActorHasTag("Enemy"))
		return;

	if (PlayerCharacter && PlayerCharacter->GetCurrentState() == EPlayerCharacterState::Dead)
	{
		if (EnemyTimerHandle.IsValid())
			TimerManager->ClearTimer(EnemyTimerHandle);

		LoseTrackOfPlayer();
		PlayerCharacter = nullptr;
		return;
	}

	if (actor->ActorHasTag("Player") && stimulus.WasSuccessfullySensed())
	{
		PlayerCharacter = Cast<APlayerCharacter>(actor);

		if (PlayerCharacter && PlayerCharacter->GetCurrentState() == EPlayerCharacterState::Dead)
		{
			PlayerCharacter = nullptr;
			return;
		}

		if (EnemyTimerHandle.IsValid())
			TimerManager->ClearTimer(EnemyTimerHandle);

		BlackboardComponent->SetValueAsBool(HasLineOfSight, true);
		BlackboardComponent->SetValueAsObject(PlayerActor, actor);
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