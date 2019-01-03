#include "l298n.h"
#include <cmath>
#include "pigpiod_if2.h"
#include <iostream>
L298NDriver::~L298NDriver()
{
	pigpio_stop(fd);
}

L298NDriver::L298NDriver() : pwm_resolution( 1e6 )
{
	hw_map = new uint8_t[6];

	//PWM0
	hw_map[WHEEL_MAG_LEFT] = 12; // physical pin 32

	// HIGH when forward
	hw_map[WHEEL_DIR_LEFT_H] = 8; // physical pin 24 (IN1)

	// LOW when forward
	hw_map[WHEEL_DIR_LEFT_L] = 7; // physical pin 26 (IN2)

	// PWM1
	hw_map[WHEEL_MAG_RIGHT] = 13; // physical pin 33

	// HIGH when forward
	hw_map[WHEEL_DIR_RIGHT_H] = 5; // physical pin 29 (IN3)

	// LOW when forward
	hw_map[WHEEL_DIR_RIGHT_L] = 6; // physical pin 31 (IN4)


	lrm_mag = new uint32_t[2];
	lrm_dir = new uint8_t[2];


}

int L298NDriver::initialise()
{
	fd = pigpio_start(NULL, NULL);
	if (fd < 0) return 1;

	set_mode
	(
		fd,
		hw_map[WHEEL_MAG_LEFT],
		PI_ALT0
	);
	set_mode
	(
		fd,
		hw_map[WHEEL_DIR_LEFT_H],
		PI_OUTPUT
	);
	set_mode
	(
		fd,
		hw_map[WHEEL_DIR_LEFT_L],
		PI_OUTPUT
	);
	set_mode
	(
		fd,
		hw_map[WHEEL_MAG_RIGHT],
		PI_ALT0
	);

	set_mode
	(
		fd,
		hw_map[WHEEL_DIR_RIGHT_H],
		PI_OUTPUT
	);
	set_mode
	(
		fd,
		hw_map[WHEEL_DIR_RIGHT_L],
		PI_OUTPUT
	);
}


void L298NDriver::setPin( uint8_t hardware, uint8_t pin )
{
	hw_map[ hardware ] = pin;
}

void L298NDriver::executeCommand()
{

	gpio_write
	(
		fd,
		hw_map[WHEEL_DIR_LEFT_H],
		lrm_dir[WHEEL_LEFT] == false
	);

	gpio_write
	(
		fd,
		hw_map[WHEEL_DIR_LEFT_L],
		lrm_dir[WHEEL_LEFT] == true
	);

	hardware_PWM
	(
		fd,
		hw_map[WHEEL_MAG_LEFT],
		100,
		lrm_mag[WHEEL_LEFT]
	);

	gpio_write
	(
		fd,
		hw_map[WHEEL_DIR_RIGHT_H],
		lrm_dir[WHEEL_RIGHT] == false
	);
	gpio_write
	(
		fd,
		hw_map[WHEEL_DIR_RIGHT_L],
		lrm_dir[WHEEL_RIGHT] == true
	);

	hardware_PWM
	(
		fd,
		hw_map[WHEEL_MAG_RIGHT],
		100,
		lrm_mag[WHEEL_RIGHT]
	);
}

void L298NDriver::convertCommand( double cmd, uint8_t wheel)
{
	lrm_dir[wheel] = cmd < 0;
	lrm_mag[wheel] =
		(uint32_t) std::round( fabs(cmd) * pwm_resolution );
}

void L298NDriver::storeMotorCommands( double* cmd )
{
	convertCommand( cmd[WHEEL_LEFT], WHEEL_LEFT);
	convertCommand( cmd[WHEEL_RIGHT], WHEEL_RIGHT);
}

uint32_t L298NDriver::getMotorMagnitude(uint8_t wheel)
{
	return lrm_mag[wheel];
}

uint8_t L298NDriver::getMotorDirection(uint8_t wheel)
{
	return lrm_dir[wheel];
}
