/* See LICENSE file for copyright and license details. */

/*
 * appearance
 *
 * font: see http://freedesktop.org/software/fontconfig/fontconfig-user.html
 */
static char *font = "Iosevka Nerd Font Mono:style=Bold:pixelsize=24:antialias=true:autohint=true";
static int borderpx = 12;

/*
 * What program is execed by st depends of these precedence rules:
 * 1: program passed with -e
 * 2: scroll and/or utmp
 * 3: SHELL environment variable
 * 4: value of shell in /etc/passwd
 * 5: value of shell in config.h
 */
static char *shell = "/bin/sh";
char *utmp = NULL;
/* scroll program: to enable use a string like "scroll" */
char *scroll = NULL;
char *stty_args = "stty raw pass8 nl -echo -iexten -cstopb 38400";

/* identification sequence returned in DA and DECID */
char *vtiden = "\033[?6c";

/* Kerning / character bounding-box multipliers */
static float cwscale = 1.0;
static float chscale = 1.0;

/*
 * word delimiter string
 */
wchar_t *worddelimiters = L" ";

/* selection timeouts (in milliseconds) */
static unsigned int doubleclicktimeout = 300;
static unsigned int tripleclicktimeout = 600;

/* alt screens */
int allowaltscreen = 1;

/* allow certain non-interactive (insecure) window operations */
int allowwindowops = 1;

/* draw latency range in ms */
static double minlatency = 2;
static double maxlatency = 33;

/* blinking timeout */
static unsigned int blinktimeout = 800;

/* thickness of underline and bar cursors */
static unsigned int cursorthickness = 2;

/* bell volume */
static int bellvolume = 0;

/* default TERM value */
char *termname = "st-256color";

/* spaces per tab */
unsigned int tabspaces = 8;

/* Background Opacity (Requires Alpha Patch) */
float alpha = 0.8;

/* Terminal colors (TokyoNight Palette) */
static const char *colorname[] = {
    /* 8 normal colors */
    "#15161e", /* 0: Black */
    "#f7768e", /* 1: Red */
    "#9ece6a", /* 2: Green */
    "#e0af68", /* 3: Yellow/Orange */
    "#7aa2f7", /* 4: Blue */
    "#bb9af7", /* 5: Magenta */
    "#7dcfff", /* 6: Cyan */
    "#a9b1d6", /* 7: White (TokyoNight Blue-Grey White) */

    /* 8 bright colors */
    "#414868", /* 8: Bright Black */
    "#ff7a93", /* 9: Bright Red */
    "#b9f27c", /* 10: Bright Green */
    "#ff9e64", /* 11: Bright Yellow */
    "#7da6ff", /* 12: Bright Blue */
    "#bb9af7", /* 13: Bright Magenta */
    "#7dcfff", /* 14: Bright Cyan */
    "#c0caf5", /* 15: Bright White */

    [255] = 0,

    /* Custom high-contrast indices */
    "#ffffff", /* 256: Pure White (Primary Foreground) */
    "#1a1b26", /* 257: TokyoNight Storm (Primary Background) */
    "#cccccc", /* 258: Cursor */
    "#555555", /* 259: Reverse Cursor */
};

/*
 * Default colors (colorname index)
 */
unsigned int defaultfg = 256; /* Forced to Pure White */
unsigned int defaultbg = 257; /* Forced to TokyoNight Storm */
unsigned int defaultcs = 258;
static unsigned int defaultrcs = 259;

/* Default shape of cursor: 2 (Block) */
static unsigned int cursorshape = 2;

/* Default columns and rows numbers */
static unsigned int cols = 80;
static unsigned int rows = 24;

/* Default colour and shape of the mouse cursor */
static unsigned int mouseshape = XC_xterm;
static unsigned int mousefg = 7;
static unsigned int mousebg = 0;

/* Color for font attribute mismatches */
static unsigned int defaultattr = 11;

/* Force mouse select/shortcuts */
static uint forcemousemod = ShiftMask;

/* Internal mouse shortcuts */
static MouseShortcut mshortcuts[] = {
    { XK_ANY_MOD,           Button2, selpaste,       {.i = 0},      1 },
    { ShiftMask,            Button4, ttysend,        {.s = "\033[5;2~"} },
    { XK_ANY_MOD,           Button4, ttysend,        {.s = "\031"} },
    { ShiftMask,            Button5, ttysend,        {.s = "\033[6;2~"} },
    { XK_ANY_MOD,           Button5, ttysend,        {.s = "\005"} },
};

/* Internal keyboard shortcuts */
#define MODKEY Mod1Mask
#define TERMMOD (ControlMask|ShiftMask)

static Shortcut shortcuts[] = {
    { XK_ANY_MOD,           XK_Break,       sendbreak,      {.i =  0} },
    { ControlMask,          XK_Print,       toggleprinter,  {.i =  0} },
    { ShiftMask,            XK_Print,       printscreen,    {.i =  0} },
    { XK_ANY_MOD,           XK_Print,       printsel,       {.i =  0} },
    { ControlMask,          XK_minus,       zoom,           {.f = -1} },
    { ControlMask,          XK_equal,       zoom,           {.f = +1} },
    { ControlMask,          XK_0,           zoomreset,      {.f =  0} },
    { TERMMOD,              XK_C,           clipcopy,       {.i =  0} },
    { TERMMOD,              XK_V,           clippaste,      {.i =  0} },
    { TERMMOD,              XK_Y,           selpaste,       {.i =  0} },
    { ShiftMask,            XK_Insert,      selpaste,       {.i =  0} },
    { TERMMOD,              XK_Num_Lock,    numlock,        {.i =  0} },
};

static KeySym mappedkeys[] = { -1 };
static uint ignoremod = Mod2Mask|XK_SWITCH_MOD;

/*
 * The standard st key array - kept intact for functionality
 */
static Key key[] = {
    { XK_KP_Home,       ShiftMask,      "\033[2J",       0,   -1},
    { XK_KP_Home,       ShiftMask,      "\033[1;2H",     0,   +1},
    { XK_KP_Home,       XK_ANY_MOD,     "\033[H",        0,   -1},
    { XK_KP_Home,       XK_ANY_MOD,     "\033[1~",       0,   +1},
    { XK_Up,            XK_ANY_MOD,     "\033[A",        0,    0},
    { XK_Down,          XK_ANY_MOD,     "\033[B",        0,    0},
    { XK_Left,          XK_ANY_MOD,     "\033[D",        0,    0},
    { XK_Right,         XK_ANY_MOD,     "\033[C",        0,    0},
    { XK_KP_Up,         XK_ANY_MOD,     "\033[A",        0,    0},
    { XK_KP_Down,       XK_ANY_MOD,     "\033[B",        0,    0},
    { XK_Return,        Mod1Mask,       "\033\r",        0,    0},
    { XK_Return,        XK_ANY_MOD,     "\r",            0,    0},
    { XK_Insert,        ShiftMask,      "\033[4l",      -1,    0},
    { XK_Insert,        ShiftMask,      "\033[2;2~",    +1,    0},
    { XK_BackSpace,     XK_NO_MOD,      "\177",          0,    0},
    { XK_Home,          XK_ANY_MOD,     "\033[H",        0,    0},
    { XK_End,           XK_ANY_MOD,     "\033[4~",       0,    0},
    { XK_Prior,         XK_ANY_MOD,     "\033[5~",       0,    0},
    { XK_Next,          XK_ANY_MOD,     "\033[6~",       0,    0},
};

static uint selmasks[] = {
    [SEL_RECTANGULAR] = Mod1Mask,
};

static char ascii_printable[] =
    " !\"#$%&'()*+,-./0123456789:;<=>?"
    "@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_"
    "`abcdefghijklmnopqrstuvwxyz{|}~";
