#ifndef PLAYERSCARD_H
#define PLAYERSCARD_H

#include "Player.h"
#include "Card.h"

class Player;
class Card;

class PlayersCard {

	public:
		PlayersCard(Player *, Card *);
		~PlayersCard();

		Player *p;
		Card *c;

};

#endif
