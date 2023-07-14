#include <stdio.h>
#include <stdlib.h>

int main()
{
    int letra=0;
    do
    {
        printf("Presione una tecla   ");
        letra=getch();
        printf("Tecla :  [%c] ASCII : %i          [ESC] para salir \n",letra,letra);
    }while(letra!=27);
    printf("Usted presiono [ESC] %c : %i          SALIENDO \n",letra,letra);
    system("pause");

    return 0;
}
