#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>

void	clear_console(void)
{
#ifdef _WIN32
   	system("cls"); // Windows
#else
    system("clear"); // Linux/macOS 
#endif
}

void	console_progressbar(int progress, int total)
{
    const int barWidth = 50;
    float percentage = (float)progress / total;
    int progressBarWidth = (int)(percentage * barWidth);

    printf("[");
    for (int i = 0; i < barWidth; i++) {
        if (i < progressBarWidth) {
            printf("#"); // 진행 부분은 "#"으로 표시
        } else {
            printf(" "); // 나머지는 공백으로 표시
        }
    }
    printf("] %.2f%%\r", percentage * 100); // 퍼센트 표시 및 커서 이동
    fflush(stdout); // 버퍼 비우기
}

void	console_msg(const char *msg)
{
	printf("%s\n", msg);
}
