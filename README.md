# LogicSim
Multi-Threaded Simulator for Logic Circuits as Node.JS Native C++ Module.
## Getting Started
### Prerequisites
You need to have node and npm installed to use this module.
#### Debian
```
apt install npm
```
### Installation
Download the contents of the repository, open the command line in that directory and install it using ```npm install```.
#### Linux / Unix
```
git clone 'https://github.com/yEinFallsLos/LogicSim.git' && cd ./LogicSim && npm install
```
alternatively, you can install it using npm:
```
npm install logicsim -g
```
## Usage
Import the module in your Node.JS Script: ```const logicsim = require('./index');``` (if you installed it using npm, use ```const logicsim = require('logicsim');```)
### Functions
| Function  | Decription |
| --- | --- |
| ```logicsim.newBoard("*unique identifier for your board*", *object with the contents of the board, see below for an example*);```  | Creates a new Board |
| ```logicsim.startBoard("*identifier*" [, *amount of ticks the simulation will run, leave out for endless simulation*]);``` | Start your Board |
| ```logicsim.stopBoard("*identifier*");``` | Stop your Board, if simulation is running |
| ```logicsim.getBoardStatus("*identifier*");``` | Get the current Status of the Board, like passed ticks, current execution state or current simulation speed |
| ```logicsim.getBoard("*identifier*");``` | Get the components and their current state of the board |
| ```logicsim.triggerInput("*identifier*", *index of component to trigger*, *index of input on component*, *input event (0 = down, 1 = up)*)``` | Trigger an input element on the board |
### Sample Board Object:
```
{
  "links": 4,
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
  		"type": "XOR",
  		"inputs": [
  			0, 1
  		],
  		"outputs": [
  			2
  		]
  	},
  	{
  		"type": "AND",
  		"inputs": [
  			0, 2
  		],
  		"outputs": [
  			3
  		]
  	}
  ]
}
```

## License
This Project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
