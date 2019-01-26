const logicsim = require('./build/Release/logicsim.node');
logicsim.init({
	"links" : 3,
	"threads": 1,
	"components" : [
		{
			"type" : "CLK",
			"CLK_Speed" : 1,
			"inputs" : [
				1
			],
			"outputs" : [
				0
			]
		},
		{
			"type" : "AND",
			"inputs" : [
				0, 1
			],
			"outputs" : [
				2
			]
		},
		{
			"type" : "AND",
			"inputs" : [
				0, 1
			],
			"outputs" : [
				2
			]
		}
	]
});
logicsim.start();

setInterval(() => {
	console.log(logicsim.getStatus());
	console.log(logicsim.getBoard());
}, 1000);