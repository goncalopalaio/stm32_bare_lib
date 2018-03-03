/* Copyright 2017 Pete Warden. All Rights Reserved.
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
    http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

// Shows how to set up and read a simple timer counter.

#include "adc.h"
#include "debug_log.h"

void OnReset(void) {
  // Start up the clock system.
  RccInitForAdc();

  TimerInit(TIMERID_TIM1);
  const uint16_t start_time = TimerGetCounter(TIMERID_TIM1);
  while (1) {
    const uint16_t current_time = TimerGetCounter(TIMERID_TIM1) - start_time;
    const int32_t seconds = current_time / 1000;
    const int32_t milliseconds = current_time - (seconds * 1000);
    const int32_t adc_log_length = 256;
    char adc_log[adc_log_length];
    StrCpy(adc_log, adc_log_length, "Time: ");
    StrCatInt32(adc_log, adc_log_length, seconds, 10);
    StrCatStr(adc_log, adc_log_length, ".");
    StrCatInt32(adc_log, adc_log_length, milliseconds, 10);
    StrCatStr(adc_log, adc_log_length, "ms\n");
    DebugLog(adc_log);
  }
}
