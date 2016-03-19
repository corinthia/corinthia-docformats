/*
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
        .factory('testsService', testsService);

    testsService.$inject = ['$http', '$log'];

    function testsService($http, $log) {
        var service = {
            testlist: [],
            currentTest: {},

            //functions
            getTests: getTests,
            getTest: getTest,
            seed: seed,
            saveDoc: saveDoc
        };
        return service;

        ////////////////
        function getTests($scope) {
            return $http.get('tests.json')
                .then(listComplete)
                .catch(errHandler);
        }

        function listComplete(res) {
            return res.data.tests;
        }

        function errHandler(err) {
            $log.error(err);
        }

        ///////////////////////////
        function getTest(from) {
            return $http.get(from)
                .then(testResponse)
                .catch(testErr);
        }
        //should move this down to a service
        function testResponse(response) {
            service.currentTest = response.data;
            return response.data;
        }

        function testErr(err) {
            $log.error(err.statusText);
        }

        ///////////////////////////
        function seed(url, data) {
            return $http.post(url, data)
                .then(seeded)
                .catch(seedErr);
        }

        function seeded(res) {
            return res.data;
        }

        function seedErr(err) {
            $log.error(err);
        }
        ////////////////////////////////
        function saveDoc(data) {
            return $http.post('save', data)
                .then(saved)
                .catch(saveErr);
        }

        function saved(response) {
            return response.data;
        }

        function saveErr(response) {
            $log.error(response.statusText);
        }
    }
})();
