# Omniwheel Bluetooth Robot

A 30 cm × 30 cm Arduino-based omniwheel/mecanum robot chassis controlled through Bluetooth. The robot uses four DC gear motors, four omni/mecanum wheels mounted at 45° relative to the chassis corners, two H-bridge motor drivers, an Arduino Uno, and a 3-cell 18650 battery pack.

## Project Contents

```text
Omniwheel_Robot_GitHub_Repo/
├── code/
│   └── arduino/
│       └── OmniBluetoothControl.ino
├── docs/
│   ├── boq/
│   │   └── Omniwheel_Robot_BOQ.xlsx
│   ├── images/
│   │   ├── OmniWheelsRobot_real_photo.jpeg
│   │   └── robot_3d_diagram.png
│   └── assembly_steps/
│       ├── full_build_guide_45_degree_mount.png
│       ├── step_1_cut_prepare_chassis_parts.png
│       ├── step_2_assemble_300x300_frame.png
│       ├── step_3_square_frame_tighten_connections.png
│       ├── step_4_mount_motors_45_degree.png
│       ├── step_5_attach_omni_mecanum_wheels.png
│       └── step_6_final_alignment_ready_chassis.png
├── media/
│   ├── demo_video_placeholder.txt
│   └── omniWheelReobotDemo2.mp4
├── android_app/
│   └── BTRobotFeedBack1.apk
├── LICENSE
└── README.md
```

## Hardware Components

The main components are documented in the BOQ file:

- 4 × omni/mecanum wheels
- 4 × JGA25-370 DC gear motors
- 4 × motor mounting brackets
- 2 × H-bridge motor drivers
- 1 × Arduino Uno
- 1 × Bluetooth module
- 3 × 18650 rechargeable batteries with holder
- 2040 aluminum profile chassis pieces
- Corner brackets, bolts, nuts, washers, and T-nuts

See: `docs/boq/Omniwheel_Robot_BOQ.xlsx`

## Chassis Design

- Base size: 30 cm × 30 cm
- Material: aluminum extrusion profile
- Wheel configuration: four omni/mecanum wheels installed at the chassis corners
- Motor/wheel orientation: 45° relative to the chassis sides

Assembly graphics are available in:

`docs/assembly_steps/`

## Arduino Pin Configuration

```cpp
SoftwareSerial BT(2, 4); // RX, TX

const int EN_FL = 5;
const int IN1_FL = 6;
const int IN2_FL = 7;

const int EN_FR = 10;
const int IN1_FR = 8;
const int IN2_FR = 9;

const int EN_RL = 11;
const int IN1_RL = 12;
const int IN2_RL = 13;

const int EN_RR = 3;
const int IN1_RR = A0;
const int IN2_RR = A1;
```

## Bluetooth Commands

| Command | Motion |
|---|---|
| `F` | Move forward |
| `B` | Move backward |
| `L` | Strafe left |
| `R` | Strafe right |
| `Q` | Rotate left |
| `E` | Rotate right |
| `G` | Forward-left diagonal |
| `I` | Forward-right diagonal |
| `H` | Backward-left diagonal |
| `J` | Backward-right diagonal |
| `S` | Stop |
| `0`–`9` | Set speed level |
| `+` | Increase speed |
| `-` | Decrease speed |

## Arduino Code

The Arduino control file is available at:

`code/arduino/OmniBluetoothControl.ino`

Upload it using the Arduino IDE after selecting:

- Board: Arduino Uno
- Port: the detected Arduino COM port

## Demo Video

Place the demo video file inside the `media/` folder, or add a YouTube/Google Drive link in this README.

Demo video link: **Add your link here**

## Android App

Add the Android app link here.

Android app link: **Add your link here**

## Notes

- Test the robot first at low speed.
- If a motor rotates in the wrong direction, change the corresponding motor inversion variable in the Arduino code.
- Make sure the 3-cell lithium battery pack is protected using a suitable BMS.
- Ensure all four wheels touch the ground and that the chassis is square before testing movement.

## Suggested Repository Description

Arduino Bluetooth-controlled 30×30 cm omniwheel/mecanum robot with 45° corner-mounted wheels, H-bridge drivers, BOQ, assembly graphics, and Arduino control code.
