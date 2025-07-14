# Smart-Parking-System---IOT-Based-Project

This project implements a smart parking solution using NodeMCU ESP8266, IR sensors, and ThingSpeak.

## Features

- Monitors 5 parking slots using IR sensors.
- Automatically opens/closes barriers for 2 slots via servo motors.
- Sends real-time slot data to ThingSpeak for visualization.

## Hardware Required

- NodeMCU ESP8266
- IR Sensors (x5)
- Servo Motors (x2)
- Breadboard and jumper wires
- 9V power supply

## Connections

| Component       | NodeMCU Pin  |
|-----------------|--------------|
| IR Sensor 1     | D1           |
| IR Sensor 2     | D2           |
| IR Sensor 3     | D3           |
| IR Sensor 4     | D4           |
| IR Sensor 5     | D5           |
| Servo Motor 1   | D6           |
| Servo Motor 2   | D7           |

## Setup Instructions

1. Install the ESP8266 board in Arduino IDE:
   - File > Preferences > Additional Board Manager URLs:
     ```
     http://arduino.esp8266.com/stable/package_esp8266com_index.json
     ```
   - Tools > Board > Boards Manager > Install "esp8266".

2. Install the Servo library if not installed:
   Sketch > Include Library > Servo


3. Configure `ssid`, `password`, and `apiKey` in `smart_parking.ino`.

4. Upload the code to NodeMCU.

5. View real-time data on ThingSpeak dashboard.

## ThingSpeak Setup

- Create a new channel with 5 fields (Field1 to Field5).
- Copy your API key and paste into the code.

## Working Principle

- IR sensors detect slot occupancy.
- Servo motors open/close barriers.
- Data is sent to ThingSpeak every 5 seconds.
- You can integrate alerts and mobile dashboards via IFTTT.

## License

MIT License.


