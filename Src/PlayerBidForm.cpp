#include "Common.h"
#include "PlayerBidForm.h"
#include "PitchApp.h"

#include "GameManager.h"

extern GameManager *gManager;

// Form open handler
Boolean CPlayerBidForm::OnOpen(EventPtr pEvent, Boolean& bHandled) {

	current_high.Attach(this, PlayerBidCurrentHighField );
	current_dealer.Attach(this, PlayerBidDealerInfoField );

	CString foo = "Current dealer is ";
	foo = foo + dealer->getName();

	CString foo2 = "Current bid is ";
	if ( high_bid > 2 ) {
		char high_bid_str[2];
		StrPrintF(high_bid_str, "%d", high_bid);
		foo2 = foo2 + high_bid_str;
	}
	else {
		foo2 = "No bid yet";	
	}

	current_dealer.Replace( foo );
	current_high.Replace( foo2 );

	player_hand.Attach(this, PlayerBidPlayerHandGadget );
//	player_hand.CurrentTrick(gManager->trk);
	player_hand.CurrentPlayer(gManager->players[3]);
	player_hand.Render(true);

	int tmp = 0;

	if ( dealer->playerIndex != 3 || ! gManager->dealer_take_bid ) {
		tmp = high_bid;
	}
	else {
		tmp = high_bid - 1;
	}
	
	FormPtr frmP = FrmGetActiveForm();

	if ( dealer->playerIndex != 3 && high_bid < 2 ) {
		CtlSetEnabled((ControlType *)FrmGetObjectPtr( frmP, FrmGetObjectIndex( frmP, PlayerBid4PushButton )), false);	
		CtlSetLabel ((ControlType *)FrmGetObjectPtr( frmP, FrmGetObjectIndex( frmP, PlayerBid4PushButton )), "-4-");
		CtlSetEnabled((ControlType *)FrmGetObjectPtr( frmP, FrmGetObjectIndex( frmP, PlayerBid3PushButton )), false);
		CtlSetLabel ((ControlType *)FrmGetObjectPtr( frmP, FrmGetObjectIndex( frmP, PlayerBid3PushButton )), "-3-");
		CtlSetEnabled((ControlType *)FrmGetObjectPtr( frmP, FrmGetObjectIndex( frmP, PlayerBidPassPushButton )), false);
		CtlSetLabel ((ControlType *)FrmGetObjectPtr( frmP, FrmGetObjectIndex( frmP, PlayerBidPassPushButton )), "-Pass-");
	}
	else {
		switch (tmp) {
			case 5:
				CtlSetEnabled((ControlType *)FrmGetObjectPtr( frmP, FrmGetObjectIndex( frmP, PlayerBidSmudgePushButton )), false);	
				CtlSetLabel ((ControlType *)FrmGetObjectPtr( frmP, FrmGetObjectIndex( frmP, PlayerBidSmudgePushButton )), "-S-");
			case 4:
				CtlSetEnabled((ControlType *)FrmGetObjectPtr( frmP, FrmGetObjectIndex( frmP, PlayerBid4PushButton )), false);	
				CtlSetLabel ((ControlType *)FrmGetObjectPtr( frmP, FrmGetObjectIndex( frmP, PlayerBid4PushButton )), "-4-");
			case 3:
				CtlSetEnabled((ControlType *)FrmGetObjectPtr( frmP, FrmGetObjectIndex( frmP, PlayerBid3PushButton )), false);
				CtlSetLabel ((ControlType *)FrmGetObjectPtr( frmP, FrmGetObjectIndex( frmP, PlayerBid3PushButton )), "-3-");
			case 2:
				CtlSetEnabled((ControlType *)FrmGetObjectPtr( frmP, FrmGetObjectIndex( frmP, PlayerBid2PushButton )), false);
				CtlSetLabel ((ControlType *)FrmGetObjectPtr( frmP, FrmGetObjectIndex( frmP, PlayerBid2PushButton )), "-2-");
		}
	}


	bHandled = false;
	return true;
}



Boolean CPlayerBidForm::OnOK(EventPtr pEvent, Boolean& bHandled) {

	bidval = 0;

	FormPtr frmP = FrmGetActiveForm();

	if ( CtlGetValue((ControlType *)FrmGetObjectPtr( frmP, FrmGetObjectIndex( frmP, PlayerBid2PushButton ) )) ) {
		bidval = 2;
	}
	else if ( CtlGetValue((ControlType *)FrmGetObjectPtr( frmP, FrmGetObjectIndex( frmP, PlayerBid3PushButton ) ) ) ){
		bidval = 3;
	}
	else if ( CtlGetValue((ControlType *)FrmGetObjectPtr( frmP, FrmGetObjectIndex( frmP, PlayerBid4PushButton ) ) ) ) {
		bidval = 4;
	}
	else if ( CtlGetValue((ControlType *)FrmGetObjectPtr( frmP, FrmGetObjectIndex( frmP, PlayerBidSmudgePushButton ) ) ) ) {
		bidval = 5;
	}
	else {
		//PlayerBidPassPushButton
		bidval = 0;
	}

	CloseForm(true);
	return true;
}



void CPlayerBidForm::CurrentHigh(int x) {
	high_bid = x;
	
//	char high_bid_str[2];
//	StrPrintF(high_bid_str, "%d", high_bid);
//	current_high.Replace(high_bid_str);
}


void CPlayerBidForm::CurrentDealer(Player *x) {
	dealer = x;
//	current_dealer.Replace( x->getName() );
}

