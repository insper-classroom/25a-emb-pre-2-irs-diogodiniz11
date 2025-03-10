#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;
const int LED = 4; 
volatile int g_cnt = 0;

void btn_callback(uint gpio, uint32_t events) {
  if (events == 0x4) { 
    g_cnt = 1;
  } 
}

int main() {
  stdio_init_all();
  bool estado = false;

  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);

  gpio_init(LED);
  gpio_set_dir(LED, GPIO_OUT);

  gpio_set_irq_enabled_with_callback(
      BTN_PIN_R, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &btn_callback);

  while (true) {
    if (g_cnt){
      estado = !estado;
      gpio_put(LED,estado);
      g_cnt = 0;
    }
    sleep_ms(10);

  }
}
