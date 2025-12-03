# Scout Robot - Autonomous IoT Micro-Explorer 🤖

> **Intelligent Autonomous Navigation Platform**  
> An ESP32-driven miniature vehicle designed for remote exploration, mapping, and autonomous navigation in hazardous or confined environments using MQTT, ROS2, SLAM, and Edge Impulse ML.

---

## 📋 Project Overview

**Scout Robot** is an advanced autonomous micro-explorer designed to navigate and map hazardous or confined spaces with precision. It addresses critical challenges in:
- 🚷 **Inaccessible Confined Spaces** - Access areas humans cannot reach
- 🔍 **Lack of Real-Time Vision** - Provide live monitoring in high-risk zones  
- 🗺️ **Dynamic Mapping & Localization** - Build real-time maps in unknown environments

This comprehensive project combines **embedded systems**, **IoT communication**, **robotic operating systems**, and **machine learning** to create a scalable platform for remote exploration, inspection, and autonomous data acquisition.

### Key Features
- ✅ **Real-time MQTT IoT Control** via Mosquitto broker and Node-RED dashboard
- ✅ **Multi-sensor Integration** (Ultrasonic, TCRT5000 Line Tracking, MPU6050 IMU)
- ✅ **Differential Drive Control** with independent motor PWM speed management
- ✅ **ROS2 Integration** with SLAM Toolbox for real-time mapping and localization
- ✅ **Collision Avoidance System** with dual ultrasonic sensors
- ✅ **Node-RED Visualization Dashboard** for intuitive remote control
- ✅ **Gazebo Simulation** with LiDAR, Differential Drive, and IMU plugins
- ✅ **Edge Impulse ML Integration** for intelligent sensor data analysis
- ✅ **3D CAD Design** (SolidWorks) with full URDF export for ROS2

---

## 🏗️ System Architecture

### Hardware Platform
- **Microcontroller**: ESP32 (Dual-core, 240MHz)
- **Motor Driver**: L298N H-Bridge with PWM control
- **Sensors**:
  - Ultrasonic Sensors (Forward & Backward distance detection)
  - TCRT5000 Line Tracking Sensors (Left & Right)
  - MPU6050 IMU (6-axis gyroscope + accelerometer)
- **Connectivity**: WiFi + MQTT Broker
- **Power**: Lithium Battery with charging module

### Software Stack
```
┌─────────────────────────────────────────────────────┐
│    Edge Impulse ML Layer (Optional)                 │  (ML Analysis)
│  - Sensor Data Classification & Regression         │
└─────────────────────────────────────────────────────┘
                         ↓
┌─────────────────────────────────────────────────────┐
│         ROS2 Navigation & SLAM Layer                │  (ros2/)
│  - SLAM Toolbox, Gazebo Simulation                 │
│  - Differential Drive, LiDAR, IMU Plugins          │
│  - Real-time Mapping & Path Planning               │
└─────────────────────────────────────────────────────┘
                         ↓
┌─────────────────────────────────────────────────────┐
│    Node-RED IoT Visualization Dashboard             │  (Control Layer)
│  - MQTT-based Web UI                               │
│  - Real-time Command Execution                      │
│  - Status Monitoring & Feedback                     │
└─────────────────────────────────────────────────────┘
                         ↓
┌─────────────────────────────────────────────────────┐
│       Mosquitto MQTT Broker                         │  (Message Hub)
│  - Asynchronous Communication Channel              │
│  - Topic-based Publish/Subscribe                   │
└─────────────────────────────────────────────────────┘
                         ↓
┌─────────────────────────────────────────────────────┐
│       ESP32 Embedded Firmware                       │  (embedded_iot/)
│  - Hardware Abstraction Layer (HAL)                │
│  - Sensor Reading & Motor Control                  │
│  - Real-time Task Scheduling (FreeRTOS)           │
└─────────────────────────────────────────────────────┘
```

---

## 📁 Repository Structure

```
ScoutRobot/
├── embedded_iot/                 # ESP32 Firmware (IDF-based)
│   ├── main/                     # Main application entry point
│   │   ├── main.cpp             # Core firmware logic
│   │   ├── main.h               # Configuration & MQTT topics
│   │   └── CMakeLists.txt
│   ├── hall/                     # Hardware Abstraction Layer
│   │   ├── led.h                # LED control
│   │   ├── dc_motor.h           # Motor driver interface
│   │   ├── ultrasonic.h         # Distance measurement
│   │   ├── TCRT5000.h           # Line tracking sensor
│   │   ├── MPU6050.h            # IMU sensor driver
│   │   └── pid.h                # PID controller
│   ├── mcu/                      # MCU Components
│   │   ├── MQTT.h               # MQTT client wrapper
│   │   ├── WiFi.h               # WiFi connection manager
│   │   └── NVS.h                # Non-volatile storage
│   ├── lib/                      # Custom libraries
│   ├── CMakeLists.txt           # ESP-IDF build configuration
│   ├── sdkconfig                # IDF SDK config
│   └── connections.txt          # Hardware pinout documentation
│
├── ros_elegoo/                   # ROS URDF Package
│   ├── urdf/                     # Robot Description Files
│   ├── meshes/                   # 3D mesh models
│   ├── launch/                   # ROS2 launch configurations
│   ├── config/                   # Robot parameters
│   └── package.xml
│
├── ros2/                         # ROS2 Workspace
│   ├── src/                      # ROS2 packages source code
│   ├── build/                    # Build artifacts
│   └── install/                  # Installation directory
│
├── matlab_analysis/              # MATLAB Simulation & Analysis
│   ├── Elegoo.slx               # Simulink model
│   ├── Elegoo_DataFile.m        # System analysis data
│   ├── *.STEP                   # CAD models (STEP format)
│   └── *.png                    # Simulation results & diagrams
│
├── Elegoo/                       # SolidWorks CAD Models
│   ├── *.SLDPRT                 # Individual component parts
│   ├── *.SLDASM                 # Assembly definitions
│   └── [Various mechanical components]
│
├── DOCs/                         # Documentation & Media
│   ├── V2V Communication and Collision Avoidance System - Technical Documentation.pdf
│   ├── system_digram.png        # System architecture diagram
│   ├── urdf.png, rviz2.png      # Visualization screenshots
│   └── [Additional documentation]
│
└── README.md                     # This file
```

---

## 🔌 Hardware Connections

### Motor Driver (L298N) Pin Mapping
| Signal | ESP32 Pin | Description |
|--------|-----------|-------------|
| ENB (Left Speed) | GPIO5 | PWM enable for left motor |
| ENA (Right Speed) | GPIO4 | PWM enable for right motor |
| IN1 (Right Motor) | GPIO19 | Direction control |
| IN2 (Right Motor) | GPIO18 | Direction control |
| IN3 (Left Motor) | GPIO17 | Direction control |
| IN4 (Left Motor) | GPIO16 | Direction control |

### Sensor Connections
| Sensor | Signal | ESP32 Pin |
|--------|--------|-----------|
| **Ultrasonic (Forward)** | TRIG | GPIO21 |
| | ECHO | GPIO22 |
| **Ultrasonic (Backward)** | TRIG | GPIO27 |
| | ECHO | GPIO26 |
| **TCRT5000 (Right)** | D0 | GPIO2 |
| **TCRT5000 (Left)** | D0 | GPIO0 |
| **MPU6050** | SDA | GPIO21 (I2C) |
| | SCL | GPIO22 (I2C) |

---

## 📡 MQTT Topic Structure

### Control Topics (Receive)
```
/smart_car/control/forward              # Move forward
/smart_car/control/backward             # Move backward
/smart_car/control/right                # Turn right
/smart_car/control/left                 # Turn left
/smart_car/control/stop                 # Stop movement
/smart_car/control/speed/right          # Right motor speed (0-255)
/smart_car/control/speed/left           # Left motor speed (0-255)
```

### Monitor Topics (Publish)
```
/smart_car/monitor/distance/forward     # Forward distance (cm)
/smart_car/monitor/distance/backward    # Backward distance (cm)
/smart_car/monitor/track/right          # Right line sensor state
/smart_car/monitor/track/left           # Left line sensor state
/smart_car/monitor/rpy/roll             # Roll angle (degrees)
/smart_car/monitor/rpy/pitch            # Pitch angle (degrees)
/smart_car/monitor/rpy/yaw              # Yaw angle (degrees)
/smart_car/monitor/acc/x                # X-axis acceleration
/smart_car/monitor/acc/y                # Y-axis acceleration
/smart_car/monitor/acc/z                # Z-axis acceleration
/smart_car/monitor/temp/mpu6050         # Temperature (°C)
```

---

## 🚀 Getting Started

### Prerequisites
- **ESP-IDF v4.4+** (for embedded firmware)
- **ROS2 Humble/Iron** (for robot simulation)
- **MATLAB** (for system analysis) - Optional
- **MQTT Broker** (e.g., Mosquitto)
- **Python 3.8+**

### 1. Build and Flash ESP32 Firmware

```bash
cd embedded_iot/

# Configure project
idf.py menuconfig

# Build firmware
idf.py build

# Flash to ESP32 (replace /dev/ttyUSB0 with your port)
idf.py -p /dev/ttyUSB0 flash

# Monitor serial output
idf.py -p /dev/ttyUSB0 monitor
```

### 2. Setup ROS2 Environment

```bash
cd ros2/

# Build ROS2 packages
colcon build

# Source the environment
source install/setup.bash

# Launch URDF visualization
ros2 launch ros_elegoo robot_state_publisher.launch.py
```

### 3. Start MQTT Broker

```bash
# Install Mosquitto (if not already installed)
sudo apt-get install mosquitto mosquitto-clients

# Start broker
mosquitto -c /etc/mosquitto/mosquitto.conf

# Monitor topics (in another terminal)
mosquitto_sub -h localhost -t "/smart_car/#" -v
```

### 4. Test Communication

```bash
# Publish test command
mosquitto_pub -h localhost -t "/smart_car/control/forward" -m "1"

# Check sensor readings
mosquitto_sub -h localhost -t "/smart_car/monitor/distance/forward" -v
```

---

## 🎯 Key Features Explained

### 1. **Real-time Motor Control**
- PWM-based speed control (0-255 range)
- Independent left/right motor control for turning
- PID controller for consistent velocity

### 2. **Collision Avoidance**
- Dual ultrasonic sensors (forward/backward distance detection)
- TCRT5000 IR sensors for close-range obstacle detection
- Automatic emergency stop if object detected
- Adaptive speed reduction based on proximity

### 3. **ROS2 SLAM & Autonomous Navigation**
- Real-time Simultaneous Localization and Mapping (SLAM)
- Autonomous path planning and obstacle avoidance
- Dynamic map building in Gazebo virtual environments
- Integration with Gazebo LiDAR simulator

### 4. **Node-RED Remote Control Dashboard**
- Web-based graphical user interface
- Real-time control commands via MQTT
- Visual feedback and status monitoring
- Easy-to-use button interface for all operations

### 5. **IMU-based Orientation Tracking**
- MPU6050 provides 6-axis motion data (accelerometer + gyroscope)
- Calculates roll, pitch, yaw angles
- Odometry data for pose estimation

### 6. **Machine Learning (Edge Impulse)**
- Classification model for sensor pattern recognition
- Regression model for continuous value prediction
- Intelligent sensor data interpretation
- Runs on ESP32 for edge computing

---

## 📊 SLAM & Mapping System

Scout Robot features an advanced **SLAM (Simultaneous Localization and Mapping)** system using ROS2 SLAM Toolbox:

- **Real-time Map Building** - Constructs 2D occupancy grid maps from LiDAR/sensor data
- **Dynamic Localization** - Tracks robot position within the built map
- **Gazebo Integration** - Full simulation in virtual industrial warehouse environment
- **Occupancy Grid** - Distinguishes free space from obstacles for autonomous navigation

### ROS2 Plugins in Simulation
1. **Differential Drive Plugin** - Simulates wheel physics and publishes `/odom` data
2. **Ray Sensor (LiDAR) Plugin** - Publishes `/scan` data for SLAM processing
3. **IMU Plugin** - Provides realistic inertial measurement data

---

## 🎨 Node-RED Dashboard & Mosquitto Broker

### Node-RED Visualization Layer
Node-RED provides a **flow-based programming interface** for real-time remote control:

- **Web-based Dashboard UI** - Intuitive graphical interface for operators
- **MQTT Integration** - Direct connection to Mosquitto broker
- **Real-time Command Execution** - Button clicks map to MQTT topics
  - "Forward" button → `/smart_car/control/forward` topic
  - Speed controls → `/smart_car/control/speed/left|right` topics
- **Status Monitoring** - Visual feedback via UI LEDs connected to monitor topics
- **Asynchronous Communication** - Robust, efficient system operation

### Mosquitto MQTT Broker
Acts as the **central message hub** for the entire IoT system:
- Receives control commands from Node-RED dashboard
- Distributes commands to ESP32 micro-explorer
- Collects sensor data from ESP32
- Routes data back to Node-RED for visualization
- Ensures real-time, reliable communication

---

## 🤖 ROS2 Integration

### Launch Robot Visualization
```bash
ros2 launch ros_elegoo display.launch.py
```

### View in RViz2
- Robot URDF is automatically loaded
- Sensor frames visualized
- Real-time SLAM map display
- Joint states updated in real-time
- Mesh models for realistic rendering

### Gazebo Simulation
```bash
ros2 launch ros_elegoo gazebo.launch.py
```

---

## 🧠 Edge Impulse Machine Learning Integration

Scout Robot incorporates an **optional ML layer** using Edge Impulse platform for intelligent sensor data analysis:

### ML Capabilities
- **Classification Model** - Pattern recognition in sensor data
  - Detect specific movement patterns
  - Recognize environmental conditions
  - Classify terrain types
  
- **Regression Model** - Continuous value prediction
  - Distance estimation refinement
  - Speed optimization prediction
  - Temperature trend analysis

### ML Workflow
```
Raw Sensor Data (CSV from MPU6050, Ultrasonic, TCRT5000)
        ↓
Upload to Edge Impulse Platform
        ↓
Data Preprocessing & Feature Extraction
        ↓
Model Training (Classification & Regression)
        ↓
Model Testing & Validation
        ↓
Deploy to ESP32 Embedded System
        ↓
Real-time Inference & Decision Making
```

### Running ML on Scout Robot
```cpp
// Edge Impulse library integration (in ESP32 firmware)
#include "edge-impulse-sdk/classifier.h"

// Collect sensor data → Run inference → Execute intelligent action
// All processing happens on-device (edge computing)
```

---

## 📈 Performance Specifications

| Metric | Value |
|--------|-------|
| **Max Speed** | ~30 cm/s (configurable) |
| **Turning Radius** | Differential drive (in-place rotation) |
| **Sensor Range** | 2-400 cm (ultrasonic) |
| **Update Rate** | 50 Hz (20ms cycle) |
| **WiFi Range** | ~50m (line-of-sight) |
| **Battery Life** | 3-4 hours (continuous operation) |
| **Processing Power** | Dual 240MHz cores (ESP32) |

---

## 🔧 Configuration

All configuration parameters are in `embedded_iot/main/main.h`:

```cpp
// WiFi Credentials
#define ssid        "Your_SSID"
#define password    "Your_Password"

// MQTT Broker Settings
#define mqtt_broker "mqtt://192.168.100.25"
#define mqtt_port   1883

// Motor Speed (0-255)
#define DEFAULT_SPEED 200

// Collision Distance Threshold (cm)
#define COLLISION_DISTANCE 20
```

---

## 📝 Contributing

Contributions are welcome! Please feel free to submit pull requests or open issues for bugs and feature requests.

### Development Guidelines
- Follow ESP-IDF coding conventions
- Comment complex algorithms
- Test on real hardware before submission
- Update documentation for new features

---

## 📄 License

This project is licensed under the BSD License - see the documentation for details.

---

## 👨‍💻 Author

**Ziad Mohamed Fathy**  
Embedded Systems & Robotics Engineer  
Scout Robot Project Lead  
contact@scoutrobot.project

---

## 📚 References & Resources

- [ESP-IDF Official Documentation](https://docs.espressif.com/projects/esp-idf/)
- [ROS2 Documentation](https://docs.ros.org/en/humble/)
- [MQTT Protocol Specification](https://mqtt.org/)
- [SolidWorks to URDF Conversion](http://wiki.ros.org/urdf)

---

## 🎯 Roadmap

- [ ] **Gazebo Environment Expansion** - Create additional warehouse/indoor worlds
- [ ] **Advanced SLAM Algorithms** - Implement graph-based SLAM
- [ ] **Obstacle Avoidance Optimization** - Machine learning-based path planning
- [ ] **Multi-Robot Fleet Management** - Coordinate multiple Scout robots
- [ ] **Web Dashboard Enhancement** - Full Node-RED control center
- [ ] **3D LiDAR Integration** - Replace ultrasonic with full LiDAR
- [ ] **Real-time Video Streaming** - Camera module integration
- [ ] **Autonomous Docking** - Self-charging capability
- [ ] **MQTT Message Encryption** - Security improvements

---

**Last Updated**: December 2025  
**Project Status**: Active Development ✅  
**Repository**: [Scout Robot on GitHub](https://github.com)
