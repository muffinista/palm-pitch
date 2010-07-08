#ifndef TABLECTINFOFORM_H_
#define TABLECTINFOFORM_H_

class CTableCTInfoDialog : public CModalForm {
public:
	// constructor
	CTableCTInfoDialog() :
		CModalForm(TableCTInfoForm)
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
	CField playersField;
//	CField humanField;
	CField scoreField;
	CField dealerField;

	CString player_names;
//	CString human;
	char scorestr[10];
	CString dealerstr;
};

#endif // ABOUTFORM_H_

