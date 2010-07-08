#ifndef WINNINGSFORM_H_
#define WINNINGSFORM_H_

class CWinningsDialog : public CModalForm {
/*

FORM ID WinLossForm  AT ( 2 77 156 80 )
MODAL
BEGIN
        TITLE "Win-Loss Record"
    BUTTON "OK" ID OKButton  AT (126 65 AUTO AUTO)
    LABEL "North/South Team:" AUTOID AT (3 20)
    FIELD ID NSGamesWon  AT (88 20 24 13) MAXCHARS 20 NONEDITABLE
    LABEL "wins" AUTOID AT (118 20)
    LABEL "East/West Team:" AUTOID AT (3 35)
    FIELD ID EWGamesWon  AT (88 35 24 13) MAXCHARS 20 NONEDITABLE
    LABEL "wins" AUTOID AT (118 35)
    BUTTON "Reset Scores" ID ResetScoresButton  AT (59 65 AUTO AUTO)
END
*/
public:
	// constructor
	CWinningsDialog() :
		CModalForm(Winnings)
		{ }

	// Event handlers
	Boolean OnOpenPost(EventPtr pEvent, Boolean& bHandled);
	Boolean OnClose(EventPtr pEvent, Boolean& bHandled);
	Boolean OnOK(EventType* pEvent, Boolean& bHandled);

	// Event map
	BEGIN_EVENT_MAP(CModalForm)
		EVENT_MAP_COMMAND_ENTRY(WinningsOKButton, OnOK)
		EVENT_MAP_ENTRY(frmCloseEvent, OnClose)
 	END_EVENT_MAP()

	// Post-Event map
	BEGIN_POST_EVENT_MAP(CModalForm)
		POST_EVENT_MAP_ENTRY(frmOpenEvent, OnOpenPost)
 	END_POST_EVENT_MAP()
 	
private:

	CField names[3];

};

#endif // WINNINGSFORM_H_
