#ifndef REGFORM_H_
#define REGFORM_H_

/*

FORM ID EnterSerialNumber   AT ( 2 58 156 100 )
MODAL SAVEBEHIND
BEGIN
    TITLE "Enter Serial Number"
	FIELD ID SerialNumber  AT (22 63 90 13) MAXCHARS 10 EDITABLE UNDERLINED
	BUTTON "OK" ID SerialOK  AT (3 85 AUTO AUTO)
	BUTTON "Cancel" ID SerialCancel  AT (32 85 AUTO AUTO)
	LABEL "First, purchase the game at\rhttp://www.muffin-works.com/" AUTOID AT (6 18)
	LABEL "Second, enter your code here:" AUTOID AT (6 49)
	GRAFFITISTATEINDICATOR AT (145 88)
END

*/
class CRegDialog : public CModalForm {

public:
	// constructor
	CRegDialog() : CModalForm(EnterSerialNumber)	{ }

	// Event handlers
	Boolean OnOpenPost(EventPtr pEvent, Boolean& bHandled);
	Boolean OnOK(EventType* pEvent, Boolean& bHandled);
	Boolean OnClose(EventType* pEvent, Boolean& bHandled);
	Boolean OnCancel(EventType* pEvent, Boolean& bHandled);

	CString RegCode();

	// Event map
	BEGIN_EVENT_MAP(CModalForm)
		EVENT_MAP_COMMAND_ENTRY(SerialOK, OnOK)
		EVENT_MAP_COMMAND_ENTRY(SerialCancel, OnCancel)
		EVENT_MAP_ENTRY(frmCloseEvent, OnClose)
 	END_EVENT_MAP()

	// Post-Event map
	BEGIN_POST_EVENT_MAP(CModalForm)
		POST_EVENT_MAP_ENTRY(frmOpenEvent, OnOpenPost)
 	END_POST_EVENT_MAP()
 	
private:
	CField m_RegCode;
	CString tmpCode;
};

#endif // REGFORM_H_
