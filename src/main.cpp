
#include <iostream>
#include "hal.h"
#include "mongoose_glue.h"


static void blink_timer(void *arg) {
  (void) arg;
  gpio_write(LED1, !gpio_read(LED1));
}

int main(void) {
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