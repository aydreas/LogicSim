#pragma once
#include "component.h"

class UserInputComponent :
	public Component
{
public:
	enum InputEvent { Down, Up };
	virtual void triggerUserInput(int index, InputEvent inputEvent) = 0;
	virtual int getUserInputCount() = 0;
protected:
	UserInputComponent(Board* board, Link** inputs, Link** outputs, int inputCount, int outputCount) : Component(board, inputs, outputs, inputCount, outputCount) { }
	UserInputComponent(Board* board, Input** inputs, Output** outputs, int inputCount, int outputCount) : Component(board, inputs, outputs, inputCount, outputCount) { }
};
