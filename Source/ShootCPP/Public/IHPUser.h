#pragma once

class IHPUser
{
public:
	virtual float GetHP() const = 0;
	virtual void TakeDamage(float damage) = 0;
};
