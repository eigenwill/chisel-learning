#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Vtop.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

int main(int argc, char** argv)
{

	VerilatedContext* contextp = new VerilatedContext;

	contextp->commandArgs(argc, argv);
	contextp->traceEverOn(true);

	Vtop* top = new Vtop{contextp};

	VerilatedVcdC* tfp = new VerilatedVcdC;
	top->trace(tfp,0);
	tfp->open("obj_dir/wave.vcd");

	while(!contextp->gotFinish()) {
		int a = rand() & 1;
		int b = rand() & 1;
		top->a = a;
		top->b = b;
		contextp->timeInc(1);
		top->eval();
		printf("a = %d, b = %d, f = %d\n", a, b, top->f);
		assert(top->f == (a ^ b));
		tfp->dump(contextp->time());
	}

	top->final();
	tfp->close();
	delete top;
	delete contextp;
	delete tfp;
	return 0;

}
