#include "Common.h"
#include "GameManager.h"
#include "WinLossRecord.h"
#include "PitchApp.h"

extern GameManager *gManager;

Boolean CWinLossDialog::OnOK(EventPtr pEvent, Boolean& bHandled) {
	CloseForm();
	return true;
}

Boolean CWinLossDialog::OnResetScores(EventPtr pEvent, Boolean& bHandled) {

	gManager->games_won[0] = 0;
	gManager->games_won[1] = 0;
	gManager->games_won[2] = 0;

	CloseForm();
	return true;
}

Boolean CWinLossDialog::OnOpenPost(EventPtr pEvent, Boolean& bHandled) {

	m_ns_games_Field.Attach(this, GamesWon);
	m_ew_games_Field.Attach(this, GamesLost);

	char ns_score[10];
	char ew_score[10];

	StrPrintF(ns_score, "%d", gManager->games_won[0] );
	StrPrintF(ew_score, "%d", gManager->games_won[1] + gManager->games_won[2] );

	m_ns_games_Field.Replace(ns_score);
	m_ew_games_Field.Replace(ew_score);

	return true;
}

Boolean CWinLossDialog::OnClose(EventPtr pEvent, Boolean& bHandled) {

	m_ns_games_Field.Detach();
	m_ew_games_Field.Detach();

	return false;
}
