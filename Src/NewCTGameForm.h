#ifndef NEWCTGAMEFORM_H_
#define NEWCTGAMEFORM_H_

class CNewCTGameForm : public CForm {

public:
/*
    TITLE "New Game"
    FIELD ID SetPlayer3Name  AT (56 108 78 12) USABLE LEFTALIGN FONT 0   MAXCHARS 14 UNDERLINED EDITABLE AUTOSHIFT
    FIELD ID SetPlayer2Name  AT (117 39 38 12) USABLE LEFTALIGN FONT 0   MAXCHARS 14 UNDERLINED AUTOSHIFT EDITABLE
    FIELD ID SetPlayer1Name  AT (62 20 38 12) USABLE LEFTALIGN FONT 0   MAXCHARS 14 UNDERLINED AUTOSHIFT EDITABLE
    FIELD ID SetPlayer0Name  AT (4 42 38 12) USABLE LEFTALIGN FONT 0   MAXCHARS 14 EDITABLE UNDERLINED AUTOSHIFT
    LIST "Smart" "Risky" "Dumb"    ID PlayerTypes0    AT (3 56 40 35) VISIBLEITEMS 3
    LIST "Smart" "Risky" "Dumb"    ID PlayerTypes1    AT (62 34 40 35) VISIBLEITEMS 3
    LIST "Smart" "Risky" "Dumb"    ID PlayerTypes2    AT (117 54 40 35) VISIBLEITEMS 3
    LABEL "Play To:" AUTOID AT (19 123)
    FIELD ID SetWinningScore AT (56 123 20 11) MAXCHARS 2 EDITABLE UNDERLINED NUMERIC
    BUTTON "OK" ID StartGameButton  AT (4 141 32 13)
    LABEL "points." AUTOID AT (78 123)
    LABEL "Your Name:" AUTOID AT (5 109)
    BUTTON "Cancel" ID CancelGameButton   AT (41 141 39 13)
	GRAFFITISTATEINDICATOR AT (148 141)
*/

	// Form event handlers
	Boolean OnOpen(EventType* pEvent, Boolean& bHandled);
	Boolean OnClose(EventType* pEvent, Boolean& bHandled);

	// Command handlers
	Boolean OnOK(EventPtr pEvent, Boolean& bHandled);
	Boolean OnCancel(EventPtr pEvent, Boolean& bHandled);
	Boolean OnGameOptions(EventPtr pEvent, Boolean& bHandled);

	Boolean OnHelp(EventPtr pEvent, Boolean& bHandled);
	Boolean OnAbout(EventPtr pEvent, Boolean& bHandled);

	// Event map
	BEGIN_EVENT_MAP(CForm)
		EVENT_MAP_ENTRY(frmOpenEvent, OnOpen)
		EVENT_MAP_ENTRY(frmCloseEvent, OnClose)
		EVENT_MAP_COMMAND_ENTRY(StartGameButton, OnOK)
		EVENT_MAP_COMMAND_ENTRY(OptionsGameButton, OnGameOptions)
		EVENT_MAP_COMMAND_ENTRY(CancelGameButton, OnCancel)

		EVENT_MAP_MENU_ENTRY(MainOptionsQuitGame, OnCancel )
		EVENT_MAP_MENU_ENTRY(HelpInstructions, OnHelp )
		EVENT_MAP_MENU_ENTRY(HelpAboutPitch, OnAbout )
	END_EVENT_MAP()

protected:
	CField p0name;
	CField p1name;
	CField p2name;
	CField p3name;
	CField winning_score;
};

#endif // NEWGAMEFORM_H_
