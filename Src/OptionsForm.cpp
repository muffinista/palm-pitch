// MainForm.cpp
//
// This file implements the main form for
// your application.

#include "Common.h"
#include "OptionsForm.h"
#include "PitchApp.h"

#include "GameManager.h"

extern GameManager *gManager;

// Form open handler
Boolean COptionsDialog::OnOpen(EventPtr pEvent, Boolean& bHandled) {

	m_NoTrickCheckbox.Attach(this, PrefsNoTrickCheckbox);
	m_DealerTakeBidCheckbox.Attach(this, PrefsDealerTakeBidCheckbox);
	m_WinOnBidCheckbox.Attach(this, PrefsWinOnBidCheckbox);
	m_WinOnSmudgeCheckbox.Attach(this, PrefsWinOnSmudge);
//	m_AISlider.Attach(this, PrefsAILevel);

	m_NoTrickCheckbox.SetValue(gManager->no_trump_first_trick);
	m_DealerTakeBidCheckbox.SetValue(gManager->dealer_take_bid);
	m_WinOnBidCheckbox.SetValue(gManager->win_on_bid);
	m_WinOnSmudgeCheckbox.SetValue(gManager->win_on_smudge);
//	m_AISlider.SetValue(gManager->ai_level);

	bHandled = false;
	return true;
}

Boolean COptionsDialog::OnOK(EventPtr pEvent, Boolean& bHandled) {


	gManager->no_trump_first_trick = m_NoTrickCheckbox.GetValue();
	gManager->dealer_take_bid = m_DealerTakeBidCheckbox.GetValue();
	gManager->win_on_bid = m_WinOnBidCheckbox.GetValue();
	gManager->win_on_smudge = m_WinOnSmudgeCheckbox.GetValue();
//	gManager->ai_level = m_AISlider.GetValue();

	CloseForm();
	return false;
}

Boolean COptionsDialog::OnClose(EventPtr pEvent, Boolean& bHandled) {

	m_NoTrickCheckbox.Detach();
	m_DealerTakeBidCheckbox.Detach();
	m_WinOnBidCheckbox.Detach();
//	m_AISlider.Detach();
	
	bHandled = false;
	return false;
}


Boolean COptionsDialog::OnCancel(EventPtr pEvent, Boolean& bHandled) {
	CloseForm();
	return false;
}
