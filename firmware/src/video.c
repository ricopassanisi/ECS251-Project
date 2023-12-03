#include <core/video.h>
#include <stdlib.h>

vid_node * video_queue = NULL;

void load_video_data() {
    //Loop over video queue

    vid_node * head = video_queue;

    while(head != NULL) {
        //load in bytes in data
        video_buf buffer = head->data;
        
        for(int i = 0; i < buffer.num_bytes; ++i) {
            buffer.video_mem8[i] = buffer.bytes[i];
        }
        
        
        for(int i = 0; i < buffer.num_words; ++i) {
            buffer.video_mem32[i] = buffer.words[i];
        }
        
        head = head->next;
    }

}

void add_to_video_queue(video_buf buf) {

    if(video_queue == NULL) {
        video_queue = (vid_node*) malloc(sizeof(vid_node));
        video_queue->data = buf;
        video_queue->next = NULL;
    } else {
        //vid_node * head = video_queue;
        //while(head->next != NULL) { //find next empty slot
        //    head = head->next;
        //}
        //head->next = (vid_node*) malloc(sizeof(vid_node));
        //head->next->data = buf;
        //head->next->next = NULL;

        vid_node * head = (vid_node*) malloc(sizeof(vid_node));
        head->data = buf;
        head->next = video_queue;
        video_queue = head;

    }

}

void clear_video_queue() {
    vid_node * head = video_queue;

    if(head == NULL) return;

    while(head->next != NULL) {
        video_queue = video_queue->next;
        free(head);
        free(head->data.words);
        head = video_queue;
    }
}
