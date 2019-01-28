#include <algorithm>
#include "link.h"
#include "output.h"

Link::Link(Board* board) :
	board(board),
	inputCount(0),
	outputCount(0),
	inputs(nullptr),
	outputs(nullptr)
{
}

Link::Link(Board* board, Input** inputs, Output** outputs, int inputCount, int outputCount) :
	board(board),
	inputs(inputs),
	outputs(outputs),
	inputCount(inputCount),
	outputCount(outputCount)
{
}

Link::~Link()
{
}

bool Link::getPowered()
{
	return std::any_of(outputs, outputs + outputCount, [](Output* x) { return x->getPowered(); });
}
