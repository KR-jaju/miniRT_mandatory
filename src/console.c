#include <stdio.h>
#include "console.h"
#include "settings.h"

void	console_msg(const char *msg)
{
	printf("%s\n", msg);
}

void	console_settings(void)
{
	printf("-------------- Rendering settings --------------\n");
	printf("Image Size: ");
	printf("width=%d, height=%d\n", IMAGE_WIDTH, IMAGE_HEIGHT);
	printf("Image Update Interval: %d%%\n", IMAGE_PUT_INTERVAL_PERCENT);
	printf("Smooth Shading: %d (If false, Flat Shading)\n", SMOOTH_SHADING);
	printf("Resolution: %f\n", RESOLUTION);
	printf("Material: ");
	printf("reflectivity=%.1f, ", REFLECTIVITY);
	printf("k_diffuse=%.1f, \n\t", K_DIFFUSE);
	printf("  k_specular=%.1f, ", K_SPECULAR);
	printf("shininess=%f\n", SHININESS);
	if (K_DIFFUSE + K_SPECULAR > 1)
		printf(ANSI_YELLOW \
		"\t(Warning: k_diffuse + k_specular is bigger than 1)\n"\
		ANSI_BLUE);
	printf("------------------------------------------------\n");
	printf(ANSI_RESET);
}

void	console_start(void)
{
	console_msg(ANSI_GREEN"\n"MSG_SCENE_LOADED"\n"ANSI_RESET);
	console_settings();
	console_msg(ANSI_RESET);
	console_msg(MSG_RENDER_START);
	console_msg(MSG_RENDER_PROGRESS"\n");
}

void	console_finish(void)
{
	console_msg("\n"ANSI_GREEN""MSG_RENDER_FINISHED);
}
