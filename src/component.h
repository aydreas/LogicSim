#pragma once

class Input;
class Output;
class Link;

class Component
{
public:
	~Component();
	static int getNextComponentIndex();
	virtual int getInputCount() = 0;
	virtual int getOutputCount() = 0;
	virtual void compute() = 0;
	int componentIndex;
	Input** inputs;
	Output** outputs;
protected:
	Component(Link** inputs, Link** outputs, int inputCount, int outputCount);
	Component(Input** inputs, Output** outputs);
private:
	static int componentCounter;
};
