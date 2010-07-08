#include "Player.h"
#include "GameManager.h"

extern GameManager *gManager;

Int16 Player::playerIndex_static = 0;

Player::~Player() {
	playerIndex_static--;

	hand.DeleteAll();
	winnings.DeleteAll();
	played_cards.DeleteAll();

}

Player::Player() {

//	StrCopy(name, "chuck");
	playerIndex = playerIndex_static;
	playerIndex_static++;

	bid = -1;
	bestSuit = (Card::suit_t)-1;
	
	played_card = NULL;
	
	gamepoints = 0;
}


Player::Player(char c, CString myname) : 
	playerIndex(playerIndex_static), team(c),
	partner(NULL),
	bid(-1), bestSuit((Card::suit_t)-1), played_card(NULL), gamepoints(0) {

//	StrCopy(name, myname);
	name = myname;
	playerIndex_static++;;
}


void Player::Read(CStream& rs) {

	Int16 card_offset = 0;
	
	rs >> playerIndex;
	
	CString tmpname;
	rs >> tmpname;
	
	name = tmpname;

	rs >> team;

	rs >> bid;
	
	Int16 tmpsuit;
	rs >> tmpsuit;
	
	bestSuit = (Card::suit_t)tmpsuit;

	rs >> gamepoints;

	rs >> TOLERANCE;
	rs >> PARTNER_WIN_TOLERANCE;
	rs >> VALUE_TOLERANCE;
	rs >> LOW_TRUMP_HOLD_VAL;

	Int16 tmp = 0;
	rs >> tmp;
	no_trump_first_trick = tmp;

	rs >> tmp;
	out_of_trump = tmp;

	Int16 hand_count = 0;
	rs >> hand_count;

	for ( Int16 i = 0; i < hand_count; i++ ) {
		Int16 card_offset = 0;
		rs >> card_offset;
		Card *tmp = gManager->theDeck->GetCard(card_offset);
		hand.Add(tmp);
	}


	Int16 winnings_count = 0;
	rs >> winnings_count;

	for ( Int16 i = 0; i < winnings_count; i++ ) {
		Int16 card_offset = 0;
		rs >> card_offset;
		Card *tmp = gManager->theDeck->GetCard(card_offset);
		winnings.Add(tmp);
	}

	Int16 played_cards_count = 0;
	rs >> played_cards_count;

	for ( Int16 i = 0; i < played_cards_count; i++ ) {
		rs >> card_offset;
		Card *tmp = gManager->theDeck->GetCard(card_offset);
		played_cards.Add(tmp);
	}
	
	rs >> card_offset;
	if ( card_offset != 53 ) {
		Card *tmp = gManager->theDeck->GetCard(card_offset);
		played_card = tmp;
	}
	else {
		played_card = NULL;
	}

}


void Player::Write(CStream& rs) {

	rs << playerIndex;
	rs << (const char *)name.GetBuffer();
	name.ReleaseBuffer();

	rs << team;

	rs << bid;
	
	Int16 tmp = (Int16)bestSuit;
	rs << tmp;

	rs << gamepoints;

	rs << TOLERANCE;
	rs << PARTNER_WIN_TOLERANCE;
	rs << VALUE_TOLERANCE;
	rs << LOW_TRUMP_HOLD_VAL;	
	rs << (Int16)no_trump_first_trick;
	rs << (Int16)out_of_trump;

	rs << hand.GetCount();
	for ( CArray<Card*>::iterator i = hand.BeginIterator() ; 
		i != hand.EndIterator(); i++) {
		rs << (*i)->Offset();
	}

	rs << winnings.GetCount();
	for ( CArray<Card*>::iterator i = winnings.BeginIterator() ; 
		i != winnings.EndIterator(); i++) {
		rs << (*i)->Offset();
	}

	rs << played_cards.GetCount();
	for ( CArray<Card*>::iterator i = played_cards.BeginIterator() ; 
		i != played_cards.EndIterator(); i++) {
		rs << (*i)->Offset();
	}

	if ( played_card ) {
		rs << played_card->Offset();
	}
	else {
		rs << 53;
	}

}



/* deals Player their cards */
void Player::dealCards( Deck &d, Int16 numCards ) {

	hand.DeleteAll();

	for (Int16 i = 0; i < numCards; i++) {
		hand.Add( d.deal() );
	}

}


void Player::claimWinnings(CArray<PlayersCard *> *book) {

	for ( CArray<PlayersCard*>::iterator i = book->BeginIterator() ; 
		i != book->EndIterator(); i++)
	{
		switch ( (*i)->c->Face() )
		{
			case Card::jack:	gamepoints += 1; break;
			case Card::queen:	gamepoints += 2; break;
			case Card::king:	gamepoints += 3; break;
			case Card::ace:		gamepoints += 4; break;
			case Card::ten:		gamepoints += 10; break;
			default: break;
		}

		winnings.Add( (*i)->c );
	}

}


/* funtion that determines if you can follow suit of follow trump */
Boolean Player::followSuit(Trick * trk, Card *c) {

	//
	// if some knucklehead wants to win the bid even though
	// they don't have any trump cards, this code will let the
	// game continue
	//
	if ( trk->FirstTrickP() &&
		trk->lead == NULL &&
		! HasSuit(trk->getTrump() )
		) {
		return true;
	}


	/* 	
		if lead is not set, the you can lead trump 
		if your Card is the same suit as trump, you can play
		if your Card is the same suit as lead Card you can play
	*/
	if ( trk->no_trump_first_trick == true && 
		c->Suit() == trk->getTrump() && 
		trk->FirstTrickP() ) {
			return false;
	}

	//
	// don't allow non-trump if this is the dealer and its the 1st hand
	//
	if ( trk->no_trump_first_trick == false && 
		c->Suit() != trk->getTrump() && 
		trk->FirstTrickP() &&
		trk->lead == NULL ) {

			return false;

	}

	if ( trk->lead == NULL ) {
		return true;
	}


	if ( c->Suit() == trk->getTrump() || c->Suit() == trk->getLead() ) {
		return true;
	}
	else if ( HasSuit(trk->getLead() ) ) {
		return false;
/*		for ( CArray<Card *>::iterator i = hand.BeginIterator() ; 
				i != hand.EndIterator(); i++)
		{
			if ( (*i) != c && (*i)->Suit() == trk->getLead() ) {

				// if found that you have a Card that can follow suit, 
				// you must play it, so return false
				return false;	
			}
		}
*/
	}


	/*
		if found that you do not have suit 
		that matches lead or trump,
		you can play anything
	*/
	return true;


}

Boolean Player::HasSuit(Card::suit_t s) {

	for ( CArray<Card *>::iterator i = hand.BeginIterator() ; 
			i != hand.EndIterator(); i++) {

		if ( (*i)->Suit() == s ) {
			return true;
		}
	}
	
	return false;
}

/* 'getter' function for the Player's bid */
Int16 Player::Bid() {
	return bid;
}

CString Player::getName() {
	return name;
}

Card::suit_t Player::Trump() {

	Card::suit_t trump;
	trump = Card::club;
	return trump;
}	

void Player::assignPartner(Player *p) {
	partner = p;
}

Int16 Player::getPoints() {
	return gamepoints;
}

char Player::getTeam() {
	return team;
}


void Player::sort_hand() {

	//
	// first, sort by suit
	//
    for( Int16 p = 1; p < hand.GetCount(); p++ ) {

	    Card *tmp = hand[p];

	    Int16 j;

	    for( j = p; j > 0 && (tmp->Suit() > hand[ j - 1 ]->Suit() ); j-- ) {
	    	hand[ j ] = hand[ j - 1 ];
		}
		hand[ j ] = tmp;
	}


	//
	// then sort by face
	//
    for( Int16 p = 1; p < hand.GetCount(); p++ ) {

	    Card *tmp = hand[p];

	    Int16 j;

	    for( j = p; j > 0 && (tmp->Suit() == hand[ j - 1 ]->Suit() && tmp->Face() > hand[ j - 1 ]->Face()); j-- ) {
	    	hand[ j ] = hand[ j - 1 ];
		}
		hand[ j ] = tmp;
	}


}

Boolean Player::NoTrumpFirstTrickP() {
	return no_trump_first_trick;
}


/* clears winnings after a hand has been played */
void Player::clearWinnings( ) {
	out_of_trump = false;
	gamepoints = 0;
	winnings.DeleteAll();
}

void Player::post_hand_cleanup() {
	played_cards.DeleteAll();
	clearWinnings();
}

void Player::post_game_cleanup() {
	post_hand_cleanup();
	
	bid = -1;
	bestSuit = (Card::suit_t)-1;
//	myScore = 0;
	gamepoints = 0;
	
	hand.DeleteAll();
	no_trump_first_trick = false;

}

Card *Player::PlayedCard() {
	return played_card;
}

void Player::Bid(Int16 x) {
	bid = x;
}