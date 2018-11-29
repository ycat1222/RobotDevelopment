#include<BBB_gpio.hpp>
#include<BBB_pwm.hpp>

namespace BBB{
class Motor{
public:
    void setPWM(int pinNum);
    void setGPIO(int gpioNumIN1, int gpioNumIN2);
    void runNormalRotation();
    void runReverseRotation();
    
private:
    PWM pwm;
    GPIO IN1, IN2;
};
};