#ifndef COMMON_H_
#define COMMON_H_

#include <POL.h>
#include <68K/Hs.h>

using namespace POL;

#include "Pitch_Rsc.h"

#define CARDS_IN_HAND 6

typedef enum {
	PreGame = 0,
	SetGameInfo,
	GetGameInfo,
	NewGame,
	ResetGame,
	DealNewHands,
	GetHandBids,
	SetHandTrump,
	ShowBiddingResults,
	ReadyToPlay,
	RedrawTable,
	PlayACard,
	TrickOver,
	HandOver,
	DisplayHandResults,
	GameOver
} GameStatus;

#endif // COMMON_H_
