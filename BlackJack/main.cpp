#include "Blackjack.h"
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <Windows.h>
#include <memory>
int main()
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	std::shared_ptr<BlackJack> blackJack = std::make_shared<BlackJack>(BlackJack());
	if (blackJack->Init() != 1) return -1;
	do 
	{
		blackJack->OnUpdateRender();
		blackJack->OnClear();
	} while (blackJack->bGame);
}
