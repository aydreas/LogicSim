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
	int speed = 1;

	CLK(Input** inputs, Output** outputs) : Component(inputs, outputs)
	{
		outputChange();
	}

	CLK(Input** inputs, Output** outputs, int speed) : Component(inputs, outputs)
	{
		this->speed = speed;
		outputChange();
	}

	CLK(Link** inputs, Link** outputs) : Component(inputs, outputs, getInputCount(), getOutputCount())
	{
		outputChange();
	}

	CLK(Link** inputs, Link** outputs, int speed) : Component(inputs, outputs, getInputCount(), getOutputCount())
	{
		this->speed = speed;
		outputChange();
	}

	int getInputCount()
	{
		return 1;
	}

	int getOutputCount()
	{
		return 1;
	}

	void compute() {
		outputChange();
	}
private:
	bool subscribed = false;
	int tickCount = 0;
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
				Board::tickEvent -= tickEvent;
				subscribed = false;
			}
		}
		else {
			if (!subscribed) {
				Board::tickEvent += tickEvent;
				subscribed = true;
			}
		}
	}
};