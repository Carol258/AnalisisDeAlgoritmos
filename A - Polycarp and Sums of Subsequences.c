    #include <stdio.h>
    #include <stdlib.h>
    #include <time.h>
     
    int main() {
        int array[3]; 
        int a, b;
        int sum;
     
        srand (time(NULL));
        for (a=1; a<4; a++) {
            array[a] = rand()%10;
            sum = array[a] + a;
            array[b] = sum; 
            printf("%d", array[b]);
        }
        return 0;
    }
