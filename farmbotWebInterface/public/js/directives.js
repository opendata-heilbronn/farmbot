 angular.module('myApp')
 .directive('makeResponsive', function() {
     return{
         restrict: 'A',
         link: function($scope, element){
             window.addEventListener("resize", function(){
                //element 0 because element is a jqlite object and with [0] you get the native dom element 
                var position = element[0].getBoundingClientRect();
                $scope.zeropointpixel_x = position.left;
                $scope.zeropointpixel_y = position.top;
                $scope.divwidth = (position.right -position.left);
                $scope.divheight = (position.bottom - position.top);
                $scope.$apply();
             });
            
         }
     }
            
});