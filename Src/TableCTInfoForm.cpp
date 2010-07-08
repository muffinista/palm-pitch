#include "Common.h"
#include "TableCTInfoForm.h"
#include "PitchApp.h"
#include "GameManager.h"

extern GameManager *gManager;

// Form open handler
Boolean CTableCTInfoDialog::OnOpenPost(EventPtr pEvent, Boolean& bHandled) {
/*
    FIELD ID TableInfoComputerPlayers  AT (7 30 120 12) USABLE LEFTALIGN FONT 0 NONEDITABLE UNDERLINED MULTIPLELINES MAXCHARS 80
    FIELD ID TableInfoHumanPlayer  AT (7 58 120 12) USABLE LEFTALIGN FONT 0 NONEDITABLE UNDERLINED MULTIPLELINES MAXCHARS 80
    BUTTON "OK" ID TableInfoOKButton AT (118 139 36 12) USABLE FRAME FONT 0
    FIELD ID TableInfoWinningScoreField AT (69 98 15 12) USABLE LEFTALIGN FONT 0 NONEDITABLE MULTIPLELINES MAXCHARS 3
    LABEL "First player to" ID TableInfoUnnamed1707Label AT (7 98) USABLE FONT 0
    LABEL "wins" ID TableInfoUnnamed1708Label AT (86 98) USABLE FONT 0
    FIELD ID TableInfoFirstDealField AT (6 84 120 12) USABLE LEFTALIGN FONT 0 NONEDITABLE MULTIPLELINES MAXCHARS 80

	CField playersField;
	CField aiField;
	CField scoreField;
	CField dealerField;

	CString player_names;
	CString human;
	char scorestr[10];
	CString dealerstr;

*/

	playersField.Attach(this, TableInfoComputerPlayers);
//	humanField.Attach(this, TableInfoHumanPlayer);
	scoreField.Attach(this, TableInfoWinningScoreField);
	dealerField.Attach(this, TableInfoFirstDealField);

	player_names.Format("%s, %s and %s", 
		(const char *)gManager->players[1]->getName(), 
		(const char *)gManager->players[2]->getName(),
		(const char *)gManager->players[0]->getName() );

//	Player *tmp =  gManager->getNextPlayer(*gManager->tbl->dealer);
	Player *tmp =  *gManager->tbl->dealer;
	dealerstr.Format("%s has the first deal", (const char *)tmp->getName() );

	StrPrintF(scorestr, "%d", gManager->winning_score );

	playersField.Replace(player_names);
//	humanField.Replace(human);
	scoreField.Replace(scorestr);
	dealerField.Replace(dealerstr);

	UInt32 hsStatusVersion;
	
	if (FtrGet (hsFtrCreator, hsFtrIDNavigationSupported, &hsStatusVersion) == 0) {
		FrmGlueNavObjectTakeFocus(FrmGetActiveForm(), TableInfoOKButton );
	}


	bHandled = false;
	return true;
}

Boolean CTableCTInfoDialog::OnClose(EventPtr pEvent, Boolean& bHandled) {

	playersField.Detach();
//	humanField.Detach();
	scoreField.Detach();
	dealerField.Detach();

	bHandled = false;
	return true;
}

Boolean CTableCTInfoDialog::OnOK(EventPtr pEvent, Boolean& bHandled) {

	CloseForm();
	return true;
}
