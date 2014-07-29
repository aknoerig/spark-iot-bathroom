angular.module('starter.controllers', [])

.controller('DashCtrl', function($scope, $rootScope, $http) {

	angular.element(document).ready(function () {

        var requestURL = $rootScope.sparkURL + $rootScope.deviceID +  "/locked";
        $http.get(requestURL, { headers: {'Authorization': 'Bearer '+$rootScope.accessToken} }).
	        success(function(data, status) {
	          	$scope.onStatusChange(data.result);
	        });


        var source = new EventSource($rootScope.sparkURL + $rootScope.deviceID + "/events/lock?access_token=" + $rootScope.accessToken);
        source.addEventListener('lock', function (e) {
        	$scope.$apply(function() {
	            var result = JSON.parse(e.data).data;
	          	$scope.onStatusChange(result);
        	});
        }, false);

    });

	$scope.onButtonClick = function() {
		var requestURL = $rootScope.sparkURL + $rootScope.deviceID + "/knock";
        $http.post( requestURL, null, { headers: {'Authorization': 'Bearer '+$rootScope.accessToken} });
	}

	$scope.onStatusChange = function(status) {
		if (status == 0) {
			$scope.statusMsg = "Free";
			$scope.lockStatus = false;
			navigator.notification.vibrate(1000);
		} else {
			$scope.statusMsg = "Occupied";
			$scope.lockStatus = true;
		}
	}


})


.controller('ConfigCtrl', function($scope) {
  
})

