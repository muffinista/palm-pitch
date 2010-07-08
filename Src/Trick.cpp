#include "Trick.h"
#include "GameManager.h"

extern GameManager *gManager;

Trick::Trick() {

	first_trick = true;
	book = new CArray<PlayersCard *>;

	lead = NULL;
	current_winner = NULL;
	
	high_c = (Card::face_t)0;
	low_c = (Card::face_t)-1;

	high_p = -1;
	low_p = -1;
	jack_p = -1;
	game_p = -1;
	
	cards_left = 52 - CARDS_IN_HAND;

}

Trick::~Trick() {

	int tmp = book->GetCount();
	
	for (int i = tmp; i > 0; i-- ) {
		PlayersCard *tmp = book->GetAt(i - 1);
		delete tmp;
	}

	book->DeleteAll();
	delete book;

	team_winnings[0].DeleteAll();
	team_winnings[1].DeleteAll();
	team_winnings[2].DeleteAll();

	played_clubs.DeleteAll();
	played_spades.DeleteAll();
	played_hearts.DeleteAll();
	played_diamonds.DeleteAll();
}

Boolean Trick::hasJack() {

	for ( CArray<PlayersCard*>::iterator i = book->BeginIterator() ;
			 i != book->EndIterator();
			 i++) {

		Card *tmp = (*i)->c;

		if ( tmp->Suit() == gManager->tbl->trump && tmp->Face() == Card::jack ) {
			return true;
		}
	}
	
	return false;

}

Boolean Trick::hasTen() {

	for ( CArray<PlayersCard*>::iterator i = book->BeginIterator() ;
			 i != book->EndIterator();
			 i++) {
		Card *tmp = (*i)->c;

		if ( tmp->Face() == Card::ten ) {
			return true;
		}
	}
	
	return false;

}



Card *Trick::currentLow() {

	Card *low_c = NULL;

	for (Int16 i = 0; i < gManager->numPlayers; i++) {

		for( CArray<Card*>::iterator a = gManager->getPlayer(i)->winnings.BeginIterator() ;
			a != gManager->getPlayer(i)->winnings.EndIterator(); a++) {


			if ( (*a)->Suit() == gManager->tbl->trump ) {
					
				if ( !low_c || low_c->Face() < (*a)->Face() ) {
					low_c = (*a);
				}
			}

		}

	}
	
	return low_c;

}



Card *Trick::currentHigh() {


	Card *low_c = NULL;

	for (Int16 i = 0; i < gManager->numPlayers; i++) {

		for( CArray<Card*>::iterator a = gManager->getPlayer(i)->winnings.BeginIterator() ;
			a != gManager->getPlayer(i)->winnings.EndIterator(); a++) {


			if ( (*a)->Suit() == gManager->tbl->trump ) {
					
				if ( !low_c || low_c->Face() > (*a)->Face() ) {
					low_c = (*a);
				}
			}

		}

	}
	
	return low_c;

}

Boolean Trick::isCardPlayed(Card::suit_t s, Card::face_t f) {

	CArray<Card*> tmp;

	switch ( s )
	{
		case Card::club:
			tmp = played_clubs;
			break;
		case Card::spade:
			tmp = played_spades;
			break;
		case Card::heart:
			tmp = played_hearts;
			break;
		case Card::diamond:
			tmp = played_diamonds;
			break;
	}


	for( CArray<Card*>::iterator a = tmp.BeginIterator() ;
		a != tmp.EndIterator(); a++) {

		if ( (*a)->Suit() == s && (*a)->Face() == f) {
			return true;
		}

	}

	return false;

}


//
// look at the top 5 cards or so and see what the highest unplayed Card is
//
Card* Trick::highestCardNotPlayed(Card::suit_t f) {

	Card::face_t high = Card::ace;

	for ( Int16 i = 0; i <= 12; i++ ) {

		if ( ! isCardPlayed(f, high) ) {
			return new Card(f, high);
		}
		
		high = (Card::face_t)((Int16)high - 1);

	}
	
	return new Card(f, high);
}


Card* Trick::highestCardPlayed(Card::suit_t s) {

	Card::face_t high = Card::ace;

	for ( Int16 i = 12; i > 0 ; i-- ) {

		if ( isCardPlayed(s, high) ) {
			return new Card(s, high);
		}
		
		high = (Card::face_t)((Int16)high - 1);

	}
	
	return new Card(s, high);
}

Card* Trick::lowestCardPlayed() {

	Card::face_t low = Card::two;

	for ( Int16 i = 0; i < 12 ; i++ ) {

		if ( isCardPlayed(gManager->tbl->trump, low) ) {
			return new Card(gManager->tbl->trump, low);
		}
		
		low = (Card::face_t)((Int16)low + 1);

	}
	
	return new Card(gManager->tbl->trump, low);
}




Boolean Trick::FirstTrickP() {
	return first_trick;
}


Card * Trick::RecordPlayedCard(Player *p, Card *c) {

	if ( c->Suit() == gManager->tbl->trump ) {
		trump_played++;
	}

	//
	// add the new Card to the book
	//
	PlayersCard *pcard = new PlayersCard(p, c);
	book->Add(pcard);


	if ( lead == NULL ) {
		lead = pcard;
	}


	//
	// figure out who is currently winning this play
	//
	
	
	//
	// first Card played
	//
	if ( current_winner == NULL ) {
		current_winner = pcard;
	}
	//
	// trump always beats non-trump
	//
	else if (c->Suit() == gManager->tbl->trump && current_winner->c->Suit() != gManager->tbl->trump) {
		current_winner = pcard;
	}
	//
	// both the same suit, do a std compare
	//
	else if (c->Suit() == current_winner->c->Suit() ) {

		if ( static_cast<Int16>(c->Face()) > static_cast<Int16>(current_winner->c->Face()) ) {
			current_winner = pcard;
		}

	}


	// add the card to our array of cards sorted by suit
	switch ( pcard->c->Suit() ) {
		case Card::club:
			played_clubs.Add(pcard->c);
			break;
		case Card::spade:
			played_spades.Add(pcard->c);
			break;
		case Card::heart:
			played_hearts.Add(pcard->c);
			break;
		case Card::diamond:
			played_diamonds.Add(pcard->c);
			break;
	}        

	// return the Card that was played
	return c;

}



Player* Trick::Winner() {

	Player *winner = current_winner->p;

	first_trick = false;
	current_winner->p->claimWinnings(book);

	gManager->tbl->RecordRound(book, current_winner->p);

	Int16 team = 0;

//	if ( gManager->CutThroat() ) {
//		team = current_winner->p->playerIndex + 'a';
//	}
//	else {
		if (current_winner->p->team == 'a' ) {
			team = 0;
		}
		else if (current_winner->p->team == 'b' ) {
			team = 1;
		}

		else {
			team = 2;
		}
//	}

	for ( CArray<PlayersCard*>::iterator i = book->BeginIterator() ;
			 i != book->EndIterator();
			 i++) {
		team_winnings[team].Add( (*i)->c );
	}

	int tmp = book->GetCount();
	for (int i = tmp; i > 0; i-- ) {
		PlayersCard *tmp = book->GetAt(i - 1);
		delete tmp;
	}

	book->DeleteAll();
	
	gManager->tbl->lead = winner;

	return winner;

}

//
// return true if all players after this Player are either out of trump,
// or are a partner of this Player
//
Boolean Trick::noTrumpLeft(Player *p) {

	CArray<Player *>::iterator tmp = gManager->current;

	for ( Int16 i = 0; i < gManager->numPlayers; i++ ) {

		tmp = gManager->getNextPlayerIter(tmp);

		if ( *tmp != p->partner ) {
			if ( (*tmp)->out_of_trump == false ) {
				return false;
			}
		}
		
	}

	return true;
}


Card::suit_t  Trick::getTrump() {
	return gManager->tbl->trump;
}


Card::suit_t Trick::getLead() {
	if ( lead != NULL ) {
		return lead->c->Suit();
	}

	return (Card::suit_t)-1;
}


void  Trick::CleanUp() {

	first_trick = true;

	int tmp = book->GetCount();
	for (int i = tmp; i > 0; i-- ) {
		PlayersCard *tmp = book->GetAt(i - 1);
		delete tmp;
	}

	book->DeleteAll();

	current_winner = NULL;
	lead = NULL;

}

void Trick::PostHandCleanUp() {

	CleanUp();

	cards_left = 52 - CARDS_IN_HAND;
	
	team_winnings[0].DeleteAll();
	team_winnings[1].DeleteAll();
	team_winnings[2].DeleteAll();

	played_clubs.DeleteAll();
	played_spades.DeleteAll();
	played_hearts.DeleteAll();
	played_diamonds.DeleteAll();

	high_c = (Card::face_t)0;
	low_c = (Card::face_t)-1;

	high_p = -1;
	low_p = -1;
	jack_p = -1;
	game_p = -1;

	for ( Int16 i = 0; i < gManager->numPlayers; i++ ) {
		gManager->players[i]->post_hand_cleanup();
	}


}

void Trick::ApplyGamePoints() {

	Boolean smudge = false;

	Boolean won_bid = CalculateGamePoints(&high_p, &low_p, &jack_p, &game_p, 
									&high_c, &low_c, &smudge );

	NewScore( &score0, &score1, &score2, 
			won_bid, high_p, low_p, jack_p, game_p, high_c, low_c, 
			smudge );	
			
	gManager->scores[0] = score0;
	gManager->scores[1] = score1;
	gManager->scores[2] = score2;


	if ( won_bid ) {
		gManager->tbl->last_bid_winner = (*gManager->tbl->winning_bidder)->playerIndex;
		if ( (*gManager->tbl->winning_bidder)->bid == 5 ) {
			gManager->tbl->won_smudge = true;
		}
		else {
			gManager->tbl->won_smudge = false;
		}
		
	}
	else {
		gManager->tbl->last_bid_winner = -1;
		gManager->tbl->won_smudge = false;
	}

}


void Trick::NewScore(Int16 *score0, Int16 *score1, Int16 *score2,
						Boolean won_bid,
						Int16 tmp_high, Int16 tmp_low, Int16 tmp_jack, Int16 tmp_game, 
						Card::face_t tmp_high_c, Card::face_t tmp_low_c,
						Boolean smudge ) {


	// check to see if the bidder actually made their bid
	old_score0 = gManager->scores[0];
	old_score1 = gManager->scores[1];
	old_score2 = gManager->scores[2];

	Int16 p[2];

	if ( gManager->CutThroat() ) {
		p[0] = (*gManager->tbl->winning_bidder)->playerIndex;
		p[1] = (*gManager->tbl->winning_bidder)->playerIndex;
	}
	else {
		if ( (*gManager->tbl->winning_bidder)->playerIndex == 0 || 
			(*gManager->tbl->winning_bidder)->playerIndex == 2 ) {
			p[0] = 0;
			p[1] = 2;
		}
		else {
			p[0] = 1;
			p[1] = 3;
		}
	}


	Int16 points[4] = {0, 0, 0, 0};

	points[high_p]++;
	points[low_p]++;
	
	if ( game_p != -1 ) {
		points[game_p]++;
	}
	
	if ( jack_p != -1 ) {
		points[jack_p]++;
	}
	
	if ( smudge ) {
		points[(*gManager->tbl->winning_bidder)->playerIndex]++;
	}

	if ( gManager->CutThroat() ) {

		if ( ! won_bid ) {
			points[(*gManager->tbl->winning_bidder)->playerIndex] = gManager->tbl->bid * -1;
		}

		old_score0 += points[0];
		old_score1 += points[1];
		old_score2 += points[2];

	}
	else {

		if ( won_bid ) {
			old_score0 += points[0] + points[2];
			old_score1 += points[1] + points[3];
		}
		else {

			if ( p[0] == 0 || p[1] == 2 ) {
				old_score0 -= gManager->tbl->bid;
				old_score1 += points[1] + points[3];
			}
			else {
				old_score0 += points[0] + points[2];
				old_score1 -= gManager->tbl->bid;
			}
		
		}

	}

	*score0 = old_score0;
	*score1 = old_score1;
	*score2 = old_score2;

									
}

Boolean Trick::CalculateGamePoints(Int16 *tmp_high, Int16 *tmp_low, Int16 *tmp_jack, Int16 *tmp_game, 
									Card::face_t *tmp_high_c, Card::face_t *tmp_low_c, Boolean *won_smudge ) {

	*tmp_high = -1;
	*tmp_low = -1;
	*tmp_jack = -1;
	*tmp_game = -1;

	*tmp_high_c = (Card::face_t)0;
	*tmp_low_c = (Card::face_t)-1;

	//
	// we need some special logic for points since two partners share their points
	//
	if ( gManager->GetTeamPoints('a') > gManager->GetTeamPoints('b') &&
			gManager->GetTeamPoints('a') > gManager->GetTeamPoints('c')	) {
		*tmp_game = 0;
	}
	else if ( gManager->GetTeamPoints('b') > gManager->GetTeamPoints('a') &&
			gManager->GetTeamPoints('b') > gManager->GetTeamPoints('c')	) {
		*tmp_game = 1;
	}
	else if ( gManager->GetTeamPoints('c') > gManager->GetTeamPoints('a') &&
			gManager->GetTeamPoints('c') > gManager->GetTeamPoints('b')	) {
		*tmp_game = 2;
	}
	else {
		*tmp_game = -1;
	}


	for (Int16 i = 0; i < gManager->numPlayers; i++) {

		Player *p = gManager->players[i];

		for( CArray<Card*>::iterator a = gManager->players[i]->winnings.BeginIterator() ;
			a != gManager->players[i]->winnings.EndIterator(); a++) {


			if ( (*a)->Suit() == gManager->tbl->trump ) {

				if (*tmp_high_c <= (*a)->Face() ) { 
					*tmp_high_c = (*a)->Face();
					*tmp_high = i; 
				}
					
				if ( *tmp_low_c >= (*a)->Face() ) {
					*tmp_low_c = (*a)->Face();
					*tmp_low = i;
				}
				
				/* check for jack */
				if ( (*a)->Face() == Card::jack ) { 
					*tmp_jack = i;
				}
			}

		}

	}


	Int16 points[4] = {0, 0, 0, 0};

	points[*tmp_high]++;
	points[*tmp_low]++;
	
	if ( (*tmp_game) != -1 ) {
		points[*tmp_game]++;
	}
	
	if ( (*tmp_jack) != -1 ) {
		points[*tmp_jack]++;
	}
	

	won_bid = false;

	if ( gManager->CutThroat() ) {

		if ( points[(*gManager->tbl->winning_bidder)->playerIndex] >= gManager->tbl->bid ) {
			won_bid = true;
		}
		else {
			won_bid = false;
		}

	
	}
	else {

		if ( (*gManager->tbl->winning_bidder)->playerIndex == 0 || 
				(*gManager->tbl->winning_bidder)->playerIndex == 2 ) {

			if ( points[0] + points[2] >= gManager->tbl->bid ) {
				won_bid = true;
			}
			else {
				won_bid = false;
			}

		}
		else {

			if ( points[1] + points[3] >= gManager->tbl->bid ) {
				won_bid = true;
			}
			else {
				won_bid = false;
			}

		}
	}


	//
	// do a check for smudge here
	//

	*won_smudge = false;

	if ( (*gManager->tbl->winning_bidder)->Bid() == 5 ) {

		if ( gManager->CutThroat() ) {
			Int16 cards_won = (*gManager->tbl->winning_bidder)->winnings.GetCount();
			if ( cards_won >= 18 && points[(*gManager->tbl->winning_bidder)->playerIndex] >= 4 ) {
				won_bid = true;
				*won_smudge = true;
			}
			else {
				won_bid = false;
			}
		
		}
		else {

			Int16 cards_won_1 = gManager->players[0]->winnings.GetCount() + gManager->players[2]->winnings.GetCount();
			Int16 cards_won_2 = gManager->players[1]->winnings.GetCount() + gManager->players[3]->winnings.GetCount();

			if ( (*gManager->tbl->winning_bidder)->playerIndex == 0 || 
						(*gManager->tbl->winning_bidder)->playerIndex == 2 ) {
				if ( cards_won_1 >= 24 && points[0] + points[2] >= 4 ) {
					*won_smudge = true;
					won_bid = true;
				}
				else {
					won_bid = false;
				}
			}
			else {
				if ( cards_won_2 >= 24 && points[1] + points[3] >= 4 ) {
					*won_smudge = true;
					won_bid = true;
				}
				else {
					won_bid = false;
				}
			}
		}

	}


	//
	// refresh our score values after bid checking 
	//

	score0 = gManager->scores[0];
	score1 = gManager->scores[1];
	score2 = gManager->scores[2];

	return won_bid;

}


void Trick::Read(CStream& rs) {
	
	Int16 tmp = 0;
	Int16 card_offset = 0;
	Int16 player_index = 0;
	Card *tmpcard = NULL;

	rs >> no_trump_first_trick;
	rs >> first_trick;
	rs >> cards_left;
	rs >> trump_played;

	rs >> won_bid;

	// this will be the # of cards in the book
	rs >> tmp;

	// read in the book
	for ( Int16 i = 0; i < tmp; i++ ) {

		rs >> player_index;
		rs >> card_offset;

		Card *tmp = gManager->theDeck->GetCard(card_offset);
		PlayersCard *p = new PlayersCard(gManager->players[player_index], tmp);

		book->Add(p);
	}

	// get the current winner
	rs >> player_index;

	if ( player_index != -1 ) {
		rs >> card_offset;
		tmpcard = gManager->theDeck->GetCard(card_offset);

		Int16 bookcount = book->GetCount();

		for ( Int16 i = 0; i < bookcount; i++ ) {
		
			PlayersCard *tmp = book->GetAt(i);
		
			if ( tmp->c == tmpcard ) {
				current_winner = tmp;
				break;
			}
		}

	}
	else {
		current_winner = NULL;
	}	

	// get the lead playerscard	
	rs >> player_index;

	if ( player_index != -1 ) {
		rs >> card_offset;
		tmpcard = gManager->theDeck->GetCard(card_offset);

		Int16 bookcount = book->GetCount();

		for ( Int16 i = 0; i < bookcount; i++ ) {
		
			PlayersCard *tmp = book->GetAt(i);
		
			if ( tmp->c == tmpcard ) {
				lead = tmp;
				break;
			}
		}

	}
	else {
		lead = NULL;
	}	





	// get the team winnings
	for ( Int16 j = 0; j < 3; j++ ) {

		// this is the # of cards for this team
		rs >> tmp;

		for ( Int16 i = 0; i < tmp; i++ ) {
			rs >> card_offset;
			tmpcard = gManager->theDeck->GetCard(card_offset);
			team_winnings[j].Add(tmpcard);
		}

	}

	// get the played cards
	for ( Int16 j = 0; j < 4; j++ ) {
	

		// this is the # of cards in this suit
		rs >> tmp;

		for ( Int16 i = 0; i < tmp; i++ ) {
			rs >> card_offset;
			tmpcard = gManager->theDeck->GetCard(card_offset);
			played_cards[j].Add(tmpcard);
		}

	}


}

void Trick::Write(CStream& rs) {

	rs << no_trump_first_trick;
	rs << first_trick;
	rs << cards_left;
	rs << trump_played;
	rs << won_bid;

	rs << book->GetCount();

	for ( CArray<PlayersCard*>::iterator i = book->BeginIterator() ;
			 i != book->EndIterator();
			 i++) {

		rs << (*i)->p->playerIndex;
		rs << (*i)->c->Offset();
	}


	if ( current_winner ) {
		rs << current_winner->p->playerIndex;
		rs << current_winner->c->Offset();
	}
	else {
		rs << -1;
	}	

	if ( lead ) {
		rs << lead->p->playerIndex;
		rs << lead->c->Offset();
	}
	else {
		rs << -1;
	}

	for ( Int16 j = 0; j < 3; j++ ) {
	
		rs << team_winnings[j].GetCount();
	
		for ( CArray<Card*>::iterator i = team_winnings[j].BeginIterator() ;
				 i != team_winnings[j].EndIterator();
				 i++) {

//			Card *tmp = (*i);
//			tmp->Write(rs);
			rs << (*i)->Offset();

		}
	}

	for ( Int16 j = 0; j < 4; j++ ) {
	
		rs << played_cards[j].GetCount();
	
		for ( CArray<Card*>::iterator i = played_cards[j].BeginIterator() ;
				 i != played_cards[j].EndIterator();
				 i++) {

			rs << (*i)->Offset();

		}
	}

} // Write


