#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <getopt.h>

#define BUFSIZE 1450

#define USAGE                                                \
    "usage:\n"                                               \
    "  transferclient [options]\n"                           \
    "options:\n"                                             \
    "  -s                  Server (Default: localhost)\n"    \
    "  -p                  Port (Default: 51418)\n"           \
    "  -o                  Output file (Default cs6200.txt)\n" \
    "  -h                  Show this help message\n"

/* OPTIONS DESCRIPTOR ====================================================== */
static struct option gLongOptions[] = {
    {"server", required_argument, NULL, 's'},
    {"port", required_argument, NULL, 'p'},
    {"output", required_argument, NULL, 'o'},
    {"help", no_argument, NULL, 'h'},
    {NULL, 0, NULL, 0}};

/* Main ========================================================= */
int main(int argc, char **argv)
{
    int option_char = 0;
    char *hostname = "localhost";
    unsigned short portno = 51418;
    char *filename = "cs6200.txt";

    setbuf(stdout, NULL);

    // Parse and set command line arguments
    while ((option_char = getopt_long(argc, argv, "s:p:o:hx", gLongOptions, NULL)) != -1)
    {
        switch (option_char)
        {
        case 's': // server
            hostname = optarg;
            break;
        case 'p': // listen-port
            portno = atoi(optarg);
            break;
        default:
            fprintf(stderr, "%s", USAGE);
            exit(1);
        case 'o': // filename
            filename = optarg;
            break;
        case 'h': // help
            fprintf(stdout, "%s", USAGE);
            exit(0);
            break;
        }
    }

    if (NULL == hostname)
    {
        fprintf(stderr, "%s @ %d: invalid host name\n", __FILE__, __LINE__);
        exit(1);
    }

    if (NULL == filename)
    {
        fprintf(stderr, "%s @ %d: invalid filename\n", __FILE__, __LINE__);
        exit(1);
    }

    if ((portno < 1025) || (portno > 65535))
    {
        fprintf(stderr, "%s @ %d: invalid port number (%d)\n", __FILE__, __LINE__, portno);
        exit(1);
    }

    /* Socket Code Here */
    int client_socket;
    ssize_t len;
    struct sockaddr_in remote_addr;
    char buffer[BUFSIZE];
    int file_size;
    FILE *received_file;
    int remain_data = 0;

    /* Zeroing remote_addr struct */
    memset(&remote_addr, 0, sizeof(remote_addr));

    /* Construct remote_addr struct */
    remote_addr.sin_family = AF_INET;
    inet_pton(AF_INET, hostname, &(remote_addr.sin_addr));
    remote_addr.sin_port = htons(portno);

    /* Create client socket */
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1)
    {
        fprintf(stderr, "Error creating socket --> %s\n", strerror(errno));

        exit(EXIT_FAILURE);
    }

    /* Connect to the server */
    if (connect(client_socket, (struct sockaddr *)&remote_addr, sizeof(struct sockaddr)) == -1)
    {
        fprintf(stderr, "Error on connect --> %s\n", strerror(errno));

        exit(EXIT_FAILURE);
    }

    /* Receiving file size */
    recv(client_socket, buffer, BUFSIZE, 0);
    file_size = atoi(buffer);
    fprintf(stdout, "\nFile size : %d\n", file_size);

    received_file = fopen(filename, "w");
    if (received_file == NULL)
    {
        fprintf(stderr, "Failed to open file foo --> %s\n", strerror(errno));

        exit(EXIT_FAILURE);
    }

    remain_data = file_size;

    while (((len = recv(client_socket, buffer, BUFSIZE, 0)) > 0) && (remain_data > 0))
    {
        fwrite(buffer, sizeof(char), len, received_file);
        remain_data -= len;
        fprintf(stdout, "Receive %d bytes and we hope :- %d bytes\n", len, remain_data);
    }
    fclose(received_file);

    close(client_socket);

    return 0;
}
