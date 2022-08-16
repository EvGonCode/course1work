#include "GamePanel.h"
#include "MenuPanel.h"
#include "cMain.h"
#include <string>
#include <format>
using namespace std;

const int ID_B_EXITTOMENU = 100;
const int ID_B_MUTEMUSIC = 101;
const int ID_B_GUIDE = 102;
const int ID_B_PLAYCARD = 103;
const int ID_B_TAKECARD = 104;
const int ID_B_ENDSTEP = 105;
const int ID_B_SELECTDIAMONDS = 106;
const int ID_B_SELECTHEARTS = 107;
const int ID_B_SELECTCLUBS = 108;
const int ID_B_SELECTSPADES = 109;
const int ID_P_CARDSPANEL = 302;
const int ID_P_SELECTNEWSUITPANEL = 303;


GamePanel::GamePanel(wxPanel* parent) : wxPanel(parent, wxID_ANY, wxPoint(0, 0), wxSize(800, 600)) {
	parrentPanel = parent;

	//menu
	isMuted = false;

	btnMuteMusic = new wxButton(this, ID_B_MUTEMUSIC, wxT(" "), wxPoint(730, 10), wxSize(40, 40));
	btnExitToMenu = new wxButton(this, ID_B_EXITTOMENU, wxT("Exit"), wxPoint(20, 515));
	btnOnGuide = new wxButton(this, ID_B_GUIDE, wxT("Guide"), wxPoint(720, 540), wxSize(50, 20));
	btnOnTakeCard = new wxButton(this, ID_B_TAKECARD, wxT("Take card"), wxPoint(550, 330), wxSize(70, 20));
	btnOnEndStep = new wxButton(this, ID_B_ENDSTEP, wxT("End step"), wxPoint(670, 80), wxSize(100, 300));

	btnMuteMusic->SetBitmap(wxICON(icon_unmute));
	sound->Play(music_DOOM, wxSOUND_ASYNC | wxSOUND_LOOP);

	btnMuteMusic->Bind(wxEVT_BUTTON, &GamePanel::OnMuteMusic, this);
	btnExitToMenu->Bind(wxEVT_BUTTON, &GamePanel::OnExitToMenu, this);
	btnOnGuide->Bind(wxEVT_BUTTON, &GamePanel::OnGuide, this);
	btnOnTakeCard->Bind(wxEVT_BUTTON, &GamePanel::OnTakeCard, this);
	btnOnEndStep->Bind(wxEVT_BUTTON, &GamePanel::OnEndStep, this);




	//Game table
	playedCardsTxt = new wxTextCtrl(this, wxID_ANY, wxT(""), wxPoint(300, 150), wxSize(150, 200), wxTE_MULTILINE | wxTE_READONLY);
	currentPlayerNameTxt = new wxTextCtrl(this, wxID_ANY, wxT(""), wxPoint(200, 310), wxSize(100, 20), wxTE_READONLY);
	gameDirectionTxt = new wxTextCtrl(this, wxID_ANY, wxT(""), wxPoint(200, 330), wxSize(100, 20), wxTE_READONLY);
	stockCardsAmountTxt = new wxTextCtrl(this, wxID_ANY, wxT(""), wxPoint(450, 310), wxSize(100, 20), wxTE_READONLY);
	cardsmustBeTakenAmountTxt = new wxTextCtrl(this, wxID_ANY, wxT(""), wxPoint(450, 330), wxSize(100, 20), wxTE_READONLY);
	currSuetTxt = new wxTextCtrl(this, wxID_ANY, wxT(""), wxPoint(200, 290), wxSize(100, 20), wxTE_READONLY);
	currStepMustBeSkippedTxt = new wxTextCtrl(this, wxID_ANY, wxT(""), wxPoint(180, 270), wxSize(120, 20), wxTE_READONLY);
	isSnowballModeTxt = new wxTextCtrl(this, wxID_ANY, wxT(""), wxPoint(180, 250), wxSize(120, 20), wxTE_READONLY);

	allawedCardsToStep = new wxTextCtrl(this, wxID_ANY, wxT(""), wxPoint(0, 50), wxSize(150, 400), wxTE_MULTILINE | wxTE_READONLY); // tests



	//User cards panel
	cardsPanel = new wxPanel(this, ID_P_CARDSPANEL, wxPoint(160, 400), wxSize(500, 140));

	cardsTxt = new wxTextCtrl(cardsPanel, wxID_ANY, wxT(""), wxPoint(-1, -1), wxSize(400, 140), wxTE_MULTILINE | wxTE_READONLY);
	wxFont font(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_LIGHT, false);
	cardsTxt->SetFont(font);
	userSelectedCardTxt = new wxTextCtrl(cardsPanel, wxID_ANY, wxT(""), wxPoint(400, -1), wxSize(100, 20));

	btnOnPlayCard = new wxButton(cardsPanel, ID_B_PLAYCARD, wxT("put"), wxPoint(400, 20), wxSize(100, 20));
	btnOnPlayCard->Bind(wxEVT_BUTTON, &GamePanel::OnPlayCard, this);



	//Select new suit panel
	selectNewSuitPanel = new wxPanel(this, ID_P_SELECTNEWSUITPANEL, wxPoint(160, 400), wxSize(500, 140));

	btnOnSeletcDiamonds = new wxButton(selectNewSuitPanel, ID_B_SELECTDIAMONDS, wxT("Diamonds"), wxPoint(0, 0), wxSize(125, 140));
	btnOnSeletcHearts = new wxButton(selectNewSuitPanel, ID_B_SELECTHEARTS, wxT("Hearts"), wxPoint(125, 0), wxSize(125, 140));
	btnOnSeletcClubs = new wxButton(selectNewSuitPanel, ID_B_SELECTCLUBS, wxT("Clubs"), wxPoint(250, 0), wxSize(125, 140));
	btnOnSeletcSpades = new wxButton(selectNewSuitPanel, ID_B_SELECTSPADES, wxT("Spades"), wxPoint(375, 0), wxSize(125, 140));

	btnOnSeletcDiamonds->Bind(wxEVT_BUTTON, &GamePanel::OnSeletcDiamonds, this);
	btnOnSeletcHearts->Bind(wxEVT_BUTTON, &GamePanel::OnSeletcHearts, this);
	btnOnSeletcClubs->Bind(wxEVT_BUTTON, &GamePanel::OnSeletcClubs, this);
	btnOnSeletcSpades->Bind(wxEVT_BUTTON, &GamePanel::OnSeletcSpades, this);

	hideSelectSuitButton();



}

GamePanel::~GamePanel() {

}

void GamePanel::OnMuteMusic(wxCommandEvent& event) {
	if (isMuted) {
		btnMuteMusic->SetBitmap(wxICON(icon_unmute));
		sound->Play(music_DOOM, wxSOUND_ASYNC | wxSOUND_LOOP);
		isMuted = false;
	}
	else {
		btnMuteMusic->SetBitmap(wxICON(icon_mute));
		sound->Stop();
		isMuted = true;
	}
}
void GamePanel::OnExitToMenu(wxCommandEvent& event) {
	this->Hide();
	MenuPanel* mp = (MenuPanel*)this->parrentPanel->GetChildren()[1];
	mp->Show();

	this->sound->Stop();
	if (!this->isMuted) {
		mp->isMuted = false;
		mp->btnMuteMusic->SetBitmap(wxICON(icon_unmute));
		mp->sound->Play(music_Serious_Sam, wxSOUND_ASYNC | wxSOUND_LOOP);
	}
	else {
		mp->isMuted = true;
		mp->btnMuteMusic->SetBitmap(wxICON(icon_mute));
		mp->sound->Stop();
	}

	this->cardsTxt->Clear();
	this->deleteBotsTxt();
	this->userSelectedCardTxt->Clear();
}
void GamePanel::OnGuide(wxCommandEvent& event) {
	cMain* cmain = (cMain*)parrentPanel->GetParent();
	if (cmain->isGuideOpen == false) {
		cmain->guideWindow = new GuideWindow(cmain);
		cmain->guideWindow->Show();
		cmain->isGuideOpen = true;
	}
	else {
		cmain->guideWindow->Close();
		cmain->isGuideOpen = false;
	}
}
void GamePanel::OnPlayCard(wxCommandEvent& event) {
	cMain* cmain = (cMain*)parrentPanel->GetParent();
	GameProcess* gameprocess = cmain->gameProcess;
	vector<Card> userCards = gameprocess->getCurrentPlayer()->getAvailableCards();
	int cardID = wxAtoi(userSelectedCardTxt->GetValue()) - 1;

	if (gameprocess->getCurrentPlayer()->getName() == gameprocess->getUserName()) {
		if (wxAtoi(userSelectedCardTxt->GetValue()) <= 0 or wxAtoi(userSelectedCardTxt->GetValue()) >= userCards.size()) {
			userSelectedCardTxt->SetBackgroundColour(wxColor(255, 0, 0));
		}
		else if (gameprocess->getIsCurrStepMustBeSkiped()) {
			userSelectedCardTxt->SetBackgroundColour(wxColor(255, 0, 0));
		}
		else if (!cmain->gameProcess->isCardCanBePlayed(userCards[cardID])) {
			userSelectedCardTxt->SetBackgroundColour(wxColor(255, 0, 0));
		}
		else {
			if (userCards[cardID].getMass() != 8 and userCards[cardID].getMass() != 15) {
				gameprocess->makeStep(cardID, "");
				userSelectedCardTxt->SetBackgroundColour(wxColor(255, 255, 255));
				this->refreshInfo();
			}
			else {
				if (userCards[cardID].getMass() == 8) {
					if (this->selectedSuit == "") {
						showSelectSuitButton();
					}
					else {
						Card card(selectedSuit, 8);
						if (gameprocess->isCardCanBePlayed(card)) {
							gameprocess->makeStep(cardID, selectedSuit);
							selectedSuit = "";
						}
						else {
							userSelectedCardTxt->SetBackgroundColour(wxColor(255, 0, 0));
						}
					}

				}
				this->refreshInfo();
			}
		}
	}
}
void GamePanel::OnTakeCard(wxCommandEvent& event) {
	cMain* cmain = (cMain*)parrentPanel->GetParent();
	GameProcess* gameprocess = cmain->gameProcess;

	if (gameprocess->getCardsMustBeTakenCurrent() > 0 and gameprocess->getCurrentPlayer()->getName() == gameprocess->getUserName()) {
		gameprocess->getCurrentPlayer()->addCard(gameprocess->getStockCards()->pop_front());
		gameprocess->reduceMustBeenTakenCards();
		refreshInfo();
	}
}

void GamePanel::OnSeletcDiamonds(wxCommandEvent& event) {
	this->selectedSuit = SUITS[0];
	hideSelectSuitButton();
	this->OnPlayCard(event);
}
void GamePanel::OnSeletcHearts(wxCommandEvent& event) {
	this->selectedSuit = SUITS[1];
	hideSelectSuitButton();
	this->OnPlayCard(event);
}
void GamePanel::OnSeletcClubs(wxCommandEvent& event) {
	this->selectedSuit = SUITS[2];
	hideSelectSuitButton();
	this->OnPlayCard(event);
}
void GamePanel::OnSeletcSpades(wxCommandEvent& event) {
	this->selectedSuit = SUITS[3];
	hideSelectSuitButton();
	this->OnPlayCard(event);
}
void GamePanel::hideSelectSuitButton() {
	this->selectNewSuitPanel->Hide();
	btnOnSeletcDiamonds->Hide();
	btnOnSeletcHearts->Hide();
	btnOnSeletcClubs->Hide();
	btnOnSeletcSpades->Hide();
	this->cardsPanel->Show();
}
void GamePanel::showSelectSuitButton() {
	this->selectNewSuitPanel->Show();
	btnOnSeletcDiamonds->Show();
	btnOnSeletcHearts->Show();
	btnOnSeletcClubs->Show();
	btnOnSeletcSpades->Show();
	this->cardsPanel->Hide();
}

void GamePanel::displayUserCards() {
	this->cardsTxt->Clear();
	cMain* cm = (cMain*)parrentPanel->GetParent();
	vector<Card> mainPlayerCards = cm->gameProcess->getPlayersInGame()[0]->getAvailableCards();

	for (int i = 0; i < mainPlayerCards.size(); i++) {
		if (i + 1 != mainPlayerCards.size()) {
			wxString str = wxString::Format(wxT("%d) "), (i + 1));
			str += mainPlayerCards[i].toString() + ", ";
			this->cardsTxt->WriteText(str);
		}
		else {
			wxString str = wxString::Format(wxT("%d) "), (i + 1));
			str += mainPlayerCards[i].toString();
			this->cardsTxt->WriteText(str);
		}
	}
}
void GamePanel::displayGameDirection() {
	cMain* cmain = (cMain*)parrentPanel->GetParent();
	GameProcess* gameprocess = cmain->gameProcess;

	this->gameDirectionTxt->Clear();
	if (gameprocess->getIsClockwise()) {
		this->gameDirectionTxt->WriteText(wxT("Clockwise"));
	}
	else {
		this->gameDirectionTxt->WriteText(wxT("Anticlockwise"));
	}
}
void GamePanel::displayPlayedCards() {
	cMain* cmain = (cMain*)parrentPanel->GetParent();
	GameProcess* gameprocess = cmain->gameProcess;

	this->playedCardsTxt->Clear();
	for (int i = 0; i < gameprocess->getPlayedCards().size(); i++) {
		this->playedCardsTxt->WriteText(gameprocess->getPlayedCards()[i].toString() + ", ");
	}
}
void GamePanel::displayNameOfCurrentPlayer() {
	cMain* cmain = (cMain*)parrentPanel->GetParent();
	GameProcess* gameprocess = cmain->gameProcess;

	this->currentPlayerNameTxt->Clear();
	this->currentPlayerNameTxt->WriteText(gameprocess->getCurrentPlayer()->getName());
}
void GamePanel::displayStockCardsAmount() {
	cMain* cmain = (cMain*)parrentPanel->GetParent();
	GameProcess* gameprocess = cmain->gameProcess;

	wxString stringnumber = wxString::Format(wxT("%d"), (int)gameprocess->getStockCards()->getSize());

	this->stockCardsAmountTxt->Clear();
	this->stockCardsAmountTxt->WriteText("Stock cards:" + stringnumber);
}
void GamePanel::displayBotPlayers() {
	cMain* cmain = (cMain*)parrentPanel->GetParent();
	GameProcess* gameprocess = cmain->gameProcess;

	if (botsTxt.size() == 0) {
		for (int i = 1; i < gameprocess->getPlayersAmount(); i++) {
			wxTextCtrl* botTxt = new wxTextCtrl(this, wxID_ANY, wxT(""), wxPoint(100 + 100 * i, 20), wxSize(100, 40), wxTE_READONLY | wxTE_MULTILINE);

			wxString stringnumber = wxString::Format(wxT("%d"), (int)gameprocess->getPlayersInGame()[i]->getAvailableCards().size());
			botTxt->WriteText(gameprocess->getPlayersInGame()[i]->getName() + "\n" + "Cards: " + stringnumber);

			botsTxt.push_back(botTxt);
		}
	}
	else {
		for (int i = 0; i < botsTxt.size(); i++) {
			botsTxt[i]->Clear();
		}

		for (int i = 1; i < gameprocess->getPlayersAmount(); i++) {
			wxString stringnumber = wxString::Format(wxT("%d"), (int)gameprocess->getPlayersInGame()[i]->getAvailableCards().size());

			botsTxt[i - 1]->WriteText(gameprocess->getPlayersInGame()[i]->getName() + "\n" + "Cards: " + stringnumber);
		}
	}
}
void GamePanel::displaycardsmustBeTakenAmount() {
	this->cardsmustBeTakenAmountTxt->Clear();
	cMain* cmain = (cMain*)parrentPanel->GetParent();
	GameProcess* gameprocess = cmain->gameProcess;

	wxString stringnumber = wxString::Format(wxT("%d"), (int)gameprocess->getCardsMustBeTakenCurrent());
	this->cardsmustBeTakenAmountTxt->WriteText("Must take: " + stringnumber);
}
void GamePanel::displayCurrSuet() {
	this->currSuetTxt->Clear();
	cMain* cmain = (cMain*)parrentPanel->GetParent();
	GameProcess* gameprocess = cmain->gameProcess;

	this->currSuetTxt->WriteText("Curr. suet: " + gameprocess->getCurrSuet());
}
void GamePanel::displayCurrStepMustBeSkipped() {
	this->currStepMustBeSkippedTxt->Clear();
	cMain* cmain = (cMain*)parrentPanel->GetParent();
	GameProcess* gameprocess = cmain->gameProcess;

	if (gameprocess->getIsCurrStepMustBeSkiped()) {
		this->currStepMustBeSkippedTxt->WriteText("Skip step: true");
	}
	else {
		this->currStepMustBeSkippedTxt->WriteText("Skip step: false");
	}
}
void GamePanel::displayIsSnowballMode() {
	this->isSnowballModeTxt->Clear();
	cMain* cmain = (cMain*)parrentPanel->GetParent();
	GameProcess* gameprocess = cmain->gameProcess;

	if (gameprocess->getIsSnowballMode()) {
		this->isSnowballModeTxt->WriteText("SnawballMode: true");
	}
	else {
		this->isSnowballModeTxt->WriteText("SnawballMode: false");
	}
}
//Tests
void GamePanel::displayAllawedCardsToStep() {
	this->allawedCardsToStep->Clear();
	cMain* cmain = (cMain*)parrentPanel->GetParent();
	GameProcess* gameprocess = cmain->gameProcess;

	vector<Card> cards = gameprocess->getAllowedCardsToStep();
	for (int i = 0; i < cards.size(); i++) {
		allawedCardsToStep->WriteText(cards[i].toString() + ", ");
	}
}
void GamePanel::refreshInfo() {
	displayUserCards();
	displayGameDirection();
	displayPlayedCards();
	displayNameOfCurrentPlayer();
	displayStockCardsAmount();
	displaycardsmustBeTakenAmount();
	displayBotPlayers();
	displayCurrSuet();
	displayCurrStepMustBeSkipped();
	displayIsSnowballMode();
	//Tests
	displayAllawedCardsToStep();
}
void GamePanel::deleteBotsTxt() {
	for (int i = 0; i < botsTxt.size(); i++) {
		botsTxt[i]->Clear();
		botsTxt[i]->Hide();
	}
	botsTxt.clear();
}

void GamePanel::rollStepsToUser(wxCommandEvent& event) {
	cMain* cmain = (cMain*)parrentPanel->GetParent();
	GameProcess* gameprocess = cmain->gameProcess;

	while (gameprocess->getCurrentPlayer()->getName() != gameprocess->getUserName()) {
		Sleep(1000);						//Sleep needed to let user see the game process
		gameprocess->makeMoveForBot();
		refreshInfo();
		if (gameprocess->getIsUserLoosed()) {
			OnExitToMenu(event);
			break;
		}
		else if (gameprocess->getIsUserWon()) {
			OnExitToMenu(event);
			break;
		}
	}
}
void GamePanel::OnEndStep(wxCommandEvent& event) {
	cMain* cmain = (cMain*)parrentPanel->GetParent();
	GameProcess* gameprocess = cmain->gameProcess;
	
	if (gameprocess->isStepCanBeEnded() and gameprocess->getCurrentPlayer()->getName() == gameprocess->getUserName()) {
		gameprocess->endStep();
		refreshInfo();
		rollStepsToUser(event);
	}
}