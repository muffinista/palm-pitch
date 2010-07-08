#ifndef MANAGER_H
#define MANAGER_H

#include "common.h"

#include "Deck.h"
#include "Player.h"
#include "GameTable.h"
#include "Trick.h"

class GameManager {

	private:
		void createTable();
		void setDealer();
		void assignTeams();
		void players_cleanUp();

		//
		// game data
		//
		GameStatus game_status;
		Int16 cards_played;
		
		Boolean cutthroat;

	public:

		GameManager();
		~GameManager();

		void Reset();
		void Load();
		void Save();

		void ShortDelay();
		void LongDelay();

		Boolean CutThroat();
		void CutThroat(Boolean x);

		UInt16 humanIndex;

		//
		// game data
		//
		Int16 numPlayers;

		CArray<Player *> players;
		Trick *trk;
		GameTable *tbl;
		Deck *theDeck;

		CArray<Player *>::iterator human;
		CArray<Player *>::iterator current;

		Int16 scores[3];

		Boolean first_hand;
		Boolean first_game;

		Int16 trick_rounds;


		//
		// prefs
		//
		UInt8 winning_score;
		Int16 play_delay_ticks;
		Boolean no_trump_first_trick;
		Boolean dealer_take_bid;
		Boolean win_on_bid;
		Boolean win_on_smudge;
		Int16 games_played;

		Int16 games_won[3];
		UInt8 ai_level;

		CString player_names[4];

		void FinalizeBidding();
		void BidSummary();	

		void ResetBidding();
		Boolean GetNextBid(Trick *trk, Boolean bid_already_set );

		void createPlayers();
		void playCards(Trick *);

		GameStatus CheckGameCondition();

		void NewTrick();
		void NewTrick(Boolean move_deal);

		Boolean IsTrickOver();
		Boolean IsHandOver();
		void HandleEndOfTrick();
		void HandleEndOfHand();

		void dealCards();

		Boolean GetNextPlay(Trick *trk );
		Boolean NextPlayedCard(Player *p, Card *c);

		Boolean playACard( Trick * );

		Player* getPlayer(Int16 index);
//		Player* getPlayer(CArray<Player *>::iterator i);
		CArray<Player*>::iterator getPlayerIter(Int16 index);

		Player* getNextPlayer(Player *p);
		Player* getPrevPlayer(Player *p);
		Player* getNextPlayer(CArray <Player*>::iterator);

		CArray<Player*>::iterator getNextPlayerIter(CArray<Player *>::iterator i);

		void refresh_display();
		void update_status();
		void update_score();

//		Boolean noWinner();
		Boolean tied();

		void clear();
		void load_prefs(Boolean load_game_data);
		void save_prefs();
		
		void Status(GameStatus);
		GameStatus Status();

		void DealHands();

		Boolean NoWinner();
		Player * GetWinner();
	
		void NewGame();
		
		Int16 GetTeamPoints(char team);

};
#endif
