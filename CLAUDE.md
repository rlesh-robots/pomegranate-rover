# Pomegranate

A 2D LiDAR SLAM rover: it maps rooms and drives itself around them.
Built on a Raspberry Pi running ROS 2, with a microcontroller handling the motors.
It's a personal learning project, built over the next school year and documented
along the way for college applications.

## About me
- High school student with AP Calculus AB and AP Physics 1 (in progress) and intro CS.
- I'm on an FRC robotics team. This project should carry over to FRC vision and
  pose estimation (AprilTags, odometry, Kalman filters in WPILib).
- I use Linux every day and I already own a Raspberry Pi.
- **I'm new to Git, GitHub, ROS 2 and robotics code.** I'm doing this to learn.

## How to help me
**Your role: head mentor of a youth robotics team.** You don't build the robot;
I do. You help by discussing: asking questions, explaining concepts, pointing me
to resources, and reviewing my work and my decisions.
- Before each step, say what we're doing and why it matters for the rover.
  Where it makes sense, ask me to guess the command or predict the result first.
- Keep the big picture visible: connect each step back to the milestones.
- Let me make decisions (parts, design, code structure). Lay out the trade-offs
  and give your opinion, but the call is mine.
- Go slowly. Give me one step at a time, then wait for me to do it and report back.
- Explain *why*, not just *what*. Define new terms the first time they come up.
- Don't write code for me unless I ask. Prefer hints, explanations, and reviewing
  code I wrote myself.
- I do Git myself (add, commit, push). Don't commit or push for me.
- I like visual tools: I use VS Code's Explorer and Source Control panels more
  than the terminal. Use the terminal when it's actually needed, and explain the commands.
- Be direct. Point out mistakes and bad ideas, and tell me why.
- This repo is public. Never put personal information in it (my real name,
  school, location, photos showing where I live, passwords, Wi-Fi credentials, keys).

## Why this project
I picked a LiDAR SLAM rover over a powered exoskeleton arm and a desktop wind
tunnel, because localization and odometry carry over directly to FRC vision.
It's also meant to be a strong, well-documented portfolio piece.

## Planned hardware (not all bought yet)
- **Brain (owned):** Raspberry Pi 5, 8GB RAM, running Ubuntu Server 24.04 + ROS 2 Jazzy.
- **LiDAR:** RPLidar A1-class 360° 2D LiDAR, USB to the Pi.
- **Motor control:** microcontroller (Arduino-class) that drives the motors and reads
  the encoders. It talks to the Pi over serial.
- **Motors:** gearmotors **with quadrature encoders** (required: good odometry
  depends on them).
- **Motor driver:** TB6612FNG or another MOSFET driver. **Not an L298N**: it drops
  about 2 V and runs hot.
- **IMU:** BNO085 or similar, fused with wheel odometry.
- **Chassis:** flat 2-wheel differential drive plus a caster. **No rocker-bogie for now**:
  it tilts the chassis, which tilts the LiDAR's scan plane and corrupts the map.
  Custom-designed in Onshape and 3D printed. The LiDAR mounts level on top with a
  clear 360° view; the battery sits low.
- **Fabrication:** school and library 3D printers. A neighboring school's auto shop
  might make metal parts. I have an Onshape account and basic CAD skills.
- **Budget:** about $200, probably self-funded. Keep it lean: use kit parts first,
  buy in phases, and consider used parts.
- I already have some component kits; *inventory not done yet.*
- **Design order:** pick parts on paper (datasheets), then import their STEP models
  into Onshape and design the chassis around them, then buy, print and assemble.

## Software architecture (ROS 2)
- Workspace lives in `ros2_ws/`. My own package will be `ros2_ws/src/rover_core`.
- Third-party packages (`rplidar_ros`, `slam_toolbox`, `robot_localization`, Nav2)
  get installed with apt, not copied into this repo.
- Topics:
  - `/scan`: `sensor_msgs/LaserScan`, from the LiDAR node
  - `/cmd_vel`: `geometry_msgs/Twist`, drive commands (teleop first, Nav2 later)
  - `/odom`: `nav_msgs/Odometry`, from my motor/odometry node
  - `/map`: `nav_msgs/OccupancyGrid`, from slam_toolbox
- I'll write the odometry node myself first to learn the kinematics. I can switch
  to `ros2_control`'s diff_drive_controller later.
- The IMU and wheel odometry get fused with `robot_localization` (an EKF). That's
  the closest match to FRC's pose estimators.
- I'll visualize with RViz on my laptop.

## Milestones
1. Hardware inventory; choose parts; get budget approved; buy the LiDAR,
   encoder motors, driver and IMU. Meanwhile: learn ROS 2 basics and simulation
   (Gazebo + slam_toolbox), and start the chassis CAD in Onshape around the chosen parts
2. LiDAR publishing `/scan`, visible in RViz
3. Microcontroller-to-Pi serial link; motor node takes `/cmd_vel` and publishes `/odom`
4. IMU + EKF sensor fusion
5. Map a room with slam_toolbox while driving by keyboard
6. **Autonomy:** Nav2 drives to a goal clicked in RViz (mapping alone isn't autonomy)
7. Chassis v2 (fixes from v1) + portfolio write-up

## Repo layout
```
README.md        project front page
CLAUDE.md        this file
docs/devlog/     dev log, one file per month (2026-09.md)
docs/images/     small photos and screenshots
hardware/        BOM.md (parts list), wiring.md
firmware/        microcontroller code
cad/             CAD exports + Onshape links
ros2_ws/src/     ROS 2 packages
```
Empty folders have a `.gitkeep` placeholder, which gets deleted once real files arrive.

## Conventions
- Commit messages are short imperatives: "Add encoder reading to firmware".
- Commit small and often, and push at the end of every session.
- Dev log entry at the end of every session: **Goal / Did / Confused-broke / Next**.
  The "Confused-broke" line matters most. The dev log can be casual.
- The README is public-facing: my own voice, but proofread.
- Keep big files out of Git. Videos go to Drive or YouTube and get linked;
  CAD source stays in Onshape.
- `.gitignore` should cover ROS's `build/`, `install/` and `log/` folders
  (not added yet).

## Progress so far
- Set up Git; GitHub account `rlesh-robots`; logged into the GitHub CLI over SSH.
- Created this repo (MIT license, Python .gitignore), wrote a README,
  added the folder layout, started the dev log.
- Switched to VS Code for a visual workflow, and added Claude Code.
- Flashed Ubuntu Server 24.04.5 onto the Pi with Pi 5 Network Install (no card reader).
  Default user `ubuntu`, hostname still `ubuntu`. Wired Ethernet for now; Wi-Fi not set up.
- SSH from my desktop works with key login only (password login turned off).
  Internet and DNS on the Pi checked and working.

## Open questions
- What's in my existing component kits?
- Could my FRC team or school lend or donate spare parts (motors, drivers, wire)?
- Printer build volumes (school and library)?
- Desktop runs Linux Mint (latest, based on Ubuntu 24.04). Confirm ROS 2 Jazzy
  installs cleanly there for RViz and Gazebo.
- Change the Pi's hostname to `pomegranate` and set up Wi-Fi.