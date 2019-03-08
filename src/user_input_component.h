#pragma once
#include "component.h"

class UserInputComponent :
	public Component
{
public:
	enum InputEvent { Down, Up };
	virtual void triggerUserInput(std::size_t index, InputEvent inputEvent) = 0;
	virtual std::size_t getUserInputCount() = 0;
protected:
	UserInputComponent(Board* board, Link** inputs, Link** outputs, std::size_t inputCount, std::size_t outputCount) : Component(board, inputs, outputs, inputCount, outputCount) { }
	UserInputComponent(Board* board, Input** inputs, Output** outputs, std::size_t inputCount, std::size_t outputCount) : Component(board, inputs, outputs, inputCount, outputCount) { }
};
