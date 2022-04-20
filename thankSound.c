#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	system("canberra-gtk-play -f audio/thankyou.wav");
	return 0;
}
