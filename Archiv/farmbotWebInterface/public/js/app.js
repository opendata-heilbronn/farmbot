 angular.module('myApp', []).controller('myCtrl', function($scope) {
      var socket = io.connect('http://localhost:3000');
      $scope.fieldWidth=1100;
      $scope.fieldHeight=650;
      $scope.doClick = function(event){
            $scope.offsetX = event.offsetX;
            $scope.offsetY = event.offsetY;
            var xcord_in_hundredthsofamillimeter = (event.offsetX*($scope.fieldWidth/$scope.divwidth));
            var ycord_in_hundredthsofamillimeter = (event.offsetY*($scope.fieldHeight/$scope.divheight));
            console.log("("+ xcord_in_hundredthsofamillimeter +"|"+ ycord_in_hundredthsofamillimeter +")");
            socket.emit('movetoxy', xcord_in_hundredthsofamillimeter, ycord_in_hundredthsofamillimeter);
            
        };
        //masureing width and hieght of the div (vitual field)
        var element = document.getElementById('coordinateSystem');
        var position = element.getBoundingClientRect();
            $scope.zeropointpixel_x = position.left;
            $scope.zeropointpixel_y = position.top;
            $scope.divwidth = (position.right -position.left);
            $scope.divheight = (position.bottom - position.top);
        console.log(position.bottom);
        console.log(position.top);
        console.log($scope.divheight);
    });