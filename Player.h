#pragma once
#include "Card.h"
#include <string>
#include <vector>

using namespace std;


class Player
{
private:
	string name;
	vector<Card> availableCards;
	int gameScore;
public:

	string getName();
	vector<Card> getAvailableCards();

	Player(string name);
	void addCard(Card card);
	Card getCard(int ID);
	int countScore();
	vector<Card> sortCards(vector<Card> AC_notSorted);
};

