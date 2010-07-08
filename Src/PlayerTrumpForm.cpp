#include "Common.h"
#include "PlayerTrumpForm.h"
#include "PitchApp.h"

#include "GameManager.h"

extern GameManager *gManager;


// Form open handler
Boolean CPlayerTrumpForm::OnOpen(EventPtr pEvent, Boolean& bHandled) {

	FormPtr frmP = FrmGetActiveForm();

	if ( gManager->no_trump_first_trick == false ) {
		CtlHideControl((ControlType *)FrmGetObjectPtr( frmP, FrmGetObjectIndex( frmP, PlayerTrumpNoTrumpFirstTrickPCheckbox ) ) );
	}

	//
	// display the user's hand here
	//
	player_hand.Attach(this, PlayerTrumpPlayerHandGadget );
	player_hand.CurrentPlayer(gManager->players[gManager->humanIndex]);
	player_hand.Render(true);


	bHandled = false;
	return true;
}


Boolean CPlayerTrumpForm::OnClose(EventPtr pEvent, Boolean& bHandled) {

	//
	// display the user's hand here
	//
	player_hand.Detach();

	bHandled = false;
	return true;
}


Boolean CPlayerTrumpForm::OnChooseTrump(EventPtr pEvent, Boolean& bHandled) {

	UInt32 hsStatusVersion;
	
	if (FtrGet (hsFtrCreator, hsFtrIDNavigationSupported, &hsStatusVersion) == 0) {
		FrmGlueNavObjectTakeFocus(FrmGetActiveForm(), PlayerTrumpOKButton );
	}
	
	bHandled = false;
	return false;

}

Boolean CPlayerTrumpForm::OnOK(EventPtr pEvent, Boolean& bHandled) {

	FormPtr frmP = FrmGetActiveForm();

	Card::suit_t trump = (Card::suit_t)-1;
	Boolean no_trump_first_trick;

	if ( CtlGetValue( (ControlType *)FrmGetObjectPtr( frmP, FrmGetObjectIndex( frmP, PlayerTrumpHeartsPushButton ) ) ) ) {
		trump = Card::heart;
	}
	else if ( CtlGetValue( (ControlType *)FrmGetObjectPtr( frmP, FrmGetObjectIndex( frmP, PlayerTrumpDiamondsPushButton ) ) ) ) {
		trump = Card::diamond;
	}
	else if ( CtlGetValue( (ControlType *)FrmGetObjectPtr( frmP, FrmGetObjectIndex( frmP, PlayerTrumpClubsPushButton ) ) ) ) {
		trump = Card::club;
	}
	else if ( CtlGetValue( (ControlType *)FrmGetObjectPtr( frmP, FrmGetObjectIndex( frmP, PlayerTrumpSpadesPushButton ) ) ) ) {
		trump = Card::spade;
	}
	else {
		return true;
	}


	if ( CtlGetValue( (ControlType *)FrmGetObjectPtr( frmP, FrmGetObjectIndex( frmP, PlayerTrumpNoTrumpFirstTrickPCheckbox ) ) ) ) {
		no_trump_first_trick = true;
	}
	else {
		no_trump_first_trick = false;
	}

	gManager->players[gManager->humanIndex]->bestSuit = trump;
	gManager->players[gManager->humanIndex]->no_trump_first_trick = no_trump_first_trick;

	CloseForm(true);
	return true;
}
