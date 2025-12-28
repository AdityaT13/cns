printf("Client");

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

long long modexp(long long base, long long exp, long long mod)
{
    long long result = 1;
    base %= mod;
    while (exp > 0)
    {
        if (exp & 1)
            result = (result * base) % mod;
        exp >>= 1;
        base = (base * base) % mod;
    }
    return result;
}

int main()
{
    int sockfd;
    struct sockaddr_in serv;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    serv.sin_family = AF_INET;
    serv.sin_port = htons(8080);
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sockfd, (struct sockaddr *)&serv, sizeof(serv));

    long long p, g, B;
    read(sockfd, &p, sizeof(p));
    read(sockfd, &g, sizeof(g));
    read(sockfd, &B, sizeof(B));

    printf("Received: p=%lld, g=%lld, Bob's public B=%lld\n", p, g, B);

    long long a;
    printf("Enter Alice's private key a: ");
    scanf("%lld", &a);
    long long A = modexp(g, a, p);
    write(sockfd, &A, sizeof(A));

    long long key = modexp(B, a, p);

    printf("Shared secret key = %lld\n", key);

    close(sockfd);
    return 0;
}
printf("-----------------------------");
printf("server");

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

long long modexp(long long base, long long exp, long long mod)
{
    long long result = 1;
    base %= mod;
    while (exp > 0)
    {
        if (exp & 1)
            result = (result * base) % mod;
        exp >>= 1;
        base = (base * base) % mod;
    }
    return result;
}

int main()
{
    int sockfd, newsock;
    struct sockaddr_in serv, cli;
    socklen_t cli_len = sizeof(cli);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(8080);

    bind(sockfd, (struct sockaddr *)&serv, sizeof(serv));
    listen(sockfd, 1);

    printf("Bob (Server) waiting for Alice...\n");
    newsock = accept(sockfd, (struct sockaddr *)&cli, &cli_len);
    printf("Alice connected!\n");

    long long p, g, b;
    printf("Enter prime p: ");
    scanf("%lld", &p);

    printf("Enter primitive root g: ");
    scanf("%lld", &g);

    printf("Enter Bob's private key b: ");
    scanf("%lld", &b);

    long long B = modexp(g, b, p);

    write(newsock, &p, sizeof(p));
    write(newsock, &g, sizeof(g));
    write(newsock, &B, sizeof(B));

    long long A;
    read(newsock, &A, sizeof(A));

    long long key = modexp(A, b, p);

    printf("Alice public A = %lld\n", A);
    printf("Shared secret key = %lld\n", key);

    close(newsock);
    close(sockfd);
    return 0;
}