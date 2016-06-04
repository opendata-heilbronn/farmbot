var app = require ('express')();
var http = require('http').Server(app);
var io = require('socket.io')(http);

//running index.html as simple web client here ==> see on ip:3000
app.get('/', function(req, res){
  res.sendFile(__dirname + '/public/index.html');
});
// app.use('/', app.static(__dirname + '/public'));
// app.use('/', express.static(__dirname + '/public'));
// app.use("/public", express.static(path.join(__dirname, 'public')));
http.listen(3000, function(){
  console.log('listening on *:3000');
});

//get called if somebody connects via socket.io to our ip
io.on('connection', function(socket){
  socket.on('movetoxy', function(xcord_in_hundredthsofamillimeter, ycord_in_hundredthsofamillimeter){
                console.log("Moving to: ("+ xcord_in_hundredthsofamillimeter +"|"+ ycord_in_hundredthsofamillimeter +")");

  })
  console.log('A new connection is now open');
  socket.on('disconnect', function () {
    console.log('A connection was closed');
  });
});

