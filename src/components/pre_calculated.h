#pragma once
#include "component.h"
#include "output.h"
#include "input.h"
#include "link.h"

class pre_calculated :
	public Component
{
public:
	pre_calculated(Board* board, Input** inputs, Output** outputs, std:size_t inputCount, std:size_t outputCount) : Component(board, inputs, outputs, inputCount, outputCount) { }
	pre_calculated(Board* board, Link** inputs, Link** outputs, std:size_t inputCount, std:size_t outputCount) : Component(board, inputs, outputs, inputCount, outputCount) { }

	std::size_t getMinInputCount() { return 1; }
	std::size_t getMaxInputCount() { return SIZE_MAX; }
	std::size_t getMinOutputCount() { return 1; }
	std::size_t getMaxOutputCount() { return SIZE_MAX; }

	void compute() {
		for (int i = 0; i < inputCount; i++) {
			if (!inputs[i]->getPowered()) {
				outputs[0]->setPowered(false);
				return;
			}
			outputs[0]->setPowered(true);
		}
	}
};

