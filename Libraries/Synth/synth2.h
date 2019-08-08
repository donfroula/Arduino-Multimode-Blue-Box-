#ifndef _SYNTH
#define _SYNTH
//*************************************************************************************
//  Arduino Tone Generator
// Generates four simultaneous square/sine wave tones at any relative amplitude
//*************************************************************************************
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include "tables2.h"

//No explicit DIFF mode needed, since either A or B output on 
//Atmega 32U4 has a complimentary output pin that can be used
//on both CHA and CHB. However, DIFF mode included in case normal
//bits can be used (one from each channel, for pin flexibility).
#define DIFF_10_13 1  
#define CHB_9 2
#define CHB_10 3
#define CHB_DIFF_9_10 4
#define CHA_5 5
#define CHA_13 6
#define CHA_DIFF_5_13 7

#define FS 40000.0                            //-Rate must be evenly divisable into 16,000,000. Higher rates have worse frequency error, but better resolution. Not amy issue with 32-bit phase accumulators.
                                              //-Must be at least twice the highest frequency. Frequency resolution is FS/(2^32). (2^32) = the size of the phase accumulator.
#define SET(x,y) (x |=(1<<y))		        	  	//-Bit set/clear macros
#define CLR(x,y) (x &= (~(1<<y)))       			// |
#define CHK(x,y) (x & (1<<y))           			// |
#define TOG(x,y) (x^=(1<<y))            			//-+

volatile unsigned long PCW[4] = {
  0, 0, 0, 0};			            //-Wave phase accumulators - Index into wave table (upper 8 bits of 32)
volatile unsigned long FTW[4] = {
  0, 0, 0, 0};                  //-Wave frequency tuning words - Actual frequency being produced
volatile unsigned int wavs[4];  //-Wave table selector [address of wave table in memory]

volatile unsigned char output_mode;

volatile unsigned char VOL = 0; //Volume attenuation

//*********************************************************************************************
//  Audio driver interrupt
//*********************************************************************************************

SIGNAL(TIMER1_COMPA_vect)
{
  //---------------------------------------------------------
  //  Audio mixer
  //---------------------------------------------------------
  //pgm_read_byte reads a byte from the wave table in program memory. The function requires the memory address of the byte to be retrieved.
  //Here, the start address of the wave table array, wavs[X], is added to the most-significant 8 bits of the current value of the (32-bit phase accumulator + 32-bit tuning word).
  //This is the address of the retrieved wave table value.
  //The wave table signed 256-bit value is then multiplied by a 256-bit unsigned volume adjustment constant and divided by 256 to render a level-adjusted wave table sample.
  //The volume adjusted waves are summed togather and divided by 4 to render a volume-adjusted  single PWM duty cycle sample value.
   OCR4A = OCR4B = 127 +  //Start at 127 or 2.5 volts as zero level after capacitor coupling the output. Output voltage swings 5 volts p-p.
    ((
    (((signed char)pgm_read_byte(wavs[0] + ((PCW[0]+=FTW[0]) >> 24)) * VOL) >> 8) +
    (((signed char)pgm_read_byte(wavs[1] + ((PCW[1]+=FTW[1]) >> 24)) * VOL) >> 8) +
    (((signed char)pgm_read_byte(wavs[2] + ((PCW[2]+=FTW[2]) >> 24)) * VOL) >> 8) +
    (((signed char)pgm_read_byte(wavs[3] + ((PCW[3]+=FTW[3]) >> 24)) * VOL) >> 8)
    ) >> 2);

}

class synth
{
private:

public:

  synth()
  {
  }

  //*********************************************************************
  //  Startup default Timer 4 used for Atmega 32U4 board, as Timer 2 is missing
  //*********************************************************************

  void begin()
  {
    output_mode=CHA_DIFF_5_13;
    TCCR1A = 0x00;                                  //-Start audio interrupt
    TCCR1B = 0x09;
    TCCR1C = 0x00;
    OCR1A=16000000.0 / FS;			                //-Auto sample rate
    SET(TIMSK1, OCIE1A);                            //-Start audio interrupt
    sei();                                          //-+

	//Default to CHA_DIFF_5_13 mode
    TCCR4A = 0x42;                                  //8-bit audio PWM - Enable PWM on CHA, Enable normal and complimentary outputs on CHA.
    TCCR4B = 0x02;                                  //Enable PWM OCR4A comparator on CHA
    OCR4A = 127;                                    //Initialize output compare toggle at zero voltage from wave table
    SET(DDRC, 7);				                    //Enable PWM pins - CHA Normal Pin (13) - differential output on both normal and complimentary pins.
    SET(DDRC, 6);                                   //Enable PWM pins - CHA Complimentary Pin (5) - differential output on both normal and complimentary pins.
  }

  //*********************************************************************
  //  Startup selecting various output modes
  //*********************************************************************

  void begin(unsigned char d)
  {
  //Timer 1 is used for PWM audio clock
    TCCR1A = 0x00;                                  //-Start audio interrupt
    TCCR1B = 0x09;
    TCCR1C = 0x00;
    OCR1A=16000000.0 / FS;			                //-Auto sample rate
    SET(TIMSK1, OCIE1A);                            //-Start audio interrupt
    sei();                                          //-+

    output_mode=d;

    switch(d)
    {
	
	
//No explicit DIFF mode needed, since either A or B output on 
//Atmega 32U4 has a complimentary output pin that can be used
//on both CHA and CHB. However, DIFF mode included so both normal
//pins can be used (one from each channel), for pin flexibility).

    case DIFF_10_13:	                              //Differential signal on CHA and CHB Normal pins only (13/10). 43U4 does not allow complementary bits to be on in opposite (set/clear) modes.
	  TCCR4A = 0xB3;                                  //8-bit audio PWM - Enable PWM on CHA and CHB, Enable normal outputs only on CHA and CHB, but CHA sets bit, CHB clears bit
      TCCR4B = 0x03;                                  //Enable PWM OCR4A and OCR4B comparator on CHA and CHB
      OCR4A = OCR4B = 127;                            //Initialize output compare toggle at zero voltage from wave table
      SET(DDRC, 7); SET(DDRB, 6);				      //Enable PWM pins - CHA Normal Pin (13) and CHB Normal Pin (10)
      break;

    case CHB_9:                                       //Single-ended output on pin 9.
	  TCCR4A = 0x11;                                  //8-bit audio PWM - Enable PWM on CHB, Enable normal and complimentary outputs on CHB.
      TCCR4B = 0x01;                                  //Enable PWM OCR4B comparator on CHB
      OCR4B = 127;                                    //Initialize output compare toggle at zero voltage from wave table
      SET(DDRB, 5);                                   //Enable PWM pins - CHB Complimentary Pin (9) - Use with ground reference
	  break;
	  
	 case CHB_10:                                     //Single-ended output on pin 10.
	  TCCR4A = 0x11;                                  //8-bit audio PWM - Enable PWM on CHB, Enable normal and complimentary outputs on CHB.
      TCCR4B = 0x01;                                  //Enable PWM OCR4B comparator on CHB
      OCR4B = 127;                                    //Initialize output compare toggle at zero voltage from wave table
      SET(DDRB, 6);		                              //Enable PWM pins - CHB Normal Pin (10) - Use with ground reference
      break;
	  
	 case CHB_DIFF_9_10:                              //Differential output on on pins 9 and pin 10
	  TCCR4A = 0x11;                                  //8-bit audio PWM - Enable PWM on CHB, Enable normal and complimentary outputs on CHB.
      TCCR4B = 0x01;                                  //Enable PWM OCR4B comparator on CHB
      OCR4B = 127;                                    //Initialize output compare toggle at zero voltage from wave table
      SET(DDRB, 6);		                              //Enable PWM pins - CHB Normal Pin (10) - differential output on both normal and complimentary pins.
      SET(DDRB, 5);                                   //Enable PWM pins - CHB Complimentary Pin (9) - differential output on both normal and complimentary pins.
	  break;
	  
     case CHA_5:                                      //Single-ended output on pin 5.
	  TCCR4A = 0x42;                                  //8-bit audio PWM - Enable PWM on CHA, Enable normal and complimentary outputs on CHA.
      TCCR4B = 0x02;                                  //Enable PWM OCR4A comparator on CHA
      OCR4A = 127;                                    //Initialize output compare toggle at zero voltage from wave table
      SET(DDRC, 6);                                   //Enable PWM pins - CHA Complimentary Pin (5) - Use with ground reference
	  break;
	
	 case CHA_13:                                     //Single-ended output on pin 13.
	  TCCR4A = 0x42;                                  //8-bit audio PWM - Enable PWM on CHA, Enable normal and complimentary outputs on CHA.
      TCCR4B = 0x02;                                  //Enable PWM OCR4A comparator on CHA
      OCR4A = 127;                                    //Initialize output compare toggle at zero voltage from wave table
      SET(DDRC, 7);				                      //Enable PWM pins - CHA Normal Pin (13) - Use with ground reference
	  break;
	
     case CHA_DIFF_5_13:                              //Differential output on on pins 5 and pin 13
     default:
      output_mode=CHA_DIFF_5_13;                      
      TCCR4A = 0x42;                                  //8-bit audio PWM - Enable PWM on CHA, Enable normal and complimentary outputs on CHA.
      TCCR4B = 0x02;                                  //Enable PWM OCR4A comparator on CHA
      OCR4A = 127;                                    //Initialize output compare toggle at zero voltage from wave table
      SET(DDRC, 7);				                      //Enable PWM pins - CHA Normal Pin (13) - differential output on both normal and complimentary pins.
      SET(DDRC, 6);                                   //Enable PWM pins - CHA Complimentary Pin (5) - differential output on both normal and complimentary pins.
	  break;
    }
  }



  //*********************************************************************
  //  Setup wave
  //*********************************************************************

  void setWave(unsigned char voice)
  {
      wavs[voice] = (unsigned int)SinTable;
  }


  //*********************************************************************
  //  Set frequency direct
  //*********************************************************************

  void setFrequency(unsigned char voice,float f)
  {
    //32-bit phase accumulator provides 0.000009313 Hz. resolution at 40KHz sampling rate (FS/(2^32))
    //FTW[voice]=f/(FS/4294967295.0); //frequency/(sample_rate/max_32bit_count)
    //f * 1/(40,000/4294967295.0) = f * 107,374.182375
    FTW[voice]=f * 107374.182375;

  }


  
  //*********************************************************************
  //  Set volume attenuation
  //*********************************************************************

  void setAtten(unsigned char volume)
  {
    VOL = 255 - volume;
  }

  //*********************************************************************
  //  Suspend/resume synth
  //*********************************************************************

  void suspend()
  {
    CLR(TIMSK1, OCIE1A);                            //-Stop audio interrupt
  }
  void resume()
  {
    SET(TIMSK1, OCIE1A);                            //-Start audio interrupt
  }

};

#endif

