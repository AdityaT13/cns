#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void encryptFile();
void decryptFile();

int encrypted = 0;
int modInverse(int a)
{
    int x;
    a = (a % 26 + 26) % 26;
    for (x = 1; x < 26; x++)
        if ((a * x) % 26 == 1)
            return x;
    return -1;
}

int main()
{
    int choice;

    while (1)
    {
        printf("\n--- Hill Cipher 3x3 Menu ---\n");
        printf("1. Encrypt\n2. Decrypt\n3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1)
            encryptFile();
        else if (choice == 2)
            decryptFile();
        else if (choice == 3)
            exit(0);
        else
            printf("Invalid choice\n");
    }
}

void encryptFile()
{
    FILE *fin, *fout;
    int k[3][3];
    char text[1000], ch;
    int n = 0, i;

    if (encrypted)
    {
        printf("Data already encrypted\n");
        return;
    }

    fin = fopen("plain.txt", "r");
    fout = fopen("encrypt.txt", "w");

    if (fin == NULL || fout == NULL)
    {
        printf("File error\n");
        return;
    }

    printf("Enter encryption key matrix (3x3):\n");
    for (i = 0; i < 9; i++)
        scanf("%d", &k[i / 3][i % 3]);

    while ((ch = fgetc(fin)) != EOF)
        if (isalpha(ch))
            text[n++] = toupper(ch);

    while (n % 3 != 0)
        text[n++] = 'X';

    for (i = 0; i < n; i += 3)
    {
        int a = text[i] - 'A';
        int b = text[i + 1] - 'A';
        int c = text[i + 2] - 'A';

        int r1 = (k[0][0] * a + k[0][1] * b + k[0][2] * c) % 26;
        int r2 = (k[1][0] * a + k[1][1] * b + k[1][2] * c) % 26;
        int r3 = (k[2][0] * a + k[2][1] * b + k[2][2] * c) % 26;

        fputc(r1 + 'A', fout);
        fputc(r2 + 'A', fout);
        fputc(r3 + 'A', fout);
    }

    fclose(fin);
    fclose(fout);
    encrypted = 1;

    printf("Encryption done -> encrypt.txt\n");
}

void decryptFile()
{
    FILE *fin, *fout;
    int k[3][3], cof[3][3], inv[3][3];
    char text[1000], ch;
    int n = 0, i, j;

    if (!encrypted)
    {
        printf("Encryption not done\n");
        return;
    }

    fin = fopen("encrypt.txt", "r");
    fout = fopen("decrypt.txt", "w");

    if (fin == NULL || fout == NULL)
    {
        printf("Encryption not done\n");
        return;
    }

    printf("Enter SAME encryption key matrix (3x3):\n");
    for (i = 0; i < 9; i++)
        scanf("%d", &k[i / 3][i % 3]);

    int det =
        k[0][0] * (k[1][1] * k[2][2] - k[1][2] * k[2][1]) -
        k[0][1] * (k[1][0] * k[2][2] - k[1][2] * k[2][0]) +
        k[0][2] * (k[1][0] * k[2][1] - k[1][1] * k[2][0]);

    det = (det % 26 + 26) % 26;

    int invDet = modInverse(det);
    if (invDet == -1)
    {
        printf("Key not invertible\n");
        return;
    }

    cof[0][0] = (k[1][1] * k[2][2] - k[1][2] * k[2][1]);
    cof[0][1] = -(k[1][0] * k[2][2] - k[1][2] * k[2][0]);
    cof[0][2] = (k[1][0] * k[2][1] - k[1][1] * k[2][0]);

    cof[1][0] = -(k[0][1] * k[2][2] - k[0][2] * k[2][1]);
    cof[1][1] = (k[0][0] * k[2][2] - k[0][2] * k[2][0]);
    cof[1][2] = -(k[0][0] * k[2][1] - k[0][1] * k[2][0]);

    cof[2][0] = (k[0][1] * k[1][2] - k[0][2] * k[1][1]);
    cof[2][1] = -(k[0][0] * k[1][2] - k[0][2] * k[1][0]);
    cof[2][2] = (k[0][0] * k[1][1] - k[0][1] * k[1][0]);

    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
        {
            inv[i][j] = (cof[j][i] * invDet) % 26;
            if (inv[i][j] < 0)
                inv[i][j] += 26;
        }

    while ((ch = fgetc(fin)) != EOF)
        if (isalpha(ch))
            text[n++] = toupper(ch);

    for (i = 0; i < n; i += 3)
    {
        int a = text[i] - 'A';
        int b = text[i + 1] - 'A';
        int c = text[i + 2] - 'A';

        int r1 = (inv[0][0] * a + inv[0][1] * b + inv[0][2] * c) % 26;
        int r2 = (inv[1][0] * a + inv[1][1] * b + inv[1][2] * c) % 26;
        int r3 = (inv[2][0] * a + inv[2][1] * b + inv[2][2] * c) % 26;

        fputc(r1 + 'A', fout);
        fputc(r2 + 'A', fout);
        fputc(r3 + 'A', fout);
    }

    fclose(fin);
    fclose(fout);
    printf("Decryption done -> decrypt.txt\n");
}
