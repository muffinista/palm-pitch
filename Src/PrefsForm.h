#ifndef PREFSFORM_H_
#define PREFSFORM_H_

class CPrefsDialog : public CModalForm {
/*
    BUTTON "OK" ID PrefsOKButton AT (3 124 36 12) USABLE FRAME FONT 0
    BUTTON "Cancel" ID PrefsCancelButton AT (43 124 36 12) USABLE FRAME FONT 0
    FIELD ID PrefsPlayerNameField AT (54 17 100 12) USABLE LEFTALIGN FONT 0 EDITABLE UNDERLINED SINGLELINE MAXCHARS 14
	SLIDER ID PrefsTricksDelay  AT (32 44 93 15) MIN 0 MAX 100 PAGESIZE 10 VALUE 50
	CHECKBOX "Allow No Trump on First Trick?" ID PrefsNoTrickCheckbox  AT (6 81 AUTO AUTO)
	CHECKBOX "Dealer can take bid" ID PrefsDealerTakeBidCheckbox   AT (6 93 AUTO AUTO)
	CHECKBOX "Win on a bid only" ID PrefsWinOnBidCheckbox    AT (6 107 AUTO AUTO)
*/

public:
	// constructor
	CPrefsDialog() :
		CModalForm(PrefsForm)
		{ }


	// Form event handlers
	Boolean OnOpen(EventType* pEvent, Boolean& bHandled);
	Boolean OnClose(EventType* pEvent, Boolean& bHandled);

	// Command handlers
	Boolean OnOK(EventPtr pEvent, Boolean& bHandled);
	Boolean OnCancel(EventPtr pEvent, Boolean& bHandled);

	// Event map
	BEGIN_EVENT_MAP(CModalForm)
		EVENT_MAP_COMMAND_ENTRY(PrefsOKButton, OnOK)
		EVENT_MAP_COMMAND_ENTRY(PrefsCancelButton, OnCancel)
		EVENT_MAP_ENTRY(frmCloseEvent, OnClose)
	END_EVENT_MAP()

	// Post-Event map
	BEGIN_POST_EVENT_MAP(CModalForm)
		POST_EVENT_MAP_ENTRY(frmOpenEvent, OnOpen)
 	END_POST_EVENT_MAP()

protected:

	CField 	m_HumanName;
	CSlider m_DelaySlider;

//	CControl m_NoTrickCheckbox;
//	CControl m_DealerTakeBidCheckbox;
//	CControl m_WinOnBidCheckbox;

};

#endif // PREFSFORM_H_
