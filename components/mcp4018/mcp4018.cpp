/**
 * @file mcp4018.cpp
 * @brief Implementation for the mcp4018 ESPHome component
 * @author Soldered Electronics
 */

#include "mcp4018.h"
#include "esphome/core/log.h"

#include <cmath>

namespace esphome {
namespace mcp4018 {

static const char *const TAG = "mcp4018";

void MCP4018Output::setup() {
  // The MCP4018 has no command/register address, a bare one-byte read returns the wiper position.
  uint8_t data;
  if (this->read(&data, 1) != i2c::ERROR_OK) {
    ESP_LOGE(TAG, "Failed to read wiper, check wiring and I2C address");
    this->mark_failed();
    return;
  }
  this->wiper_ = data & MCP4018_WIPER_MAX;

  if (this->initial_value_.has_value()) {
    this->set_level(*this->initial_value_);
  }
}

void MCP4018Output::dump_config() {
  ESP_LOGCONFIG(TAG, "MCP4018 Digital Potentiometer:");
  LOG_I2C_DEVICE(this);
  if (this->is_failed()) {
    ESP_LOGE(TAG, "  Communication with MCP4018 failed!");
    return;
  }
  ESP_LOGCONFIG(TAG, "  Wiper: %u/%u", this->wiper_, MCP4018_WIPER_MAX);
  LOG_FLOAT_OUTPUT(this);
}

void MCP4018Output::write_state(float state) {
  // A bare one-byte write sets the wiper, bit 7 is don't-care.
  uint8_t wiper = static_cast<uint8_t>(lroundf(state * MCP4018_WIPER_MAX)) & MCP4018_WIPER_MAX;
  if (this->write(&wiper, 1) != i2c::ERROR_OK) {
    ESP_LOGW(TAG, "Failed to write wiper");
    this->status_set_warning();
    return;
  }
  this->status_clear_warning();
  this->wiper_ = wiper;
  ESP_LOGV(TAG, "Wiper set to %u/%u", wiper, MCP4018_WIPER_MAX);
}

}  // namespace mcp4018
}  // namespace esphome
