#include "Common.h"
#include "GameManager.h"
#include "PlayedCardsGadget.h"

extern GameManager *gManager;

Int16 CPlayedCardsGadget::card_width = 20;
Int16 CPlayedCardsGadget::card_height = 28;
Int16 CPlayedCardsGadget::card_spacing = 14;


CPlayedCardsGadget::CPlayedCardsGadget() {
	Reset();
}

Boolean CPlayedCardsGadget::OnDraw(Boolean& bVisible) {

    bVisible = true;
	Render(true);

    return true;
}


Boolean CPlayedCardsGadget::OnDelete() {
	return true;
}

void CPlayedCardsGadget::Render() {
	Render(false);
}

void CPlayedCardsGadget::Reset() {
	book_count = -1;
}


void CPlayedCardsGadget::Render(Boolean redraw) {

	if ( redraw || book_count != trk->book->GetCount() ) {

		FormPtr  frmP = FrmGetActiveForm();
		UInt16 gadgetIndex = FrmGetObjectIndex(frmP, GetObjectID() );
		FrmGetObjectBounds(frmP, gadgetIndex, &bounds);

		WinHandle handWindowH;
		Err error;


		book_count = trk->book->GetCount();

		//create an offscreen window for the bitmap
		handWindowH = WinCreateOffscreenWindow(bounds.extent.x, bounds.extent.y, screenFormat, &error);
		ErrFatalDisplayIf(error, "Could Not Create Offscreen Window");

		WinHandle screenH = WinSetDrawWindow(handWindowH);

		WinEraseRectangle (&bounds, 0);

//		UInt16 x_offset[] = {5, 31, 57, 31};
//		UInt16 y_offset[] = {15, 1, 15, 38};

		UInt16 x_offset[] = {31, 5, 31, 57};
		UInt16 y_offset[] = {38, 15, 1, 15};

		if ( gManager->CutThroat() == true ) {
			x_offset[2] = x_offset[3];
			y_offset[2] = y_offset[3];
		}

		UInt8 cnt = 0;

		for( CArray<Player *>::iterator i = gManager->players.BeginIterator(); i != gManager->players.EndIterator(); i++ ) {

			if ( (*i)->PlayedCard() != NULL ) {
				Int16 x = x_offset[(*i)->playerIndex];
				Int16 y = y_offset[(*i)->playerIndex];

				(*i)->PlayedCard()->Draw(x, y, card_width, card_height);

			}
			
		}


		//
		// now copy our image into the draw window
		//
		RectangleType  size;
		WinGetDrawWindowBounds(&size);

		//
		// return the draw window to the screen
		//
		WinSetDrawWindow(screenH);


		WinCopyRectangle(handWindowH, screenH, &size,
			bounds.topLeft.x, bounds.topLeft.y, winPaint); // winPaint

		WinDeleteWindow(handWindowH, false);

	}


}


void CPlayedCardsGadget::CurrentTrick(Trick *t) {
	trk = t;
}

Trick *CPlayedCardsGadget::CurrentTrick() {
	return trk;
}
