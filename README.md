# Automated-Battery-Cycler-V1
This device enabled you to test the endurance of your battery from LiFePO4, Li-On, and Li-Po (1 Cell). The size right now is for 18650 or 26650 battery cell. The load is an IRFZ44N with CC (Constant Current) and CP (Constant Power) mode

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
