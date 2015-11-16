package calculator

type stringHolder struct {
    str string
    strPtr *string
}

func newStringHolder() stringHolder {
    return stringHolder{
        str: "",
        strPtr: nil,
    }
}

func (this stringHolder) isEmpty() bool {
    return this.strPtr == nil
}

func (this *stringHolder) setValue(value string) {
    this.str = value
    this.strPtr = &(this.str)
}

func (this stringHolder) getValue() string {
    return this.str
}

func (this *stringHolder) clear() {
    this.str = ""
    this.strPtr = nil
}