#include "Common.h"
#include "PitchApp.h"

#include "GameManager.h"
#include "protect.h"

GameManager *gManager = NULL;

//Boolean no_exit_yet = true;

CPitchApp * CPitchApp::GetInstance() {
	return static_cast<CPitchApp *>(CPalmApp::GetInstance());
}

Err CPitchApp::InitInstance() {

	if (m_wLaunchFlags & sysAppLaunchFlagNewGlobals) {
	}
	else {
//		no_annoy_yet = true;	
	}


//	HostTraceInit();
	
	return CPalmApp::InitInstance();
}

#if 0
Boolean CPitchApp::PreSystemEventHook(EventType *pEvent) {


	if ( pEvent->eType == keyDownEvent && 
		pEvent->data.keyDown.chr == vchrFind ) {

		pEvent->eType = nilEvent;
		return true;
		
	}
	else if ( pEvent->eType == appStopEvent && 
			( no_annoy_yet || no_exit_yet ) && 
			! IsRegistered() && 
			GetDaysSinceFirst() > 3 &&
			FrmGetActiveFormID() != RegAnnoyer
			) {

		no_annoy_yet = false;
		CForm::GotoForm(RegAnnoyer);

		// if we don't mark this as a non-appStopEvent, the app will exit here
		pEvent->eType = nilEvent;
		return true;
	}
	
	return false;
}
#endif
	
Err CPitchApp::ExitInstance() {

	gManager->Save();
	delete gManager;

//	HostTraceClose();

	return CPalmApp::ExitInstance();
}

// Normal launch handler
Err CPitchApp::NormalLaunch() {

	gManager = new GameManager();
	gManager->Load();

	// turn on copy protection
	InitProtection();

	switch ( gManager->Status() ) {

		case NewGame:
			CForm::GotoForm(NewGameForm);
			break;
		case DealNewHands:
		case GetHandBids:
		case ShowBiddingResults:
		case SetHandTrump:
		case RedrawTable:
			CForm::GotoForm(BiddingForm);
			break;
		case ReadyToPlay:
		case TrickOver:
		case HandOver:
		case PlayACard:
			CForm::GotoForm(GameForm);
			break;
		case DisplayHandResults:
			CForm::GotoForm(ScoringForm);
			break;
		case PreGame:
		case GetGameInfo:
		case SetGameInfo:
		default:
			CForm::GotoForm(MainForm);
			break;
	}

	return errNone;

}
