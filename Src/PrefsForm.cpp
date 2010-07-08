// MainForm.cpp
//
// This file implements the main form for
// your application.

#include "Common.h"
#include "PrefsForm.h"
#include "PitchApp.h"

#include "GameManager.h"

extern GameManager *gManager;

// Form open handler
Boolean CPrefsDialog::OnOpen(EventPtr pEvent, Boolean& bHandled) {

	m_HumanName.Attach(this, PrefsPlayerNameField);
	m_DelaySlider.Attach(this, PrefsTricksDelay);

	m_HumanName.Replace(gManager->player_names[0]);

	if ( gManager->play_delay_ticks < 25 ) {
		gManager->play_delay_ticks = 25;
	}
	else if ( gManager->play_delay_ticks > 125 ) {
		gManager->play_delay_ticks = 125;
	}
	m_DelaySlider.SetValue(gManager->play_delay_ticks);
	

	bHandled = false;
	return true;
}

Boolean CPrefsDialog::OnOK(EventPtr pEvent, Boolean& bHandled) {

	if ( m_HumanName.GetTextPtr() ) {
		gManager->player_names[0] = m_HumanName.GetTextPtr();
	}

	if ( gManager->players.GetCount() > 0 ) {
		gManager->players[0]->name = m_HumanName.GetTextPtr();
	}
	gManager->play_delay_ticks = m_DelaySlider.GetValue();

	CloseForm();
	return false;
}

Boolean CPrefsDialog::OnClose(EventPtr pEvent, Boolean& bHandled) {

	//
	// display the user's hand here
	//
	m_HumanName.Detach();
	m_DelaySlider.Detach();
	
	bHandled = false;
	return false;
}


Boolean CPrefsDialog::OnCancel(EventPtr pEvent, Boolean& bHandled) {
	CloseForm();
	return false;
}
