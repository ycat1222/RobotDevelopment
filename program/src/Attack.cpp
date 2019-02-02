#include "Attack.hpp"

void BBB::attack()
{
	RobotController robot;
	robot.initPosition(15, 15);
	robot.initMotorGPIO(61, 60, 65, 46);
	robot.initMotorPWM(14, 22);
	robot.initSensorGPIO(27, 47, 115, 45);

	robot.moveEast(150);



}
