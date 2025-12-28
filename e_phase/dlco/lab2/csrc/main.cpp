#include <nvboard.h>
#include <Vtop.h>
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
static TOP_NAME dut;

void nvboard_bind_all_pins(TOP_NAME* top);

static void single_cycle() {
  dut.eval();
}

static void reset(int n) {
  // while (n -- > 0) single_cycle();
}

int main() {
  // nvboard_bind_all_pins(&dut);
  // nvboard_init();
  bool  test_add_pass = true;
  bool  test_sub_pass = true;
  reset(10);

  for(int i=-8; i<=7; i++){
    for(int j=-8; j<=7; j++){
      dut.x = i;
      dut.y = j;
      dut.sub = 0;
      single_cycle();

      int8_t expect = (int8_t)(i+j) & 0xf;
      if(dut.z != expect){
        test_add_pass = false;
        printf("%d + %d expect %d but return %d \n", dut.x, dut.y, expect, dut.z);
      }
    }
  }
  if(test_add_pass){
    printf("[PASS] all add \n");
  }

  for(int i=-8; i<=7; i++){
    for(int j=-8; j<=7; j++){
      dut.x = i;
      dut.y = j;
      dut.sub = 1;
      single_cycle();

      int8_t expect = (int8_t)(i-j) & 0xf;
      if(dut.z != expect){
        test_sub_pass = false;
        printf("%d - %d expect %d but return %d \n", dut.x, dut.y, expect, dut.z);
      }
    }
  }
  if(test_sub_pass){
    printf("[PASS] all sub \n");
  }

  while(1) {
    // nvboard_update();
    single_cycle();
  }
}
