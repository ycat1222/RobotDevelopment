#include "BBB_gpio.hpp"

using namespace std;
using namespace BBB;

const std::vector<int> GPIO::availableGpioNum = 
    {60, 48, 49, 117, 115, 112, 20, 66, 67, 69, 68, 45, 44, 26, 47, 46, 27, 65, 61};

GPIO::GPIO(int gpioNum_)
{
    bool isGPIOexist;

    for(auto num : availableGpioNum)
        if(gpioNum_ == num) isGPIOexist = true;

    if(isGPIOexist){
        gpioNum = gpioNum_;
        ofstream file("/sys/class/gpio/export", ios::binary);
        file << gpioNum;
        isGPIOSetted = true;
    } else {
        throw std::runtime_error("存在しないGPIO番号が参照されました");
    }
}

GPIO::~GPIO()
{
    ofstream file("/sys/class/gpio/unexport", ios::binary);
    file.write((char *)&gpioNum, sizeof(gpioNum));
}

void GPIO::setDirection(bool is_IN)
{
    if(!isGPIOSetted) throw std::runtime_error("GPIO番号が設定されていません");

    stringstream path;
    path << "/sys/class/gpio/gpio" << gpioNum << "/direction";

    ofstream file(path.str());

    if (is_IN)
        file << "in";
    else
        file << "out";
}

void GPIO::setEdge(bool is_both)
{
    if(!isGPIOSetted) throw std::runtime_error("GPIO番号が設定されていません");

    stringstream path;
    path << "/sys/class/gpio/gpio" << gpioNum << "/edge";

    ofstream file(path.str());

    if (is_both)
        file << "both";
    //else  よくわからない;
}

void GPIO::setActiveLow()
{
    if(!isGPIOSetted) throw std::runtime_error("GPIO番号が設定されていません");

    stringstream path;
    path << "/sys/class/gpio/gpio" << gpioNum << "/active_low";

    ofstream file(path.str(), ios::binary);
    file.write((char *)1, sizeof(int));
}

int GPIO::getValue()
{
    if(!isGPIOSetted) throw std::runtime_error("GPIO番号が設定されていません");
    
    stringstream path;
    path << "/sys/class/gpio/gpio" << gpioNum << "/value";

    ifstream file(path.str(), ios::binary);
    int value;
    file.read((char *)&value, sizeof(int));
    return value;
}