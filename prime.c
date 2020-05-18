#include <stdio.h>


int est_premier(int n) {
    int i, flag = 0;
    for (i = 2; i <= n / 2; ++i) {
        if (n % i == 0) {
            flag = 1;
            break;
        }
    }

    if (n == 1) {
      return 0;
    }
    else {
        if (flag == 0)
           return 1;
        else
	   return 0;
    }

}



int main() {

    printf("%d",est_premier(13));
    return 0;
}
