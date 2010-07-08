#include "Common.h"
#include "RegDialog.h"
#include "PitchApp.h"
#include "Protect.h"

Boolean load_reg_form() {

	if ( IsRegistered() ) {
		FrmCustomAlert(RegThanks, "", "", "");	
		return false;
	}


	CRegDialog frmPrefs;
	
	Boolean try_again = false;

	try_again = frmPrefs.DoModal();

	return try_again;

} // load_reg_form


CString CRegDialog::RegCode() {
	return tmpCode;
}

Boolean CRegDialog::OnOK(EventPtr pEvent, Boolean& bHandled) {

	if ( m_RegCode.GetTextPtr() ) {
		tmpCode = m_RegCode.GetTextPtr();
	}
	else {
		tmpCode = "";
	}

	SaveCode( (const char *)tmpCode );
		
	if ( IsRegistered() ) {
		FrmCustomAlert(RegThanks, "", "", "");
		CloseForm(false);
	}
	else {
		FrmCustomAlert(RegProblem, "", "", "");
	}

	return true;
}

Boolean CRegDialog::OnCancel(EventPtr pEvent, Boolean& bHandled) {
	CloseForm(false);
	return true;
}

Boolean CRegDialog::OnOpenPost(EventPtr pEvent, Boolean& bHandled) {
	m_RegCode.Attach(this, SerialNumber);
	return true;
}


Boolean CRegDialog::OnClose(EventPtr pEvent, Boolean& bHandled) {
	m_RegCode.Detach();
	
	bHandled = false;
	return false;
}