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

var testControllers = angular.module('corTest');

testControllers.controller('corAutoEditCtrl', ['$scope', '$routeParams', '$http', '$document', '$location',
    function($scope, $routeParams, $http, $document, $location) {

        $scope.testName = $routeParams.test;
        $scope.documentUrl = "";


        // We should/could go get the test definition file and then do the init - or document process thing...
        // Also the directory names may need to be flipped about to put the relevant test data into the test directory
        // So post to test rather than edit
        // that way we can get the seed document name and it can then be separate to the test name

        var docHead = $document[0].head;
        var testScript = $document[0].createElement("script");
        testScript.setAttribute("src", "tests/" + $routeParams.test + "/runtest.js");
        docHead.appendChild(testScript);

        getTest($scope.testName);


        //should move this down to a service
        function getTest(test) {
            $http({
                method: "Get",
                url: "tests/" + test + "/" + test + ".json",
            }).then(
                function onSuccess(response) {
                    $scope.testData = response.data;
                    $scope.$emit("Corintia.testData");
                },
                function onError(response) {
                    $scope.myWelcome = response.statusText;
                }
            );
        }
        //should move this down to a service
        function init(test, documentName) {
            $http({
                method: 'POST',
                url: 'edit',
                data: {
                    name: documentName,
                    dataDirectory: test
                }
            }).then(
                function onSuccess(response) {
                    $scope.$emit("Corintia.get");
                },
                function onError(response) {
                    $scope.myWelcome = response.statusText;
                }
            );
        }

        $scope.$on("Corintia.testData", function() {
            init($scope.testName, $scope.testData.seedDoc);
        });

        $scope.$on("Corintia.get", function() {
            $scope.documentUrl = "data/" + $scope.testData.seedDoc + "/" + $scope.testData.seedDoc + ".html";
        });

        $scope.saveDoc = function() {
            cleanup();
            var ef = $document[0].getElementById("editFrame");
            var w = ef.contentWindow;
            var d = w.document;
            //var jdoc = JSON.stringify(d.documentElement.outerHTML);
            //send document d to the server.
            $http({
                method: 'POST',
                url: '/corput',
                data: {
                    doc: d.documentElement.outerHTML
                }
            }).then(
                function onSuccess(response) {
                    $location.url("app/test.html")
                },
                function onError(response) {
                    $scope.myWelcome = response.statusText;
                }
            );
        }


    }
]);
