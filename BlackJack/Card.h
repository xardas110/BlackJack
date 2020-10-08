#pragma once
#include <string>
#include <memory>
#include "TerminalHelpers.h"
#include "Vec.h"
enum CardT
{
	Club, Diamond, Heart, Spade, Siz
};
enum CardNr
{
	Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace, Size 
};

class Card
{
private:
	Card(std::pair<CardNr, CardT> type);
public:
	int								val;
	std::wstring					text;
	std::pair<CardNr, CardT>		type;
	iVec2D							SP;
	iVec2D							Extents;

	bool							Intersect(std::shared_ptr<Card> card, iVec2D &MTV);
	bool							Intersect(std::shared_ptr<Card> card);
	static void						Init();
	static std::shared_ptr<Card>	GetRandCard();
	static void						ClearTakenCards();
	void							Draw(iVec2D trans, iVec2D size = iVec2D(8,6));
	void							Draw();
	void							DrawBack();
	void							Clear();
	void							ClearBack();
};

