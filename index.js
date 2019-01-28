const logicsim = require('./build/Release/logicsim.node');

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

for (let i = 0; i < 1; i++) {
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

logicsim.init({
	"links" : 3,
    "threads": 1,
    "components": components
});
logicsim.start();

setInterval(() => {
	console.log(logicsim.getStatus());
	console.log(logicsim.getBoard());
}, 1000);