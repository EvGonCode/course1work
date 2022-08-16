#pragma once
#include <wx/string.h>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include "Card.h"
#include "Player.h"
#include "Deck.h"
using namespace std;



class GameProcess
{
private:
	int playersAmount;
	int startCardsAmount;
	int firstPlayerToStep;
	Deck* stockCards;
	vector<Card> playedCards;
	vector<Player*> playersInGame;
	Player* currPlayer;
	//Player* nextPlayer;
	string playerName;
	string currentSuet; //Масть яку можна класти
	bool isItFirstStep;
	bool isClockwise;
	bool isCardPlayed;
	bool isCardTaken;
	bool isSnowballMode; //Чи діє на теперішній хід правило із пункту про карту 4
	bool isUserLoosed;
	bool isUserWon;


	//string currAllovedSuit; //Масть яку можна класти
	//bool isCurrStepIsSnowBall; //Чи діє на теперішній хід правило із пункту про карту 4
	bool isCurrStepMustBeSkiped; //Чи повинен теперішній гравець пропустити свій хід
	int cardsMustBeTakenCurrent; //Скільки карт повинен взяти теперішній гравець

	//string nextAllovedSuit; 
	//bool isNextStepIsSnowBall; 
	bool isNextStepMustBeSkiped; 
	int cardsMustBeTakenNext;

	Player* getPlayerWithMaxPoints() {
		int max = 0;
		for (int i = 0; i < playersInGame.size(); i++) {
			if (playersInGame[i]->countScore() > max) {
				max = playersInGame[i]->countScore();
			}
		}
		for (int i = 0; i < playersInGame.size(); i++) {
			if (playersInGame[i]->countScore() == max) {
				return playersInGame[i];
			}
		}
	}
	void startNewRound() {
		Player* looser = getPlayerWithMaxPoints();
		if (looser->getName() != playerName and playersInGame.size() == 2) {
			isUserWon = true;
			return;
		}
		playersAmount--;
		isItFirstStep = true;
		isClockwise = true;
		isCardPlayed = false;
		isCardTaken = false;
		Deck* stockCards = new Deck();
		playedCards.clear();

		for (int i = 0; i < playersInGame.size(); i++) {
			if (playersInGame[i]->getName() == looser->getName()) {
				if (playersInGame[i]->getName() == playerName) {
					isUserLoosed = true;
					return;
				}
				playersInGame.erase(playersInGame.begin() + i);
				break;
			}
		}
		
		if (firstPlayerToStep >= playersInGame.size()) {
			firstPlayerToStep = playersInGame.size() - 1;
		}
		currPlayer = playersInGame[firstPlayerToStep];
		currentSuet = "";
		isSnowballMode = false;

		isCurrStepMustBeSkiped = false;
		cardsMustBeTakenCurrent = 0;

		isNextStepMustBeSkiped = false;
		cardsMustBeTakenNext = 0;
	}
	Player* getNextPlayer() {
		if (isClockwise) {
			for (int i = 0; i < playersInGame.size(); i++) {
				if (playersInGame[i]->getName() == currPlayer->getName()) {
					if (i + 1 == playersInGame.size()) {
						return playersInGame[0];
					}
					else {
						return playersInGame[i + 1];
					}
				}
			}
		}
		else {
			for (int i = 0; i < playersInGame.size(); i++) {
				if(playersInGame[i]->getName() == currPlayer->getName()) {
					if (i - 1 < 0) {
						return playersInGame[playersInGame.size() - 1];
					}
					else {
						return playersInGame[i - 1];
					}
				}
			}
		}
	}
	Card getCardToStep(Player* player) {
		vector<Card> playerCards = player->getAvailableCards();
		bool needToCheck = true;
		while (needToCheck) {
			needToCheck = false;
			for (int i = 0; i < playerCards.size(); i++) {
				if (!isCardCanBePlayed(playerCards[i])) {
					playerCards.erase(playerCards.begin() + i);
					needToCheck = true;
					break;
				}
			}
		}

		Card card = playerCards[0];
		for (int i = 0; i < playerCards.size(); i++) {
			if (card.getScoreMass() < playerCards[i].getScoreMass()) {
				card = playerCards[i];
			}
		}
		return card;
		
	}

public:
	//Tests
	vector<Card> getAllowedCardsToStep() {
		Deck* deck = new Deck();
		vector<Card> allawedCardsNotSorted;
		for (int i = 0; i < 54; i++) {
			Card card = deck->pop_front();
			if (isCardCanBePlayed(card)) {
				allawedCardsNotSorted.push_back(card);
			}
		}

		return currPlayer->sortCards(allawedCardsNotSorted);
	}

	vector<Card> getPlayedCards() {
		return this->playedCards;
	}
	void reduceMustBeenTakenCards() {
		this->cardsMustBeTakenCurrent--;
	}
	Player* getCurrentPlayer() {
		return this->currPlayer;
	}
	bool getIsClockwise() {
		return this->isClockwise;
	}
	bool getIsUserLoosed() {
		return this->isUserLoosed;
	}
	bool getIsUserWon() {
		return this->isUserWon;
	}
	bool getIsSnowballMode() {
		return this->isSnowballMode;
	}
	Deck* getStockCards() {
		return this->stockCards;
	}
	int getPlayersAmount() {
		return this->playersAmount;
	}
	bool getIsCurrStepMustBeSkiped() {
		return this->isCurrStepMustBeSkiped;
	}
	string getUserName() {
		return playerName;
	}
	string getCurrSuet() {
		return this->currentSuet;
	}
	void InitiateNewGame(int playersAmount, int startCardsAmount, string playerName) {
		this->playerName = playerName;
		this->playersAmount = playersAmount;
		this->startCardsAmount = startCardsAmount;
		stockCards = new Deck();
		//currAllovedSuit = "";
		if (playedCards.size() != 0) {
			playedCards.clear();
		}
		if (playersInGame.size() != 0) {
			playersInGame.clear();
		}
		isClockwise = true;
		isItFirstStep = true;
		isCardPlayed = false;
		isCardTaken = false;
		isSnowballMode = false;
		isCurrStepMustBeSkiped = false;
		cardsMustBeTakenCurrent = false;
		isNextStepMustBeSkiped = false;
		cardsMustBeTakenNext = false;
		isUserLoosed = false;
		isUserWon = false;
		firstPlayerToStep = rand() % ((playersAmount - 1) - 0 + 1) + 0;


		Player* player = new Player(playerName);
		playersInGame.push_back(player);
		wxString stringnumber;
		for (int i = 1; i < playersAmount; i++) {
			stringnumber = wxString::Format(wxT("%d"), (int)(i + 1));
			string str = "P" + stringnumber.ToStdString();
			player = new Player(str);
			playersInGame.push_back(player);
		}

		for (int i = 0; i < playersAmount; i++) {
			for (int j = 0; j < startCardsAmount; j++) {
				playersInGame[i]->addCard(stockCards->pop_front());
			}
		}

		currPlayer = playersInGame[firstPlayerToStep];
	}
	GameProcess(int playersAmount, int startCardsAmount, string playerName) {
		InitiateNewGame(playersAmount, startCardsAmount, playerName);
	}
	GameProcess() {}
	bool isStepCanBeEnded() {
		if (isCardPlayed) {
			return true;
		}
		else if (cardsMustBeTakenCurrent == 0 and isCardTaken) {
			return true;
		}
		else if (isCurrStepMustBeSkiped and cardsMustBeTakenCurrent == 0) {
			return true;
		}
		return false;
	}
	int getPlayerCardsAmount() {
		return playedCards.size();
	}
	int getCardsMustBeTakenCurrent() {
		return cardsMustBeTakenCurrent;
	}
	void endStep() {
		if (currPlayer->getAvailableCards().size() == 0) {
			startNewRound();
			if (isUserWon or isUserLoosed) {
				return;
			}
		}
		else {
			currPlayer = getNextPlayer();
			isCardPlayed = false;
			isCardTaken = false;
			isCurrStepMustBeSkiped = isNextStepMustBeSkiped;
			isNextStepMustBeSkiped = false;
			cardsMustBeTakenCurrent = cardsMustBeTakenNext;
			cardsMustBeTakenNext = 0;

			if (currPlayer->getName() == getUserName() and !isCurrStepMustBeSkiped) {
				if (!isPlayerHaveAppropriateCard(currPlayer)) {
					isCurrStepMustBeSkiped = true;
					if (isSnowballMode) {
						isSnowballMode = false;
						if (playedCards[playedCards.size() - 1].getMass() > stockCards->getSize()) {
							for (int i = 0; i < stockCards->getSize(); i++) {
								cardsMustBeTakenCurrent++;
							}
						}
						else {
							for (int i = 0; i < playedCards[playedCards.size() - 1].getMass(); i++) {
								cardsMustBeTakenCurrent++;
							}
						}
					}
					else {
						cardsMustBeTakenCurrent++;
					}
				}
			}
		}
	}
	vector<Player*> getPlayersInGame() {
		return playersInGame;
	}
	bool isCardCanBePlayed(Card card) {
		if (this->isItFirstStep) {
			return true;
		}
		Card prevCard = playedCards[playedCards.size() - 1];

		if (card.getMass() == 15) {
			if (isSnowballMode and prevCard.getMass() == 14) {
				return false;
			}
			else {
				return true;
			}
		}
		if (!isCardPlayed) {

			if (isSnowballMode and card.getMass() != prevCard.getMass() + 1) {
				return false;
			}
			if (isSnowballMode and card.getSuit() != currentSuet) {
				return false;
			}
			if (isSnowballMode and prevCard.getMass() == 14) {
				return false;
			}

			if (card.getMass() == 8 and !isCardPlayed) {
				return true;
			}

			if (!isSnowballMode and (prevCard.getMass() == 5 or prevCard.getMass() == 6 or prevCard.getMass() == 7)) {
				if (card.getMass() == 4 and card.getSuit() == currentSuet) {
					return true;
				}
			}

			if (!isSnowballMode and currentSuet != card.getSuit() and card.getMass() != prevCard.getMass()) {
				return false;
			}

			return true;
		}
		else {
			if (isSnowballMode and card.getSuit() != currentSuet) {
				return false;
			}
			if (isSnowballMode and card.getMass() != prevCard.getMass() + 1) {
				return false;
			}
			if (isSnowballMode and prevCard.getMass() == 14) {
				return false;
			}
			if (!isSnowballMode and (prevCard.getMass() == 5 or prevCard.getMass() == 6 or prevCard.getMass() == 7)) {
				if (card.getMass() == 4 and card.getSuit() == currentSuet) {
					return true;
				}
			}
			if (!isSnowballMode and isCardPlayed and prevCard.getMass() == 3) {
				return true;
			}
			if (!isSnowballMode and card.getMass() != prevCard.getMass()) {
				return false;
			}
			return true;
		}
	}
	bool isPlayerHaveAppropriateCard(Player* player) {
		vector<Card> cards = player->getAvailableCards();
		for (int i = 0; i < cards.size(); i++) {
			if (isCardCanBePlayed(cards[i])) {
				return true;
			}
		}
		return false;
	}
	// AI (smarter than you)
	void makeMoveForBot() {
		if (isCurrStepMustBeSkiped) {
			for (int i = 0; i < cardsMustBeTakenCurrent; i++) {
				currPlayer->addCard(stockCards->pop_front());
			}
			endStep();
		}
		else if (!isPlayerHaveAppropriateCard(currPlayer) and !isCardPlayed) {
			if (isSnowballMode) {
				isSnowballMode = false;
				if (playedCards[playedCards.size() - 1].getMass() <= stockCards->getSize()) {
					for (int i = 0; i < playedCards[playedCards.size() - 1].getMass(); i++) {
						currPlayer->addCard(stockCards->pop_front());
					}
				}
				else {
					for (int i = 0; i < stockCards->getSize(); i++) {
						currPlayer->addCard(stockCards->pop_front());
					}
				}
			}
			else {
				for (int i = 0; i < cardsMustBeTakenCurrent; i++) {
					currPlayer->addCard(stockCards->pop_front());
				}
			}
			endStep();
		}
		else if (!isPlayerHaveAppropriateCard(currPlayer) and isCardPlayed) {
			endStep();
		}
		else if (isPlayerHaveAppropriateCard(currPlayer)) {
			Card card = getCardToStep(currPlayer);
			int cardID = 0;
			for (int i = 0; i < currPlayer->getAvailableCards().size(); i++) {
				if (currPlayer->getAvailableCards()[i] == card) {
					cardID = i;
					break;
				}
			}
			if (card.getMass() == 8) {
				if (currPlayer->getAvailableCards().size() != 1) {
					string suit = getCardToStep(currPlayer).getSuit();
					makeStep(cardID, suit);
				}
				else {
					makeStep(cardID, SUITS[0]);
				}
			}

			else if (card.getMass() == 15) {
				if (isItFirstStep) {
					currPlayer->getCard(cardID);
					Card jokerCard(SUITS[0], 3);
					currPlayer->addCard(jokerCard);
					for (int i = 0; i < currPlayer->getAvailableCards().size(); i++) {
						if (jokerCard == currPlayer->getAvailableCards()[i]) {
							cardID = i;
							break;
						}
					}
					makeStep(cardID, "");
				}
				else {
					currPlayer->getCard(cardID);
					if (isSnowballMode) {
						Card jokerCard(playedCards[playedCards.size() - 1].getSuit(), playedCards[playedCards.size() - 1].getMass() + 1);
						currPlayer->addCard(jokerCard);
						for (int i = 0; i < currPlayer->getAvailableCards().size(); i++) {
							if (jokerCard == currPlayer->getAvailableCards()[i]) {
								cardID = i;
								break;
							}
						}
						if (jokerCard.getMass() == 8) {
							if (getCardToStep(currPlayer).getMass() != 15) {
								makeStep(cardID, getCardToStep(currPlayer).getSuit());
							}
							else {
								Card secondJoler = getCardToStep(currPlayer);
								for (int i = 0; i < currPlayer->getAvailableCards().size(); i++) {
									if (currPlayer->getAvailableCards()[i] == jokerCard) {
										currPlayer->getCard(i);
									}
								}
								makeStep(cardID, getCardToStep(currPlayer).getSuit());
								currPlayer->addCard(secondJoler);
							}
						}
					}
					else {
						if (getCardToStep(currPlayer).getMass() != 15) {
							Card jokerCard(playedCards[playedCards.size() - 1].getSuit(), 3);
							currPlayer->addCard(jokerCard);
							for (int i = 0; i < currPlayer->getAvailableCards().size(); i++) {
								if (jokerCard == currPlayer->getAvailableCards()[i]) {
									cardID = i;
									break;
								}
							}
							makeStep(cardID, "");
						}
						else {
							Card jokerCard(playedCards[playedCards.size() - 1].getSuit(), 2);
							currPlayer->addCard(jokerCard);
							for (int i = 0; i < currPlayer->getAvailableCards().size(); i++) {
								if (jokerCard == currPlayer->getAvailableCards()[i]) {
									cardID = i;
									break;
								}
							}
							makeStep(cardID, "");

							for (int i = 0; i < currPlayer->getAvailableCards().size(); i++) {
								if (currPlayer->getAvailableCards()[i].getMass() == 15) {
									currPlayer->getCard(i);
									break;
								}
							}
							Card secondJokerCard(playedCards[playedCards.size() - 1].getSuit(), 3);
							currPlayer->addCard(secondJokerCard);
							for (int i = 0; i < currPlayer->getAvailableCards().size(); i++) {
								if (secondJokerCard == currPlayer->getAvailableCards()[i]) {
									cardID = i;
									break;
								}
							}
							makeStep(cardID, "");
						}
					}
				}
			}
			else {
				makeStep(cardID, "");
			}
		}
	}
	void makeStep(int card_ID, string newSuit) {
		Card choosenCard = currPlayer->getCard(card_ID);
		playedCards.push_back(choosenCard);

		if (choosenCard.getMass() == 2) {
			isNextStepMustBeSkiped = true;
			cardsMustBeTakenNext++;
			if (stockCards->getSize() < cardsMustBeTakenNext) {
				cardsMustBeTakenNext = stockCards->getSize();
			}
		}
		else if (choosenCard.getMass() == 4) {
			isSnowballMode = true;
		}
		else if (choosenCard.getMass() == 8) {
			currentSuet = newSuit;
			if (isItFirstStep) {
				isItFirstStep = false;
			}
			if (!isCardPlayed) {
				isCardPlayed = true;
			}
			return;
		}
		else if(choosenCard.getMass() == 11){
			isNextStepMustBeSkiped = true;
		}
		else if (choosenCard.getMass() == 14) {
			if (isClockwise) {
				isClockwise = false;
			}
			else {
				isClockwise = true;
			}
		}
		if (isItFirstStep) {
			isItFirstStep = false;
		}
		if (!isCardPlayed) {
			isCardPlayed = true;
		}
		currentSuet = choosenCard.getSuit();
	}
};

