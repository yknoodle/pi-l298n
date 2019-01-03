#include "l298n.h"
#include <iostream>

int main (int argc, char const* argv[])
{
	L298NDriver driver;
	driver.initialise();
	driver.convertCommand(.87, WHEEL_LEFT);
	std::cout << driver.getMotorMagnitude(WHEEL_LEFT) << "\n";
	std::cout << driver.getMotorDirection(WHEEL_LEFT) << "\n";
	driver.executeCommand();
	return 0;
}
