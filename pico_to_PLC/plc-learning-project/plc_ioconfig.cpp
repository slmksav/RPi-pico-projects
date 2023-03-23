/**********************************************************************/
/* This file has been generated automatically by Beremiz4Pico Manager */
/* WARNING : DO NOT EDIT MANUALLY THIS FILE                           */
/**********************************************************************/

#include "iec_types.h"
#include <Arduino.h>
#include <Servo.h>

uint8_t DigitalInput[30];
uint8_t DigitalOutput[30];

IEC_BOOL* __QX0_25=&DigitalOutput[25];

void ConfigurePLCIO (void)
{
  pinMode (25, OUTPUT);
}

void AcquirePLCInputs (void)
{
}

void UpdatePLCOutputs (void)
{
  digitalWrite (25, DigitalOutput[25]);
}
