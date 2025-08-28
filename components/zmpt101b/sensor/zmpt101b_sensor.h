#pragma once

#include "esphome.h"
#include "esphome/components/sensor/sensor.h"
#include "zmpt101b.h"

namespace esphome {
namespace zmpt101b_ns {

class ZMPT101BSensor : public PollingComponent, public sensor::Sensor {
 public:
  uint8_t adcPin;
  esphome::zmpt101b_ns::ZMPT101B *zmpt101b;
  // constructor
  ZMPT101BSensor(uint8_t adcPin, float sensitivity, uint32_t update_interval = 1000)
    : PollingComponent(update_interval) {
      this->adcPin = adcPin;
      this->zmpt101b = new esphome::zmpt101b_ns::ZMPT101B(adcPin);
      this->zmpt101b->setSensitivity(sensitivity);
  }

  float get_setup_priority() const override { return esphome::setup_priority::HARDWARE; }

  void setup() override {
    
  }

  void update() override {
    float Vrms = this->zmpt101b->getRmsVoltage();
    publish_state(Vrms);
  }
};

}
}
