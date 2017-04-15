#ifndef KEYBOARD_H_INCLUDED
#define KEYBOARD_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>



/*/restore terminal settings*/
void restore_terminal_settings(void);
/*/make terminal read 1 char at a time*/
void disable_terminal_return(void);




#endif /*/ KEYBOARD_H_INCLUDED*/
