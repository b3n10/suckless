/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int focusonwheel       = 0;
static const char *fonts[]          = { "xos4 Terminus:pixelsize=14:antialias=true:autohint=true" };
static const char dmenufont[]       = "xos4 Terminus:pixelsize=14:antialias=true:autohint=true";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "|||",      col },
};

/* key definitions */
#define MODKEY Mod1Mask
#define SUPERKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ SUPERKEY,                     KEY,      view,           {.ui = 1 << TAG} }, \
	{ SUPERKEY|ControlMask,         KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ SUPERKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ SUPERKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

/* custom commands */
static const char *rangercmd[]  = { "st", "-e", "ranger", NULL };
static const char *htopcmd[]  = { "st", "-e", "htop", NULL };
static const char *browser[]  = { "xdg-open", "about:newtab", NULL };
static const char *slockcmd[]  = { "slock", NULL };
static const char *muttcmd[]  = { "st", "-e", "mutt", NULL };
static const char *ttrvcmd[]  = { "st", "-e", "ttrv", NULL };
static const char *subscmd[]  = { "bash", "/home/ben/.local/bin/ytsubs/ytsubs", NULL };
static const char *clipmenucmd[]  = { "clipmenu", NULL };

static Key keys[] = {

	/* modifier                     key        function        argument */

    /* custom keys */
    { SUPERKEY|ControlMask,         XK_m,      spawn,          {.v = rangercmd } },
    { SUPERKEY|ControlMask,         XK_h,      spawn,          {.v = htopcmd } },
    { SUPERKEY|ControlMask,         XK_b,      spawn,          {.v = browser } },
    { SUPERKEY|ControlMask,         XK_l,      spawn,          {.v = slockcmd } },
    { SUPERKEY|ControlMask,         XK_e,      spawn,          {.v = muttcmd } },
    { SUPERKEY|ControlMask,         XK_t,      spawn,          {.v = ttrvcmd } },
    { SUPERKEY|ControlMask,         XK_s,      spawn,          {.v = subscmd } },
    { MODKEY|ControlMask,           XK_h,      spawn,          {.v = clipmenucmd } },

	{ SUPERKEY,                     XK_p,      spawn,          {.v = dmenucmd } },
	{ SUPERKEY|ControlMask,         XK_Return, spawn,          {.v = termcmd } },
	{ SUPERKEY,                     XK_b,      togglebar,      {0} },
	{ SUPERKEY,                     XK_j,      focusstack,     {.i = +1 } },
	{ SUPERKEY,                     XK_k,      focusstack,     {.i = -1 } },
	{ SUPERKEY,                     XK_i,      incnmaster,     {.i = +1 } },
	{ SUPERKEY,                     XK_d,      incnmaster,     {.i = -1 } },
	{ SUPERKEY,                     XK_h,      setmfact,       {.f = -0.05} },
	{ SUPERKEY,                     XK_l,      setmfact,       {.f = +0.05} },

	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },

	{ SUPERKEY,                     XK_Return, zoom,           {0} },
	{ SUPERKEY,                     XK_Tab,    view,           {0} },
	{ SUPERKEY|ShiftMask,           XK_c,      killclient,     {0} },
	{ SUPERKEY,                     XK_t,      setlayout,      {.v = &layouts[0]} },
	{ SUPERKEY,                     XK_f,      setlayout,      {.v = &layouts[1]} },
	{ SUPERKEY,                     XK_m,      setlayout,      {.v = &layouts[2]} },
	{ SUPERKEY,                     XK_c,      setlayout,      {.v = &layouts[3]} },
	{ SUPERKEY,                     XK_space,  setlayout,      {0} },
	{ SUPERKEY|ShiftMask,           XK_space,  togglefloating, {0} },
    /*
	{ SUPERKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ SUPERKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
    */
	{ SUPERKEY,                     XK_comma,  focusmon,       {.i = -1 } },
	{ SUPERKEY,                     XK_period, focusmon,       {.i = +1 } },
	{ SUPERKEY|ShiftMask,           XK_comma,  tagmon,         {.i = -1 } },
	{ SUPERKEY|ShiftMask,           XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ SUPERKEY|ShiftMask,           XK_q,      quit,           {0} },
	{ MODKEY,                       XK_Tab,     focusstack,     {.i = +1 } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

