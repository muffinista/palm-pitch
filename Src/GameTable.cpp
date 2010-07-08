#include "GameTable.h"
#include "GameManager.h"


extern GameManager *gManager;

GameTable::GameTable() {

	trump = (Card::suit_t)-1;
	bid = -1;
	high_bid = -1;
	
	dealer = NULL;
	winning_bidder = NULL;
	current_bidder = NULL;

	lead = NULL;

	last_bid_winner = -1;
	won_smudge = false;
}

GameTable::~GameTable() {

	played_cards.DeleteAll();
	DeleteCardHistory();
}

void GameTable::clear_played_cards() {
	played_cards.DeleteAll();
}

void GameTable::Dealer(CArray<Player *>::iterator p) {
	dealer = p;
}


void GameTable::Reset() {
	Reset(true);
}

void GameTable::DeleteCardHistory() {

	for ( Int16 i = 0; i < CARDS_IN_HAND; i++ ) {

		int tmp = card_history[i].GetCount();
		
		for (int j = tmp - 1; j >= 0; j-- ) {
			PlayersCard *foo = card_history[i].GetAt(j);
			delete foo;
		}

		card_history[i].DeleteAll();

	} // for

}

void GameTable::Reset(Boolean move_game) {


	played_cards.DeleteAll();
	
	DeleteCardHistory();


	trump = (Card::suit_t)-1;
	bid = -1;
	high_bid = -1;


	//
	// move the deal along
	//
//	if ( ! move_game && dealer ) {
	if ( move_game && dealer ) {
		dealer = gManager->getNextPlayerIter(dealer);
		current_bidder = gManager->getNextPlayerIter(dealer);
	}

	lead = NULL;

}


void GameTable::RecordRound(CArray<PlayersCard *> *book, Player *round_winner) {

	Int16 j = 0;

	for ( CArray<PlayersCard*>::iterator i = book->BeginIterator() ; 
		i != book->EndIterator(); i++) {

		PlayersCard *foo = new PlayersCard( (*i)->p, (*i)->c );
		card_history[gManager->trick_rounds].Add( foo );
		
		if ( (*i)->p == round_winner ) {
			won_round[gManager->trick_rounds][j] = true;
		}
		else {
			won_round[gManager->trick_rounds][j] = false;
		}

		j++;
	}

}

void GameTable::Read(CStream& rs) {

	Int16 tmp = 0;

	// get the winning bid
	rs >> bid;

	// get the current high bid (during bidding process)
	rs >> high_bid;

	// get the last bid winner
	rs >> last_bid_winner;
	rs >> won_smudge;

	// get the dealer
	rs >> tmp;
	if ( tmp != -1 ) {
		dealer = gManager->getPlayerIter(tmp);
	}
	else {
		dealer = NULL;
	}

	// get the winning bidder
	rs >> tmp;
	if ( tmp != -1 ) {
		winning_bidder = gManager->getPlayerIter(tmp);
	}
	else {
		winning_bidder = NULL;
	}

	// get the current bidder
	rs >> tmp;
	if ( tmp != -1 ) {
		current_bidder = gManager->getPlayerIter(tmp);
	}
	else {
		current_bidder = NULL;
	}

	// get the lead player
	rs >> tmp;
	if ( tmp != -1 ) {
		lead = gManager->players[tmp];
	}
	else {
		lead = NULL;
	}
	

	// get the played cards
	rs >> tmp;
	
	for ( Int16 i = 0; i < tmp; i++ ) {
		Int16 tmp2;
		rs >> tmp2;
		
		Card *c = gManager->theDeck->GetCard(tmp2);
		played_cards.Add(c);
	
	}

	rs >> tmp;

	// get trump
	trump = (Card::suit_t)tmp;


	//
	// card history
	//
	for ( int x = 0; x < CARDS_IN_HAND; x++ ) {

		int count = 0;
		rs >> count;
		
		if ( count > 0 ) {
			for ( int tmp = 0; tmp < count; tmp++ ) {
				int tmp_player;
				int offset;
				
				rs >> tmp_player;
				rs >> offset;

				Card *c = gManager->theDeck->GetCard(offset);
				PlayersCard *p = new PlayersCard(gManager->players[tmp_player], c);

				card_history[x].Add(p);
			
			}
		}
		else {
			break;
		}
	}


} // Read

void GameTable::Write(CStream& rs) {

	// set the winning bid
	rs << bid;

	// set the current high bid (during bidding process)
	rs << high_bid;

	// set the last bid winner
	rs << last_bid_winner;
	rs << won_smudge;

	// set the dealer
	if ( dealer ) {
		rs << (*dealer)->playerIndex;
	}
	else {
		rs << -1;
	}

	// set the winning bidder
	if ( winning_bidder ) {
		rs << (*winning_bidder)->playerIndex;
	}
	else {
		rs << -1;
	}

	// set the current bidder
	if ( current_bidder ) {
		rs << (*current_bidder)->playerIndex;
	}
	else {
		rs << -1;
	}

	// set the lead player
	if ( lead ) {
		rs << lead->playerIndex;
	}
	else {
		rs << -1;
	}
	
	// set the played cards
	rs << played_cards.GetCount();
	for ( CArray<Card*>::iterator i = played_cards.BeginIterator() ; 
		i != played_cards.EndIterator(); i++) {
		rs << (*i)->Offset();
	}

	// set trump
	Int16 tmp = (Int16)trump;
	rs << tmp;


	//
	// card history
	//
	for ( int x = 0; x < CARDS_IN_HAND; x++ ) {

		int count = card_history[x].GetCount();
		rs << count;

		if ( count > 0 ) {
			for ( CArray<PlayersCard*>::iterator i = card_history[x].BeginIterator() ; 
				i != card_history[x].EndIterator(); i++) {
				
				int p = (*i)->p->playerIndex;
				int c = (*i)->c->Offset();
				
				rs << p;
				rs << c;
			}
		}
		else {
			break;
		}
	}

}
