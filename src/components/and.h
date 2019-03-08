#pragma once
#include "component.h"
#include "output.h"
#include "input.h"
#include "link.h"

class AND :
	public Component
{
public:
	AND(Board* board, Input** inputs, Output** outputs, std::size_t inputCount) : Component(board, inputs, outputs, inputCount, 1) { }
	AND(Board* board, Link** inputs, Link** outputs, std::size_t inputCount) : Component(board, inputs, outputs, inputCount, 1) { }

	std::size_t getMinInputCount() { return 1; }
	std::size_t getMaxInputCount() { return SIZE_MAX; }
	std::size_t getMinOutputCount() { return 1; }
	std::size_t getMaxOutputCount() { return 1; }

	void compute() {
		for (std::size_t i = 0; i < inputCount; i++) {
			if (!inputs[i]->getPowered()) {
				outputs[0]->setPowered(false);
				return;
			}
			outputs[0]->setPowered(true);
		}
	}
};

