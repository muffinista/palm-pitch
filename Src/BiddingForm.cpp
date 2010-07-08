#include "Common.h"
#include "BiddingForm.h"
#include "PitchApp.h"

#include "GameManager.h"


extern GameManager *gManager;


Boolean CBiddingForm::OnOpen(EventPtr pEvent, Boolean& bHandled) {

	InitDisplay();

	player_has_bid = false;

	FormPtr frmP = FrmGetActiveForm();
	FrmDrawForm(frmP);
	
	//
	// if the user exited the app from the bidding form, we will
	// restart the bidding process
	//
	GameStatus tmp = gManager->Status();
	if ( tmp == SetHandTrump || tmp == GetHandBids ) {
		gManager->Status(GetHandBids);
		gManager->NewTrick(false);
	}

	//
	// start bidding to the left of the dealer
	//
	gManager->tbl->current_bidder = 
		gManager->getNextPlayerIter(gManager->tbl->dealer);

	EventType event;
	event.eType = nilEvent;
	EvtAddEventToQueue (&event);

	bHandled = false;
	return true;
	
}

Boolean CBiddingForm::OnClose(EventPtr pEvent, Boolean& bHandled) {

	player_hand.Detach();

	for ( Int16 i = 0; i < gManager->numPlayers; i++ ) {
		bids[i].Detach();
		names[i].Detach();
	}

	bid_winner.Detach();

	if ( gManager->CutThroat() == false ) {
		ns_score.Detach();
		ew_score.Detach();
	}

	bHandled = false;
	return true;
}


void CBiddingForm::HighlightActiveBidder() {

	Int16 player_index = (*gManager->tbl->current_bidder)->playerIndex;

	for ( Int16 i = 0; i < gManager->numPlayers; i++ ) {

		FontID tmpFont;

		if ( player_index == i ) {
			tmpFont = boldFont;
		}
		else {
			tmpFont = stdFont;
		}

		if ( names[i].GetFont() != tmpFont ) {
			names[i].SetFont( tmpFont );
		}

	}

}

Boolean CBiddingForm::OnNilEvent(EventPtr pEvent, Boolean& bHandled) {

	if ( gManager->Status() == GetHandBids ) {

		HighlightActiveBidder();

		FormPtr frmP = FrmGetActiveForm();

		Int16 player_index = (*gManager->tbl->current_bidder)->playerIndex;


		//
		// if this is a human player, we need to render the screen widgets for their bid
		//
		if ( player_index == gManager->humanIndex && player_has_bid == false ) {

			player_hand.Render(true);

			Int16 current_bid = 0;

			if ( (*gManager->tbl->dealer)->playerIndex != gManager->humanIndex || ! gManager->dealer_take_bid ) {
				current_bid = gManager->tbl->high_bid;
			}
			else {
				current_bid = gManager->tbl->high_bid - 1;
			}
			
			if ( (*gManager->tbl->dealer)->playerIndex == gManager->humanIndex && gManager->tbl->high_bid < 2 ) {
				CtlSetEnabled((ControlType *)FrmGetObjectPtr( frmP, FrmGetObjectIndex( frmP, PlayerBid4PushButton )), false);	
				CtlSetLabel ((ControlType *)FrmGetObjectPtr( frmP, FrmGetObjectIndex( frmP, PlayerBid4PushButton )), "-4-");
				CtlSetEnabled((ControlType *)FrmGetObjectPtr( frmP, FrmGetObjectIndex( frmP, PlayerBid3PushButton )), false);
				CtlSetLabel ((ControlType *)FrmGetObjectPtr( frmP, FrmGetObjectIndex( frmP, PlayerBid3PushButton )), "-3-");
				CtlSetEnabled((ControlType *)FrmGetObjectPtr( frmP, FrmGetObjectIndex( frmP, PlayerBidPassPushButton )), false);
				CtlSetLabel ((ControlType *)FrmGetObjectPtr( frmP, FrmGetObjectIndex( frmP, PlayerBidPassPushButton )), "-Pass-");
			}
			else {
				switch (current_bid) {
					case 5:
						CtlSetEnabled((ControlType *)FrmGetObjectPtr( frmP, FrmGetObjectIndex( frmP, PlayerBidSmudgePushButton )), false);	
						CtlSetLabel ((ControlType *)FrmGetObjectPtr( frmP, FrmGetObjectIndex( frmP, PlayerBidSmudgePushButton )), "-S-");
					case 4:
						CtlSetEnabled((ControlType *)FrmGetObjectPtr( frmP, FrmGetObjectIndex( frmP, PlayerBid4PushButton )), false);	
						CtlSetLabel ((ControlType *)FrmGetObjectPtr( frmP, FrmGetObjectIndex( frmP, PlayerBid4PushButton )), "-4-");
					case 3:
						CtlSetEnabled((ControlType *)FrmGetObjectPtr( frmP, FrmGetObjectIndex( frmP, PlayerBid3PushButton )), false);
						CtlSetLabel ((ControlType *)FrmGetObjectPtr( frmP, FrmGetObjectIndex( frmP, PlayerBid3PushButton )), "-3-");
					case 2:
						CtlSetEnabled((ControlType *)FrmGetObjectPtr( frmP, FrmGetObjectIndex( frmP, PlayerBid2PushButton )), false);
						CtlSetLabel ((ControlType *)FrmGetObjectPtr( frmP, FrmGetObjectIndex( frmP, PlayerBid2PushButton )), "-2-");
				}
			}

		} // if if ( player_index == 3 && player_has_bid == false )


		//
		// handle processing actual bids here - get one automatically if this player isn't
		// a human, or if the human has already bid
		//
		if ( player_index != gManager->humanIndex || player_has_bid == true ) {

			Boolean player_did_bid = gManager->GetNextBid(gManager->trk, false );
			Int16 tmp_bid = (*gManager->tbl->current_bidder)->Bid();

			if ( player_did_bid && 
					gManager->tbl->current_bidder == gManager->tbl->winning_bidder &&
					(tmp_bid >= 2) ) {

				char x[10];
				StrPrintF(x, "bids %d", tmp_bid );
				bidstr = x;
			}
			else {
				bidstr = "passes";
			}
				
			bids[(*gManager->tbl->current_bidder)->playerIndex].Replace(bidstr);


			//
			// if we just got the dealer's bid, then we are all done
			//
			if ( gManager->tbl->current_bidder == gManager->tbl->dealer ) {

				//
				// at this point we need to set trump...
				//	
				gManager->Status(SetHandTrump);


				if ( (*gManager->tbl->winning_bidder)->playerIndex == gManager->humanIndex ) {
					CPlayerTrumpForm frmPlayerTrump;
					frmPlayerTrump.DoModal();
				}

				FrmDrawForm(frmP);

				//
				// ... and display the final results
				//

				Card::suit_t foo = (*gManager->tbl->winning_bidder)->Trump();
				gManager->tbl->trump = foo;
				gManager->trk->no_trump_first_trick = (*gManager->tbl->winning_bidder)->NoTrumpFirstTrickP();

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

				if ( gManager->trk->no_trump_first_trick ) {
					FrmCustomAlert(NoTrumpFirstTrickAlert, (*gManager->tbl->winning_bidder)->name, "", "");
				}


				RectangleType bounds;

				UInt16 gadgetIndex = FrmGetObjectIndex(frmP, BiddingTrumpGadget);
				FrmGetObjectBounds(frmP, gadgetIndex, &bounds);
				WinPaintChars("Trump Is: ", StrLen("Trump Is: "), bounds.topLeft.x, bounds.topLeft.y );

				ErrFatalDisplayIf(!hRsc, "Could not get bitmap family resource");
				bitmapP = (BitmapType*) MemHandleLock(hRsc);
				WinDrawBitmap (bitmapP, bounds.topLeft.x + 40, bounds.topLeft.y);
				MemHandleUnlock(hRsc);
				DmReleaseResource(hRsc);

				UInt32 hsStatusVersion;
				
				if (FtrGet (hsFtrCreator, hsFtrIDNavigationSupported, &hsStatusVersion) == 0) {
					FrmGlueNavObjectTakeFocus(FrmGetActiveForm(), BiddingOKButton );
				}

			
			} // if ( dealer bid )

			else {

				// move along to the next player
				gManager->tbl->current_bidder = gManager->getNextPlayerIter(gManager->tbl->current_bidder);

				EventType event;
				event.eType = nilEvent;
				EvtAddEventToQueue (&event);

				// pause here
//				SysTaskDelay(SysTicksPerSecond());
				gManager->ShortDelay();
			
			}


		} // if ( player_index != 3 || player_has_bid == true )


	} // if GetHandBids

	bHandled = false;
	return true;
}


Boolean CBiddingForm::OnChooseBid(EventPtr pEvent, Boolean& bHandled) {

	UInt32 hsStatusVersion;
	
	if (FtrGet (hsFtrCreator, hsFtrIDNavigationSupported, &hsStatusVersion) == 0) {
		FrmGlueNavObjectTakeFocus(FrmGetActiveForm(), SetBidButton );
	}
	
	bHandled = false;
	return false;

}

Boolean CBiddingForm::OnSetBid(EventPtr pEvent, Boolean& bHandled) {

	Int16 player_index = (*gManager->tbl->current_bidder)->playerIndex;

	if ( gManager->Status() == GetHandBids && player_index == gManager->humanIndex && player_has_bid == false ) {

		FormPtr frmP = FrmGetActiveForm();

		UInt16 bidval = 0;

		if ( CtlGetValue((ControlType *)FrmGetObjectPtr( frmP, FrmGetObjectIndex( frmP, PlayerBid2PushButton ) )) ) {
			bidval = 2;
		}
		else if ( CtlGetValue((ControlType *)FrmGetObjectPtr( frmP, FrmGetObjectIndex( frmP, PlayerBid3PushButton ) ) ) ){
			bidval = 3;
		}
		else if ( CtlGetValue((ControlType *)FrmGetObjectPtr( frmP, FrmGetObjectIndex( frmP, PlayerBid4PushButton ) ) ) ) {
			bidval = 4;
		}
		else if ( CtlGetValue((ControlType *)FrmGetObjectPtr( frmP, FrmGetObjectIndex( frmP, PlayerBidSmudgePushButton ) ) ) ) {
			bidval = 5;
		}
		else {
			//PlayerBidPassPushButton
			bidval = 0;
		}

		(*gManager->tbl->current_bidder)->Bid(bidval);
		player_has_bid = true;	

		EventType event;
		event.eType = nilEvent;
		EvtAddEventToQueue (&event);
		
	}

	bHandled = false;
	return true;

} // OnSetBid


Boolean CBiddingForm::OnOK(EventPtr pEvent, Boolean& bHandled) {

	if ( gManager->Status() == SetHandTrump ) {

		gManager->current = gManager->getPlayerIter(gManager->tbl->lead->playerIndex);

		//
		// switch into game play mode
		//
		gManager->Status(ReadyToPlay);
		CForm::GotoForm(GameForm);

	}

	return true;
}


void  CBiddingForm::InitDisplay() {

	UInt16 player_names[] = {BiddingP0NameField, BiddingP1NameField, BiddingP2NameField, BiddingP3NameField };
	UInt16 player_bids[] = {BiddingP0BidField, BiddingP1BidField, BiddingP2BidField, BiddingP3BidField };

	if ( gManager->CutThroat() == true ) {
		player_names[2] = player_names[3];
		player_bids[2] = player_bids[3];

		FrmHideObject( FrmGetActiveForm(), FrmGetObjectIndex( FrmGetActiveForm(), BiddingEWScoreField ) );
		FrmHideObject( FrmGetActiveForm(), FrmGetObjectIndex( FrmGetActiveForm(), BiddingUnnamed1011Label ) );
		FrmHideObject( FrmGetActiveForm(), FrmGetObjectIndex( FrmGetActiveForm(), BiddingNSScoreField ) );
		FrmHideObject( FrmGetActiveForm(), FrmGetObjectIndex( FrmGetActiveForm(), BiddingLabel1Label ) );


		FrmHideObject( FrmGetActiveForm(), FrmGetObjectIndex( FrmGetActiveForm(), BiddingP2NameField ) );
		FrmHideObject( FrmGetActiveForm(), FrmGetObjectIndex( FrmGetActiveForm(), BiddingP2BidField ) );
	}

	for ( Int16 i = 0; i < gManager->numPlayers; i++ ) {

		bids[i].Attach(this, player_bids[i]);
		names[i].Attach(this, player_names[i]);
		
		if ( gManager->CutThroat() == true ) {
			CString foo;
			foo.Format("%d", gManager->scores[i]);
			CString tmp = gManager->players[i]->getName() + ": " + foo;
			names[i].Replace( tmp );
		}
		else {
			names[i].Replace( (const char *)gManager->players[i]->getName() );
		}

	}


	if ( gManager->CutThroat() == false ) {
		ns_score.Attach(this, BiddingNSScoreField);
		ew_score.Attach(this, BiddingEWScoreField);

		char score0str[4];
		char score1str[4];

		StrPrintF(score0str, "%d", gManager->scores[0]);
		StrPrintF(score1str, "%d", gManager->scores[1]);

		ns_score.Replace( score0str );
		ew_score.Replace( score1str );
	}

	player_hand.Attach(this, PlayerBidPlayerHandGadget );
	player_hand.CurrentPlayer(gManager->players[gManager->humanIndex]);

	bid_winner.Attach(this, BidWinnerField);
}


Boolean CBiddingForm::OnHelp(EventPtr pEvent, Boolean& bHandled) {
	FrmHelp(InstructionsString);
	return true;
}

Boolean CBiddingForm::OnAbout(EventType* pEvent, Boolean& bHandled) {

	CAboutDialog frmAbout;
	frmAbout.DoModal();
	
	bHandled = false;
	return true;
}

Boolean CBiddingForm::OnCancel(EventPtr pEvent, Boolean& bHandled) {

	if ( HostGremlinIsRunning() == false ) {
		gManager->Reset();
		CForm::GotoForm(MainForm);
	}

	bHandled = false;
	return true;
}

