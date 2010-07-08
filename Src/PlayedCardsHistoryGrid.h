// Declaration of Address grid class
#ifndef __AddressGrid_H__
#define __AddressGrid_H__

// Address grid class
class CPlayedCardsHistoryGrid : public CGrid {

public:
	// Returns pointer to item's text or NULL value if no text should be shown
//	virtual const Char* GetItemText(Int16 wAbsoluteRow, Int16 wColumn);

	void DrawItem(Int16 wAbsoluteRow, Int16 wColumn, const RectangleType &  rcBounds );

protected:

};

#endif
