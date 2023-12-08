#ifndef VIDEO_H
#define VIDEO_H


#include <stdint.h>
//Ideas for delaying for video interrupt:
//keep a "queue" of stuff that needs to be written to video memory
//Need 3 things: num bytes, where they're being written, and buffer of bytes to write



typedef struct video_buf {
    uint16_t num_bytes;
    uint16_t num_words;
    volatile uint8_t * video_mem8;
    volatile uint32_t * video_mem32;
    uint8_t * bytes;
    uint32_t * words;
} video_buf;

typedef struct vid_node {
    video_buf data;
    struct vid_node * next;
} vid_node;

extern vid_node* video_queue;

void load_video_data();

void add_to_video_queue(video_buf buf);

void clear_video_queue();

#endif