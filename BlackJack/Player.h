#pragma once
#include <vector>
#include "Card.h"
#include "Vec.h"

class Player
{
protected:	
	int cardSum;
	int offset;//card spacing offset
	int numAces;
	iVec2D cardSize;
	iVec2D translation;
	std::vector<std::shared_ptr<Card>> cards;
public:	
	int cash;
	Player();
	virtual void	TakeCard();
	const size_t	GetNumCards() const;
	const size_t	GetCardSum() const;
	const size_t	GetNumAces() const;
	iVec2D			GetCardSize() const;
	iVec2D			GetTranslation() const;
	void			SetTranslation(iVec2D trans);
	void			DrawCards();
	void			DrawCard(int offset);
	void			ClearCard(int offset);
	virtual void	ClearCards();
};

