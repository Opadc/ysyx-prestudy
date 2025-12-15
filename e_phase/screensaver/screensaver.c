#include <am.h>
#include <klib-macros.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 300
static uint32_t canvas[SCREEN_HEIGHT][SCREEN_WIDTH];

static inline uint8_t R(uint32_t p) { return p >> 16; }
static inline uint8_t G(uint32_t p) { return p >> 8; }
static inline uint8_t B(uint32_t p) { return p; }
static inline uint32_t pixel(uint8_t r, uint8_t g, uint8_t b) {
  return (r << 16) | (g << 8) | b;
}

void draw(uint32_t color) {
  // add code here
  AM_GPU_CONFIG_T info = io_read(AM_GPU_CONFIG);
  int w = info.width, h = info.height;
  for(uint32_t i=0; i<SCREEN_HEIGHT; i++){
    for(uint32_t j=0; j<SCREEN_WIDTH; j++){
      canvas[i][j] = color;
    }
  }

  io_write(AM_GPU_FBDRAW, 0, 0, canvas, w, h, true);

}

const uint32_t all_colors[] = {0x000000, 0xff0000, 0x00ff00, 0x0000ff, 0xffff00, 0xff00ff, 0x00ffff, 0xffffff};
#define COLOR_NUMS (sizeof(all_colors)/sizeof(uint32_t))
#define MAX_STEPS (5)
int main() {
  uint32_t step = 0;
  ioe_init(); // initialization for GUI
  srand(time(NULL));

  int32_t true_sec = 1;
  int sec = 1;

  while (1) {
    uint32_t curr_color = all_colors[rand()%COLOR_NUMS];
    uint32_t next_color = all_colors[rand()%COLOR_NUMS];
    printf("curr_color: %x, next_color: %x\n", curr_color, next_color);
    while(1){
      uint32_t next_r = R(curr_color) + (R(next_color)-R(curr_color))*(step*100/MAX_STEPS)/100;
      uint32_t next_g = G(curr_color) + (G(next_color)-G(curr_color))*(step*100/MAX_STEPS)/100;
      uint32_t next_b = B(curr_color) + (B(next_color)-B(curr_color))*(step*100/MAX_STEPS)/100;
      uint32_t step_color = pixel(next_r, next_g, next_b);
      step = (step + 1) % MAX_STEPS;
      printf("next_r: %x, next_g: %x, next_b: %x\n", next_r, next_g, next_b);
      printf("step color: %x\n", step_color);
      draw(step_color);

      uint32_t speed_up = 0;
      
      while(io_read(AM_TIMER_UPTIME).us / 1000000 + speed_up < sec){
          AM_INPUT_KEYBRD_T ev = io_read(AM_INPUT_KEYBRD);
          if (ev.keycode == AM_KEY_ESCAPE){
            return 0; 
          }else{
            if(ev.keydown){
                speed_up += 100000;
            }else{
                sec = true_sec;
                speed_up = 0;
                
            }
          }
      };
      sec ++;
      true_sec++;




      if(step == 4){
        break;
      }
    }
    

  }
  return 0;
}
