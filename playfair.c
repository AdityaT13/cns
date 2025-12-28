#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char matrix[5][5];
int encrypted = 0; /* encryption state for current run */

int validateKey(char key[])
{
    int used[26] = {0};
    int i;
    char ch;

    if (strlen(key) == 0)
        return 0;

    for (i = 0; key[i]; i++)
    {
        if (!isalpha(key[i]))
            return 0;

        ch = toupper(key[i]);
        if (ch == 'J')
            ch = 'I';

        if (used[ch - 'A'])
            return 0;

        used[ch - 'A'] = 1;
    }
    return 1;
}

void createMatrix(char key[])
{
    int used[26] = {0};
    int i, k = 0;
    char ch;

    used['J' - 'A'] = 1;

    for (i = 0; key[i]; i++)
    {
        ch = toupper(key[i]);
        if (ch == 'J')
            ch = 'I';

        if (!used[ch - 'A'])
        {
            matrix[k / 5][k % 5] = ch;
            used[ch - 'A'] = 1;
            k++;
        }
    }

    for (ch = 'A'; ch <= 'Z'; ch++)
    {
        if (!used[ch - 'A'])
        {
            matrix[k / 5][k % 5] = ch;
            used[ch - 'A'] = 1;
            k++;
        }
    }
}

void displayMatrix()
{
    int i, j;
    printf("\nPlayfair 5x5 Matrix:\n");
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
            printf("%c ", matrix[i][j]);
        printf("\n");
    }
}

void findPos(char ch, int *r, int *c)
{
    int i, j;
    if (ch == 'J')
        ch = 'I';

    for (i = 0; i < 5; i++)
        for (j = 0; j < 5; j++)
            if (matrix[i][j] == ch)
            {
                *r = i;
                *c = j;
                return;
            }
}

void encryptFile()
{
    FILE *fin, *fout;
    char key[100], a, b;
    int r1, c1, r2, c2;

    fin = fopen("plain.txt", "r");
    fout = fopen("encrypt.txt", "w");

    if (fin == NULL || fout == NULL)
    {
        printf("File error\n");
        return;
    }

    printf("Enter KEY: ");
    scanf("%s", key);

    if (!validateKey(key))
    {
        printf("Key must contain only unique alphabets\n");
        fclose(fin);
        fclose(fout);
        return;
    }

    createMatrix(key);
    displayMatrix();

    while ((a = fgetc(fin)) != EOF)
    {
        if (!isalpha(a))
            continue;

        b = fgetc(fin);
        while (b != EOF && !isalpha(b))
            b = fgetc(fin);

        if (b == EOF || toupper(a) == toupper(b))
            b = 'X';

        a = toupper(a);
        b = toupper(b);

        findPos(a, &r1, &c1);
        findPos(b, &r2, &c2);

        if (r1 == r2)
        {
            fputc(matrix[r1][(c1 + 1) % 5], fout);
            fputc(matrix[r2][(c2 + 1) % 5], fout);
        }
        else if (c1 == c2)
        {
            fputc(matrix[(r1 + 1) % 5][c1], fout);
            fputc(matrix[(r2 + 1) % 5][c2], fout);
        }
        else
        {
            fputc(matrix[r1][c2], fout);
            fputc(matrix[r2][c1], fout);
        }
    }

    fclose(fin);
    fclose(fout);

    encrypted = 1;
    printf("Encryption done\n");
}

void decryptFile()
{
    FILE *fin, *fout;
    char key[100], a, b;
    int r1, c1, r2, c2;

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

    printf("Enter SAME KEY: ");
    scanf("%s", key);

    if (!validateKey(key))
    {
        printf("Key must contain only unique alphabets\n");
        fclose(fin);
        fclose(fout);
        return;
    }

    createMatrix(key);
    displayMatrix();

    while ((a = fgetc(fin)) != EOF)
    {
        if (!isalpha(a))
            continue;

        b = fgetc(fin);
        while (b != EOF && !isalpha(b))
            b = fgetc(fin);

        if (b == EOF)
            break;

        a = toupper(a);
        b = toupper(b);

        findPos(a, &r1, &c1);
        findPos(b, &r2, &c2);

        if (r1 == r2)
        {
            fputc(matrix[r1][(c1 + 4) % 5], fout);
            fputc(matrix[r2][(c2 + 4) % 5], fout);
        }
        else if (c1 == c2)
        {
            fputc(matrix[(r1 + 4) % 5][c1], fout);
            fputc(matrix[(r2 + 4) % 5][c2], fout);
        }
        else
        {
            fputc(matrix[r1][c2], fout);
            fputc(matrix[r2][c1], fout);
        }
    }

    fclose(fin);
    fclose(fout);
    printf("Decryption done\n");
}

int main()
{
    int choice;

    while (1)
    {
        printf("\n--- Playfair Cipher Menu ---\n");
        printf("1. Encrypt\n2. Decrypt\n3. Exit\nEnter choice: ");
        scanf("%d", &choice);

        if (choice == 1)
            encryptFile();
        else if (choice == 2)
            decryptFile();
        else if (choice == 3)
        {
            printf("Exiting...\n");
            exit(0);
        }
        else
            printf("Invalid choice\n");
    }
}
