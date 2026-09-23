# Soldered MCP4018 ESPHome Component

| ![MCP4018 Breakout](https://cms.soldered.com/products/333090/media/333090_featured-photo_5f392d.jpg) |
| :--------------------------------------------------------------------------------------------------: |
|                           [MCP4018 Breakout](https://www.solde.red/333090)                           |

Breakout board for the Microchip MCP4018 I2C digital potentiometer, with 128 wiper steps and 5k, 10k and 50k ohm
variants. The board is part of the [Qwiic ecosystem](https://soldered.com/collections/qwiic-ecosystem).

External ESPHome component for the Soldered MCP4018 breakout board. It is a port of the
[Soldered MCP4018 Arduino library](https://github.com/SolderedElectronics/Soldered-Digipot-MCP4018-Arduino-Library)
and exposes the wiper as an ESPHome [float output](https://esphome.io/components/output/), so it can be driven by
`output.set_level`, a template `number`, a `light`, or anything else that takes an output.

## Repository Contents

- **components/** - the ESPHome external component (Python config + C++ implementation)
- **examples/** - example YAML configs showing how to use the component

## Usage

Reference this repo directly from your own ESPHome YAML (no need to clone it locally):

```yaml
external_components:
  - source: github://SolderedElectronics/Soldered-MCP4018-ESPHome-Component
    components: [mcp4018]

i2c:
  sda: GPIO21
  scl: GPIO22

output:
  - platform: mcp4018
    id: digipot
    initial_value: 0.5
```

An output level of `0.0` - `1.0` maps linearly onto wiper positions `0` - `127`, measured from the GND side of the
potentiometer.

See [`examples/basic.yaml`](examples/basic.yaml) for a full working example with a 0 - 100 % slider.

### Configuration variables

- **id** (**Required**, [ID](https://esphome.io/guides/configuration-types#config-id)): the ID of the output.
- **address** (*Optional*, int): I2C address of the chip. Defaults to `0x2F` (fixed on the MCP4018).
- **initial_value** (*Optional*, float): level (`0.0` - `1.0`) written to the wiper on boot. The MCP4018 wiper is
  volatile and resets to mid-scale on power-up; if this option is omitted, that power-on value is left untouched.
- All other options from [Output](https://esphome.io/components/output/#config-output) (`min_power`, `max_power`,
  `inverted`, ...).

### Hardware design

You can find hardware design for this board in the MCP4018 hardware repositories ([5k](https://github.com/SolderedElectronics/Digipot-5k-MCP4018-breakout-hardware-design), [10k](https://github.com/SolderedElectronics/Digipot-10k-MCP4018-breakout-hardware-design), [50k](https://github.com/SolderedElectronics/Digipot-50k-MCP4018-breakout-hardware-design)).

### Documentation

Access library documentation [here](https://docs.soldered.com/).

### About Soldered

<img src="https://raw.githubusercontent.com/SolderedElectronics/Soldered-Generic-Arduino-Library/dev/extras/Soldered-logo-color.png" alt="soldered-logo" width="500"/>

At Soldered, we design and manufacture a wide selection of electronic products to help you turn your ideas into acts and bring you one step closer to your final project. Our products are intented for makers and crafted in-house by our experienced team in Osijek, Croatia. We believe that sharing is a crucial element for improvement and innovation, and we work hard to stay connected with all our makers regardless of their skill or experience level. Therefore, all our products are open-source. Finally, we always have your back. If you face any problem concerning either your shopping experience or your electronics project, our team will help you deal with it, offering efficient customer service and cost-free technical support anytime. Some of those might be useful for you:

- [Web Store](https://www.soldered.com/shop)
- [Tutorials & Projects](https://soldered.com/learn)
- [Documentation](https://docs.soldered.com)

### Open-source license

Soldered invests vast amounts of time into hardware & software for these products, which are all open-source. Please support future development by buying one of our products.

Check license details in the LICENSE file. Long story short, use these open-source files for any purpose you want to, as long as you apply the same open-source licence to it and disclose the original source. No warranty - all designs in this repository are distributed in the hope that they will be useful, but without any warranty. They are provided "AS IS", therefore without warranty of any kind, either expressed or implied. The entire quality and performance of what you do with the contents of this repository are your responsibility. In no event, Soldered (TAVU) will be liable for your damages, losses, including any general, special, incidental or consequential damage arising out of the use or inability to use the contents of this repository.

## Have fun!

And thank you from your fellow makers at Soldered Electronics.
