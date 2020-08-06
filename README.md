# 240x320-2.4-Display-TFT


Library [here](https://github.com/Bodmer/TFT_eSPI)

Untuk pertama kali buka File Examples Generic -> Touch_calibrate
dan ``tft.setRotation(0);`` ke `0` (sesuaikan dengan kebutuhan)
hasil dari kalibrasi taruh di ``void setup();``
## Wiring For ESP32 

| ESP32    | DISPLAY    |
|----------|------------|
| 3V       | VCC        |
| GND      | GND        |
| 5        | CS         |
| EN/RESET | RESET      |
| 17       | DC         |
| 23       | SDI (MOSI) |
| 18       | SCK        |
| 3V       | LED        |
|          | SDO (MISO) |
| 18       | T_CLK      |
| 4        | T_CS       |
| 23       | T_DIN      |
| 19       | T_DO       |
| -        | T_IRQ      |

