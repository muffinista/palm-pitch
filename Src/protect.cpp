#include <PalmOS.h>
#include "Pitch_Rsc.h"
#include "GameManager.h"

extern GameManager *gManager;
extern Boolean no_exit_yet;

#include "PitchApp.h"
#include "protect.h"

const UInt32 SEED = 8346;

static Boolean IsDigit(char c) {
  if (c=='0')
    return true;
  if (c=='1')
    return true;
  if (c=='2')
    return true;
  if (c=='3')
    return true;
  if (c=='4')
    return true;
  if (c=='5')
    return true;
  if (c=='6')
    return true;
  if (c=='7')
    return true;
  if (c=='8')
    return true;
  if (c=='9')
    return true;
    
    
   return false;
}

void InitProtection() {

	RegPreferenceType v;
	UInt16 prefsSize;

	//
	// check to see if we have the right version of the preferences
	//
	// Read the saved preferences / saved-state information.
	prefsSize = sizeof(RegPreferenceType);

	if (PrefGetAppPreferences(CreatorID, RegPrefID, &v, &prefsSize, true) != 
		noPreferenceFound) {
	}
	else {
		v.install_time = TimGetTicks();

		PrefSetAppPreferences (CreatorID, RegPrefID, RegPrefVersionNum, 
			&v, sizeof (v), true);

	}

}  // InitProtection



Boolean CheckCode(const char *code) {


	if ( StrCompare(code, "RVNG30428") == 0 ) {
		return false;
	}

	if ( StrLen(code) != 9 ) {
		return false;
	}

	char nums[5];
	UInt32 text[5];
	
	nums[4] = 0;
	text[4] = 0;
	
	UInt32 numval;
	UInt32 textval;
	char checkbit = code[8];
	UInt32 checkval = 0;

	char checkstr[2];
	checkstr[0] = checkbit;
	checkstr[1] = 0;
	
	UInt32 check = StrAToI(checkstr);


	Int16 i = 0;
	Int16 j = 0;
	Int16 k = 0;

	for ( Int16 i = 0; i < 8; i++ ) {
		if ( IsDigit(code[i]) && j < 4 ) {
			nums[j] = code[i];
			j++;
		}
		else if ( k < 4 ) {
			text[k] = code[i];
			k++;
		}

		checkval ^= code[i];
	}

	checkval %= 10;

	numval = StrAToI(nums);
	textval = text[0] * text[1] * text[2] * text[3];

	textval = textval % SEED;


	if ( numval == textval ) {

		if ( checkval == check ) {
			return true;
		}
	}


	return false;

} // CheckCode


Boolean IsRegistered() {

	RegPreferenceType v;
	UInt16 prefsSize;

	//
	// check to see if we have the right version of the preferences
	//
	// Read the saved preferences / saved-state information.
	prefsSize = sizeof(RegPreferenceType);

	if (PrefGetAppPreferences(CreatorID, RegPrefID, &v, &prefsSize, true) != 
		noPreferenceFound) {

		if ( CheckCode(v.code) ) {
			return true;
		}
	}

	return false;

} // IsRegistered


void SaveCode( const char *code ) {

	RegPreferenceType v;
	UInt16 prefsSize;

	//
	// check to see if we have the right version of the preferences
	//
	// Read the saved preferences / saved-state information.
	prefsSize = sizeof(RegPreferenceType);

	if (PrefGetAppPreferences(CreatorID, RegPrefID, &v, &prefsSize, true) != 
		noPreferenceFound) {
		v.install_time = TimGetTicks();
	}

	StrCopy(v.code, code);

	PrefSetAppPreferences (CreatorID, RegPrefID, RegPrefVersionNum, 
		&v, sizeof (v), true);

} // SaveCode


UInt32 GetDaysSinceFirst() {
	UInt32 tmp = 0;

	RegPreferenceType v;
	UInt16 prefsSize;


	//
	// check to see if we have the right version of the preferences
	//
	// Read the saved preferences / saved-state information.
	prefsSize = sizeof(RegPreferenceType);

	if (PrefGetAppPreferences(CreatorID, RegPrefID, &v, &prefsSize, true) != 
		noPreferenceFound) {
		tmp = ( TimGetTicks() - v.install_time ) / 3600L  / 24L;
	}

	return tmp;
//	return 5;

} // GetDaysSinceFirst




Boolean CAnnoyForm::OnContinue(EventPtr pEvent, Boolean& bHandled) {
/*//	no_exit_yet = false;

	EventType evt;
	evt.eType = appStopEvent;
	EvtAddEventToQueue(&evt);
*/
	CForm::GotoForm(BiddingForm);
	return true;
}

Boolean CAnnoyForm::OnRegister(EventPtr pEvent, Boolean& bHandled) {
	while ( load_reg_form() ) {}
	return true;
}

Boolean CAnnoyForm::OnOpen(EventPtr pEvent, Boolean& bHandled) {

	m_pleaField.Attach(this, PleaField);
	m_gamesField.Attach(this, GamesPlayedField);

	h = DmGetResource('tSTR', PleaString );

	if ( h ) {
		char * s = (char*)MemHandleLock(h);
		m_pleaField.Replace(s);
	}

	FormPtr frmP = FrmGetActiveForm();

	//
	// lock the continue button
	//
	ControlPtr OKButtonPtr = (ControlType *)FrmGetObjectPtr( frmP, FrmGetObjectIndex( frmP, AnnoyContinueButton ));

	CtlSetEnabled((ControlType *)OKButtonPtr, false);	
	CtlHideControl((ControlType *)OKButtonPtr);

	FrmDrawForm( frmP );

	EventType event;
	Err error;

	EvtGetEvent(&event, 0 );

	Int16 i = 0;
	char count[10];

	Boolean exit = false;
	Boolean enabled = false;

	//
	// only track events until we've hit our games played count, then
	// turn back over to the regular loop
	//
	while ( ! exit && ! enabled ) {
	
		if ( i <= gManager->games_played ) {
			StrPrintF(count, "%d", i );
			m_gamesField.Replace( count );
			i++;
		}
		
		if ( ! enabled && ( i * 2 >= gManager->games_played ) ) {
			enabled = true;
			CtlSetEnabled((ControlType *)OKButtonPtr, true);	
			CtlShowControl((ControlType *)OKButtonPtr);

//			no_exit_yet = false;
		}
		

		if (! SysHandleEvent(&event))
			if (! MenuHandleEvent(0, &event, &error))
					FrmDispatchEvent(&event);

		EvtGetEvent(&event, SysTicksPerSecond() / 10L );

	}


	//
	// re-queue the event so it gets sent and the user exits
	//
	if ( event.eType != appStopEvent ) {
		EvtAddEventToQueue (&event);
	}

	return true;
}

Boolean CAnnoyForm::OnClose(EventPtr pEvent, Boolean& bHandled) {

	m_pleaField.Detach();
	m_gamesField.Detach();

	MemHandleUnlock(h);
	DmReleaseResource(h);

	bHandled = false;
	return true;
}
