#include <PalmOS.h>
#include "Common.h"

#include "ComputerPlayer.h"
#include "GameManager.h"
#include "GameTable.h"
#include "HumanPlayer.h"
#include "PitchApp.h"


GameManager::GameManager() {

	//
	// set some defaults
	//
	cutthroat = false;

	winning_score = 11;
	first_game = true;
	
	scores[0] = 0;
	scores[1] = 0;
	scores[2] = 0;

	numPlayers = 0;
	game_status = PreGame;
	trick_rounds = 0;
	cards_played = 0;
	
	human = NULL;
	current = NULL;

	games_won[0] = 0;
	games_won[1] = 0;
	games_won[2] = 0;

	ai_level = 100;

	//
	// create some objects
	//
	theDeck = new Deck();
	trk = new Trick();
	tbl = new GameTable();


}


GameManager::~GameManager() {

	delete theDeck;
	delete trk;
	delete tbl;

	for( Int16 i = 0; i < numPlayers; i++ ) {
		delete players[i];
	}
}

void GameManager::Reset() {

	delete theDeck;
	delete trk;
	delete tbl;
	
	for( Int16 i = 0; i < numPlayers; i++ ) {
		delete players[i];
	}

	players.DeleteAll();
	Player::playerIndex_static = 0;

	first_game = true;
	
	scores[0] = 0;
	scores[1] = 0;
	scores[2] = 0;

	numPlayers = 0;
	game_status = PreGame;
	trick_rounds = 0;
	cards_played = 0;
	
	human = NULL;
	current = NULL;

	theDeck = new Deck();
	trk = new Trick();
	tbl = new GameTable();
	
}


void GameManager::ShortDelay() {
	if ( HostGremlinIsRunning() == false ) {
		SysTaskDelay( play_delay_ticks * 3 / 4);
	}
}


void GameManager::LongDelay() {

	if ( HostGremlinIsRunning() == false ) {
		SysTaskDelay( play_delay_ticks );
	}

}


void GameManager::Load() {

	CAppPrefStream pref(CreatorID, PrefID, PrefVersion);

	if ( pref.Read() ) {

		Int16 tmp = 0;

		// load the GameStatus
		pref >> tmp;
		Status((GameStatus)tmp);

		// load the # of players
		pref >> numPlayers;

		if ( numPlayers ) {
			createPlayers();
		}
		// load player data accoring to # of players
		for ( Int16 i = 0; i < numPlayers; i++ ) {
			players[i]->Read(pref);
		} // for
		
		assignTeams();

		// load the human
		pref >> tmp;
		if ( tmp != -1 ) {
			human = getPlayerIter(tmp);
		}
		else {
			human = NULL;
		}

		// load the current player
		pref >> tmp;
		if ( tmp != -1 ) {
			current = getPlayerIter(tmp);
		}
		else {
			current = NULL;
		}

		pref >> scores[0];
		pref >> scores[1];
		pref >> scores[2];
		pref >> first_hand;
		pref >> first_game;

		pref >> winning_score;
		for ( int i = 0; i < 4; i++ ) {
			pref >> player_names[i];
		}
		pref >> play_delay_ticks;
		pref >> no_trump_first_trick;
		pref >> dealer_take_bid;
		pref >> win_on_bid;
		pref >> games_played;

		pref >> games_won[0];
		pref >> games_won[1];
		pref >> games_won[2];

		pref >> cards_played;
		pref >> trick_rounds;

		pref >> ai_level;
		pref >> win_on_smudge;

		pref >> cutthroat;

		// load any trick data
		trk->Read(pref);

		// load the game table
		tbl->Read(pref);

		pref.Close();

	}
	else {

		cutthroat = false;
	
		no_trump_first_trick = true;
		dealer_take_bid = true;
		win_on_bid = true;
	
		play_delay_ticks = SysTicksPerSecond();

		const char *random_name[] = {"Chuck", "Mary", "Bob", "Igor", "Marge", "Jill",
									"Billy", "Beth", "Jane", "Izzy", "Yvette",
									"Han", "Peter", "Bruce", "Brian", "Phil", "Eunice"};
		const Int16 name_count = 16;

		Int16 random_num[3];

		random_num[0] = SysRandom(0) % name_count;
		random_num[1] = SysRandom(0) % name_count;
		random_num[2] = SysRandom(0) % name_count;
		
		while ( random_num[0] == random_num[1] || random_num[0] == random_num[2] ||
					random_num[1] == random_num[2] ) {

			random_num[0] = SysRandom(0) % name_count;
			random_num[1] = SysRandom(0) % name_count;
			random_num[2] = SysRandom(0) % name_count;
					
		}
		

		player_names[1] = random_name[random_num[0]];
		player_names[2] = random_name[random_num[1]];
		player_names[3] = random_name[random_num[2]];

		const char *human = "Human";
		player_names[0] = human;
		games_played = 0;

	}

}

void GameManager::Save() {

	CAppPrefStream pref(CreatorID, PrefID, PrefVersion);
	pref.SetSaved(true);

	// save the GameStatus
	pref << (Int16)Status();

	// save the # of players
	pref << numPlayers;

	// save player data
	for ( Int16 i = 0; i < numPlayers; i++ ) {
		players[i]->Write(pref);
	} // for

	// save the human
	if ( human ) {
		pref << (*human)->playerIndex;
	}
	else {
		pref << -1;
	}

	// save the current player
	if ( current ) {
		pref << (*current)->playerIndex;
	}
	else {
		pref << -1;
	}

	pref << scores[0];
	pref << scores[1];
	pref << scores[2];
	pref << first_hand;
	pref << first_game;

	pref << winning_score;

	for ( int i = 0; i < 4; i++ ) {
		pref << player_names[i];
	}

	pref << play_delay_ticks;
	pref << no_trump_first_trick;
	pref << dealer_take_bid;
	pref << win_on_bid;
	pref << games_played;

	pref << games_won[0];
	pref << games_won[1];
	pref << games_won[2];

	pref << cards_played;
	pref << trick_rounds;
	
	pref << ai_level;
	pref << win_on_smudge;

	pref << cutthroat;
	
	// save any trick data
	trk->Write(pref);

	// save the game table
	tbl->Write(pref);

 
} // Save


Boolean GameManager::CutThroat() {

	return cutthroat;
}

void GameManager::CutThroat(Boolean x) {

	if ( players.GetCount() == 0 ) {
		createPlayers();
	}

	if ( cutthroat != x && x == true ) {
//		if ( players.GetCount() == 4 ) {
//			delete players[3];
//			numPlayers = 3;

			players[0]->team = 'a';
			players[1]->team = 'b';
			players[2]->team = 'c';

//		}
	}
	else if ( cutthroat != x && x == false ) {
		if ( players.GetCount() == 3 ) {
			players.Add( new ComputerPlayer('b', player_names[3]) );
			numPlayers = 4;
		}			
			players[0]->team = 'a';
			players[2]->team = 'a';

			players[1]->team = 'b';
			players[3]->team = 'b';
//		}
	}


	cutthroat = x;

}

void GameManager::createPlayers() {

	if ( players.GetCount() == 0 ) {
	
		if ( numPlayers == 3 || CutThroat() ) {
			numPlayers = 3;
			humanIndex = 0;

			CString name1 = player_names[0];
			CString name2 = player_names[1];
			CString name3 = player_names[2];

			players.Add( new HumanPlayer('a', name1) );
			players.Add( new ComputerPlayer('b', name2) );
			players.Add( new ComputerPlayer('c', name3) );
//			players.Add( new HumanPlayer('a', player_names[0]) );
//			players.Add( new ComputerPlayer('b', player_names[1]) );
//			players.Add( new ComputerPlayer('c', player_names[2]) );
		}
		else {
			numPlayers = 4;
			humanIndex = 0;

			CString name1 = player_names[0];
			CString name2 = player_names[1];
			CString name3 = player_names[2];
			CString name4 = player_names[3];

			players.Add( new HumanPlayer('a', name1) );
			players.Add( new ComputerPlayer('b', name2) );
			players.Add( new ComputerPlayer('a', name3) );
			players.Add( new ComputerPlayer('b', name4) );

//			players.Add( new HumanPlayer('a', player_names[0]) );
//			players.Add( new ComputerPlayer('b', player_names[1]) );
//			players.Add( new ComputerPlayer('a', player_names[2]) );
//			players.Add( new ComputerPlayer('b', player_names[3]) );
		}
		
	}


	current = players.BeginIterator();	
	tbl->lead = players[0];
	tbl->winning_bidder = NULL;

	human = players.BeginIterator();
	humanIndex = 0;

}

Player* GameManager::getPlayer(Int16 index) {
	Player *tmp = players[index];
	return tmp;
}


CArray <Player*>::iterator GameManager::getPlayerIter(Int16 index) {

	CArray <Player*>::iterator tmp = players.BeginIterator();

	for ( Int16 i = 0; i < index; i++ ) {
		tmp++;
	}

	return tmp;
}


CArray <Player*>::iterator GameManager::getNextPlayerIter(CArray<Player*>::iterator i) {

	Int16 index = (*i)->playerIndex;


	if ( index == numPlayers - 1 ) {
		CArray <Player*>::iterator tmp = players.BeginIterator();
		return tmp;
	}

	return getPlayerIter(index + 1);

}


Player* GameManager::getNextPlayer(Player *p) {

	if ( p->playerIndex == numPlayers - 1 ) {
		return players[0];
	}

	return players[p->playerIndex + 1];

}

Player* GameManager::getPrevPlayer(Player *p) {

	if ( p->playerIndex == 0 ) {
		return players[numPlayers - 1];
	}

	return players[p->playerIndex - 1];

}

Player* GameManager::getNextPlayer(CArray <Player*>::iterator i) {
	Int16 index = (*i)->playerIndex;
	return getNextPlayer(players[index]);
}

void GameManager::assignTeams() {

	for (CArray <Player*>::iterator i = players.BeginIterator(); i != players.EndIterator(); i++ ) {

		for (CArray <Player*>::iterator a = players.BeginIterator(); a != players.EndIterator(); a++ ) {

			if( (*a)->getTeam() == (*i)->getTeam() & (*a) != (*i) ) {	
				(*a)->assignPartner(*i);
				(*i)->assignPartner(*a);
			}

		}

	}

}


Boolean GameManager::tied() {

	if ( CutThroat() && ( scores[0] == scores[1] || scores[0] == scores[2] || scores[1] == scores[2] ) ) {
		return true;
	}
	else if ( scores[0] == scores[1] ) {
		return true;
	}
	
	return false;

}


void GameManager::dealCards() {

	// clear out our list of played cards
	tbl->clear_played_cards();

	theDeck->reset();

	for (CArray <Player*>::iterator  i = players.BeginIterator(); i != players.EndIterator(); i++ )
	{
		(*i)->dealCards(*theDeck, CARDS_IN_HAND);
		(*i)->clearWinnings();
	}

}

void GameManager::FinalizeBidding( ) {	


}

void GameManager::BidSummary( ) {	


}


void GameManager::ResetBidding() {
//	winner = tbl->dealer;
	tbl->winning_bidder = NULL;
	tbl->high_bid = -1;
}

Boolean GameManager::GetNextBid(Trick *trk, Boolean bid_already_set ) {	

	Player *p = *tbl->current_bidder;

	Int16 tmp = -1;

/*	if ( tbl->winning_bidder ) {
		tmp = p->BeginBidProcess( (*tbl->dealer), *tbl->winning_bidder );
	}
	else {
		tmp = p->BeginBidProcess( (*tbl->dealer), NULL );	
	}

	if ( p->playerIndex == (*tbl->dealer)->playerIndex && tmp < 2 && tbl->high_bid < 2 ) {
		tmp = 2;
	}
*/

	if ( p->playerIndex == (*tbl->dealer)->playerIndex && tbl->high_bid < 2 ) {
		p->BeginBidProcess( (*tbl->dealer), NULL );	
		tmp = 2;
	}
	else if ( tbl->winning_bidder ) {
		tmp = p->BeginBidProcess( (*tbl->dealer), *tbl->winning_bidder );
	}
	else {
		tmp = p->BeginBidProcess( (*tbl->dealer), NULL );	
	}

	//
	// the bid either must be higher, or the dealer can take the bid - if that pref is set
	//
	if (
		tmp > tbl->high_bid || 
		( dealer_take_bid && 
			(*tbl->current_bidder)->playerIndex == (*tbl->dealer)->playerIndex && 
			tmp >= tbl->high_bid )
		) {

		//
		// this bidder is the new winner
		//		
		tbl->winning_bidder = tbl->current_bidder;
		tbl->lead = (*tbl->winning_bidder);

		// don't let the dealer bid more than has already been 
		// bid, unless it's smudge
		if ( tbl->winning_bidder == tbl->dealer && tmp != 5 ) {
			tmp = tbl->high_bid;
		}

		if ( tbl->winning_bidder == tbl->dealer ) {

			if ( tmp <= 2 ) {
				tmp = 2;
				tbl->high_bid = 2;
				(*tbl->winning_bidder)->bid = 2;
			}

			tbl->high_bid = tmp;
			tbl->bid = tmp;

		}
		else {

			tbl->high_bid = tmp;
			tbl->bid = tmp;
		}
		
		return true;

	}
	else if ( tbl->winning_bidder == tbl->dealer && tbl->high_bid < 2 ) {
		tbl->high_bid = 2;			
		return true;
	}



	if ( tbl->current_bidder == tbl->dealer && tbl->high_bid < 2 ) {

		tbl->winning_bidder = tbl->dealer;
		tbl->lead = (*tbl->winning_bidder);
		(*tbl->winning_bidder)->bid = 2;

		return true;
	}


	// this was not a winning bid
	return false;

}

void GameManager::NewGame() {

	Reset();

	createPlayers();
	assignTeams();
	
	tbl->Reset();

	Status(SetGameInfo);
}


void GameManager::NewTrick() {
	NewTrick(true);
}


void GameManager::NewTrick(Boolean move_deal) {
	trk->CleanUp();
	cards_played = 0;
	
	tbl->Reset(move_deal);
}

Boolean GameManager::IsTrickOver() {

	if ( cards_played == numPlayers ) {
		return true;
	}

	return false;

}

Boolean GameManager::IsHandOver() {

	if ( trick_rounds == CARDS_IN_HAND ) {
		return true;
	} // if ( rounds == 6 )

	return false;

}

void GameManager::HandleEndOfTrick() {

	tbl->lead = trk->Winner();
	current = getPlayerIter( tbl->lead->playerIndex );

	cards_played = 0;
	trick_rounds++;


	for (CArray <Player*>::iterator i = players.BeginIterator(); i != players.EndIterator(); i++ ) {
	
		if ( (*i)->played_card != NULL ) {
			(*i)->played_card = NULL;
		}
	}


	trk->book->DeleteAll();
	trk->current_winner = NULL;
	trk->lead = NULL;

	Status(ReadyToPlay);
}

void GameManager::HandleEndOfHand() {

	Status(HandOver);

	trick_rounds = 0;
	trk->PostHandCleanUp();
	tbl->Reset();
	
	Int16 cnt = 0;

	for (cnt = 0; cnt < numPlayers; cnt++  )
	{
		players[cnt]->post_hand_cleanup();
	}



}


Boolean GameManager::GetNextPlay(Trick *trk ) {

	Boolean result = (*current)->PickCard(trk);
	
	if ( result == true ) {


		char hand[22];
		hand[0] = 0;

		for (int cnt = 0; cnt < (*current)->hand.GetCount(); cnt++ ) {

			char tmpstr[4];
			tmpstr[0] = (*current)->hand[cnt]->FaceChar();
			tmpstr[1] = (*current)->hand[cnt]->SuitChar();
			tmpstr[2] = ' ';
			tmpstr[3] = 0;

			StrCat(hand, tmpstr);
		}

		HostTraceOutputTL(sysErrorClass, 
			"%d: %s -> %c%c ",
			(*current)->playerIndex,
			hand,
			(*current)->PlayedCard()->FaceChar(),
			(*current)->PlayedCard()->SuitChar() );

		if ( cards_played + 1 == numPlayers ) {
			HostTraceOutputTL(sysErrorClass, "*********************");

		}
	}

	return result;
	
}


Boolean GameManager::NextPlayedCard(Player *p, Card *c) {

	if ( c != NULL ) {

		cards_played++;

		//
		// analyze the current standings for this hand
		//
		trk->RecordPlayedCard( p, c );
		
		current = getNextPlayerIter(current);

		// add the card to the vector of played cards
		// so that our AI can do some figuring
		tbl->played_cards.Add(c);

		return true;
	}
	
	return false;
}

GameStatus GameManager::CheckGameCondition() {

	return game_status;

}

void GameManager::Status(GameStatus x) {
	game_status = x;
}

GameStatus GameManager::Status() {
	return game_status;
}


void GameManager::DealHands() {

	dealCards();

	trick_rounds = 0;
	cards_played = 0;

	Status(GetHandBids);
}


/* 
	if neither team has won, return true 
*/
Boolean GameManager::NoWinner() {

	if (
		// don't allow ties!!
		( ! win_on_bid && tied() ) ||

		// can't win if you have to win on a bid
		( win_on_bid && tbl->last_bid_winner == -1 ) ) {

		return true;

	}
	

	//
	// if you can win on smudge and someone got it, game over
	//	
	if ( win_on_bid && win_on_smudge && 
			tbl->last_bid_winner != -1 && 
			tbl->won_smudge == true ) {
		return false;
	}

	if ( CutThroat() &&	scores[2] >= winning_score &&
			( ! win_on_bid || tbl->last_bid_winner == 2 )
			) { 
		return false;
	}

	if (
		( scores[1] >= winning_score ) &&
		( ! win_on_bid || tbl->last_bid_winner == 1 || tbl->last_bid_winner == 3 )
		) { 
		return false;
	}

	if (
		( scores[0] >= winning_score )  &&
		( ! win_on_bid || tbl->last_bid_winner == 0 || tbl->last_bid_winner == 2 )
		) {
		return false;
	}

	
	return true;

}

Player * GameManager::GetWinner() {

	//
	// if you must win on a bid,
	// the last bid winner will be the winner;
	//
	if ( win_on_bid && tbl->last_bid_winner != -1 ) {
		return players[tbl->last_bid_winner];
	}
	
	//
	// otherwise, just pick the higher score
	//
	if ( scores[2] != 0 ) {
		if ( scores[2] >= scores[1] && scores[2] >= scores[0] ) {
			return players[2];
		}
	}
	else if ( scores[0] >= scores[1] ) {
		return players[0];
	}

	return players[1];

}


Int16 GameManager::GetTeamPoints(char t) {

	for (CArray <Player*>::iterator  i = players.BeginIterator(); i != players.EndIterator(); i++ ) {

		Player *p = (*i);
		
		if ( p->team == t && p->partner != NULL ) {
			return p->getPoints() + p->partner->getPoints();
		}
		else if ( p->team == t ) {
			return p->getPoints();
		}

	}

	return 0;

}