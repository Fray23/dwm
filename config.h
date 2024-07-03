/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int gappx     = 10;
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int rmaster            = 1;        /* 1 means master-area is initially on the right */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
// static const char *fonts[]          = { "JetBrainsMono NF:bold:size=13", "Symbols NF:size=13" };
static const char *fonts[]          = { "JetBrainsMono NF:bold:size=12", "Symbols NF:size=12" };
static const char col_gray1[]       = "#1d2021";   // bar background
static const char col_gray2[]       = "#232A2E";   // границы неактивных оккан
static const char col_gray3[]       = "#FAF3DD";   // неактивные теги // #bbbbbb
static const char col_fg1[]         = "#FAF3DD";   // активные теги и титул
static const char col_accent[]      = "#ebdbb2";   // границы активного окна

// #5BC0EB #FDE74C #9BC53D #C3423F #404E4D #232A2E
// #1C3144 #596F62 #7EA16B #C3D898 #9A775B #70161E
// #F05D5E #0F7173 #E7ECEF #878B91 #272932 #D8A47F
// #FFA69E #FAF3DD #B8F2E6 #AED9E0 #869FA9 #5E6472
// #FF0000 #ebdbb2 #282828 #1d2021 #FFFFFF

static const char *colors[][3]      = {
	/*               fg          bg           border   */
	[SchemeNorm] = { col_gray3,  col_gray1,   col_gray2  },
	[SchemeSel]  = { col_gray1,  col_fg1,     col_accent },

        // bar without title and col_fg1 <-> col_gray1
        // [SchemeNorm] = { col_gray3,  col_gray1,   col_gray2 },
	// [SchemeSel]  = { col_fg1,  col_gray1,     col_accent  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
// static const char *tags[] = { "󰈹", "󰕷", "󰅱", "󰈄", "󰓓", "󰇏", "󰊠", "󰒃", "" };
// static const char *tags[] = { "一", "二", "三", "四", "五", "六", "七", "八", "九" };
// static const char *tags[] = { "I", "II", "III", "IV", "V", "VI", "VII", "IX", "X" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5;  /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "   ",      tile },    /* first entry is default */
	{ "  ",       NULL },    /* no layout function means floating behavior */
	{ " [M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask

#define TAGKEYS(KEY,TAG)		\
	&((Keychord){1, {{MODKEY, KEY}},				   view,           {.ui = 1 << TAG} }), \
		&((Keychord){1, {{MODKEY|ControlMask, KEY}},		   toggleview,     {.ui = 1 << TAG} }), \
		&((Keychord){1, {{MODKEY|ShiftMask, KEY}},		   tag,            {.ui = 1 << TAG} }), \
		&((Keychord){1, {{MODKEY|ControlMask|ShiftMask, KEY}},	   toggletag,      {.ui = 1 << TAG} }),

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *rofi[]           = { "/home/fs/bin/rofi", NULL };
static const char *termcmd[]        = { "kitty", NULL };
static const char *change_layout[]  = { "/home/fs/bin/change_layout.sh", NULL };
static const char *screenshot[]     = { "flameshot", "gui", NULL };
static const char *return_monitor[] = { "/home/fs/bin/dpms", NULL };
/* volume commands */
static const char *uvol[]           = { "pactl", "set-sink-volume", "0", "+5%", NULL };
static const char *dvol[]           = { "pactl", "set-sink-volume", "0", "-5%", NULL };
static const char *mvol[]           = { "pactl", "set-sink-mute", "0", "toggle", NULL };
/* moc */
static const char *mocseekp[]       = { "mocp", "--seek", "+5", NULL };
static const char *mocseekl[]       = { "mocp", "--seek", "-5", NULL };
static const char *mocppause[]      = { "mocp", "--toggle-pause", NULL };
static const char *mocnext[]        = { "mocp", "--next", NULL };
static const char *mocprevious[]    = { "mocp", "--previous", NULL };
/* brightness commands */
static const char *ubright[]        = { "xbacklight", "-inc", "10", NULL };
static const char *dbright[]        = { "xbacklight", "-dec", "10", NULL };

/* apps */
static const char *firefox[]        = { "/home/fs/bin/firefox_profiles.sh", NULL };
static const char *emacs[]          = { "emacsclient", "-c", NULL };
static const char *emacs_docs[]     = { "emacsclient", "-c", "~/Documents/", NULL };
static const char *emacs_pictures[] = { "emacsclient", "-c", "~/Pictures/", NULL };
static const char *emacs_video[]    = { "emacsclient", "-c", "~/Videos/", NULL };
static const char *emacs_mnt[]      = { "emacsclient", "-c", "~/mnt/", NULL };

static const char *filemanager[]    = { "pcmanfm", NULL };

/* Movestack Patch */
#include "movestack.c"

static Keychord *keychords[] = {
        &((Keychord){1, {{MODKEY|ShiftMask, XK_j}},	                   movestack,     {.i = +1 } }),
        &((Keychord){1, {{MODKEY|ShiftMask, XK_k}},	                   movestack,     {.i = -1 } }),

	&((Keychord){1, {{MODKEY, XK_Control_L}},			   spawn,         {.v = change_layout } }),
	&((Keychord){1, {{MODKEY, XK_Control_R}},			   spawn,         {.v = change_layout } }),
	&((Keychord){1, {{MODKEY, XK_space}},    			   spawn,         {.v = change_layout } }),

	&((Keychord){1, {{MODKEY, XK_p}},       			   spawn,         {.v = screenshot } }),
	&((Keychord){1, {{MODKEY|ShiftMask, XK_m}},       		   spawn,         {.v = return_monitor } }),
	// monitor
	&((Keychord){1, {{0, 0x1008FF02}},       			   spawn,         {.v = ubright } }),
	&((Keychord){1, {{0, 0x1008FF03}},       			   spawn,         {.v = dbright } }),
	// vol
	&((Keychord){1, {{0, 0x1008FF13}},       			   spawn,         {.v = uvol } }),
	&((Keychord){1, {{0, 0x1008FF11}},       			   spawn,         {.v = dvol } }),
	&((Keychord){1, {{0, 0x1008FF12}},       			   spawn,         {.v = mvol } }),
	// moc

        &((Keychord){1, {{Mod4Mask, XK_equal}},       			   spawn,         {.v = mocseekp } }),
	&((Keychord){1, {{Mod4Mask, XK_minus}},       			   spawn,         {.v = mocseekl } }),
	&((Keychord){1, {{Mod4Mask, XK_space}},       			   spawn,         {.v = mocppause } }),
	&((Keychord){1, {{Mod4Mask, XK_comma}},       			   spawn,         {.v = mocprevious } }),
	&((Keychord){1, {{Mod4Mask, XK_period}},       			   spawn,         {.v = mocnext } }),

        // scripts

	// // apps
	&((Keychord){2, {{MODKEY, XK_e}, {0, XK_e}},       		   spawn,         {.v = emacs } }),
	&((Keychord){2, {{MODKEY, XK_e}, {0, XK_d}},       		   spawn,         {.v = emacs_docs} }),
	&((Keychord){2, {{MODKEY, XK_e}, {0, XK_p}},       		   spawn,         {.v = filemanager } }),
	&((Keychord){2, {{MODKEY, XK_e}, {0, XK_i}},       		   spawn,         {.v = emacs_pictures } }),
	&((Keychord){2, {{MODKEY, XK_e}, {0, XK_m}},       		   spawn,         {.v = emacs_mnt } }),
	&((Keychord){2, {{MODKEY, XK_e}, {0, XK_v}},       		   spawn,         {.v = emacs_video } }),

	&((Keychord){1, {{MODKEY, XK_Return}},       			   spawn,         {.v = termcmd } }),

	&((Keychord){2, {{MODKEY, XK_r}, {0, XK_i}},       	           spawn,         {.v = rofi } }),
	&((Keychord){2, {{MODKEY, XK_r}, {0, XK_u}},       	           spawn,         {.v = firefox } }),

	// // legacy
	&((Keychord){1, {{MODKEY, XK_b}},       			   togglebar,     {0} }),
	&((Keychord){1, {{MODKEY, XK_j}},       			   focusstackvis, {.i = +1 } }),
	&((Keychord){1, {{MODKEY, XK_k}},       			   focusstackvis, {.i = -1 } }),
	&((Keychord){1, {{MODKEY, XK_i}},       			   incnmaster,    {.i = +1 } }),
	&((Keychord){1, {{MODKEY, XK_d}},       			   incnmaster,    {.i = -1 } }),
	&((Keychord){1, {{MODKEY, XK_h}},       			   setmfact,      {.f = +0.05} }),
	&((Keychord){1, {{MODKEY, XK_l}},       			   setmfact,      {.f = -0.05} }),
	&((Keychord){1, {{MODKEY, XK_Return}},       			   zoom,          {0} }),
	&((Keychord){1, {{MODKEY, XK_Tab}},       			   view,          {0} }),
	&((Keychord){1, {{MODKEY, XK_q}},       			   killclient,    {0} }),
	&((Keychord){1, {{MODKEY, XK_t}},       			   setlayout,     {.v = &layouts[0]} } ),
	&((Keychord){1, {{MODKEY, XK_f}},       			   setlayout,     {.v = &layouts[1]} } ),
	&((Keychord){1, {{MODKEY, XK_m}},       			   setlayout,     {.v = &layouts[2]} } ),
	&((Keychord){1, {{MODKEY, XK_0}},       			   view,          {.ui = ~0 } }),
	&((Keychord){1, {{MODKEY, XK_0}},       			   tag,           {.ui = ~0 } }),
	&((Keychord){1, {{MODKEY, XK_comma}},       			   focusmon,      {.i = -1 } }),
	&((Keychord){1, {{MODKEY, XK_period}},       			   focusmon,      {.i = +1 } }),
	&((Keychord){1, {{MODKEY|ShiftMask, XK_comma}},       		   tagmon,        {.i = -1 } }),
	&((Keychord){1, {{MODKEY|ShiftMask, XK_period}},       		   tagmon,        {.i = +1 } }),

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	&((Keychord){1, {{MODKEY|ShiftMask, XK_q}},       		     quit,       {0} }),
};


/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */

	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	// { ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
