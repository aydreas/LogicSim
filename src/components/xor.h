#pragma once
#include "component.h"
#include "output.h"
#include "input.h"
#include "link.h"

class XOR :
	public Component
{
public:
	XOR(Board* board, Input** inputs, Output** outputs, std::size_t inputCount) : Component(board, inputs, outputs, inputCount, 1) { }
	XOR(Board* board, Link** inputs, Link** outputs, std::size_t inputCount) : Component(board, inputs, outputs, inputCount, 1) { }

	std::size_t getMinInputCount() { return 1; }
	std::size_t getMaxInputCount() { return SIZE_MAX; }
	std::size_t getMinOutputCount() { return 1; }
	std::size_t getMaxOutputCount() { return 1; }

	void compute() {
		unsigned int c = 0;
		for (std::size_t i = 0; i < inputCount; i++) {
			if (inputs[i]->getPowered())
				c++;
		}
		outputs[0]->setPowered(c % 2);
	}
};

