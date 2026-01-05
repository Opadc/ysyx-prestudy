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
  while (n -- > 0) single_cycle();
}

int main() {
  nvboard_bind_all_pins(&dut);
  nvboard_init();
  reset(10);


  while(1) {
    nvboard_update();
    single_cycle();
  }
}
