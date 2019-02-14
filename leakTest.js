const fs = require('fs');
const logicsim = require('./build/Debug/logicsim.node');

for (let i = 0; i < 100000; i++) {
    logicsim.newBoard("board_" + i, {
        "links": 8,
        "threads": 1,
        "components": [
            {
                "type": "SWITCH",
                "inputs": [
                ],
                "outputs": [
                    0
                ]
            },
            {
                "type": "SWITCH",
                "inputs": [
                ],
                "outputs": [
                    1
                ]
            },
            {
                "type": "SWITCH",
                "inputs": [
                ],
                "outputs": [
                    2
                ]
            },
            {
                "type": "XOR",
                "inputs": [
                    1, 2
                ],
                "outputs": [
                    3
                ]
            },
            {
                "type": "AND",
                "inputs": [
                    1, 2
                ],
                "outputs": [
                    4
                ]
            },
            {
                "type": "XOR",
                "inputs": [
                    0, 3
                ],
                "outputs": [
                    5
                ]
            },
            {
                "type": "AND",
                "inputs": [
                    0, 3
                ],
                "outputs": [
                    6
                ]
            },
            {
                "type": "OR",
                "inputs": [
                    4, 6
                ],
                "outputs": [
                    7
                ]
            }
        ]
    });
    logicsim.removeBoard("board_" + i);
}

console.log("ready.");
wait(100000);
async function wait(ms) {
    await new Promise(resolve => setTimeout(resolve, ms));
}