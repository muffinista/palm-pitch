#ifndef DECK_H
#define DECK_H

#include "Card.h"

class Deck {
	public:
		Deck();
		~Deck();

		Card *deal();
		void reset();
		Card *GetCard(Int16 offset);

	private:
		void shuffle();

		CArray<Card*> theDeck;
		Boolean is_shuffled;
		Int16 deal_pos;

};

#endif
