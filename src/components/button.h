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
	BUTTON(Board* board, Input** inputs, Output** outputs) : UserInputComponent(board, inputs, outputs, getInputCount(), getOutputCount()) { }
	BUTTON(Board* board, Link** inputs, Link** outputs) : UserInputComponent(board, inputs, outputs, getInputCount(), getOutputCount()) { }

	int getInputCount() {
		return 0;
	}

	int getOutputCount() {
		return 1;
	}

	int getUserInputCount() {
		return 1;
	}

	void triggerUserInput(int i, InputEvent inputEvent) {
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

