#ifndef BIDFORM_H_
#define BIDFORM_H_

#include "Player.h"
#include "PlayerHandGadget.h"

class CBiddingForm : public CForm {

public:

	// Form event handlers
	Boolean OnOpen(EventType* pEvent, Boolean& bHandled);

	// Command handlers
	Boolean OnOK(EventPtr pEvent, Boolean& bHandled);
	Boolean OnClose(EventPtr pEvent, Boolean& bHandled);
	Boolean OnChooseBid(EventPtr pEvent, Boolean& bHandled);
	Boolean OnSetBid(EventPtr pEvent, Boolean& bHandled);
	Boolean OnCancel(EventPtr pEvent, Boolean& bHandled);
	Boolean OnNilEvent(EventType* pEvent, Boolean& bHandled);

	Boolean OnHelp(EventPtr pEvent, Boolean& bHandled);
	Boolean OnAbout(EventPtr pEvent, Boolean& bHandled);

	// Event map
	BEGIN_EVENT_MAP(CForm)
		EVENT_MAP_ENTRY(frmOpenEvent, OnOpen)
		EVENT_MAP_ENTRY(frmCloseEvent, OnClose)
		EVENT_MAP_ENTRY(nilEvent, OnNilEvent)
		EVENT_MAP_COMMAND_ENTRY(BiddingOKButton, OnOK)
		EVENT_MAP_COMMAND_ENTRY(PlayerBidPassPushButton, OnChooseBid)
		EVENT_MAP_COMMAND_ENTRY(PlayerBid2PushButton, OnChooseBid)
		EVENT_MAP_COMMAND_ENTRY(PlayerBid3PushButton, OnChooseBid)
		EVENT_MAP_COMMAND_ENTRY(PlayerBid4PushButton, OnChooseBid)
		EVENT_MAP_COMMAND_ENTRY(PlayerBidSmudgePushButton, OnChooseBid)
		EVENT_MAP_COMMAND_ENTRY(SetBidButton, OnSetBid)		
		EVENT_MAP_MENU_ENTRY(MainOptionsQuitGame, OnCancel )
		EVENT_MAP_MENU_ENTRY(HelpInstructions, OnHelp )
		EVENT_MAP_MENU_ENTRY(HelpAboutPitch, OnAbout )
	END_EVENT_MAP()

protected:

	CField names[4];
	CField bids[4];

	CField bid_winner;

	CField ns_score;
	CField ew_score;

	CString bidstr;

	Boolean player_has_bid;
	CPlayerHandGadget player_hand;

	void InitDisplay();
	void HighlightActiveBidder();

};

#endif // BIDFORM_H_
