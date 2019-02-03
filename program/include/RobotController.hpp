#pragma once
#include <chrono>
#include <iostream>
#include <cmath>
#include <thread>
#include <mutex>
#include "BeagleBone_Black.hpp"

using namespace BBB;

class RobotController{
public:
	RobotController() {};
	void initMotorPWM(int motor1_PWM, int motor2_PWM);
	void initMotorGPIO(int motor1_IN1, int motor1_IN2, int motor2_IN1, int motor2_IN2);
	void initSensorGPIO(int east, int west, int south, int north);
	void initPosition(size_t __x, size_t __y);
	void correctPosition();

	double aveDutyRate();
	void mSecWait(const size_t mSec);

	bool checkRobotProperties();
	void moveEastTime(const size_t mSec);
	void moveWestTime(const size_t mSec);
	void moveSouthTime(const size_t mSec);
	void moveNorthTime(const size_t mSec);

	void moveEast(const double distance);
	void moveWest(const double distance);
	void moveSouth(const double distance);
	void moveNorth(const double distance);

	double distanceEast();
	double distanceWest();
	double distanceSouth();
	double distanceNorth();

	void setDutyRate(double bothMotorRate);
	void setDutyRate(double motor1Rate, double motor2Rate);

	//座標系の単位は[cm]
	size_t x();
	size_t y();

private:
	Motor motor1, motor2;
	UltraSonicSensor sensorEast, sensorWest, sensorSouth, sensorNorth;

	bool isSetMotorPWM = false,
		isSetMotorGPIO = false,
		isSetSensorGPIO = false,
		isInitializePosition = false;

	double dutyRate_Motor1ToMotor2 = 1.0;
	const double DUTY_TO_VELOCITY = 0.03811;

	size_t eastTime = 0, westTime = 0, southTime = 0, northTime = 0;
	size_t _x, _y;

	std::mutex mtx;
};