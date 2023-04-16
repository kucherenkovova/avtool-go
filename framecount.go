package avtool

/*
#cgo pkg-config: libavformat
#include <stdlib.h>
#include "framecount.h"
*/
import "C"
import "unsafe"

func GetFrameCount(videoFilePath string) (int64, error) {
	cinput := C.CString(videoFilePath)
	defer C.free(unsafe.Pointer(cinput))

	frameCount := int64(C.get_frame_count(cinput))
	return frameCount, nil
}
