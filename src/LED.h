//
// Created by starry on 24-12-9.
//

#ifndef WEB_DEMO_LED_H
#define WEB_DEMO_LED_H

#include<string>

class LED {
private:
    std::string public_path;
    std::string path;
    int number;
    virtual void writeLED(std::string filename,std::string value);
    virtual int readLED(std::string filename);

    void removeTrigger();
public:
    LED(int number);
    LED(std::string path,int number);
    virtual void turnOn();
    virtual void turnOff();
    virtual void toggle();
    virtual void status_set(bool s);
    virtual void flash(std::string delaymson,std::string delaymsoff);
    void change_mode_status(bool sate,int mode,int blink_delay_on,int blink_delay_off);
    virtual void outputState();
    virtual ~LED();
};


#endif //WEB_DEMO_LED_H
