#include "InputGamepad.h"

InputGamepad::InputGamepad()
{
	lx = 0;
	ly = 0;
	rx = 0;
	ry = 0;
	padding = 0.2f;
}

InputGamepad::~InputGamepad()
{
}

float InputGamepad::NormalizeAxis(int value)
{
	if (value > 0)
	{
		return value / 32767.f;
	}
	else
	{
		return value / 32768.f;
	}
}

void InputGamepad::ResetAxis()
{
	lx = 0;
	ly = 0;
	rx = 0;
	ry = 0;
}

void InputGamepad::StopAxis()
{
	if (lx < padding && lx >(padding * -1))
	{
		lx = 0;
	}
	if (ly < padding && ly >(padding * -1))
	{
		ly = 0;
	}
	if (rx < padding && rx >(padding * -1))
	{
		rx = 0;
	}
	if (ry < padding && ry >(padding * -1))
	{
		ry = 0;
	}
}
