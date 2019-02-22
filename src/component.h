#pragma once

class Input;
class Output;
class Link;
class Board;

class Component
{
public:
	~Component();
	virtual unsigned int getMinInputCount() = 0;
	virtual unsigned int getMaxInputCount() = 0;
	virtual unsigned int getMinOutputCount() = 0;
	virtual unsigned int getMaxOutputCount() = 0;
	virtual void compute() = 0;
	unsigned int componentIndex;
	Input** inputs;
	Output** outputs;
protected:
	Board* board;
	Component(Board* board, Link** inputs, Link** outputs, int inputCount, int outputCount);
	Component(Board* board, Input** inputs, Output** outputs, int inputCount, int outputCount);
	unsigned int inputCount;
	unsigned int outputCount;
};
