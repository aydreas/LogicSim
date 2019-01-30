const logicsim = require('./index');

var components = [];

components.push({
    "type": "CLK",
    "CLK_Speed": 1,
    "inputs": [
        1
    ],
    "outputs": [
        0
    ]
});

for (let i = 0; i < 100000; i++) {
    components.push({
        "type": "AND",
        "inputs": [
            0, 1
        ],
        "outputs": [
            2
        ]
    });
}

logicsim.newBoard("testBoard", {
    "links": 3,
    "threads": 1,
    "components": components
});
logicsim.startBoard("testBoard");

setInterval(() => {
    console.log(logicsim.getBoardStatus("testBoard"));
}, 1000);