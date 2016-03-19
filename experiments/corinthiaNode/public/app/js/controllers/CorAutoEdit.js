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

(function() {
    'use strict';

    angular
        .module('corTest')
        .controller('CorAutoEditCtrl', CorAutoEditCtrl);

    CorAutoEditCtrl.$inject = ['$scope', '$routeParams', '$http', '$document', '$location', '$log', 'testsService'];

    /* @ngInject */
    function CorAutoEditCtrl($scope, $routeParams, $http, $document, $location, $log, testsService) {
        var vm = this;
        vm.testName = $routeParams.test;
        vm.documentUrl = "";
        vm.testData = {};

        $scope.autoSaveDoc = autoSaveDoc;
        vm.saveDoc = saveDoc;

        // We should/could go get the test definition file and then do the init - or document process thing...
        // Also the directory names may need to be flipped about to put the relevant test data into the test directory
        // So post to test rather than edit
        // that way we can get the seed document name and it can then be separate to the test name

        var docHead = $document[0].head;
        var testScript = $document[0].createElement("script");
        testScript.setAttribute("src", "tests/" + $routeParams.test + "/runtest.js");
        docHead.appendChild(testScript);

        getTest(vm.testName);

        function getTest(testName) {
            var url = 'tests/' + testName + '/test.json';
            testsService.getTest(url)
                .then(function(testData) {
                    vm.testData = testData;
                    seed(vm.testName, vm.testData.seedDoc);
                })
                .catch(function(err) {
                    $log.error(err);
                }); //can we get this?
        }

        function seed(testName, documentName) {
            var editdata = {
                test: testName,
                seedDoc: documentName
            };
            testsService.seed('seedtest', editdata)
                .then(function(dochtml) {
                    //set the documentUrl to trigger load
                    //and cause the test to run
                    vm.documentUrl = "tests/" + vm.testName + "/" + vm.testData.seedDoc + ".html";
                })
                .catch(function(err) {
                    $log.error(err);
                });
        }

        function autoSaveDoc() {
            vm.saveDoc(vm.testData.name, vm.testData.seedDoc);
        }

        function saveDoc(testName, doc) {
            cleanup();
            var ef = $document[0].getElementById("editFrame");
            var w = ef.contentWindow;
            var d = w.document;
            //send document d to the server.
            var data = {
                abstractHTML: d.documentElement.outerHTML,
                documentName: doc,
                test: testName
            };
            testsService.saveDoc(data)
            .then(function(resp){
                $location.url("app/test.html");
            })
            .catch(function(err) {
                $log.error(err);
            });
        }
    }
})();
