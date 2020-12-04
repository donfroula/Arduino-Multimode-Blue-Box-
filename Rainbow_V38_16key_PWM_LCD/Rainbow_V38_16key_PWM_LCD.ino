                                                                         /*
ProjectMF Rainbow Box - 16 Key Version - Sine Wave PWM Output
v38 - PWM Mode and Optional LCD
by: Don Froula
12/4/2018

BE SURE TO SET UP KEYPAD?TONE OUTPUT/LED CONFIGURATION WITH #DEFINEs AFTER COMMENTS!!!!!

v38 Changes
===========
Fixed IMTS ANI mode even/odd pulse parity generation to apply across entired ANI string, not per-digit.
Parity is reset on power-up or after the "D" Seize Radio Channel key is pressed in IMTS ANI mode.

v37 Changes
===========
Synth2 library optimizations

v36 Changes - Synth LIBRARY UPDATE REQUIRED!!!
==============================================
Added Green Box pay phone control functions
Added Canadian Red Box tones
Renamed "Red Box Mode" to "Pay Phone Modes"

v35 Changes - Synth LIBRARY UPDATE REQUIRED!!!
==============================================
Fixed IMTS connect sequence to play back continuous guard tone after connect tone, until beginning of ANI.
Removed manual guard tone on B key, as corrected connect sequence makes the tone unnecessary.
Increased sample rate in Synth library from 20KHz to 40KHz for better tone quality. LIBRARY UPDATE REQUIRED WITH THIS VERSION!!!
Changed tone generation subroutine to turn on and off PWM interrupts after playing tone for better response time at new higher interrupt rate.
Removed separate #define for LED pin selection and renamed board type #define to be more generic.
The separate non-LCD version of code will no longer be maintained, as the LCD code does not care if an LCD is not connected.

v34 Changes
===========
Updated the MFR2 mode to add a 2280Hz seizure beep after the 2280Hz Clear Forward tone
Reduced button hold detect time to 1 second from 1.5 seconds.
Fixed MTS mode to play correct tones, based upon new documentation. Also changed MTS tone description in comments.
Fixed IMTS dialing mode to send 2150Hz guard tone at the start of each digit as the dial is pulled off-normal. Clarified description in comments.
Fixed IMTS disconnect tone and comments description.
Moved volume controls to keys B and C in playback mode to avoid issue with changing volume when changing modes from Red Box mode.
Moved backlight control to D key in playback mode to avoid issue with changing backlight setting when changing modes from Red Box mode.
Eliminated capability of playing B-C-D keys in playback mode to allow control functions on those keys
Eliminated capability of changing playback timing and reminder beeps in playback mode to allow control functions on C and D keys

v33 Changes
===========
Correct a bug where tone mode would not be set when "#define keypadpins_diff_promicro"
Added LCD backlight toggle with digit 0 in Redbox mode. LCD backlight state stored in EEPROM.
Added "<<MEMORY EMPTY>>" notification when attempting to play back an empty or uninitialized memory.

v32 Changes
===========
Fixed a bug in memory playback routine that caused a corrupted tone mode and unneeded loop through the playback
routine if a memory location was empty. In the LCD version, an incorrect LCD diaplay was shown when playing
back an empty memory location.
Fixed a bug that resulted in the memory record function removing a character from the buffer when the key
pressed to save a recording did not result in a buffer update. This could cause the last digit pressed
not to be saved to memory.

v31 Changes
===========
Modified the Synth library further to remove non-Sine wave tables and related functions for less memory utilization
Code adjusted for new library with simplified tone voice initialization
Install new version of Synth library or code will not compile

v30 Changes
===========
Modified the Synth library and code to add a 15-step volume control. 
Volume setting is stored in EEPROM. In Red Box mode, * and # decrease, increase volume in 15 steps.
Volume is stored to EEPROM with each change. Volume cannot be reduced to zero.
The Synth library must be updated along with the v30 code for the code to compile.
Stripped all of the MIDI, pitch modulation, and envelope modulation from the Synth library to save program memory space

v29 Changes
===========
Added a PWM output mode that supports up to 4 simultaneous tones in various waveforms using a customized wave table synthesizer library
R2 seizure tone changed to in-band 2280Hz to agree with in-band usage in the UK

v28 Changes
===========
- Fixed a bug that screwed up the state machine if a memory playback key was held down in playback mode

v27 Changes
===========
- Added MTS Dial Pulse mode (Secode/GE), along with technical notes

v26 Changes
===========
- Added IMTS ANI and IMTS Dial Pulse modes, along with technical notes

v25 Changes
===========
- Corrected a bug in the MF playback function that caused the interval between a KP and the following digit to be too short
- Corrected the AC1 Forward Clear by extending the second 700ms 600Hz tone to 800ms and removing the gap between tones
- Added current AC1 timings in the code comments section

v24 Changes
===========
- Corrected the AC9 mode tones and timings, per an old 78RPM British Post Office recording of an AC1 trunk call setup sequence


This version is for a 16x16 telephone-style keypad.

A special version of the Synth library that supports up to 4 simultaneous tones
on a single output pin, and works around the missing Timer 2 in the Atmega 32U4 chip, on which the
Arduino Micro and Arduino Micro Pro is based, is required. The output uses a 40KHz sampling frequency.
This frequency must be filtered from the output with a low pass filter (see ASCII diagrams below).
The PWM library generates tones with a sine wave lookup table, varying the pulse width of the output according
to values in the 8-bit table. The low pass filter integrates the varying pulse width to a varying
analog voltage. Nominal voltage at silence ("127" is 2.5 volts. Using differential output modes 
increases this to 5 volts, doubling the tone output voltage and increasing the volume.

Row-Column keypad pin assignments, LCD pin assignments, and LED pin assignment may be changed with the
one #define or directly in code to match the board and tone output mode desired.

An external LED may be connected to pin 13 (Arduino Micro) or pin TX0 (Arduino Micro Pro), 
set in the #define at the beginning of the code, with a series 330 ohm
(or similar) resistor to show the special mode status on the front panel of the box.

The numeric keys play tones at the currently selected mode 
(MF, DTMF, C5, SS4, SF Dial Pulse, Red Box, AC1, AC9, IMTS ANI, IMTS Dial, or MTS Dial) 
and duration (MF, DTMF, C5, R2) - 75ms or 120 ms. In Red Box mode, keys 1, 2, 
and 3 play a single nickel, dime, or quarter tone sequence.

The column 4 keys (A, B, C, D) have different functions, depending
upon the signalling system chosen. See the manual for details.

From manual mode, pressing and holding the numeric keys selects the tone mode, according to the following:

1 = MF (R1)
2 = DTMF (Touch-Tone, Autovon)
3 = CCITT #5 (C5, SS5)
4 - CCITT #4 (C4, SS4)
5 - 2600 Dial Pulse (2600Hz Dial Pulse and Supervisory, 10 PPS, 66%/34% Make/Break)
6 - Pay Phone Modes (US and Canadian ACTS pay station coin drop tones, Green Box tones)
7 - R2 (MFC - Unique forward multifrequency tones (not C5 tones), 2280Hz supervisory tone - See manual)
8 - AC1 (750Hz Dial Pulse/Seizure, 600Hz Supervisory, 10 PPS, 66%/34% Make/Break)
9 - AC9 (2280Hz Dial Pulse and Supervisory, 10 PPS, 66%/34% Make/Break)
0 - MTS (Manual Telephone Service Dial Pulse mode extension, unauthenticated - Secode/GE system)
* - IMTS ANI (Improved Mobile Telephone Service ANI digit sequence, with parity)
# - IMTS Digit Dialing - Improved Mobile Telephone Service digit dialing

A 1000Hz beep will sound and the LED will flash once
to indicate the mode change. Setting is stored in EEPROM and retrieved at powerup.

In Playback mode, C and B decrease, increase volume in 15 steps.
Volume is stored to EEPROM with each change. Volume cannot be reduced to zero.
Low to high or high to low beeps confirm each volume change.
Error beeps sound when trying to go above max or below min volume.

In Playback mode, the D key toggles the LCD backlight off and on. State is stored to EEPROM with each change.

From manual mode, a 1.0 second press of key A, in any mode toggles between normal and memory playback 
modes. The on-board/external LED is on when in playback mode as a reminder.
When in playback mode, keys 1,2,3,4,5,6,7,8,9,*,0,# will play back the 
stored sequence at the current tone duration, with appropriate delays inserted 
after trunk supervisory tones, where required.

From manual mode, a 1.0 second press of key B enters memory record mode. The 
on-board/external LED is on when in record mode as a reminder. A second long press of the B key
exits memory record mode with no changes.

From manual mode, a 1.0 second press of key C toggles between short (75ms) and long 
(120ms) tone modes, with confirming beeps. This setting affects only the 
MF, DTMF, C5, and R2 modes. Setting is stored in EEPROM and 
retrieved at powerup. In MF and C5 modes, the * key (KP) and
B key (KP2/ST2P)always play at the longer 120ms tone length per Bell/CCITT specification.

From manual mode, a 1.0 second press of key D toggles the 5-minute reminder beep and LED
indication on and off. Mode stored in EEPROM.

There are 12-32 digit tone sequence memories. To initiate a memory 
write, select the desired tone mode with a long press 
of the corresponding digit key, then press and hold key B for 1 second until a confirming 
beep is heard. The on-board/external LED will 
also light to indicate record mode is active. Enter up to 32 digits 
(a short 2800 Hz beep will sound after each tone as a reminder you 
are in record mode). Any active tone key in the currently-selected signalling mode may be saved to memory. 
Then press and hold the desired storage location memory key 
(1,2,3,4,5,6,7,8,9,0,*,0,#) until another confirming beep is heard. 
The signalling tone or tone sequence that sounds when doing a long press to save 
the sequence will automatically be removed from memory and not stored. 
If one tries to enter more than 32 digits, error tones will sound. 
However, the first 32 digits entered can still be saved by 
pressing and holding a valid memory key. Recording may be aborted by pressing
and holding the B key again, while in record mode. Note that the tone mode
is also stored in the EEPROM for each memory, so a mix of 
signalling system sequences may be stored and played back in individual memories.

Warning beeps sound and the LED flashes after every 5 minutes of inactivity (after last key press)
as a reminder to switch off the box to conserve battery power, if enabled with the D key
(enabled by default).

NOTE: The following AC1 timings were measured from an actual 78 RPM recoding of an AC1 trunk circuit call,
with all tones audible. The AC1 tone timings and playback mode timings are based on this
recording, as well as on anecdotal information:

Measured AC1 Recording Timings
==========================
Trunk Seizure (Forward) - 100ms of 750Hz
Delay to start of dial pulses - 3 seconds
Dial Pulses - 100ms total (10 PPS) for each pulse, 66ms 750Hz on/33ms off, 1 second inter-digit delay
Reverse Supervision on Answer - 133ms of 600Hz
Reverse Flash pips on hangup - 8 pips of 600Hz, each 150ms long, 400ms between pips
Delay from last Reverse Flash pip to Release Clear - 400ms
Clear Reverse - 1.5 seconds of 750Hz, a 25ms gap, 100ms of 600Hz

AC1 timings in the code
==========================
Forward Clear: 2 seconds of 750Hz, 800ms of 600Hz (no gap between tones).
Forward Seizure: 750Hz for 100ms (from recording and consistent with accounts)
Dial Pulses: 750Hz on for 66ms, off for 34ms (from recording, but also standard 66%/34% Make/Break at 10 PPS)
Inter-digit interval: 1 second (from recording)
Clear Forward to Seizure interval: 2 seconds (arbitrary, but seems reasonable)
Seizure to start of dialing interval: 3 seconds (from recording)

IMTS (Improved Mobile Telephone Service)
========================================
When the mobile goes off hook, it sends 350ms of guard (2150Hz) followed by
50 ms of connect (1633Hz). The mobile then immediately sends 190ms of guard tone
and waits for removal of seize tone by the base station. It then starts
transmitting the ID sequence at 20 pulses per second. The ID is the area code
and last four digits of the mobile's number. The pulses are marked by 25ms of
connect (1633Hz) followed by 25ms of either silence or guard tone (2150Hz).
If the pulse is odd, it is followed by silence. If even, it is followed by
guard tone. This is used for parity checking. The inter-digit time is 190ms and
will be either silence or guard tone depending on whether the last pulse was
odd or even. If the last pulse of the last digit in the ID is even it will be
followed by 190ms of guard tone. No tone is sent after the ANI is sent while
waiting for dial tone.

When a number is dialed from a mobile phone, 2150 Hz is sent continuously
as soon a the dial goes off normal (when the dial is moved from its resting
position). Dial pulses representing breaks are marked by 1633 Hz and are sent
at 10 pulses per second. A pulse is 60 ms of 1633 Hz with 40 ms of 2150 Hz
between pulses.

When the mobile hangs up, it sends disconnect, which is 750 ms of alternating 1336Hz and 2150Hz
at 50% make/break at 20 PPS (15 cycles of 1336HZ for 25ms followed by 2150Hz for 25ms).

Normal use is to store the desired ANI in one memory and the dialed digits in another,
as the ANI and dial pulse digits are encoded differently.
Seizure and ANI sequence: D(channel seizure) + B(initial guard tone) + ANI(area code plus last 4 or all 7 digits of calling party mobile number)
Dialed digit: The 10-digit telephone number of the called party
The C key sends a disconnect to hang up the call


MTS (Manual Telephone Service with Dial - Secode/GE System)
====================================================
When the mobile subscriber takes the handset off its hanger the unit is prepared 
for the initialization of a call.  If the channel is not busy the subscriber pushes 
the Initiate button in the center of the channel selector knob and the mobile transmits 
a one-second burst of 1700 Hz and 1100 Hz tones.  This combination of tones 
constitutes the Connect signal which is accepted by the terminal equipment.  
The terminal equipment connects to a free telephone trunk line and returns a dial 
tone to the mobile unit on the land side transmit frequency.  The subscriber, 
once he hears the dial tone, then dials the desired number.  When this is done, 
the dial is pulled off rest, keying the mobile's transmitter, and  the mobile 
transmits 1100 and 1700 Hz tones.  When the dial is released, as it returns to the 
rest position it pulses 1500+1700 (make) and 1100+1700 (break) Hz alternating tones corresponding to the 
digit dialed.  Once the digit has been outpulsed and the dial returns to rest, 
the mobile transmitter un-keys and its carrier drops.  Successive digits dialed 
repeat the process.  Once the number has been dialed, the terminal connects to 
the land party's number being dialed and completes the circuit path if the party 
answers.  In the Dial system, the conversation is normally carried on in the 
Push-to-Talk mode of operation.  The mobile transmitter is nonetheless operating 
in the full duplex mode and for all practical purposes the Push-to-Talk operation 
is constructive in only preserving current drain on the battery and minimizing 
mobile signal flutter heard by the called party.

At the conclusion of the call, the mobile subscriber ends the call by hanging 
up the handset.  This triggers the transmitter to send 1700 and 1300 Hz tones 
for one second.  This tone transmission constitutes the Disconnect signal 
from the mobile.  The land terminal then closes down and returns to the standby mode.
*/

//SET UP CONFIGURATION HERE FIRST BY UNCOMMENTING ONE KEYPAD?TONE CONFIGURATION AND ONE LED CONFIGURATION - SEE MANUAL
//******************************************************************************************************************************
//Set up contional compilation for keypad, output pin(s), and LED pin assgnments
//Uncoment one:

//R1-R2-R3-R4-C1-C2-C3-C4 keypad pinout - standard keypad, LED, and output pin assignments, per schematic, for Arduino Micro
//#define single_micro

//R1-R2-R3-R4-C1-C2-C3-C4 keypad pinout - standard keypad, LED, and output pin assignments, per schematic, for Arduino Pro Micro
//#define single_promicro

//R1-R2-R3-R4-C1-C2-C3-C4 keypad pinout - alternate keypad, LED, and output pin assignments, per schematic, for Arduino Micro
//#define diff_micro

//R1-R2-R3-R4-C1-C2-C3-C4 keypad pinout - alternate keypad, LED, and output pin assignments, per schematic, for Arduino Pro Micro
#define diff_promicro

//**********************************************************************************


#include <Keypad.h> // This library makes it easy to use a key matrix
#include <EEPROM.h> //This library allows reading and writing to the EEPROM
#include <SimpleTimer.h> //This library allows simple timer functions without interfering with keypad.h timer use
#include <synth2.h>  //Modified Synth library, for Atmega 32U4 Arduinos and basic wave generation - MIDI and pitch/envelope shaping removed.
#include <LiquidCrystal.h>

const byte ROWS = 4; // Four rows of keys
const byte COLS = 4;  // Four columns 

//define the symbols on the buttons of the keypads,
//makes the code easier to understand down the line.
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A',},
  {'4','5','6','B',},
  {'7','8','9','C',},
  {'*','0','#','D',}
};

#if defined(single_micro)
  //R1-R2-R3-R4-C1-C2-C3-C4 keypad pinout - standard keypad, LED and output pin assignments, per schematic, for Arduino Micro
  byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
  byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad
  int ledPin = 13; //Pin of on-board/external special mode status LED - Arduino Micro
#endif

#if defined(single_promicro)
  //R1-R2-R3-R4-C1-C2-C3-C4 keypad pinout - standard keypad, LED and output pin assignments, per schematic, for Arduino Pro Micro
  byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
  byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad
  int ledPin = 1; //Pin of on-board/external special mode status LED - Arduino MicroPro (shared with serial data TX)
#endif

#if defined(diff_micro)
  //R1-R2-R3-R4-C1-C2-C3-C4 keypad pinout - alternate keypad, LED and output pin assignments, per schematic, for Arduino Micro
  byte rowPins[ROWS] = {11, 8, 7, 6}; //connect to the row pinouts of the keypad
  byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad
  int ledPin = 13; //Pin of on-board/external special mode status LED - Arduino Micro
#endif

#if defined(diff_promicro)
  //R1-R2-R3-R4-C1-C2-C3-C4 keypad pinout - alternate keypad, LED and output pin assignments, per schematic, for Arduino Pro Micro
  byte rowPins[ROWS] = {16, 8, 7, 6}; //connect to the row pinouts of the keypad
  byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad
  int ledPin = 1; //Pin of on-board/external special mode status LED - Arduino MicroPro (shared with serial data TX)
#endif

float MF_freq1[16] = {1300,700,700,900,700,900,1100,700,900,1100,1100,1500,900,1300,700,2600}; // MF tone 1, 0-9, *, #, #, A, B, C, D
float MF_freq2[16] = {1500,900,1100,1100,1300,1300,1300,1500,1500,1500,1700,1700,1700,1700,1700,0}; // MF tone 2, 0-9, *, #, #, A, B, C, D

float DTMF_freq1[16] = {941,697,697,697,770,770,770,852,852,852,941,941,697,770,852,941}; // DTMF tone 1, 0-9, *, #, A, B, C, D
float DTMF_freq2[16] = {1336,1209,1336,1477,1209,1336,1477,1209,1336,1477,1209,1477,1633,1633,1633,1633}; // DTMF tone 2, 0-9, *, #, A, B, C, D

float MFR2_freq1[16] = {1740,1380,1380,1500,1380,1500,1620,1380,1500,1620,1620,1860,1500,1740,1380,3825}; // MFR2 tone 1, 0-9, *, #, A, B, C, D
float MFR2_freq2[16] = {1860,1500,1620,1620,1740,1740,1740,1860,1860,1860,1980,1980,1980,1980,1980,0}; // MFR2 tone 2, 0-9, *, #, #, A, B, C, D

//Digit codings for SS4 sequences
int ss4Freqs[][4] = {
  {1,0,1,0},{0,0,0,1},{0,0,1,0}, //0,1,2
  {0,0,1,1},{0,1,0,0},{0,1,0,1}, //3,4,5
  {0,1,1,0},{0,1,1,1},{1,0,0,0}, //6,7,8
  {1,0,0,1},{},{1,1,1,1},        //9,*(Terminal Seize,#(End-of-pulsing)
  {1,1,0,0},{},{1,0,1,1},        //A(Code 12),B,C(Code 11)
  {}                             //D
};

  String opmode[12] = { //String array of operating modes for LCD display
    "MF/R1 Mode",
    "DTMF Mode",
    "CCITT #5 Mode",
    "CCITT #4 Mode",
    "2600 DP Mode",
    "Pay Phone Mode",
    "R2/MFC Mode",
    "UK AC1 Mode",
    "UK AC9 Mode",
    "IMTS ANI Mode",
    "IMTS Dial Mode",
    "MTS Dial Mode"
  };
char keylist[17] = {'0','1','2','3','4','5','6','7','8','9','*','#','A','B','C','D',' '}; //Character array for LCD display toneindex translation

//Initialize an instance of class NewKeypad
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

int keybuffer[35]; //Temporary RAM buffer for recording digits for EEPROM storage
int bufferpointer; //Pointer into keybuffer
int toneindex = 16; //Index into tone arrays, depending upon key pressed. Initialize to invalid key for proper LCD display on start.
const int mf = 0; //Constant for MF tone mode
const int dtmf = 1; //Constant for DTMF tone mode
const int c5 = 2; //Constant for DTMF tone mode
const int ss4 = 3; //Constant for SS4 tone mode
const int dialpulse = 4; //Constant for dialpulse mode
const int redbox = 5; //Constant for redbox mode
const int mfr2 = 6; //Constant for redbox mode
const int ac1 = 7; //Constant for ac1 mode
const int ac9 = 8; //Constant for ac9 mode
const int imtsani = 9; //Constant for IMTS ANI mode
const int imtsdial = 10; //Constant for IMTS dialpulse mode
const int mtsdial = 11; //Constant for MTS dialpulse mode
const int normal = 0; //Constant for playback mode off
const int playback = 1; //Constant for playback mode on
const int eofmarker = 255; //Constant for keybuffer and EEPROM memory end of sequence marker
const int abortrecord = 9999; //Constant for aborting recording withou writing EEPROM test, above highest EEPROM location
const int off = 0; //Constant for mode off
const int on = 1; //Constant for mode on
const int EEmemory1 = 0; //Start of EEPROM for memory 1 (34 * 0)
const int EEmemory2 = 34; //Start of EEPROM for memory 2 (34 * 1)
const int EEmemory3 = 68; //Start of EEPROM for memory 3 (34 * 2)
const int EEmemory4 = 102; //Start of EEPROM for memory 4 (34 * 3)
const int EEmemory5 = 136; //Start of EEPROM for memory 5 (34 * 4)
const int EEmemory6 = 170; //Start of EEPROM for memory 6 (34 * 5)
const int EEmemory7 = 204; //Start of EEPROM for memory 7 (34 * 6)
const int EEmemory8 = 238; //Start of EEPROM for memory 8 (34 * 7)
const int EEmemory9 = 272; //Start of EEPROM for memory 9 (34 * 8)
const int EEmemory10 = 306; //Start of EEPROM for memory 10 (34 * 9)
const int EEmemory11 = 340; //Start of EEPROM for memory 11 (34 * 10)
const int EEmemory12 = 374; //Start of EEPROM for memory 12 (34 * 11)
const int mfmodeEE = 408; //Tone mode storage starts at (34 * 12) 
const int delaymfEE = 409; //Tone duration storage starts at ((34 * 12) + 1)
const int timerEE = 410; //Timer state (on or off) storage starts at ((34 * 12) + 2)
const int volattenEE = 411; //Volume attenuation storage starts at ((34 * 12) + 3)
const int backlightEE = 412; //LCD backlight state storage starts at ((34 * 12) + 4)
const int shorttone = 75; //Short duration MF/DTMF tone
const int longtone = 120; //Long duration MF/DTMF tone
const unsigned long delay2600 = 1250; //Fixed duration for 2600 seizure tone
float ss4Tone[2] = {2400,2040}; // SS4 digit tones for 0,1 respectively
int mfmode; //Storage for tone mode, MF, DTMF, or SS4
int mfmodeplayback; //Storage for retrieved tone mode from stored EEPROM tone sequence on playback
unsigned long delayMF; //Storage for current MF/DTMF tone duration
int playbackmode = off; //Storage for playback mode, on or off
int recordmode = off; //Storage for record mode, on or off
unsigned char pwm_mode; //Storage for PWM libray output mode and ouput pin assignments
int timermode; //Storage for warning timer on/off state
int timer_id; //Specific timer ID for restarting timer
long idle_timer_interval = 300000; //Idle timer interval in milliseconds, 5 minutes
byte volume_atten; //Set default volume attenuation to none
byte backlight; //LCD backlight state
int backlightPin = 0; //LCD backlight pin assignment
byte bufferflag = 0; //Flag to indicate if buffer has been updated, to determine if tone needs to be removed when saving recording to memory
bool imts_ani_parity = 0;  //Global IMTS parity flag

//Instantiate idle timer object - No interrupts or hardware timers used with SimpleTimer!
SimpleTimer idleTimer;

//Instaniate PWM tone generator
synth notePlayer;

#if defined(single_micro)
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5); //Define Arduino pins for 16x2 LCD module
#endif

#if defined(single_promicro)
LiquidCrystal lcd(14, 15, A0, A1, A2, A3); //Define Arduino pins for 16x2 LCD module
#endif

#if defined(diff_micro)
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5); //Define Arduino pins for 16x2 LCD module
#endif

#if defined(diff_promicro)
LiquidCrystal lcd(14, 15, A0, A1, A2, A3); //Define Arduino pins for 16x2 LCD module
#endif

void setup(){
  Serial.begin(9600); // Initialize serial port for debugging

//The following tone output modes are supported for custom configurations, or allow #DEFINE to set mode
  //pwm_mode = DIFF_10_13; //Differential output on pins 10 and 13
  //pwm_mode = CHB_9; //Single-ended (ground referenced) output on pin 9
  //pwm_mode = CHB_10; //Single-ended (ground referenced) output on pin 10
  //pwm_mode = CHB_DIFF_9_10; //Differential output on pins 9 and 10
  //pwm_mode = CHA_5; //Single-ended (ground referenced) output on pin 5
  //pwm_mode = CHA_13; //Single-ended (ground referenced) output on pin 13
  //pwm_mode = CHA_DIFF_5_13; //Differential output on pins 5 and 13 
  
#if defined(single_micro)
 pwm_mode = CHB_10; //Single-ended (ground referenced) output on pin 10 - Arduino Micro
#endif

#if defined(single_promicro)
 pwm_mode = CHB_10; //Single-ended (ground referenced) output on pin 10 - Arduino Pro Micro
#endif

#if defined(diff_micro)
 pwm_mode = CHB_DIFF_9_10; //Differential output on pins 9 and 10 - Arduino Micro
#endif
  
#if defined(diff_promicro)
 pwm_mode = CHB_DIFF_9_10; //Differential output on pins 9 and 10 - Arduino Pro Micro
#endif  

// Single-ended low-pass filter (required) - Only 15dB down at 20KHz with volume loss:
//                           2-10µF
//          PIN---[ 150 ]-+---||--->> Audio out
//                        |
//                       === .33µF
//                        |
//                       GND



//             12mH inductor   2-10µF
//          PIN---^^^^^^------ +||--->> Audio out
//                              |
//                             === .33µF
//                              |
//                             GND



// Differential mode gives twice the voltage swing and may be better for driving piezos or speakers directly.
// Here are some examples:

//            PIN------- Speaker/Piezo +

//            PIN------- Speaker/Piezo -

// Or better with a low pass filter - Almost 40 dB down at 20KHz, with less volume loss
//
//
//         PIN ------+
//                   |
//                    )
//                    ) 12mH inductor
//                    )
//                   |      2-10µF
//                   +--- -- +||----Speaker/Piezo +
//                   |
//                  === .33µF
//                   |
//         PIN  -----+------ +||---- Speaker/Piezo -
//                          2-10µF

  
  notePlayer.begin(pwm_mode); //Sets up output pins and single-ended or differential mode, according to the uncommented mode above.
  
  notePlayer.setWave(0); //Tone 1 initialization
  notePlayer.setWave(1); //Tone 2 initialization
  //notePlayer.setWave(2); //Tone 3 initialization
  //notePlayer.setWave(3); //Tone 4 initialization

  customKeypad.setHoldTime(1000); // hold for 1.0 seconds to change state to HOLD
  
  //Set a listener event for this keypad
  customKeypad.addEventListener(keypadEvent);
  
  //Initialize and turn off special status LED (and built-in LED on Arduino Micro)
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  
  //Set up timer object for idle reminder
  timer_id = idleTimer.setInterval(idle_timer_interval, callback_Reminder); //Set initial idle timer callback
  
  //Read stored mfmode and initialize to MF tone mode on first run or on error
  mfmode = EEPROM.read(mfmodeEE);
  if (mfmode != mf && mfmode != dtmf && mfmode != c5 && mfmode != ss4 && 
      mfmode != dialpulse && mfmode != redbox && mfmode != mfr2 && 
      mfmode != ac1 && mfmode != ac9 && mfmode != imtsani && mfmode != imtsdial &&
      mfmode != mtsdial){
    mfmode = mf;
    EEPROM.write(mfmodeEE, mf);}
    
  //Read stored delayMF and initialize to 75ms on first run or on error  
  delayMF = EEPROM.read(delaymfEE);
  if (delayMF != longtone && delayMF != shorttone){
    delayMF = shorttone;
    EEPROM.write(delaymfEE, shorttone);}
       
   //Read stored timermode and initialize to "on" on first run or on error  
  timermode = EEPROM.read(timerEE);
  if (timermode != off && timermode != on){
    timermode = on;
    EEPROM.write(timerEE, timermode);}
    
   //Read stored volume attenuation and initialize to none (0) on first run or on error  
  volume_atten = EEPROM.read(volattenEE);
  if (volume_atten > 238){  //Check if EE memory is out of allowable volume attenuation range
    volume_atten = 0; //Reset to no attenuation and save, if it is
    EEPROM.write(volattenEE, volume_atten);}
  notePlayer.setAtten(volume_atten); //Set the volume attenuation
  
  //Read stored LCD backlight state and initialize to on, on first run or error
  backlight = EEPROM.read(backlightEE);
  if (backlight > 1){  //Check if EE memory is out of allowable backlight range
    backlight = 1; //Turn on LCD backlight and save, if it is
    EEPROM.write(backlightEE, backlight);}
  
  //Initialize LCD backlight
  pinMode(backlightPin, OUTPUT);
  digitalWrite(backlightPin, backlight);
    
  //Initialize RAM keybuffer
  initbuffer();
  
  lcd.begin(16, 2); //Initialize the LCD for a 16x2 display. Larger displays will probably work, but not smaller.
  
  updateDisplay(); //Refresh the display to show the current box state
  
  //Beeps/LED flash on powerup or reset
  digitalWrite(ledPin, HIGH);
  startbeeps();
  digitalWrite(ledPin, LOW);
}
  
  
//Main loop  
void loop(){
if (timermode) {idleTimer.run();} //Poll idle timer, if option enabled
char customKey = customKeypad.getKey();  //Get key from keypad
if(customKey) {idleTimer.restartTimer(timer_id);} //Reset idle timer if key is pressed
//Serial.println(heldButton);   //Debug printing of detected key
}
//End of loop


//Event listener for keypad events.
void keypadEvent(KeypadEvent key){
    switch (customKeypad.getState()){
    case PRESSED:
           switch (key) {
            case '1':
              toneindex = 1; //Set index into tone tables for key
              if (mfmode == mf && playbackmode == off) {playMF(toneindex,delayMF); updatebuffer();} //If not in playback and tone mode is MF, play tone at current duration and update keybuffer
              else if (mfmode == dtmf && playbackmode == off) {playDTMF(toneindex,delayMF); updatebuffer();} //If not in playback and tone mode is DTMF, play tone at current duration and update keybuffer
              else if (mfmode == c5 && playbackmode == off) {playMF(toneindex,delayMF); updatebuffer();} //If not in playback and tone mode is C5, play tone at current duration and update keybuffer
              else if (mfmode == redbox && playbackmode == off) {redBox(1,66,1); updatebuffer();} //If in redbox mode, play nickel coin tone once
              else if (mfmode == ss4 && playbackmode == off) {ss4Signal(toneindex); updatebuffer();}
              else if (mfmode == dialpulse && playbackmode == off) {pulse(toneindex); updatebuffer();}
              else if (mfmode == mfr2 && playbackmode == off) {playMFR2(toneindex,delayMF); updatebuffer();} //If not in playback and tone mode is MFR2, play tone at current duration and update keybuffer
              else if (mfmode == ac1 && playbackmode == off) {pulseAC1(toneindex); updatebuffer();}
              else if (mfmode == ac9 && playbackmode == off) {pulseAC9(toneindex); updatebuffer();}
              else if (mfmode == imtsani && playbackmode == off) {imtsANI(toneindex); updatebuffer();}
              else if (mfmode == imtsdial && playbackmode == off) {imtsDial(toneindex); updatebuffer();}
              else if (mfmode == mtsdial && playbackmode == off) {mtsDial(toneindex); updatebuffer();}
              else if (playbackmode == on) {eeplay(EEmemory1);} //If in playback mode, playback EEPROM memory location
            break;
           case '2':
              toneindex = 2;
              if (mfmode == mf && playbackmode == off) {playMF(toneindex,delayMF); updatebuffer();}
              else if (mfmode == dtmf && playbackmode == off) {playDTMF(toneindex,delayMF); updatebuffer();}
              else if (mfmode == c5 && playbackmode == off) {playMF(toneindex,delayMF); updatebuffer();}
              else if (mfmode == redbox && playbackmode == off) {redBox(2,66,1); updatebuffer();} //If in redbox mode, play dime coin tone once
              else if (mfmode == ss4 && playbackmode == off) {ss4Signal(toneindex); updatebuffer();}
              else if (mfmode == dialpulse && playbackmode == off) {pulse(toneindex); updatebuffer();}
              else if (mfmode == mfr2 && playbackmode == off) {playMFR2(toneindex,delayMF); updatebuffer();}
              else if (mfmode == ac1 && playbackmode == off) {pulseAC1(toneindex); updatebuffer();}
              else if (mfmode == ac9 && playbackmode == off) {pulseAC9(toneindex); updatebuffer();}
              else if (mfmode == imtsani && playbackmode == off) {imtsANI(toneindex); updatebuffer();}
              else if (mfmode == imtsdial && playbackmode == off) {imtsDial(toneindex); updatebuffer();}
              else if (mfmode == mtsdial && playbackmode == off) {mtsDial(toneindex); updatebuffer();}
              else if (playbackmode == on) {eeplay(EEmemory2);}
            break;
           case '3':
              toneindex = 3;
              if (mfmode == mf && playbackmode == off) {playMF(toneindex,delayMF); updatebuffer();}
              else if (mfmode == dtmf && playbackmode == off) {playDTMF(toneindex,delayMF); updatebuffer();}
              else if (mfmode == c5 && playbackmode == off) {playMF(toneindex,delayMF); updatebuffer();}
              else if (mfmode == redbox && playbackmode == off) {redBox(5,33,1); updatebuffer();} //If in redbox mode, play quarter coin tone once
              else if (mfmode == ss4 && playbackmode == off) {ss4Signal(toneindex); updatebuffer();}
              else if (mfmode == dialpulse && playbackmode == off) {pulse(toneindex); updatebuffer();}
              else if (mfmode == mfr2 && playbackmode == off) {playMFR2(toneindex,delayMF); updatebuffer();}
              else if (mfmode == ac1 && playbackmode == off) {pulseAC1(toneindex); updatebuffer();}
              else if (mfmode == ac9 && playbackmode == off) {pulseAC9(toneindex); updatebuffer();}
              else if (mfmode == imtsani && playbackmode == off) {imtsANI(toneindex); updatebuffer();}
              else if (mfmode == imtsdial && playbackmode == off) {imtsDial(toneindex); updatebuffer();}
              else if (mfmode == mtsdial && playbackmode == off) {mtsDial(toneindex); updatebuffer();}
              else if (playbackmode == on) {eeplay(EEmemory3);}
            break;
           case '4':
              toneindex = 4;
              if (mfmode == mf && playbackmode == off) {playMF(toneindex,delayMF); updatebuffer();}
              else if (mfmode == dtmf && playbackmode == off) {playDTMF(toneindex,delayMF); updatebuffer();}
              else if (mfmode == c5 && playbackmode == off) {playMF(toneindex,delayMF); updatebuffer();}
              else if (mfmode == redbox && playbackmode == off) {playMF(2,700); updatebuffer();} //Operator Coin Collect Green Box tone (MF "2")
              else if (mfmode == ss4 && playbackmode == off) {ss4Signal(toneindex); updatebuffer();}
              else if (mfmode == dialpulse && playbackmode == off) {pulse(toneindex); updatebuffer();}
              else if (mfmode == mfr2 && playbackmode == off) {playMFR2(toneindex,delayMF); updatebuffer();}
              else if (mfmode == ac1 && playbackmode == off) {pulseAC1(toneindex); updatebuffer();}
              else if (mfmode == ac9 && playbackmode == off) {pulseAC9(toneindex); updatebuffer();}
              else if (mfmode == imtsani && playbackmode == off) {imtsANI(toneindex); updatebuffer();}
              else if (mfmode == imtsdial && playbackmode == off) {imtsDial(toneindex); updatebuffer();}
              else if (mfmode == mtsdial && playbackmode == off) {mtsDial(toneindex); updatebuffer();}
              else if (playbackmode == on) {eeplay(EEmemory4);}
            break;
           case '5':
              toneindex = 5;
              if (mfmode == mf && playbackmode == off) {playMF(toneindex,delayMF); updatebuffer();}
              else if (mfmode == dtmf && playbackmode == off) {playDTMF(toneindex,delayMF); updatebuffer();}
              else if (mfmode == c5 && playbackmode == off) {playMF(toneindex,delayMF); updatebuffer();}
              else if (mfmode == redbox && playbackmode == off) {playPWM(1100, 1700, 700); updatebuffer();} //Operator Coin Return Green Box tone (MF "KP")
              else if (mfmode == ss4 && playbackmode == off) {ss4Signal(toneindex); updatebuffer();}
              else if (mfmode == dialpulse && playbackmode == off) {pulse(toneindex); updatebuffer();}
              else if (mfmode == mfr2 && playbackmode == off) {playMFR2(toneindex,delayMF); updatebuffer();}
              else if (mfmode == ac1 && playbackmode == off) {pulseAC1(toneindex); updatebuffer();}
              else if (mfmode == ac9 && playbackmode == off) {pulseAC9(toneindex); updatebuffer();}
              else if (mfmode == imtsani && playbackmode == off) {imtsANI(toneindex); updatebuffer();}
              else if (mfmode == imtsdial && playbackmode == off) {imtsDial(toneindex); updatebuffer();}
              else if (mfmode == mtsdial && playbackmode == off) {mtsDial(toneindex); updatebuffer();}
              else if (playbackmode == on) {eeplay(EEmemory5);}
            break;
           case '6':
              toneindex = 6;
              if (mfmode == mf && playbackmode == off) {playMF(toneindex,delayMF); updatebuffer();}
              else if (mfmode == dtmf && playbackmode == off) {playDTMF(toneindex,delayMF); updatebuffer();}
              else if (mfmode == c5 && playbackmode == off) {playMF(toneindex,delayMF); updatebuffer();}
              else if (mfmode == redbox && playbackmode == off) {playMF(14,700); updatebuffer();} //Operator Ringback Green Box tone (MF "ST3P")
              else if (mfmode == ss4 && playbackmode == off) {ss4Signal(toneindex); updatebuffer();}
              else if (mfmode == dialpulse && playbackmode == off) {pulse(toneindex); updatebuffer();}
              else if (mfmode == mfr2 && playbackmode == off) {playMFR2(toneindex,delayMF); updatebuffer();}
              else if (mfmode == ac1 && playbackmode == off) {pulseAC1(toneindex); updatebuffer();}
              else if (mfmode == ac9 && playbackmode == off) {pulseAC9(toneindex); updatebuffer();}
              else if (mfmode == imtsani && playbackmode == off) {imtsANI(toneindex); updatebuffer();}
              else if (mfmode == imtsdial && playbackmode == off) {imtsDial(toneindex); updatebuffer();}
              else if (mfmode == mtsdial && playbackmode == off) {mtsDial(toneindex); updatebuffer();}
              else if (playbackmode == on) {eeplay(EEmemory6);}
            break;
           case '7':
              toneindex = 7;
              if (mfmode == mf && playbackmode == off) {playMF(toneindex,delayMF); updatebuffer();}
              else if (mfmode == dtmf && playbackmode == off) {playDTMF(toneindex,delayMF); updatebuffer();}
              else if (mfmode == c5 && playbackmode == off) {playMF(toneindex,delayMF); updatebuffer();}
              else if (mfmode == redbox && playbackmode == off) {playMF(8,700); updatebuffer();} //Operator Released Green Box tone (MF "8")
              else if (mfmode == ss4 && playbackmode == off) {ss4Signal(toneindex); updatebuffer();}
              else if (mfmode == dialpulse && playbackmode == off) {pulse(toneindex); updatebuffer();}
              else if (mfmode == mfr2 && playbackmode == off) {playMFR2(toneindex,delayMF); updatebuffer();}
              else if (mfmode == ac1 && playbackmode == off) {pulseAC1(toneindex); updatebuffer();}
              else if (mfmode == ac9 && playbackmode == off) {pulseAC9(toneindex); updatebuffer();}
              else if (mfmode == imtsani && playbackmode == off) {imtsANI(toneindex); updatebuffer();}
              else if (mfmode == imtsdial && playbackmode == off) {imtsDial(toneindex); updatebuffer();}
              else if (mfmode == mtsdial && playbackmode == off) {mtsDial(toneindex); updatebuffer();}
              else if (playbackmode == on) {eeplay(EEmemory7);}
            break;
           case '8':
              toneindex = 8;
              if (mfmode == mf && playbackmode == off) {playMF(toneindex,delayMF); updatebuffer();}
              else if (mfmode == dtmf && playbackmode == off) {playDTMF(toneindex,delayMF); updatebuffer();}
              else if (mfmode == c5 && playbackmode == off) {playMF(toneindex,delayMF); updatebuffer();}
              else if (mfmode == redbox && playbackmode == off) {playMF(0,700); updatebuffer();} //Operator Attached Green Box tone (MF "0")
              else if (mfmode == ss4 && playbackmode == off) {ss4Signal(toneindex); updatebuffer();}
              else if (mfmode == dialpulse && playbackmode == off) {pulse(toneindex); updatebuffer();}
              else if (mfmode == mfr2 && playbackmode == off) {playMFR2(toneindex,delayMF); updatebuffer();}
              else if (mfmode == ac1 && playbackmode == off) {pulseAC1(toneindex); updatebuffer();}
              else if (mfmode == ac9 && playbackmode == off) {pulseAC9(toneindex); updatebuffer();}
              else if (mfmode == imtsani && playbackmode == off) {imtsANI(toneindex); updatebuffer();}
              else if (mfmode == imtsdial && playbackmode == off) {imtsDial(toneindex); updatebuffer();}
              else if (mfmode == mtsdial && playbackmode == off) {mtsDial(toneindex); updatebuffer();}
              else if (playbackmode == on) {eeplay(EEmemory8);}
            break;
           case '9':
              toneindex = 9;
              if (mfmode == mf && playbackmode == off) {playMF(toneindex,delayMF); updatebuffer();}
              else if (mfmode == dtmf && playbackmode == off) {playDTMF(toneindex,delayMF); updatebuffer();}
              else if (mfmode == c5 && playbackmode == off) {playMF(toneindex,delayMF); updatebuffer();}
              else if (mfmode == redbox && playbackmode == off) {playMF(11,700); updatebuffer();} //Combined operator Coin Collect and Operator Released Green Box tone (MF "ST")
              else if (mfmode == ss4 && playbackmode == off) {ss4Signal(toneindex); updatebuffer();}
              else if (mfmode == dialpulse && playbackmode == off) {pulse(toneindex); updatebuffer();}
              else if (mfmode == mfr2 && playbackmode == off) {playMFR2(toneindex,delayMF); updatebuffer();}
              else if (mfmode == ac1 && playbackmode == off) {pulseAC1(toneindex); updatebuffer();}
              else if (mfmode == ac9 && playbackmode == off) {pulseAC9(toneindex); updatebuffer();}
              else if (mfmode == imtsani && playbackmode == off) {imtsANI(toneindex); updatebuffer();}
              else if (mfmode == imtsdial && playbackmode == off) {imtsDial(toneindex); updatebuffer();}
              else if (mfmode == mtsdial && playbackmode == off) {mtsDial(toneindex); updatebuffer();}
              else if (playbackmode == on) {eeplay(EEmemory9);}
            break;
           case '*': // Key Pulse or KP if MF/C5 modes
              toneindex = 10;
              if (mfmode == mf && playbackmode == off) {playMF(toneindex,delayMF); updatebuffer();}
              else if (mfmode == dtmf && playbackmode == off) {playDTMF(toneindex,delayMF); updatebuffer();}
              else if (mfmode == c5 && playbackmode == off) {playMF(toneindex,delayMF); updatebuffer();}
              else if (mfmode == redbox && playbackmode == off) {canredBox(1,60,1); updatebuffer();} //Canadian nickel tone
              else if (mfmode == ss4 && playbackmode == off) {playSS4Termseize(); updatebuffer();}
              //else if (mfmode == dialpulse && playbackmode == off) {}
              else if (mfmode == mfr2 && playbackmode == off) {playMFR2(toneindex,delayMF); updatebuffer();} //MFR2 Cable route/test call
              else if (mfmode == ac1 && playbackmode == off) {playPWM(750, 0, 100); updatebuffer();} //Seizure
              else if (mfmode == ac9 && playbackmode == off) {playPWM(2280, 0, 95); updatebuffer();} //Seizure
              //else if (mfmode == imtsani && playbackmode == off) {} 
              //else if (mfmode == imtsdial && playbackmode == off) {}
              else if (playbackmode == on) {eeplay(EEmemory10);}
            break;
           case '0':
              toneindex = 0;
              if (mfmode == mf && playbackmode == off) {playMF(toneindex,delayMF); updatebuffer();}
              else if (mfmode == dtmf && playbackmode == off) {playDTMF(toneindex,delayMF); updatebuffer();}
              else if (mfmode == c5 && playbackmode == off) {playMF(toneindex,delayMF); updatebuffer();}
              else if (mfmode == redbox && playbackmode == off) {canredBox(2,60,1); updatebuffer();}
              else if (mfmode == ss4 && playbackmode == off) {ss4Signal(toneindex); updatebuffer();}
              else if (mfmode == dialpulse && playbackmode == off) {pulse(toneindex); updatebuffer();}
              else if (mfmode == mfr2 && playbackmode == off) {playMFR2(toneindex,delayMF); updatebuffer();}
              else if (mfmode == ac1 && playbackmode == off) {pulseAC1(toneindex); updatebuffer();}
              else if (mfmode == ac9 && playbackmode == off) {pulseAC9(toneindex); updatebuffer();}
              else if (mfmode == imtsani && playbackmode == off) {imtsANI(toneindex); updatebuffer();}
              else if (mfmode == imtsdial && playbackmode == off) {imtsDial(toneindex); updatebuffer();}
              else if (mfmode == mtsdial && playbackmode == off) {mtsDial(toneindex); updatebuffer();}
              else if (playbackmode == on) {eeplay(EEmemory11);}
            break;
           case '#': // "Start" or ST tone if MF/C5 modes
              toneindex = 11;
              if (mfmode == mf && playbackmode == off) {playMF(toneindex,delayMF); updatebuffer();}
              else if (mfmode == dtmf && playbackmode == off) {playDTMF(toneindex,delayMF); updatebuffer();}
              else if (mfmode == c5 && playbackmode == off) {playMF(toneindex,delayMF); updatebuffer();}
              else if (mfmode == redbox && playbackmode == off) {canredBox(5,33,1); updatebuffer();}
              else if (mfmode == ss4 && playbackmode == off) {ss4Signal(toneindex); updatebuffer();}
              //else if (mfmode == dialpulse && playbackmode == off) {}
              else if (mfmode == mfr2 && playbackmode == off) {playMFR2(toneindex,delayMF); updatebuffer();}
              //else if (mfmode == ac1 && playbackmode == off) {}
              //else if (mfmode == ac9 && playbackmode == off) {}
              else if (playbackmode == on) {eeplay(EEmemory12);}
            break;
            case 'A':
               toneindex = 12;
               if (mfmode == mf && playbackmode == off) {playMF(toneindex,delayMF); updatebuffer();}
               else if (mfmode == dtmf && playbackmode == off) {playDTMF(toneindex,delayMF); updatebuffer();}
               else if (mfmode == c5 && playbackmode == off) {playMF(toneindex,delayMF); updatebuffer();}
               //else if (mfmode == redbox && playbackmode == off) {}
               else if (mfmode == ss4 && playbackmode == off) {ss4Signal(toneindex); updatebuffer();}
               //else if (mfmode == dialpulse && playbackmode == off) {}
               else if (mfmode == mfr2 && playbackmode == off) {playMFR2(toneindex,delayMF); updatebuffer();}
               //else if (mfmode == ac1 && playbackmode == off) {}
               //else if (mfmode == ac9 && playbackmode == off) {}
               //else if (mfmode == imtsani && playbackmode == off) {}
               //else if (mfmode == imtsdial && playbackmode == off) {}
               //else if (playbackmode == on) {} //Do nothing
             break;
            case 'B':
               toneindex = 13;
               if (mfmode == mf && playbackmode == off) {playMF(toneindex,delayMF); updatebuffer();}
               else if (mfmode == dtmf && playbackmode == off) {playDTMF(toneindex,delayMF); updatebuffer();}
               else if (mfmode == c5 && playbackmode == off) {playMF(toneindex,delayMF); updatebuffer();}
               //else if (mfmode == redbox && playbackmode == off) {}
               else if (mfmode == ss4 && playbackmode == off) {playSS4Transitseize(); updatebuffer();}
               else if (mfmode == mfr2 && playbackmode == off) {playMFR2(toneindex,delayMF); updatebuffer();} //MFR2 satellite route
               //else if (mfmode == ac1 && playbackmode == off) {}
               //else if (mfmode == ac9 && playbackmode == off) {}
               //else if (mfmode == dialpulse && playbackmode == off) {}
               //else if (mfmode == imtsani && playbackmode == off) {}
               //else if (mfmode == imtsdial && playbackmode == off) {}
               else if (playbackmode == on) {volumeUp();} //Volume Up function in Playback Mode
             break;
            case 'C':
               toneindex = 14;
               if (mfmode == mf && playbackmode == off) {playMF(toneindex,delayMF); updatebuffer();}
               else if (mfmode == dtmf && playbackmode == off) {playDTMF(toneindex,delayMF); updatebuffer();}
               else if (mfmode == c5 && playbackmode == off) {playMF(toneindex,delayMF); updatebuffer();}
               //else if (mfmode == redbox && playbackmode == off) {}
               else if (mfmode == ss4 && playbackmode == off) {ss4Signal(toneindex); updatebuffer();}
               //else if (mfmode == dialpulse && playbackmode == off) {}
               else if (mfmode == mfr2 && playbackmode == off) {playMFR2(toneindex,delayMF); updatebuffer();}
               //else if (mfmode == ac1 && playbackmode == off) {}
               //else if (mfmode == ac9 && playbackmode == off) {}
               else if (mfmode == imtsani && playbackmode == off) {imtsDisconnect(); updatebuffer();} //IMTS disconnect
               else if (mfmode == imtsdial && playbackmode == off) {imtsDisconnect(); updatebuffer();} //IMTS disconnect
               else if (mfmode == mtsdial && playbackmode == off) {playPWM(1300, 1700, 1000); updatebuffer();} //MTS disconnect
               else if (playbackmode == on) {volumeDown();} //Volume Down function in Playback Mode
             break;
            case 'D': // Signalling trunk seizure key
               toneindex = 15;
               if (mfmode == mf && playbackmode == off) {play2600(); updatebuffer();} //Play 2600 in MF mode
               else if (mfmode == dtmf && playbackmode == off) {playDTMF(toneindex,delayMF); updatebuffer();} //Play normal DTMF D tone in DTMF mode
               else if (mfmode == c5 && playbackmode == off) {playc5seize(); updatebuffer();} //Play C5 seizure in C5 mode
               else if (mfmode == redbox && playbackmode == off) {playPWM(2600, 0, 425); updatebuffer();} //Preparation wink for sending a Green Box control signal
               else if (mfmode == ss4 && playbackmode == off) {playSS4Clear(); updatebuffer();} //Play SS4 seizure in SS4 mode
               else if (mfmode == dialpulse && playbackmode == off) {play2600(); updatebuffer();} //Play 2600 in dial pulse mode
               else if (mfmode == mfr2 && playbackmode == off) {playmfr2seize(); updatebuffer();}
               else if (mfmode == ac1 && playbackmode == off) {playAC1Clear(); updatebuffer();}
               else if (mfmode == ac9 && playbackmode == off) {playPWM(2280, 0, 1000); updatebuffer();}
               else if (mfmode == imtsani && playbackmode == off) {imtsSeize(); updatebuffer();}
               else if (mfmode == imtsdial && playbackmode == off) {imtsSeize(); updatebuffer();}
               else if (mfmode == mtsdial && playbackmode == off) {playPWM(1100, 1700, 1000); updatebuffer();} //MTS connect
               else if (playbackmode == on) {toggleBacklight();} //LCD Backlight toggle function in Playback Mode
             break;        
    }
        break;

    case RELEASED:
        bufferflag = 0; //Clear bufferflag if key press resulted in a buffer update
        break;

    case HOLD:
        switch (key) {
            case '1':
                if(recordmode == on) {memrecordend(EEmemory1);} //If key held and in record mode, complete write of buffered digits to EEPROM memory
                else if(recordmode == off && playbackmode == off) {mfmode = mf;  playmodechange(); EEPROM.write(mfmodeEE, mfmode);} //Change to MF mode if not in record or playback modes
              break;
            case '2':
                if(recordmode == on) {memrecordend(EEmemory2);}
                else if(recordmode == off && playbackmode == off) {mfmode = dtmf; playmodechange(); EEPROM.write(mfmodeEE, mfmode);} //Change to DTMF mode if not in record or playback modes
              break;
            case '3':
                if(recordmode == on) {memrecordend(EEmemory3);}
                else if(recordmode == off && playbackmode == off) {mfmode = c5; playmodechange(); EEPROM.write(mfmodeEE, mfmode);} //Change to C5 mode if not in record or playback modes
              break;
            case '4':
                if(recordmode == on) {memrecordend(EEmemory4);}
                else if(recordmode == off && playbackmode == off) {mfmode = ss4; playmodechange(); EEPROM.write(mfmodeEE, mfmode);} //Change to SS4 mode if not in record or playback modes
              break;
            case '5':
                if(recordmode == on) {memrecordend(EEmemory5);}
                else if(recordmode == off && playbackmode == off) {mfmode = dialpulse; playmodechange(); EEPROM.write(mfmodeEE, mfmode);} //Change to Dial Pulse mode if not in record or playback modes
              break;
            case '6':
                if(recordmode == on) {memrecordend(EEmemory6);}
                else if(recordmode == off && playbackmode == off) {mfmode = redbox; playmodechange(); EEPROM.write(mfmodeEE, mfmode);} //Change to Red Box mode if not in record or playback modes
              break;
            case '7':
                if(recordmode == on) {memrecordend(EEmemory7);}
                else if(recordmode == off && playbackmode == off) {mfmode = mfr2; playmodechange(); EEPROM.write(mfmodeEE, mfmode);} //Change to MFR2 mode if not in record or playback modes
              break;
            case '8':
                if(recordmode == on) {memrecordend(EEmemory8);}
                else if(recordmode == off && playbackmode == off) {mfmode = ac1; playmodechange(); EEPROM.write(mfmodeEE, mfmode);} //Change to AC1 mode if not in record or playback modes
              break;
            case '9':
                if(recordmode == on) {memrecordend(EEmemory9);}
                else if(recordmode == off && playbackmode == off) {mfmode = ac9; playmodechange(); EEPROM.write(mfmodeEE, mfmode);} //Change to AC9 mode if not in record or playback modes
              break;
            case '*':
                if(recordmode == on) {memrecordend(EEmemory10);}
                else if(recordmode == off && playbackmode == off) {mfmode = imtsani; playmodechange(); EEPROM.write(mfmodeEE, mfmode);} //Change to IMTS ANI mode if not in record or playback modes
              break;
            case '0':
                if(recordmode == on) {memrecordend(EEmemory11);}
                else if(recordmode == off && playbackmode == off) {mfmode = mtsdial; playmodechange(); EEPROM.write(mfmodeEE, mfmode);} //Change to MTS Dial Pulse mode if not in record or playback modes
              break;
            case '#':
                if(recordmode == on) {memrecordend(EEmemory12);}
                else if(recordmode == off && playbackmode == off) {mfmode = imtsdial; playmodechange(); EEPROM.write(mfmodeEE, mfmode);} //Change to IMTS Dial Pulse mode if not in record or playback modes  
              break;
            case 'A':
                if (recordmode == off){ //Allow toggling playback mode while not in record mode
                    if(playbackmode == off){
                       playbackmode = on;
                       digitalWrite(ledPin, HIGH); //Light on-board LED when in playback mode
                       playlohi();
                       updateDisplay(); }
                       else {
                          playbackmode = off;
                          digitalWrite(ledPin, LOW);
                          playhilo();}
                          updateDisplay();}
              break;
            case 'B':
                if(playbackmode == off && recordmode == off){ //Allow initiating recording while not in record mode or playback mode
                memrecordstart(); //Initiate memory recording
                }
                else if(recordmode == on) {memrecordend(abortrecord); updateDisplay();} //If in record mode, abort record mode without writing EEPROM on long "B" press
              break;
            case 'C':
                if(playbackmode == off && recordmode == off){ //Allow changing duration while not in record mode or playback mode
                if (delayMF == longtone){
                  delayMF = shorttone;
                  playhilo();}
                  else {
                    delayMF = longtone;
                    playlohi();}
                    updateDisplay();
                    EEPROM.write(delaymfEE, delayMF);
                }
              break;
            case 'D':
                if(playbackmode == off && recordmode == off){  //Allow toggling alert timer beeps if not in record mode or playback mode
                  if (timermode == off){
                  timermode = on;
                  playlohi();}
                  else {
                    timermode = off;
                    playhilo();}
                    updateDisplay();
                    EEPROM.write(timerEE, timermode);   
                }
              break;
    }
    break;
  }
}
  


//Function to play MF tones in tone library. 
void playMF(uint8_t number, long duration) 
{
  if (number == 10 || number == 13) {duration = longtone;} //Trap and always use longer length for KP or KP1
  playPWM(MF_freq1[number], MF_freq2[number], duration);
}



//Function to play DTMF tones in tone library.
void playDTMF(uint8_t number, long duration) 
{
  playPWM(DTMF_freq1[number], DTMF_freq2[number], duration);
}



//Function to play MF-R2 (MFC) tones in tone library.
void playMFR2(uint8_t number, long duration) 
{
  playPWM(MFR2_freq1[number], MFR2_freq2[number], duration);
}



//Play 2600 tone with built-in completion delay, so tone will finish playing even if followed by another tone in calling routine.
void play2600() 
{
  playPWM(2600, 0, delay2600);
}



void redBox(int iterations,unsigned long delayMs, int coincount){ //Function to play redbox tones in tone library
  for (int x=0;x<coincount;x++){ //Number of coins to play
     for(int i=0;i<iterations;i++){
       playPWM(1700, 2200, delayMs);
       delay(delayMs); //wait additional delay between tones
     }
  if (x < coincount - 1) {delay(500);} //Wait 500ms between coins, unless last coin to avoid unnecessary delay
  else{return;}
  }
}



void canredBox(int iterations,unsigned long delayMs, int coincount){ //Function to play redbox tones in tone library
  for (int x=0;x<coincount;x++){ //Number of coins to play
     for(int i=0;i<iterations;i++){
       playPWM(2200, 0, delayMs); //Canadian coin box tones
       delay(delayMs); //wait additional delay between tones
     }
  if (x < coincount - 1) {delay(500);} //Wait 500ms between coins, unless last coin to avoid unnecessary delay
  else{return;}
  }
}



void playlohi() //Function to play short low to high indicator beep
{
  playPWM(1300, 0, 100);
  playPWM(1700, 0, 100);
}



void playhilo() //Function to play short high to low indicator beep
{
  playPWM(1700, 0, 100);
  playPWM(1300, 0, 100);
}



void playlolong() //Function to play longer duration low indicator beep
{
  playPWM(1300, 0, 500);
}



void playhilong() //Function to play longer duration high indicator beep
{
  playPWM(1700, 0, 500);
}



void playmodechange() //Function to play mode change beep and LED flash
{
  digitalWrite(ledPin, HIGH);
  playPWM(1000, 0, 750);
  digitalWrite(ledPin, LOW);
  updateDisplay();
}



void startbeeps() //Function to play reset and error indicator beeps
{
    for(int x = 0; x < 3; x++) {
    playPWM(2600, 0, 50);
    delay(50);}
}



void updatebuffer() //Function to update keybuffer on recordable tone keypress
{
  bufferflag = 1; //Set flag to indicate buffer was updated (cleared on key release)
  updateDisplay();
  if (bufferpointer >= 33 && recordmode == on){delay(delayMF); startbeeps(); startbeeps();} //Play error beeps if in record mode and memory capacity exceeded
  if (bufferpointer < 33 && recordmode == on){delay(delayMF); playPWM(2800, 0, 50);} //If in record mode, play signal beep after entered tone as a record mode reminder
  if (bufferpointer == 34){return;}  //Don't attempt to update buffer past keybuffer array size
  keybuffer[bufferpointer] = toneindex; //Set keybuffer location to value of current key's tone array index
  bufferpointer = ++bufferpointer; //Increment the keybuffer pointer for next write
  keybuffer[bufferpointer] = eofmarker; //Set the location after the current tone array index to end of sequence marker
  //for(int x = 0; x < 35; x++) { //Serial debug statements to dump current contents of keybuffer to serial port
  //Serial.print(keybuffer[x]); //debug
  //Serial.print(" ");} //debug
  //Serial.println(); //debug
}



void initbuffer() //Function to initialize the keybuffer, normally when entering record mode as it is still updated in normal mode
{
  keybuffer[0] = mfmode; //set the first element in the buffer to the current mfmode, MF or DTMF
  keybuffer[1] = eofmarker; //Set the first location after the tone mode to the end of sequence marker
  bufferpointer = 1; //Set to buffer pointer to the first location after the stored tone mode
}



void eeplay(int readaddress)  //Function to play the tone sequence stored in EEPROM
{  
  int tempreadaddress = readaddress; //Temporary variable for calculating LCD cursor position for line wrap
  lcd.clear(); //Clear the LCD
  lcd.setCursor(0, 0); //Set the cursor to the home position for display of played digits
  
     if(EEPROM.read(readaddress) != eofmarker){ //Check for uninitialized empty memory location
      mfmodeplayback = EEPROM.read(readaddress); //Get tone mode from first location of base address
      readaddress = ++readaddress; //Go to the next address
      if(EEPROM.read(readaddress) == eofmarker){lcd.print("<<MEMORY EMPTY>>");} //Check for cleared memory location
     }
     else{lcd.print("<<MEMORY EMPTY>>");} //Print for uninitialized empty memory location
      
     while(EEPROM.read(readaddress) != eofmarker){ //Keep playing until end of sequence marker detected
      toneindex = EEPROM.read(readaddress);
      if(readaddress - tempreadaddress == 17) {lcd.setCursor(0, 1);} //Wrap to the second line if more than 16 characters played back
      lcd.print(keylist[toneindex]); //Display the retrieved digit
      if(mfmodeplayback == mf){
        if(toneindex == 15) {play2600(); delay(delay2600);} //Trap stored 2600 key and play with extra delay for seizure
        else{
         playMF(toneindex, delayMF); //Play MF digit
         delay(delayMF); //Wait for inter-digit delay
        }
      }
      if(mfmodeplayback == dtmf){
       playDTMF(toneindex, delayMF); //Play DTMF digit
       delay(delayMF); //Wait for inter-digit delay
      }
      if(mfmodeplayback == c5){
       if(toneindex == 15) {playc5seize(); delay(delay2600);} //Trap stored C5 Clear Forward code and play with added delay
       else{
        playMF(toneindex, delayMF); //Play C5 MF digit
        delay(delayMF); //Wait for inter-digit delay
       }
      }
      if(mfmodeplayback == ss4){
        if(toneindex == 10) {playSS4Termseize();delay(delay2600);} //Trap stored SS4 Terminal Seizure code and play with added delay
        else if(toneindex == 13) {playSS4Transitseize();delay(delay2600);} //Trap stored SS4 Transit Seizure code and play with added delay
        else if(toneindex == 15) {playSS4Clear();delay(delay2600);} //Trap stored SS4 Clear Forward code and play with added delay
        else{ss4Signal(toneindex); delay(100);} //Otherwise, data is an SS4 binary digit sequence - play with 100ms delay between digits, per CCITT
        }
      if(mfmodeplayback == dialpulse){
        if(toneindex == 15) {play2600(); delay(delay2600);} //Trap stored 2600 key and play with extra delay for seizure
        else{pulse(toneindex);} //Otherwise process stored digit as 2600 dial pulses
        }
      if(mfmodeplayback == redbox){
        if(toneindex == 15) {playPWM(2600, 0, 425); delay(850);} //Trap stored D key and play long 2600Hz flash for Green Box tone prep
        else if(toneindex == 1) {redBox(1,66,1);} //Play nickel once
        else if(toneindex == 2) {redBox(2,66,1);} //Play dime once
        else if(toneindex == 3) {redBox(5,33,1);} //Play quarter once
        else if(toneindex == 4) {playMF(2,700);} //Operator Coin Collect Green Box tone (MF "2")
        else if(toneindex == 5) {playPWM(1100, 1700, 700);} //Operator Coin Return Green Box tone (MF "KP")
        else if(toneindex == 6) {playMF(14,700);} //Operator Ringback Green Box tone (MF "ST3P")
        else if(toneindex == 7) {playMF(8,700);} //Operator Released Green Box tone (MF "8")e
        else if(toneindex == 8) {playMF(0,700);} //Operator Attached Green Box tone (MF "0")
        else if(toneindex == 9) {playMF(11,700);} //Combined operator Coin Collect and Operator Released Green Box tone (MF "ST")
        else if(toneindex == 10) {canredBox(1,60,1);} //Canadian Red Box nickel tone
        else if(toneindex == 0) {canredBox(2,60,1);} //Canadian Red Box dime tones
        else if(toneindex == 11) {canredBox(5,33,1);} //Canadian Red Box quarter tones
        delay(500); //Wait 500ms between coins or Green Box tones
        }
      if(mfmodeplayback == mfr2){
        if(toneindex == 15) {playmfr2seize(); delay(1250);} //Trap stored 2280 key and play with extra delay for seizure
        else{
         playMFR2(toneindex, delayMF); //Play MF digit
         delay(delayMF); //Wait for inter-digit delay
         }
        }
      if(mfmodeplayback == ac1){
        if(toneindex == 15) {playAC1Clear(); delay(2000);} //Trap stored Clear Forward key and play AC1 Clear Forward sequence with extra delay between clear and seize
        else if(toneindex == 10) {playPWM(750, 0, 100); delay(3000);} //Trap * and play seizure tone (3 seconds, based on old recording)
        else{pulseAC1(toneindex);} //Otherwise process stored digit as 600Hz dial pulses
        }
      if(mfmodeplayback == ac9){
        if(toneindex == 15) {playPWM(2280, 0, 1000); delay(1000);} //Trap stored 2280 key and play with extra delay for Clear Forward
        else if(toneindex == 10) {playPWM(2280, 0, 95); delay(1000);} //Trap * and play seizure tone
      //Trap # and play end of dialing tone
        else{pulseAC9(toneindex);} //Otherwise process stored digit as 2280 dial pulses
        }
      if(mfmodeplayback == imtsani){
        if(toneindex == 14) {imtsDisconnect();} //Trap stored C key and play IMTS disconnect tone
        else if(toneindex == 15) {imtsSeize();} //Trap stored D key and play IMTS seizure sequence
        else{imtsANI(toneindex);} //Otherwise process stored digit as IMTS ANI mobile identifier pulses
        }
      if(mfmodeplayback == imtsdial){
        if(toneindex == 14) {imtsDisconnect();} //Trap stored C key and play IMTS disconnect tone
        else if(toneindex == 15) {imtsSeize(); delay(1500);} //Trap stored D key and play IMTS seizure sequence, followed by delay
        else{imtsDial(toneindex);} //Otherwise process stored digit as IMTS Dial Pulse digit
        }
      if(mfmodeplayback == mtsdial){
        if(toneindex == 13) {} //Trap B key
        else if(toneindex == 14) {playPWM(1300, 1700, 1000); delay(3000);} //Trap stored C key - play MTS disconnect with added 1 second delay
        else if(toneindex == 15) {playPWM(1100, 1700, 1000); delay(3000);} //Trap stored D key - Play MTS connect with added 3 second delay for dial tone
        else{mtsDial(toneindex);} //Otherwise process stored digit as MTS Dial Pulse digit
        }
      //Serial.print(EEPROM.read(readaddress)); //debug to print played tone index to serial port
      //Serial.print(" "); //debug to print played tone index to serial port
      readaddress = ++readaddress; //Index to next memory location
      }
      //Serial.println(); //debug to print played tone index to serial port
      //Serial.println(); //debug to print played tone index to serial port
}



void memrecordstart() //Start tone sequence memory recording mode
  {
if(playbackmode == off){ //No recording allowed in playback mode
  if(recordmode == off){
    playlolong(); //Play recording start tone
    recordmode = on;
    updateDisplay();
    digitalWrite(ledPin, HIGH); //Light on-board LED when in record mode
    initbuffer();} //Initialize the RAM keybuffer to store key sequence before writing to EEPROM
    }
}



void memrecordend(int memlocation) //Complete tone sequence memory recording
{
if(recordmode == on && memlocation != abortrecord){
  recordmode = off;
  updateDisplay();
  digitalWrite(ledPin, LOW);
  if(bufferflag){keybuffer[--bufferpointer] = eofmarker;} //Remove keypress pressed for save from buffer, if memory save keypress did a buffer update
  int x = 0; //Start write of keybuffer to EEPROM
  while(keybuffer[x] != eofmarker){
    EEPROM.write(memlocation, keybuffer[x]);
    memlocation = ++memlocation;
    x = ++x;}
    EEPROM.write(memlocation, eofmarker); //Finish up write with end of sequence marker in EEPROM
    //dumpEE(); //debug dump of EE memory to serial monitor
    playhilong();
    }
    else if(recordmode == on && memlocation == abortrecord){ //Abort recording and exit record mode without EEPROM write
      recordmode = off;
      digitalWrite(ledPin, LOW);
      startbeeps();
      startbeeps();
      }
}



void callback_Reminder() //Callback function for idle timer fire
{
    for (int x = 0; x < 6; x++){ //Play warning beeps that power was left on
      playlohi();
    }
    for (int i = 0; i < 10; i++){ //Flash front panel LED repeatedly, preserving the current LED state
      if (digitalRead(ledPin) == HIGH) {digitalWrite(ledPin, LOW);} else{digitalWrite(ledPin, HIGH);}
      delay(50);
      if (digitalRead(ledPin) == HIGH) {digitalWrite(ledPin, LOW);} else{digitalWrite(ledPin, HIGH);}
      delay(50);
      }
}



//Play C5 Clear-Forward/Seize sequence
void playc5seize() //Play CCITT #5 clear forward and seizeure sequence
{
  playPWM(2400, 2600, 150); //Clear Forward - 125ms nominal detection time per CCITT spec (125ms +- 25ms)
  delay(20); //No spec, but recommended by various annecdotal accounts by phreaks
  playPWM(2400, 0, 150); //Seizing - 40ms nominal detection time per CCITT spec (40ms +- 10ms) - 150ms recommended by phreak accounts
}



//Play mfr2 Clear-Forward/Seize sequence
void playmfr2seize() //Play MFR2 clear forward and seizeure sequence
{
  playPWM(2280, 0, 1250); //Clear Forward - Seize at 2280Hz
  delay(1000); //No spec, but recommended by various annecdotal accounts by phreaks
  playPWM(2280, 0, 100); //Seizing - Recommended by phreak accounts
}



// Play SS4 digit signalling:
void ss4Signal(int signal)
{
 for(int i=0; i<=3; i++){
   (ss4Freqs[signal][i]) ? playPWM(ss4Tone[1],0 , 35) : playPWM(ss4Tone[0], 0, 35);
   delay(35); //Wait 35ms inter-element spacing, per CCITT spec
   }
}



//Play SS4 Clear Forward
void playSS4Clear()
{
  playPWM(2040, 2400, 150);
  playPWM(2040, 0, 350);
}



//Play SS4 Terminal Seizing
void playSS4Termseize()
{
  playPWM(2040, 2400, 150);
  playPWM(2040, 0, 100);
}



//Play SS4 Transit Seizing
void playSS4Transitseize()
{
  playPWM(2040, 2400, 150);
  playPWM(2400, 0, 100);
}



// pulse dialing mode
void pulse(int signal)
{
    if(signal == 0){ signal = 10;}
    for(int i=0; i<signal; i++){
      if (digitalRead(ledPin) == HIGH) {digitalWrite(ledPin, LOW);} else{digitalWrite(ledPin, HIGH);} // pulsing LED
      playPWM(2600, 0, 66);
      if (digitalRead(ledPin) == HIGH) {digitalWrite(ledPin, LOW);} else{digitalWrite(ledPin, HIGH);}
      delay(34);}
    delay(500); // no new digit accepted until after this time
}



// AC1 pulse dialing mode
void pulseAC1(int signal)
{
    if(signal == 0){ signal = 10;}
    for(int i=0; i<signal; i++){
      if (digitalRead(ledPin) == HIGH) {digitalWrite(ledPin, LOW);} else{digitalWrite(ledPin, HIGH);} // pulsing LED
      playPWM(750, 0, 66);
      if (digitalRead(ledPin) == HIGH) {digitalWrite(ledPin, LOW);} else{digitalWrite(ledPin, HIGH);}
      delay(34);}
    delay(1000); // no new digit accepted until after this time (1 second between digits, based on old recording)
}



//AC1 Clear Forward tone sequence, from an old 2VF AC1 78 RPM recording of reverse subscriber hangup, as heard by an operator, as well as old enthusiast articles
void playAC1Clear()
{
    playPWM(750, 0, 2000); //Play 1500ms of 750Hz (Somewhat longer than Reverse Clear timing in old recording (1.5 sec). Based on old article)
    playPWM(600, 0, 800); //Play 100ms of 600Hz (Much longer than Reverse Clear timing in old recording (100ms). Based on old article)
}



// AC9 pulse dialing mode
void pulseAC9(int signal)
{
    if(signal == 0){ signal = 10;}
    for(int i=0; i<signal; i++){
      if (digitalRead(ledPin) == HIGH) {digitalWrite(ledPin, LOW);} else{digitalWrite(ledPin, HIGH);} // pulsing LED
      playPWM(2280, 0, 66);
      if (digitalRead(ledPin) == HIGH) {digitalWrite(ledPin, LOW);} else{digitalWrite(ledPin, HIGH);}
      delay(34);}
    delay(500); // no new digit accepted until after this time
}



//IMTS seizure sequence
void imtsSeize()
{
    imts_ani_parity = 0; /* Reset to odd parity */
    playPWM(2150, 0, 350); //Send IMTS guard tone
    playPWM(1633, 0, 50); //Send IMTS Connect tone
    playPWM(2150, 0, 2000); //Send IMTS guard tone waiting for seizure from base station
}



// IMTS ANI pulse mode
void imtsANI(int signal)
{
    if(signal == 0){ signal = 10;}
    for(int i=1; i<=signal; i++){
      if (digitalRead(ledPin) == HIGH) {digitalWrite(ledPin, LOW);} else{digitalWrite(ledPin, HIGH);} // pulsing LED
      playPWM(1633, 0, 25); //Play connect tone for dial pulse
      if (digitalRead(ledPin) == HIGH) {digitalWrite(ledPin, LOW);} else{digitalWrite(ledPin, HIGH);}
      if (!imts_ani_parity) {delay(25);} //If pulse is odd, just delay with no tone, to generate parity indication
        else{playPWM(2150, 0, 25);} //If pulse is even, play guard tone, to generate parity indication
        imts_ani_parity = !imts_ani_parity; //Toggle parity flag
      if(i == signal){
        if(!imts_ani_parity) {delay(190);} //If last pulse is odd, just delay inter-digit time
           else {playPWM(2150, 0, 190);} //If last pulse is even, play guard tone for the inter-digit interval
        imts_ani_parity = !imts_ani_parity; //Toggle parity flag
      }
    }
}



// IMTS dial pulse mode
void imtsDial(int signal)
{
    if(signal == 0){ signal = 10;}
    playPWM(2150, 0, 250); //Play guard tone at the start of each pulse, as the dial is pulled off-normal
    for(int i=0; i<signal; i++){
      if (digitalRead(ledPin) == HIGH) {digitalWrite(ledPin, LOW);} else{digitalWrite(ledPin, HIGH);} // pulsing LED
      playPWM(1633, 0, 66);
      if (digitalRead(ledPin) == HIGH) {digitalWrite(ledPin, LOW);} else{digitalWrite(ledPin, HIGH);}
      playPWM(2150, 0, 34);}
    delay(500); // no new digit accepted until after this time
}



// IMTS disconnect
void imtsDisconnect()
{
    for(int i=0; i<15; i++){ //15-50ms bursts (20pps) = 750ms
      playPWM(1336, 0, 25);
      playPWM(2150, 0, 25);}
}



// MTS dial pulse mode
void mtsDial(int signal)
{
    if(signal == 0){ signal = 10;}
    playPWM(1100, 1700, 250); //Play the Connect tones at the start of each pulse, as the dial is pulled off-normal
    for(int i=0; i<signal; i++){
      if (digitalRead(ledPin) == HIGH) {digitalWrite(ledPin, LOW);} else{digitalWrite(ledPin, HIGH);} // pulsing LED
      playPWM(1500, 1700, 66);
      if (digitalRead(ledPin) == HIGH) {digitalWrite(ledPin, LOW);} else{digitalWrite(ledPin, HIGH);}
      playPWM(1100, 1700, 34);}
    delay(500); // no new digit accepted until after this time
}



//Play PWM-generated tones
void playPWM(float freq1, float freq2, unsigned long length)
{
  notePlayer.setFrequency(0,freq1); //Set the new Tone 1 frequency
  notePlayer.setFrequency(1,freq2); //Set the new Tone 2 frequency
  notePlayer.resume(); //Turn on PWM interrupts
  delay(length); //Wait for the tone duration
  notePlayer.suspend(); //Turn off PWM interrupts for better response time at new, higher sampling rate (40KHz)
  notePlayer.setFrequency(0,0); //Set for silence - keep PWM running for pop/click elimination on tone changes
  notePlayer.setFrequency(1,0); //Set for silence - keep PWM running for pop/click elimination on tone changes
}


void volumeDown() //Function to step volume down (increase attenuation) and save to EE
{
  if (volume_atten == 238) {startbeeps(); return;} //Limit reduced volume to audible value
  volume_atten = volume_atten + 17; notePlayer.setAtten(volume_atten); playhilo(); EEPROM.write(volattenEE, volume_atten); //Step down volume and save to EE
  updateDisplay();
}



void volumeUp() //Function to step volume up (decrease attenuation) and save to EE
{
  if (volume_atten == 0) {startbeeps(); return;}
  volume_atten = volume_atten - 17; notePlayer.setAtten(volume_atten); playlohi(); EEPROM.write(volattenEE, volume_atten); //Step up volume and save to EE
  updateDisplay();
}


void toggleBacklight() //Function to toggle LCD backlight
{
  if (backlight == on){backlight = off; playhilo();} else{backlight = on; playlohi();}
  EEPROM.write(backlightEE, backlight);
  digitalWrite(backlightPin, backlight);
  updateDisplay();
}


void updateDisplay() //Subroutine to refresh the entire display
{
  String modestring; //Temporary storage for current operating mode
  
lcd.clear(); //Clear the entire display before each update
  if(recordmode == off && playbackmode == off){modestring = opmode[mfmode];} //Set display to current tone mode
  if(playbackmode == on){modestring = "PLAYBACK MODE   ";} //If in playback mode, display that
  if(recordmode == on){modestring = "RECORD MODE     ";} //If in record mode, play that
  lcd.setCursor(0, 0); //Set LCD cursor to the beginning of the first line
  lcd.print(modestring); //Send current operating mode to display
  
lcd.setCursor(0, 1); //Set the LCD cursor to the beginning of the second line
lcd.print(delayMF); lcd.print("ms VOL="); lcd.print((255-volume_atten)/17); //Display the current MF timing and volume level

lcd.setCursor(13, 1); //Set the LCD cusor to the position for display of the key pressed
lcd.print(keylist[toneindex]); //Translate toneindex to key and display to LCD - one digit only

if(timermode){ //Display an indicator on last character of second line, if reminder beep is turned on
lcd.setCursor(15, 1); //Set LCD cursor to last character of second line
lcd.print((char)255);} //Print a character block of solid pixels as reminder beep indicator
}


//void dumpEE() //Function to debug EEPROM - dump memory contents to serial port
//{
//  Serial.println();
//  for (int i = 0; i < 12; i++){
//    for(int x = 0; x < 35; x++) {
//  //int address = (34*i)+x;
//  Serial.print(EEPROM.read((34*i)+x));
//  Serial.print(" ");}
//  Serial.println();}
//  Serial.println();
//}
