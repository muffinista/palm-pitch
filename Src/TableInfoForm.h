#ifndef TABLEINFOFORM_H_
#define TABLEINFOFORM_H_

class CTableInfoDialog : public CModalForm {
public:
	// constructor
	CTableInfoDialog() :
		CModalForm(TableInfoForm)
		{}

	// Event handlers
	Boolean OnOpenPost(EventPtr pEvent, Boolean& bHandled);
	Boolean OnClose(EventType* pEvent, Boolean& bHandled);
	Boolean OnOK(EventType* pEvent, Boolean& bHandled);

	// Event map
	BEGIN_EVENT_MAP(CModalForm)
		EVENT_MAP_COMMAND_ENTRY(TableInfoOKButton, OnOK)
		EVENT_MAP_ENTRY(frmCloseEvent, OnClose)
 	END_EVENT_MAP()

	// Post-Event map
	BEGIN_POST_EVENT_MAP(CModalForm)
		POST_EVENT_MAP_ENTRY(frmOpenEvent, OnOpenPost)
 	END_POST_EVENT_MAP()
 	
private:
	CField ns_teamField;
	CField ew_teamField;
	CField scoreField;
	CField dealerField;

	CString ns_team;
	CString ew_team;
	char scorestr[10];
	CString dealerstr;
};

#endif // ABOUTFORM_H_

