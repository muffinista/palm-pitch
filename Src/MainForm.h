// MainForm.h
//
// This file declares a class for the main form of
// your application.

#ifndef MAINFORM_H_
#define MAINFORM_H_

class CMainForm : public CForm {

public:

	// Form event handlers
	Boolean OnOpen(EventType* pEvent, Boolean& bHandled);

	// Command handlers
	Boolean OnNewGame(EventPtr pEvent, Boolean& bHandled);
	Boolean OnPrefs(EventPtr pEvent, Boolean& bHandled);
	Boolean OnGameOptions(EventPtr pEvent, Boolean& bHandled);
	Boolean OnHelp(EventPtr pEvent, Boolean& bHandled);
	Boolean OnRegister(EventPtr pEvent, Boolean& bHandled);

	Boolean OnViewWinTotals(EventType* pEvent, Boolean& bHandled);
	Boolean OnInstructions(EventType* pEvent, Boolean& bHandled);
	Boolean OnAbout(EventType* pEvent, Boolean& bHandled);

	// Event map
	BEGIN_EVENT_MAP(CForm)
		EVENT_MAP_ENTRY(frmOpenEvent, OnOpen)
		EVENT_MAP_COMMAND_ENTRY(IntroNewGameButton, OnNewGame)
		EVENT_MAP_COMMAND_ENTRY(IntroPrefsButton, OnPrefs)
		EVENT_MAP_COMMAND_ENTRY(IntroGameOptionsButton, OnGameOptions)
		EVENT_MAP_COMMAND_ENTRY(IntroInstructionsButton, OnHelp)
		EVENT_MAP_COMMAND_ENTRY(IntroRegisterPitchButton, OnRegister)

		EVENT_MAP_MENU_ENTRY(StartNewGame, OnNewGame)
		EVENT_MAP_MENU_ENTRY(ViewWinTotals, OnViewWinTotals)
		EVENT_MAP_MENU_ENTRY(MainOptionsPreferences, OnPrefs)
		EVENT_MAP_MENU_ENTRY(MainOptionsGameOptions, OnGameOptions)
		EVENT_MAP_MENU_ENTRY(MainOptionsRegister, OnRegister)
		EVENT_MAP_MENU_ENTRY(HelpInstructions, OnHelp)
		EVENT_MAP_MENU_ENTRY(HelpAboutPitch, OnAbout)
	END_EVENT_MAP()

};

#endif // MAINFORM_H_
