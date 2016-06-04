var express = require('express');
var app = express();
var http = require('http').Server(app);
var io = require('socket.io')(http);
var serialport = require("serialport");
var SerialPort = serialport.SerialPort;

var serialPort = new SerialPort("/dev/ttyAMA0", {
  baudrate: 15200,
  parser: serialport.parsers.readline("\n")
});

serialPort.on("open", function () {
  console.log('serialportopen');
  serialPort.on('data', function(data) {
    console.log(data);
  });
});


  app.use('/', express.static(__dirname + '/public'));
  app.use('/node_modules', express.static(__dirname + '/node_modules'));
  // app.use('/', app.static(__dirname + '/public'));
  // app.use('/', express.static(__dirname + '/public'));
  // app.use("/public", express.static(path.join(__dirname, 'public')));
  http.listen(3000, function () {
    console.log('listening on *:3000');
  });



  //get called if somebody connects via socket.io to our ip
  io.on('connection', function (socket) {
    socket.on('movetoxy', function (xcord_in_hundredthsofamillimeter, ycord_in_hundredthsofamillimeter) {
      console.log("Moving to: (" + xcord_in_hundredthsofamillimeter + "|" + ycord_in_hundredthsofamillimeter + ")");
      port.write('G00 X'+xcord_in_hundredthsofamillimeter+' Y'+ycord_in_hundredthsofamillimeter);
    })
    console.log('A new socket connection is now open');
    socket.on('disconnect', function () {
      console.log('A socket connection was closed');
    });
  });

