#include "Common.h"
#include "GameOverForm.h"
#include "PitchApp.h"

#include "GameManager.h"

extern GameManager *gManager;

// Form open handler
Boolean CGameOverForm::OnOpen(EventPtr pEvent, Boolean& bHandled) {

	gManager->Status(GameOver);

	m_winners.Attach(this, GameResultsField);

	// figure out who won and what the score was
	
	CString winners;

	if ( gManager->CutThroat() == true ) {

		winners.Format("%s wins, %d to %d to %d!", 
			(const char *)gManager->GetWinner()->getName(), 
			gManager->scores[0], gManager->scores[1], gManager->scores[2] );
	
	}
	else {

		winners.Format("%s and %s win, %d to %d!", 
			(const char *)gManager->GetWinner()->getName(), 
			(const char *)gManager->GetWinner()->partner->getName(),
			gManager->scores[0], gManager->scores[1] );

	}

	m_winners.Replace(winners);

	bHandled = false;
	return true;
}

Boolean CGameOverForm::OnNewGame(EventPtr pEvent, Boolean& bHandled) {

	CChooseGameTypeDialog frmGT;

	if ( frmGT.DoModal() ) {

		if ( frmGT.CutThroat() ) {
			gManager->CutThroat(true);
			CForm::GotoForm(NewCTGameForm);
		}
		else {
			gManager->CutThroat(false);
			CForm::GotoForm(NewGameForm);
		}
	}
	return true;
}

Boolean CGameOverForm::OnExit(EventPtr pEvent, Boolean& bHandled) {

	m_winners.Detach();

	gManager->Reset();
	CForm::GotoForm(MainForm);
	return true;
}
