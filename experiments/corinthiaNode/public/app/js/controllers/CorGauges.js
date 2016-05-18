(function() {
    'use strict';
    angular
        .module('corTest')
        .controller('CorinthiaGaugesCtrl', CorinthiaGaugesCtrl);

    CorinthiaGaugesCtrl.$inject = ['$scope', '$log', 'testsService'];

    function CorinthiaGaugesCtrl($scope, $log, testsService) {
        var vm = this;
        vm.testList = testsService.testList;
        vm.addTest = addTest;
        vm.coverage = [];
        vm.showall = false;

        vm.gaugeFilter = gaugeFilter;

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

        function addTest(test) {
            return testsService.getCoverage(test)
                .then(function(coverage) {
                    if (vm.coverage.length === 0) {
                        for (var ns = 0; ns < coverage.length; ns++) {
                            var namespace = coverage[ns];
                            namespace.total = 0;
                            for (var g = 0; g < namespace.gauges.length; g++) {
                                if (namespace.gauges[g].value) {
                                    namespace.total += namespace.gauges[g].value;
                                }
                            }
                            vm.coverage.push(namespace);
                        }
                    } else {
                        adjustGauges(coverage, test.check);
                    }
                });
        }

        function gaugeFilter(ele) {
            if (vm.showall) {
                return true;
            } else if (ele.total > 0) {
                return true;
            } else if (ele.value > 0) {
                return true;
            } else {
                return false;
            }
        }

        function adjustGauges(coverage, adding) {
            for (var ns = 0; ns < coverage.length; ns++) {
                var nsgauges = coverage[ns].gauges;
                for (var g = 0; g < nsgauges.length; g++) {
                    if (adding) {
                        if (nsgauges[g].value) {
                            vm.coverage[ns].gauges[g].value += nsgauges[g].value;
                            vm.coverage[ns].total += nsgauges[g].value;
                        }
                    } else {
                        if (nsgauges[g].value) {
                            vm.coverage[ns].gauges[g].value -= nsgauges[g].value;
                            vm.coverage[ns].total -= nsgauges[g].value;
                        }
                    }
                }
            }

        }
    }
})();
