#include "Common.h"
#include "PlayedCardsHistoryGrid.h"

#include "GameManager.h"

extern GameManager *gManager;


void CPlayedCardsHistoryGrid::DrawItem(Int16 wAbsoluteRow, Int16 wColumn, const RectangleType &  rcBounds ) {

	Int16 card_width = 19;
	Int16 card_height = 26;
	Int16 card_spacing = 12;
	
	UInt16 wIndex = GetRowID(wAbsoluteRow);

	// Text buffer used for filling grid
	CString tmp;
	
	if ( wIndex < gManager->trick_rounds && gManager->tbl->card_history[wAbsoluteRow].GetCount() > wColumn ) {

		//
		// first, draw the name of the player
		//
		tmp = gManager->tbl->card_history[wAbsoluteRow][wColumn]->p->name;

		//
		// if this was the winning card, make it bold
		//	
		if ( gManager->tbl->won_round[wAbsoluteRow][wColumn] ) {
			FntSetFont(boldFont);
		}
		
		if ( FntCharsWidth(tmp, StrLen(tmp)) > 35 ) {
			while ( FntCharsWidth(tmp, StrLen(tmp)) > 35 ) {
				tmp = tmp.Left(StrLen(tmp) - 1);
			}
		}

		WinPaintChars(tmp, StrLen(tmp), rcBounds.topLeft.x + 2, rcBounds.topLeft.y);

		//
		// now draw the card they played
		//
		gManager->tbl->card_history[wAbsoluteRow][wColumn]->c
			->Draw(rcBounds.topLeft.x + 4, rcBounds.topLeft.y + FntCharHeight(), card_width, card_height, false);


		if ( gManager->tbl->won_round[wAbsoluteRow][wColumn] ) {
			FntSetFont(stdFont);
		}

	}

}
