# Automated-Battery-Cycler-V1
This device enabled you to test the endurance of your battery from LiFePO4, Li-On, and Li-Po (1 Cell). The size right now is for 18650 or 26650 battery cell. The load is an IRFZ44N with CC (Constant Current) and CP (Constant Power) mode.
This project is coded with PlatformIO.

Parts needed for this project:
1. ESP32 DevKit V1
2. INA219
3. ADS1115
4. TC4422
5. IRFZ44N
6. Voltage divider (R1 10K R2 10K) with 100nF ceramic cap for filter
7. NTC 10k and R2 10K (act like a Voltage divider) in series with 100nF cap for filter
8. Custom made 2 channel SPDT relay
9. 470uF electrolytic cap
10. 22uF electrolytic cap
11. MicroSD card module

# Schematic
<img width="1150" height="791" alt="Screenshot 2026-07-10 221117" src="https://github.com/user-attachments/assets/0cb4b745-1106-41a5-a494-db36a455e7df" />
It is best to drive the TC4422 with +12V for better control for the MOSFET and you can still give it PWN straight from the ESP32 pin. You can also change the relay with something more capable.
REMINDER!!!: Change the shunt in the INA219 according to how much current you need or use INA226 for better resolution.

# PCB
<img width="1549" height="742" alt="Screenshot 2026-07-10 221159" src="https://github.com/user-attachments/assets/e71e5999-00e6-4274-8e9c-b217a2ca35af" />
This is my PCB. Still quite basic but sufficient enough for this project.

Everything can be change according to your need. Let me know what your thought about this project.
