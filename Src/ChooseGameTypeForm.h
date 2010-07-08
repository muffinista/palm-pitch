#ifndef GTFORM_H_
#define GTFORM_H_

class CChooseGameTypeDialog : public CModalForm {

public:
	// constructor
	CChooseGameTypeDialog() :
		CModalForm(ChooseGameTypeForm)
		{ }


	// Form event handlers
	Boolean OnOpen(EventType* pEvent, Boolean& bHandled);
	Boolean OnClose(EventType* pEvent, Boolean& bHandled);

	// Command handlers
	Boolean OnOK(EventPtr pEvent, Boolean& bHandled);
	Boolean OnCancel(EventPtr pEvent, Boolean& bHandled);

	Boolean CutThroat();

	// Event map
	BEGIN_EVENT_MAP(CModalForm)
		EVENT_MAP_COMMAND_ENTRY(GameTypeOKButton, OnOK)
		EVENT_MAP_COMMAND_ENTRY(GameTypeCancelButton, OnCancel)
	END_EVENT_MAP()

	// Post-Event map
	BEGIN_POST_EVENT_MAP(CModalForm)
		POST_EVENT_MAP_ENTRY(frmOpenEvent, OnOpen)
		POST_EVENT_MAP_ENTRY(frmCloseEvent, OnClose)
 	END_POST_EVENT_MAP()


protected:
	CListCtrl m_GameType;
	Boolean _cutthroat;

};

#endif // PREFSFORM_H_
