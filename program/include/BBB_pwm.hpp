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
    //先に有効化するPWMについて、pwmNum = 15,
    //後に有効化するPWMについて、pwmNum = 16 が対応
    PWM(int pinNum, int pwmNum);

    void setPeriod(int period);
    void setDuty(int duty);
    void setPolarity(bool polarity = 0);
    void run();
    void stop();

    int getPeriod();
    int getDuty();
    bool getPolarity();
    bool isRun();

    static const std::vector<int> availablePwmPinNum;

  private:
    std::string PWMPath;

    static const int capemgr = 9;
    static const int ocp = 3;
    static const int pinConnector = 9;
};
};

