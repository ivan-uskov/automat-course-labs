package calculator

import "strings"
import "strconv"


func deleteSpaces(str string) string {
    return strings.Replace(str, " ", "", -1)
}

func strToFloat64(str string) float64 {
    result, err := strconv.ParseFloat(str, 64)
    if err != nil {
        panic("Has no suitable conversion to float64: " + str)
    }

    return result
}

func deleteSubStrLeftOnce(str string, subStr string) string {
    return strings.Replace(str, subStr, "", 1)
}

func processOperator(operator string, lhs float64, rhs float64) float64 {
    if operator == "+" {
        return lhs + rhs
    } else if operator == "-" {
        return lhs - rhs
    } else if operator == "*" {
        return lhs * rhs
    } else if operator == "/" {
        return lhs / rhs
    } else {
        panic("Invalid operator")
    }
}

func isHighPriorityOperator(op string) bool {
    return op == "*" || op == "/"
}