#pragma once
#include "component.h"
#include "output.h"
#include "input.h"
#include "board.h"
#include "events.h"
#include "link.h"

class CLK : 
	public Component
{
public:
	unsigned long speed = 1;

	CLK(Board* board, Input** inputs, Output** outputs) : Component(board, inputs, outputs, 1, 1) {
		outputChange();
	}

	CLK(Board* board, Input** inputs, Output** outputs, unsigned long speed) : Component(board, inputs, outputs, 1, 1) {
		this->speed = speed;
		outputChange();
	}

	CLK(Board* board, Link** inputs, Link** outputs) : Component(board, inputs, outputs, 1, 1) {
		outputChange();
	}

	CLK(Board* board, Link** inputs, Link** outputs, unsigned long speed) : Component(board, inputs, outputs, 1, 1) {
		this->speed = speed;
		outputChange();
	}

	std::size_t getMinInputCount() { return 1; }
	std::size_t getMaxInputCount() { return 1; }
	std::size_t getMinOutputCount() { return 1; }
	std::size_t getMaxOutputCount() { return 1; }

	void compute() {
		outputChange();
	}
private:
	bool subscribed = false;
	unsigned long tickCount = 0;
	Events::EventHandler<>* tickEvent = new Events::EventHandler<>([this](Events::Emitter* e, Events::EventArgs& a) {
		tickCount++;

		if (tickCount >= speed) {
			if (outputs[0]->getPowered())
				outputs[0]->setPowered(false);
			else
				outputs[0]->setPowered(true);

			tickCount = 0;
		}
	});
	
	void outputChange() {
		if (inputs[0]->getPowered()) {
			if (subscribed) {
				board->tickEvent -= tickEvent;
				subscribed = false;
			}
		}
		else {
			if (!subscribed) {
				board->tickEvent += tickEvent;
				subscribed = true;
			}
		}
	}
};