/*
 * iec_std_lib.c
 * copyright 2022 Benoit BOUCHEZ for Raspberry Pico port
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
 * 
 */

 /* This file is needed in Arduino toolchain to force compiler to use C rather than C++
  * Including directly iec_std_lib.h in ino files leads to compilation issues because
  * of polymophism : C++ complains it find ambiguous functions (mainly "div")
  * This has no impact on the PLC code, which is natively written in C and imported
  * as is in the C++ runtime code
  */

#include "iec_std_lib.h"

IEC_TIMESPEC __time_to_timespec (int sign, int mseconds, int seconds, int minutes, int hours, int days)
{
	IEC_TIMESPEC retval;
	
	retval.tv_sec = seconds;
	if (minutes!=0) retval.tv_sec += minutes*60;
	if (hours!=0) retval.tv_sec += hours*3600;
	if (days!=0) retval.tv_sec += days*86400;		// 24 * 60 * 60
	retval.tv_msec = mseconds;
	
	// Add sign (but what is a NEGATIVE time ????)
	if (sign < 0)
	{
		retval.tv_msec = -retval.tv_msec;
		retval.tv_sec = -retval.tv_sec;
	}
	
	return retval;
}  // __time_to_timespec
/* ------------------------------------------------- */

IEC_TIMESPEC __tod_to_timespec(int seconds, int minutes, int hours)
{
	IEC_TIMESPEC retval;
	
	retval.tv_sec = seconds;
	if (minutes!=0) retval.tv_sec += minutes*60;
	if (hours!=0) retval.tv_sec += hours*3600;	
	retval.tv_msec = 0;
	
	return retval;
}  // __tod_to_timespec
/* ------------------------------------------------- */
