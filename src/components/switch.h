#pragma once
#include "user_input_component.h"
#include "output.h"
#include "input.h"
#include "link.h"
#include "board.h"

class SWITCH :
	public UserInputComponent
{
public:
	SWITCH(Board* board, Input** inputs, Output** outputs) : UserInputComponent(board, inputs, outputs, 0, 1) { }
	SWITCH(Board* board, Link** inputs, Link** outputs) : UserInputComponent(board, inputs, outputs, 0, 1) { }

	std::size_t getMinInputCount() { return 0; }
	std::size_t getMaxInputCount() { return 0; }
	std::size_t getMinOutputCount() { return 1; }
	std::size_t getMaxOutputCount() { return 1; }

	std::size_t getUserInputCount() { return 1; }

	void triggerUserInput(std::size_t i, InputEvent inputEvent) {
		if(inputEvent == InputEvent::Down)
			outputs[0]->setPowered(!outputs[0]->getPowered());
	}

	void compute() { }
};

