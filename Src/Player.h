#ifndef PLAYER_H
#define PLAYER_H

#include "Common.h"

class PlayersCard;
class GameTable;
class Trick;

#include "Deck.h"
#include "PlayersCard.h"
#include "Trick.h"

typedef enum { 
	Human,
	Computer,
	Remote
} PlayerType;


class Player {
	
	public:

		Player();
		Player(char, CString);
		virtual ~Player();

		virtual Int16 BeginBidProcess(Player *, Player *) = 0;

		// let the player pick a card, return true
		// if they did and false if they didn't
		virtual Boolean PickCard( Trick * ) = 0;

		virtual Card::suit_t Trump() = 0;

		Boolean NoTrumpFirstTrickP();

		char getTeam();
		CString getName();
		Int16 getPoints();

		Int16 Bid();
		void Bid(Int16);

		void dealCards(Deck &, Int16 numCards );
		void sort_hand();

		// get the card the player chose
		Card *PlayedCard();
		
		void clearWinnings();			
		void claimWinnings(CArray<PlayersCard *> *);

		void assignPartner(Player *);

		void print_debug_hand();
		
		void post_hand_cleanup();
		void post_game_cleanup();

		Boolean followSuit(Trick *, Card *);



		/* public member fields */

		static Int16 card_width;
		static Int16 card_height;
		static Int16 card_spacing;

		static Int16 playerIndex_static;

		Int16 playerIndex;

		CArray<Card *> winnings;
		CArray<Card *> played_cards;

		Int16 bid;
		Card::suit_t  bestSuit;

		Player * partner;
		char team;
		CString name;

		Int16 gamepoints;

		CArray<Card *> hand;

		Boolean no_trump_first_trick;
		Boolean out_of_trump;
		Card *played_card;

		void Read(CStream& rStream);
		void Write(CStream& rStream);

		Boolean HasSuit(Card::suit_t s);

	protected:

		Int32 TOLERANCE;
		Int32 PARTNER_WIN_TOLERANCE;
		Int32 VALUE_TOLERANCE;

		Int16 LOW_TRUMP_HOLD_VAL;

};

#endif
