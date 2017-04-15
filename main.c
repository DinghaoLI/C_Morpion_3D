#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "keyboard.h"
#include "menu.h"
#include "player.h"
#include "seisme.h"

int main()
{

    int key;
    showInfo();
    key=start();
    if(key==1)
    {
        dessus();
    }
    else if(key==2)
    {
        variante3D();
    }
    else if (key==3)
    {
        dessus_seisme();
    }
    else if (key==4)
    {
        Morpion3D_seisme();
    }



    return 1;
}
