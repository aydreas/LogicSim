#pragma once

class Input;
class Output;

class Link
{
public:
	Link();
	Link(Input** inputs, Output** outputs, int inputCount, int outputCount);
	~Link();
	bool getPowered();
	Input** inputs;
	Output** outputs;
	int inputCount;
	int outputCount;
};

