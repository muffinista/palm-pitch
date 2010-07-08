#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "Player.h"

class HumanPlayer : public Player {

	public:
		HumanPlayer();
		HumanPlayer(char);
		HumanPlayer(char c, CString name);

		~HumanPlayer();

		void sort_hand();

       	Boolean PickCard( Trick * );
		Card *PlayedCard();
		Int16 BeginBidProcess(Player *, Player *);
		Card::suit_t Trump();
		void record_stats(Trick *t);

//		void draw_suit(Int16 x, Int16 y, UInt16 rsc, Boolean inverted );

};

#endif
