const fs = require('fs');
const logicsim = require('./index');

var args = process.argv;

for (let fileIndex = 2; fileIndex < args.length; fileIndex++) {
	process.stdout.write("Running test '" + args[fileIndex] + "'.. ");
	let config = JSON.parse(fs.readFileSync(args[fileIndex]));
	
	logicsim.newBoard("testBoard_" + fileIndex, config.board);
	for (let i = 0; i < config.inputTriggers.length; i++) {
		logicsim.triggerInput('testBoard_' + fileIndex, config.inputTriggers[i], 0, 0);
	}
	
	logicsim.startBoard('testBoard_' + fileIndex, config.ticks);
	
	while (logicsim.getBoardStatus('testBoard_' + fileIndex).currentState != 1) {}
	let boardState = logicsim.getBoard('testBoard_' + fileIndex);
	
	let errorOccurred = false;
	for (let i = 0; i < config.expected.components.length; i++) {
		for (let j = 0; j < config.expected.components[i].length; j++) {
			if (boardState.components[i][j] !== config.expected.components[i][j]) {
				if (!errorOccurred)
					console.log('\x1b[31m%s\x1b[0m', "failed!");
				console.error('\x1b[31m%s\x1b[0m', 'Component[' + i + '][' + j + '] failed (expected: ' + config.expected.components[i] + ', actual: ' + boardState.components[i] + ')');
				errorOccurred = true;
			}
		}
	}
	
	for (let i = 0; i < config.expected.links.length; i++) {
		if (boardState.links[i] !== config.expected.links[i]) {
			if (!errorOccurred)
				console.log('\x1b[31m%s\x1b[0m', "failed!");
			console.error('\x1b[31m%s\x1b[0m', 'Link[' + i + '] failed (expected: ' + config.expected.links[i] + ', actual: ' + boardState.links[i] + ')');
			errorOccurred = true;
		}
	}
	
	if(!errorOccurred)
		console.log('\x1b[32m%s\x1b[0m', 'passed!');
}
