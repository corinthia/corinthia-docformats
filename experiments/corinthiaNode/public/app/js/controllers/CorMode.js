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



    corControllers.controller('corModeCtrl', ['$scope', '$routeParams', '$http', '$window',
        function($scope, $routeParams, $http, $window) {
            $http.get('docs.json').success(function(data) {
                 $scope.dirlist = data;
            });

            $scope.mode = $routeParams.mode;
            $scope.notReady = true;
            $scope.upload = function() {
                $fileUpload.upload($scope.files);
            };
            $scope.edit = function(file) {
                $http({
                    method: 'POST',
                    url: 'edit',
                    data: file
                }).then(
                    function onSuccess(response) {
                        $window.location.href = response.data;
                    }, 
                    function onError(response) {
                        $scope.myWelcome = response.statusText;
                    }
                );
            }
        }]);

