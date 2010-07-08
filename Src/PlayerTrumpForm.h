// MainForm.h
//
// This file declares a class for the main form of
// your application.

#ifndef PLAYERTRUMPFORM_H_
#define PLAYERTRUMPFORM_H_

#include "PlayerHandGadget.h"

class CPlayerTrumpForm : public CModalForm {

public:

	// constructor
	CPlayerTrumpForm() :
		CModalForm(PlayerTrumpForm)
		{}

	// Form event handlers
	Boolean OnOpen(EventType* pEvent, Boolean& bHandled);
	Boolean OnClose(EventType* pEvent, Boolean& bHandled);

	// Command handlers
	Boolean OnOK(EventPtr pEvent, Boolean& bHandled);
	Boolean OnChooseTrump(EventPtr pEvent, Boolean& bHandled);


	// Event map
	BEGIN_EVENT_MAP(CModalForm)
		EVENT_MAP_COMMAND_ENTRY(PlayerTrumpOKButton, OnOK)
		EVENT_MAP_ENTRY(frmCloseEvent, OnClose)
		EVENT_MAP_COMMAND_ENTRY(PlayerTrumpHeartsPushButton, OnChooseTrump)
		EVENT_MAP_COMMAND_ENTRY(PlayerTrumpDiamondsPushButton, OnChooseTrump)
		EVENT_MAP_COMMAND_ENTRY(PlayerTrumpClubsPushButton, OnChooseTrump)
		EVENT_MAP_COMMAND_ENTRY(PlayerTrumpSpadesPushButton, OnChooseTrump)
	END_EVENT_MAP()

	BEGIN_POST_EVENT_MAP(CModalForm)
		POST_EVENT_MAP_ENTRY(frmOpenEvent, OnOpen)
	END_POST_EVENT_MAP()

protected:
	CPlayerHandGadget player_hand;

};

#endif // PLAYERTRUMPFORM_H_
