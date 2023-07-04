package main

import (
	"fmt"
	"os"
	"time"

	"github.com/stianeikeland/go-rpio/v4"
)

func main() {
	fmt.Println("Starting Program...")

	err := rpio.Open()
	if err != nil {
		os.Exit(1)
	}

	defer rpio.Close()

	pin := rpio.Pin(12)
	pin.Mode(rpio.Pwm)
	pin.Freq(50)
	pin.DutyCycle(0, 32)

	time.Sleep(time.Second * 3)
}
