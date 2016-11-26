package calculator

import "regexp"

var numRegexp *regexp.Regexp
var operatorRegexp *regexp.Regexp

func init() {
    numRegexp = regexp.MustCompile(`^([0-9])+(\.[0-9]+)?`)
    operatorRegexp = regexp.MustCompile(`^[\+\-\*\/]`)
}