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
Import the module in your Node.JS Script: ```const logicsim = require('./index').logicsim;``` (if you installed it using npm, use ```const logicsim = require('logicsim').logicsim;```)

If you are using TypeScript, import the module with: ```import {BoardObject, logicsim} from "logicsim";```
### Functions
| Function  | Decription |
| --- | --- |
| ```logicsim.newBoard("*unique identifier for your board*", *object with the contents of the board, see below for an example*);```  | Creates a new Board |
| ```logicsim.startBoard("*identifier*" [, *amount of ticks the simulation will run, leave out for endless simulation*]);``` | Starts a Board |
| ```logicsim.stopBoard("*identifier*");``` | Stops a Board, if simulation is running |
| ```logicsim.getBoardStatus("*identifier*");``` | Gets the current Status of a Board, like passed ticks, current execution state or current simulation speed |
| ```logicsim.getBoard("*identifier*");``` | Gets the components and their current state of a board |
| ```logicsim.triggerInput("*identifier*", *index of component to trigger*, *index of input on component*, *input event (0 = down, 1 = up)*)``` | Triggers an input element on a board |
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
