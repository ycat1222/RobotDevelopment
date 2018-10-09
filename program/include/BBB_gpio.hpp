#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

namespace BBB{
class GPIO
{
  public:
    GPIO(){};
    GPIO(int gpioNum_);

    void setGPIO(int gpioNum_) { *this = GPIO(gpioNum_); };
    //inならtrue、outならfalse
    void setDirection(bool is_IN);
    void setEdge(bool isBoth);
    void setActiveLow();

    int getValue();
    int getGPIONum() { return gpioNum; }


    static std::vector<int> const availableGpioNum;

    ~GPIO();

  private:
    int gpioNum;

};
};




