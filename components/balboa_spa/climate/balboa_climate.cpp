#include "esphome/components/balboa_spa/climate/balboa_climate.h"
namespace esphome
{
  namespace balboa_spa
  {
    static const char *TAG = "balboa_spa.climate";

    void BalboaClimate::setup()
    {
      this->parent_->register_sensor_callback(40, [this](const float temp)
                                              { this->target_temperature = temp; this->publish_state(); });
      this->parent_->register_sensor_callback(41, [this](const float temp)
                                              { this->current_temperature = temp; this->publish_state(); });

      // Register callback for heater state
      this->parent_->register_binary_sensor_callback(21, [this](const bool state) {
        this->mode = state ? climate::CLIMATE_MODE_HEAT : climate::CLIMATE_MODE_OFF;
        this->publish_state();
      });

    }
    void BalboaClimate::control(const climate::ClimateCall &call)
    {
      if (call.get_target_temperature().has_value())
      {
        float temp = *call.get_target_temperature();
        this->parent_->on_set_temp(temp);
      }
    }
  }
}
