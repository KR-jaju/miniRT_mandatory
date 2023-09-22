#include <stdio.h>
#include "console.h"
#include "settings.h"

void	console_msg(const char *msg)
{
	printf("%s\n", msg);
}

void	console_settings(void)
{
	printf(ANSI_BLUE);
	printf("-------- Rendering settings --------\n");
	printf("Image Size: \n");
	printf("\tWidth=%d, Height=%d\n", IMAGE_WIDTH, IMAGE_HEIGHT);
	printf("Image Update Interval: %d%%\n", IMAGE_PUT_INTERVAL_PERCENT);
	printf("Smooth Shading: %d (if false, Flat Shading)\n", SMOOTH_SHADING);
	printf("Resolution: %d\n", RESOLUTION);
	printf("Material: \n");
	printf("\treflectivity=%f\n", REFLECTIVITY);
	printf("\tk_diffuse=%f\n", K_DIFFUSE);
	printf("\tk_specular=%f\n", K_SPECULAR);
	printf("\tshininess=%d\n", SHININESS);
	printf("------------------------------------\n");
	printf(ANSI_RESET);
}

void	console_start(void)
{
	console_msg(ANSI_GREEN""MSG_SCENE_LOADED"\n"ANSI_RESET);
	console_settings();
	console_msg(ANSI_RESET);
	console_msg(MSG_RENDER_START);
	console_msg(MSG_RENDER_PROGRESS"\n");
}
