#pragma once
#include "Card.h"
#include "TerminalHelpers.h"
#include "Vec.h"
#include "Player.h"
#include "Dealer.h"
#include "ConsoleText.h"
#include <conio.h>

class BlackJack
{
public:
	int currentRound;
	int currentPot;
	bool bGame = true;
	BlackJack();
	CMDText optionText;
	CMDText statusText;
	CMDText playerCardSumText;
	CMDText dealerCardSumText;
	CMDText playerCashText;
	CMDText currentRoundText;
	Player player;
	Dealer dealer;
	void PlaceBet(Player& play);
	virtual int Init();	
	virtual void OnUpdateRender();
	virtual void OnClear();
};