#ifndef GAMEOVERFORM_H_
#define GAMEOVERFORM_H_

class CGameOverForm : public CForm {
/*


FORM ID GameOverForm  AT ( 0 0 160 160 )
NOFRAME
BEGIN
    TITLE "Game Over"
	FIELD ID GameResultsField  AT (26 26 119 13) MAXCHARS 255 EDITABLE
	BUTTON "New Game" ID NewGameButton  AT (104 142 AUTO AUTO)
	BUTTON "Exit" ID ExitButton   AT (74 142 AUTO AUTO)
END

*/
public:

	// Form event handlers
	Boolean OnOpen(EventType* pEvent, Boolean& bHandled);

	// Command handlers
	Boolean OnNewGame(EventPtr pEvent, Boolean& bHandled);
	Boolean OnExit(EventPtr pEvent, Boolean& bHandled);

	// Event map
	BEGIN_EVENT_MAP(CForm)
		EVENT_MAP_ENTRY(frmOpenEvent, OnOpen)
		EVENT_MAP_COMMAND_ENTRY(NewGameButton, OnNewGame)
		EVENT_MAP_COMMAND_ENTRY(ExitButton, OnExit)
	END_EVENT_MAP()

protected:

	CField m_winners;

};

#endif // GAMEOVERFORM_H_
