#include <stdio.h>
#include <unistd.h>

void clear_console(void)
{
#ifdef _WIN32
   	system("cls"); // Windows
#else
    system("clear"); // Linux/macOS 
#endif
}

void print_progress_bar(int progress, int total) {
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

// int main() {
//     int total = 100; // 총 진척도
//     for (int progress = 0; progress <= total; progress++) {
//         clearConsole(); // 콘솔 화면 지우기
//         printProgressBar(progress, total);
//         usleep(100000); // 100,000 마이크로초 (0.1초) 대기
//     }

//     printf("\n작업 완료\n");

//     return 0;
// }
