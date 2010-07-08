#ifndef SCORING_FORM_H__
#define SCORING_FORM_H__

#include "Card.h"

class CScoringForm : public CForm {

public:

	// Form event handlers
	Boolean OnOpen(EventType* pEvent, Boolean& bHandled);
	Boolean OnClose(EventType* pEvent, Boolean& bHandled);

	// Command handlers
	Boolean OnOK(EventPtr pEvent, Boolean& bHandled);
	Boolean OnViewPlayedCards(EventType* pEvent, Boolean& bHandled);
	Boolean OnViewWinnings(EventType* pEvent, Boolean& bHandled);
	Boolean OnViewWinTotals(EventType* pEvent, Boolean& bHandled);

	Boolean OnPrefs(EventType* pEvent, Boolean& bHandled);

	void OnDraw();

	// Event map
	BEGIN_EVENT_MAP(CForm)
		EVENT_MAP_ENTRY(frmOpenEvent, OnOpen)
		EVENT_MAP_ENTRY(frmCloseEvent, OnClose)
		EVENT_MAP_COMMAND_ENTRY(ScoringOKButton, OnOK)
		EVENT_MAP_MENU_ENTRY(ViewPlayedCards, OnViewPlayedCards)
		EVENT_MAP_MENU_ENTRY(ViewWinnings, OnViewWinnings)
		EVENT_MAP_MENU_ENTRY(ViewWinTotals, OnViewWinTotals)
		EVENT_MAP_MENU_ENTRY(MainOptionsPreferences, OnPrefs)
	END_EVENT_MAP()

protected:
	CField high_field;
	CField low_field;
	CField jack_field;
	CField game_field;

//	CField ns_score;
//	CField ew_score;
	CGadget score_gadget;

	CField bid_results;
//	CField other_team_results;

};

#endif // SCORING_FORM_H__
