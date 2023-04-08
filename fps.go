package avtool

/*
#cgo pkg-config: libavformat
#include <stdlib.h>
#include "fps.h"
*/
import "C"
import "unsafe"

func GetFPS(videoFilePath string) (float64, error) {
	cinput := C.CString(videoFilePath)
	defer C.free(unsafe.Pointer(cinput))

	fps := float64(C.get_video_fps(cinput))
	return fps, nil
}
