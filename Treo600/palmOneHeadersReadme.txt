====================================
palmOne DTS Team
http://pluggedin.palmone.com
====================================
***If you want to submit a bug report send an email to DevBugs@palmOne.com
   Note that there will be NO feedback from this email as it is 
   only for bug reports and not for submitting technical questions.

***This information is subject to the palmOne Prototype 
   License/Confidentiality Agreement.
   

------------------------------------------
Treo 600 SDK: Header Files
------------------------------------------
March 23, 2004
Latest update of the header files

Updates:
A. Voice Recording support has been added to this release. 
   The Sound Manager API is used to record voice. Please refer to 
   the "Voice Recorder" sample code included in the SDK.

B. Browser
   1. Supports the playing of in-line MIDI files
   2. MSISDN forwarding
   3. Support the playback of AMR voice captures

C. GSM Lib
   1. Life-timer for all GSM carriers.
   2. Updated supported Toll-free numbers and DTMF tones.
   3. Updated the VMI
   4. Added a check feature, if the F/W versioning strings do not match, 
      the radio will shutdown

D. Localisation
   1. Too many to list

E. Mail
   1. Added Mail to the CDMA ROM
   2. Updated or removed carrier settings as required.

F. MMS
   1. MIDI file extension now correctly sent
   2. Cingular, MMS only supports GPRS, no fall-back to CSD 

G. Phone App
   1. Caller ID now properly displaying the 2nd. call
   2. #*31 support
   3. Fixed long contact number issue
   4. UDHI for VMI display
   5. Re-map the <space> bar to no longer answer the phone

H. SMS
   1. Fixed the crash after HotSync
   2. Validity period support
   3. E-mail address displayed in the From: field
   4. Support message duplicates
   5. Support message priority
   6. Resolve corrupt dB crashing

I. System and other
   1. Fixed vibration setting in the Prefs panel
   2. ##RTN hard reset
   3. palmOne rebranding
   4. Removed the Flip logo
   5. Proper battery indication
   6. Added the Car kit App into the ROM.  (GSM and CDMA)


February 4, 2004
Latest update of the header to files (Revision 1.00)
Added:
	Camera Library headers
	Image Library headers
	Updated comments in the SmartTextEngine header files
	Added HsPostProcessPopupList() to the public API
	Added the MMS Type to support MMS Exchange Library
	


September 19, 2003
Latest update of the header files to reflect:
 - GM candidate of the Orange and Sprint ROM
 - PalmSource release of their latest R3 SDK which means
   you don't have to replace any Palm header file anymore
   IMPORTANT: THE Treo 600 SDK NOW NEEDS THE PALMOS R3 
   (OR ABOVE) SDK. 5-WAY AND KEYBOARD WORK PROPERLY IF YOU
   DON'T UPDATE TO THE LATEST PALMSOURCE SDK

August 29, 2003
August 11, 2003

Update to the header file with latest ROM and Simulator release
See Revision history for more info.


July 24th, 2003

Update to the header file with latest ROM and Simulator release
See Revision history for more info.

July 18th, 2003

1. Compiling
        * These are the header files required for developing applications  
          specific to Treo 600 which is based on Palm OS-5.2.1
          
          **NOTE: DELETE THE OLD HANDSPRING5 DIRECTORY BEFORE PUTTING**
          **      THIS NEW ONE IN                                    **
          
        * If you are using GCC, the header files should be placed under 
          /PalmDev/include/Treo600
          (Just extract this package to PalmDev/include)
          
        * If you are using Metrowerks CodeWarrior, the header files should
          be placed under 
          (MW PATH)\CW for Palm OS Support\(Other SDKs)\Treo600
          and simply include the path in your project.
        
        * You first need to download and install the latest version of 
          Palm Source SDK for OS 5. We cannot distribute this SDK.
          You have to register on Palm Source developer website 
          and get the SDK yourself: http://www.palmsource.com/developers/
          The OS 5 SDK is in the seeding area:
          	http://www.palmos.com/cgi-bin/sdk50.cgi
        ****Download the latest version as it is needed to support 5-
            way navigations.
		
		After you've downloaded the Palm OS SDK, you now need to replace 
		files from the Palm Source SDK. These files are included in the
		PalmModified directory:
		This is an interim solution until Palm Source releases another 
		version of their SDK that will incorporate the change needed.
		
		There are some sample codes that you might find usefull. 
		For GCC, the code compiles with the latest Cygwin, PRC-Tools and PilRC
		In particular, you will see how to simply include 68K/Hs.h 
		to use *any and all* Public Treo 600 API.

2. Known Bugs:
	At this time, there are no known bugs in the public header files.
	Let us know if you find any issues by sending an email to 
	                 DevBugs@palmOne.com


3. Revision History
	* Version 1.00
		-Final release of the header for the Treo 600

	* Version 0.95
		-GM release of Sprint and Orange ROM
		-Removed Palm Modified directory since Palm Source released their
		 R3 SDK and they now support Handspring 5-way and keyboard features.
		 (YOU NEED TO UPDATE YOU PALMOS HEADER TO THE LATEST PALMSOURCE SDK)
		
		
	* Version 0.93
		PhnLibForceDataDormant: this API was moved back to private because
		of Operator request. Nothing we can do about it as it would disturb
		network behavior in very congested network.
		Fix some path issue with STE Library
		
    * Version 0.92
    	Minor corrections to private and public API.
		At least added the following:
		- New public API for CDMA:
			PhnLibAPGetField: enable getting the phone number.
			PhnLibForceDataDormant: forces immediate 1xRTT dormancy on CDMA.
    	
	* Version 0.91 
		PhoneEvents.h: 
			changed #include <CoreCompatibility.h>
				to  #include <PalmCompatibility.h>
				
		HsPhoneLibrary.h
			converted DWordPtr to UInt32* in certain functions
		HsPhoneSMS.h
			Added PhnLibSendPendingMessages(UInt16 refNum)
		HsExtCommon.h
			Added 	hsAttrAutoSnoozeAttns
	* Version 0.90 First Public Beta (July 18nd 2003)
			


