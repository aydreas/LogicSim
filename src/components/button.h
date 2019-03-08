#pragma once
#include "user_input_component.h"
#include "output.h"
#include "input.h"
#include "link.h"
#include "events.h"
#include "board.h"

class BUTTON :
	public UserInputComponent
{
public:
	BUTTON(Board* board, Input** inputs, Output** outputs) : UserInputComponent(board, inputs, outputs, 0, 1) { }
	BUTTON(Board* board, Link** inputs, Link** outputs) : UserInputComponent(board, inputs, outputs, 0, 1) { }

	std::size_t getMinInputCount() { return 0; }
	std::size_t getMaxInputCount() { return 0; }
	std::size_t getMinOutputCount() { return 1; }
	std::size_t getMaxOutputCount() { return 1; }

	std::size_t getUserInputCount() { return 1; }

	void triggerUserInput(std::size_t i, InputEvent inputEvent) {
		if (inputEvent != InputEvent::Down)
			return;

		outputs[0]->setPowered(true);
		if (!subscribed) {
			subscribed = true;
			board->tickEvent += tickEvent;
		}
	}

	void compute() { }
private:
	bool subscribed = false;
	Events::EventHandler<>* tickEvent = new Events::EventHandler<>([this](Events::Emitter* e, Events::EventArgs& a) {
		outputs[0]->setPowered(false);
		board->tickEvent -= tickEvent;
		subscribed = false;
	});
};

