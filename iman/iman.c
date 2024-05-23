#include "../headers.h"

void iman(char *input_full)
{
    char *ptr = NULL;
    char *token = strtok_r(input_full, " \t\n", &ptr);
    // printf("%s\n", token);
    token = strtok_r(NULL, " \t\n", &ptr);
    int pid;
    if (token == NULL)
    {
        printf("No man page requested.\n");
        return;
    }
    char *hostname = "man.he.net";
    char *path = token;

    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    struct addrinfo *result;
    int s = getaddrinfo(hostname, NULL, &hints, &result);
    if (s != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }

    char *ip_ad = inet_ntoa(((struct sockaddr_in *)result->ai_addr)->sin_addr);

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        perror("Socket creation failed");
        return;
    }

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(80);
    inet_pton(AF_INET, ip_ad, &serv_addr.sin_addr);

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) != 0)
    {
        perror("Connection failed");
        close(sock);
        return;
    }

    // printf("Connected\n");

    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "GET /?topic=%s&section=all HTTP/1.1\r\nHost: %s\r\nContent-Type: text/plain\r\nUser-Agent: MyHTTPClient/1.0\r\nAccept: */*\r\n\r\n", path, hostname);

    sendto(sock, buffer, strlen(buffer), 0, result->ai_addr, result->ai_addrlen);

    char recvBuffer[9012];
    size_t bytesReceived = recvfrom(sock, recvBuffer, sizeof(recvBuffer), 0, NULL, NULL);

    // printf("%s\n", recvBuffer);

    char *start = strstr(recvBuffer, "NAME\n");
    if (start == NULL)
    {
        printf("ERROR\n\tNo such command\n");
        return;
    }
    char *mid = strstr(recvBuffer, "DESCRIPTION\n");
    if (mid == NULL)
        goto print;
    char *end = strstr(mid, "\n\n");
    end += 2;
    while (*end == ' ')
    {
        end = strstr(end, "\n\n");
        if (end == NULL)
            goto print;
        end += 2;
    }

    *end = '\0';

print:
    printf("%s\n", start);

    freeaddrinfo(result);
    close(sock);

    return;
}