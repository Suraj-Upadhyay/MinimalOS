#include "../drivers/screen.h"

void kernel_main(void)
{
	int i;
	clear_screen();
	for (i = 0; i < 25; i++)
		print("MrSquanchee\n");
}
