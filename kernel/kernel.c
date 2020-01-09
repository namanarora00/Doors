#include "low_level.h"

void main()
{

    char *video_mem = (char *)0xb8000; // address offset of the first text cell of the video memeory.
    int n = 5;

    char *name = "Naman";
    int i = 0;

    *video_mem = 'K';
    video_mem += 2;

    *video_mem = 'A';
    video_mem += 2;

    *video_mem = 'N';
    video_mem += 2;

    *video_mem = 'A';
    video_mem += 2;

    *video_mem = 'O';
    video_mem += 2;

    *video_mem = 'S';
    video_mem += 2;

    *video_mem = ' ';
    video_mem += 2;
}