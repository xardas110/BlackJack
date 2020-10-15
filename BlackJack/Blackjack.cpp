#include "Blackjack.h"
#include <thread>
#include <chrono>

#define DELAY 3000

BlackJack::BlackJack()
	:currentRound{ 0 }, currentPot{0}
{
}

void BlackJack::PlaceBet(Player& play)
{
	int temp{};
	iVec2D betOffset(0, 19);
REDOBID:
	SetCursorPosition(betOffset);
	AskInput(L"Place a bet: ", temp);
	if (temp > play.cash or temp <= 0)
		goto REDOBID;
	system("cls");
	play.cash -= temp;
	currentPot = temp * 2;
}

int BlackJack::Init()
{
	Card::Init();
	player.cash = 2000;
	dealer.cash = 20000000;

	optionText = CMDText(
		{0, 20}, 
		L"1. Hit\n"
		L"2. Stand\n");

	currentRoundText = CMDText	({ 100, 0 }, L"");
	statusText = CMDText		({ 30, 12 }, L"");
	dealer.SetTranslation		({ 30, 0  });
	player.SetTranslation		({ 30, 20 });

	dealerCardSumText = CMDText(dealer.GetTranslation() + iVec2D(0, dealer.GetCardSize().y + 1), L"");
	playerCardSumText = CMDText(player.GetTranslation() + iVec2D(0, player.GetCardSize().y + 1), L"");
	playerCashText =	CMDText(player.GetTranslation() + iVec2D(0, -1), L"");

	return 1;
}

void BlackJack::OnUpdateRender()
{
	currentRound++;
	currentRoundText.SetText(L"Round: " + std::to_wstring(currentRound));
	currentRoundText.Print();

	playerCashText.SetText(L"Cash: " + std::to_wstring(player.cash) + L'$');
	playerCashText.Print();
	PlaceBet(player);
	
	dealer.TakeCards();
	player.TakeCard();
	player.TakeCard();

	statusText.SetText(L"Current pot: " + std::to_wstring(currentPot) + L"$");
	playerCashText.SetText(L"Cash: " + std::to_wstring(player.cash) + L'$');
	playerCardSumText.SetText(L"Card Sum: " + std::to_wstring(player.GetCardSum()));
	dealerCardSumText.SetText(L"Card Sum: " + std::to_wstring(dealer.GetCardValue(1)));

	statusText.Print();
	playerCashText.Print();
	playerCardSumText.Print();
	dealerCardSumText.Print();

	if (player.GetCardSum() == 21)
	{
		const auto BJPot = (int)((float)currentPot * 1.5f);
		statusText.Clear();
		statusText.SetText(L"Player BLACKJACK! wins pot: " + std::to_wstring(BJPot));
		statusText.Print();
		player.cash += BJPot;
		std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
		return;
	}

	optionText.Print();
	bool OnGoing = true;
	do
	{				
		switch (_getch())
		{		
		case '1':
		{
			player.TakeCard();
			const auto playerCardSum = player.GetCardSum();

			playerCardSumText.Clear();
			playerCardSumText.SetText(L"Card Sum: " + std::to_wstring(playerCardSum));
			playerCardSumText.Print();
			if (playerCardSum > 21)
			{
				statusText.Clear();
				statusText.SetText(L"Player Busted!");
				statusText.Print();
				std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
				OnGoing = false;
				break;
			}
			if (playerCardSum == 21)
			{
				const auto BJPot = (int)((float)currentPot * 1.5f);
				statusText.Clear();
				statusText.SetText(L"Player BLACKJACK! wins pot: " + std::to_wstring(BJPot));
				statusText.Print();
				player.cash += BJPot;
				std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
				OnGoing = false;
				break;
			}
		}
		break;
		case '2':
		{
			dealer.ShowCards();
			const auto playerCardSum = player.GetCardSum();
			const auto dealerCardSum = dealer.GetCardSum();

			dealerCardSumText.Clear();
			dealerCardSumText.SetText(L"Card sum: " + std::to_wstring(dealerCardSum));
			dealerCardSumText.Print();

			playerCardSumText.Clear();
			playerCardSumText.SetText(L"Card sum: " + std::to_wstring(playerCardSum));
			playerCardSumText.Print();

			if (dealerCardSum > 21)
			{
				statusText.Clear();
				statusText.SetText(L"Dealer Busted!");
				statusText.Print();
				player.cash += currentPot;
				std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
				OnGoing = false;
				break;
			}
			if (playerCardSum > dealerCardSum)
			{
				statusText.Clear();
				statusText.SetText(L"Player Wins!");
				statusText.Print();
				player.cash += currentPot;
				std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
				OnGoing = false;
				break;
			}
			else if (playerCardSum == dealerCardSum)
			{
				statusText.Clear();
				statusText.SetText(L"Draw!");
				statusText.Print();
				int halfPot = currentPot / 2;
				player.cash += halfPot;
				dealer.cash += halfPot;
				std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
				OnGoing = false;
				break;
			}
			else
			{
				statusText.Clear();
				statusText.SetText(L"Dealer Wins!");
				statusText.Print();
				dealer.cash += currentPot;
				std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
				OnGoing = false;
				break;
			}
		}
		break;
		default:
			break;
		}
	} while (OnGoing);	
}

void BlackJack::OnClear()
{
	optionText.Clear();
	statusText.Clear();
	player.ClearCards();
	dealer.ClearCards();
	playerCashText.Clear();
	playerCardSumText.Clear();
	dealerCardSumText.Clear();
	currentRoundText.Clear();
	Card::ClearTakenCards();

	if (player.cash <= 0)
	{
		system("cls");
		SetCursorPosition(0, 0);
		std::wcout << "Game Over!";
		bGame = false;
	}
}
