// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State.h"

template<typename TEnum>
class TStateMachine
{
	using FCondition = TFunction<bool()>;

	struct FTransition
	{
		State* Next;
		FCondition Cond;
	};

private:
	TMap<TEnum, TUniquePtr<State>> StateDict;
	TMap<State*, TArray<FTransition>> TransitionDict;
	State* CurrentState = nullptr;

public:
	TStateMachine() {}
	TStateMachine(State* startState)
	{
		CurrentState = startState;
	}
	~TStateMachine() {}

	void RegisterState(TEnum Key, TUniquePtr<State> InState)
	{
		StateDict.Add(Key, MoveTemp(InState));
	}

	void ChangeState(TEnum Key)
	{
		TUniquePtr<State>* Found = StateDict.Find(Key);
		if (!Found) return;

		if (CurrentState) CurrentState->Exit();
		CurrentState = Found->Get();
		CurrentState->Enter();
	}

	void RemoveState(TEnum Key)
	{
		StateDict.Remove(Key);
	}

	void Execute(float DeltaTime)
	{
		if (CurrentState) CurrentState->Execute(DeltaTime);
		CheckConditions();
	}

	void RegisterCondition(TEnum From, TEnum To, FCondition Cond)
	{
		TUniquePtr<State>* F = StateDict.Find(From);
		TUniquePtr<State>* T = StateDict.Find(To);
		if (!F || !T || !Cond) return;

		TransitionDict.FindOrAdd(F->Get()).Add({ T->Get(), Cond });
	}

private:
	void CheckConditions()
	{
		TArray<FTransition>* Transitions = TransitionDict.Find(CurrentState);
		if (!Transitions) return;

		for (auto& T : *Transitions)
		{
			if (T.Cond())
			{
				if (CurrentState) CurrentState->Exit();
				CurrentState = T.Next;
				CurrentState->Enter();
				break;
			}
		}
	}
};
