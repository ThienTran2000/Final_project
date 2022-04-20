#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    char request1[50];
    char request2[50];
    sprintf(request1,"canberra-gtk-play -f audio/%s.wav",argv[1]);
    sprintf(request2,"canberra-gtk-play -f audio/%s.wav",argv[2]);
    system("canberra-gtk-play -f audio/beginaudio.wav");
    system(request1);
    system("canberra-gtk-play -f audio/middleaudio.wav");
    system(request2);
    system("canberra-gtk-play -f audio/endaudio.wav");
    return 0;
}
