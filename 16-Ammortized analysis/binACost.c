#include<stdio.h>
#include<stdlib.h>

unsigned  dec2bin(unsigned int k) {
    return (k == 0 || k == 1 ? k : ((k % 2) + 10 * dec2bin(k / 2)));
}

int count1s(unsigned int n) {
    int count = 0;
    n = dec2bin(n);
    while(n) {
        if(n % 10 == 1)
            count++;
        n /= 10;
    }

    return count;
}

int countCost(unsigned int a, unsigned int b) {
    a = dec2bin(a);
    b = dec2bin(b);

    int cost = 0;
    while(b) {
        if(a % 10 != b % 10)
            cost++;
        a /= 10;
        b /= 10;
    }

    return cost;
}

int main() {
    int n;
    printf("Enter the number of digits in the binary number: ");
    scanf("%d", &n);

    int t_i = 0;
    int c_i = 0;
    int c_i_prev = 0;

    printf("\nSteps\tInteger\t\tt_i\tc_i\ta_i\n");

    for(int i = 0; i < (1 << n); i++) {
        printf("%d\t", i);
        printf("%0*d\t\t", n, dec2bin(i));

        int prev_num = i == 0 ? 0 : i - 1;
        t_i = countCost(prev_num, i);
        printf("%d\t", t_i);

        c_i = count1s(i);
        printf("%d\t", c_i);

        int a_i = t_i + c_i - c_i_prev;
        printf("%d\t\n", a_i);

        c_i_prev = c_i;
    }

    return 0;
}