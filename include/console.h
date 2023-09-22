#ifndef CONSOLE_H
#define CONSOLE_H

/* ---------------------------- MACRO CONSTANTS ----------------------------- */

// ANSI styles
# define ANSI_RESET		"\x1b[0m"
# define ANSI_GRAY		"\033[37m"
# define ANSI_BLACK		"\x1b[30m"
# define ANSI_RED		"\x1b[31m"
# define ANSI_GREEN		"\x1b[32m"
# define ANSI_YELLOW	"\x1b[33m"
# define ANSI_BLUE		"\x1b[34m"
# define ANSI_MAGENTA	"\x1b[35m"
# define ANSI_CYAN		"\x1b[36m"
# define ANSI_WHITE		"\x1b[37m"
# define ANSI_BOLD		"\x1b[1m"
# define ANSI_DIM		"\x1b[2m"
# define ANSI_UNDERLINE	"\x1b[4m"
# define ANSI_REVERSE	"\x1b[7m"

// message for usual case
# define MSG_USAGE "Usage: miniRT <filename>.rt"
# define MSG_SCENE_LOADED "Scene loaded successfully"
# define MSG_RENDER_START	"Start rendering"
# define MSG_RENDER_PROGRESS	"Rendering in progress..."
# define MSG_RENDER_FINISHED	"Rendering finished!"
# define MSG_SHUTDOWN	"Shutting down program"

// message for error case
# define MSG_ERROR_MALLOC "memory allocation failed"
# define MSG_ERROR_FILEOPEN "file open failed"
# define MSG_ERROR_INVALID_LINE_FORMAT "invalid line format"
# define MSG_ERROR_DUPLIATE_DECLARED "duplicate declared"
# define MSG_ERROR_MANDATORY_NOT_EXIST "mandatory element not exist in scene"

/* --------------------------- FUNCTION PROTOTYPES -------------------------- */

void	console_msg(const char *msg);
void	console_start(void);
void	console_finish(void);

#endif
