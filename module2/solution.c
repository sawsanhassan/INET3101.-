
#include <stdio.h>

void to_base_n(unsigned int num, int base)
{
    char digits[] = "0123456789!@#$%^";

    if (num >= base)
    {
        to_base_n(num / base, base);
    }

    printf("%c", digits[num % base]);
}

int main(void)
{
    unsigned int num;
    int base;

    printf("Enter a number: ");
    scanf("%u", &num);

    printf("Enter a base (2-16): ");
    scanf("%d", &base);

    if (base < 2 || base > 16)
    {
        printf("Error: Invalid base.\n");
    }
    else
    {
        printf("Converted number: ");

        if (base == 8)
        {
            printf("0");
        }

        if (base == 16)
        {
            printf("0x");
        }

        to_base_n(num, base);
        printf("\n");
    }

    return 0;
}
