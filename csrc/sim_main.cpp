#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Vtop.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

#include <nvboard.h>

VerilatedContext* contextp = new VerilatedContext;
Vtop* top = NULL;

void nvboard_bind_all_pins(Vtop *top);

void single_cycle() {
	top->clock = 0; top->eval(); nvboard_update();
	top->clock = 1; top->eval(); nvboard_update();
}

void reset(int n) {
	top->reset = 1;
	while (n -- > 0) single_cycle();
	top->reset = 0;
}

void sim_init(int argc, char** argv) {
	top = new Vtop{contextp};
	contextp->commandArgs(argc, argv);
	nvboard_bind_all_pins(top);
	nvboard_init();
}

void sim_end() {
	top->final();
	delete top;
	delete contextp;
	nvboard_quit();
}

int main(int argc, char** argv)
{
	sim_init(argc, argv);

	reset(10);
	while(1) {
		single_cycle();
	}

	sim_end();
	return 0;

}
