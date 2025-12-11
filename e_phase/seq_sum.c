#include <stdio.h>

/* 1 */ int main() {
/* 2 */   long long sum = 0;
/* 3 */   long long i = 0;
/* 4 */   do {
/* 5 */     sum = sum + i;
/* 6 */     i = i + 1;
/* 7 */   } while (i <= 0x10000000);
/* 8 */   printf("sum = %lld\n", sum);
/* 9 */   return 0;
/* 10*/ }

