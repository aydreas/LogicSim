const fs = require('fs');
const logicsim = require('./index');

var args = process.argv;
run();

async function run() {
    for (let fileIndex = 2; fileIndex < args.length; fileIndex++) {
        let config = JSON.parse(fs.readFileSync("./tests/" + args[2]));
        logicsim.newBoard("testBoard_" + fileIndex, config.board);
        logicsim.startBoard("testBoard_" + fileIndex);

        for (let i = 0; i < config.inputTriggers.length; i++) {
            logicsim.triggerInput("testBoard_" + fileIndex, config.inputTriggers[i], 0, 0);
        }

        await new Promise(resolve => setTimeout(resolve, config.simulationTime));
        logicsim.stopBoard("testBoard_" + fileIndex);
        let boardState = logicsim.getBoard("testBoard_" + fileIndex);
		console.log(boardState);
        for (let i = 0; i < config.expected.components.length; i++) {
            for (let j = 0; j < config.expected.components[i].length; j++) {
                if (boardState.components[i][j] !== config.expected.components[i][j])
                    console.error("Component[" + i + "][" + j + "] failed (expected: " + config.expected.components[i] + ", actual: " + boardState.components[i] + ")");
            }
        }

        for (let i = 0; i < config.expected.links.length; i++) {
            if (boardState.links[i] !== config.expected.links[i])
                console.error("Link[" + i + "] failed (expected: " + config.expected.links[i] + ", actual: " + boardState.links[i] + ")");
        }
    }
}
