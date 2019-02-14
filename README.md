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
## Usage
Import the module in your Node.JS Script: ```const logicsim = require('./index');```
### Functions
Create a new Board:
```logicsim.newBoard("*unique identifier for your board*", *object with the contents of the board, see below for an example*);```

Start your Board:
```logicsim.startBoard("*identifier*" [, *amount of ticks the simulation will run, leave out for endless simulation*]);```

Stop your Board, if simulation is running:
```logicsim.stopBoard("*identifier*");```

Get the current Status of the Board, like passed ticks, current execution state or current simulation speed:
```logicsim.getBoardStatus("*identifier*");```

Get the components and their current state of the board:
```logicsim.getBoard("*identifier*");```

Trigger an input element on the board:
```logicsim.triggerInput("*identifier*", *index of component to trigger*, *index of input on component*, *input event (0 = down, 1 = up)*)```

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
