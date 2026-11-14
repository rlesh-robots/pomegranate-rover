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
- **LiDAR (arrived 2026-11-03):** Slamtec RPLidar C1, ~$99, 12m max / 5cm min range.
  Driver `sllidar_ros2` lists the C1; last commit ~2 years old, but a successful build
  was reported ~Sept 2025 with no critical issues. Backup driver: `rplidar_ros` (ROS 2 branch).
  Neither apt driver supports the C1 (apt `rplidar_ros` is 2.1.0 from 2022; its C1 support is
  unreleased; `rplidar_driver` doesn't mention C1), so I build `sllidar_ros2` from source:
  cloned into `ros2_ws/src/`, git-ignored, URL + commit noted in `docs/Tools.md`.
  On the Pi the CP210x adapter shows up as `/dev/ttyUSB0`; user `ubuntu` added to `dialout`.
- **IMU (chosen, phase 3):** BNO085 (~$25), over the BNO055 (older, pricier) and MPU-6050
  (discontinued, so clone quality varies). Use the "game rotation vector" mode (no
  magnetometer indoors). Connects to the Arduino Mega over I2C (pins 20/21), since Pi I2C has
  issues with BNO08x; its data goes to the Pi as a later protocol message type.
- **Power:** one 3S (~11.1V) battery for everything: motors directly (through the driver),
  Pi through a 5V ≥5A regulator. Low brownout risk (motors stall <0.75A each), cheaper,
  lighter. Replaces my earlier two-battery idea.
- **Wheels:** 80mm Pololu wheels matched to the motor shaft.
- **Chassis:** my own design in Onshape, 3D printed (school or library printers;
  maybe metal parts from a nearby school's auto shop). Pick parts first, then
  design around them.
- **Pi mounting:** bare Pi 5 on standoffs (no CanaKit case), for a simpler design. Needs
  cooling: reuse the case's fan if it comes out, else buy an active cooler.
- **Layout (first CAD draft):** two drive wheels in front, caster trailing behind, Pi on
  a raised mount in the middle. Plate was 2.5mm; motor mount and second level not designed yet.
- **Budget:** about $200, probably self-funded, so keep it lean and buy in phases.
- **ROS:** ROS 2 Jazzy (matches Ubuntu 24.04; Humble would need 22.04). Pi gets
  `ros-jazzy-ros-base` (no GUI); RViz runs on the desktop. Following the official
  docs.ros.org Jazzy deb install (2025+ `ros2-apt-source` method). Pi locale is C.UTF-8 (fine).
- **Desktop ROS:** install ROS 2 Jazzy (`ros-jazzy-desktop`) on Mint to run RViz locally.
  Chosen over X11 forwarding (laggy 3D), Foxglove (third-party) and Docker.
- **Speed control on the Arduino:** the Pi sends target wheel speeds; the Arduino runs the
  feedback loop (encoder → motor power) because it has precise, steady timing and sits next to
  the hardware (like FRC motor controllers). Pi does kinematics, odometry, SLAM, navigation.
- **Languages (leaning, not final):** Python for ROS 2 nodes (I know it well; ROS
  doesn't officially support Java). Arduino C++ for the firmware.
- **Parts list:** `hardware/BOM.md`, which I write.

## Current state
- **Pi 5, 8GB:** Ubuntu Server 24.04.5, user `ubuntu`, hostname still `ubuntu`,
  Ethernet plus Wi-Fi (netplan file `/etc/netplan/60-wifi.yaml` on the Pi, not in the repo).
  SSH from my desktop with key login only.
- **ROS on the Pi:** Jazzy `ros-base` + `ros-dev-tools` installed and working; sourced
  from `~/.bashrc`. SSH shortcut on desktop: `ssh Pomegranate` (in `~/.ssh/config`).
- **Desktop:** Linux Mint (latest, based on Ubuntu 24.04).
- **Owned and useful:** Arduino Mega (label not confirmed) and an Uno, plus an
  Arduino starter kit (breadboards, wires, resistors, etc.). Arrived by 2026-11-04:
  LiDAR, 1 GM16 gearmotor (second one ordered), 3S battery,
  charger, LiPo bag, 5V buck converter, wheels, IMU. A parent agreed to buy the whole BOM at
  once (2026-11-08); most has arrived. Still in transit: second gearmotor, motor driver (and
  possibly other slow items).
- **Parts (the BOM picks, all ordered):** Roaring Top 3S 2200mAh 25C
  XT60 battery (22.4×32×102mm, 159g), ISDT PD60S charger (USB-C PD input, XT60 +
  JST-XH balance port), fixed 5V 5A USB-C buck converter (8–32V in, no PD), 10A dual
  H-bridge driver (3–18V motor and logic), McMaster 24215T69 caster ($2.62: 2" nylon twin-wheel
  swivel, 60.3mm mount height, 3/8"-16 × 3/4" stem, STEP available; picked over the
  1-5/8" version to climb my ~10mm rug edge, and over the D50 M8 with no published
  height), LiPo bag. FRC team's charger doesn't fit.
- **Where we left off:** chassis in Onshape, driven by variables. Plate 5mm, underside at
  caster height (60.325mm). Mirrored motor walls at the plate's side edges: 4mm thick,
  15.6 wide, motor centre 20.325 below the plate, wall runs 12 below the centre, 6mm
  chamfer as gusset (clears the motor top by ~6.6mm). From the GM16 drawing: 2× M2
  holes 9mm apart (Ø2.4 clearance), boss Ø4.0 × 1.5 (Ø4.5 hole), 3mm D-shaft 10mm long,
  body 36mm long, JST ZH 6-pin connector. 2mm pocket for the gearbox face, so ~8mm of
  shaft past the wall: full grip for the 6.5mm Pololu hub (3mm D insert). Tire clearance:
  ring groove (Ø71–Ø89 around the axle) cut 6mm into the plate edge. Front of the plate is
  ~30mm ahead of the axle, so the tires stick out in front. Next: caster position, battery
  placement (tipping), second level.
- **CAD:** paused until I measure the real parts, which are mostly here now.
- **Software progress:** derived diff-drive kinematics myself (in `docs/Tools.md`: inverse
  and forward, plus counts→m/s with Δcounts/Δt, 0.0000598 m per count). Protocol design:
  text lines ending in `\n`, cumulative encoder counts, Arduino watchdog stops motors;
  no retransmission (repeating commands + cumulative counts make lost lines harmless; maybe
  an "OK" ack later for one-off commands). Draft motor command: `ML251R-129` (whole mm/s).
  115200 baud (well under 5% used); Arduino watchdog timeout 500 ms. Arduino → Pi sends
  cumulative counts + an Arduino timestamp (Pi computes speed with the Arduino's Δt, not
  arrival times; a timestamp going backwards means the Arduino reset).
  Spec being written in `firmware/protocol.md`. Ran and read the
  demo_nodes_py talker/listener/qos/serialized nodes; understand nodes, publishers,
  subscriptions, timers, callbacks, spin and QoS (tested the best-effort → reliable mismatch).
  Python classes/inheritance are new to me; practice still recommended.
  Repo cloned on the Pi (`~/pomegranate-rover`, deploy key with write access, no-reply
  git email). Practice package `ros2_ws/src/py_pubsub` (ament_python): my own talker
  (`MyTalker`, node `my_talker`, topic `my_chatter`, entry point `talker`) works with
  `ros2 run py_pubsub talker`; committed and pushed from the Pi. Build with
  `colcon build --symlink-install` from `ros2_ws`, then `source install/setup.bash`.
  Listener (`MyListener`, node `my_listener`, entry point `listener`) also works;
  talker → listener over `my_chatter` confirmed.
- **LiDAR working:** `sllidar_ros2` built (warnings only) and `ros2 launch sllidar_ros2
  sllidar_c1_launch.py` publishes `/scan` at a steady ~10.0 Hz (~720 points/scan, frame
  `laser`). ROS 2 Jazzy desktop installed on Mint (UBUNTU_CODENAME=noble, no workaround
  needed) and the desktop sees the Pi's `/scan` over the wired network. **Milestone 2 done
  (2026-11-04):** `/scan` visible in RViz on the desktop (Fixed Frame `laser`, LaserScan display).
- **Encoder working (2026-11-05):** `firmware/encoder_test` counts every edge of A and B
  (×4) with two `CHANGE` interrupts and copies `count` with interrupts paused. Measured
  ~4200 counts per wheel turn, which confirms 150:1. Pins: left motor A→2, B→3; right
  motor A→18, B→19 (20/21 stay free for the IMU). Table in `hardware/Wiring.md`. My ISRA sign is opposite to my original written
  rule; I'll set the final sign with a "forward = up" test. The sketch also prints wheel
  speed in m/s (100 ms `millis()` window, Δcounts/Δt, float math); a steady turn every 2 s
  read ~0.13 m/s as predicted. Hand-spun max ~0.55 m/s (don't back-drive hard: gearbox, back-EMF).
- **Hardware to buy:** M2 screw assortment (thread depth unknown: wall + ~2mm, never
  force), 3/8"-16 nuts for the caster, M2.5 standoffs for the Pi.
- **Network problem (unsolved):** home has two networks. Wired (desktop, Pi eth0) is
  192.168.0.x; the Wi-Fi comes from a second router behind it (Pi wlan0 is on
  192.168.68.x/22). The desktop can't reach the Pi's Wi-Fi address, and it has no Wi-Fi
  card. SSH still works over Ethernet (192.168.0.75). Needs fixing before the rover
  drives untethered (ROS also needs both on one network). Options: Wi-Fi router into
  access point mode (needs a parent's OK), or a USB Wi-Fi adapter for the desktop.
  I decided to defer this and keep working over Ethernet for now.
- **Printer:** Prusa Core One, build volume 250 × 220 × 270mm.
- **Wiring notes:** Arduino is powered and talks over USB from the Pi. Arduino GND must
  connect directly to the driver GND. Motor listing confirms 150:1, 7 PPR; encoder runs
  on 3.3–5V, so the Mega's 5V pin powers it. Wiring table goes in `hardware/Wiring.md`.

## Open questions
- BOM total is ~$210 before shipping (phase 1 ≈ $110, LiDAR + IMU ≈ $100), plus
  unlisted small parts: power switch, fuse, XT60 connectors and wire, screws, filament.
- Where does the weight go so the rover doesn't tip forward when it stops (battery position)?
- Second level for the Pi, Mega and LiDAR: not designed yet.
