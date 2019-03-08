#pragma once
#include <cstddef>

class Input;
class Output;
class Board;

class Link
{
public:
	Link(Board* board);
	Link(Board* board, Input** inputs, Output** outputs, std::size_t inputCount, std::size_t outputCount);
	~Link();
	bool powered;
	Input** inputs;
	Output** outputs;
	Board* board;
	std::size_t inputCount;
	std::size_t outputCount;
};

