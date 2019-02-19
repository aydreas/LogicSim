#pragma once
#include "component.h"
#include "output.h"
#include "input.h"
#include "link.h"

class OR :
	public Component
{
public:
	OR(Board* board, Input** inputs, Output** outputs) : Component(board, inputs, outputs, getInputCount(), getOutputCount()) { }
	OR(Board* board, Link** inputs, Link** outputs) : Component(board, inputs, outputs, getInputCount(), getOutputCount()) { }

	int getInputCount() {
		return 2;
	}

	int getOutputCount() {
		return 1;
	}

	void compute() {
		outputs[0]->setPowered(inputs[0]->getPowered() || inputs[1]->getPowered());
	}
};

