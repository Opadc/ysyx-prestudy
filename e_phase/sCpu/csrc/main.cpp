#include <nvboard.h>
#include <Vtop.h>
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include "verilated_fst_c.h"

static TOP_NAME *top;

void nvboard_bind_all_pins(TOP_NAME* top);

static void single_cycle() {
  top->clk = 0; top->eval();
  top->clk = 1; top->eval();
}

static void reset(int n) {
  top->rst = 0;
  while (n -- > 0) single_cycle();
  top->rst = 1;
}

int main(int argc, char** argv) {
  VerilatedContext* contextp = new VerilatedContext;
  contextp->commandArgs(argc, argv);

  top = new TOP_NAME{contextp};
  nvboard_bind_all_pins(top);
  nvboard_init();

  Verilated::traceEverOn(true);
  VerilatedFstC* tfp = new VerilatedFstC;
  top->trace(tfp, 99);
  tfp->open("simx.fst");

  reset(10);

  while(1) {
    contextp->timeInc(1);
    nvboard_update();
    single_cycle();
    // tfp->dump(contextp->time());
    
  }
  tfp->close();
}
