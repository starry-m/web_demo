#include "hal.h"
#include "mongoose_glue.h"
#include <thread>
#include "mymain.h"
#include "LED.h"

using namespace std;
int run_led=0;

//LED led = LED(3);
//LED mled0 = LED(0);
//LED mled1 = LED(1);
//LED mled2 = LED(2);
static bool led_status=false;
static void blink_timer(void *arg) {
  (void) arg;
  gpio_write(LED1, !gpio_read(LED1));
//  if(run_led)
//  {
//    if(led_status)
//    {
//        led_status= false;
//        led.turnOn();
//    } else
//    {
//        led_status = true;
//        led.turnOff();
//    }
//  }

}
#if defined(__cplusplus)
extern "C" {
#endif
void update_led_status(bool led1,bool led2,bool led3)
{
//    mled0.status_set(led1);
//    mled1.status_set(led2);
//    mled2.status_set(led3);
}
#if defined(__cplusplus)
}
#endif

void web_thread()
{
    MG_INFO(("HAL initialised, starting firmware..."));

    // This blocks forever. Call it at the end of main(), or in a
    // separate RTOS task. Give that task 8k stack space.
    mongoose_init();
    mg_timer_add(&g_mgr, 1000, MG_TIMER_REPEAT, blink_timer, NULL);
    for (;;) {
        mongoose_poll();
    }
}


int main(int argc, char* argv[]) {
//    if(argc != 2){
//        cout << "Args error, on/off/flash/status supported only." << endl;
//        return 1;
//    }

    if(argc >=  2)
    {
        run_led=1;

    }
    sysConfigInit();
  // Cross-platform hardware init
  hal_init();
//    std::thread mongoose_thread(web_thread);
//    mongoose_thread.join();
  return 0;
}