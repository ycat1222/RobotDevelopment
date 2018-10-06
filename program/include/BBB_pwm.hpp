#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

class PWM
{
  public:
    PWM(int capemgr, int ocp, int pinConnector, int pinNum, int pwmNum);

    void setPeriod(int period);
    void setDuty(int duty);
    void setPolarity(bool polarity = 0);
    void run();
    void stop();

    int getPeriod();
    int getDuty();
    bool getPolarity();
    bool getIsRun();

    static const std::vector<int> availablePwmPinNum;

  private:
    std::string PWMPath;
};

