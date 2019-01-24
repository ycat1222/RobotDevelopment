#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

#include<BBB_error.hpp>

namespace BBB{
class PWM
{
  public:
	PWM() {}
    //先に有効化するPWMについて、pwmNum = 15,
    //後に有効化するPWMについて、pwmNum = 16 が対応
    PWM(int pinNum, int pwmNum);

    void setPeriod(int period);
	void setDutyRate(double rate);
    void setPolarity(bool polarity = 0);
    void run();
    void stop();

    int period();
    int duty();
	double dutyRate();
    bool polarity();
    bool isRun();

    static const std::vector<int> availablePwmPinNum;

  private:
	void setDuty(int duty);
    std::string PWMPath;

    static const int CAPEMGR = 9;
    static const int OCP = 3;
    static const int pinConnector = 9;
	static const int PERIOD = 10000000;
};
};

