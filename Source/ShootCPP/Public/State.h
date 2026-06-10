// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class State
{
public:
	State();
	virtual ~State();
	
	virtual void Enter();
	virtual void Execute(float DeltaTime);
	virtual void Exit();
	
};
