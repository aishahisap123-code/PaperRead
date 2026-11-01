# PaperRead — E-Reader Project

PaperRead is a custom, low-power e-paper reader built around the Seeed Studio XIAO ESP32-C3 microcontroller. It features dedicated page-navigation buttons, an integrated 3.3V MicroSD card module for reading text files, and a custom double-sided PCB.
<img width="2650" height="1755" alt="Screenshot 2026-10-28 133617" src="https://github.com/user-attachments/assets/a51eccd1-c5ab-4daa-bee6-891f89b1a580" />
<img width="1192" height="1566" alt="Screenshot 2026-10-28 222143" src="https://github.com/user-attachments/assets/30e92427-ad1e-466d-af2e-fc994ba41233" />
<img width="582" height="841" alt="Screenshot 2026-10-29 151802" src="https://github.com/user-attachments/assets/b7d89dc2-6f4e-4099-a10e-f8bc55a75814" />
<img width="587" height="832" alt="Screenshot 2026-10-29 151755" src="https://github.com/user-attachments/assets/2155d22c-aa6c-43cb-b837-0b79ce8e05a1" />
<img width="924" height="1482" alt="Screenshot 2026-10-29 153356" src="https://github.com/user-attachments/assets/4d9701db-138a-4004-b78f-46505e6d6fea" />
<img width="859" height="1478" alt="Screenshot 2026-10-29 153419" src="https://github.com/user-attachments/assets/f04e8bf2-75d4-4f2f-aa4f-36760125acb0" />

---

## Technical Specifications

* **Microcontroller:** Seeed Studio XIAO ESP32-C3 (Wi-Fi / Bluetooth)
* **Display:** SPI E-Paper Display Module (compatible with GxEPD2 library)
* **Storage:** 3.3V MicroSD Card Module (SPI interface)
* **Controls:** 3x Tactile Push Buttons (Previous Page, Next Page, Select/Menu)
* **Power Management:** Slide Switch (SW6) with JST-PH 2.0mm LiPo battery header

---

## Hardware & PCB Design

The custom 2-layer PCB was designed in KiCad and manufactured via JLCPCB:

* **Dimensions:** Compact dual-layer board with 4 corner mounting holes for custom enclosure mounting.
* **Grounding:** Solid `GND` copper pours on both top and bottom layers to minimize electrical noise.
* **Silkscreen:** Custom vector artwork positioned clear of copper pads for clean soldering.
* **Enclosure:** Modeled in Onshape (STEP file exported for 3D printing).

---

## Firmware Setup

The firmware is written for the Arduino IDE using the following libraries:
* `GxEPD2` (for e-paper display control)
* `SD` and `SPI` (for reading text files off the MicroSD card)

### Pinout Mapping
* **Button Previous:** GPIO 3
* **Button Next:** GPIO 4
* **Button Select:** GPIO 5
* **SD Card CS:** GPIO 2

---

## Bill of Materials (BOM)

Save the following table as `bom.csv` in the root of your repository for automated tracking:

```csv
Item,Qty,Supplier,Cost/item,Total Cost,link
Seeed Studio XIAO ESP32-C3,1,Seeed Studio,$5.00,$5.00,
E-Paper Display Module,1,AliExpress,$12.00,$12.00,
3.3V MicroSD Card Module,1,AliExpress,$1.50,$1.50,
Tactile Push Buttons,3,AliExpress,$0.33,$1.00,
Slide Power Switch,1,AliExpress,$0.50,$0.50,
JST-PH 2.0mm Battery Connector,1,AliExpress,$0.50,$0.50,
Custom PCB,5,JLCPCB,$0.40,$2.00,
Estimated total shipping,1,,, $0.00,
