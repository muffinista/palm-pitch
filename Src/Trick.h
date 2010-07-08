#ifndef TRICK_H
#define TRICK_H

#include "PlayersCard.h"

class Player;

class Trick {

	public:

		Trick();
		~Trick();

		//
		// load/save routines
		//
		void Read(CStream& rStream);
		void Write(CStream& rStream);


		//
		// cleanup routines
		//
		void CleanUp();
		void PostHandCleanUp();


		//
		// routines for AI, display, etc.
		//
		Boolean FirstTrickP();
		Player *Winner();
		Card::suit_t getLead();
		Card::suit_t getTrump();
		Boolean hasJack();
		Boolean hasTen();
		Card *currentLow();
		Card *currentHigh();
		Card *highestCardNotPlayed(Card::suit_t f);
		Card *highestCardPlayed(Card::suit_t f);
		Card *lowestCardPlayed();
		Boolean noTrumpLeft(Player *p);
		
		//
		// logic routines
		//
		Card *RecordPlayedCard(Player *, Card *);

		
		Boolean CalculateGamePoints(Int16 *tmp_high, Int16 *tmp_low, Int16 *tmp_jack, Int16 *tmp_game, 
										Card::face_t *tmp_high_c, Card::face_t *tmp_low_c,
										Boolean *won_smudge );

		void ApplyGamePoints();


		/* public member fields */
		CArray<PlayersCard *> *book;

		PlayersCard *current_winner;
		PlayersCard *lead;

		CArray<Card*> team_winnings[3];
		CArray<Card*> played_cards[4];

		#define played_clubs  		played_cards[0]
		#define played_diamonds 	played_cards[1]
		#define played_hearts  		played_cards[2]
		#define played_spades  		played_cards[3]

		Boolean no_trump_first_trick;
		Boolean first_trick;
		Boolean won_bid;
		Int16 cards_left;
		
		Int16 trump_played;

	private:

		Boolean isCardPlayed(Card::suit_t s, Card::face_t f);

		void NewScore(Int16 *score0, Int16 *score1, Int16 *score2,
						Boolean won_bid,
						Int16 tmp_high, Int16 tmp_low, Int16 tmp_jack, Int16 tmp_game, 
						Card::face_t tmp_high_c, Card::face_t tmp_low_c,
						Boolean smudge );

		/* pointers to high and low card */
		Card::face_t high_c;
		Card::face_t low_c;
		
		/* pointer to players of high and low cards and jack */
		Int16 high_p;
		Int16 low_p;
		Int16 jack_p;
		Int16 game_p;

		Int16 old_score0;
		Int16 old_score1;
		Int16 old_score2;

		Int16 score0;
		Int16 score1;
		Int16 score2;

};

#endif
