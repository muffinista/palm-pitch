#include "Common.h"
#include "MainForm.h"
#include "PitchApp.h"

#include "GameManager.h"

#include "AboutForm.h"
#include "OptionsForm.h"
#include "PrefsForm.h"
#include "Protect.h"
#include "WinLossRecord.h"
#include "ChooseGameTypeForm.h"

extern GameManager *gManager;

// Form open handler
Boolean CMainForm::OnOpen(EventPtr pEvent, Boolean& bHandled) {
	bHandled = false;
	return true;
}

Boolean CMainForm::OnNewGame(EventPtr pEvent, Boolean& bHandled) {
	
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

Boolean CMainForm::OnPrefs(EventPtr pEvent, Boolean& bHandled) {
	CPrefsDialog frmPrefs;
	frmPrefs.DoModal();
	return true;
}

Boolean CMainForm::OnGameOptions(EventPtr pEvent, Boolean& bHandled) {
	COptionsDialog frmPrefs;
	frmPrefs.DoModal();
	return true;
}

Boolean CMainForm::OnHelp(EventPtr pEvent, Boolean& bHandled) {
	FrmHelp(InstructionsString);
	return true;
}

Boolean CMainForm::OnRegister(EventPtr pEvent, Boolean& bHandled) {

	while ( load_reg_form() ) {}
	return true;
}

Boolean CMainForm::OnViewWinTotals(EventType* pEvent, Boolean& bHandled) {

	CWinLossDialog frmWinLoss;
	frmWinLoss.DoModal();

	CForm::DrawForm();
	
	bHandled = false;
	return true;
}

Boolean CMainForm::OnAbout(EventType* pEvent, Boolean& bHandled) {

	CAboutDialog frmAbout;
	frmAbout.DoModal();
	
	bHandled = false;
	return true;
}