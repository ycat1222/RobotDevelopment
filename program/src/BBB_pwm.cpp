#include "BBB_pwm.hpp"

using namespace std;

std::vector<int> PWM::availablePwmPinNum = {14, 16, 13, 19};

PWM::PWM(int capemgr, int ocp, int pinConnector, int pinNum, int pwmNum)
{
    stringstream path;
    path << "/sys/devices/bonecapemgr." << capemgr << "/slots";

    ofstream pwmFile(path.str());
    pwmFile << "am33xx_pwm";
    pwmFile.close();

    pwmFile = ofstream(path.str());
    pwmFile << "bone_pwm_P" << pinConnector << "_" << pinNum;

    path << "/sys/devices/ocp." << ocp << "pwm_test_P" 
        << pinConnector << "_" << pinNum << "." << pwmNum;
    PWMPath = path.str();
}

void PWM::setPeriod(int period)
{
    ofstream file(PWMPath + "/period", ios::binary);
    file.write((char *)&period, sizeof(period));
}

void PWM::setDuty(int duty)
{
    ofstream file(PWMPath + "/duty", ios::binary);
    file.write((char *)&duty, sizeof(duty));
}

void PWM::setPolarity(bool polarity)
{
    ofstream file(PWMPath + "/polarity", ios::binary);
    file.write((char *)&polarity, sizeof(polarity));
}

void PWM::run()
{
    ofstream file(PWMPath + "/run", ios::binary);
    file.write((char *)1, sizeof(int));
}

void PWM::stop()
{
    ofstream file(PWMPath + "/run", ios::binary);
    file.write((char *)0, sizeof(int));
}

int PWM::getPeriod()
{
    ifstream file(PWMPath + "/period", ios::binary);
    int period;
    file.read((char *)&period, sizeof(period));
    return period;
}

int PWM::getDuty()
{
    fstream file(PWMPath + "/duty", ios::binary);
    int duty;
    file.read((char *)&duty, sizeof(duty));
    return duty;
}

bool PWM::getPolarity()
{
    ifstream file(PWMPath + "/polarity", ios::binary);
    int tmp;
    file.read((char *)&tmp, sizeof(tmp));
    if (tmp == 0)
        return 0;
    else
        return 1;
}

bool PWM::getIsRun()
{
    ifstream file(PWMPath + "/run", ios::binary);
    int tmp;
    file.read((char *)&tmp, sizeof(tmp));
    if (tmp == 1)
        return true;
    else
        return false;
}