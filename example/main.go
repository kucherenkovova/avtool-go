package main

import (
	"fmt"

	"github.com/kucherenkovova/avtool-go"
)

func main() {
	fps, err := avtool.GetFPS("./testdata/video.mp4")
	if err != nil {
		panic(err)
	}
	fmt.Println(fps)
}
