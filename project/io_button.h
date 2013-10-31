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

#ifndef IO_BUTTON_H
#define IO_BUTTON_H

#include <Arduino.h>

#include "debouncer.h"

// A class that wraps a button I/O pin. The pin has two modes, as input where
// the button state is sensed and debounced and as output, when the pin output
// open collect LOW state, simulating a button press.
class IoButton {
private:
  // The voltage in millivolt of the button sensing threshold. The 
  // buttons is considered to be pressed if the voltage on its 
  // pullup pole is less than this voltage.
  static const int BUTTON_THRESHOLD_MILLI_VOLTS = 1000;

public:
  IoButton(int pin_as_digital, int pin_as_analog, int debounce_time_millis)
: 
    pin_as_digital_(pin_as_digital),
    pin_as_analog_(pin_as_analog),
    in_input_mode_(true),
    debouncer_(debounce_time_millis) {
      pinMode(pin_as_digital, INPUT); 
      debouncer_.restart();
    }

  // --- INPUT mode (sensing the button)

  // Set mode to input sensing. Does nothing if already in this state.
  void setModeInput() {
    if (!in_input_mode_) {
      pinMode(pin_as_digital_, INPUT); 
      debouncer_.restart();
      in_input_mode_ = true;
    }
  }

  // Read button state and update debouncer.
  void updateDebouncer() {
    if (in_input_mode_) {
      // Full scale of 5000mv equals reading of 1023.
      // Making the computation as long to avoid overflow.
      const long theshold_counts =  (1023L * BUTTON_THRESHOLD_MILLI_VOLTS ) / 5000;
      const boolean isPressed = analogRead(pin_as_analog_) < theshold_counts;
      debouncer_.update(isPressed);
    }
  }
 
  // Test if the debouncer has a value. Resets upon entering the
  // input mode.
  boolean hasStableValue() const {
    return in_input_mode_ && debouncer_.hasStableValue();
  }

  // If debouncer has a stable value, this returns it.
  boolean stableValue() const {
    return in_input_mode_ && debouncer_.stableValue();
  }

  // If debouncer has a stable value, this is the time since we seen 
  // this value.
  int millisInStableValue() const {
    return in_input_mode_ ? debouncer_.millisInStableValue() : 0;
  }
  
  // --- OUTPUT mode (simulating button press)
  
  // Set the output pin to issue an open collector signal to the
  // external button. This exists input mode. Does nothing if 
  // already in output low mode.
  void setModeOutputLow() {
    if (in_input_mode_) {
      pinMode(pin_as_digital_, OUTPUT); 
      digitalWrite(pin_as_digital_, LOW);
      in_input_mode_ = false;
    }
  }

private:
  // Same pin has differnet index when is used as digital and when used as analog.
  const int pin_as_digital_;
  const int pin_as_analog_;

  // True -> sense input mode. False -> output low mode.
  boolean in_input_mode_;

  // Debounces button input.
  Debouncer debouncer_;
};

#endif




