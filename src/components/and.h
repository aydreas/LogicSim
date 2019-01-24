#pragma once
#include "component.h"
#include "output.h"
#include "input.h"
#include "link.h"

class AND :
	public Component
{
public:
	AND(Input** inputs, Output** outputs) : Component(inputs, outputs) { }
	AND(Link** inputs, Link** outputs) : Component(inputs, outputs, getInputCount(), getOutputCount()) { }

	int getInputCount()
	{
		return 2;
	}

	int getOutputCount()
	{
		return 1;
	}

	void compute() {
		outputs[0]->setPowered(inputs[0]->getPowered() && inputs[1]->getPowered());
	}
};

