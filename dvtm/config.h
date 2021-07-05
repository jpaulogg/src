/* valid curses attributes are listed below they can be ORed
 *
 * A_NORMAL        Normal display (no highlight)
 * A_STANDOUT      Best highlighting mode of the terminal.
 * A_UNDERLINE     Underlining
 * A_REVERSE       Reverse video
 * A_BLINK         Blinking
 * A_DIM           Half bright
 * A_BOLD          Extra bright or bold
 * A_PROTECT       Protected mode
 * A_INVIS         Invisible or blank mode
 */

enum {
	DEFAULT,
	RED,
	GREEN,
};

static Color colors[] = {
	[DEFAULT] =  { .fg = -1,           .bg = -1, .fg256 = -1, .bg256 = -1, },
	[RED]     =  { .fg = COLOR_RED,    .bg = -1, .fg256 = 1,  .bg256 = -1, },
	[GREEN]   =  { .fg = COLOR_GREEN,  .bg = -1, .fg256 = 10, .bg256 = -1, },
};

#define COLOR(c)        COLOR_PAIR(colors[c].pair)
/* curses attributes for the currently focused window */
#define SELECTED_ATTR   (COLOR(GREEN) | A_BOLD)
/* curses attributes for normal (not selected) windows */
#define NORMAL_ATTR     (COLOR(DEFAULT) | A_NORMAL)
/* curses attributes for a window with pending urgent flag */
#define URGENT_ATTR     NORMAL_ATTR
/* curses attributes for the status bar */
#define BAR_ATTR        (COLOR(DEFAULT) | A_DIM)
/* characters for beginning and end of status bar message */
#define BAR_BEGIN       '['
#define BAR_END         ']'
/* status bar (command line option -s) position */
#define BAR_POS         BAR_TOP /* BAR_BOTTOM, BAR_OFF */
/* whether status bar should be hidden if only one client exists */
#define BAR_AUTOHIDE    true
/* master width factor [0.1 .. 0.9] */
#define MFACT 0.5
/* number of clients in master area */
#define NMASTER 1
/* scroll back buffer size in lines */
#define SCROLL_HISTORY 1000
/* printf format string for the tag in the status bar */
#define TAG_SYMBOL   "[%s]"
/* curses attributes for the currently selected tags */
#define TAG_SEL      (COLOR(GREEN) | A_BOLD)
/* curses attributes for not selected tags which contain no windows */
#define TAG_NORMAL   (COLOR(DEFAULT) | A_NORMAL)
/* curses attributes for not selected tags which contain windows */
#define TAG_OCCUPIED (COLOR(DEFAULT) | A_BOLD)
/* curses attributes for not selected tags which with urgent windows */
#define TAG_URGENT (COLOR(RED) | A_NORMAL | A_BLINK)

const char tags[][8] = { "1", "2", "3", "4", "5" };

#include "tile.c"
#include "grid.c"
#include "bstack.c"
#include "fullscreen.c"
#include "tstack.c"
#include "vstack.c"

/* by default the first layout entry is used */
static Layout layouts[] = {
	{ "[]=", tile },
	{ "TTT", bstack },
	{ "+++", grid },
	{ "[ ]", fullscreen },
};

#define MOD  CTRL('g')
#define TAGKEYS(KEY,TAG) \
	{ { MOD, KEY,              }, { view,           { tags[TAG] }  } }, \
	{ { MOD, CTRL('v'), KEY,   }, { toggleview,     { tags[TAG] }  } }, \
	{ { MOD, CTRL('t'), KEY,   }, { toggletag,      { tags[TAG] }  } },

/* you can specifiy at most 3 arguments */
static KeyBinding bindings[] = {
	{ { MOD, '\r',           }, { create,         { NULL }                    } },
	{ { MOD, 'n',            }, { create,         { NULL, NULL, "$CWD" }      } },
	{ { MOD, 'c',            }, { killclient,     { NULL }                    } },
	{ { MOD, 'q',            }, { quit,           { NULL }                    } },
	{ { MOD, 'w',            }, { focusnext,      { NULL }                    } },
	{ { MOD, 'j',            }, { focusdown,      { NULL }                    } },
	{ { MOD, 'k',            }, { focusup,        { NULL }                    } },
	{ { MOD, 'h',            }, { focusleft,      { NULL }                    } },
	{ { MOD, 'l',            }, { focusright,     { NULL }                    } },
	{ { MOD, 't',            }, { setlayout,      { "[]=" }                   } },
	{ { MOD, 'g',            }, { setlayout,      { "+++" }                   } },
	{ { MOD, 'b',            }, { setlayout,      { "TTT" }                   } },
	{ { MOD, 'm',            }, { setlayout,      { "[ ]" }                   } },
	{ { MOD, ' ',            }, { setlayout,      { NULL }                    } },
	{ { MOD, 'J',            }, { incnmaster,     { "+1" }                    } },
	{ { MOD, 'K',            }, { incnmaster,     { "-1" }                    } },
	{ { MOD, '-',            }, { setmfact,       { "-0.05" }                 } },
	{ { MOD, '+',            }, { setmfact,       { "+0.05" }                 } },
	{ { MOD, 'H',            }, { toggleminimize, { NULL }                    } },
	{ { MOD, 's',            }, { togglebar,      { NULL }                    } },
	{ { MOD, 'M',            }, { togglemouse,    { NULL }                    } },
	{ { MOD, KEY_BACKSPACE,  }, { zoom ,          { NULL }                    } },
	{ { MOD, 'p',            }, { focuslast,      { NULL }                    } },
	{ { MOD, 'a',            }, { togglerunall,   { NULL }                    } },
	{ { MOD, CTRL('L'),      }, { redraw,         { NULL }                    } },
	{ { MOD, 'r',            }, { redraw,         { NULL }                    } },
	{ { MOD, 'e',            }, { copymode,       { "dvtm-editor" }           } },
	{ { MOD, 'E',            }, { copymode,       { "dvtm-pager" }            } },
	{ { MOD, '/',            }, { copymode,       { "dvtm-pager", "/" }       } },
	{ { MOD, 'P',            }, { paste,          { NULL }                    } },
	{ { KEY_SPREVIOUS,       }, { scrollback,     { "-1" }                    } },
	{ { KEY_SNEXT,           }, { scrollback,     { "1"  }                    } },
	{ { MOD, '?',            }, { create,         { "man dvtm", "Dvtm help" } } },
	{ { MOD, '0',            }, { view,           { NULL }                    } },
	{ { MOD, '\t',           }, { viewprevtag,    { NULL }                    } },
	{ { MOD, '!',            }, { tag,            { tags[0] }                 } },
	{ { MOD, '@',            }, { tag,            { tags[1] }                 } },
	{ { MOD, '#',            }, { tag,            { tags[2] }                 } },
	{ { MOD, '$',            }, { tag,            { tags[3] }                 } },
	{ { MOD, '%',            }, { tag,            { tags[4] }                 } },
	{ { MOD, ')'             }, { tag,            { NULL }                    } },
	/* Minhas adições */  
	{ { MOD, 'd',            }, { create,     { "lf -command two-panels", NULL, "$CWD" } } },
	/* Tagkeys */
	TAGKEYS( '1',                              0)
	TAGKEYS( '2',                              1)
	TAGKEYS( '3',                              2)
	TAGKEYS( '4',                              3)
	TAGKEYS( '5',                              4)
};

static const ColorRule colorrules[] = {
	{ "", A_NORMAL, &colors[DEFAULT] }, /* default */
};

/* possible values for the mouse buttons are listed below:
 *
 * BUTTON1_PRESSED          mouse button 1 down
 * BUTTON1_RELEASED         mouse button 1 up
 * BUTTON1_CLICKED          mouse button 1 clicked
 * BUTTON1_DOUBLE_CLICKED   mouse button 1 double clicked
 * BUTTON1_TRIPLE_CLICKED   mouse button 1 triple clicked
 * BUTTON2_PRESSED          mouse button 2 down
 * BUTTON2_RELEASED         mouse button 2 up
 * BUTTON2_CLICKED          mouse button 2 clicked
 * BUTTON2_DOUBLE_CLICKED   mouse button 2 double clicked
 * BUTTON2_TRIPLE_CLICKED   mouse button 2 triple clicked
 * BUTTON3_PRESSED          mouse button 3 down
 * BUTTON3_RELEASED         mouse button 3 up
 * BUTTON3_CLICKED          mouse button 3 clicked
 * BUTTON3_DOUBLE_CLICKED   mouse button 3 double clicked
 * BUTTON3_TRIPLE_CLICKED   mouse button 3 triple clicked
 * BUTTON4_PRESSED          mouse button 4 down
 * BUTTON4_RELEASED         mouse button 4 up
 * BUTTON4_CLICKED          mouse button 4 clicked
 * BUTTON4_DOUBLE_CLICKED   mouse button 4 double clicked
 * BUTTON4_TRIPLE_CLICKED   mouse button 4 triple clicked
 * BUTTON_SHIFT             shift was down during button state change
 * BUTTON_CTRL              control was down during button state change
 * BUTTON_ALT               alt was down during button state change
 * ALL_MOUSE_EVENTS         report all button state changes
 * REPORT_MOUSE_POSITION    report mouse movement
 */

#ifdef NCURSES_MOUSE_VERSION
# define CONFIG_MOUSE /* compile in mouse support if we build against ncurses */
#endif

#define ENABLE_MOUSE true /* whether to enable mouse events by default */

#ifdef CONFIG_MOUSE
static Button buttons[] = {
	{ BUTTON1_CLICKED,        { mouse_focus,      { NULL  } } },
	{ BUTTON1_DOUBLE_CLICKED, { mouse_fullscreen, { "[ ]" } } },
	{ BUTTON2_CLICKED,        { mouse_zoom,       { NULL  } } },
	{ BUTTON3_CLICKED,        { mouse_minimize,   { NULL  } } },
};
#endif /* CONFIG_MOUSE */

static Cmd commands[] = {
	/* create [cmd]: create a new window, run `cmd` in the shell if specified */
	{ "create", { create,	{ NULL } } },
	/* focus <win_id>: focus the window whose `DVTM_WINDOW_ID` is `win_id` */
	{ "focus",  { focusid,	{ NULL } } },
	/* tag <win_id> <tag> [tag ...]: add +tag, remove -tag or set tag of the window with the given identifier */
	{ "tag",    { tagid,	{ NULL } } },
	/* Minhas adições */
	{ "view2",  { view,     { tags[1] } } },
};

/* gets executed when dvtm is started */
static Action actions[] = {
	{ create, { NULL } },
};

static char const * const keytable[] = {
	/* add your custom key escape sequences */
};
