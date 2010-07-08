#include "Common.h"
#include "GameManager.h"
#include "PlayedCardsHistory.h"
#include "PitchApp.h"

extern GameManager *gManager;

Boolean CPlayedCardsHistoryDialog::OnOK(EventPtr pEvent, Boolean& bHandled) {
	CloseForm();
	return true;
}

Boolean CPlayedCardsHistoryDialog::OnClose(EventPtr pEvent, Boolean& bHandled) {

	grid.Detach();

	bHandled = false;
	return true;
}


Boolean CPlayedCardsHistoryDialog::OnOpenPost(EventPtr pEvent, Boolean& bHandled) {

	grid.Attach( CardTable, CardTableScrollBar );
	grid.SetGridMode(CGrid::GM_FULLROWSELECT);
    grid.SetRowCount(6);
    grid.SetRowHeight(40);

	return true;
}
