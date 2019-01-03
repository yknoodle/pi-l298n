#ifndef __L298N_DRIVER_H__
#define __L298N_DRIVER_H__

#include <cstdint>

enum Wheel
{
	WHEEL_LEFT,
	WHEEL_RIGHT,
	WHEEL_END
};

enum WheelHW
{
	WHEEL_MAG_LEFT,
	WHEEL_DIR_LEFT_H,
	WHEEL_DIR_LEFT_L,
	WHEEL_MAG_RIGHT,
	WHEEL_DIR_RIGHT_H,
	WHEEL_DIR_RIGHT_L,
	WHEEL_DIR_END
};

class L298NDriver
{
	public:
		/*
		** assign new memory addresses
		** set default pwm resolution ( 10-bit )
		** set default hardware locations
		*/
		L298NDriver();

		/*
		** deletes memory assignments
		*/
		virtual ~L298NDriver ();

		void setPin( uint8_t hardware, uint8_t pin );
		int initialise();

		void convertCommand(double cmd, uint8_t wheel);

		// place command in buffer
		void storeMotorCommands(double* cmd);
		
		// writes command to motors
		void executeCommand();

		uint32_t getMotorMagnitude(uint8_t wheel);
		uint8_t getMotorDirection(uint8_t wheel);

	private:
		// should only initialize with 2 motors
		// shows which pwm pin each motor is connected to
		uint8_t fd;
		uint8_t* hw_map;
		uint8_t* lrm_dir;
		uint32_t* lrm_mag;
		const int32_t pwm_resolution;
};

#endif /* __L298N_DRIVER_H__ */
