#pragma once
#include "component.h"
#include "output.h"
#include "input.h"
#include "link.h"

class DELAY :
	public Component
{
public:
	DELAY(Board* board, Input** inputs, Output** outputs) : Component(board, inputs, outputs, 1, 1) { }
	DELAY(Board* board, Link** inputs, Link** outputs) : Component(board, inputs, outputs, 1, 1) { }

	std::size_t getMinInputCount() { return 1; }
	std::size_t getMaxInputCount() { return 1; }
	std::size_t getMinOutputCount() { return 1; }
	std::size_t getMaxOutputCount() { return 1; }

	void compute() {
		outputs[0]->setPowered(inputs[0]->getPowered());
	}
};

