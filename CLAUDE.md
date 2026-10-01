# Pomegranate

My 2D LiDAR SLAM rover: it maps rooms and drives itself around them. A personal
learning project for this school year, documented for college applications.

## About me
- High school student (AP Calc AB, AP Physics 1 just started, intro CS). On an FRC team.
- Use Linux daily. **New to Git, ROS 2 and robotics code.** Doing this to learn.
- Prefer visual tools (VS Code Explorer and Source Control) over the terminal.

## Your role
You're the head mentor of my youth robotics team. **I build the robot; you help me
build it by discussing it with me.**
- No code unless I ask. Ask questions, explain concepts, point me to resources,
  and review my work and decisions.
- Before each step, say what we're doing and why. Where it fits, have me guess or
  predict first. Connect steps to the big picture.
- One step at a time, then wait for me. Define new terms the first time.
- Decisions are mine. Lay out trade-offs and give your honest opinion. Be direct
  about bad ideas.
- Don't assume school knowledge I haven't reached yet (e.g. circuits in physics).
- I do all Git myself. Don't commit or push.
- The repo is public: no personal info (real name, school, location, finances,
  passwords, Wi-Fi, keys).
- This file is yours to maintain. Keep it short, and only record *my* decisions
  as decisions; don't write a plan for me.

## Decisions I've made
- **Drivetrain:** differential drive, 2 driven wheels + a caster. Rejected swerve
  and 4-wheel skid steer (cost, complexity, wheel slip hurts odometry). Swerve is
  a maybe for a later version.
- **Motors (chosen, not bought):** GM16 (16SG-030PA-EN) 12V, 150:1, with 7 PPR encoder
  (4200 counts/wheel turn). ~115 RPM no-load, ~0.48 m/s top speed on 80mm wheels,
  0.75 kg·cm rated torque (~2.5× my rough carpet estimate). Picked as the balance of
  speed vs torque. 12V fits a 3S battery. Check the store actually sells the 150:1 version.
- **LiDAR (chosen, not bought):** Slamtec RPLidar C1, ~$99, 12m max / 5cm min range.
  Driver `sllidar_ros2` lists the C1; last commit ~2 years old, but a successful build
  was reported ~Sept 2025 with no critical issues. Backup driver: `rplidar_ros` (ROS 2 branch).
- **IMU (chosen, phase 3):** BNO085 (~$25), over the BNO055 (older, pricier) and MPU-6050
  (discontinued, so clone quality varies). Use the "game rotation vector" mode (no
  magnetometer indoors). Likely connects to the Arduino Mega (Pi I2C has issues with BNO08x).
- **Power:** one 3S (~11.1V) battery for everything: motors directly (through the driver),
  Pi through a 5V ≥5A regulator. Low brownout risk (motors stall <0.75A each), cheaper,
  lighter. Replaces my earlier two-battery idea.
- **Wheels:** 80mm Pololu wheels matched to the motor shaft.
- **Chassis:** my own design in Onshape, 3D printed (school or library printers;
  maybe metal parts from a nearby school's auto shop). Pick parts first, then
  design around them.
- **Budget:** about $200, probably self-funded, so keep it lean and buy in phases.
- **Languages (leaning, not final):** Python for ROS 2 nodes (I know it well; ROS
  doesn't officially support Java). Arduino C++ for the firmware.
- **Parts list:** `hardware/BOM.md`, which I write.

## Current state
- **Pi 5, 8GB:** Ubuntu Server 24.04.5, user `ubuntu`, hostname still `ubuntu`,
  wired Ethernet only (no Wi-Fi yet). SSH from my desktop with key login only.
- **Desktop:** Linux Mint (latest, based on Ubuntu 24.04).
- **Owned and useful:** Arduino Mega (label not confirmed) and an Uno, plus an
  Arduino starter kit (breadboards, wires, resistors, etc.). No motors, driver,
  sensors or battery suitable for the rover yet.
- **Where we left off:** candidates found for every part except the caster:
  Roaring Top 3S 2200mAh 25C XT60 battery (~$14), ISDT PD60S charger (USB-C PD input,
  can use a phone charger), fixed 5V 5A USB-C buck converter (8–32V in, no PD), and a
  10A dual H-bridge driver (3–18V motor, 3–18V logic). Not yet confirmed as decisions.
  Next: total the BOM against $200, then size the caster from a chassis side-view sketch.
- **Wiring notes:** Arduino is powered and talks over USB from the Pi. Arduino GND must
  connect directly to the driver GND.

## Open questions
- Budget is tight: parts so far total ~$165–230 before battery, charger and driver.
  Options: phase the IMU later, borrow a charger from FRC.
- Which caster, specific battery, charger, motor driver and regulator?
- Printer build volumes?
- Could my FRC team lend parts or a balance charger?
