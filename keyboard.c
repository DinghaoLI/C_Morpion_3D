#include "keyboard.h"
static struct termios oldt;
/*/restore terminal settings*/


/*@require: rien
  @assigns: rien
  @ensure : laisser le terminal normale
 */
void restore_terminal_settings(void)
{
  /*/Apply saved settings*/
    tcsetattr(0, TCSANOW, &oldt);
}


/*@require: rien
  @assigns: rien
  @ensure : lasser terminal obtenir un char dans un fois*/
void disable_terminal_return(void)
{
    struct termios newt;

    /*/save terminal settings*/
    tcgetattr(0, &oldt);
    /*/init new settings*/
    newt = oldt;
    /*/change settings*/
    newt.c_lflag &= ~(ICANON | ECHO);
    /*/apply settings*/
    tcsetattr(0, TCSANOW, &newt);

    /*/make sure settings will be restored when program ends*/
    atexit(restore_terminal_settings);
}

