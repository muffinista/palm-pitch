// PitchApp.h
//
// This file implements any methods CPitchApp
// that differ from the standard implementation in CPalmApp

// Declaration of Application class
#ifndef PITCHAPP_H_
#define PITCHAPP_H_

#include "MainForm.h"
#include "NewGameForm.h"
#include "NewCTGameForm.h"
#include "TableInfoForm.h"
#include "TableCTInfoForm.h"
#include "BiddingForm.h"
#include "PrefsForm.h"
#include "ScoringForm.h"
#include "PlayerTrumpForm.h"
#include "GameForm.h"
#include "AboutForm.h"
#include "GameOverForm.h"
#include "Protect.h"
#include "ChooseGameTypeForm.h"

#define CreatorID 'JVpp'

#define PrefID 'GDTA'
#define PrefVersion 0x2007


#define RegPrefID				0x03
#define RegPrefVersionNum		0x03


// Application class
class CPitchApp : public CPalmApp {

public:
	// Overrides
	virtual Err NormalLaunch();
//	Boolean PreSystemEventHook(EventType *pEvent); 

	Err InitInstance();
	Err ExitInstance();
	static CPitchApp * GetInstance();
	
	void DisplayAnnoyForm();

	// Form map
	BEGIN_FORM_MAP()
		FORM_MAP_ENTRY( MainForm, CMainForm )
		FORM_MAP_ENTRY( GameOverForm, CGameOverForm)
		FORM_MAP_ENTRY( NewGameForm, CNewGameForm )
		FORM_MAP_ENTRY( NewCTGameForm, CNewCTGameForm )
		FORM_MAP_ENTRY( TableInfoForm, CTableInfoDialog )
		FORM_MAP_ENTRY( TableCTInfoForm, CTableCTInfoDialog )
		FORM_MAP_ENTRY( BiddingForm, CBiddingForm )
		FORM_MAP_ENTRY( PrefsForm, CPrefsDialog )
		FORM_MAP_ENTRY( ChooseGameTypeForm, CChooseGameTypeDialog )
		FORM_MAP_ENTRY( ScoringForm, CScoringForm )
		FORM_MAP_ENTRY( PlayerTrumpForm, CPlayerTrumpForm )
		FORM_MAP_ENTRY( GameForm, CGameForm )
		FORM_MAP_ENTRY( AboutForm, CAboutDialog )
		FORM_MAP_ENTRY( RegAnnoyer, CAnnoyForm )

	END_FORM_MAP()
	
private:
//	Boolean no_annoy_yet;

};

#endif // PITCHAPP_H_
