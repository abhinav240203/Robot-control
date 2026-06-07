# ROS2 Control Robot Project

This project demonstrates a ROS2-based robot simulation using ros2_control, Gazebo, and custom robot description packages. The robot is controlled using a velocity-based controller 
via ROS2 topics.

---

## Project Structure

```
robot_ws/
├── src/
│   ├── robot_controller/
│   │   ├── config/
│   │   │   └── robot_controller.yaml
│   │   ├── include/
│   │   ├── launch/
│   │   │   └── controller.launch.py
│   │   ├── src/
│   │   ├── CMakeLists.txt
│   │   └── package.xml
│   │
│   ├── robot_cpp/
│   │   ├── include/
│   │   ├── src/
│   │   │   └── simple_parameter.cpp
│   │   ├── CMakeLists.txt
│   │   └── package.xml
│   │
│   ├── robot_description/
│   │   ├── launch/
│   │   │   ├── display.launch.py
│   │   │   └── gazebo.launch.py
│   │   ├── meshes/
│   │   │   ├── base_link.STL
│   │   │   ├── caster_front_link.STL
│   │   │   ├── caster_rear_link.STL
│   │   │   ├── imu_link.STL
│   │   │   ├── wheel_left_link.STL
│   │   │   └── wheel_right_link.STL
│   │   ├── rviz/
│   │   │   └── display.rviz
│   │   ├── urdf/
│   │   │   ├── robot.urdf.xacro
│   │   │   ├── robot_gazebo.xacro
│   │   │   └── robot_ros2_control.xacro
│   │   ├── CMakeLists.txt
│   │   └── package.xml
│   │
│   └── robot_py/
│       ├── resource/
│       ├── robot_py/
│       │   ├── __init__.py
│       │   └── simple_parameters.py
│       ├── test/
│       ├── package.xml
│       ├── setup.cfg
│       └── setup.py
│
├── images/
│   ├── gazebo.png
│   ├── rviz.png
│
├── videos/
│   └── ros2_control.webm
```

---

## Installation

### Install ROS2 dependencies

```bash
sudo apt update
sudo apt install ros-jazzy-desktop \
  ros-jazzy-ros-gz \
  ros-jazzy-robot-state-publisher \
  ros-jazzy-joint-state-publisher-gui
```

### Install workspace dependencies

```bash
rosdep update
rosdep install --from-paths src --ignore-src -r -y
```

---

## Build Workspace

```bash
cd ~/robot_ws
colcon build --symlink-install
source install/setup.bash
```

---

## Run Simulation

### Launch Gazebo

```bash
ros2 launch robot_description gazebo.launch.py
```

### Start Controllers (new terminal)

```bash
source ~/robot_ws/install/setup.bash
ros2 launch robot_controller controller.launch.py
```

---

## Control the Robot

```bash
ros2 topic pub /simple_velocity_controller/commands std_msgs/msg/Float64MultiArray "data:
- 1.0
- 0.0"
```

---

## Notes

- Always launch Gazebo first
- Then start controller in a new terminal
- Always source workspace before running ROS2 commands
- Check active controllers:

```bash
ros2 control list_controllers
```
