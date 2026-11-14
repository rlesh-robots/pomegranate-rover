# Docs, equations i learn, Important stuff for when im coding and testing.

inverse Kinematics
Velocity (left wheel) = Velocity (forward) - baseWidth/2 * w | v_left = v − (b/2)·ω

Velocity (right wheel) = Velocity (forward) + baseWidth/2 * w | v_right = v + (b/2)·ω

forward Kinematics
Velocity (angular) = (Vright - Vleft) / BaseWidth | ω = (v_right − v_left) / b

Velocity (forward) = (Vleft + Vright) / 2 | v = (v_left + v_right) / 2

Velocity (wheel) = Encoder counts * meters per count / t | (Δcounts*m/c)/Δt 
(meters per count is 0.06 millimeters / 0.0000598 meters
4200 counts per turn, on an 80mm wheel, 2piR = 251.33 circumference
251 / 4200 = 0.05976190476
)

LiDAR driver: sllidar_ros2, https://github.com/Slamtec/sllidar_ros2, commit 3430009. i already gitignored it.
To launch the driver, these commands are necessary:

cd ~/pomegranate-rover/ros2_ws
source install/setup.bash
ros2 launch sllidar_ros2 sllidar_c1_launch.py

source install/setup.bash is needed because i have to tell ros2 where the install file is.

## For examples
/opt/ros/jazzy/lib/python3.12/site-packages/demo_nodes_py/ \
/\ \
go here for publisher/listener nodes with timed examples