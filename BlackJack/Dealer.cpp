#include "Dealer.h"


void Dealer::Init(iVec2D trans)
{
	translation = trans;
}

void Dealer::TakeCard()
{
	std::shared_ptr<Card> card = Card::GetRandCard();
	cardSum += card->val;
	card->SP = translation + iVec2D(offset * cards.size(), 0);
	card->Extents = cardSize;
	if (card->type.first == Ace)
		numAces++;
	cards.push_back(card);
	if (cards.size() == 1)
		cards[0]->DrawBack();
	else if (cards.size() == 2)
		DrawCard(1);
}

void Dealer::ShowCards()
{
	Clear(translation, translation + iVec2D(offset, 0) + cardSize);
	DrawCards();
}

const size_t Dealer::GetCardValue(int offset) const
{
	if (cards.size() > offset)
		return cards[offset]->val;
}

void Dealer::ClearCards()
{
	for (auto& current : cards)
	{
		current->Clear();
		current->ClearBack();
	}
	cardSum = 0;
	numAces = 0;
	cards.erase(cards.begin(), cards.end());
}

void Dealer::TakeCards()
{
	for (;;)
	{			
		TakeCard();
		if (cardSum > 17)
			break;
	}
}
