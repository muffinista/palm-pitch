/**
 * \file Common/Libraries/HsSoundLib/HsSoundLibCommon.h
 * HsSoundLib common constants, types, structs, etc
 *
 * 
 *
 * \license
 *
 *    Copyright (c) 2003 Handspring Inc., All Rights Reserved
 *
 * \author Frankie Sierra
 *
 * $Id:$
 *
 *****************************************************************************/
#ifndef __HSSOUNDLIB_COMMON__H__
#define __HSSOUNDLIB_COMMON__H__

#include <PalmTypes.h>
#include <Common/System/HsErrorClasses.h>		/* For hsSoundLibErrorClass */

#define hsSndLibVersion				0x01000000	/* current HsSoundLib version */

#define hsSoundLibCreatorID			hsFileSoundLib
#define hsSoundLibTypeID			sysFileTLibrary
#define hsSoundLibName				"HsSoundLib"


// Sound library event notifications
#define hsSndNotify					hsFileSoundLib /* HsSoundLib broadcaster's ID */
#define hsSndNotifyUnplugged		'hOff' /* notification of headset jack unplugged event */
#define hsSndNotifyHeadset			'hSet' /* a headset with mic has just been detected */
#define hsSndNotifyHeadphones		'hPho' /* a stereo headphones has just been detected */
#define hsSndNotifyAnswerButton		'hAns' /* while a headset was connected, the answer-button event was detected */


// Sound library error codes
#define hsSndErrBase				hsSoundLibErrorClass
#define HS_SND_ERR(x)				((Err)((x) + hsSndErrBase))
#define hsSndErr_Failed				(HS_SND_ERR(1))  /* The operation or request failed, there is no additional information */
#define hsSndErr_NotSupported		(HS_SND_ERR(2))  /* Attempt to use functionality that is documented, but not supported in this version */
#define hsSndErr_InvalidPort		(HS_SND_ERR(3))  /* An invalid port was passed to a function, operation failed */
#define hsSndErr_PortCannotMute		(HS_SND_ERR(4))  /* Unable to change mute state on a port that do Not have mute capabilities */
#define hsSndErr_PortCannotVolume	(HS_SND_ERR(5))  /* Unable to change volume gains on a port that do Not have volume capabilities */
#define hsSndErr_PortCannotBoost	(HS_SND_ERR(6))  /* Unable to change boost state on a port that do Not have boost capabilities */
#define hsSndErr_PortCannotPan		(HS_SND_ERR(7))  /* Unable to change pan settings on a port that do Not have panning capabilities */
#define hsSndErr_InvalidSwitch		(HS_SND_ERR(8))  /* An invalid switch was passed to a function, operation failed */
#define hsSndErr_UnknownSndParam	(HS_SND_ERR(9))  /* An unknown HsSndParam selector passed to a function call */
#define hsSndErr_UnknownPortClass	(HS_SND_ERR(10)) /* An unknown HsSndPortClass value was passed to a function call */
#define hsSndErr_PortIDNotInClass	(HS_SND_ERR(11)) /* The portID/portClass combination is Not supported */
#define hsSndErr_LastPublicError	(HS_SND_ERR(63)) /* Just a marker for last public library error code, private sound error codes start at 64 */

// Additional system sounds for PalmOS SndPlaySystemSound (patched by Handspring to support these below)
enum hsSndSysBeepTag
{
	hsSndCardInsert = 64,
	hsSndCardRemove,
	hsSndSyncStart,
	hsSndSyncStop,
	hsSndChargerAttach,
	hsSndChargerDetach,
	hsSndRadioOn,
	hsSndRadioOff,
	hsSndBatFull,
	hsSndBatLow,
	hsSndBatShutdown,
	hsSndDeepWake,
	hsSndDeepSleep,
	hsSndRadioInServiceArea,
	hsSndRadioOutServiceArea

};
typedef UInt8 hsSndSysBeepType;


#define hsSndMode_Current				((HsSndMode) 0x0000)
#define hsSndMode_Receiver				((HsSndMode) 0x0001)
#define hsSndMode_Speakerphone			((HsSndMode) 0x0002)
#define hsSndMode_SpeakerHost			((HsSndMode) 0x0003) /* mode when radio is off and speaker used exclusively by system and third party audio */
#define hsSndMode_Headset				((HsSndMode) 0x0004)
#define hsSndMode_Headphones			((HsSndMode) 0x0005)
#define hsSndMode_HeadphonesHost		((HsSndMode) 0x0006) /* mode when radio is off and headphones used exclusively by system and third party audio */
#define hsSndMode_CarKit				((HsSndMode) 0x0007)
#define hsSndMode_Reserved				((HsSndMode) 0x0008)

typedef Int16 HsSndMode;


// Use these for toneType parameter when calling HsSndTonePlay
#define hsSndToneType_Square			0

// Use this for SndBayID
#define hsSndBayID_AC97					0x01000000 /* we currently support an AC97 compatible chip as the analog sound patch bay on Treo */

// Utility macro to associate hsSndBayID_AC97 ID to other elements
#define HS_AC97(n)						((n) | hsSndBayID_AC97) /* utility to associate the SndBayID with other elements ID */

// Use these for HsSndSwitchID
#define hsSndSwitchID_InRadioSpkr		HS_AC97(0x00010000) /* controls the destination port for data coming from the Radio */
#define hsSndSwitchID_OutRadioMic		HS_AC97(0x00020000) /* controls the source microphone to connect to the Radio */
#define hsSndSwitchID_InMic				HS_AC97(0x00030000) /* test control for Mfg to directly connect Mic input into any destination speaker */
#define hsSndSwitchID_InHostPlay		HS_AC97(0x00040000) /* controls to which speaker to direct PalmOS audio */
#define hsSndSwitchID_OutHostRec		HS_AC97(0x00050000) /* controls from which port are we going to digitize to send to PalmOS for recording */

// Use these for HsSndPortID
#define hsSndPortID_Off					0x00000000 /* special meta port ID used to turn off a sound switch */
#define hsSndPortID_Current				HS_AC97(0x00000000) /* special meta port ID used to specify currently active user port */
#define hsSndPortID_OutReceiver			HS_AC97(0x00000001) /* this is the speaker the user will put to his ear when holding Treo */
#define hsSndPortID_OutSpeaker			HS_AC97(0x00000002) /* this is the back speaker for system audio and speakerphone functions */
#define hsSndPortID_OutHeadset			HS_AC97(0x00000003) /* represents audio output to mono headset (right channel output), left can be used as input */
#define hsSndPortID_OutHeadphones		HS_AC97(0x00000004) /* configures the headset port for full left and right stereo output, no inputs */
#define hsSndPortID_OutSpeakerAuto		HS_AC97(0x00000005) /* automatic port, according to headset insertion. Use with hsSndSwitchID_InRadioSpkr */
#define hsSndPortID_InLineRec			HS_AC97(0x00000006) /* use to configure headset jack as input, precluding headset use (special port for test purposes) */
#define hsSndPortID_InBaseMic			HS_AC97(0x00000007) /* this is the microphone at the base of the Treo body */
#define hsSndPortID_InHeadsetMic		HS_AC97(0x00000008) /* this is the microphone on a mono headset (comes from left channel as input) */
#define hsSndPortID_InMicAuto			HS_AC97(0x00000009) /* automatic port, according to headset insertion. Use with hsSndSwitchID_OutRadioMic */
#define hsSndPortID_OutRadioMic			HS_AC97(0x0000000A) /* this output is connected to the Radio microphone input */
#define hsSndPortID_InRadioSpkr			HS_AC97(0x0000000B) /* this input comes from the Radio speaker output */
#define hsSndPortID_OutHostRec			HS_AC97(0x0000000C) /* this output goes to the Host digitized recording input */
#define hsSndPortID_InHostPlay			HS_AC97(0x0000000D) /* this input from the Host is converted to analog for output to speakers */
#define hsSndPortID_LastPort			HS_AC97(0x0000000D) /* keep this updated at the end, it is needed elsewhere (same ID as last defined port in sequence) */


// Use these when passing a parameter of type HsSndPortClass in function call HsSndSwitchGetPort
#define hsSndPortClass_Virtual			((UInt16) 0) /* Symbolic port definition, use for portID save/restore operations (applies to any port) */
#define hsSndPortClass_Real				((UInt16) 1) /* Current physical port, use for changing port parameters (apply only to actual ports, Not "auto" ports) */
#define hsSndPortClass_BaseDefault		((UInt16) 2) /* Default port to use, when restoring a Built-In port (eg: User unplugged headset for an "auto" port) */

// Use these when passing a parameter of type HsSndParam
#define hsSndParam_Volume				((UInt16) 1) /* use to change the volume of a port */
#define hsSndParam_Mute					((UInt16) 2) /* use to change the mute state of a port */
#define hsSndParam_Boost				((UInt16) 3) /* use to change the boost state of a port */
#define hsSndParam_Pan					((UInt16) 4) /* use to change the panning value of a port */

// Use these for enabling or disabling a hsSndParam_Mute parameter
#define hsSndMute_Enable				1	/* use this to activate mute on a port */
#define hsSndMute_Disable				0	/* use this to disable mute on a port */

// Use these for enabling or disabling a hsSndParam_Boost parameter
#define hsSndBoost_Enable				1	/* use this to activate boost on a port */
#define hsSndBoost_Disable				0	/* use this to disable boost on a port */

// Use these as special hsSndParam_Pan parameters, otherwise use actual Pan value
#define hsSndPan_Middle					((Int16) 0x0000) /* pan at midpoint between left and right */
#define hsSndPan_Right					((Int16) 0x7FFF) /* pan all the way to the right */
#define hsSndPan_Left					((Int16) 0x8000) /* pan all the way to the left  */

// Use these for the "flags" variable in HsSndPortInfo structure
#define hsSndPortFlags_Enabled			0x00000001	/* indicates the port is enabled and in use */
#define hsSndPortFlags_Disabled			0x00000000	/* indicates the port is disabled */
#define hsSndPortFlags_EnableMask		0x00000001

#define hsSndPortFlags_MuteOn			0x00000002	/* indicates that volume is muted */
#define hsSndPortFlags_MuteOff			0x00000000	/* indicates that volume is as specified (Not muted) */
#define hsSndPortFlags_MuteMask			0x00000002

#define hsSndPortFlags_TypeDigital		0x00000004	/* sound data through port is digital */
#define hsSndPortFlags_TypeAnalog		0x00000000	/* sound data through port is analog */
#define hsSndPortFlags_TypeMask			0x00000004

#define hsSndPortFlags_BoostOn			0x00000008	/* boost control on port is active */
#define hsSndPortFlags_BoostOff			0x00000000	/* boost control on port is inactive */
#define hsSndPortFlags_BoostMask		0x00000008

#define hsSndPortFlags_CanInputOnly		0x00000000	/* set if port is for sound input exclusively */
#define hsSndPortFlags_CanOutputOnly	0x00000010	/* set if port is for sound output exclusively */
#define hsSndPortFlags_CanIOSelect		0x00000020	/* set if port can switch between being input or being output */
#define hsSndPortFlags_CanIOBothways	0x00000030	/* set if input and output can be selected simultaneously */
#define hsSndPortFlags_CanIOMask		0x00000030

#define hsSndPortFlags_InputOn			0x00000040	/* indicates if port as input is enabled */
#define hsSndPortFlags_InputOff			0x00000000	/* indicates if port as input is disabled */
#define hsSndPortFlags_InputMask		0x00000040

#define hsSndPortFlags_OutputOn			0x00000080	/* indicates if port as output is enabled */
#define hsSndPortFlags_OutputOff		0x00000000	/* indicates if port as output is disabled */
#define hsSndPortFlags_OutputMask		0x00000080

#define hsSndPortFlags_CanMute_Yes		0x00000100	/* indicates that port has mute control available */
#define hsSndPortFlags_CanMute_No		0x00000000	/* indicates that port has No mute control */
#define hsSndPortFlags_CanMuteMask		0x00000100

#define hsSndPortFlags_CanBoost_Yes		0x00000200	/* indicates that port has boost control available */
#define hsSndPortFlags_CanBoost_No		0x00000000	/* indicates that port has No boost control */
#define hsSndPortFlags_CanBoostMask		0x00000200

#define hsSndPortFlags_CanPan_Yes		0x00000400	/* indicates that port has pan control available */
#define hsSndPortFlags_CanPan_No		0x00000000	/* indicates that port has No pan control */
#define hsSndPortFlags_CanPanMask		0x00000400

#define hsSndPortFlags_CanVol_Yes		0x00000800	/* indicates that port has volume control available */
#define hsSndPortFlags_CanVol_No		0x00000000	/* indicates that port has No volume control */
#define hsSndPortFlags_CanVolMask		0x00000800

// Type definitions for elemental units of the API
typedef UInt32 HsSndPortID;
typedef UInt32 HsSndSwitchID;

// Type used as parameter to HsSndPortSetParam function call
typedef UInt16 HsSndParam;

// Type used as parameter to HsSndSwitchGetParam function call
typedef UInt16 HsSndPortClass;


#if CPU_ENDIAN == CPU_ENDIAN_BIG
	#define hsSndPortInfo_Signature	'SPRT'
#else
	#define hsSndPortInfo_Signature	'TRPS' /* "SPRT" char array as UInt32 little endian */
#endif
typedef struct
{
	UInt32		signature;	 // always set to hsSndPortInfo_Signature
	UInt32		flags;		 // control and information about port
	HsSndPortID	portID;		 // this identifies the portID
	Int16		minVol;		 // bottom value of the volume range
	Int16		maxVol;		 // top value of the volume range
	Int16		unityVol;	 // volume value where there is no gain or dampening
	Int16		stepVol;     // step size for volume changes within vol range
	Int16		currentVol;  // keeps track of current volume setting
	Int16		currentPan;	 // pan control (0 is midpoint pan between L and R) max pan = maxVol - minVol
	UInt16		stepDB;		 // How many dBs per step = (stepDB >> 8) / (stepDB & 0x0F)
	UInt16		boostDB;     // How many dBs with boost = (boostDB >> 8) / (boostDB & 0x0F)
	UInt16		reserved1;	 // reserved field, set to zero
	UInt16		reserved2;	 // reserved field, set to zero

} HsSndPortInfo, *HsSndPortInfoPtr;


// Use these flags for the commandFlags parameter to HsSndFormatPlay function call
#define hsSndCmdFlags_noWait		0x00000001
#define hsSndCmdFlags_yesWait		0x00000000
#define hsSndCmdFlags_waitMask		0x00000001


enum HsSndFormatEnumTag
{
	/* hsSndFormatWav = 1, For future support */
	hsSndFormatMidi = 2,
	hsSndFormatAmr

};
typedef UInt16 HsSndFormatType;

// Use these constants for HsSndBufferData.flags field
#define hsSndBufFlags_canInterrupt		0x0001	/* playback can be interrupted by user events */
#define hsSndBufFlags_cannotInterrupt	0x0000	/* (default) playback cannot be interrupted by user events */
#define hsSndBufFlags_interruptMask		0x0001

#define hsSndBufFlags_yesRepeat			0x0002	/* repeat the buffer using the "repeat" count in HsSndBufferData.controls */
#define hsSndBufFlags_noRepeat			0x0000	/* (default) buffer used only once */
#define hsSndBufFlags_repeatMask		0x0002

#define hsSndBufFlags_yesEndDelay		0x0004	/* delay completion of playback using the "delay" count in HsSndBufferData.controls */
#define hsSndBufFlags_noEndDelay		0x0000	/* (default) no delay after last audio data processed */
#define hsSndBufFlags_endDelayMask		0x0004

// Use these constants with HsSndBufferData.amplitude field
#define hsSndAmplitude_silent			((UInt32) 0)
#define hsSndAmplitude_unity			((UInt32) 1024)

// Use these macros to set or get the proper control in HsSndBufferData.controls field
#define HsSndBufControl_SetRepeat(controls, value)	 (controls = ((controls & 0xFFFFFF00) |  (((UInt32) value) & 0xFF)      ))
#define HsSndBufControl_GetRepeat(controls)			 (controls & 0x000000FF)
#define HsSndBufControl_SetEndDelay(controls, value) (controls = ((controls & 0xFFFF00FF) | ((((UInt32) value) & 0xFF) << 8)))
#define HsSndBufControl_GetEndDelay(controls)		 ((controls & 0x0000FF00) >> 8)

#define hsSndBufControl_repeatForever				 (0xFF)

/*
	The HsSndCmdType is used as the first parameter to the
	function HsSndFormatPlay. Use the constants below:
*/
enum HsSndCmdEnumTag
{
	hsSndCmdPlay = 1,	// use this command to initiate a playback session
	hsSndCmdStop		// can use to terminate the current playback session

};
typedef UInt16 HsSndCmdType;

/*
	HsSndBufferProc is a "C" style function used as
	a callback under various conditions.

    Parameters:
		userdata		This is the userdata passed when setting the callback routine.
		flags			This is a copy of the HsSndBufferData.flags field
		buffer			This is the pointer originally passed in HsSndBufferData
		bytesUsed		Indicates how many bytes have been cosumed from buffer
		time			Number of milliseconds available for the callback processing
*/
typedef Err (*HsSndBufferProc)  (void * userdata, UInt32 flags, 
								 void * buffer, UInt32 bytesUsed, UInt32 time);

/*
	When using the hsSndCmdPlay command in function HsSndFormatPlay,
	you should pass a pointer to a properly filled HsSndBufferData
	structure. This structure provides information about the buffer
	of coded audio data that is going to be processed and played.

    Notes:
		signature	Must be set to hsSndBufferData_Signature, otherwise
		            function returns an error code.
		flags		Use the various hsSndBufferFlags_* symbols appropriately
		amplitude	PalmOS 5.x amplitude number (valid range from 0 to hsSndAmplitude_unity)
		buffer		Pointer to coded audio data to process.
		bufferSize	Size in bytes of "buffer"
		progress_callback	When Not NULL, it will be invoked at regular intervals
							If progress_callback returns an error, then the play session terminates
		progress_userdata	Passed to progress_callback when invoked
		completion_callback	When Not NULL, it will be invoked when buffer processing completed
		completion_userdata	Passed to completion_callback when invoked
		controls    Compound field with repeat count and end delay controls (use HsSndBufControl_Set* macros with this field)
						repeat field  valid range from 1 to 254, or hsSndBufControl_repeatForever (255).
						              The processing of the buffer will be looped according to this number.
									  When repeatForever is used, then termination should be done by
									  returning an error code from the progress callback. Alternatively,
									  for non-blocking playback, the caller may issue another "Play"
									  call with the "Stop" command. This field is valid and non-zero
									  when hsSndBufFlags_yesRepeat is set in the buffer flags, otherwise
									  this field must be set to zero. A repeat value of 1 means play
									  one time (ie: no repeat), values of 2 and greater will perform
									  the requested number of playbacks by looping on the same buffer data.
						              Use HsSndBufControl_SetRepeat macro to set values in this field.
						endDelay fld  valid range from 1 to 255, each unit is a 1/50th second delay.
						              Use HsSndBufControl_SetEndDelay macro to set values in this field.
									  This field is valid and non-zero when hsSndBufFlags_yesEndDelay
									  is set in the buffer flags, otherwise this field must be set to zero.
*/

#if CPU_ENDIAN == CPU_ENDIAN_BIG
	#define hsSndBufferData_Signature	'SBDA'
#else
	#define hsSndBufferData_Signature	'ADBS' /* 'SBDA' as little endian UInt32 */
#endif
typedef struct HsSndBufferData
{
	UInt32			signature;	// always set to hsSndBufferData_Signature
	UInt32			flags;		// flags and status bits for this data buffer
								// set to zero any flag bits undefined or unused
	UInt32			amplitude;	// volume level for playback
	void *			buffer;		// pointer to beginning of coded audio data to process/play
	UInt32			bufferSize;	// size in bytes of the buffer of coded audio data
	HsSndBufferProc	progress_callback;
	void *			progress_userdata;
	HsSndBufferProc	completion_callback;
	void *			completion_userdata;

	UInt32			controls;	// provides repeat and endDelay controls if proper flags set, otherwise set to zero
	UInt32			reserved1;	// reserved, must set to zero
	UInt32			reserved2;	// reserved, must set to zero

} HsSndBufferData;


#endif // __HSSOUNDLIB_COMMON__H__

