package calculator

import "errors"

type Calculator struct {
    expression string
    operator stringHolder
    cacheNum float64Holder
    cacheOp stringHolder
    state parseState
    result float64
}

func NewCalculator(expression string) Calculator {
    return Calculator{
        deleteSpaces(expression),
        newStringHolder(),
        newFloat64Holder(),
        newStringHolder(),
        psEmpty,
        0,
    }
}

func (this *Calculator) Calculate() (float64, error) {
    for len(this.expression) > 0 {
        if this.state == psNumber {
            err := this.absorbOperator()
            if err != nil {
                return 0, err
            }
        } else {
            err := this.absorbNumber()
            if err != nil {
                return 0, err
            }
        }
    }

    if this.state == psEmpty {
        return 0, errors.New("Empty expression")
    } else {
        err := this.flushCache()
        if err != nil {
            return 0, err
        }
    }

    return this.result, nil
}

func (this *Calculator) absorbOperator() error {
    operator := operatorRegexp.FindString(this.expression)
    if len(operator) <= 0 {
        return this.getUnexpectedTokenError("operator")
    }

    this.processOperator(operator)
    this.trimLeftOnce(operator)
    this.state = psOperator
    return nil
}

func (this *Calculator) absorbNumber() error {
    numberStr := numRegexp.FindString(this.expression)
    if len(numberStr) <= 0 {
        return this.getUnexpectedTokenError("number")
    }

    this.processNumber(strToFloat64(numberStr))
    this.trimLeftOnce(numberStr)
    this.state = psNumber
    return nil
}

func (this *Calculator) processOperator(operator string) {
    if this.cacheOp.isEmpty() {
        this.cacheOp.setValue(operator)
    } else {
        this.operator.setValue(operator)
    }
}

func (this *Calculator) processNumber(number float64) {
    if this.state == psEmpty {
        this.result = number
    } else if this.cacheNum.isEmpty() {
        this.cacheNum.setValue(number)

        if isHighPriorityOperator(this.cacheOp.getValue()) {
            this.flushCache()
        }
    } else {
        if isHighPriorityOperator(this.operator.getValue()) {
            this.cacheNum.setValue(processOperator(this.operator.getValue(), this.cacheNum.getValue(), number))
        } else {
            this.flushCache()
            this.cacheOp.setValue(this.operator.getValue())
            this.cacheNum.setValue(number)
        }

        this.operator.clear()
    }
}

func (this *Calculator) flushCache() error {
    if this.cacheOp.isEmpty() {
        return nil
    } else if this.cacheNum.isEmpty() {
        return errors.New("Last token can't be operator")
    }

    this.result = processOperator(this.cacheOp.getValue(), this.result, this.cacheNum.getValue())
    this.cacheOp.clear()
    this.cacheNum.clear()
    return nil
}

func (this Calculator) getUnexpectedTokenError(expected string) error {
    return errors.New("Look for: " + expected + ", unexpected token: " + this.expression)
}

func (this *Calculator) trimLeftOnce(str string) {
    this.expression = deleteSubStrLeftOnce(this.expression, str)
}