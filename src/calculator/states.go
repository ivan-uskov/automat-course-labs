package calculator

type parseState int
const (
    psEmpty parseState = iota
    psOperator
    psNumber
)