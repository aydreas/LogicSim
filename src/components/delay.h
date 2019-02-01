#pragma once
#include "component.h"
#include "output.h"
#include "input.h"
#include "link.h"

class DELAY :
	public Component
{
public:
	DELAY(Board* board, Input** inputs, Output** outputs) : Component(board, inputs, outputs) { }
	DELAY(Board* board, Link** inputs, Link** outputs) : Component(board, inputs, outputs, getInputCount(), getOutputCount()) { }

	int getInputCount() {
		return 1;
	}

	int getOutputCount() {
		return 1;
	}

	void compute() {
		outputs[0]->setPowered(inputs[0]->getPowered());
	}
};

