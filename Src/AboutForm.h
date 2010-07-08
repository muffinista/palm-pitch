// MainForm.h
//
// This file declares a class for the main form of
// your application.

#ifndef ABOUTFORM_H_
#define ABOUTFORM_H_

class CAboutDialog : public CModalForm
{
public:
	// constructor
	CAboutDialog() :
		CModalForm(AboutForm)
		{ }

	// Event handlers
	Boolean OnOpenPost(EventPtr pEvent, Boolean& bHandled);
	Boolean OnOK(EventType* pEvent, Boolean& bHandled);

	// Event map
	BEGIN_EVENT_MAP(CModalForm)
		EVENT_MAP_COMMAND_ENTRY(AboutOKButton, OnOK)
 	END_EVENT_MAP()

	// Post-Event map
	BEGIN_POST_EVENT_MAP(CModalForm)
		POST_EVENT_MAP_ENTRY(frmOpenEvent, OnOpenPost)
 	END_POST_EVENT_MAP()
 	
private:
	CField m_versionField; 	
};

#endif // ABOUTFORM_H_
