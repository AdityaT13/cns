#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void encryptFile();
void decryptFile();

int encrypted = 0; /* encryption state */

int main()
{
    int choice;

    while (1)
    {
        printf("\n--- Rail Fence Cipher Menu ---\n");
        printf("1. Encrypt\n");
        printf("2. Decrypt\n");
        printf("3. Exit\n");
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
    char text[1000], ch;
    int r, n, i, j;
    int row, dir;

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

    printf("Enter number of rails: ");
    scanf("%d", &r);

    if (r <= 1)
    {
        printf("Invalid number of rails\n");
        fclose(fin);
        fclose(fout);
        return;
    }

    n = 0;
    while ((ch = fgetc(fin)) != EOF)
    {
        if (isalpha(ch))
            text[n++] = toupper(ch);
    }
    text[n] = '\0';

    char rail[r][1000];

    i = 0;
    while (i < r)
    {
        j = 0;
        while (j < n)
        {
            rail[i][j] = 0;
            j++;
        }
        i++;
    }

    row = 0;
    dir = 1;

    i = 0;
    while (i < n)
    {
        rail[row][i] = text[i];

        if (row == 0)
            dir = 1;
        else if (row == r - 1)
            dir = -1;

        row += dir;
        i++;
    }

    i = 0;
    while (i < r)
    {
        j = 0;
        while (j < n)
        {
            if (rail[i][j] != 0)
                fputc(rail[i][j], fout);
            j++;
        }
        i++;
    }

    fclose(fin);
    fclose(fout);

    encrypted = 1;
    printf("Encryption done\n");
}

void decryptFile()
{
    FILE *fin, *fout;
    char text[1000], ch;
    int r, n, i, j;
    int row, dir, idx;

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

    printf("Enter SAME number of rails: ");
    scanf("%d", &r);

    if (r <= 1)
    {
        printf("Invalid number of rails\n");
        fclose(fin);
        fclose(fout);
        return;
    }

    n = 0;
    while ((ch = fgetc(fin)) != EOF)
    {
        if (isalpha(ch))
            text[n++] = toupper(ch);
    }
    text[n] = '\0';

    char rail[r][1000];

    i = 0;
    while (i < r)
    {
        j = 0;
        while (j < n)
        {
            rail[i][j] = 0;
            j++;
        }
        i++;
    }

    row = 0;
    dir = 1;

    i = 0;
    while (i < n)
    {
        rail[row][i] = '*';

        if (row == 0)
            dir = 1;
        else if (row == r - 1)
            dir = -1;

        row += dir;
        i++;
    }

    idx = 0;
    i = 0;
    while (i < r)
    {
        j = 0;
        while (j < n)
        {
            if (rail[i][j] == '*')
                rail[i][j] = text[idx++];
            j++;
        }
        i++;
    }

    row = 0;
    dir = 1;

    i = 0;
    while (i < n)
    {
        fputc(rail[row][i], fout);

        if (row == 0)
            dir = 1;
        else if (row == r - 1)
            dir = -1;

        row += dir;
        i++;
    }

    fclose(fin);
    fclose(fout);
    printf("Decryption done\n");
}
