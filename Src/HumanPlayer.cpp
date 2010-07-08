#include "HumanPlayer.h"


HumanPlayer::HumanPlayer() { 
}

HumanPlayer::HumanPlayer(char c) : Player(c, "human") { 
}

HumanPlayer::HumanPlayer(char c, CString name) : Player(c, name) { 
}

HumanPlayer::~HumanPlayer() {
}


/* when human plays Card */
Boolean HumanPlayer::PickCard(Trick * trk) {
	return false;
}

Int16 HumanPlayer::BeginBidProcess(Player *dealer, Player *current_winner) {
	return bid;
}

// function for setting trump if player wins bid
Card::suit_t HumanPlayer::Trump() {
	return bestSuit;
}	
