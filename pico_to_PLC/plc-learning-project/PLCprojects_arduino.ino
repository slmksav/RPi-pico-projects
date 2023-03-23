/*
 * pico_runtime.ino
 * Beremiz runtime for Raspberry Pi Pico platform
 * Copyright 2020 Benoit BOUCHEZ
 * 
 * Offered to the public under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser
 * General Public License for more details.
 *
 * This code is made available on the understanding that it will not be
 * used in safety-critical situations without a full and competent review.
 */

#include "iec_types_all.h"
#include "config.h"

/* Functions declared in plc_ioconfig.cpp */
void ConfigurePLCIO (void);
void AcquirePLCInputs (void);
void UpdatePLCOutputs (void);

// runtime system variables
unsigned long LastMillis;
unsigned long TickCounter;
IEC_TIME __CURRENT_TIME;

// These two prototypes are not in the config.h file...
extern "C" void config_init__(void);
extern "C" void config_run__(unsigned long tick);

void setup() 
{ 
  ConfigurePLCIO();

  config_init__();

  __CURRENT_TIME.tv_msec=0;
  __CURRENT_TIME.tv_sec=0;
  LastMillis=millis();
}

void loop() 
{
  unsigned long CurrentMillis;
  unsigned long ElapsedMillis;
  
  // Update current IEC time
  CurrentMillis = millis();
  // Check that millisecond counters has not wrapped around
  if (CurrentMillis < LastMillis)
  {  // Counter has wrapped around (happens every 49 days...)
	ElapsedMillis = 0;		// TODO : do this better to take overflow into account
  }
  else ElapsedMillis = CurrentMillis-LastMillis;
  LastMillis = CurrentMillis;

  __CURRENT_TIME.tv_msec += ElapsedMillis;
  // if loop() executes in more than 1000 ms, that would mean a serious problem in the PLC code...
  // but let's stay safe and keep seconds counter correct with a while loop rather than
  // a simple substraction
  while (__CURRENT_TIME.tv_msec >= 1000) 
  {
    __CURRENT_TIME.tv_msec -= 1000;   
    __CURRENT_TIME.tv_sec += 1;
  }
  
  AcquirePLCInputs();

  config_run__ (TickCounter);
  TickCounter++;

  UpdatePLCOutputs();
}
