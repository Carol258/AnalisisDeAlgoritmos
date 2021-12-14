    #include <stdio.h>
    #include <conio.h>
    #include <string.h>
     
    int validar_numero(char numero[]);
    int main()
    {
        char numero[];
        int N;
        int numerovalido;
        
        do
        {
            printf ("Ingresa un numero: ");
            scanf("%s", numero);
            validar_numero(numero);
        }while(N==0);
        
        numerovalido=atoi(numero);
        printf("\n %i", numerovalido);
        
        getch();
        return 1;
     
    int validar_numero(char numero[])
    {
        int i;
        for(i=0; i<strlen(numero); i++)
        {
            if(!(isdigit(numero[i])))
            {
                printf ("\n Ingresa solo numeros\n");
                getch();
                return 0;
            }
        }
    }
