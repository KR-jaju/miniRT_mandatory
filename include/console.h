#ifndef CONSOLE_H
#define CONSOLE_H

# define ANSI_RESET       "\x1b[0m"
# define ANSI_BLACK       "\x1b[30m"
# define ANSI_RED         "\x1b[31m"
# define ANSI_GREEN       "\x1b[32m"
# define ANSI_YELLOW      "\x1b[33m"
# define ANSI_BLUE        "\x1b[34m"
# define ANSI_MAGENTA     "\x1b[35m"
# define ANSI_CYAN        "\x1b[36m"
# define ANSI_WHITE       "\x1b[37m"

# define ANSI_BOLD        "\x1b[1m"
# define ANSI_DIM         "\x1b[2m"
# define ANSI_UNDERLINE   "\x1b[4m"
# define ANSI_REVERSE     "\x1b[7m"

# define MSG_USAGE "Usage: miniRT <filename>.rt"
# define MSG_SCENE_LOADED "Scene loaded successfully"
# define MSG_RENDER_SETTINGS "Rendering settings: "
# define MSG_RENDER_READY	"Ready"
# define MSG_RENDER_START	"Start rendering"
# define MSG_RENDER_PROGRESS	"Rendering in progress..."
# define MSG_RENDER_DONE	"Rendering done!"
# define MSG_SHUTDOWN	"Shutting down program"

void	console_msg(const char *msg);
void	console_progressbar(int progress, int total);

#endif
