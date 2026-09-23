import esphome.codegen as cg
from esphome.components import i2c, output
import esphome.config_validation as cv
from esphome.const import CONF_ID, CONF_INITIAL_VALUE

DEPENDENCIES = ["i2c"]

mcp4018_ns = cg.esphome_ns.namespace("mcp4018")
MCP4018Output = mcp4018_ns.class_(
    "MCP4018Output", output.FloatOutput, cg.Component, i2c.I2CDevice
)

CONFIG_SCHEMA = (
    output.FLOAT_OUTPUT_SCHEMA.extend(
        {
            cv.Required(CONF_ID): cv.declare_id(MCP4018Output),
            cv.Optional(CONF_INITIAL_VALUE): cv.float_range(min=0.0, max=1.0),
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
    .extend(i2c.i2c_device_schema(0x2F))
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)
    await output.register_output(var, config)

    if CONF_INITIAL_VALUE in config:
        cg.add(var.set_initial_value(config[CONF_INITIAL_VALUE]))
