//#include "BackendController.h"
//#include "cMain.h"
//using namespace std;
//
//BackendController::BackendController(wxObject* parent) {
//	this->parent = parent;
//	playersCardsBtns = new vector<wxButton*>();
//}
//
//void BackendController::displayPlayerCards() {
//	cMain* cParent = (cMain*)parent;
//
//	int size = playersCardsBtns->size();
//	for (int i = 0; i < size; i++) {
//		playersCardsBtns->at(i)->Hide();
//	}
//	for (int i = 0; i < size; i++) {
//		playersCardsBtns->erase(playersCardsBtns->begin());
//	}
//
//	for (int i = 0; gameProcess->getPlayerCardsAmount(); i++) {
//		if (i <= 4) {
//			wxButton* btn = new wxButton(cParent->gamePanel->cardsPanel, wxID_ANY, char(i), wxPoint(0, 100 * i));
//			playersCardsBtns->push_back(btn);
//		}
//		if (i <= 8 and i > 4) {
//			wxButton* btn = new wxButton(cParent->gamePanel->cardsPanel, wxID_ANY, char(i), wxPoint(20, 100 * (i - 5)));
//			playersCardsBtns->push_back(btn);
//		}
//	}
//}
//
//void BackendController::onPlayButton(int playersAmount, int startCardsAmount) {
//	this->gameProcess = new GameProcess(playersAmount, startCardsAmount, "P1");
//	displayPlayerCards();
//}
