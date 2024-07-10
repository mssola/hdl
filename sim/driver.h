#pragma once

#if __has_include("verilator/verilated.h")
#include <verilator/verilated.h>
#include <verilator/verilated_vcd_c.h>
#else
#include <verilated.h>
#include <verilated_vcd_c.h>
#endif

class Driver {
public:
	vluint64_t m_time;
	std::string m_name;
	VerilatedVcdC *m_trace;

public:
	Driver(std::string name)
	{
		this->m_name = name;
		this->m_time = 0;
		this->m_trace = new VerilatedVcdC;
	}

	~Driver()
	{
		delete this->m_trace;
	}

	void tick()
	{
		this->m_trace->dump(this->m_time);
		this->m_time++;
	}

	virtual void before()
	{
	}

	virtual void after()
	{
		this->m_trace->close();
	}

	virtual void driver_run() = 0;

	void run()
	{
		this->before();
		this->driver_run();
		this->after();
	}
};
