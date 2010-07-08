#include "Card.h"
#include "Pitch_Rsc.h"

Boolean check_color_support();
Boolean sort_by_trump = false;
Card::suit_t trump_suit;


#define DRAW_NORMAL 	0
#define DRAW_GREY 		1
#define DRAW_INVERTED 	2


/* default constructor */
Card::Card() {
	f = two;
	s = spade;
}


/* constructor that specifies face value, and suit value */
Card::Card(suit_t suit, face_t rank) {
	f = rank;
	s = suit;
}

Card::~Card() {

}

/* 
	operator for comparing two cards 
*/
/*
Boolean Card::operator<(card *a) {

	if ( sort_by_trump ) {

		//
		// if this card is trump but the card we're comparing isn't, then it is worth less
		//
		if ( a->Suit() != trump_suit && this->Suit() == trump_suit ) {
			return true;
		}


		//
		// if the other card is trump, but this card isn't, the other is worth more
		//
		if ( a->Suit() == trump_suit && this->Suit() != trump_suit ) {
			return false;
		}

	}


	if (static_cast<Int16>(a->Suit()) != static_cast<Int16>(this->Suit()))
	{
		return false;
	}

	return ( (Int16)a->Face() < (Int16)this->Face() );

}
*/

char Card::FaceChar() {

	char rtn;
	switch(this->Face())
	{

		case two: 		rtn = '2'; break;
		case three: 		rtn = '3'; break;
		case four: 		rtn = '4'; break;
		case five: 		rtn = '5'; break;
		case six: 		rtn = '6'; break;
		case seven: 		rtn = '7'; break;
		case eight: 		rtn = '8'; break;
		case nine: 		rtn = '9'; break;
		case ten: 		rtn = 'T'; break;
		case jack: 		rtn = 'J'; break;
		case queen: 		rtn = 'Q'; break;
		case king: 		rtn = 'K'; break;
		case ace: 		rtn = 'A'; break;
		default:				rtn = 'd' ; break;
	}
	return rtn;
}

char Card::SuitChar() {

	switch(this->Suit()) {
		case diamond:	return 'D'; break;
		case spade: 	return 'S'; break;
		case heart: 	return 'H'; break;
		case club: 	return 'C'; break;
	}
	
	return '?';
}

#define DRAW_NORMAL 	0
#define DRAW_GREY 		1
#define DRAW_INVERTED 	2


UInt16 Card::SuitBitmap(UInt16 draw_method) {

	if ( ! check_color_support() ) {
	
		switch(this->Suit()) {
			case diamond:	return DiamondBitmapFamily; break;
			case spade: 	return SpadeBitmapFamily; break;
			case heart: 	return HeartBitmapFamily; break;
			case club: 	return ClubBitmapFamily; break;
		}
	
	}
	else {

		if ( draw_method == DRAW_GREY ) {
			switch(this->Suit()) {
				case diamond:	return GreyedDiamondBitmapFamily; break;
				case spade: 	return GreyedSpadeBitmapFamily; break;
				case heart: 	return GreyedHeartBitmapFamily; break;
				case club: 	return GreyedClubBitmapFamily; break;
			}
		}
		else if ( draw_method == DRAW_INVERTED ) {
			switch(this->Suit()) {
				case diamond:	return InvertedDiamondBitmapFamily; break;
				case spade: 	return InvertedSpadeBitmapFamily; break;
				case heart: 	return InvertedHeartBitmapFamily; break;
				case club: 	return InvertedClubBitmapFamily; break;
			}
		}
		else {
			switch(this->Suit()) {
				case diamond:	return DiamondBitmapFamily; break;
				case spade: 	return SpadeBitmapFamily; break;
				case heart: 	return HeartBitmapFamily; break;
				case club: 	return ClubBitmapFamily; break;
			}	
		}
	}

	return 0;

} // Suit

Card::face_t Card::Face() {
	return f;
}

Card::suit_t Card::Suit() {
	return s; 
}


void Card::Draw(Int16 x, Int16 y, Int16 width, Int16 height ) {
	Draw(x, y, width, height, false);
}

void Card::Draw(Int16 x, Int16 y, Int16 width, Int16 height, Boolean draw_grey ) {
	Draw(x, y, width, height, draw_grey, false);
}

void Card::Draw(Int16 x, Int16 y, Int16 width, Int16 height, Boolean draw_grey, Boolean inverted ) {

	RectangleType bounds;
	RGBColorType rgb;
	Int16 blackIndex, redIndex, whiteIndex;

	UInt16 method = DRAW_NORMAL;

	if ( draw_grey == true ) {
		method = DRAW_GREY;	
	}

	if ( inverted == true ) {
		method = DRAW_INVERTED;	
	}

	WinPushDrawState();

	bounds.topLeft.x = x;
	bounds.topLeft.y = y;
	bounds.extent.x = width;
	bounds.extent.y = height;

	// Find and cache the indexes in the system palette for the colors we want to draw with.
	whiteIndex = 0;   // White is always 0 in the system palette. 

	if ( method == DRAW_GREY ) {

		// black's index changes for different depths (but is always at the highest palette entry)
		MemSet(&rgb, sizeof(rgb), 0);
		rgb.r=0xdd;
		rgb.g=0xdd;
		rgb.b=0xdd;
		blackIndex = WinRGBToIndex(&rgb);

		// ditto for red.  The shade is used on the cards, but not in grayscale.
		MemSet(&rgb, sizeof(rgb), 0);
		rgb.r=0xdd;
		rgb.g=0xdd;
		rgb.b=0xdd;
		redIndex = WinRGBToIndex(&rgb);
	
	}
	else {	
		// black's index changes for different depths (but is always at the highest palette entry)
		MemSet(&rgb, sizeof(rgb), 0);
		blackIndex = WinRGBToIndex(&rgb);

		// ditto for red.  The shade is used on the cards, but not in grayscale.
		if ( check_color_support() ) {
			MemSet(&rgb, sizeof(rgb), 0);
			rgb.r=0xb0;
			redIndex = WinRGBToIndex(&rgb);
		}
		else {
			redIndex = blackIndex;
		}
	}
	
	if ( method == DRAW_INVERTED ) {
		Int16 tmp = blackIndex;
		blackIndex = whiteIndex;
		whiteIndex = tmp;
		
		redIndex = blackIndex;

	}

	if ( check_color_support() ) {

		// set color - white
		WinSetBackColor(whiteIndex);
		WinSetForeColor(blackIndex);

	}


	// draw a rectangle for the card
	WinEraseRectangle (&bounds, 0);
	WinPaintRectangleFrame (rectangleFrame, &bounds);

	// set color - red or black	
	if ( check_color_support() ) {
		if ( s == diamond || s == heart ) {
			WinSetTextColor(redIndex);
		}
		else {
			WinSetTextColor(blackIndex);
		}
	}
	
	// draw the face
	WinPaintChar( FaceChar(), x + 1, y );


	// draw the suit
	if ( SuitBitmap(method) != 0 ) {

		MemHandle hRsc = DmGetResource(bitmapRsc, SuitBitmap(method) );
		ErrFatalDisplayIf(!hRsc, "Could not get bitmap family resource");
		BitmapType* bitmapP = (BitmapType*) MemHandleLock(hRsc);

		WinPaintBitmap (bitmapP, x + 1, y + 10);

		MemHandleUnlock(hRsc);
		DmReleaseResource(hRsc);

	}

	WinPopDrawState();

} // Draw


Boolean Card::check_color_support() {

	Err err;
	UInt32 supportedDepths;
	
	Boolean supports_color = false;

	err = WinScreenMode(winScreenModeGetSupportedDepths, NULL, NULL,
	     &supportedDepths, NULL);

	err = WinScreenMode(winScreenModeGetSupportsColor, NULL, NULL,
	     NULL, &supports_color);

	return supports_color;
}

Int16 Card::Offset() {
	return (Int16)s * 13 + (Int16)f;
}