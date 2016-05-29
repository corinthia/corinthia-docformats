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
        vm.noGauges = noGauges;
        vm.gaugeStr = gaugeStr;
        vm.gaugeClass = gaugeClass;

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
                    vm.coverage[ns].gauges[g].orig = -1;
                    if (adding) {
                        if (nsgauges[g].value) {
                            vm.coverage[ns].gauges[g].orig = vm.coverage[ns].gauges[g].value;
                            vm.coverage[ns].gauges[g].value += nsgauges[g].value;
                            vm.coverage[ns].total += nsgauges[g].value;
                        }
                    } else {
                        if (nsgauges[g].value) {
                            vm.coverage[ns].gauges[g].orig = vm.coverage[ns].gauges[g].value;
                            vm.coverage[ns].gauges[g].value -= nsgauges[g].value;
                            vm.coverage[ns].total -= nsgauges[g].value;
                        }
                    }
                }
            }
        }

        //don't like the negative logic but feeding a disabled
        function noGauges(test) {
            var retval = true;
            if (test.gauges && test.gauges !== "") {
                retval = false;
            }
            return retval;
        }

        function gaugeStr(gauge) {
            if (gauge.orig && gauge.orig >=0 ) {
                return gauge.orig + " -> " + gauge.value;
            } else {
                return gauge.value;
            }
        }

        function gaugeClass(gauge) {
            if(gauge.value) {
                if(gauge.orig >= 0) {
                    return "success";
                } else {
                    return "info";
                }
            } else {
                return "info";
            }
        }
    }
})();
