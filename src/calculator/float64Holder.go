package calculator

type  float64Holder struct {
    value float64
    valuePtr *float64
}

func newFloat64Holder() float64Holder {
    return float64Holder{
        value: 0,
        valuePtr: nil,
    }
}

func (this float64Holder) isEmpty() bool {
    return this.valuePtr == nil
}

func (this *float64Holder) setValue(value float64) {
    this.value = value
    this.valuePtr = &(this.value)
}

func (this float64Holder) getValue() float64 {
    return this.value
}

func (this *float64Holder) clear() {
    this.value = 0
    this.valuePtr = nil
}