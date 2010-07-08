#include "Common.h"
#include "GameForm.h"
#include "PitchApp.h"
#include "PlayedCardsHistory.h"
#include "Protect.h"
#include "WinningsForm.h"
#include "WinLossRecord.h"

#include "GameManager.h"

#include <PalmNavigator.h>

extern GameManager *gManager;

	Int16 card_width = 16;
	Int16 card_height = 20;
	Int16 card_spacing = 10;


Boolean CGameForm::OnOpen(EventPtr pEvent, Boolean& bHandled) {

	FrmDrawForm(FrmGetActiveForm());
	InitScreen();
	DrawLead();

	EventType event;
	event.eType = nilEvent;
	EvtAddEventToQueue (&event);

	bHandled = false;
	return true;
}

Boolean CGameForm::OnClose(EventPtr pEvent, Boolean& bHandled) {

	for ( Int16 i = 0; i < gManager->numPlayers; i++ ) {
		names[i].Detach();
	}
	
	bidder_name.Detach();

	if ( gManager->CutThroat() == false ) {
		ns_score.Detach();
		ew_score.Detach();
	}
	
	played_cards.Detach();
	player_hand.Detach();

	bHandled = false;
	return false;
}

Boolean CGameForm::OnViewPlayedCards(EventType* pEvent, Boolean& bHandled) {

	CPlayedCardsHistoryDialog pch;
	pch.DoModal();

	CForm::DrawForm();

	played_cards.Render(true);
	player_hand.Render(true);

	bHandled = false;
	return true;
}

Boolean CGameForm::OnViewWinnings(EventType* pEvent, Boolean& bHandled) {

	CWinningsDialog wd;
	wd.DoModal();

	CForm::DrawForm();

	played_cards.Render(true);
	player_hand.Render(true);

	bHandled = false;
	return true;
}

Boolean CGameForm::OnViewWinTotals(EventType* pEvent, Boolean& bHandled) {

	CWinLossDialog frmWinLoss;
	frmWinLoss.DoModal();

	CForm::DrawForm();

	played_cards.Render(true);
	player_hand.Render(true);
	
	bHandled = false;
	return true;
}

Boolean CGameForm::OnQuitGame(EventType* pEvent, Boolean& bHandled) {

	if ( HostGremlinIsRunning() == false ) {
		gManager->Reset();
		CForm::GotoForm(MainForm);
	}	
	
	bHandled = false;
	return true;
}
Boolean CGameForm::OnPrefs(EventType* pEvent, Boolean& bHandled) {

	CString old_name = gManager->players[gManager->humanIndex]->getName();

	CPrefsDialog frmPrefs;
	frmPrefs.DoModal();
	
	if ( old_name.Compare( gManager->players[gManager->humanIndex]->getName() ) != 0 ) {
		names[gManager->humanIndex].Replace((const char *)gManager->players[gManager->humanIndex]->getName() );
	}


	bHandled = false;
	return true;
}
Boolean CGameForm::OnRegister(EventType* pEvent, Boolean& bHandled) {

	while ( load_reg_form() ) {}

	bHandled = false;
	return true;
}
Boolean CGameForm::OnInstructions(EventType* pEvent, Boolean& bHandled) {

	FrmHelp(InstructionsString);

	bHandled = false;
	return true;
}
Boolean CGameForm::OnAbout(EventType* pEvent, Boolean& bHandled) {

	CAboutDialog frmAbout;
	frmAbout.DoModal();
	
	bHandled = false;
	return true;
}
	

void CGameForm::InitScreen() {

	UInt16 player_names[] = {MainP0NameField, 
							MainP1NameField,
							MainP2NameField,
							MainP3NameField};

	if ( gManager->CutThroat() == true ) {
		player_names[2] = player_names[3];
	}


	for ( Int16 i = 0; i < gManager->numPlayers; i++ ) {
		names[i].Attach(this, player_names[i]);
		names[i].Replace((const char *)gManager->players[i]->getName() );		

		if ( gManager->CutThroat() == true ) {

			CString foo;
			foo.Format("%d pts", gManager->scores[i]);

			if ( i == 1 || i == 2 ) {
				CField tmpscore;

				if ( i == 1 ) {
					tmpscore.Attach(this, MainP1ScoreField);
				}
				else {
					tmpscore.Attach(this, MainP3ScoreField);
				}
				
				tmpscore.Replace(foo);
			}
			else {
				CString tmp = gManager->players[i]->getName() + ": " + foo;
				names[i].Replace( tmp );
			}

		}

	}
	
	bidder_name.Attach(this, MainBidderField);
	bidder_name.Replace( (const char *)(*gManager->tbl->winning_bidder)->getName() );

	if ( gManager->CutThroat() == false ) {

		ns_score.Attach(this, MainNSScoreField);
		ew_score.Attach(this, MainEWScoreField);

		char score0str[4];
		char score1str[4];

		StrPrintF(score0str, "%d", gManager->scores[0] );
		StrPrintF(score1str, "%d", gManager->scores[1] );

		ns_score.Replace( score0str );
		ew_score.Replace( score1str );
	}
	else {

		FrmHideObject( FrmGetActiveForm(), FrmGetObjectIndex( FrmGetActiveForm(), NSScoreLabel ) );
		FrmHideObject( FrmGetActiveForm(), FrmGetObjectIndex( FrmGetActiveForm(), EWScoreLabel ) );
	}


	played_cards.Attach(this, MainPlayedCardsGadget );
	played_cards.CurrentTrick(gManager->trk);

	player_hand.Attach(this, MainPlayerHandGadget );
	player_hand.CurrentTrick(gManager->trk);
	player_hand.CurrentPlayer(gManager->players[gManager->humanIndex]);

}


void CGameForm::DrawLead() {

	UInt16 gadgets[] = {MainP0NameField,
				MainP1NameField,
				MainP2NameField,
				MainP3NameField};

	if ( gManager->CutThroat() == true ) {
		gadgets[2] = gadgets[3];
	}

	FormPtr frmP = FrmGetActiveForm();
	FieldPtr fldP;

	CArray<Player*>::iterator tmp = gManager->players.BeginIterator();

	for (Int16 i = 0; i < gManager->numPlayers; i++ ) {

		if ( *tmp == gManager->tbl->lead ) {
			if ( FldGetFont( (FieldPtr)FrmGetObjectPtr(frmP, FrmGetObjectIndex( frmP, gadgets[i] )) ) != boldFont ) {
				FldSetFont((FieldPtr)FrmGetObjectPtr(frmP, FrmGetObjectIndex( frmP, gadgets[i] )), boldFont);
			}
		}
		else {
			if ( FldGetFont( (FieldPtr)FrmGetObjectPtr(frmP, FrmGetObjectIndex( frmP, gadgets[i] )) ) != stdFont ) {
				FldSetFont((FieldPtr)FrmGetObjectPtr(frmP, FrmGetObjectIndex( frmP, gadgets[i] )), stdFont);
			}
		}

		fldP = (FieldType *)FrmGetObjectPtr( frmP, 
				FrmGetObjectIndex( frmP, gadgets[i] ) );

		FntSetFont(stdFont);
		
		tmp++;

	}

}



void CGameForm::OnDraw() {

	played_cards.Render(true);
	player_hand.Render(true);

	char bid_trump_str[2];
	StrPrintF(bid_trump_str, "%d", gManager->tbl->bid  );

	FormPtr frmP = FrmGetActiveForm();
/*
	RectangleType bounds;
	UInt16 gadgetIndex = FrmGetObjectIndex( frmP, MainBidTrumpGadget );
	FrmGetObjectBounds(frmP, gadgetIndex, &bounds);

	// draw the bid
	char bidval = bid_trump_str[0];
	WinPaintChar( bidval, bounds.topLeft.x, bounds.topLeft.y );

	Card foo(gManager->trk->getTrump(), (Card::face_t)1 );

	// now, draw the suit
	MemHandle hRsc = DmGetResource(bitmapRsc, foo.SuitBitmap(false) );
	ErrFatalDisplayIf(!hRsc, "Could not get bitmap family resource");
	BitmapType* bitmapP = (BitmapType*) MemHandleLock(hRsc);

	WinPaintBitmap (bitmapP, bounds.topLeft.x + 6, bounds.topLeft.y);

	MemHandleUnlock(hRsc);
	DmReleaseResource(hRsc);
*/
	// handle MainBidTrumpGadget here also
	MemHandle hRsc;
	BitmapType* bitmapP;

	switch ( gManager->tbl->trump ) {

		case Card::heart:
			hRsc = DmGetResource(bitmapRsc, HeartBitmapFamily );
			break;
		case Card::diamond:
			hRsc = DmGetResource(bitmapRsc, DiamondBitmapFamily );
			break;
		case Card::club:
			hRsc = DmGetResource(bitmapRsc, ClubBitmapFamily );
			break;
		case Card::spade:
			hRsc = DmGetResource(bitmapRsc, SpadeBitmapFamily );
			break;
	}

	RectangleType bounds;

//	FormPtr frmP = FrmGetActiveForm();
	UInt16 gadgetIndex = FrmGetObjectIndex(frmP, MainBidTrumpGadget);
	FrmGetObjectBounds(frmP, gadgetIndex, &bounds);
	char bidstr[4];
	StrPrintF(bidstr, "%d", gManager->tbl->bid);
	WinPaintChar(bidstr[0], bounds.topLeft.x, bounds.topLeft.y );

	ErrFatalDisplayIf(!hRsc, "Could not get bitmap family resource");
	bitmapP = (BitmapType*) MemHandleLock(hRsc);
	WinDrawBitmap (bitmapP, bounds.topLeft.x + FntCharWidth(bidstr[0]) + 1, bounds.topLeft.y);
	MemHandleUnlock(hRsc);
	DmReleaseResource(hRsc);

}


void CGameForm::DrawPlayerHand(UInt8 index, UInt16 x, UInt16 y) {

	gManager->players[index]->sort_hand();

	UInt8 cnt = 0;

	UInt16 new_x = 2;
	UInt16 new_y = 1;

	for (cnt = 0; cnt < gManager->players[index]->hand.GetCount(); cnt++ ) {
			
		Boolean can_play = true;
		
		can_play = gManager->players[index]->followSuit(gManager->trk, gManager->players[index]->hand[cnt]);

		gManager->players[index]->hand[cnt]->Draw(x + new_x, y + new_y, card_width, card_height, true);

		new_x += card_spacing;
	}

}

Boolean CGameForm::OnNilEvent(EventPtr pEvent, Boolean& bHandled) {

	if ( gManager->IsTrickOver() ) {

		gManager->LongDelay();

		gManager->HandleEndOfTrick();

		if ( gManager->IsHandOver() ) {
			CForm::GotoForm(ScoringForm);
		}

		//
		// redraw this form
		//
		else {

			DrawLead();
			played_cards.Reset();

			CForm::DrawForm();
			CheckGameCondition();
		}

	}
	else {

		CheckGameCondition();

	}

	bHandled = false;
	return false;
}

void CGameForm::CheckGameCondition() {

	//
	// if we're not done with the trick and it's not the
	// human's turn...
	//
	if ( ! gManager->IsTrickOver() &&
			gManager->current != gManager->human ) {

		DrawLead();

		//
		// then get the played card from everyone up to the human
		//

		if ( gManager->GetNextPlay( gManager->trk ) ) {


			Int16 i = (*gManager->current)->playerIndex;
/*			if ( i != 0 ) {

				DrawPlayerHand(i, 0, 0);
				(*gManager->current)->PlayedCard()->Draw(140, 0, card_width, card_height, false);

				gManager->LongDelay();
				gManager->LongDelay();

			}
*/

			gManager->LongDelay();

			gManager->NextPlayedCard( (*gManager->current), 
				(*gManager->current)->PlayedCard() );
				
			played_cards.Render(true);

		} // if ( played card )
	
		if ( gManager->current == gManager->human ) {
			player_hand.Render(true);
		}
	

		EventType event;
		event.eType = nilEvent;
		EvtAddEventToQueue (&event);

	} // if
	else {

		if ( gManager->IsTrickOver() ) {

			EventType event;
			event.eType = nilEvent;
			EvtAddEventToQueue (&event);
		}
	
	}
 
} // CheckGameCondition


Boolean CGameForm::OnPenDown(EventPtr pEvent, Boolean& bHandled) {

	FormPtr frmP = FrmGetActiveForm();
	RectangleType  bounds;
	UInt16 gadgetIndex = FrmGetObjectIndex(frmP, MainPlayerHandGadget);
	FrmGetObjectBounds(frmP, gadgetIndex, &bounds);

	//
	// check and see if this event happened in the gadget
	//
	if ( gManager->current == gManager->human &&
			pEvent->screenX >= bounds.topLeft.x && 
			pEvent->screenX <= bounds.topLeft.x + bounds.extent.x &&
			pEvent->screenY >= bounds.topLeft.y && 
			pEvent->screenY <= bounds.topLeft.y + bounds.extent.y ) {
		player_hand.OnPenDown(pEvent, bHandled);
	}

	bHandled = false;
	return false;
}

Boolean CGameForm::OnPenUp(EventPtr pEvent, Boolean& bHandled) {

	FormPtr frmP = FrmGetActiveForm();
	RectangleType  bounds;
	UInt16 gadgetIndex = FrmGetObjectIndex(frmP, MainPlayerHandGadget);
	FrmGetObjectBounds(frmP, gadgetIndex, &bounds);

	//
	// check and see if this event happened in the gadget
	//
	if ( gManager->current == gManager->human &&
			pEvent->screenX >= bounds.topLeft.x && 
			pEvent->screenX <= bounds.topLeft.x + bounds.extent.x &&
			pEvent->screenY >= bounds.topLeft.y && 
			pEvent->screenY <= bounds.topLeft.y + bounds.extent.y ) {

		//
		// if this comes back true, then the user picked a card
		//
		if ( player_hand.OnPenUp(pEvent, bHandled) ) {
		
			//
			// play the card
			//
			gManager->NextPlayedCard( player_hand.CurrentPlayer(), 
				player_hand.CurrentPlayer()->PlayedCard() );

			// render anything that needs doing
			player_hand.Render(true);
			played_cards.Render(true);
			
			// check the game condition
			CheckGameCondition();
		}

	}
	else {
		player_hand.Reset();
		player_hand.Render(true);
	}

	bHandled = false;
	return false;
}

Boolean CGameForm::OnKeyDown(EventPtr pEvent, Boolean& bHandled) {

	WChar 		chr			= pEvent->data.keyDown.chr;

	switch(chr) {

		case vchrRockerUp:
		case vchrPageUp:
			player_hand.MoveLeft();
			break;
		case vchrRockerDown:
		case vchrPageDown:
			player_hand.MoveRight();
			break;
		case vchrRockerCenter:
			if ( player_hand.Select() ) {
				//
				// play the card
				//
				gManager->NextPlayedCard( player_hand.CurrentPlayer(), 
					player_hand.CurrentPlayer()->PlayedCard() );

				// render anything that needs doing
				player_hand.Render(true);
				played_cards.Render(true);
				
				// check the game condition
				CheckGameCondition();
			}
			break;
		case vchrRockerLeft:
			player_hand.MoveLeft();
			break;
		case vchrRockerRight:
			player_hand.MoveRight();
			break;
	}
	
	bHandled = false;
	return false;
}
