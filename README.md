# Arduino-Multimode-Blue-Box-
A "Blue Box" design that emulates classic Blue Box tones, plus 12 other historical, tone modes

https://www.instructables.com/id/Arduino-12-mode-Blue-Box-Introduction/

Presented here is an Arduino-based "Blue Box". It produces the "traditional" Blue Box 2600Hz tone and MF (multi-frequency) tones, but does much more! It also produces 12 tone signalling systems used by phone phreaks to hack other more exotic system in the US and overseas, including early pre-cellular mobile telephone systems from the 50s, 60s, and 70s,

The box has 12 non-volatile tone sequence storage memories that can store and play back up to 32 tones each. Each memory saves the tone mode as well. All operating parameters, such as tone duration, volume level, backlight status, reminder beep status, and current tone mode are saved to non-volatile EEPROM memory automatically and are restored when the box is powered up. EEPROM errors are automatically detected and corrected when the box is powered on.

An optional LCD provides full information of the operating status of the box and enhances the appearance and user-friendliness of the unit.

This box features sine-wave tone generation using PWM wave-table lookup techniques. It sounds much better than generating the tones using the two-pin square wave output techniques utilized by the standard Arduino "Tone" library.

I designed this new blue box, as I was out of the PCB boards for my older PIC_based blue box design and was looking for a way for others to easily construct a blue box for use with my ProjectMF system, using inexpensive and commonly available parts. This design is easily the most full-featured and technically sophisticated blue box design available. I am a telecommunications and software engineer and took great pains to be sure all of the tone modes are accurately represented. The code has been thoroughly debugged and well-tested.

The following modes are supported. Note that ALL of these modes are obsolete (well, not DTMF!) and no longer work on "real" public telephone systems, except for private systems (like ProjectMF) set up for historical purposes. They are included to preserve the sounds of these old tone signalling systems:

MF (R1) - The 2600Hz/Multi-frequencysystem that ran Ma Bell's long distance network back in the day

DTMF (Touch-Tone, Autovon) - Used on almost every land line phone. A-B-C-D keys used to set call priority on the old Autovon military phone system.

CCITT #5 (C5, SS5) - Same MF tones as R1 (with a few additional tone pairs for special routing), but uses a different tone sequence for international trunk clear/seize.

CCITT #4 (C4, SS4) - Unusual 4-bits/digit tone encoding. Used in the UK and other European countries.

2600 Dial Pulse - Same method used by Joybubbles (Joe Engressia), Captain Crunch (John Draper), and Bill from New York (Bill Acker) to whistle free calls.

Pay Phone Modes - Simulates both US and Canadian nickel/dime/quarter payphone coin drop tones (Red Box). Also simulates US pay phone remote operator control tones (Green Box) and 2600Hz prefix control flash.

R2 (MFC) - Unique forward multi-frequency tone pairs, 2280Hz clear/seize tone, as used in the UK. Replaced the older AC1/AC9 UK dial pulse systems.

AC1- Old UK tone dial pulse trunk signalling, as used by very early UK telephone "enthusiasts".

AC9 - Newer UK dial pulse trunk signalling, as used by early UK telephone "enthusiasts".

MTS (Mobile Telephone Service) - Pre-cellular, pre-IMTS mobile phone service tone signalling and dialing

IMTS ANI (Improved Mobile Telephone Service ANI ) - Newer pre-cellular mobile authentication spoofing

IMTS Digit Dialing - Improved Mobile Telephone Service (pre-cellular) digit dialing,
