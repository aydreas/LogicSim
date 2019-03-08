#pragma once
#include <cstddef>

class Input;
class Output;
class Link;
class Board;

class Component
{
public:
	~Component();
	virtual std::size_t getMinInputCount() = 0;
	virtual std::size_t getMaxInputCount() = 0;
	virtual std::size_t getMinOutputCount() = 0;
	virtual std::size_t getMaxOutputCount() = 0;
	std::size_t getOutputCount();
	std::size_t getInputCount();
	virtual void compute() = 0;
	std::size_t componentIndex;
	Input** inputs;
	Output** outputs;
protected:
	Board* board;
	Component(Board* board, Link** inputs, Link** outputs, std::size_t inputCount, std::size_t outputCount);
	Component(Board* board, Input** inputs, Output** outputs, std::size_t inputCount, std::size_t outputCount);
	std::size_t inputCount;
	std::size_t outputCount;
};
