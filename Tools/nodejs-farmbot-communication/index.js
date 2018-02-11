const SerialPort = require('serialport');
const testcode = require('./testcode');
const readline = require('readline');
const Console = require('Console');

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

const port = new SerialPort('/dev/ACM0', {
    baudRate: 115200
});

rl.on('line', (input) => {
    if (input === 'testcode') {
        sendCommand(testcode.movex);
    }
    else if (input[0] === 'F' || input[0] === 'G' || input[0] === 'e') {
        sendCommand('\n' + input);
    }
    else Console.error('"' + input + '"' + 'is not a valid command!')
});

function sendCommand(command) {
    port.write(command, function (err) {
        console.stress(command + ' will be send')
        if (err) {
            return console.error('Error on write: ', err.message);
        }
        else console.success('message written');
    });
};

port.on('error', function (err) {
    console.error('Error: ', err.message);
});
port.on("data", (data) => {
    console.debug(data.toString());
});
