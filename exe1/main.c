#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;
volatile int g_cnt = -1;

void btn_callback(uint gpio, uint32_t events) {
  if (events == 0x4) { 
    g_cnt = 1;
  } 
  if (events == 0x8) { 
    g_cnt = 0;
  }
}

int main() {
  stdio_init_all();

  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);

  gpio_set_irq_enabled_with_callback(
      BTN_PIN_R, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &btn_callback);

  while (true) {
    if (g_cnt == 1) {
      printf("fall\n");
      g_cnt = -1;
    } 
    else if (g_cnt == 0) {
      printf("rise\n");
      g_cnt = -1; 
    }
    sleep_ms(10); 
  }
}
