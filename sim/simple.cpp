#include <stdlib.h>
#include <string>
#include "driver.h"
#include "../build/Vsimple.h"

class SimpleDriver : public Driver {
	Vsimple *m_driver;

public:
	SimpleDriver()
		: Driver("simple")
	{
		this->m_driver = new Vsimple;
	}

	~SimpleDriver()
	{
		delete this->m_driver;
	}

	void before()
	{
		Verilated::traceEverOn(true);
		this->m_driver->trace(this->m_trace, 5);

		std::string file = this->m_name.append(".vcd");
		this->m_trace->open(file.c_str());
	}

	void eval(int a, int b, int c)
	{
		this->m_driver->a = a;
		this->m_driver->b = b;
		this->m_driver->c = c;
		this->m_driver->eval();

		this->tick();
	}

	void driver_run()
	{
		this->eval(0, 0, 0);
		this->eval(0, 0, 1);
		this->eval(0, 1, 0);
		this->eval(0, 1, 1);
		this->eval(1, 0, 0);
		this->eval(1, 0, 1);
		this->eval(1, 1, 0);
		this->eval(1, 1, 1);
	}
};

int main(int argc, char **argv, char **env)
{
	SimpleDriver driver;
	driver.run();

	exit(EXIT_SUCCESS);
}
