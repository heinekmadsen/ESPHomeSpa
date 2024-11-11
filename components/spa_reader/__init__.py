import esphome.codegen as cg
import esphome.config_validation as cv
#<<<<<<< HEAD
from esphome import pins
from esphome.components import uart, sensor, binary_sensor
from esphome.const import CONF_ID
from esphome.const import *
DEPENDENCIES = ['uart']
AUTO_LOAD = ['uart', 'sensor', 'text_sensor', 'binary_sensor']

spa_reader_ns = cg.esphome_ns.namespace('spa_reader')
SpaReader = spa_reader_ns.class_('SpaReader', cg.Component, uart.UARTDevice)
CONF_TEMP_SENSOR = "temp_sensor"
CONF_CIRC_SENSOR = "circ_binary_sensor"

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(SpaReader),
    cv.Optional(CONF_TEMP_SENSOR):
        sensor.sensor_schema(device_class=DEVICE_CLASS_TEMPERATURE,unit_of_measurement=UNIT_CELSIUS,accuracy_decimals=1,state_class=STATE_CLASS_MEASUREMENT).extend(), 
    cv.Optional(CONF_CIRC_SENSOR):
        binary_sensor.binary_sensor_schema().extend(), 
}).extend(uart.UART_DEVICE_SCHEMA)

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    cg.add_library(name="rlogiacco/CircularBuffer", version=None)
    yield uart.register_uart_device(var, config)

    if CONF_TEMP_SENSOR in config:
        conf = config[CONF_TEMP_SENSOR]
        sens = yield sensor.new_sensor(conf)
        cg.add(var.set_temp_sensor(sens))
    if CONF_CIRC_SENSOR in config:
        conf = config[CONF_CIRC_SENSOR]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_circ_binary_sensor(sens))