#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;
const int BTN_PIN_G = 26;

const int LED_GREEN = 4; 
const int LED_RED = 6; 


volatile int g_cnt_verde = 0;
volatile int g_cnt_vermelho = 0;

void btn_callback(uint gpio, uint32_t events) {
  if (events == 0x4) { // fall edge
    if (gpio == BTN_PIN_R)
    g_cnt_vermelho = 1;
  }
  if (events ==0x8){
    if (gpio == BTN_PIN_G)
  g_cnt_verde = 1;  }
  }
int main() {
  stdio_init_all();

  int estado = 0; 

  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);

  gpio_init(BTN_PIN_G);
  gpio_set_dir(BTN_PIN_G, GPIO_IN);
  gpio_pull_up(BTN_PIN_G);

  gpio_init(LED_GREEN);
  gpio_set_dir(LED_GREEN, GPIO_OUT);

  gpio_init(LED_RED);
  gpio_set_dir(LED_RED, GPIO_OUT);

  // callback led r (first)
  gpio_set_irq_enabled_with_callback(BTN_PIN_R, GPIO_IRQ_EDGE_FALL, true,
                                     &btn_callback);
                                     
  gpio_set_irq_enabled_with_callback(BTN_PIN_G, GPIO_IRQ_EDGE_RISE, true,
                                     &btn_callback);



  while (true) {
    if (g_cnt_verde){
      estado = !estado;
      gpio_put(LED_RED,estado);
      g_cnt_verde = 0;
    }
    else if (g_cnt_vermelho){
      estado = !estado;
      gpio_put(LED_GREEN,estado);
      g_cnt_vermelho = 0;
    }


  }
}
