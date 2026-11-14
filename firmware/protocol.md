# Pi-Arduino
- Example message from the Pi to the arduino, at 20hz.
- Communication will run at 115200 baud rate between Pi and Arduino. Lost lines will get ignored; the pi is telling the arduino what to do at 20hz.
- Watchdog timeout on arduino will be 500ms, timeout will stop motors and wait for a new message from the pi.

`ML251R-129\n`

- M - command letter, Movement
- L251 - left wheel 251mm/s forward
- R-129 - right wheel 129mm/s backward


# Arduino - Pi
- Example message from the arduino to the pi, at 20hz

T8701L588R-1907{IMU}

- Timestamp [T] , Count Left, Count Right, IMU readouts