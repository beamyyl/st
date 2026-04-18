/* See LICENSE file for copyright and license details. */

static char *font = "Iosevka Nerd Font Mono:style=Bold:pixelsize=24:antialias=true:autohint=true";
static int borderpx = 12;

static char *shell = "/bin/sh";
char *utmp = NULL;
char *scroll = NULL;
char *stty_args = "stty raw pass8 nl -echo -iexten -cstopb 38400";

char *vtiden = "\033[?6c";

static float cwscale = 1.0;
static float chscale = 1.0;

wchar_t *worddelimiters = L" ";

static unsigned int doubleclicktimeout = 300;
static unsigned int tripleclicktimeout = 600;

int allowaltscreen = 1;

int allowwindowops = 1;

static double minlatency = 2;
static double maxlatency = 33;

static unsigned int blinktimeout = 800;

static unsigned int cursorthickness = 2;

static int bellvolume = 0;

char *termname = "st-256color";

unsigned int tabspaces = 8;

float alpha = 0.8;

static const char *colorname[] = {
    "#15161e",
    "#f7768e",
    "#9ece6a",
    "#e0af68",
    "#7aa2f7",
    "#bb9af7",
    "#7dcfff",
    "#a9b1d6",

    "#414868",
    "#ff7a93",
    "#b9f27c",
    "#ff9e64",
    "#7da6ff",
    "#bb9af7",
    "#7dcfff",
    "#c0caf5",

    [255] = 0,

    "#ffffff",
    "#1a1b26",
    "#cccccc",
    "#555555",
};

unsigned int defaultfg = 256;
unsigned int defaultbg = 257;
unsigned int defaultcs = 258;
static unsigned int defaultrcs = 259;

static unsigned int cursorshape = 2;

static unsigned int cols = 80;
static unsigned int rows = 24;

static unsigned int mouseshape = XC_xterm;
static unsigned int mousefg = 7;
static unsigned int mousebg = 0;

static unsigned int defaultattr = 11;

static uint forcemousemod = ShiftMask;

static MouseShortcut mshortcuts[] = {
    { XK_ANY_MOD,           Button2, selpaste,       {.i = 0},      1 },
    { 0,                    Button4, kscrollup,      {.i = 1} },
    { 0,                    Button5, kscrolldown,    {.i = 1} },
    { XK_ANY_MOD,           Button4, ttysend,        {.s = "\031"} },
    { XK_ANY_MOD,           Button5, ttysend,        {.s = "\005"} },
};

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
    { ShiftMask,            XK_Page_Up,     kscrollup,      {.i = -1} },
    { ShiftMask,            XK_Page_Down,   kscrolldown,    {.i = -1} },
};

static KeySym mappedkeys[] = { -1 };
static uint ignoremod = Mod2Mask|XK_SWITCH_MOD;

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
