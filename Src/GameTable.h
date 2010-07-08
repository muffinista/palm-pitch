#ifndef TABLE_H
#define TABLE_H

#include "common.h"

#include "Card.h"
#include "PlayersCard.h"

class Card;
class Player;

class GameTable {

	public:
		GameTable();
		GameTable(Int16);
		~GameTable();

		void Reset(Boolean move_bid);
		void Reset();

		void Dealer(CArray<Player *>::iterator p);
		void clear_played_cards();

		void RecordRound(CArray<PlayersCard *> *book, Player *round_winner);

		//
		// load/save routines
		//
		void Read(CStream& rStream);
		void Write(CStream& rStream);

		void DeleteCardHistory();


		// what suit is trump
		Card::suit_t trump;

		// the winning bid
		Int16 bid;

		// set during the bidding process
		Int16 high_bid;

		// who won the last bid?  -1 if no one
		Int16 last_bid_winner;
		
		Boolean won_smudge;

		CArray<Player *>::iterator dealer;
		CArray<Player *>::iterator winning_bidder;
		CArray<Player *>::iterator current_bidder;

		Player *lead;

		CArray<Card*> played_cards;

		CArray<PlayersCard *> card_history[6];

		Boolean won_round[6][4];

};

#endif

