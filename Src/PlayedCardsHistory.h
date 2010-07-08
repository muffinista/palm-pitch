#ifndef PCHISTORYFORM_H_
#define PCHISTORYFORM_H_

#include "PlayedCardsHistoryGrid.h"

class CPlayedCardsHistoryDialog : public CModalForm {

public:
	// constructor
	CPlayedCardsHistoryDialog() :
		CModalForm(CardsPlayed)
		{ }

	// Event handlers
	Boolean OnOpenPost(EventPtr pEvent, Boolean& bHandled);
	Boolean OnOK(EventType* pEvent, Boolean& bHandled);
	Boolean OnClose(EventType* pEvent, Boolean& bHandled);

	// Event map
	BEGIN_EVENT_MAP(CModalForm)
		EVENT_MAP_COMMAND_ENTRY(CardsPlayedOKButton, OnOK)
		EVENT_MAP_ENTRY(frmCloseEvent, OnClose)
 	END_EVENT_MAP()

	// Post-Event map
	BEGIN_POST_EVENT_MAP(CModalForm)
		POST_EVENT_MAP_ENTRY(frmOpenEvent, OnOpenPost)
 	END_POST_EVENT_MAP()
 	
private:

	CField ns_names;
	CField ew_names;
	
	CPlayedCardsHistoryGrid grid;

};

#endif // PCHISTORYFORM_H_
