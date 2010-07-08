#ifndef ANNOYFORM_H_
#define ANNOYFORM_H_

typedef struct {
	UInt32 install_time;
	char code[11];
} RegPreferenceType;


void InitProtection();
Boolean IsRegistered();
void SaveCode( const char *code );
UInt32 GetDaysSinceFirst();
Boolean load_reg_form();
Boolean CheckCode(const char *code);


class CAnnoyForm : public CForm {

public:

	// Event handlers
	Boolean OnOpen(EventPtr pEvent, Boolean& bHandled);
	Boolean OnClose(EventPtr pEvent, Boolean& bHandled);
	Boolean OnRegister(EventType* pEvent, Boolean& bHandled);
	Boolean OnContinue(EventType* pEvent, Boolean& bHandled);

	// Event map
	BEGIN_EVENT_MAP(CForm)
		EVENT_MAP_COMMAND_ENTRY(AnnoyContinueButton, OnContinue)
		EVENT_MAP_COMMAND_ENTRY(AnnoyRegisterButton, OnRegister)
		EVENT_MAP_ENTRY(frmCloseEvent, OnClose)
		EVENT_MAP_ENTRY(frmOpenEvent, OnOpen)
 	END_EVENT_MAP()

 	
private:

	CField m_pleaField;
	CField m_gamesField;

	MemHandle h;

};

#endif // ANNOYFORM_H_
