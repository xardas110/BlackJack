#pragma once
#include "Player.h"
#include "Vec.h"
class Dealer: public Player
{
public:
	void			Init(iVec2D trans);
	virtual void	TakeCard() override;
	virtual void	ClearCards() override;
	void			ShowCards();
	const size_t	GetCardValue(int offset) const;
	void			TakeCards();
};

