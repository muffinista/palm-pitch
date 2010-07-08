#ifndef OPTIONSFORM_H_
#define OPTIONSFORM_H_

class COptionsDialog : public CModalForm {

/*    LABEL "AI:" ID PrefsUnnamed1203Label AT (2 18) USABLE FONT 0
	LABEL "Smart" AUTOID AT (125 18)
	SLIDER ID PrefsAILevel   AT (48 16 72 15) MIN 0 MAX 100 PAGESIZE 10 VALUE 50
	LABEL "Dumb" AUTOID AT (18 17)*/
public:
	// constructor
	COptionsDialog() :
		CModalForm(GameOptionsForm)
		{ }


	// Form event handlers
	Boolean OnOpen(EventType* pEvent, Boolean& bHandled);
	Boolean OnClose(EventType* pEvent, Boolean& bHandled);

	// Command handlers
	Boolean OnOK(EventPtr pEvent, Boolean& bHandled);
	Boolean OnCancel(EventPtr pEvent, Boolean& bHandled);

	// Event map
	BEGIN_EVENT_MAP(CModalForm)
		EVENT_MAP_COMMAND_ENTRY(OptionsOKButton, OnOK)
		EVENT_MAP_COMMAND_ENTRY(OptionsCancelButton, OnCancel)
		EVENT_MAP_ENTRY(frmCloseEvent, OnClose)
	END_EVENT_MAP()

	// Post-Event map
	BEGIN_POST_EVENT_MAP(CModalForm)
		POST_EVENT_MAP_ENTRY(frmOpenEvent, OnOpen)
 	END_POST_EVENT_MAP()

protected:
	CControl m_NoTrickCheckbox;
	CControl m_DealerTakeBidCheckbox;
	CControl m_WinOnBidCheckbox;
	CControl m_WinOnSmudgeCheckbox;
//	CSlider m_AISlider;
};

#endif // OPTIONSFORM_H_
