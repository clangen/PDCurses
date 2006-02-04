/**************************************************************************
* This file comprises part of PDCurses. PDCurses is Public Domain software.
* You may use this code for whatever purposes you desire. This software
* is provided AS IS with NO WARRANTY whatsoever.
* Should this software be used in another application, an acknowledgement
* that PDCurses code is used would be appreciated, but is not mandatory.
*
* Any changes which you make to this software which may improve or enhance
* it, should be forwarded to the current maintainer for the benefit of 
* other users.
*
* The only restriction placed on this code is that no distribution of
* modified PDCurses code be made under the PDCurses name, by anyone
* other than the current maintainer.
* 
* See the file maintain.er for details of the current maintainer.
**************************************************************************/

#define	CURSES_LIBRARY 1
#ifdef HAVE_CONFIG_H
# include <config.h>
#endif
#include <curses.h>

/* undefine any macros for functions defined in this module */
#undef cbreak
#undef nocbreak
#undef echo
#undef noecho
#undef halfdelay
#undef intrflush
#undef keypad
#undef meta
#undef nl
#undef nonl
#undef nodelay
#undef notimeout
#undef raw
#undef noraw
#undef noqiflush
#undef qiflush
#undef timeout
#undef wtimeout
#undef typeahead

/* undefine any macros for functions called by this module if in debug mode */
#ifdef PDCDEBUG
# undef move
# undef wmove
#endif

#ifdef PDCDEBUG
const char *rcsid_inopts =
	"$Id: inopts.c,v 1.16 2006/02/04 02:33:30 wmcbrine Exp $";
#endif

/*man-start*********************************************************************

  Name:                                                        inopts

  Synopsis:
	int cbreak(void);
	int nocbreak(void);
	int echo(void);
	int noecho(void);
	int halfdelay(int tenths);
	int intrflush(WINDOW *win, bool bf);
	int keypad(WINDOW *win, bool bf);
	int meta(WINDOW *win, bool bf);
	int nl(void);
	int nonl(void);
	int nodelay(WINDOW *win, bool bf);
	int notimeout(WINDOW *win, bool bf);
	int raw(void);
	int noraw(void);
	void noqiflush(void);
	void qiflush(void);
	void timeout(int delay);
	void wtimeout(WINDOW *win, int delay);
	int typeahead(int fildes);

  X/Open Description:
	cbreak() and nocbreak() puts the terminal into and out of cbreak
	mode. In cbreak mode, characters typed by the user are immediately
	available to the program and erase/kill character processing is
	not performed.  When out of cbreak mode, the terminal driver
	will buffer characters typed until a newline or carriage return
	is typed.  Interrupt and flow control characters are unaffected
	by this mode.  Initially the terminal may or may not need be
	in cbreak mode.

	echo() and noecho() control whether characters typed by the user
	are echoed by the input routine.  Initially, input characters
	are echoed.  Subsequent calls to echo() and noecho() do not
	flush type-ahead.

	halfdelay is similar to cbreak() but allows for a specified time 
	limit to be specified (in 1/10thes of a second). This causes 
	getch() to block for that period before returning ERR if no key 
	has been received.  tenths must be between 1 and 255.

	If the intrflush() option is enabled (bf is TRUE), and an 
	interrupt is pressed on the keyboard (INTR, BREAK, or QUIT) all 
	output in the terminal driver queue will be flushed, giving the 
	effect of faster response to the interrupt but causing curses to 
	have the wrong idea of what is on the screen.  Disabling the 
	option prevents the flush.  The default for the option is 
	inherited from the terminal driver settings.  The window 
	argument is ignored.

	The keypad() function changes the keypad option of the user's 
	terminal. If enabled (bf is TRUE), the user can press a function 
	key (such as the left arrow key) and getch() will return a 
	single value that represents the KEY_LEFT function key.  (See 
	Section 11.3.3, Input Values.)  If disabled, curses will not 
	treat function keys as special keys and the program has to 
	interpret the escape sequences itself.  If the keypad is 
	enabled, the terminal keypad is turned on before input begins.

	The meta() function forces the user's terminal to return 7 or 8
	significant bits on input.  To force 8 bits to be returned,
	invoke meta() with bf as TRUE.  To force 7 bits to be returned,
	invoke meta() with bf as FALSE. The window argument is always 
	ignored, but it must still be a valid window to avoid compiler 
	errors.

	The nodelay() function controls whether wgetch() is a non-blocking
	call. If the option is enabled, and no input is ready, wgetch()
	will return ERR. If disabled, wgetch() will hang until input
	is ready.

        The nl() function enables the translation of a carriage return 
	into a newline on input. The nonl() function disables it. 
	Initially, the translation does occur.

	While interpreting an input escape sequence, wgetch sets a timer 
	while waiting for the next character.  If notimeout(win, TRUE) 
	is called, then wgetch does not set a timer.  The purpose of the 
	timeout is to differentiate between sequences received from a 
	function key and those typed by a user.

	With raw() and noraw(), the terminal in placed into or out of 
	raw mode.  Raw mode is similar to cbreak mode, in that 
	characters typed are immediately passed through to the user 
	program.  The differences are that in raw mode, the INTR, QUIT, 
	SUSP, and STOP characters are passed through without being 
	interpreted, and without generating a signal.  The behaviour of 
	the BREAK key depends on other parameters of the terminal drive 
	that are not set by curses.

	The timeout() and wtimeout() functions set blocking or 
	non-blocking reads for the specified window. "delay" is measured 
	in milliseconds. If "delay" is negative a blocking read is used. 
	If "delay" is zero then non-blocking reads are done. If no input 
	is waiting, ERR is returned immediately. If "delay" is positive, 
	the read blocks for the "delay" period. If the period expires, 
	ERR is returned.

	The curses package does the "line-breakout optimisation" by
	looking for type-ahead periodically while updating the screen.
	If input is found, the current update will be postponed until
	refresh() or doupdate() are called again.  This allows faster
	response to commands typed in advance.  Normally, the input FILE
	pointer passed to newterm(), or stdin in the case when initscr()
	was called, will be used to do this type-ahead checking.  The
	typeahead() routine specified that the file descriptor fd is to
	be used to check for type-ahead instead.  If fd is -1, then no
	type-ahead checking will be done.

  PDCurses Description:
	The meta() function is provided for portability.  By default, 8 bits
	are returned.

	notimeout(), noqiflush() and qiflush() are no-ops in PDCurses.

  X/Open Return Value:
	All functions return OK on success and ERR on error.

  X/Open Errors:
	No errors are defined for this function.

  Portability				     X/Open    BSD    SYS V
					     Dec '88
	cbreak					Y	Y	Y
	nocbreak				Y	Y	Y
	echo					Y	Y	Y
	noecho					Y	Y	Y
	halfdelay				-	-	Y
	intrflush				Y	-	Y
	keypad					Y	-	Y
	meta					-	-	Y
	nl					Y	Y	Y
	nonl					Y	Y	Y
	nodelay					Y	-	Y
	notimeout				-	-	Y
	raw					Y	Y	Y
	noraw					Y	Y	Y
	noqiflush				-	-	Y
	qiflush					-	-	Y
	timeout					-	-	Y
	wtimeout				-	-	Y
	typeahead				Y	-	Y

**man-end**********************************************************************/

int PDC_CDECL cbreak(void)
{
	PDC_LOG(("cbreak() - called\n"));

	SP->cbreak = TRUE;

	return OK;
}

int PDC_CDECL nocbreak(void)
{
	PDC_LOG(("nocbreak() - called\n"));

	SP->cbreak = FALSE;
	SP->delaytenths = 0;

	return OK;
}

int PDC_CDECL echo(void)
{
	PDC_LOG(("echo() - called\n"));

	SP->echo = TRUE;

	return OK;
}

int PDC_CDECL noecho(void)
{
	PDC_LOG(("noecho() - called\n"));

	SP->echo = FALSE;

	return OK;
}

int PDC_CDECL halfdelay(int tenths)
{
	PDC_LOG(("halfdelay() - called\n"));

	if (tenths < 1 || tenths > 255)
		return ERR;

	SP->delaytenths = tenths;

	return OK;
}

int PDC_CDECL intrflush(WINDOW *win, bool bf)
{
	int y, maxy;

	PDC_LOG(("intrflush() - called\n"));

	if (win == (WINDOW *)NULL)
		return ERR;

	maxy = win->_maxy - 1;

	for (y = 0; y <= maxy; y++)
		win->_firstch[y] = _NO_CHANGE;

	return OK;
}

int PDC_CDECL keypad(WINDOW *win, bool bf)
{
	PDC_LOG(("keypad() - called\n"));

	if (win == (WINDOW *)NULL)
		return ERR;

	win->_use_keypad = bf;

	return OK;
}

int PDC_CDECL meta(WINDOW *win, bool bf)
{
	PDC_LOG(("meta() - called\n"));

	SP->raw_inp = bf;

	return OK;
}

int PDC_CDECL nl(void)
{
	PDC_LOG(("nl() - called\n"));

	SP->autocr = TRUE;

	return OK;
}

int PDC_CDECL nonl(void)
{
	PDC_LOG(("nonl() - called\n"));

	SP->autocr = FALSE;

	return OK;
}

int PDC_CDECL nodelay(WINDOW *win, bool flag)
{
	PDC_LOG(("nodelay() - called\n"));

	if (win == (WINDOW *)NULL)
		return ERR;

	win->_nodelay = flag;

	return OK;
}

int PDC_CDECL notimeout(WINDOW *win, bool flag)
{
	PDC_LOG(("notimeout() - called\n"));

	return OK;
}

int PDC_CDECL raw(void)
{
#ifdef OS2
# ifndef EMXVIDEO
	KBDINFO KbdInfo;
# endif
#endif

	PDC_LOG(("raw() - called\n"));

#ifdef OS2
# ifndef EMXVIDEO
	KbdGetStatus(&KbdInfo, 0);
	KbdInfo.fsMask |= KEYBOARD_BINARY_MODE;
	KbdInfo.fsMask &= ~KEYBOARD_ASCII_MODE;
	KbdSetStatus(&KbdInfo, 0);
# endif
#endif

	SP->raw_inp = TRUE;
	PDC_set_ctrl_break(FALSE);      /* disallow ^BREAK on disk I/O */
/*	flushinp(); */

	return OK;
}

int PDC_CDECL noraw(void)
{
#ifdef OS2
# ifndef EMXVIDEO
	KBDINFO KbdInfo;
# endif
#endif

	PDC_LOG(("noraw() - called\n"));

#ifdef OS2
# ifndef EMXVIDEO
	KbdGetStatus(&KbdInfo, 0);
	KbdInfo.fsMask |= KEYBOARD_ASCII_MODE;
	KbdInfo.fsMask &= ~KEYBOARD_BINARY_MODE;
	KbdSetStatus(&KbdInfo, 0);
# endif
#endif

	SP->raw_inp = FALSE;
	PDC_set_ctrl_break(TRUE);

	return OK;
}

void PDC_CDECL noqiflush(void)
{
	PDC_LOG(("noqiflush() - called\n"));
}

void PDC_CDECL qiflush(void)
{
	PDC_LOG(("qiflush() - called\n"));
}

int PDC_CDECL typeahead(int fildes)
{
	PDC_LOG(("typeahead() - called\n"));

	SP->refrbrk = (fildes >= 0);

	return OK;
}

void PDC_CDECL wtimeout(WINDOW *win, int delay)
{
	PDC_LOG(("wtimeout() - called\n"));

	if (win == NULL)
		return;

	if (delay < 0)
	{
		/* This causes a blocking read on the window
		   so turn on delay mode */

		win->_nodelay = FALSE;
		win->_delayms = 0;
	}
	else if (delay == 0)
	{
		/* This causes a non-blocking read on the window
		   so turn off delay mode */

		win->_nodelay = TRUE;
		win->_delayms = 0;
	}
	else
	{
		/* This causes the read on the window to delay for the 
		   number of milliseconds. Also forces the window into 
		   non-blocking read mode */

		/*win->_nodelay = TRUE;*/
		win->_delayms = delay;
	}
}

void PDC_CDECL timeout(int delay)
{
	PDC_LOG(("timeout() - called\n"));

	wtimeout(stdscr, delay);
}
