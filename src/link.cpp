#include "link.h"
#include "output.h"
#include "input.h"

Link::Link(Board* board) :
	board(board),
	inputCount(0),
	outputCount(0),
	inputs(nullptr),
	outputs(nullptr),
	powered(false)
{
}

Link::Link(Board* board, Input** inputs, Output** outputs, std::size_t inputCount, std::size_t outputCount) :
	board(board),
	inputs(inputs),
	outputs(outputs),
	inputCount(inputCount),
	outputCount(outputCount),
	powered(false)
{
}

Link::~Link() {
	delete[] inputs;
	delete[] outputs;
}
