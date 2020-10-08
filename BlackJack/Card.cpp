#include "Card.h"
#include <ctime>
#include <vector>
#include "Math.h"

using CardVectorPair = std::vector<std::pair<CardNr, CardT>>;
CardVectorPair takenCards;
CardVectorPair availableCards;
std::wstring cardType[] =
{
 L"\u2663", L"\u001b[31m\u2666\u001b[0m", L"\u001b[31m\u2665\u001b[0m", L"\u2660"
};
std::wstring cardNrString[] =
{
 L"2", L"3", L"4", L"5", L"6", L"7", L"8", L"9", L"10", L"J", L"Q", L"K", L"A"
};

Card::Card(std::pair<CardNr, CardT> type)
    :type(type), val{ 0 }, text{cardNrString[type.first] + cardType[type.second]}
{
    switch (type.first)
    {
    case Jack:
        val = 10;
        break;
    case Queen:
        val = 10;
        break;
    case King:
        val = 10;
        break;
    case Ace:
        val = 11;
        break;
    default:
        val = type.first+2;
        break;
    }
}

bool Card::Intersect(std::shared_ptr<Card> card, iVec2D &MTV)
{
    const auto c1TotalX = (this->SP.x + this->Extents.x);
    const auto c1TotalY = (this->SP.y + this->Extents.y);

    const auto c2TotalX = (card->SP.x + card->Extents.x);
    const auto c2TotalY = (card->SP.y + card->Extents.y);

    if (c1TotalX >= card->SP.x && this->SP.x <= c2TotalX && c1TotalY >= card->SP.y && this->SP.y <= c2TotalY)
    { 
        auto const mX = Math::Min(Math::Abs(c1TotalX - card->SP.x), Math::Abs(c2TotalX-this->SP.x));
        auto const mY = Math::Min(Math::Abs(c1TotalY - card->SP.y), Math::Abs(c2TotalY - this->SP.y));
        MTV = iVec2D(mX, mY);
        return true;
    }
    return false;
}

bool Card::Intersect(std::shared_ptr<Card> card)
{
    const auto c1TotalX = (this->SP.x + this->Extents.x);
    const auto c1TotalY = (this->SP.y + this->Extents.y);

    const auto c2TotalX = (card->SP.x + card->Extents.x); 
    const auto c2TotalY = (card->SP.y + card->Extents.y);
    
    if (c1TotalX >= card->SP.x && this->SP.x <= c2TotalX && c1TotalY >= card->SP.y && this->SP.y <= c2TotalY)
        return true;
    return false;
}

void Card::Init()
{
    srand((uint32_t)std::time(nullptr));
    for (int i = 0; i < CardNr::Size; i++)
        for (int j = 0; j < CardT::Siz; j++)
            availableCards.push_back(CardVectorPair::value_type((CardNr)i, (CardT)j));  
}

std::shared_ptr<Card> Card::GetRandCard()
{ 
    const auto randNr = rand() % availableCards.size();
    const auto cpy = availableCards[randNr];
    takenCards.emplace_back(availableCards[randNr]);
    availableCards.erase(availableCards.begin() + randNr);
    return std::shared_ptr<Card>(new Card(cpy));
}

void Card::ClearTakenCards()
{
    for (const auto &current : takenCards)
        availableCards.emplace_back(current);
    takenCards.clear();
}

void Card::Draw(iVec2D trans, iVec2D size)
{
    SP = trans;
    Extents = size;
    auto const totalX = trans.x + size.x;
    auto const totalY = trans.y + size.y;

    //Card Corners
    SetCursorPosition(trans.x, trans.y);
    std::wcout << L"\u2554";
    SetCursorPosition(totalX, trans.y);
    std::wcout << L"\u2557";
    SetCursorPosition(trans.x, totalY);
    std::wcout << L"\u255A";
    SetCursorPosition(totalX, totalY);
    std::wcout << L"\u255D";

    //Card horizontal lines
    for (int x = trans.x + 1; x < totalX; x++)
    {
        SetCursorPosition(x, trans.y);
        std::wcout << L"\u2550";
        SetCursorPosition(x, totalY);
        std::wcout << L"\u2550";
    }
    //Card Vertical Lines
    for (int y = trans.y + 1; y < totalY; y++)
    {
        SetCursorPosition(trans.x, y);
        std::wcout << L"\u2551";
        SetCursorPosition(totalX, y);
        std::wcout << L"\u2551";
    }
    //Card text
    SetCursorPosition(trans.x + 1, trans.y + 1);
    std::wcout << text;
    SetCursorPosition(totalX - 2, totalY - 1);
    std::wcout << text;
    std::wcout << std::endl;
}

void Card::Draw()
{
    iVec2D trans = SP;
    iVec2D size = Extents;
    auto const totalX = trans.x + size.x;
    auto const totalY = trans.y + size.y;

    SetCursorPosition(trans.x, trans.y);
    std::wcout << L"\u2554";
    SetCursorPosition(totalX, trans.y);
    std::wcout << L"\u2557";
    SetCursorPosition(trans.x, totalY);
    std::wcout << L"\u255A";
    SetCursorPosition(totalX, totalY);
    std::wcout << L"\u255D";

    for (int x = trans.x + 1; x < totalX; x++)
    {
        SetCursorPosition(x, trans.y);
        std::wcout << L"\u2550";
        SetCursorPosition(x, totalY);
        std::wcout << L"\u2550";
    }
    for (int y = trans.y + 1; y < totalY; y++)
    {
        SetCursorPosition(trans.x, y);
        std::wcout << L"\u2551";
        SetCursorPosition(totalX, y);
        std::wcout << L"\u2551";
    }

    SetCursorPosition(trans.x + 1, trans.y + 1);
    std::wcout << text;
    SetCursorPosition(totalX - 2, totalY - 1);
    std::wcout << text;
    std::wcout << std::endl;
}

void Card::DrawBack()
{
    auto const totalX = SP.x + Extents.x;
    auto const totalY = SP.y + Extents.y;

    SetCursorPosition(SP.x, SP.y);
    std::wcout << L"\u2554";
    SetCursorPosition(totalX, SP.y);
    std::wcout << L"\u2557";
    SetCursorPosition(SP.x, totalY);
    std::wcout << L"\u255A";
    SetCursorPosition(totalX, totalY);
    std::wcout << L"\u255D";
    for (int y = SP.y+1; y < SP.y + Extents.y; y++)
    { 
        SetCursorPosition(totalX, y);
        std::wcout << L"\u2551";
        SetCursorPosition(SP.x, y);
        std::wcout << L"\u2551";    
        for (int x = SP.x+1; x < SP.x + Extents.x; x++)
        {
            std::wcout << L"#";
        }
    }

    for (int x = SP.x + 1; x < totalX; x++)
    {
        SetCursorPosition(x, SP.y);
        std::wcout << L"\u2550";
        SetCursorPosition(x, totalY);
        std::wcout << L"\u2550";
    }
    std::wcout << std::endl;
}

void Card::Clear()
{
    iVec2D trans = SP;
    iVec2D size = Extents;
    auto const totalX = trans.x + size.x;
    auto const totalY = trans.y + size.y;

    SetCursorPosition(trans.x, trans.y);
    std::wcout << L" ";
    SetCursorPosition(totalX, trans.y);
    std::wcout << L" ";
    SetCursorPosition(trans.x, totalY);
    std::wcout << L" ";
    SetCursorPosition(totalX, totalY);
    std::wcout << L" ";

    for (int x = trans.x + 1; x < totalX; x++)
    {
        SetCursorPosition(x, trans.y);
        std::wcout << L" ";
        SetCursorPosition(x, totalY);
        std::wcout << L" ";
    }
    for (int y = trans.y + 1; y < totalY; y++)
    {
        SetCursorPosition(trans.x, y);
        std::wcout << L" ";
        SetCursorPosition(totalX, y);
        std::wcout << L" ";
    }

    SetCursorPosition(trans.x + 1, trans.y + 1);
    std::wcout << L"   ";
    SetCursorPosition(totalX - 2, totalY - 1);
    std::wcout << L"   ";
    std::wcout << std::endl;
}

void Card::ClearBack()
{
    auto const totalX = SP.x + Extents.x;
    auto const totalY = SP.y + Extents.y;

    SetCursorPosition(SP.x, SP.y);
    std::wcout << L" ";
    SetCursorPosition(totalX, SP.y);
    std::wcout << L" ";
    SetCursorPosition(SP.x, totalY);
    std::wcout << L" ";
    SetCursorPosition(totalX, totalY);
    std::wcout << L" ";
    for (int y = SP.y + 1; y < SP.y + Extents.y; y++)
    {
        SetCursorPosition(totalX, y);
        std::wcout << L" ";
        SetCursorPosition(SP.x, y);
        std::wcout << L" ";
        for (int x = SP.x + 1; x < SP.x + Extents.x; x++)
        {
            std::wcout << L" ";
        }
    }

    for (int x = SP.x + 1; x < totalX; x++)
    {
        SetCursorPosition(x, SP.y);
        std::wcout << L" ";
        SetCursorPosition(x, totalY);
        std::wcout << L" ";
    }
    std::wcout << std::endl;
}
