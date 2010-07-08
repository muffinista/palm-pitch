#ifndef WINLOSSFORM_H_
#define WINLOSSFORM_H_

class CWinLossDialog : public CModalForm {
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
	CWinLossDialog() :
		CModalForm(WinLossForm)
		{ }

	// Event handlers
	Boolean OnOpenPost(EventPtr pEvent, Boolean& bHandled);
	Boolean OnClose(EventPtr pEvent, Boolean& bHandled);
	Boolean OnOK(EventType* pEvent, Boolean& bHandled);
	Boolean OnResetScores(EventType* pEvent, Boolean& bHandled);

	// Event map
	BEGIN_EVENT_MAP(CModalForm)
		EVENT_MAP_COMMAND_ENTRY(OKButton, OnOK)
		EVENT_MAP_COMMAND_ENTRY(ResetScoresButton, OnResetScores)
		EVENT_MAP_ENTRY(frmCloseEvent, OnClose)
 	END_EVENT_MAP()

	// Post-Event map
	BEGIN_POST_EVENT_MAP(CModalForm)
		POST_EVENT_MAP_ENTRY(frmOpenEvent, OnOpenPost)
 	END_POST_EVENT_MAP()
 	
private:
	CField m_ns_games_Field; 	
	CField m_ew_games_Field; 	
};

#endif // ABOUTFORM_H_
