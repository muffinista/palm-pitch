// MainForm.h
//
// This file declares a class for the main form of
// your application.

#ifndef PLAYERBIDFORM_H_
#define PLAYERBIDFORM_H_

#include "Player.h"
#include "PlayerHandGadget.h"

class CPlayerBidForm : public CModalForm {

public:
/*
    PUSHBUTTON "Pass" ID PlayerBidPassPushButton AT (11 89 22 20) USABLE FONT 0 GROUP 1
    GADGET ID PlayerBidPlayerHandGadget AT (9 44 117 40) USABLE
    PUSHBUTTON "2" ID PlayerBid2PushButton AT (34 89 16 20) USABLE FONT 0 GROUP 1
    PUSHBUTTON "3" ID PlayerBid3PushButton AT (51 89 16 20) USABLE FONT 0 GROUP 1
    PUSHBUTTON "4" ID PlayerBid4PushButton AT (68 89 16 20) USABLE FONT 0 GROUP 1
    BUTTON "OK" ID PlayerBidOKButton AT (115 116 36 12) USABLE FRAME FONT 0
    PUSHBUTTON "Smudge" ID PlayerBidSmudgePushButton AT (85 89 36 20) USABLE FONT 0 GROUP 1
    FIELD ID PlayerBidCurrentHighField AT (9 28 140 12) USABLE LEFTALIGN FONT 0 NONEDITABLE SINGLELINE MAXCHARS 80
    FIELD ID PlayerBidDealerInfoField AT (9 15 140 12) USABLE LEFTALIGN FONT 0 NONEDITABLE SINGLELINE MAXCHARS 80
*/

	// constructor
	CPlayerBidForm() :
		CModalForm(PlayerBidForm)
		{ }

	// Form event handlers
	Boolean OnOpen(EventType* pEvent, Boolean& bHandled);
//    Boolean OnDraw(Boolean& bVisible);

	// Command handlers
	Boolean OnOK(EventPtr pEvent, Boolean& bHandled);

	void CurrentHigh(int);
	void CurrentDealer(Player *);

	// Event map
	BEGIN_EVENT_MAP(CModalForm)
		EVENT_MAP_COMMAND_ENTRY(PlayerBidOKButton, OnOK)
	END_EVENT_MAP()

//		EVENT_MAP_ENTRY(frmOpenEvent, OnOpen)

	// Post-Event map
	BEGIN_POST_EVENT_MAP(CModalForm)
		POST_EVENT_MAP_ENTRY(frmOpenEvent, OnOpen)
 	END_POST_EVENT_MAP()

	int bidval;

protected:
	int high_bid;
	Player *dealer;

	CField current_high;
	CField current_dealer;

	CPlayerHandGadget player_hand;
};

#endif // PLAYERBIDFORM_H_
