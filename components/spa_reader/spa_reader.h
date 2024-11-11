#pragma once

#include <CircularBuffer.hpp>
#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/core/log.h"
#include "esphome.h"
#define STRON "ON"
#define STROFF "OFF"
namespace esphome {
namespace spa_reader {

class SpaReader : public Component, public uart::UARTDevice {
  public:
    void setup() override;
    void loop() override;
    void set_temp_sensor(sensor::Sensor *temp_sensor);
    void set_circ_binary_sensor(binary_sensor::BinarySensor *circ_binary_sensor);
    //float get_setup_priority() const override { return esphome::setup_priority::LATE; }

    // sensor::Sensor *temp_sensor;
  protected:
    CircularBuffer<uint8_t, 35> Q_in;
    CircularBuffer<uint8_t, 35> Q_out;
    uint8_t x, i, j;
    
    uint8_t last_state_crc = 0x00;
    uint8_t send = 0x00;
    uint8_t settemp = 0x00;
    uint8_t sethour = 0x00;
    uint8_t setminute = 0x00;
    uint8_t id = 0x00;
    unsigned long lastrx = 0;

    char have_config = 0;
    char have_faultlog = 0;
    char have_filtersettings = 0;
    char faultlog_minutes = 0;
    char filtersettings_minutes = 0;

    struct {
      uint8_t jet1 :2;
      uint8_t jet2 :2;
      uint8_t blower :1;
      uint8_t light :1;
      uint8_t restmode:1;
      uint8_t highrange:1;
      uint8_t heater:1;
      uint8_t hour :5;
      uint8_t minutes :6;
      uint8_t circ :1;
    } SpaState;

    struct {
      uint8_t pump1 :2;
      uint8_t pump2 :2;
      uint8_t pump3 :2;
      uint8_t pump4 :2;
      uint8_t pump5 :2;
      uint8_t pump6 :2;
      uint8_t light1 :1;
      uint8_t light2 :1;
      uint8_t circ :1;
      uint8_t blower :1;
      uint8_t mister :1;
      uint8_t aux1 :1;
      uint8_t aux2 :1;
      uint8_t temp_scale :1;
    } SpaConfig;

    struct {
      uint8_t totEntry :5;
      uint8_t currEntry :5;
      uint8_t faultCode :6;
      std::string faultMessage;
      uint8_t daysAgo :8;
      uint8_t hour :5;
      uint8_t minutes :6;
    } SpaFaultLog;

    struct {
      uint8_t filt1Hour :5;
      uint8_t filt1Minute :6;
      uint8_t filt1DurationHour :5;
      uint8_t filt1DurationMinute :6;
      uint8_t filt2Enable :1;
      uint8_t filt2Hour :5;
      uint8_t filt2Minute :6;
      uint8_t filt2DurationHour :5;
      uint8_t filt2DurationMinute :6;
    } SpaFilterSettings;

    uint8_t crc8(CircularBuffer<uint8_t, 35> &data);
    void ID_request();
    void ID_ack();
    void rs485_send();
    //void print_msg(CircularBuffer<uint8_t, 35> &data);
    void decodeSettings();
    void decodeState();
    void decodeFilterSettings();
    void decodeFault();

    // void on_set_temp(float temp);
    // void on_set_hour(int hour);
    // void on_set_minute(int minute);
    // void on_toggle_heatingmode();
    // void on_toggle_range();
    // void on_toggle_light();
    // void on_toggle_jet1();
    // void on_toggle_jet2();
    sensor::Sensor *temp_sensor_{nullptr};
    sensor::Sensor *target_temp_sensor_{nullptr};
    sensor::Sensor *jet1_sensor_{nullptr};
    sensor::Sensor *jet2_sensor_{nullptr};
    sensor::Sensor *blower_sensor_{nullptr};
    sensor::Sensor *light_sensor_{nullptr};
    sensor::Sensor *restmode_sensor_{nullptr};
    sensor::Sensor *highrange_sensor_{nullptr};
    sensor::Sensor *hour_sensor_{nullptr};
    sensor::Sensor *minute_sensor_{nullptr};
    sensor::Sensor *heater_sensor_{nullptr};
    binary_sensor::BinarySensor *circ_binary_sensor_{nullptr};


};
}
}
