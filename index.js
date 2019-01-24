const logicsim = require('./build/Release/logicsim.node');
logicsim.init();
logicsim.start();

setInterval(() => console.log(logicsim.getStatus()), 1000);