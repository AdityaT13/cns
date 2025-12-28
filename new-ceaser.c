#include <stdio.h>
#include <stdlib.h>

void encryptFile();
void decryptFile();

int main()
{
    int choice;
    while (1)
    {
        printf("\n--- Caesar Cipher Menu ---\n");
        printf("1. Encrypt File\n");
        printf("2. Decrypt File\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            encryptFile();
            break;
        case 2:
            decryptFile();
            break;
        case 3:
            printf("Exiting...\n");
            exit(0);
        default:
            printf("Invalid choice!\n");
        }
    }
    return 0;
}

void encryptFile()
{
    FILE *fin, *fout;
    char ch, in[50], out[50];
    int key;

    printf("Enter input file name: ");
    scanf("%s", in);
    printf("Enter output file name: ");
    scanf("%s", out);

    fin = fopen(in, "r");
    fout = fopen(out, "w");
    if (fin == NULL || fout == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter encryption key (1-25): ");
    scanf("%d", &key);

    while ((ch = fgetc(fin)) != EOF)
    {
        if (ch >= 'a' && ch <= 'z')
            ch = ((ch - 'a' + key) % 26) + 'a';
        else if (ch >= 'A' && ch <= 'Z')
            ch = ((ch - 'A' + key) % 26) + 'A';
        fputc(ch, fout);
    }

    fclose(fin);
    fclose(fout);
    printf("Encryption completed! Encrypted text saved in encrypt.txt\n");
}

void decryptFile()
{
    FILE *fin, *fout;
    char ch, in[50], out[50];
    int key;

    printf("Enter input file name: ");
    scanf("%s", in);
    printf("Enter output file name: ");
    scanf("%s", out);

    fin = fopen(in, "r");
    fout = fopen(out, "w");
    if (fin == NULL || fout == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter decryption key (1-25): ");
    scanf("%d", &key);

    while ((ch = fgetc(fin)) != EOF)
    {
        if (ch >= 'a' && ch <= 'z')
            ch = ((ch - 'a' - key + 26) % 26) + 'a';
        else if (ch >= 'A' && ch <= 'Z')
            ch = ((ch - 'A' - key + 26) % 26) + 'A';
        fputc(ch, fout);
    }

    fclose(fin);
    fclose(fout);
    printf("Decryption completed! Decrypted text saved in decrypt.txt\n");
}
