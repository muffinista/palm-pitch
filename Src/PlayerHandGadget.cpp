#include "Common.h"
#include "PlayerHandGadget.h"

#include "GameManager.h"

Int16 CPlayerHandGadget::card_width = 20;
Int16 CPlayerHandGadget::card_height = 28;
Int16 CPlayerHandGadget::card_spacing = 14;

extern GameManager *gManager;

CPlayerHandGadget::CPlayerHandGadget() {
	Reset();
}

Boolean CPlayerHandGadget::OnDraw(Boolean& bVisible) {

    bVisible = true;

	if ( trk == NULL ) {
		show_all = true;
	}

	Render(true);

    return true;
}


void CPlayerHandGadget::Render() {
	Render(false);
}

void CPlayerHandGadget::Reset() {
 	handling_input = false;
 	screen_x = -1;
 	screen_y = -1;
	active_card = -1;
	show_all = false;
}


void CPlayerHandGadget::Render(Boolean redraw) {

	if ( redraw ) {

		FormPtr  frmP = FrmGetActiveForm();
		UInt16 gadgetIndex = FrmGetObjectIndex(frmP, GetObjectID() );
		FrmGetObjectBounds(frmP, gadgetIndex, &bounds);
	
		WinHandle handWindowH;
		Err error;

		CurrentPlayer()->sort_hand();

		//create an offscreen window for the bitmap
		handWindowH = WinCreateOffscreenWindow(bounds.extent.x, bounds.extent.y, screenFormat, &error);
		ErrFatalDisplayIf(error, "Could Not Create Offscreen Window");

		WinHandle screenH = WinSetDrawWindow(handWindowH);

		// draw the user's hand onto MainPlayerHandGadget

		UInt8 cnt = 0;

		UInt16 new_x = 2;
		UInt16 new_y = 1;

		for (cnt = 0; cnt < CurrentPlayer()->hand.GetCount(); cnt++ ) {
				
			Boolean can_play = true;
			
			if ( ! show_all && gManager->Status() == ReadyToPlay ) {
				can_play = CurrentPlayer()->followSuit(trk, CurrentPlayer()->hand[cnt]);
			}

			if ( show_all || gManager->Status() != ReadyToPlay || can_play ) {
				CurrentPlayer()->hand[cnt]->Draw(new_x, new_y, card_width, card_height, false);
			}
			else {
				CurrentPlayer()->hand[cnt]->Draw(new_x, new_y, card_width, card_height, true);
			}

			new_x += card_spacing;
		}


		// now copy our image into the draw window
		RectangleType  size;

		//WinGetBounds(handWindowH, &size);
		WinGetDrawWindowBounds(&size);

		//return the draw window to the screen
		WinSetDrawWindow(screenH);

		WinCopyRectangle(handWindowH, screenH, &size,
			bounds.topLeft.x, bounds.topLeft.y, winPaint);

		WinDeleteWindow(handWindowH, false);

	}
}

Boolean CPlayerHandGadget::OnPenDown(EventPtr event, Boolean& bHandled) {

	if ( gManager->current == gManager->human &&
		event->screenY < bounds.topLeft.y + bounds.extent.y &&
		 event->screenY > bounds.topLeft.y &&
		 event->screenX < bounds.topLeft.x + bounds.extent.x &&
		 event->screenX > bounds.topLeft.x ) {

		choice = 0;
		CArray<Card *> hand = CurrentPlayer()->hand;

		handling_input = true;

		UInt16 x_offset = event->screenX - bounds.topLeft.x;

		// if there's only one card, we need to make sure a click 
		// anywhere on the card is valid
		if ( hand.GetCount() == 1 ) {
			choice = x_offset / card_width;
		}
		else {
			choice = (x_offset / (card_width - (card_width - card_spacing)));
			
			if (x_offset > card_spacing * hand.GetCount() &&
				x_offset <= card_spacing * ( hand.GetCount() - 1 ) + card_width ) {

				choice = hand.GetCount() - 1;

			}

		}

		if ( choice < hand.GetCount() ) {

			// draw an inverted copy of the card
			Int16 x = (choice * card_spacing) + 2;
			Int16 y = bounds.topLeft.y + 1;

			hand[choice]->Draw(bounds.topLeft.x + x, y, card_width, card_height, false, true);

		} // if

	 } // if

	bHandled = false;
	return false;
}


Boolean CPlayerHandGadget::OnPenUp(EventPtr event, Boolean& bHandled) {

	if ( handling_input ) {

		Boolean noHumanCard = true;

		// look and see if the user selected a card
		if ( gManager->current == gManager->human &&
			event->screenY < bounds.topLeft.y + bounds.extent.y &&
			 event->screenY > bounds.topLeft.y &&
			 event->screenX < bounds.topLeft.x + bounds.extent.x &&
			 event->screenX > bounds.topLeft.x ) {

//			CArray<Card *> hand = CurrentPlayer()->hand;

			UInt16 x_offset = event->screenX - bounds.topLeft.x;
			if ( CurrentPlayer()->hand.GetCount() == 1 ) {
				choice = x_offset / card_width;
			}
			else {
				choice = (x_offset / (card_width - (card_width - card_spacing)));

				if (x_offset > card_spacing * CurrentPlayer()->hand.GetCount() &&
					x_offset <= card_spacing * ( CurrentPlayer()->hand.GetCount() - 1 ) + card_width ) {

					choice = CurrentPlayer()->hand.GetCount() - 1;

				}
			}


			if ( choice < CurrentPlayer()->hand.GetCount() ) {

				if ( CurrentPlayer()->followSuit(trk, CurrentPlayer()->hand[choice]) &&
					((trk->no_trump_first_trick == true && 
					CurrentPlayer()->hand[choice]->Suit() != trk->getTrump() &&
					trk->FirstTrickP()) || !trk->FirstTrickP()  || trk->no_trump_first_trick == false ) ) {


					CurrentPlayer()->played_cards.Add(CurrentPlayer()->hand[choice]);
					CurrentPlayer()->played_card = CurrentPlayer()->hand[choice];

					CurrentPlayer()->hand.Delete( choice );

					noHumanCard = false;
					bHandled = true;
					return true;
				}

			} // if

		 } // if


		if ( noHumanCard && handling_input ) {
			handling_input = false;
			Render(true);
		}

	} // if ( handling input )

	bHandled = true;
	return false;
}


void CPlayerHandGadget::ResetHighlight() {

	CArray<Card *> hand = CurrentPlayer()->hand;

	UInt16 new_x = 2 + bounds.topLeft.x;
	UInt16 new_y = 1 + bounds.topLeft.y;

	for (UInt16 cnt = 0; cnt < hand.GetCount(); cnt++ ) {
			
		Boolean can_play = true;
		
		if ( ! show_all && gManager->Status() == ReadyToPlay ) {
			can_play = CurrentPlayer()->followSuit(trk, hand[cnt]);
		}

		if ( show_all || gManager->Status() != ReadyToPlay || can_play ) {
			hand[cnt]->Draw(new_x, new_y, card_width, card_height, false);
		}
		else {
			hand[cnt]->Draw(new_x, new_y, card_width, card_height, true);
		}

		new_x += card_spacing;
	}

}


void CPlayerHandGadget::DrawHighlight() {

	if ( active_card != -1 ) {

		CArray<Card *> hand = CurrentPlayer()->hand;

		Int16 x = (active_card * card_spacing) + 2;
		Int16 y = bounds.topLeft.y + 1;

		hand[active_card]->Draw(bounds.topLeft.x + x, y, card_width, card_height, false, true);
	}

}


void CPlayerHandGadget::MoveLeft() {

	ResetHighlight();

	if ( active_card <= 0 ) {	
		active_card = CurrentPlayer()->hand.GetCount() - 1;
	}
	else {
		active_card--;
	}


	Boolean can_play = active_card != -1 && CurrentPlayer()->followSuit(trk, CurrentPlayer()->hand[active_card]) &&
		((trk->no_trump_first_trick == true && 
		CurrentPlayer()->hand[active_card]->Suit() != trk->getTrump() &&
		trk->FirstTrickP()) || !trk->FirstTrickP()  || trk->no_trump_first_trick == false );

	while ( ! can_play  ) {

		if ( active_card <= 0 ) {	
			active_card = CurrentPlayer()->hand.GetCount() - 1;
		}
		else {
			active_card--;
		}

		can_play = CurrentPlayer()->followSuit(trk, CurrentPlayer()->hand[active_card]) &&
			((trk->no_trump_first_trick == true && 
			CurrentPlayer()->hand[active_card]->Suit() != trk->getTrump() &&
			trk->FirstTrickP()) || !trk->FirstTrickP()  || trk->no_trump_first_trick == false );

	}


	DrawHighlight();

}


void CPlayerHandGadget::MoveRight() {

	ResetHighlight();

	active_card++;

	UInt16 cnt = CurrentPlayer()->hand.GetCount();
	if ( active_card >= cnt ) {	
		active_card = 0;
	}


	Boolean can_play = active_card != -1 && CurrentPlayer()->followSuit(trk, CurrentPlayer()->hand[active_card]) &&
		((trk->no_trump_first_trick == true && 
		CurrentPlayer()->hand[active_card]->Suit() != trk->getTrump() &&
		trk->FirstTrickP()) || !trk->FirstTrickP()  || trk->no_trump_first_trick == false );

	while ( ! can_play  ) {

		active_card++;

		if ( active_card >= cnt ) {	
			active_card = 0;
		}

		can_play = CurrentPlayer()->followSuit(trk, CurrentPlayer()->hand[active_card]) &&
			((trk->no_trump_first_trick == true && 
			CurrentPlayer()->hand[active_card]->Suit() != trk->getTrump() &&
			trk->FirstTrickP()) || !trk->FirstTrickP()  || trk->no_trump_first_trick == false );

	}

	DrawHighlight();

}

Boolean CPlayerHandGadget::Select() {

	Boolean can_play = active_card != -1 && CurrentPlayer()->followSuit(trk, CurrentPlayer()->hand[active_card]) &&
		((trk->no_trump_first_trick == true && 
		CurrentPlayer()->hand[active_card]->Suit() != trk->getTrump() &&
		trk->FirstTrickP()) || !trk->FirstTrickP()  || trk->no_trump_first_trick == false );

	if ( can_play ) {

		CurrentPlayer()->played_cards.Add(CurrentPlayer()->hand[active_card]);
		CurrentPlayer()->played_card = CurrentPlayer()->hand[active_card];

		p->hand.Delete( active_card );
		active_card = -1;
		return true;

	}
	else {

		return false;
	
	}

}

void CPlayerHandGadget::CurrentTrick(Trick *t) {
	trk = t;
}

Trick *CPlayerHandGadget::CurrentTrick() {
	return trk;
}

void CPlayerHandGadget::CurrentPlayer(Player *tmp) {
	p = tmp;
}

Player *CPlayerHandGadget::CurrentPlayer() {
	return p;
}


Boolean CPlayerHandGadget::OnDelete() {
	return true;
}
