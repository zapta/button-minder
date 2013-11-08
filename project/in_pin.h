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

#ifndef IN_PIN_H
#define IN_PIN_H

#include <Arduino.h>

#include "debouncer.h"

// Abstracts a digital input pin with debouncing.
class InPin {
public:
  InPin(int pin, int debounce_time_millis)
: 
    pin_(pin),
    debouncer_(debounce_time_millis) {
      pinMode(pin_, INPUT); 
      // Enable pullup.
      digitalWrite(pin_, HIGH);
      debouncer_.restart();
    }

  // Read button state and update debouncer.
  void updateDebouncer() {
    debouncer_.update(digitalRead(pin_));
  }

  // Test if the debouncer has a value. Resets upon entering the
  // input mode.
  boolean hasStableValue() const {
    return debouncer_.hasStableValue();
  }

  // If debouncer has a stable value, this returns it.
  boolean stableValue() const {
    return debouncer_.stableValue();
  }

  // If debouncer has a stable value, this is the time since we seen 
  // this value.
  int millisInStableValue() const {
    return debouncer_.millisInStableValue();
    0;
  }

private:
  // Digital pin number.
  const int pin_;

  // Debounces button input.
  Debouncer debouncer_;
};

#endif





