#include "Common.h"
#include "ScoringForm.h"
#include "PitchApp.h"
#include "PlayedCardsHistory.h"
#include "WinningsForm.h"
#include "WinLossRecord.h"

#include "GameManager.h"
#include "PlayerHandGadget.h"

extern GameManager *gManager;

Boolean CScoringForm::OnOpen(EventPtr pEvent, Boolean& bHandled) {

	HostTraceOutputTL(sysErrorClass, "OnOpen");

	gManager->Status(DisplayHandResults);

	high_field.Attach(this, ScoringHighWinnerField);
	low_field.Attach(this, ScoringLowWinnerField);
	jack_field.Attach(this, ScoringJackWinnerField);
	game_field.Attach(this, ScoringGameWinnerField);

	bid_results.Attach(this, ScoringBidResultsField);

	CForm::DrawForm();

	HostTraceOutputTL(sysErrorClass, "OnOpen Done");

	bHandled = false;
	return true;
}

Boolean CScoringForm::OnClose(EventPtr pEvent, Boolean& bHandled) {

	HostTraceOutputTL(sysErrorClass, "OnClose");

	high_field.Detach();
	low_field.Detach();
	jack_field.Detach();
	game_field.Detach();

	bid_results.Detach();

	HostTraceOutputTL(sysErrorClass, "OnClose done");

	bHandled = false;
	return true;
}



void CScoringForm::OnDraw() {

	HostTraceOutputTL(sysErrorClass, "OnDraw");

	Boolean won_bid = false;
	Int16 high_p = -1, low_p = -1, jack_p = -1, game_p = -1;
	Card::face_t high_c, low_c;

	Int16 points[3];
	Int16 old_points[3];
	
	points[0] = gManager->scores[0];
	points[1] = gManager->scores[1];
	points[2] = gManager->scores[2];

	old_points[0] = gManager->scores[0];
	old_points[1] = gManager->scores[1];
	old_points[2] = gManager->scores[2];



	Boolean smudge = false;

	won_bid = gManager->trk->CalculateGamePoints(&high_p, &low_p, &jack_p, &game_p, 
									&high_c, &low_c, &smudge );


	if ( gManager->CutThroat() == false ) {
	
		if ( smudge ) {
			switch ( (*gManager->tbl->winning_bidder)->playerIndex ) {
				case 0:
				case 2:
					points[0]++;
					break;
				case 1:
				case 3:
					points[1]++;
					break;
			}
		}
	
		switch( high_p ) {
			case 0:
			case 2:
				points[0]++;
				break;
			case 1:
			case 3:
				points[1]++;
				break;
		}
		
		switch( low_p ) {
			case 0:
			case 2:
				points[0]++;
				break;
			case 1:
			case 3:
				points[1]++;
				break;
		}
		
		switch( game_p ) {
			case 0:
			case 2:
				points[0]++;
				break;
			case 1:
			case 3:
				points[1]++;
				break;
		}
		
		switch( jack_p ) {
			case 0:
			case 2:
				points[0]++;
				break;
			case 1:
			case 3:
				points[1]++;
				break;
		}
	}
	else {
	
		points[high_p]++;
		points[low_p]++;
		
		if ( game_p != -1 ) {
			points[game_p]++;
		}
		
		if ( jack_p != -1 ) {
			points[jack_p]++;
		}
		

	}


	if ( high_p != -1 ) {
		high_field.Replace( (const char *)gManager->getPlayer(high_p)->getName() );
	}

	if ( low_p != -1 ) {
		low_field.Replace( (const char *)gManager->getPlayer(low_p)->getName() );
	}

	if ( jack_p != -1 ) {
		jack_field.Replace( (const char *)gManager->getPlayer(jack_p)->getName() );
	}
	else {
		jack_field.Replace("none");
	}


	Card foo(gManager->trk->getTrump(), high_c);
	Card foo2(gManager->trk->getTrump(), low_c);

	FormPtr frmP = FrmGetActiveForm();

	RectangleType  bounds;
	UInt16 gadgetIndex = FrmGetObjectIndex(frmP, HighCardGadget );
	FrmGetObjectBounds(frmP, gadgetIndex, &bounds);
	foo.Draw(bounds.topLeft.x, bounds.topLeft.y, CPlayerHandGadget::card_width, CPlayerHandGadget::card_height);

	gadgetIndex = FrmGetObjectIndex(frmP, LowCardGadget );
	FrmGetObjectBounds(frmP, gadgetIndex, &bounds);
	foo2.Draw(bounds.topLeft.x, bounds.topLeft.y, CPlayerHandGadget::card_width, CPlayerHandGadget::card_height);


	char gamestr[80];

	if ( gManager->CutThroat() == false ) {
		if ( game_p == 1 ) {
			StrPrintF(gamestr, "E/W team wins, %d - %d", 
				gManager->GetTeamPoints('b'), gManager->GetTeamPoints('a') );
		}
		else if ( game_p == 0 ) {
			StrPrintF(gamestr, "N/S team wins, %d - %d",
				gManager->GetTeamPoints('a'), gManager->GetTeamPoints('b') );
		}
		else {
			StrPrintF(gamestr, "teams tied on points at %d",
				gManager->GetTeamPoints('a') );
		}
	}
	else {
		if ( game_p == 2 ) {
			StrPrintF(gamestr, "%s wins, %d - %d - %d",
				(const char *)gManager->players[2]->getName(),
				gManager->GetTeamPoints('c'), 
				gManager->GetTeamPoints('a'),
				gManager->GetTeamPoints('b') );
		}
		else if ( game_p == 1 ) {
			StrPrintF(gamestr, "%s wins, %d - %d - %d",
				(const char *)gManager->players[1]->getName(),
				gManager->GetTeamPoints('b'), 
				gManager->GetTeamPoints('a'),
				gManager->GetTeamPoints('c') );
		}
		else if ( game_p == 0 ) {
			StrPrintF(gamestr, "%s wins, %d - %d - %d",
				(const char *)gManager->players[0]->getName(),
				gManager->GetTeamPoints('a'), 
				gManager->GetTeamPoints('b'),
				gManager->GetTeamPoints('c') );
		}
		else {
			StrPrintF(gamestr, "tied on points at %d",
				gManager->GetTeamPoints('a') );

		}

	}

	game_field.Replace( gamestr );


	char bid_results_str[255];

	char bidval[10];
	if ( gManager->tbl->bid != 5 ) {
		StrPrintF(bidval, "%d", gManager->tbl->bid);
	}
	else {
		StrCopy(bidval, "smudge");
	}

	Int16 score_diff;
	Int16 bidder_score = 0;

	char other_results[80];
	other_results[0] = 0;


	if ( gManager->CutThroat() == false ) {

		if ( (*gManager->tbl->winning_bidder)->playerIndex == 1 || 
			(*gManager->tbl->winning_bidder)->playerIndex == 3 ) {
			score_diff = points[0] - old_points[0];
			bidder_score = points[1] - old_points[1];
		}
		else {
			score_diff = points[1] - old_points[1];
			bidder_score = points[0] - old_points[0];
		}

	}
	else {

		bidder_score = points[(*gManager->tbl->winning_bidder)->playerIndex] - 
					old_points[(*gManager->tbl->winning_bidder)->playerIndex];
	}

	if ( won_bid ) {

		StrPrintF(bid_results_str, 
			"%s bid %s and won %d\n", 
			(const char *)(*gManager->tbl->winning_bidder)->getName(), 
			bidval, bidder_score );
	}
	else {
		StrPrintF(bid_results_str, 
			"%s bid %s and lost\n", 
			(const char *)(*gManager->tbl->winning_bidder)->getName(), bidval );

		
		if ( gManager->CutThroat() == false ) {

			switch ( (*gManager->tbl->winning_bidder)->playerIndex ) {
				case 0:
				case 2:
//					points[0] += (-1 * gManager->tbl->bid);
					points[0] = old_points[0] + (-1 * gManager->tbl->bid);
					break;
				case 1:
				case 3:
//					points[1] += (-1 * gManager->tbl->bid);
					points[1] = old_points[1] + (-1 * gManager->tbl->bid);
					break;
			}
		}
		else {
//			points[(*gManager->tbl->winning_bidder)->playerIndex] = -1 * gManager->tbl->bid;
			points[(*gManager->tbl->winning_bidder)->playerIndex] = 
				old_points[(*gManager->tbl->winning_bidder)->playerIndex] +
					(-1 * gManager->tbl->bid);
		}
	}


	if ( gManager->CutThroat() == false ) {

		char other_team[4];

		if ( (*gManager->tbl->winning_bidder)->playerIndex == 1 || 
				(*gManager->tbl->winning_bidder)->playerIndex == 3 ) {
			StrCopy(other_team, "N/S");
		}
		else {
			StrCopy(other_team, "E/W");
		}

		if ( score_diff == 0 ) {
			StrPrintF(other_results, "%s team scored no points", other_team);
		} else if ( score_diff == 1 ) {
			StrPrintF(other_results, "%s team scored 1 point", other_team);
		}
		else {
			StrPrintF(other_results, "%s team scored %d points", other_team, score_diff);	
		}
		
		StrCat(bid_results_str, other_results);

	}
	else {


		bidder_score = points[(*gManager->tbl->winning_bidder)->playerIndex] - 
				old_points[(*gManager->tbl->winning_bidder)->playerIndex];

		if ((*gManager->tbl->winning_bidder)->playerIndex != 0 ) {
			score_diff = points[0] - old_points[0];

			if ( score_diff == 0 ) {
				StrPrintF(other_results, "%s scored no points\n", (const char *)gManager->players[0]->getName() );
			} else if ( score_diff == 1 ) {
				StrPrintF(other_results, "%s scored 1 point\n", (const char *)gManager->players[0]->getName() );
			}
			else {
				StrPrintF(other_results, "%s scored %d points\n", (const char *)gManager->players[0]->getName(), score_diff );
			}

			StrCat(bid_results_str, other_results);
		}


		if ((*gManager->tbl->winning_bidder)->playerIndex != 1 ) {
			score_diff = points[1] - old_points[1];

			char tmpstr[40];

			if ( score_diff == 0 ) {
				StrPrintF(tmpstr, "%s scored no points\n", (const char *)gManager->players[1]->getName() );
			} else if ( score_diff == 1 ) {
				StrPrintF(tmpstr, "%s scored 1 point\n", (const char *)gManager->players[1]->getName() );
			}
			else {
				StrPrintF(tmpstr, "%s scored %d points\n", (const char *)gManager->players[1]->getName(), score_diff );
			}

			StrCat(bid_results_str, tmpstr);

		}
		


		if ((*gManager->tbl->winning_bidder)->playerIndex != 2 ) {
			score_diff = points[2] - old_points[2];

			char tmpstr[60];

			if ( score_diff == 0 ) {
				StrPrintF(tmpstr, "%s scored no points", (const char *)gManager->players[2]->getName() );
			} else if ( score_diff == 1 ) {
				StrPrintF(tmpstr, "%s scored 1 point", (const char *)gManager->players[2]->getName() );
			}
			else {
				StrPrintF(tmpstr, "%s scored %d points", (const char *)gManager->players[2]->getName(), score_diff );
			}

			StrCat(bid_results_str, tmpstr);
		}

	}

	bid_results.Replace( bid_results_str );


	RectangleType  score_bounds;
	gadgetIndex = FrmGetObjectIndex(frmP, ScoreDisplayGadget );
	FrmGetObjectBounds(frmP, gadgetIndex, &score_bounds);

	Int16 y = score_bounds.topLeft.y;

	if ( gManager->CutThroat() ) {
		CString scores[3];
		CString tmp;

		for ( int i = 0; i < 3; i++ ) {
//			tmp.Format("%d", gManager->scores[i] + points[i] - old_points[i]);
			tmp.Format("%d", points[i]);
			scores[i] = gManager->players[i]->getName() + ": " + tmp + " points";

			WinPaintChars(scores[i], StrLen(scores[i]), score_bounds.topLeft.x + 2, y);
			y += FntLineHeight() + 2;
		}
	
	}
	else {

		CString ew_score_str;
		CString ns_score_str;

//		ew_score_str.Format("E/W: %d points", gManager->scores[1] + points[1] - old_points[1]);
//		ns_score_str.Format("N/S: %d points", gManager->scores[0] + points[0] - old_points[0]);

		ns_score_str.Format("N/S: %d points", points[0]);
		ew_score_str.Format("E/W: %d points", points[1]);

		WinPaintChars(ns_score_str, StrLen(ns_score_str), 
			score_bounds.topLeft.x + 2, y );

		y += FntLineHeight() + 2;

		WinPaintChars(ew_score_str, StrLen(ew_score_str), 
			score_bounds.topLeft.x + 2, y);


	}

	HostTraceOutputTL(sysErrorClass, "OnDraw done");

}


Boolean CScoringForm::OnViewWinTotals(EventType* pEvent, Boolean& bHandled) {

	HostTraceOutputTL(sysErrorClass, "OnWins");

	CWinLossDialog frmWinLoss;
	frmWinLoss.DoModal();

	CForm::DrawForm();

	HostTraceOutputTL(sysErrorClass, "OnWins done");
	
	bHandled = false;
	return true;
}

Boolean CScoringForm::OnOK(EventPtr pEvent, Boolean& bHandled) {

	HostTraceOutputTL(sysErrorClass, "OnOK");

	gManager->trk->ApplyGamePoints();
	gManager->HandleEndOfHand();
	
	if ( gManager->NoWinner() ) {

		gManager->dealCards();

		gManager->Status(GetHandBids);
		CForm::GotoForm(BiddingForm);

		EventType event;
		event.eType = nilEvent;
		EvtAddEventToQueue (&event);
	}
	else {
		gManager->Status(GameOver);
		Int16 index = gManager->GetWinner()->playerIndex;
		gManager->games_won[index]++;
		CForm::GotoForm(GameOverForm);
	}

	HostTraceOutputTL(sysErrorClass, "OnOK done");

	bHandled = false;
	return true;
}

Boolean CScoringForm::OnViewPlayedCards(EventType* pEvent, Boolean& bHandled) {

	HostTraceOutputTL(sysErrorClass, "OnViewPlayed");

	CPlayedCardsHistoryDialog pch;
	pch.DoModal();

	CForm::DrawForm();

	HostTraceOutputTL(sysErrorClass, "OnViewPlayed done");

	bHandled = false;
	return true;
}

Boolean CScoringForm::OnViewWinnings(EventType* pEvent, Boolean& bHandled) {

	HostTraceOutputTL(sysErrorClass, "OnWinnings");

	CWinningsDialog wd;
	wd.DoModal();

	CForm::DrawForm();

	bHandled = false;

	HostTraceOutputTL(sysErrorClass, "OnWinnings done");

	return true;
}


Boolean CScoringForm::OnPrefs(EventType* pEvent, Boolean& bHandled) {

	HostTraceOutputTL(sysErrorClass, "OnPrefs");

	CPrefsDialog frmPrefs;
	frmPrefs.DoModal();

	HostTraceOutputTL(sysErrorClass, "OnPrefs done");

	bHandled = false;
	return true;
}