#include "Common.h"
#include "NewGameForm.h"
#include "OptionsForm.h"
#include "PitchApp.h"
#include "TableInfoForm.h"

#include "GameManager.h"

extern GameManager *gManager;

Boolean CNewGameForm::OnOpen(EventPtr pEvent, Boolean& bHandled) {

	p0name.Attach(this, SetPlayer0Name);
	p1name.Attach(this, SetPlayer1Name);
	p2name.Attach(this, SetPlayer2Name);
	p3name.Attach(this, SetPlayer3Name);
	winning_score.Attach(this, SetWinningScore);

	p0name.Replace(gManager->player_names[0]);
	p1name.Replace(gManager->player_names[1]);
	p2name.Replace(gManager->player_names[2]);
	p3name.Replace(gManager->player_names[3]);

	char winscore[10];
	StrPrintF(winscore, "%d", gManager->winning_score );
	winning_score.Replace(winscore);

	bHandled = false;
	return false;
}


Boolean CNewGameForm::OnClose(EventPtr pEvent, Boolean& bHandled) {

	p0name.Detach();
	p1name.Detach();
	p2name.Detach();
	p3name.Detach();
	winning_score.Detach();

	bHandled = false;
	return false;
}

Boolean CNewGameForm::OnGameOptions(EventPtr pEvent, Boolean& bHandled) {
	COptionsDialog frmPrefs;
	frmPrefs.DoModal();
	return true;
}

Boolean CNewGameForm::OnOK(EventPtr pEvent, Boolean& bHandled) {

	gManager->Reset();
	gManager->NewGame();

	if ( p0name.GetTextPtr() ) {
		CString tmp1 = p0name.GetTextPtr();
		gManager->players[0]->name = tmp1;
		gManager->player_names[0] = tmp1;
	}


	if ( p1name.GetTextPtr() ) {
		CString tmp2 = p1name.GetTextPtr();
		gManager->players[1]->name = tmp2;
		gManager->player_names[1] = tmp2;
	}

	if ( p2name.GetTextPtr() ) {
		CString tmp3 = p2name.GetTextPtr();
		gManager->players[2]->name = tmp3;
		gManager->player_names[2] = tmp3;
	}

	if ( p3name.GetTextPtr() ) {
		CString tmp4 = p3name.GetTextPtr();
		gManager->players[3]->name = tmp4;
		gManager->player_names[3] = tmp4;
	}
	const Char *tmp = winning_score.GetTextPtr();

	if ( tmp ) {
		gManager->winning_score = StrAToI( tmp );
	}
					
	if ( gManager->winning_score <= 0 ) {
		gManager->winning_score = 1;
	}

	// let's track the number of games played
	gManager->games_played++;

	gManager->Status(NewGame);
	
	if ( gManager->first_game == true ) {
		Int16 rand_dealer = SysRandom(0) % gManager->numPlayers;
		gManager->tbl->Dealer(gManager->players.BeginIterator() + rand_dealer );
		gManager->first_game = false;
	}

	gManager->DealHands();

	CTableInfoDialog frmInfo;
	frmInfo.DoModal();

	if ( ! IsRegistered() && GetDaysSinceFirst() > 3	) {
		CForm::GotoForm(RegAnnoyer);
	}
	else {
		CForm::GotoForm(BiddingForm);
	}

	bHandled = true;
	return true;
}

Boolean CNewGameForm::OnCancel(EventPtr pEvent, Boolean& bHandled) {

	CForm::GotoForm(MainForm);

	bHandled = true;
	return true;
}


Boolean CNewGameForm::OnHelp(EventPtr pEvent, Boolean& bHandled) {
	FrmHelp(InstructionsString);
	return true;
}

Boolean CNewGameForm::OnAbout(EventType* pEvent, Boolean& bHandled) {

	CAboutDialog frmAbout;
	frmAbout.DoModal();
	
	bHandled = false;
	return true;
}


