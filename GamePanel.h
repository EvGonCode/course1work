#pragma once
#include <wx/wx.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/sound.h>
#include "resource.h"
#include "Music.h"




class GamePanel : public wxPanel
{
public:
	wxPanel* parrentPanel;
	wxButton* btnMuteMusic;
	wxButton* btnExitToMenu;
	wxButton* btnOnGuide;
	wxButton* btnOnPlayCard;
	wxButton* btnOnTakeCard;
	wxButton* btnOnEndStep;

	wxPanel* cardsPanel;
	wxTextCtrl* cardsTxt;
	wxTextCtrl* userSelectedCardTxt;

	wxPanel* selectNewSuitPanel;
	wxButton* btnOnSeletcDiamonds;
	wxButton* btnOnSeletcHearts;
	wxButton* btnOnSeletcClubs;
	wxButton* btnOnSeletcSpades;
	string selectedSuit;
	void hideSelectSuitButton();
	void showSelectSuitButton();

	wxTextCtrl* playedCardsTxt;
	wxTextCtrl* gameDirectionTxt;
	wxTextCtrl* currentPlayerNameTxt;
	wxTextCtrl* stockCardsAmountTxt;
	wxTextCtrl* cardsmustBeTakenAmountTxt;
	wxTextCtrl* currSuetTxt;
	wxTextCtrl* currStepMustBeSkippedTxt;
	wxTextCtrl* isSnowballModeTxt;

	wxTextCtrl* allawedCardsToStep; //tests

	vector<wxTextCtrl*> botsTxt;

	bool isMuted;
	wxSound* sound;

	GamePanel(wxPanel* parent);
	~GamePanel();

public:
	void OnMuteMusic(wxCommandEvent& event);
	void OnExitToMenu(wxCommandEvent& event);
	void OnGuide(wxCommandEvent& event);
	void OnPlayCard(wxCommandEvent& event);
	void OnTakeCard(wxCommandEvent& event);
	void OnEndStep(wxCommandEvent& event);

	void OnSeletcDiamonds(wxCommandEvent& event);
	void OnSeletcHearts(wxCommandEvent& event);
	void OnSeletcClubs(wxCommandEvent& event);
	void OnSeletcSpades(wxCommandEvent& event);

	void displayUserCards();
	void displayGameDirection();
	void displayPlayedCards();
	void displayNameOfCurrentPlayer();
	void displayStockCardsAmount();
	void displaycardsmustBeTakenAmount();
	void displayBotPlayers();
	void displayCurrSuet();
	void displayCurrStepMustBeSkipped();
	void displayIsSnowballMode();
	void displayAllawedCardsToStep(); // tests
	void refreshInfo();

	void deleteBotsTxt();
	void rollStepsToUser(wxCommandEvent& event);
};

