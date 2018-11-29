#include "BBB_pwm.hpp"

using namespace std;
using namespace BBB;

std::vector<int> const PWM::availablePwmPinNum = {14, 22};

//先に有効化するPWMについて、pwmNum = 15,
//後に有効化するPWMについて、pwmNum = 16 が対応
PWM::PWM(int pinNum, int pwmNum)
{
    bool isPinNumExist = false;

    for(auto num : availablePwmPinNum){
        if(num == pwmNum) isPinNumExist = true;
    }
    if(!isPinNumExist) ErrorBBB("This pinNum is NOT exist.");

    stringstream path;
    path << "/sys/devices/bonecapemgr." << capemgr << "/slots";

    ofstream pwmFile(path.str());
    pwmFile << "am33xx_pwm";
    pwmFile.close();

    ofstream pwmFile2(path.str());
    pwmFile2 << "bone_pwm_P" << pinConnector << "_" << pinNum;

    path << "/sys/devices/ocp." << ocp << "pwm_test_P" 
        << pinConnector << "_" << pinNum << "." << pwmNum;
    PWMPath = path.str();
}

void PWM::setPeriod(int period)
{
    ofstream file(PWMPath + "/period", ios::binary);
    file.write(to_string(period).c_str(), sizeof(int));
}

void PWM::setDuty(int duty)
{
    ofstream file(PWMPath + "/duty", ios::binary);
    file.write(to_string(duty).c_str(), sizeof(int));
}

void PWM::setPolarity(bool polarity)
{
    ofstream file(PWMPath + "/polarity", ios::binary);

    if(polarity) file.write("1", sizeof(int));
    else         file.write("0", sizeof(int));
}

void PWM::run()
{
    ofstream file(PWMPath + "/run", ios::binary);
    file.write("1", sizeof("1"));
}

void PWM::stop()
{
    ofstream file(PWMPath + "/run", ios::binary);
    file.write("0", sizeof("0"));
}

int PWM::getPeriod()
{
    ifstream file(PWMPath + "/period", ios::binary);
    int period;
    file.read(reinterpret_cast<char*>(&period), sizeof(int));
    return period;
}

int PWM::getDuty()
{
    fstream file(PWMPath + "/duty", ios::binary);
    int duty;
    file.read(reinterpret_cast<char*>(&duty), sizeof(duty));
    return duty;
}

bool PWM::getPolarity()
{
    ifstream file(PWMPath + "/polarity", ios::binary);
    int tmp;
    file.read(reinterpret_cast<char*>(&tmp), sizeof(tmp));
    
    if (tmp == 0) return 0;
    else          return 1;
}

bool PWM::isRun()
{
    ifstream file(PWMPath + "/run", ios::binary);
    int tmp;
    file.read(reinterpret_cast<char*>(&tmp), sizeof(tmp));

    if (tmp == 1) return true;
    else          return false;
}