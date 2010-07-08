#include "Common.h"
#include "TableInfoForm.h"
#include "PitchApp.h"
#include "GameManager.h"

extern GameManager *gManager;

// Form open handler
Boolean CTableInfoDialog::OnOpenPost(EventPtr pEvent, Boolean& bHandled) {

	ns_teamField.Attach(this, TableInfoNorthSouthTeamField);
	ew_teamField.Attach(this, TableInfoEastWestTeamField);
	scoreField.Attach(this, TableInfoWinningScoreField);
	dealerField.Attach(this, TableInfoFirstDealField);

	ns_team.Format("%s and %s", (const char *)gManager->players[0]->getName(), (const char *)gManager->players[2]->getName() );
	ew_team.Format("%s and %s", (const char *)gManager->players[1]->getName(), (const char *)gManager->players[3]->getName() );

//	Player *tmp =  gManager->getNextPlayer(*gManager->tbl->dealer);
	Player *tmp =  *gManager->tbl->dealer;
	dealerstr.Format("%s has the first deal", (const char *)tmp->getName() );
//	dealerstr.Format("%s has the first deal", (const char *)(*gManager->tbl->dealer)->getName() );

	StrPrintF(scorestr, "%d", gManager->winning_score );

	ns_teamField.Replace(ns_team);
	ew_teamField.Replace(ew_team);
	scoreField.Replace(scorestr);
	dealerField.Replace(dealerstr);

	UInt32 hsStatusVersion;
	
	if (FtrGet (hsFtrCreator, hsFtrIDNavigationSupported, &hsStatusVersion) == 0) {
		FrmGlueNavObjectTakeFocus(FrmGetActiveForm(), TableInfoOKButton );
	}


	bHandled = false;
	return true;
}

Boolean CTableInfoDialog::OnClose(EventPtr pEvent, Boolean& bHandled) {

	ns_teamField.Detach();
	ew_teamField.Detach();
	scoreField.Detach();
	dealerField.Detach();

	bHandled = false;
	return true;
}

Boolean CTableInfoDialog::OnOK(EventPtr pEvent, Boolean& bHandled) {

	CloseForm();
	return true;
}
