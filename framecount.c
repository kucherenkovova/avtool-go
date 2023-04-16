#include <stdio.h>
#include <stdlib.h>
#include <libavformat/avformat.h>
#include "framecount.h"

long get_frame_count(const char *filename) {
    AVFormatContext *format_ctx = NULL;
    int ret, frame_count = 0;

    // todo: check return code
    avformat_open_input(&format_ctx, filename, NULL, NULL);
    avformat_find_stream_info(format_ctx, NULL);

    int video_stream_index = av_find_best_stream(format_ctx, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
    if (video_stream_index == -1) {
        fprintf(stderr, "Failed to find video stream in the input file\n");
        exit(1);
    }

    // Loop through all the frames of the video
    AVPacket packet;
    while (av_read_frame(format_ctx, &packet) >= 0) {
        if (packet.stream_index == video_stream_index) {
            frame_count++;
        }
        av_packet_unref(&packet);
    }

    avformat_close_input(&format_ctx);
    return frame_count;
}
