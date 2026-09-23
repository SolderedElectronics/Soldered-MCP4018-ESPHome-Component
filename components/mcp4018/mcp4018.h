/**
 * @file mcp4018.h
 * @brief Public API for the mcp4018 ESPHome component
 * @author Soldered Electronics
 */

#pragma once

#include "esphome/components/i2c/i2c.h"
#include "esphome/components/output/float_output.h"
#include "esphome/core/component.h"
#include "esphome/core/optional.h"

namespace esphome {
namespace mcp4018 {

/// Highest wiper position of the 7-bit MCP4018 (128 steps, 0 - 127).
static const uint8_t MCP4018_WIPER_MAX = 0x7F;

/**
 * @brief MCP4018 digital potentiometer exposed as an ESPHome float output.
 *
 * An output level of 0.0 - 1.0 maps linearly onto wiper positions 0 - 127, measured from the potentiometer's GND
 * side, same as setWiperPercent() in the Soldered MCP4018 Arduino library.
 */
class MCP4018Output : public output::FloatOutput, public Component, public i2c::I2CDevice {
 public:
  /**
   * @brief Set the level written to the wiper during setup().
   *
   * The MCP4018 wiper register is volatile and resets to mid-scale on power-up. If this is never called, setup()
   * leaves that power-on value untouched.
   *
   * @param initial_value Output level, 0.0 - 1.0.
   */
  void set_initial_value(float initial_value) { this->initial_value_ = initial_value; }

  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::HARDWARE; }

 protected:
  void write_state(float state) override;

  optional<float> initial_value_;
  uint8_t wiper_{0};
};

}  // namespace mcp4018
}  // namespace esphome
