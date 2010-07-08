/**
 * \file Common/Libraries/TonesLibrary/Prv/TonesLibTypes.h
 *
 * <Brief description here>
 *
 * <Full description here>
 *
 * \license
 *
 *    Copyright (c) 2002 Handspring Inc., All Rights Reserved
 *
 * \author Arun Mathias
 *
 *****************************************************************************/

#ifndef TONES_LIB_TYPES__H__
#define TONES_LIB_TYPES__H__

#define      tonesLibName           "Tones Library"

#define      tonesLibCreator        hsFileCTonesLib

#define      tonesLibType           sysFileTLibrary 

#define      kMaxTonesNameSize       32

#define		  tonesLibPlayForever	  0xFFFF

#define      tonesLibErrClass        0x9000

#define      tonesLibErrCreateDBFailed  tonesLibErrClass | 1

#define      tonesLibErrNoMemory        tonesLibErrClass | 2

#define      tonesLibErrNoTone          tonesLibErrClass | 3

#define      tonesLibErrDBNotFound      tonesLibErrClass | 4

#define      tonesLibErrDBWriteFailed   tonesLibErrClass | 5

#define      tonesLibErrUserCancel      tonesLibErrClass | 6

#define      tonesLibErrBadParams       tonesLibErrClass  | 7

#define      tonesLibErrUnknown         tonesLibErrClass | 8

#define      tonesLibErrNotAllowed       tonesLibErrClass | 9

#define      tonesLibErrAlreadyPlaying       tonesLibErrClass | 10

#define      CompareToneIdentifiers(tone1, tone2) \
             (tone1.id == tone2.id && tone1.toneType == tone2.toneType)


#define      CopyToneIdentifier(destP, src) \
			 destP->id = src.id; \
             destP->toneType = src.toneType


#define      CopyMIDIToneIdentifier(destP, src) \
			 destP->id = src; \
             destP->toneType = toneTypeMIDI
			 
enum _ToneType {
	toneTypeMIDI,		  /**< Record in MIDI Ring Tones DB */
	toneTypeWAV,		  /**< WAV in a SndFileStream */
	toneTypeAMR,		  /**< AMR in a SndFIleStream */
	toneTypeSystemSound,  /**< unused */
	toneTypeQCELP		  /**< QCELP in a SndFileStream */
};

typedef UInt16 ToneType;

enum _SoundPrefType
{
  soundPrefTypePhone,
  soundPrefTypeEmail,
  soundPrefTypeCalendar, 
  soundPrefTypeIM,
  soundPrefTypeMMS,
  soundPrefTypeSMS
};

typedef UInt16  SoundPrefType;


enum _ToneVolume
{
  toneVolumeOff,
  toneVolume1,
  toneVolume2,
  toneVolume3,
  toneVolume4,
  toneVolume5,
  toneVolume6,
  toneVolume7
};

typedef UInt16  ToneVolume;

enum _TonePlayNumberTimes
{
  tonePlayOnce,
  tonePlayTwice,
  tonePlay3Times,
  tonePlay5Times,
  tonePlay10Times,
  tonePlay100Times 
};

typedef UInt8 TonePlayNumberTimes;

enum _ToneRepeatInterval
{
  toneRepeatEveryMinute,
  toneRepeatEvery5Minutes,
  toneRepeatEvery10Minutes,
  toneRepeatEvery30Minutes
};

typedef UInt8 ToneRepeatInterval;

enum _ToneTimeUnit
{
  toneTimeUnitMinutes,
  toneTimeUnitHours,
  toneTimeUnitDays

};

typedef UInt8 ToneTimeUnit;

enum _ToneVibrateType
{
  toneVibrateNone,
  toneVibrateRing,
  toneVibrateAlert,
  toneVibrateMail,
  toneVibrateCalender,
  toneVibrateSMS,
  toneVibrateVoicemail

};

typedef UInt8 ToneVibrateType;


typedef struct {

	UInt32 id;
	ToneType toneType;
	

} ToneIdentifier;

/**
 * Item in a list of tones. 
 **/

typedef struct {

	Char   name [kMaxTonesNameSize];  /**< Name of the ring tone  */
	ToneIdentifier identifier;  /**< Unique ID for the ring tone  */
	Boolean protectedTone;   /**< Tone is protected and cannot be beamed/sent  */
	
} ToneItemType, * ToneItemPtr;

typedef struct {
	
	ToneIdentifier chatTone;
	ToneIdentifier messageTone;

} SoundPreferenceIM;

typedef struct {
	
	ToneIdentifier unknownCallerTone;
	ToneIdentifier knownCallerTone;
	ToneIdentifier roamingTone;
	ToneIdentifier  voicemailTone;
	Boolean serviceTone;


} SoundPreferencePhone;

typedef struct {

	ToneIdentifier alertTone;
	Boolean newMailAlert;

} SoundPreferenceEmail;

typedef struct {

	ToneIdentifier alarmTone;
	ToneIdentifier reminderTone;


	TonePlayNumberTimes playSoundTimes;
	TonePlayNumberTimes repeatAlarmTimes;

	ToneRepeatInterval repeatInterval;

	UInt16 presetTime;
	ToneTimeUnit presetTimeUnit;

    Boolean alarmPreset;	

} SoundPreferenceCalendar;

typedef struct {

	ToneIdentifier messageTone;

} SoundPreferenceSMS;

typedef struct {

	ToneIdentifier messageTone;

} SoundPreferenceMMS;


typedef struct {
	union _tonePrefs
	  {
		SoundPreferenceIM imSoundPrefs;
		SoundPreferencePhone phoneSoundPrefs;
		SoundPreferenceEmail emailSoundPrefs;
		SoundPreferenceCalendar calendarSoundPrefs;
		SoundPreferenceSMS  smsSoundPrefs;
		SoundPreferenceMMS  mmsSoundPrefs;
	  } tonePrefs;

	ToneVolume soundOnVolume;
	Boolean soundOnVibrate;

	Boolean soundOffVibrate;

} SoundPreference;


#define kTonesDialogFlagNonModal	  0x00000001	// Hide the Done button

/**
 * Trap id for the function that gets the tone list.
 **/
#define       tonesLibTrapGetToneList  sysLibTrapCustom 

/**
 * Trap id for the function that gets the list of tone ids
 **/
#define       tonesLibTrapGetToneIDs    sysLibTrapCustom+1

/**
 * Trap id for the function that gets the name of a tone
 **/
#define       tonesLibTrapGetToneName   sysLibTrapCustom+2

/**
 * Trap id for the function that plays a tone
 **/
#define       tonesLibTrapPlayTone      sysLibTrapCustom+3

/**
 * Trap id for the function to add a MIDI tone
 * Note: This used to be tonesLibTrapAddTone. Leaving this
 *		  trap number maintains binary compatability with existing
 *		  apps. Recompiling older source code will fail since
 *		  the new version of TonesLibAddTone takes toneType as
 *		  an additional parameter.
 **/
#define       tonesLibTrapAddMidiTone       sysLibTrapCustom+4

/**
 * Trap id for function to manage tones
 **/
#define       tonesLibTrapManageTones       sysLibTrapCustom+5

/**
 * Trap id for the function to delete a tone
 **/
#define       tonesLibTrapDeleteTone       sysLibTrapCustom+6

/**
 * Trap id for function to get sound preference
 **/
#define       tonesLibTrapGetSoundPrefs     sysLibTrapCustom+7

/**
 * Trap id for function to set sound preference
 **/
#define       tonesLibTrapSetSoundPrefs     sysLibTrapCustom+8

/**
 * Trap id for function to init tones DB
 **/
#define       tonesLibTrapInitTonesDB       sysLibTrapCustom+9

/**
 * Trap id for function to pick a tone to attach
 */
#define       tonesLibTrapPickTone          sysLibTrapCustom+10


#define       tonesLibTrapStopTone          sysLibTrapCustom+11

/**
 * Trap id for function to get the on volume of a sound type
 */
#define		  tonesLibTrapGetSoundOnVolume	sysLibTrapCustom+12

/**
 * Trap id for function to set the on volume of a sound type
 */
#define		  tonesLibTrapSetSoundOnVolume	sysLibTrapCustom+13

/**
 * Trap id for function to display the tones list
 **/
#define       tonesLibTrapDoDialog          sysLibTrapCustom+14

/**
 * Trap id for the function that gets the size of a tone
 **/
#define		  tonesLibTrapGetToneSize		sysLibTrapCustom+15

/**
 * Trap id for the function to begin adding a new tone
 **/
#define		  tonesLibTrapToneCreate		sysLibTrapCustom+16

/**
 * Trap id for the function to write data to a new tone
 **/
#define		  tonesLibTrapToneWrite			sysLibTrapCustom+17

/**
 * Trap id for the function to finish adding a new tone
 **/
#define		  tonesLibTrapToneClose			sysLibTrapCustom+18


#endif  // TONES_LIB_TYPES__H__

