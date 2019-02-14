#include "component.h"
#include "input.h"
#include "output.h"
#include "link.h"
#include "board.h"
#include <memory>

Component::Component(Board* board, Input** inputs, Output** outputs) :
	board(board),
	inputs(inputs),
	outputs(outputs)
{
	componentIndex = board->getNextComponentIndex();
}

Component::Component(Board* board, Link** inputs, Link** outputs, int inputCount, int outputCount) :
	board(board)
{
	this->inputs = new Input*[inputCount];
	for (int i = 0; i < inputCount; i++) {
		this->inputs[i] = new Input(this, inputs[i]);
	}

	this->outputs = new Output*[outputCount];
	for (int i = 0; i < outputCount; i++) {
		this->outputs[i] = new Output(this, outputs[i]);
	}

	for (int i = 0; i < inputCount; i++) {
		Input** newInputs = new Input*[inputs[i]->inputCount + 1];
		memcpy(newInputs, inputs[i]->inputs, inputs[i]->inputCount * sizeof(Input*));
		newInputs[inputs[i]->inputCount] = this->inputs[i];
		delete[] inputs[i]->inputs;
		inputs[i]->inputs = newInputs;
		inputs[i]->inputCount++;
	}

	for (int i = 0; i < outputCount; i++) {
		Output** newOutputs = new Output*[outputs[i]->outputCount + 1];
		memcpy(newOutputs, outputs[i]->outputs, outputs[i]->outputCount * sizeof(Output*));
		newOutputs[outputs[i]->outputCount] = this->outputs[i];
		delete[] outputs[i]->outputs;
		outputs[i]->outputs = newOutputs;
		outputs[i]->outputCount++;
	}

	componentIndex = board->getNextComponentIndex();
}

Component::~Component()
{
}
