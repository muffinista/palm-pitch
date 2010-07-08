#ifndef GAMEFORM_H_
#define GAMEFORM_H_

#include "PlayedCardsGadget.h"
#include "PlayerHandGadget.h"

class CGameForm : public CForm {
public:

	// Form event handlers
	Boolean OnOpen(EventType* pEvent, Boolean& bHandled);
	Boolean OnClose(EventType* pEvent, Boolean& bHandled);
	void OnDraw();

	Boolean OnPenDown(EventType* pEvent, Boolean& bHandled);
	Boolean OnPenUp(EventType* pEvent, Boolean& bHandled);
	Boolean OnNilEvent(EventType* pEvent, Boolean& bHandled);
	Boolean OnKeyDown(EventType* pEvent, Boolean& bHandled);

	Boolean OnViewPlayedCards(EventType* pEvent, Boolean& bHandled);
	Boolean OnViewWinnings(EventType* pEvent, Boolean& bHandled);
	Boolean OnViewWinTotals(EventType* pEvent, Boolean& bHandled);
	Boolean OnQuitGame(EventType* pEvent, Boolean& bHandled);
	Boolean OnPrefs(EventType* pEvent, Boolean& bHandled);
	Boolean OnRegister(EventType* pEvent, Boolean& bHandled);
	Boolean OnInstructions(EventType* pEvent, Boolean& bHandled);
	Boolean OnAbout(EventType* pEvent, Boolean& bHandled);


	// Event map
	BEGIN_EVENT_MAP(CForm)
		EVENT_MAP_ENTRY(frmOpenEvent, OnOpen)
		EVENT_MAP_ENTRY(frmCloseEvent, OnClose)
		EVENT_MAP_ENTRY(penDownEvent, OnPenDown)
		EVENT_MAP_ENTRY(penUpEvent, OnPenUp)
		EVENT_MAP_ENTRY(nilEvent, OnNilEvent)
		EVENT_MAP_ENTRY(keyDownEvent, OnKeyDown)
		EVENT_MAP_MENU_ENTRY(ViewPlayedCards, OnViewPlayedCards)
		EVENT_MAP_MENU_ENTRY(ViewWinnings, OnViewWinnings)
		EVENT_MAP_MENU_ENTRY(ViewWinTotals, OnViewWinTotals)
		EVENT_MAP_MENU_ENTRY(MainOptionsQuitGame, OnQuitGame)
		EVENT_MAP_MENU_ENTRY(MainOptionsPreferences, OnPrefs)
		EVENT_MAP_MENU_ENTRY(MainOptionsRegister, OnRegister)
		EVENT_MAP_MENU_ENTRY(HelpInstructions, OnInstructions)
		EVENT_MAP_MENU_ENTRY(HelpAboutPitch, OnAbout)
	END_EVENT_MAP()

protected:

	void DrawPlayerHand(UInt8 index, UInt16 x, UInt16 y);

	CPlayedCardsGadget played_cards;
	CPlayerHandGadget player_hand;

	CField names[4];
	CField bidder_name;
	CField ns_score;
	CField ew_score;

	void InitScreen();
	void CheckGameCondition();
	void DrawLead();
};

#endif // GAMEFORM_H_
