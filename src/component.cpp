#include "component.h"
#include "input.h"
#include "output.h"
#include "link.h"
#include "board.h"
#include <memory>
#include <cstring>

Component::Component(Board* board, Input** inputs, Output** outputs, std::size_t inputCount, std::size_t outputCount) :
	board(board),
	inputs(inputs),
	outputs(outputs),
	inputCount(inputCount),
	outputCount(outputCount)
{
	componentIndex = board->getNextComponentIndex();
}

Component::Component(Board* board, Link** inputs, Link** outputs, std::size_t inputCount, std::size_t outputCount) :
	board(board),
	inputCount(inputCount),
	outputCount(outputCount)
{
	this->inputs = new Input*[inputCount];
	for (std::size_t i = 0; i < inputCount; i++) {
		this->inputs[i] = new Input(this, inputs[i]);
	}

	this->outputs = new Output*[outputCount];
	for (std::size_t i = 0; i < outputCount; i++) {
		this->outputs[i] = new Output(this, outputs[i]);
	}

	for (std::size_t i = 0; i < inputCount; i++) {
		Input** newInputs = new Input*[inputs[i]->inputCount + 1];
		std::memcpy(newInputs, inputs[i]->inputs, inputs[i]->inputCount * sizeof(Input*));
		newInputs[inputs[i]->inputCount] = this->inputs[i];
		delete[] inputs[i]->inputs;
		inputs[i]->inputs = newInputs;
		inputs[i]->inputCount++;
	}

	for (std::size_t i = 0; i < outputCount; i++) {
		Output** newOutputs = new Output*[outputs[i]->outputCount + 1];
		std::memcpy(newOutputs, outputs[i]->outputs, outputs[i]->outputCount * sizeof(Output*));
		newOutputs[outputs[i]->outputCount] = this->outputs[i];
		delete[] outputs[i]->outputs;
		outputs[i]->outputs = newOutputs;
		outputs[i]->outputCount++;
	}

	componentIndex = board->getNextComponentIndex();
}

std::size_t Component::getOutputCount()
{
	return outputCount;
}

std::size_t Component::getInputCount() {
	return inputCount;
}

Component::~Component() {
	for (std::size_t i = 0; i < inputCount; i++) {
		delete inputs[i];
	}
	for (std::size_t i = 0; i < outputCount; i++) {
		delete outputs[i];
	}
	delete[] inputs;
	delete[] outputs;
}
