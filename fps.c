#include <stdio.h>
#include <libavformat/avformat.h>
#include "fps.h"

double get_video_fps(const char* video_file_path) {
    AVFormatContext* format_ctx = NULL;
    int stream_index = -1;
    AVCodecParameters* codec_params = NULL;

    // todo: check return code
    avformat_open_input(&format_ctx, video_file_path, NULL, NULL);
    avformat_find_stream_info(format_ctx, NULL);

    for (int i = 0; i < format_ctx->nb_streams; i++) {
        // skip non-video streams
        if (format_ctx->streams[i]->codecpar->codec_type != AVMEDIA_TYPE_VIDEO) {
            continue;
        }
        stream_index = i;
        codec_params = format_ctx->streams[i]->codecpar;
        break;
    }

    if (stream_index == -1) {
        fprintf(stderr, "Failed to find video stream in the input file\n");
        exit(1);
    }
    // convert rational to number
    double fps = av_q2d(format_ctx->streams[stream_index]->avg_frame_rate);

    avformat_close_input(&format_ctx);
    return fps;
}