#ifndef CARD_H
#define CARD_H

#include "Common.h"

class Card {	

	public:
		enum suit_t { spade = 0, club, diamond,  heart };
		enum face_t { two = 0, three, four, five, six, seven, eight, nine, ten, jack, queen, king, ace };

		Card();
		Card(suit_t,face_t);
		~Card();

		// get this cards offset in an unshuffled deck (used when loading/saving)
    	Int16 Offset();

		face_t Face();
		suit_t Suit();

		char FaceChar();
		char SuitChar();

//		UInt16 SuitBitmap(Boolean draw_grey);
		UInt16 SuitBitmap(UInt16 draw_method);

		void Draw(Int16 x, Int16 y, Int16 width, Int16 height, Boolean draw_grey, Boolean inverted );
		void Draw(Int16 x, Int16 y, Int16 width, Int16 height, Boolean draw_grey );
		void Draw(Int16 x, Int16 y, Int16 width, Int16 height);

	private:
		Boolean check_color_support();

		face_t f;
		suit_t s;

};

#endif
