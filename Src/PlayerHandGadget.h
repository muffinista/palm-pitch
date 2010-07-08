#ifndef __PLAYER_HAND_H__
#define __PLAYER_HAND_H__

#include "Common.h"

#include "Player.h"
#include "Trick.h"

class CPlayerHandGadget : public CGadget {

 public:

	CPlayerHandGadget();

    Boolean OnDraw(Boolean& bVisible);
	Boolean OnPenDown(EventType* pEvent, Boolean& bHandled);
	Boolean OnPenUp(EventType* pEvent, Boolean& bHandled);

	Boolean OnDelete();

    void Render();
    void Render(Boolean redraw);

	void MoveLeft();
	void MoveRight();

	Boolean Select();
	void Reset();

	void ResetHighlight();
	void DrawHighlight();

	
	void CurrentTrick(Trick *);
	Trick *CurrentTrick();
	
	void CurrentPlayer(Player *);
	Player *CurrentPlayer();

	static Int16 card_width;
	static Int16 card_height;
	static Int16 card_spacing;

 private:

 	Boolean handling_input;
 	Int16 screen_x;
 	Int16 screen_y;

	Int8 active_card;
	
	Boolean show_all;
	
	Trick *trk;
	Player *p;

	RectangleType  bounds;

	Int16 choice;

 };

#endif