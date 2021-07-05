/*
 * Define ESC sequences to use for scroll events.
 * Use "cat -v" to figure out favorite key combination.
 *
 * lines is the number of lines scrolled up or down.
 * If lines is negative, it's the fraction of the terminal size.
 */

struct rule rules[] = {
	/* sequence    event        lines */
	{"\033[2J",    SCROLL_UP,    25},   /* [Shift] + [Home] */
	{"\033[K",     SCROLL_DOWN,  25},   /* [Shift] + [End] */
	{"\033[5;2~",  SCROLL_UP,     1},   /* [Shift] + [PageUP or mouse wheel up] */
	{"\033[6;2~",  SCROLL_DOWN,   1},   /* [Shift] + [PageDown or mouse wheel down]*/
	/* mouse binding shadows ^E and ^Y, so it's disabled by default */
	/*{"\031",      SCROLL_UP,    1},   /* mouse wheel up */
	/*{"\005",      SCROLL_DOWN,  1},   /* mouse wheel Down */
};
