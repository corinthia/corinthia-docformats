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
        .controller('CorinthiaTestCtrl', CorinthiaTestCtrl);

    CorinthiaTestCtrl.$inject = ['$scope', '$log', 'testsService'];

    //function CorinthiaTestCtrl($scope, $routeParams, $http, $window, $log, testsService) {
    function CorinthiaTestCtrl($scope, $log, testsService) {
        var vm = this;
        vm.title = "Phew, I'm alive";
        vm.testList = testsService.testList;

        vm.getTestClass = getTestClass;

        init();

        ///// functions

        function init() {
            return getTests().then(function() {
                $log.info("Tests Received");
            });
        }

        function getTests() {
            return testsService.getTests($scope)
                .then(function(tests) {
                    vm.testList = tests;
                    return vm.testList;
                });
        }

        function getTestClass(passed) {
            if(passed !== null) {
                return passed === true ? "success" : "danger";
            } else {
                return "info";
            }
        }
    }
})();
