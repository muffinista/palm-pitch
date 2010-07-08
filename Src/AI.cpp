#include "ComputerPlayer.h"
#include "GameManager.h"

extern GameManager *gManager;

ComputerPlayer::ComputerPlayer() : Player() { 
	TOLERANCE = 80;
	VALUE_TOLERANCE = 80;
	PARTNER_WIN_TOLERANCE = 85;
	LOW_TRUMP_HOLD_VAL = (Int16)Card::five;
}

ComputerPlayer::ComputerPlayer(char c, CString name): Player(c, name) { 
	TOLERANCE = 80;
	VALUE_TOLERANCE = 80;
	PARTNER_WIN_TOLERANCE = 85;
	LOW_TRUMP_HOLD_VAL = (Int16)Card::five;
}

ComputerPlayer::~ComputerPlayer() {
	my_clubs.DeleteAll();
	my_diamonds.DeleteAll();
	my_hearts.DeleteAll();
	my_spades.DeleteAll();
}


/* funcion for giving the computer's Player's bid */
Int16 ComputerPlayer::BeginBidProcess(Player *dealer, Player *current_winner) {

	my_clubs.DeleteAll();
	my_diamonds.DeleteAll();
	my_hearts.DeleteAll();
	my_spades.DeleteAll();

	sortHand();
	analyzeHand(current_winner);

	return bid;
}


/*

AI logic:

	if we are the first player, we want to win outright.  Play our best card, unless it
	stinks, and if so, play our worst card

	if we are the second player, play junk unless we can take the 1st card and it is worth taking

	if we are the 3rd player, we want to help our partner (the lead) if we can by throwing a tasty
	card, but only if it is safe.  otherwise, follow the rules for #2

	if we are the last player, we want to sneak in a winning low card or ten if we can, otherwise throw junk
	or win outright if it's worth doing

*/
Boolean ComputerPlayer::PickCard(Trick * trk) {

	Card *i;

	if ( played_card == NULL ) {

		Boolean first = haveLeadPlay();
		Boolean last = haveLastPlay();

		if ( first ) {
			HostTraceOutputTL(sysErrorClass, "play first");
			i = first_pick_card(trk);
		}
		else if ( last ) {
			HostTraceOutputTL(sysErrorClass, "play last");
			i = last_pick_card(trk);	
		}
		else {
			HostTraceOutputTL(sysErrorClass, "play middle");
			i = middle_pick_card(trk);	
		}

		//
		// let's track if we are out of trump cards or not
		//
		if ( trk->getLead() == trk->getTrump() ) {
			if ( i->Suit() != trk->getTrump() ) {
				out_of_trump = true;
			}
		}

		//
		// find the card in our hand
		//
		CArray<Card *>::iterator tmp;
		for( tmp = hand.BeginIterator() ; tmp != hand.EndIterator(); tmp++ ) {
			if ( *tmp == i ) {
				break;
			}
		}

		//
		// delete it
		//		
		Int16 toss = hand.LinearSearch((*tmp));
		hand.Delete( toss );


		//
		// track the cards we have played
		//
		played_cards.Add(i);

		//
		// store a link to the card we chose
		//
		played_card = i;

	}

	return true;

}



Card *ComputerPlayer::first_pick_card(Trick *trk) {

	/*
	
		strategy:
			- if it's the first hand of a no Trick first trump, play a high non-trumper
			- if we have the lead and a high trump Card, always play it
			- else, if we're likely to lose, play a worthless Card
	*/
	CArray<Card *>::iterator tmp_best_card;
	CArray<Card *>::iterator tmp_worst_card;

	Int16 best_chance = -1;
	Int16 best_value = -1;

	Int16 worst_value = 9999;
	Int16 worst_chance = 9999;

	CArray<Card *>::iterator tmp;

	Card *foo = NULL;

	tmp_best_card = hand.BeginIterator();
	tmp_worst_card = hand.BeginIterator();

	Boolean first_card = true;

	//
	// lets go through and figure out our 'worst' Card, our most valuable Card,
	// and our Card most likely to win the hand
	//
	for( tmp = hand.BeginIterator() ; tmp != hand.EndIterator(); tmp++ ) {

		if ( followSuit(trk, *tmp) ) {
		
			Int16 tmp_chance = chance_of_winning_hand(trk, *tmp);
			Int16 tmp_value = chance_of_winning_point(trk, *tmp);

			if ( first_card ) {

				HostTraceOutputTL(sysErrorClass, "first card: %c%c",
					(*tmp)->FaceChar(),
					(*tmp)->SuitChar() );

				first_card = false;

				best_chance = tmp_chance;
				best_value = tmp_value;

				worst_value = tmp_value;
				worst_chance = tmp_chance;

				tmp_best_card = tmp;
				tmp_worst_card = tmp;

			}
			else {
							
				Card *x = *tmp;
				

				//
				// tens are walking timebombs, don't lead them
				// 
				if ( (*tmp_best_card)->Face() == Card::ten && tmp_chance < 100 ) {

					HostTraceOutputTL(sysErrorClass, "ten timebomb: %c%c",
						(*tmp)->FaceChar(),
						(*tmp)->SuitChar() );

					best_chance = tmp_chance;
					best_value = tmp_value;
					tmp_best_card = tmp;
				}
				else if ( 
					// if our best card is NOT trump, and so is this one
					(*tmp_best_card)->Suit() != trk->getTrump() && x->Suit() != trk->getTrump() &&
					(Int16)x->Face() > (Int16)(*tmp_best_card)->Face()
				) {

					HostTraceOutputTL(sysErrorClass, "first trump: %c%c",
						(*tmp)->FaceChar(),
						(*tmp)->SuitChar() );

					best_chance = tmp_chance;
					best_value = tmp_value;
					tmp_best_card = tmp;
				}
				else if ( 

					// if our best card is trump, and so is this one
					(*tmp_best_card)->Suit() == trk->getTrump() && x->Suit() == trk->getTrump() &&
					
					// what was this line doing???
					(Int16)(*tmp_best_card)->Face() <= LOW_TRUMP_HOLD_VAL && (Int16)x->Face() <= LOW_TRUMP_HOLD_VAL &&

					// and this card has a higher face value
					(Int16)x->Face() > (Int16)(*tmp_best_card)->Face()
					) {

					HostTraceOutputTL(sysErrorClass, "better trump: %c%c",
						(*tmp)->FaceChar(),
						(*tmp)->SuitChar() );
				
					best_chance = tmp_chance;
					best_value = tmp_value;
					tmp_best_card = tmp;
				}
				else if (
					( 
						// this Card has a higher chance of winning
						( tmp_chance > best_chance ) ||
						// OR this Card is more valuable with the same chance
						( tmp_chance == best_chance && tmp_value > best_value )
					) &&
						// this Card isn't a possible low Card
						! ( x->Suit() == trk->getTrump() && (Int16)x->Face() <= LOW_TRUMP_HOLD_VAL && tmp_value > 0 )
					) {

					HostTraceOutputTL(sysErrorClass, "better winner: %c%c",
						(*tmp)->FaceChar(),
						(*tmp)->SuitChar() );

					best_chance = tmp_chance;
					best_value = tmp_value;
					tmp_best_card = tmp;
				}
				else if (
					// this card has the same chance but is of higher value
					( tmp_chance > 0 && tmp_chance == best_chance && tmp_value > best_value) &&
					
					// AND this card is not low
					! ( x->Suit() == trk->getTrump() && (Int16)x->Face() <= LOW_TRUMP_HOLD_VAL )
				) {

					HostTraceOutputTL(sysErrorClass, "better value: %c%c",
						(*tmp)->FaceChar(),
						(*tmp)->SuitChar() );

					best_chance = tmp_chance;
					best_value = tmp_value;
					tmp_best_card = tmp;

				}
				

				if ( 
					(*tmp_worst_card)->Suit() == trk->getTrump() && (*tmp)->Suit() != trk->getTrump() 
					) {

					HostTraceOutputTL(sysErrorClass, "worst card: %c%c",
						(*tmp)->FaceChar(),
						(*tmp)->SuitChar() );

					worst_value = tmp_value;
					worst_chance = tmp_chance;
					tmp_worst_card = tmp;

				}
				else if ( tmp_value < worst_value || ( tmp_value == worst_value && tmp_chance < worst_chance ) ) {

					HostTraceOutputTL(sysErrorClass, "worser card: %c%c",
						(*tmp)->FaceChar(),
						(*tmp)->SuitChar() );

					worst_value = tmp_value;
					worst_chance = tmp_chance;
					tmp_worst_card = tmp;
				}


			} // else (not first Card)
	
		} // if

	} // for
  


	// if we are the first Player and we asked for no trump first Trick,
	// make sure we play our best Card here
	if ( trk->no_trump_first_trick && trk->first_trick ) {

		HostTraceOutputTL(sysErrorClass, "we won bid and called ntft, play best: %c%c",
			(*tmp_best_card)->FaceChar(),
			(*tmp_best_card)->SuitChar() );

		return *tmp_best_card;
	}

	//
	// only play our best Card if there's something worth winning
	//
	if ( best_chance >= TOLERANCE &&
	
		// don't play a jack unless we are guaranteed
		! ( (*tmp_best_card)->Face() == Card::jack && 
				(*tmp_best_card)->Suit() == trk->getTrump() &&
				best_chance < 100
			)
		) {

		HostTraceOutputTL(sysErrorClass, "first play best: %c%c",
			(*tmp_best_card)->FaceChar(),
			(*tmp_best_card)->SuitChar() );

		return *tmp_best_card;
	}

	HostTraceOutputTL(sysErrorClass, "worst card: %c%c",
		(*tmp_worst_card)->FaceChar(),
		(*tmp_worst_card)->SuitChar() );

	return *tmp_worst_card;

}


/*
	if we are the second player, play junk unless we can take the 1st card and it is worth taking

	if we are the 3rd player, we want to help our partner (the lead) if we can by throwing a tasty
	card, but only if it is safe.  otherwise, follow the rules for #2
*/
Card *ComputerPlayer::middle_pick_card(Trick *trk) {

	CArray<Card *>::iterator tmp_best_card;
	CArray<Card *>::iterator tmp_worst_card;
	CArray<Card *>::iterator tmp_valuable_card;

	Int16 best_chance = -1;
	Int16 best_value = -1;

	Int16 best_value_chance = -1;
	Int16 best_value_val = -1;

	Int16 worst_value = 99999;
	Int16 worst_chance = 99999;

	CArray<Card *>::iterator tmp;

	Card *foo = NULL;

	tmp_best_card = hand.BeginIterator();
	tmp_worst_card = hand.BeginIterator();
	tmp_valuable_card = hand.BeginIterator();
	
	Boolean first_card = true;

	Int16 partner_win_chance = 0;
	Boolean partner_winning = is_partner_winning(trk);

	Boolean play_junk = true;

	if ( partner_winning ) {

		HostTraceOutputTL(sysErrorClass, "partner is winning");

		partner_win_chance = chance_of_winning_hand(trk, trk->current_winner->c, true );
		
		if ( partner_win_chance >= PARTNER_WIN_TOLERANCE || want_trick(trk) ) {
			HostTraceOutputTL(sysErrorClass, "don't play junk");
			play_junk = false;
		}

	}

	Card *lowest = trk->lowestCardPlayed();

	//
	// lets go through and figure out our 'worst' Card, our most valueable Card,
	// and our Card most likely to win the hand
	//
	for( tmp = hand.BeginIterator() ; tmp != hand.EndIterator(); tmp++ ) {

		if ( followSuit(trk, *tmp) ) {

			Int16 tmp_chance = chance_of_winning_hand(trk, *tmp);
			Int16 tmp_value = chance_of_winning_point(trk, *tmp);

			HostTraceOutputTL(sysErrorClass, "card: %c%c hand: %d point: %d",
				(*tmp)->FaceChar(),
				(*tmp)->SuitChar(),
				tmp_chance,
				tmp_value );


			if ( first_card ) {

				HostTraceOutputTL(sysErrorClass, "first card: %c%c",
					(*tmp)->FaceChar(),
					(*tmp)->SuitChar() );

				first_card = false;

				best_chance = tmp_chance;
				best_value_chance = tmp_chance;

				best_value = tmp_value;
				best_value_val = tmp_value;

				worst_value = tmp_value;
				worst_chance = tmp_chance;

				tmp_best_card = tmp;
				tmp_worst_card = tmp;
				tmp_valuable_card = tmp;

			}
			else {
							
				Card *x = *tmp;

				if ( ! play_junk ) {

					//
					// tens are walking timebombs, don't lead them
					// 
					if ( (*tmp_best_card)->Face() == Card::ten && 
						( tmp_chance == 100 || partner_win_chance >= PARTNER_WIN_TOLERANCE ) ) {

						HostTraceOutputTL(sysErrorClass, "ten timebomb: %c%c",
							(*tmp)->FaceChar(),
							(*tmp)->SuitChar() );

						best_chance = tmp_chance;
						best_value = tmp_value;
						tmp_best_card = tmp;
					}
					else if (
						( ( tmp_chance > best_chance ) ||
						( tmp_chance == best_chance && tmp_value > best_value ) ) &&
						! ( x->Suit() == trk->getTrump() && (Int16)x->Face() <= LOW_TRUMP_HOLD_VAL ) ) {

						HostTraceOutputTL(sysErrorClass, "better chance: %c%c",
							(*tmp)->FaceChar(),
							(*tmp)->SuitChar() );

						best_chance = tmp_chance;
						tmp_best_card = tmp;
					}
					else if (
						( tmp_chance > 0 && tmp_chance == best_chance && tmp_value > best_value) &&
						! ( x->Suit() == trk->getTrump() && (Int16)x->Face() <= LOW_TRUMP_HOLD_VAL )
					) {

						HostTraceOutputTL(sysErrorClass, "same chance, better val: %c%c",
							(*tmp)->FaceChar(),
							(*tmp)->SuitChar() );

						best_chance = tmp_chance;
						tmp_best_card = tmp;

					}


					//
					// figure out what our most valuable Card is, and what 
					// our chance of winning is with it
					//
					if ( tmp_value > best_value || 
						( tmp_value == best_value && 
							(*tmp_valuable_card)->Face() > (*tmp)->Face() )
							//  partner_win_chance < 100 &&
						) {

						HostTraceOutputTL(sysErrorClass, "better value: %c%c",
							(*tmp)->FaceChar(),
							(*tmp)->SuitChar() );

						best_value_val = tmp_value;
						best_value_chance = tmp_chance;

						tmp_valuable_card = tmp;
					}

				} // if ( ! play junk )


				if ( 
					(*tmp_worst_card)->Suit() == trk->getTrump() && (*tmp)->Suit() != trk->getTrump()
					) {


					HostTraceOutputTL(sysErrorClass, "worst value: %c%c",
						(*tmp)->FaceChar(),
						(*tmp)->SuitChar() );

					worst_value = tmp_value;
					worst_chance = tmp_chance;
					tmp_worst_card = tmp;

				}
/*
! ( (*tmp)->Suit() == trk->getTrump() &&
						( (*tmp)->Face() == Card::jack || (int)(*tmp)->Face() <= (int)Card::five ) ) &&
					(
					(int)((*tmp)->Face()) < (*tmp_worst_card)->Face() ||
*/
				else if ( tmp_value < worst_value || 
					( tmp_value == worst_value && tmp_chance < worst_chance ) 
					)
				 {

					HostTraceOutputTL(sysErrorClass, "worser value: %c%c",
						(*tmp)->FaceChar(),
						(*tmp)->SuitChar() );

					worst_value = tmp_value;
					worst_chance = tmp_chance;
					tmp_worst_card = tmp;
				}

			}
	
		} // if

	} // for
  
	delete lowest;

	//
	// if there's nothing worth winning, don't play a good card
	//
	if ( play_junk ) {

		HostTraceOutputTL(sysErrorClass, "play junky card: %c%c",
			(*tmp_worst_card)->FaceChar(),
			(*tmp_worst_card)->SuitChar() );

		return *tmp_worst_card;
	}

	//
	// if our partner is winning, chuck her a good card
	//
	if ( is_partner_winning(trk) && 
			chance_of_winning_hand(trk, trk->current_winner->c, true ) >= PARTNER_WIN_TOLERANCE ) {

		HostTraceOutputTL(sysErrorClass, "play valuable card: %c%c",
			(*tmp_valuable_card)->FaceChar(),
			(*tmp_valuable_card)->SuitChar() );

		return *tmp_valuable_card;
	}


	//
	// if there's something worth winning, then lets win it
	//
	if ( want_trick(trk) && 
			best_chance >= TOLERANCE &&
			( best_chance >= 100 || 
				(*tmp_best_card)->Suit() != trk->getTrump() ) ) {

		HostTraceOutputTL(sysErrorClass, "want, best card: %c%c",
			(*tmp_best_card)->FaceChar(),
			(*tmp_best_card)->SuitChar() );

		return *tmp_best_card;

	}

	HostTraceOutputTL(sysErrorClass, "play worst card: %c%c",
		(*tmp_worst_card)->FaceChar(),
		(*tmp_worst_card)->SuitChar() );

	return *tmp_worst_card;


}


/*
	if we are the last player, we want to sneak in a winning low card or ten if we can, otherwise throw junk
	or win outright if it's worth doing
*/
Card *ComputerPlayer::last_pick_card(Trick *trk) {

	CArray<Card *>::iterator tmp_best_card;
	CArray<Card *>::iterator tmp_worst_card;
	CArray<Card *>::iterator tmp_worst_winning_card;
	CArray<Card *>::iterator tmp_valuable_card;

	Int16 best_value_chance = -1;
	Int16 best_value_val = -1;

	Int16 worst_value = 99999;
	Int16 worst_chance = 99999;

	Int16 best_value = -1;
	Int16 best_chance = -1;

	Int16 worst_win_value = 99999;
	Int16 worst_win_chance = -1;


	CArray<Card *>::iterator tmp;

	tmp_best_card = hand.BeginIterator();
	tmp_worst_card = hand.BeginIterator();
	tmp_worst_winning_card = hand.BeginIterator();
	tmp_valuable_card = hand.BeginIterator();

	Boolean first_card = true;

	Card *lowest = trk->lowestCardPlayed();

	//
	// lets go through and figure out our 'worst' Card, our most valueable Card,
	// and our Card most likely to win the hand
	//
	for( tmp = hand.BeginIterator() ; tmp != hand.EndIterator(); tmp++ ) {

		if ( followSuit(trk, *tmp) ) {
		
			Int16 tmp_chance = chance_of_winning_hand(trk, *tmp);
			Int16 tmp_value = chance_of_winning_point(trk, *tmp);

			if ( first_card ) {
				first_card = false;

				HostTraceOutputTL(sysErrorClass, "first card: %c%c",
					(*tmp)->FaceChar(),
					(*tmp)->SuitChar() );

				best_value_chance = tmp_chance;
				best_value_val = tmp_value;
				tmp_valuable_card = tmp;

				worst_value = tmp_value;
				worst_chance = tmp_chance;
				tmp_worst_card = tmp;

				tmp_worst_winning_card = tmp;
				worst_win_value = tmp_value;
				worst_win_chance = tmp_chance;

				best_chance = tmp_chance;
				best_value = tmp_value;

			}
			else {
							
				Card *x = *tmp;

				if ( worst_value > tmp_value ) {

					HostTraceOutputTL(sysErrorClass, "worst val card: %c%c",
						(*tmp)->FaceChar(),
						(*tmp)->SuitChar() );

					worst_value = tmp_value;
					worst_chance = tmp_chance;
					tmp_worst_card = tmp;

				}

				if ( worst_win_value > tmp_value && tmp_chance > 0 ) {

					HostTraceOutputTL(sysErrorClass, "worst win card: %c%c",
						(*tmp)->FaceChar(),
						(*tmp)->SuitChar() );

					worst_win_value = tmp_value;
					worst_win_chance = tmp_chance;
					tmp_worst_winning_card = tmp;
				}

				//
				// figure out what our most valuable Card is, and what 
				// our chance of winning is with it
				//
				if ( tmp_value > best_value_val ||
					( tmp_value == best_value_val && 
					( (*tmp_valuable_card)->Face() <= Card::four && (*tmp_valuable_card)->Face() < (*tmp)->Face() ) )
					) {

					HostTraceOutputTL(sysErrorClass, "best val card: %c%c",
						(*tmp)->FaceChar(),
						(*tmp)->SuitChar() );

					best_value_val = tmp_value;
					best_value_chance = tmp_chance;
					tmp_valuable_card = tmp;
				}


				if ( tmp_chance > best_chance ) {

					HostTraceOutputTL(sysErrorClass, "best chance card: %c%c",
						(*tmp)->FaceChar(),
						(*tmp)->SuitChar() );

					best_chance = tmp_chance;
					tmp_best_card = tmp;
				}

			}
	
		} // if

	} // for
  

	delete lowest;

	//
	// if we're last and our partner is winning, chuck her a good Card
	//
	if ( is_partner_winning(trk) && 
			(*tmp_valuable_card)->Face() <= Card::jack && 
			best_value_val >= VALUE_TOLERANCE ) {

		HostTraceOutputTL(sysErrorClass, "partner winning, best card: %c%c",
			(*tmp_valuable_card)->FaceChar(),
			(*tmp_valuable_card)->SuitChar() );

		return *tmp_valuable_card;
	}
	
	//
	// only play our best Card if there's something worth winning
	//
	if ( best_value_chance > 0 && ( best_value_val >= VALUE_TOLERANCE || want_trick(trk) ) 
		&& ! ( (*tmp_valuable_card)->Suit() == trk->getTrump() && (*tmp_valuable_card)->Face() >= Card::queen ) ) {

		HostTraceOutputTL(sysErrorClass, "win with best val card: %c%c",
			(*tmp_valuable_card)->FaceChar(),
			(*tmp_valuable_card)->SuitChar() );

		return *tmp_valuable_card;
	}
	

	//
	// if our worst winner will win, and we want the hand, then use that
	//
	if (
		( worst_win_value >= VALUE_TOLERANCE || want_trick(trk) ) &&
		worst_win_chance > 0 ) {

		HostTraceOutputTL(sysErrorClass, "want trick, win w/ worst card: %c%c",
			(*tmp_worst_winning_card)->FaceChar(),
			(*tmp_worst_winning_card)->SuitChar() );

		return *tmp_worst_winning_card;
	}


	if ( want_trick(trk) && best_chance > 0 ) {

		HostTraceOutputTL(sysErrorClass, "want trick, win w/ card: %c%c",
			(*tmp_best_card)->FaceChar(),
			(*tmp_best_card)->SuitChar() );

		return *tmp_best_card;
	}

	HostTraceOutputTL(sysErrorClass, "lose w/ worst card: %c%c",
		(*tmp_worst_card)->FaceChar(),
		(*tmp_worst_card)->SuitChar() );

	return *tmp_worst_card;

}


/* sorts Card into vectors for each suit */
void ComputerPlayer::sortHand() {

	sort_hand();

	for( CArray<Card *>::iterator i = hand.BeginIterator(); i != hand.EndIterator(); i++)
	{
		if ( (*i)->Suit() == Card::club)
		{
			my_clubs.Add(*i);
		}
		else if ((*i)->Suit() == Card::diamond)
		{ 
			my_diamonds.Add(*i); 
		}
		else if ((*i)->Suit() == Card::heart)
		{ 
			my_hearts.Add(*i); 
		}
		else if ((*i)->Suit() == Card::spade)
		{ 
			my_spades.Add(*i); 
		}

	}

} // sortHand


Int16 ComputerPlayer::handValue(Int16 suit, Boolean partner_winning, Int16 partner_bid, Int16 ourScore, Int16 theirScore) {

	Int16 points = 0;

	Int16 count = 0;
	Int16 total = suits[suit].GetCount();

	for( CArray<Card *>::iterator i = suits[suit].BeginIterator(); i != suits[suit].EndIterator(); i++) {

		Int16 win_chance = 0;
		
		// chance of a higher Card = 
		// # of higher cards / # of cards left (total - my cards)
		Int16 higher_cards = (Int16)Card::ace - (Int16)(*i)->Face() - count;
		win_chance = 100 - (higher_cards * 100)/(52 - total);

		if ( (*i)->Face() == Card::jack ) {
			have_jack = true;
		}
		else if ( (*i)->Face() == Card::king || (*i)->Face() == Card::ace ) {
			have_high = true;
		}


//		count++;
//		points += (win_chance - 74);

		/*
		12 has a 100 chance of winning
		11 has a 98 chance of winning
		10 has a 96 chance of winning
		9 has a 94 chance of winning
		8 has a 92 chance of winning
		7 has a 90 chance of winning
		6 has a 88 chance of winning
		5 has a 86 chance of winning
		4 has a 84 chance of winning
		3 has a 82 chance of winning
		2 has a 80 chance of winning
		1 has a 78 chance of winning
		0 has a 76 chance of winning */

		if ( win_chance >= 98 ) {
			points += 5;
		}
		else if ( win_chance >= 94  ) {
			points += 4;
		}
		else if ( win_chance >= 90 ) {
			points += 3;
		}
		else if ( win_chance >= 85 ) {
			points += 2;
		}
		else {
			points += 1;
		}

	} // for

	
	if ( have_high ) {
		points += 3;
	}


	if ( theirScore + 3 >= gManager->winning_score ) {
		points += 2;
	}


	return points;

} // handValue


void ComputerPlayer::analyzeHand(Player *bidder) {

	UInt16 bestIndex = 0;
	Int16 suitScore = 0;
	
	Boolean partner_winning = false;
	Int16 partner_bid = 0;

	bid = 0;

	Int16 tmpOurScore = 0;
	Int16 tmpTheirScore = 0;

	if ( gManager->CutThroat() ) {
		partner_winning = false;
		partner_bid = 0;

		tmpOurScore = gManager->scores[playerIndex];

		if ( playerIndex == 0 ) {
			tmpTheirScore = gManager->scores[1] > gManager->scores[2] ? 
									gManager->scores[1] : 
									gManager->scores[2];
		}
		else if ( playerIndex == 1 ) {
			tmpTheirScore = gManager->scores[0] > gManager->scores[2] ? 
									gManager->scores[0] : 
									gManager->scores[2];
		}
		else if ( playerIndex == 2 ) {
			tmpTheirScore = gManager->scores[0] > gManager->scores[1] ? 
									gManager->scores[0] : 
									gManager->scores[1];
		}
		
	}
	else {
		if ( bidder == partner ) {
			partner_winning = true;
			partner_bid = partner->bid;
		}

		if ( playerIndex == 0 || playerIndex == 2 ) {
			tmpOurScore = gManager->scores[0];
			tmpTheirScore = gManager->scores[1];
		}
		else {
			tmpOurScore = gManager->scores[1];	
			tmpTheirScore = gManager->scores[0];
		}
	}


	Int8 best_points = -1;

	for (Int16 i = 0; i < 4;  i++) {

		have_jack = false;
		have_high = false;

		Int16 points = handValue(i, partner_winning, partner_bid,
									tmpOurScore, tmpTheirScore );


		if ( points > best_points ) {

			best_points = points;

			// max possible score is 30 points, which would be a lock for smudge
			if ( partner_winning ) {

				if ( points >= 28 && have_jack && have_high ) {
					bid = 5;
				}
				else if ( points >= 24 && have_jack && have_high ) {
					bid = 4;
				}
				else if ( ( points >= 21  && have_high ) || ( points >= 19 && have_jack && have_high ) ) {
					bid = 3;
				}
				else if ( points >= 15  ) {
					bid = 2;
				}
				else {
					bid = 0;
				}
			}
			else {

				if ( points >= 26 && have_jack && have_high ) {
					bid = 5;
				}
				else if ( points >= 20 && have_jack && have_high ) {
					bid = 4;
				}
				else if ( ( points >= 17 && have_high ) || ( points >= 15 && have_jack && have_high ) ) {
					bid = 3;
				}
				else if ( points >= 13  ) {
					bid = 2;
				}
				else {
					bid = 0;
				}
			}


			bestIndex = i;

		} // if ( points > best_points )

	} // for


	switch (bestIndex)
	{
		case 0: 
			bestSuit = Card::club;
			break;
		case 1: 
			bestSuit = Card::diamond;
			break;
		case 2: 
			bestSuit = Card::heart;
			break;
		case 3: 
			bestSuit = Card::spade;
			break;
	}


	no_trump_first_trick = false;


	/*
		if we're running the smart AI, let's check and see if we should do a first Trick no trump
	*/
	if ( gManager->no_trump_first_trick ) {

		for (Int16 array_counter = 0; array_counter < 4;  array_counter++)
		{
		
			if ( array_counter != bestIndex && suits[array_counter].GetCount() > 0 ) {
			
				CArray<Card *>::iterator i = suits[array_counter].EndIterator() - 1;
				Card *highest = *i;
				
				if ( (Int16)highest->Face() >= Card::queen ) {
					no_trump_first_trick = true;
				}

			}

		}

	} // if Smart


} // analyzeHand


Boolean ComputerPlayer::want_trick(Trick *t) {

	Boolean has_jack = t->hasJack();
	Boolean has_ten = t->hasTen();
	Card *low = t->currentLow();
	Card *lowest = t->lowestCardPlayed();

	if ( has_jack ) {
		HostTraceOutputTL(sysErrorClass, "trick has a jack, we want it");
	}
	if ( has_ten ) {
		HostTraceOutputTL(sysErrorClass, "trick has a ten, we want it");
	}

	if ( has_jack || has_ten || ( low && low->Face() < lowest->Face() && low->Face() <= Card::four ) ) {
		delete lowest;
		return true;
	}

	delete lowest;
	return false;
}



/*
	what is the probability of getting a point out of this hand?  we're
	not actually looking at the chance of winning the hand itself, just
	it's overall value
*/
Int16 ComputerPlayer::chance_of_winning_point(Trick *t, Card *c) {

	Int16 chance = 0;
	Int16 tmp_chance = 0;

	Card *current_high = t->highestCardPlayed(c->Suit());
	Card *current_low = t->lowestCardPlayed();


	if ( c->Suit() == t->getTrump() ) {

		// check for jack
		if ( c->Face() == Card::jack ) {
			chance = 100;
		}
		else {

			// check for high
			if ( c->Face() >= current_high->Face() ) {

				// chance of a higher Card == # of cards higher than this one / # of playable cards left 
				Int16 diff = (Int16)Card::ace - (Int16)c->Face();
	
				//
				// if this isn't a face Card, we want to play it more conservatively
				//
				if ( (Int16)c->Face() <= Card::ten ) {
					diff += 2;
				}

				Int16 foo = diff * 100 / t->cards_left;
				tmp_chance = 100 - foo;

				if ( tmp_chance > chance ) {
					chance = tmp_chance;
				}

			}

			
			// check for low
			if ( (Int16)current_low->Face() >= (Int16)c->Face() ) {

				// chance of a lower Card == # of cards lower than this one / # of playable cards left 
				Int16 diff = (Int16)c->Face() - (Int16)Card::two;



				//
				// if this isn't a really low Card, we want to play it more conservatively
				//
				if ( (Int16)c->Face() >= Card::five ) {
					diff += 2;
				}

				Int16 foo = diff * 100 / t->cards_left;
				tmp_chance = 100 - foo;
				
				if ( tmp_chance > chance ) {
					chance = tmp_chance;
				}
			}
		}
		
	}


	if ( (Int16)c->Face() == (Int16)Card::ten ) {
		chance += 35;
	}
	else if ( (Int16)c->Face() > (Int16)Card::ten ) {
//		chance += 5;
	}

	
	delete current_high;
	delete current_low;

	return chance;
}


Boolean ComputerPlayer::is_partner_winning(Trick *trk) {

	if ( gManager->CutThroat() ) {
		return false;
	}

	return trk->current_winner != NULL && 
			trk->current_winner->p->playerIndex == partner->playerIndex;

}


Int16 ComputerPlayer::chance_of_winning_hand(Trick *trk, Card *c) {
	return chance_of_winning_hand(trk, c, false);
}


/*
	what is the chance of winning with the given Card, regardless of
	it's value?
*/
Int16 ComputerPlayer::chance_of_winning_hand(Trick *trk, Card *c, 
					Boolean checking_partner_card) {


	Boolean last_player = haveLastPlay();
	Boolean partner_winning = ( ! checking_partner_card ) && is_partner_winning(trk);
	Boolean no_trump_left = trk->noTrumpLeft(this);
	Boolean trump_played = trk->current_winner != NULL && trk->current_winner->c->Suit() == trk->getTrump();


	Int16 cardval = (Int16)c->Face();

	Int16 trump_left = 0;

	Int16 diff = 0;
	Int16 chance = 0;
	Int16 partner_win_chance = 0;

	HostTraceOutputTL(sysErrorClass, "guess chance of winning with %c%c", c->FaceChar(), c->SuitChar() );

	Card *highest_card_left = trk->highestCardNotPlayed(c->Suit());

	HostTraceOutputTL(sysErrorClass, "highest card left %c%c", 
		highest_card_left->FaceChar(), highest_card_left->SuitChar() );

	
	if ( last_player && partner_winning ) {
		HostTraceOutputTL(sysErrorClass, "last player and partner winning, i'll win" );
		delete highest_card_left;
		return 100;
	}

	if ( partner_winning ) {
		partner_win_chance = chance_of_winning_hand(trk, trk->current_winner->c, true );
		HostTraceOutputTL(sysErrorClass, "partner win chance: %d", partner_win_chance );
	}

	// am i the last Player?  if so, special rules
	// && c >= highest_card_left
	if ( last_player &&
		( ! trump_played && c->Suit() == trk->getTrump() ) ) {
		HostTraceOutputTL(sysErrorClass, "last player, i'll win" );
		delete highest_card_left;
		return 100;
	}

	if ( last_player && 
		trk->current_winner && 
		trk->current_winner->c->Suit() == c->Suit() &&
		trk->current_winner->c->Face() < c->Face() ) {
		HostTraceOutputTL(sysErrorClass, "last player 2, i'll win");
		delete highest_card_left;
		return 100;
	}
		

	// has the other team played the highest Card?  if so...
	if ( trk->current_winner != NULL && 
				c->Suit() == trk->current_winner->c->Suit() && 
				(Int16)c->Face() < (Int16)trk->current_winner->c->Face() ) {
		HostTraceOutputTL(sysErrorClass, "Card %c < %c, I'll lose", c->FaceChar(), 
				trk->current_winner->c->FaceChar() );
		delete highest_card_left;
		return 0;
	}

	//
	// chance of a higher Card == # of higher cards / # number of cards left
	//
	if ( trump_played && trk->getTrump() != c->Suit() ) {
		HostTraceOutputTL(sysErrorClass, "not trump, i'll lose");
		delete highest_card_left;
		return 0;
	}


	//
	// trump has not been played at this point
	//
	if ( c->Suit() != trk->getTrump() ) {

		Card *highest_trump = trk->highestCardNotPlayed(trk->getTrump());
		trump_left = (Int16)highest_trump->Face() + 1;
	
		Int16 higher_cards = trump_left + ( (Int16)Card::ace - cardval );
		chance = 100 - (higher_cards * (100 / trk->cards_left));
		
//		HostTraceOutputTL(sysErrorClass, "chance1: 100 - (%d * 100 / %d) = %d", higher_cards, trk->cards_left, chance );
		HostTraceOutputTL(sysErrorClass, "chance1: %d", chance);

		delete highest_trump;

	}
	else {
		diff = (Int16)highest_card_left->Face() - (Int16)c->Face();
		chance = 100 - (diff * (100 / trk->cards_left));

		HostTraceOutputTL(sysErrorClass, "chance2: %d", chance);

	}

	//
	// is my partner guaranteed to win?  if so...
	//
	if ( partner_win_chance >= PARTNER_WIN_TOLERANCE && partner_win_chance > chance ) {
		chance = partner_win_chance;
		HostTraceOutputTL(sysErrorClass, "go with partner win chance" );
	}


	delete highest_card_left;

	return chance;

}


/* if bid is won then this is used to set trump, just returns best suit */
Card::suit_t ComputerPlayer::Trump() {
	if ( (int)bestSuit == -1 ) {
		analyzeHand(this);
	}

	return bestSuit;
}



Boolean ComputerPlayer::haveLastPlay() {

//	CArray<Player *>::iterator tmp = gManager->players.EndIterator() - 1;

	Player *l = gManager->getPrevPlayer(gManager->tbl->lead);
//	Player *c = (*gManager->current);

//	if ( l->playerIndex == c->playerIndex ) {
	if ( l->playerIndex == playerIndex ) {
		return true;
	}

	return false;
}

Boolean ComputerPlayer::haveLeadPlay() {

	if ( gManager->tbl->lead == this ) {
		return true;
	}

	return false;
}
