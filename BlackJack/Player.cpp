#include "Player.h"

Player::Player()
	:cash{ 100 }, cardSum{ 0 }, translation{ 0, 0 }, offset{ 4 }, cardSize{ 8, 6 }, numAces{0}
{
}

void Player::TakeCard()
{
	std::shared_ptr<Card> card = Card::GetRandCard();
	cardSum += card->val;
	card->SP = translation + iVec2D(offset * cards.size(), 0);
	card->Extents = cardSize;
	if (card->type.first == Ace)
		numAces++;

	cards.push_back(card);	
	DrawCard(cards.size()-1);
}

const size_t Player::GetNumCards() const
{
	return cards.size();
}

const size_t Player::GetCardSum() const
{
	auto sum{0};

	for (int i = 0; i <= numAces; i++)
	{
		sum = cardSum - 10 * i;
		if (sum <= 21)
			break;
	}

	return sum;
}

const size_t Player::GetNumAces() const
{
	return numAces;
}

iVec2D Player::GetCardSize() const
{
	return cardSize;
}

iVec2D Player::GetTranslation() const
{
	return translation;
}

void Player::SetTranslation(iVec2D trans)
{
	translation = trans;
}

void Player::DrawCards()
{
	//Why do I do it this way? Well better performance and yeah I guess I'm bored too
	for (int i= 0, k = 1; i< cards.size(); i++, k++)
	{	
		cards[i]->Draw();	
		if (k < cards.size())
		{
			iVec2D MTV;
			if (cards[i]->Intersect(cards[k], MTV))
				Clear(cards[k]->SP, MTV);
		}
	}
}

void Player::DrawCard(int offset)
{
	if (offset < cards.size() && offset > 0)
	{
		iVec2D MTV;
		if (cards[offset-1]->Intersect(cards[offset], MTV))
			Clear(cards[offset]->SP, MTV);
	}
	cards[offset]->Draw();
}

void Player::ClearCard(int offset)
{
	if (offset < 0)
		return;

	cards[offset]->Clear();
	if (offset - 1 > 0)
		cards[offset - 1]->Draw();
	cards.erase(cards.begin()+offset);
	cardSum = 0;
	numAces = 0;
	for (const auto & current : cards)
	{
		cardSum += current->val;
		numAces += current->type.first == Ace;
	}
}

void Player::ClearCards()
{
	for (auto& current : cards) 
		current->Clear();
	
	cardSum = 0;
	numAces = 0;
	cards.erase(cards.begin(), cards.end());
}
