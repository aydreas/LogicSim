#pragma once

class Input;
class Output;
class Link;
class Board;

class Component
{
public:
	~Component();
	virtual int getInputCount() = 0;
	virtual int getOutputCount() = 0;
	virtual void compute() = 0;
	int componentIndex;
	Input** inputs;
	Output** outputs;
protected:
	Board* board;
	Component(Board* board, Link** inputs, Link** outputs, int inputCount, int outputCount);
	Component(Board* board, Input** inputs, Output** outputs, int inputCount, int outputCount);
private:
	int inputCount;
	int outputCount;
};
