// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef LED_PATTERN_H
#define LED_PATTERN_H

#include <arduino.h>

// Compute diagnostic LED pulse pattern. The pattern is made of 32 bits (lsb fitst)
// which represents 32 time slots in a 1.024 second cycle. For better pulse 
// visibility, the odd slots are x3 longer than the even slots (allows shorter 
// pulses with longer intervals).
boolean ledPattern(int t, unsigned long pattern) {
  // 64 sub slots in a 1024 ms cycle
  const int sub_slot_index = (t >> 4) & 0x3f;  
  // The index of the even slot in the slot pair of current slot.
  const int base_slot_index = ((sub_slot_index >> 1) & 0x1e);
  // If 01, 10, or 11, add one for the odd slot.
  const int slot_index = base_slot_index + ((sub_slot_index & 0x3) ? 1 : 0);
  // Extract the slot bit from the pattern.
  return (pattern >> slot_index) & 0x1;
}

#endif

