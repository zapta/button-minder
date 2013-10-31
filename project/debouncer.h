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

#ifndef PASSIVE_DEBOUNCER_H
#define PASSIVE_DEBOUNCER_H

#include "passive_timer.h"
#include <arduino.h>

// A class for debouncing binary an input signal.
class Debouncer {
private:
  // Default debounce time. Callers can override when calling reastart().
  static const int DEFAULT_DEBOUNCE_TIME_MILLIS = 100;

public:
  Debouncer(int debounce_time_millis) 
: 
    debounce_time_millis_(debounce_time_millis) {
      restart();
    }

  // Reset using a new debunce time. This resets hasStableValue() to false.
  void restart() {
    latest_value_ = false;
    time_in_latest_value_.restart();
    has_stable_value_ = false;
    stable_value_ = false;
  }

  // Update the debouncer state with a new input value.
  void update(boolean new_value) {
    // Handle changes in latest value.
    if (new_value != latest_value_) {
      latest_value_ = new_value;
      time_in_latest_value_.restart();
      return;
    } 

    // If latest value is stable for debouncing time period, propogate value
    // to stable.
    if (time_in_latest_value_.time_millis() > debounce_time_millis_) {
      has_stable_value_ = true;
      stable_value_ = latest_value_;
      // We use the eariler start time of the latest value rather than time now.
      time_in_stable_value_.copy(time_in_latest_value_); 
    }
  }

  // Test if the debouncer has a stable value. 
  boolean hasStableValue() const {
    return has_stable_value_;
  }

  // Returns the debounced state. Active high. Valid only if hasStableValue()
  // is true.
  boolean stableValue() const {
    return stable_value_;
  }

  // Return the time in millis of the current stable value. Valid only if
  // hasStableValue() is true.
  int millisInStableValue() const {
    return time_in_stable_value_.time_millis();
  }

private:
  const int debounce_time_millis_;

  // Tracks pre debouncing button stte.
  boolean latest_value_;
  PassiveTimer time_in_latest_value_;

  // The debounced button state.
  boolean has_stable_value_;
  boolean stable_value_;
  PassiveTimer time_in_stable_value_;
};

#endif




