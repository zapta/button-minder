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

#include "eeprom_settings.h"
#include <EEPROM.h>

// We use specific bit pattern when writing the true/false setting
// to the eeprom to reduce the chance of false positive.
#define EEPROM_TRUE  0x7b
#define EEPROM_FALSE 0xf3

// We write the setting flag in this address of the eeprom of the Digispark. This
// is an arbitrary address.
#define EEPROM_ADDRESS 0x0

boolean EepromSettings::read() {
  return EEPROM.read(EEPROM_ADDRESS) ==  EEPROM_TRUE;
}

void EepromSettings::write(boolean new_value) {
  EEPROM.write(EEPROM_ADDRESS, new_value ? EEPROM_TRUE : EEPROM_FALSE);
}

