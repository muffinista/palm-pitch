#ifndef __PLAYED_CARDS_H__
#define __PLAYED_CARDS_H__

#include "Common.h"

#include "Player.h"
#include "Trick.h"

class CPlayedCardsGadget : public CGadget {

 public:

	CPlayedCardsGadget();

    Boolean OnDraw(Boolean& bVisible);
    Boolean OnDelete();

    void Render();
    void Render(Boolean redraw);

	void Reset();
	
	void CurrentTrick(Trick *);
	Trick *CurrentTrick();

 private:

	RectangleType  bounds;
	Trick *trk;
	Int16 book_count;

	static Int16 card_width;
	static Int16 card_height;
	static Int16 card_spacing;
 };

#endif