#include <stdio.h>
#include <libavformat/avformat.h>
#include "fps.h"

double get_video_fps(const char* video_file_path) {
    AVFormatContext* format_ctx = NULL;
    AVCodecParameters* codec_params = NULL;

    // todo: check return code
    avformat_open_input(&format_ctx, video_file_path, NULL, NULL);
    avformat_find_stream_info(format_ctx, NULL);

    int video_stream_index = av_find_best_stream(format_ctx, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);

    if (video_stream_index == -1) {
        fprintf(stderr, "Failed to find video stream in the input file\n");
        exit(1);
    }
    // convert rational to number
    double fps = av_q2d(format_ctx->streams[video_stream_index]->avg_frame_rate);

    avformat_close_input(&format_ctx);
    return fps;
}