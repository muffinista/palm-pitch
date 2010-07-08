#ifndef ai_H
#define ai_H

#include "Player.h"

class ComputerPlayer : public Player {

	public:
		ComputerPlayer();
		explicit ComputerPlayer(char, CString);
		~ComputerPlayer();

		Card::suit_t Trump();
       	Boolean PickCard( Trick * );
		Card *PlayedCard();
		Int16 BeginBidProcess(Player *, Player *);

	private:

		void sortHand();		
		Int16 handValue(Int16 suit, Boolean partner_winning, Int16 partner_bid, Int16 ourScore, Int16 theirScore);
		void analyzeHand(Player *bidder);

		Boolean is_partner_winning(Trick *trk);
		Boolean want_trick(Trick *t);

		Int16 chance_of_winning_point(Trick *t, Card *c);
		Int16 chance_of_winning_hand(Trick *t, Card *c);
		Int16 chance_of_winning_hand(Trick *trk, Card *c, Boolean checking_partner_card);

		Card *first_pick_card(Trick *trk);
		Card *middle_pick_card(Trick *trk);
		Card *last_pick_card(Trick *trk);

		Card * pick_card(Trick *);

		Boolean haveLeadPlay();
		Boolean haveLastPlay();

		Boolean have_jack;
		Boolean have_high;

		Card::suit_t choose_suit;

		CArray<Card*> suits[4];

		#define my_clubs  		suits[0]
		#define my_diamonds 	suits[1]
		#define my_hearts  	suits[2]
		#define my_spades  	suits[3]
};

#endif
