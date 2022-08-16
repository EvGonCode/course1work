//#include "LeftPanel.h"
//#include "cMain.h"
//using namespace std;
//const int ID_BPLUS = 101;
//const int ID_BMINUS = 102;
//const int ID_BMUTEMUSIC = 103;
//const int ID_BOPENGAME = 103;
//
//LeftPanel::LeftPanel(wxPanel* parent) : wxPanel(parent, -1, wxPoint(-1, -1), wxSize(-1, -1), wxBORDER_SUNKEN) {
//	parrentPanel = parent;
//	count = 0;
//	btnPlus = new wxButton(this, ID_BPLUS, wxT("+"), wxPoint(10, 10));
//	btnMinus = new wxButton(this, ID_BMINUS, wxT("-"), wxPoint(10, 60));
//	btnMuteMusic = new wxButton(this, ID_BMUTEMUSIC, wxT(" "), wxPoint(20, 120), wxSize(40, 40));
//	isMuted = false;
//
//	btnOpenGame = new wxButton(this, ID_BOPENGAME, wxT("Play"), wxPoint(120, 10));
//
//	btnMuteMusic->SetBitmap(wxICON(icon_unmute));
//	sound->Play(wxT("../Last_Player/Music/Serious_sam_The_first_encounter.wav"));
//
//	btnPlus->Bind(wxEVT_BUTTON, &LeftPanel::OnPlus, this);
//	btnMinus->Bind(wxEVT_BUTTON, &LeftPanel::OnMinus, this);
//	btnMuteMusic->Bind(wxEVT_BUTTON, &LeftPanel::OnMuteMusic, this);
//	btnOpenGame->Bind(wxEVT_BUTTON, &LeftPanel::OnOpenGame, this);
//}
//
//LeftPanel::~LeftPanel() {
//
//}
//
//void LeftPanel::OnMuteMusic(wxCommandEvent& event) {
//	if (isMuted) {
//		btnMuteMusic->SetBitmap(wxICON(icon_unmute));
//		sound->Play(wxT("../Last_Player/Music/Serious_sam_The_first_encounter.wav"));
//		isMuted = false;
//	}
//	else {
//		btnMuteMusic->SetBitmap(wxICON(icon_mute));
//		sound->Stop();
//		isMuted = true;
//	}
//}
//
//void LeftPanel::OnOpenGame(wxCommandEvent& event) {
//	cMain* cmain = (cMain*)parrentPanel->GetParent();
//
//	cmain->gMainWindow->Show();
//	cmain->Close();
//}
