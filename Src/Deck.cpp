#include "Deck.h"

Deck::Deck() {

	deal_pos = 0;

	is_shuffled = false;

	theDeck.DeleteAll();

	for (Int16 i = 0; i < 4; ++i) {

		for (Int16 j = 0; j < 13; ++j) {

			Card *foo = new Card(static_cast<Card::suit_t>(i),
									static_cast<Card::face_t>(j));
			theDeck.Add(foo);

		}
	}

}

Deck::~Deck() {

	for ( Int16 count = 51 ; count >= 0 ; count-- ) {
		delete theDeck[count];
	}

	theDeck.DeleteAll();
}

Card *Deck::GetCard(Int16 offset) {
	if ( offset > 52 || offset < 0 ) {
		return NULL;
	}
	return theDeck[offset];
}


void Deck::shuffle() {

	Card *tmp;

	deal_pos = 0;

	for (Int16 x = 0; x < 1000; x++ ) {

		Int16 card1 = SysRandom(0) % 52;
		Int16 card2 = SysRandom(0) % 52;

		if ( card1 != card2 ) {
			tmp = theDeck[card1];
			theDeck[card1] = theDeck[card2];
			theDeck[card2] = tmp;
		}
	}

}

Card *Deck::deal() {

	if ( ! is_shuffled ) {
		is_shuffled = true;
		shuffle();
	}

	Card *tmp = theDeck[deal_pos];
	deal_pos++;

/*	if ( deal_pos == 0 )
		deal_pos = 51;

	Card *tmp = theDeck[deal_pos];
	deal_pos--;
*/
	return tmp;

}	

void Deck::reset() {
	is_shuffled = false;
	deal_pos = 0;
}

