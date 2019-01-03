# pi-l298n.git
l298n
	|--motor_1
	|  |--direction_logic+
	|  |--direction_logic-
	|  |--magnitude_control
	|--motor_2
	   |--direction_logic+
	   |--direction_logic-
	   |--magnitude_control

	** direction logic high and low signals 
	** are written to output pins using wiringPi

	** magnitude control pwm signals are written
	** to the motors by pigpio library

	** COMPILE
	**	$ mkdir build 
	**	$ cd build
	**	$ cmake .. && make

	** USE AS ROS MODULE
	** in top level directory CMakeLists.txt:
	** add_subdirectory( l298n-driver )
	** target_link_libraries( <target_name>
	** LINK_PUBLIC l298n-driver
	** )

	** SETUP
	** Remove EN1 and EN2 jumpers for controlling DC
	** motor.
	** remove jumper next to OUT1 if using voltage
	** supply greater than 12V
