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
    path << "/sys/devices/bone_capemgr." << capemgr << "/slots";

    ofstream pwmFile(path.str());
    if(!pwmFile) ErrorBBB("Cannot Open File");
    pwmFile << "am33xx_pwm";
    pwmFile.close();

    ofstream pwmFile2(path.str());
    pwmFile2 << "bone_pwm_P" << pinConnector << "_" << pinNum;

    stringstream path2;
    path2 << "/sys/devices/ocp." << ocp << "/pwm_test_P" 
          << pinConnector << "_" << pinNum << "." << pwmNum;

    PWMPath = path2.str();

	setPeriod(PERIOD);
}

void PWM::setPeriod(int period)
{
    ofstream file(PWMPath + "/period", ios::binary);
    file << period;
}

void PWM::setDuty(int duty)
{
    //注意 : 回路によって、ON/OFF時間が反転しているため、
    //      その措置(period() - duty)を含む
    auto _duty = period() - duty;
    ofstream file(PWMPath + "/duty", ios::binary);
    file << _duty;
}

void BBB::PWM::setDutyRate(double rate)
{
	//rateが、0 から 1の間のときだけ、dutyを設定する
	if(rate >= 0 && rate <= 1.0) setDuty(rate*period());
	else throw ErrorBBB("Duty rate is not valid.");
}

void PWM::setPolarity(bool polarity)
{
    ofstream file(PWMPath + "/polarity", ios::binary);

    if(polarity) file << 1;
    else         file << 0;
}

void PWM::run()
{
    ofstream file(PWMPath + "/run", ios::binary);
    file << 1;
}

void PWM::stop()
{
    ofstream file(PWMPath + "/run", ios::binary);
    file << 0;
}

int PWM::period()
{
    ifstream file(PWMPath + "/period", ios::binary);
    int period;
    file >> period;
    return period;
}

int PWM::duty()
{
    fstream file(PWMPath + "/duty", ios::binary);
    int duty;
    file >> duty;
    return period() - duty;
}

double BBB::PWM::dutyRate()
{
	return (double)duty() / period();
}

bool PWM::polarity()
{
    ifstream file(PWMPath + "/polarity", ios::binary);
    int polarity;
   
    if (polarity == 0) return 0;
    else               return 1;
}

bool PWM::isRun()
{
    ifstream file(PWMPath + "/run", ios::binary);
    int isRun_;
    file >> isRun_;

    if (isRun_ == 1) return true;
    else             return false;
}