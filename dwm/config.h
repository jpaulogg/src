/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int focusonwheel       = 0;
static const char *fonts[]          = { "monospace:style=Semibold:size=10", "Symbols Nerd Font:size=11" };
static const char green[]           = "#87d7af";
static const char red[]             = "#d78787";
static const char black[]           = "#333333";
static const char gray[]            = "#bbbbbb";
static const char dark_gray[]       = "#707070";
static const char *colors[][3]      = {
	/*                fg       bg        border   */
	[SchemeNorm] = { gray,     black,    dark_gray },
	[SchemeSel]  = { black,    green,    red   },
};

/* tagging */
static const char *tags[] = { "", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const char *alttags[] = { "", "", "", "", "", "", "", "", "嗢", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class              instance         title       tags mask    switchtag    isfloating    monitor */
	{ "okular",           NULL,            NULL,       1 << 3,      1,           0,            -1 },
	{ NULL,               "zathura",       NULL,       1 << 3,      4,           0,            -1 },
	{ "calibre",          NULL,            NULL,       1 << 4,      1,           0,            -1 },
	{ NULL,               "libreoffice",   NULL,       1 << 4,      3,           0,            -1 },
	{ "Gimp",             NULL,            NULL,       1 << 4,      1,           0,            -1 },
	{ "Scid",             NULL,            NULL,       1 << 5,      1,           0,            -1 },
	{ "Ripcord",          NULL,            NULL,       1 << 6,      1,           0,            -1 },
	{ "Nicotine",         NULL,            NULL,       1 << 6,      1,           0,            -1 },
	{ "qBittorrent",      NULL,            NULL,       1 << 6,      1,           0,            -1 },
	{ "sxiv",             NULL,            NULL,       1 << 7,      3,           0,            -1 },
	{ "mpv",              NULL,            NULL,       1 << 8,      3,           0,            -1 },
	{ "Brave-browser",    NULL,            NULL,       1 << 9,      1,           0,            -1 },
	{ NULL,               "vimb",          NULL,       1 << 9,      1,           0,            -1 },
	{ NULL,               NULL,            "webcam",   ~0,          0,           1,            -1 },
	{ NULL,               "float",         NULL,       0,           0,           1,            -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "bstack.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "[TTT]",    bstack },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-p", "run:", "-m", dmenumon, NULL };
static const char *termcmd[]  = { "st", NULL };

#include <X11/XF86keysym.h>
#include "shiftview.c"

static Key keys[] = {
	/* modifier              key              function         argument */
	{ MODKEY,                XK_d,            spawn,           {.v = dmenucmd } },
	{ MODKEY,                XK_Return,       spawn,           {.v = termcmd } },
	{ MODKEY,                XK_s,            togglebar,       {0} },
	{ MODKEY,                XK_j,            focusstack,      {.i = +1 } },
	{ MODKEY,                XK_k,            focusstack,      {.i = -1 } },
	{ MODKEY|ShiftMask,      XK_j,            incnmaster,      {.i = +1 } },
	{ MODKEY|ShiftMask,      XK_k,            incnmaster,      {.i = -1 } },
	{ MODKEY,                XK_h,            setmfact,        {.f = -0.05} },
	{ MODKEY,                XK_l,            setmfact,        {.f = +0.05} },
	{ MODKEY,                XK_BackSpace,    zoom,            {0} },
	{ MODKEY,                XK_Tab,          view,            {0} },
	{ MODKEY|ShiftMask,      XK_q,            killclient,      {0} },
	{ MODKEY,                XK_t,            setlayout,       {.v = &layouts[0]} },
	{ MODKEY,                XK_b,            setlayout,       {.v = &layouts[3]} }, /* bstack */
	{ MODKEY,                XK_f,            setlayout,       {.v = &layouts[1]} },
	{ MODKEY,                XK_m,            setlayout,       {.v = &layouts[2]} },
	{ MODKEY,                XK_space,        setlayout,       {0} },
	{ MODKEY|ShiftMask,      XK_f,            togglefloating,  {0} },
	{ MODKEY,                XK_0,            view,            {.ui = ~0 } },
	{ MODKEY|ShiftMask,      XK_0,            tag,             {.ui = ~0 } },
	{ Mod1Mask,              XK_Tab,          focusmon,        {.i = +1 } },
	{ Mod1Mask|ShiftMask,    XK_Tab,          tagmon,          {.i = +1 } },
	TAGKEYS(                 XK_apostrophe,                     0)
	TAGKEYS(                 XK_1,                              1)
	TAGKEYS(                 XK_2,                              2)
	TAGKEYS(                 XK_3,                              3)
	TAGKEYS(                 XK_4,                              4)
	TAGKEYS(                 XK_5,                              5)
	TAGKEYS(                 XK_6,                              6)
	TAGKEYS(                 XK_7,                              7)
	TAGKEYS(                 XK_8,                              8)
	TAGKEYS(                 XK_9,                              9)
	{ MODKEY|ControlMask,    XK_z,           quit,             {0} },
	/* Minhas adições */
	{ MODKEY,                XK_comma,       shiftview,       {.i = -1 } },
	{ MODKEY,                XK_period,      shiftview,       {.i = +1 } },
	{ MODKEY,                XK_x,           spawn,           SHCMD("xkill > /dev/null") },
	{ MODKEY,                XK_p,           spawn,           SHCMD("killmenu -toggle") },
	{ MODKEY,                XK_Escape,      spawn,           SHCMD("ctlmenu") },
	/* Botões e teclas de função */
	{ 0,   XF86XK_AudioMute,                 spawn,           SHCMD("setmixer.sh toggle") },
	{ 0,   XF86XK_AudioRaiseVolume,          spawn,           SHCMD("setmixer.sh 5%+") },
	{ 0,   XF86XK_AudioLowerVolume,          spawn,           SHCMD("setmixer.sh 5%-") },
	{ 0,   XF86XK_MonBrightnessUp,           spawn,           SHCMD("setxbl.sh -inc 5") },
	{ 0,   XF86XK_MonBrightnessDown,         spawn,           SHCMD("setxbl.sh -dec 5") },
	{ 0,   XF86XK_Sleep,                     spawn,           SHCMD("loginctl suspend")  },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click            event mask         button          function         argument */
	{ ClkLtSymbol,      0,                 Button1,        setlayout,       {0} },
	{ ClkWinTitle,      0,                 Button1,        focusstack,      {.i = +1 } },
	{ ClkWinTitle,      0,                 Button3,        focusstack,      {.i = -1 } },
	{ ClkWinTitle,      0,                 Button2,        killclient,      {0} },
	{ ClkWinTitle,      MODKEY,            Button3,        zoom,            {0} },
	{ ClkWinTitle,      MODKEY,            Button1,        spawn,           {.v = termcmd } },
	{ ClkStatusText,    0,                 Button1,        spawn,           SHCMD("st -A 1 -n 'float' -g 80x24-0+21 -e htop") },
	{ ClkClientWin,     MODKEY,            Button1,        movemouse,       {0} },
	{ ClkClientWin,     MODKEY,            Button2,        togglefloating,  {0} },
	{ ClkClientWin,     MODKEY,            Button3,        resizemouse,     {0} },
	{ ClkTagBar,        0,                 Button1,        view,            {0} },
	{ ClkTagBar,        ControlMask,       Button1,        toggleview,      {0} },
	{ ClkTagBar,        ShiftMask,         Button1,        tag,             {0} },
	{ ClkTagBar,  ShiftMask|ControlMask,   Button1,        toggletag,       {0} },
};
