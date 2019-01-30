#include "link.h"
#include "output.h"

Link::Link(Board* board) :
	board(board),
	inputCount(0),
	outputCount(0),
	inputs(nullptr),
	outputs(nullptr),
	powered(0)
{
}

Link::Link(Board* board, Input** inputs, Output** outputs, int inputCount, int outputCount) :
	board(board),
	inputs(inputs),
	outputs(outputs),
	inputCount(inputCount),
	outputCount(outputCount),
	powered(0)
{
}

Link::~Link()
{
}
