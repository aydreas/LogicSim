#include <algorithm>
#include "link.h"
#include "output.h"

Link::Link()
{
	this->inputCount = 0;
	this->outputCount = 0;
	this->inputs = nullptr;
	this->outputs = nullptr;
}

Link::Link(Input** inputs, Output** outputs, int outputCount, int inputCount)
{
	this->inputs = inputs;
	this->outputs = outputs;
	this->outputCount = outputCount;
	this->inputCount = inputCount;
}

Link::~Link()
{
}

bool Link::getPowered()
{
	return std::any_of(outputs, outputs + outputCount, [](Output* x) { return x->getPowered(); });
}
