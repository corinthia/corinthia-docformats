/*
 * Copyright 2015 Ian Cunningham
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.Copyright [yyyy] [name of copyright owner]
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
'use strict';

/* Controllers */

var corControllers = angular.module('corControllers');



    corControllers.controller('corModeCtrl', ['$scope', '$routeParams', '$http', '$location',
        function($scope, $routeParams, $http, $location) {
            $http.get('docs.json').success(function(data) {
                 $scope.dirlist = data;
            });

            $scope.mode = $routeParams.mode;
            $scope.notReady = true;
            $scope.upload = function() {
                $fileUpload.upload($scope.files);
            };
            $scope.editMe = function(file) {
                //alert("Edit " + file);
                $http.defaults.headers.post['Content-Type'] = 'application/x-www-form-urlencoded;charset=utf-8';
                $http.post('edit/' + file).success(function(data) {
                    $scope.response = data;
                }).error(function(data) {
                    alert("post failed " + data);
                });
/*                var xhttp = new XMLHttpRequest();
                xhttp.onreadystatechange = function() {
                    if (xhttp.readyState == 4 && xhttp.status == 200) {
                        $location.path('app/output/'+file+'.html');  
                    }
                }
                xhttp.open("POST", "edit/", true);
                xhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
                xhttp.send("fname="+file);*/
            }
        }]);

