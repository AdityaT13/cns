#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void encryptFile();
void decryptFile();

int main()
{
    int ch;

    // remove("status.txt");   /* RESET ENCRYPTION STATE */

    while (1)
    {
        printf("\n1. Encrypt\n2. Decrypt\n3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &ch);

        if (ch == 1)
            encryptFile();
        else if (ch == 2)
            decryptFile();
        else if (ch == 3)
            exit(0);
        else
            printf("Invalid choice\n");
    }
}

void encryptFile()
{
    FILE *fin, *fout, *fstatus;
    char key[50], ch;
    int i, klen, shift;

    fin = fopen("plain.txt", "r");
    if (fin == NULL)
    {
        printf("File error\n");
        return;
    }

    printf("Enter KEY: ");
    scanf("%s", key);

    klen = strlen(key);
    if (klen == 0)
    {
        printf("Invalid key value\n");
        fclose(fin);
        return;
    }

    for (i = 0; i < klen; i++)
    {
        if (key[i] >= 'a' && key[i] <= 'z')
            key[i] = key[i] - 32;

        if (key[i] < 'A' || key[i] > 'Z')
        {
            printf("Invalid key value\n");
            fclose(fin);
            return;
        }
    }

    fout = fopen("encrypt.txt", "w");
    if (fout == NULL)
    {
        printf("File error\n");
        fclose(fin);
        return;
    }

    i = 0;
    while ((ch = fgetc(fin)) != EOF)
    {
        if (ch >= 'A' && ch <= 'Z')
        {
            shift = key[i % klen] - 'A';
            ch = (ch - 'A' + shift) % 26 + 'A';
            i++;
        }
        else if (ch >= 'a' && ch <= 'z')
        {
            shift = key[i % klen] - 'A';
            ch = (ch - 'a' + shift) % 26 + 'a';
            i++;
        }
        fputc(ch, fout);
    }

    fclose(fin);
    fclose(fout);

    //  fstatus = fopen("status.txt", "w");
    // fclose(fstatus);

    printf("Encryption done\n");
}

void decryptFile()
{
    FILE *fin, *fout, *fstatus;
    char key[50], ch;
    int i, klen, shift;

    //  fstatus = fopen("status.txt", "r");
    //  if (fstatus == NULL)
    //  {
    //     printf("Encryption not done\n");
    //     return;
    // }
    // fclose(fstatus);

    fin = fopen("encrypt.txt", "r");
    if (fin == NULL)
    {
        printf("Encryption not done\n");
        return;
    }

    printf("Enter SAME KEY: ");
    scanf("%s", key);

    klen = strlen(key);
    if (klen == 0)
    {
        printf("Invalid key value\n");
        fclose(fin);
        return;
    }

    for (i = 0; i < klen; i++)
    {
        if (key[i] >= 'a' && key[i] <= 'z')
            key[i] = key[i] - 32;

        if (key[i] < 'A' || key[i] > 'Z')
        {
            printf("Invalid key value\n");
            fclose(fin);
            return;
        }
    }

    fout = fopen("decrypt.txt", "w");
    if (fout == NULL)
    {
        printf("File error\n");
        fclose(fin);
        return;
    }

    i = 0;
    while ((ch = fgetc(fin)) != EOF)
    {
        if (ch >= 'A' && ch <= 'Z')
        {
            shift = key[i % klen] - 'A';
            ch = (ch - 'A' - shift + 26) % 26 + 'A';
            i++;
        }
        else if (ch >= 'a' && ch <= 'z')
        {
            shift = key[i % klen] - 'A';
            ch = (ch - 'a' - shift + 26) % 26 + 'a';
            i++;
        }
        fputc(ch, fout);
    }

    fclose(fin);
    fclose(fout);

    printf("Decryption done\n");
}
