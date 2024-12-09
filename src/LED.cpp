//
// Created by starry on 24-12-9.
//

#include "LED.h"
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

#define LED_PATH "/sys/class/leds/beaglebone:green:usr"

LED::LED(int number){
    this->number = number;
    std::ostringstream s;
    s << LED_PATH << number;
    path = std::string(s.str());
}
LED::LED(std::string path,int number){
    this->number = number;
    std::ostringstream s;
    s << path << number;
    path = std::string(s.str());
}
void LED::writeLED(std::string filename, std::string value){
    std::ofstream fs;
    fs.open((path+filename).c_str());
    fs << value;
    fs.close();
}
int LED::readLED(std::string filename){
    std::string r;
    std::ifstream fs;
    fs.open((path+filename).c_str());
    fs >> r;
    fs.close();
    return stoi(r);
}

void LED::removeTrigger(){
    writeLED("/trigger", "none");
}

void LED::turnOn(){
    std::cout << "Turning LED" << number << " on." << std::endl;
    removeTrigger();
    writeLED("/brightness", "1");
}

void LED::turnOff(){
    std::cout << "Turning LED" << number << " off." << std::endl;
    writeLED("/brightness", "0");
}
void LED::toggle(){
    std::cout << "toggle LED" << number << std::endl;
    writeLED("/brightness", "0");

}
void LED::status_set(bool s)
{
    if (s)
        turnOn();
    else
        turnOff();
}

void LED::flash(std::string delayms = "50"){
    std::cout << "Making LED" << number << " flash." << std::endl;
    writeLED("/trigger", "timer");
    writeLED("/delay_on", delayms);
    writeLED("/delay_off", delayms);
}

void LED::outputState(){
    std::ifstream fs;
    fs.open((path + "/trigger").c_str());
    std::string line;
    while(getline(fs, line)) std::cout << line << std::endl;
    fs.close();
}

LED::~LED(){
    std::cout <<"Destroying the LED object with path: " << path << std::endl;
}