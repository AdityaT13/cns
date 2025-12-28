#include <stdio.h>
#include <stdlib.h>

int isPrime(int x)
{
    int i;
    if (x <= 1)
        return 0;
    for (i = 2; i <= x / 2; i++)
        if (x % i == 0)
            return 0;
    return 1;
}

int powerMod(int base, int exp, int mod)
{
    int result = 1;
    while (exp > 0)
    {
        result = (result * base) % mod;
        exp--;
    }
    return result;
}

int inverse(int a, int p)
{
    int i;
    for (i = 1; i < p; i++)
        if ((a * i) % p == 1)
            return i;
    return -1;
}

void encrypt(int e1, int e2, int p, int *c1)
{
    FILE *fin, *fout;
    char ch;
    int m, c2;
    int r, k;

    fin = fopen("input.txt", "r");
    fout = fopen("encrypt.txt", "w");

    if (fin == NULL || fout == NULL)
    {
        printf("File error\n");
        return;
    }

    printf("Enter random integer r: ");
    scanf("%d", &r);

    *c1 = powerMod(e1, r, p);
    k = powerMod(e2, r, p);

    while ((ch = fgetc(fin)) != EOF)
    {
        if (ch >= 'a' && ch <= 'z')
        {
            m = ch - 'a' + 1;
            c2 = (m * k) % p;
            fprintf(fout, "%d ", c2);
        }
    }

    fclose(fin);
    fclose(fout);
    printf("Encryption done -> encrypt.txt\n");
}

void decrypt(int c1, int d, int p)
{
    FILE *fin, *fout;
    int c2, m;
    int k, k_inv;

    fin = fopen("encrypt.txt", "r");
    fout = fopen("decrypt.txt", "w");

    if (fin == NULL || fout == NULL)
    {
        printf("Encryption not done\n");
        return;
    }

    k = powerMod(c1, d, p);
    k_inv = inverse(k, p);

    while (fscanf(fin, "%d", &c2) != EOF)
    {
        m = (c2 * k_inv) % p;
        fputc((char)(m + 'a' - 1), fout);
    }

    fclose(fin);
    fclose(fout);
    printf("Decryption done -> decrypt.txt\n");
}

int main()
{
    int p, d, e1, e2;
    int c1;
    int choice;

    printf("Enter prime number p (p > 26): ");
    scanf("%d", &p);

    if (!isPrime(p) || p <= 26)
    {
        printf("Invalid prime number\n");
        return 0;
    }

    printf("Enter private key d: ");
    scanf("%d", &d);

    printf("Enter generator e1: ");
    scanf("%d", &e1);

    e2 = powerMod(e1, d, p);

    printf("Public key (e1, e2, p) = (%d, %d, %d)\n", e1, e2, p);
    printf("Private key d = %d\n", d);

    while (1)
    {
        printf("\n--- Elgamal Menu ---\n");
        printf("1. Encrypt\n");
        printf("2. Decrypt\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1)
            encrypt(e1, e2, p, &c1);
        else if (choice == 2)
            decrypt(c1, d, p);
        else if (choice == 3)
        {
            printf("Exiting...\n");
            exit(0);
        }
        else
            printf("Invalid choice\n");
    }
}
