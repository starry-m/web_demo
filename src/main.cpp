
#include <iostream>
#include "hal.h"
#include "mongoose_glue.h"

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

using namespace std;

#define LED_PATH "/sys/class/leds/beaglebone:green:usr"

class LED{
private:
    string path;
    int number;
    virtual void writeLED(string filename, string value);
    virtual int readLED(string filename);

    virtual void removeTrigger();
public:
    LED(int number);
    virtual void turnOn();
    virtual void turnOff();
    virtual void toggle();
    virtual void status_set(bool s);
    virtual void flash(string delayms);
    virtual void outputState();
    virtual ~LED();
};

LED::LED(int number){

    this->number = number;
    ostringstream s;
    s << LED_PATH << number;
    path = string(s.str());

}

void LED::writeLED(string filename, string value){
    ofstream fs;
    fs.open((path+filename).c_str());
    fs << value;
    fs.close();
}
int LED::readLED(string filename){
    string r;
    ifstream fs;
    fs.open((path+filename).c_str());
    fs >> r;
    fs.close();
}
void LED::removeTrigger(){
    writeLED("/trigger", "none");
}

void LED::turnOn(){
    cout << "Turning LED" << number << " on." << endl;
    removeTrigger();
    writeLED("/brightness", "1");
}

void LED::turnOff(){
    cout << "Turning LED" << number << " off." << endl;
    writeLED("/brightness", "0");
}
void LED::toggle(){
    cout << "toggle LED" << number << endl;
    writeLED("/brightness", "0");

}
void LED::status_set(bool s)
{
    if (s)
        turnOn();
    else
        turnOff();
}

void LED::flash(string delayms = "50"){
    cout << "Making LED" << number << " flash." << endl;
    writeLED("/trigger", "timer");
    writeLED("/delay_on", delayms);
    writeLED("/delay_off", delayms);
}

void LED::outputState(){
    ifstream fs;
    fs.open((path + "/trigger").c_str());
    string line;
    while(getline(fs, line)) cout << line << endl;
    fs.close();
}

LED::~LED(){
    cout <<"Destroying the LED object with path: " << path << endl;
}
int run_led=0;

LED led = LED(3);
LED mled0 = LED(0);
LED mled1 = LED(1);
LED mled2 = LED(2);
static bool led_status=false;
static void blink_timer(void *arg) {
  (void) arg;
  gpio_write(LED1, !gpio_read(LED1));
  if(run_led)
  {
    if(led_status)
    {
        led_status= false;
        led.turnOn();
    } else
    {
        led_status = true;
        led.turnOff();
    }



  }

}
#if defined(__cplusplus)
extern "C" {
#endif
void update_led_status(bool led1,bool led2,bool led3)
{
    mled0.status_set(led1);
    mled1.status_set(led2);
    mled2.status_set(led3);
}
#if defined(__cplusplus)
}
#endif
int main(int argc, char* argv[]) {
//    if(argc != 2){
//        cout << "Args error, on/off/flash/status supported only." << endl;
//        return 1;
//    }

    if(argc >=  2)
    {
        run_led=1;

    }

//    string cmd(argv[1]);



//    if(cmd=="on") led.turnOn();
//    else if (cmd=="off") led.turnOff();
//    else if (cmd=="flash") led.flash("100");
//    else if (cmd=="status") led.outputState();
//    else {
//        cout << "Command invalid" << endl;
//        return 1;
//    }

  // Cross-platform hardware init
  hal_init();
  MG_INFO(("HAL initialised, starting firmware..."));

  // This blocks forever. Call it at the end of main(), or in a
  // separate RTOS task. Give that task 8k stack space.
  mongoose_init();
  mg_timer_add(&g_mgr, 1000, MG_TIMER_REPEAT, blink_timer, NULL);
  for (;;) {
    mongoose_poll();
  }

  return 0;
}