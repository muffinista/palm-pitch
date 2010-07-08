#include "Common.h"
#include "AboutForm.h"
#include "PitchApp.h"

Boolean CAboutDialog::OnOK(EventPtr pEvent, Boolean& bHandled) {
	CloseForm();
	return true;
}

Boolean CAboutDialog::OnOpenPost(EventPtr pEvent, Boolean& bHandled) {

	m_versionField.Attach(this, PitchVersionField);

	// set version display dynamically from 'tver' resource
	CResource resVersion(verRsc, appVersionAlternateID);
	CString version("Version ");
	version += (const char *)resVersion.Lock();
	m_versionField.Replace(version);

	return true;
}
