#include "Common.h"
#include "GameManager.h"
#include "WinningsForm.h"
#include "PitchApp.h"

extern GameManager *gManager;

void drawCards(CArray<Card*>, UInt16 gadget);

void drawCards(CArray<Card*> c, UInt16 gadget) {

	FormPtr frmP = FrmGetActiveForm();

	RectangleType  bounds;

	UInt16 new_x = 0;

	UInt16 gadgetIndex = FrmGetObjectIndex(frmP, gadget );

	FrmGetObjectBounds(frmP, gadgetIndex, &bounds);

	bounds.topLeft.x -= 1;
	bounds.extent.y += 1;

	WinEraseRectangle(&bounds, 0);

	bounds.topLeft.x += 1;
	bounds.extent.y -= 1;

	UInt8 cnt = 0;

	new_x = bounds.topLeft.x;
	Int16 y_pos = bounds.topLeft.y + 1;

	Int16 card_width = 19;
	Int16 card_height = 21;
	Int16 card_spacing = 8;

	for (cnt = 0; cnt < c.GetCount(); cnt++ ) {
	
		if ( new_x + card_width > bounds.topLeft.x + bounds.extent.x ) {
			new_x = bounds.topLeft.x;
			y_pos += 15;
		}

		c[cnt]->Draw(new_x, y_pos, card_width, card_height, false);

		new_x += card_spacing;
	}


}


Boolean CWinningsDialog::OnOK(EventPtr pEvent, Boolean& bHandled) {
	CloseForm();
	return true;
}

Boolean CWinningsDialog::OnOpenPost(EventPtr pEvent, Boolean& bHandled) {

	FormPtr frmP = FrmGetActiveForm();

	names[0].Attach(this, TeamANames);
	names[1].Attach(this, TeamBNames);
	names[2].Attach(this, TeamCNames);

	if ( gManager->CutThroat() ) {
		names[0].Replace( (const char *)gManager->players[0]->getName() );
		names[1].Replace( (const char *)gManager->players[1]->getName() );
		names[2].Replace( (const char *)gManager->players[2]->getName() );
	}
	else {

		CString team_a;
		CString team_b;

		team_a.Format("%s and %s", 
			(const char *)gManager->getPlayer(0)->getName(), 
			(const char *)gManager->getPlayer(2)->getName() );

		team_b.Format("%s and %s", 
			(const char *)gManager->getPlayer(1)->getName(), 
			(const char *)gManager->getPlayer(3)->getName() );

		names[0].Replace(team_a);
		names[2].Replace(team_b);
		
	}

	if ( gManager->CutThroat() ) {
		drawCards(gManager->trk->team_winnings[0], TeamAWinnings );
		drawCards(gManager->trk->team_winnings[1], TeamBWinnings );
		drawCards(gManager->trk->team_winnings[2], TeamCWinnings );
	}
	else {
		drawCards(gManager->trk->team_winnings[0], TeamAWinnings );
		drawCards(gManager->trk->team_winnings[1], TeamCWinnings );
	}


	return true;
}

Boolean CWinningsDialog::OnClose(EventPtr pEvent, Boolean& bHandled) {

	names[0].Detach();
	names[1].Detach();
	names[2].Detach();

	bHandled = false;
	return true;
}
