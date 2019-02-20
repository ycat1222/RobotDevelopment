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


    if(!isGPIOexist){
        throw ErrorBBB("This GPIO num is NOT exist.");
    }
    gpioNum = gpioNum_;
    ofstream file("/sys/class/gpio/export", ios::binary);
	if (!file) throw ErrorBBB("Cannot open /sys/class/gpio/export");
    file << gpioNum;
    isGPIOSetted = true;
}

void GPIO::setGPIO(int gpioNum_)
{
	new(this) GPIO(gpioNum_);
}

GPIO::~GPIO()
{
    ofstream file("/sys/class/gpio/unexport", ios::binary);
    file << gpioNum;
}

void BBB::GPIO::activate()
{
	ofstream file("/sys/class/gpio/export", ios::binary);
	if (!file) throw ErrorBBB("Cannot open /sys/class/gpio/export");
	file << gpioNum;
}

void BBB::GPIO::disActivate()
{
	ofstream file("/sys/class/gpio/unexport", ios::binary);
	if (!file) throw ErrorBBB("Cannot open /sys/class/gpio/export");
	file << gpioNum;
}

void GPIO::setDirection(bool is_IN)
{
    if(!isGPIOSetted) throw ErrorBBB("GPIO num has NOT been set.");

    stringstream path;
    path << "/sys/class/gpio/gpio" << gpioNum << "/direction";

    ofstream file(path.str());

    if (is_IN) file << "in";
    else	   file << "out";
}

void BBB::GPIO::setDirection(Direction d)
{
	if (!isGPIOSetted) throw ErrorBBB("GPIO num has NOT been set.");

	stringstream path;
	path << "/sys/class/gpio/gpio" << gpioNum << "/direction";

	ofstream file(path.str());

	if (d == IN)	   file << "in";
	else if (d == OUT) file << "out";
}

void GPIO::setEdge(bool is_both)
{
    if(!isGPIOSetted) throw ErrorBBB("GPIO num has NOT been set.");

    stringstream path;
    path << "/sys/class/gpio/gpio" << gpioNum << "/edge";

    ofstream file(path.str());

    if (is_both)
        file << "both";
    //else  よくわからない;
}

void GPIO::setActiveLow()
{
    if(!isGPIOSetted) throw ErrorBBB("GPIO num has NOT been set.");

    stringstream path;
    path << "/sys/class/gpio/gpio" << gpioNum << "/active_low";

    ofstream file(path.str(), ios::binary);
    file << 1;
}

void GPIO::setValue(bool isActive)
{
    if(!isGPIOSetted) throw ErrorBBB("GPIO num has NOT been set.");
    
    stringstream path;
    path << "/sys/class/gpio/gpio" << gpioNum << "/value";

    ofstream file(path.str(), ios::binary);
	std::string errStr = "Cannot open ./gpio/gpio" + to_string(gpioNum) + "/value";
    if(!file) throw ErrorBBB(errStr);
    
    if(isActive) file << 1;
    else         file << 0;
}

int GPIO::value()
{
    if(!isGPIOSetted) throw ErrorBBB("GPIO num has NOT been set.");
    
    stringstream path;
    path << "/sys/class/gpio/gpio" << gpioNum << "/value";

    ifstream file(path.str(), ios::binary);
    int value;
    file >> value;
    return value;
}