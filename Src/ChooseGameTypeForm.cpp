// MainForm.cpp
//
// This file implements the main form for
// your application.
#include <PalmOSGlue.h>

#include "Common.h"
#include "ChooseGameTypeForm.h"
#include "PitchApp.h"

#include "GameManager.h"

extern GameManager *gManager;

// Form open handler
Boolean CChooseGameTypeDialog::OnOpen(EventPtr pEvent, Boolean& bHandled) {

	UInt32 hsStatusVersion;
	
	if (FtrGet (hsFtrCreator, hsFtrIDNavigationSupported, &hsStatusVersion) == 0) {
//		FrmGlueNavObjectTakeFocus( FrmGetActiveForm(), GameTypeOKButton );
		FrmGlueNavObjectTakeFocus( FrmGetActiveForm(), GameTypeOKButton );
	}

	_cutthroat = false;

	bHandled = false;
	return true;
}


Boolean CChooseGameTypeDialog::OnOK(EventPtr pEvent, Boolean& bHandled) {

	m_GameType.Attach(this, GameStyleList);

	if ( m_GameType.GetSelection() == 0 ) {
		_cutthroat = false;
	}
	else {
		_cutthroat = true;	
	}

	m_GameType.Detach();
	
	CloseForm(true);
	return true;
}

Boolean CChooseGameTypeDialog::OnClose(EventPtr pEvent, Boolean& bHandled) {
	
	bHandled = false;
	return false;
}


Boolean CChooseGameTypeDialog::OnCancel(EventPtr pEvent, Boolean& bHandled) {
	CloseForm(false);
	return true;
}

Boolean CChooseGameTypeDialog::CutThroat() {
	return _cutthroat;
}
