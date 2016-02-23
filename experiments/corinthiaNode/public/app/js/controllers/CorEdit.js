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



    corControllers.controller('corEditCtrl', ['$scope', '$routeParams', '$http', '$document',
        function($scope, $routeParams, $http, $document) {

            $scope.mode = $routeParams.mode;
            $scope.docName = $routeParams.file;
            //$scope.documentUrl = "data/" + $routeParams.file + "/" + $routeParams.file + ".html";
            $scope.documentUrl = "";

            init($scope.docName);

            //should move this down to a service
            function init(file) {
                $http({
                    method: 'POST',
                    url: 'edit',
                    data: {name: file}
                }).then(
                    function onSuccess(response) {
                        $scope.$emit("Corintia.get");
                    }, 
                    function onError(response) {
                        $scope.myWelcome = response.statusText;
                    }
                );
            }

            $scope.$on("Corintia.get", function(){
                            $scope.documentUrl = "data/" + $routeParams.file + "/" + $routeParams.file + ".html";
            });

            $scope.insertX = function() {
                //need to do this to the document in the iframe...

                function deleteNeighbours(node)
                {
                    while (node.previousSibling != null)
                        w.globalAPI.dom.deleteNode(node.previousSibling);
                    while (node.nextSibling != null)
                        w.globalAPI.dom.deleteNode(node.nextSibling);
                }

                var ef = $document[0].getElementById("editFrame");
                var w = ef.contentWindow;
                w.eval(allCode);
                var d = w.document;
                w.globalAPI.dom.assignNodeIds(d);
                var b = d.getElementsByTagName("body")

                var p = d.getElementsByTagName("P")[0];
                deleteNeighbours(p);

                w.globalAPI.selection.setEmptySelectionAt(b[0],0);

                w.globalAPI.cursor.insertCharacter("X");
            }

        }]);

