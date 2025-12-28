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

int gcd(int a, int b)
{
    int r;
    while (b != 0)
    {
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int find_e(int phi)
{
    int e;
    for (e = 2; e < phi; e++)
        if (gcd(e, phi) == 1)
            return e;
    return -1;
}

int find_d(int e, int phi)
{
    int d;
    for (d = 1; d < phi; d++)
        if ((e * d) % phi == 1)
            return d;
    return -1;
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

void encrypt(int e, int n)
{
    FILE *fin, *fout;
    char ch;
    int m, c;

    fin = fopen("input.txt", "r");
    fout = fopen("encrypt.txt", "w");

    if (fin == NULL || fout == NULL)
    {
        printf("File error\n");
        return;
    }

    while ((ch = fgetc(fin)) != EOF)
    {
        if (ch >= 'a' && ch <= 'z')
        {
            m = ch - 'a' + 1;
            c = powerMod(m, e, n);
            fprintf(fout, "%d ", c);
        }
    }

    fclose(fin);
    fclose(fout);
    printf("Encryption done check encrypt.txt\n");
}

void decrypt(int d, int n)
{
    FILE *fin, *fout;
    int c, m;

    fin = fopen("encrypt.txt", "r");
    fout = fopen("decrypt.txt", "w");

    if (fin == NULL || fout == NULL)
    {
        printf("Encryption not done\n");
        return;
    }

    while (fscanf(fin, "%d", &c) != EOF)
    {
        m = powerMod(c, d, n);
        fputc((char)(m + 'a' - 1), fout);
    }

    fclose(fin);
    fclose(fout);
    printf("Decryption done check decrypt.txt\n");
}

int main()
{
    int p, q, n, phi, e, d;
    int choice;

    printf("Enter two prime numbers p and q: ");
    scanf("%d %d", &p, &q);

    if (!isPrime(p) || !isPrime(q))
    {
        printf("Invalid prime numbers\n");
        return 0;
    }

    n = p * q;
    phi = (p - 1) * (q - 1);

    if (n <= 26)
    {
        printf("n is too small. Choose larger prime numbers.\n");
        return 0;
    }

    e = find_e(phi);
    d = find_d(e, phi);

    printf("n = %d\nphi = %d\ne = %d\nd = %d\n", n, phi, e, d);

    while (1)
    {
        printf("\n--- RSA Menu ---\n");
        printf("1. Encrypt\n");
        printf("2. Decrypt\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1)
            encrypt(e, n);
        else if (choice == 2)
            decrypt(d, n);
        else if (choice == 3)
        {
            printf("Exiting...\n");
            exit(0);
        }
        else
            printf("Invalid choice\n");
    }
}
