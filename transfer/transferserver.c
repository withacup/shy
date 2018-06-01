#include <unistd.h>
#include <stdio.h>
#include <getopt.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/stat.h>
#include <sys/sendfile.h>

#define BUFSIZE 514

#define USAGE                                                \
    "usage:\n"                                               \
    "  transferserver [options]\n"                           \
    "options:\n"                                             \
    "  -f                  Filename (Default: 6200.txt)\n" \
    "  -h                  Show this help message\n"         \
    "  -p                  Port (Default: 51418)\n"

/* OPTIONS DESCRIPTOR ====================================================== */
static struct option gLongOptions[] = {
    {"filename", required_argument, NULL, 'f'},
    {"help", no_argument, NULL, 'h'},
    {"port", required_argument, NULL, 'p'},
    {NULL, 0, NULL, 0}};


void error(char *msg)
{
    perror(msg);
    exit(0);
}


int main(int argc, char **argv)
{
    int option_char;
    int portno = 51418;             /* port to listen on */
    char *filename = "6200.txt"; /* file to transfer */

    setbuf(stdout, NULL); // disable buffering

    // Parse and set command line arguments
    while ((option_char = getopt_long(argc, argv, "p:hf:x", gLongOptions, NULL)) != -1)
    {
        switch (option_char)
        {
        case 'p': // listen-port
            portno = atoi(optarg);
            break;
        default:
            fprintf(stderr, "%s", USAGE);
            exit(1);
        case 'h': // help
            fprintf(stdout, "%s", USAGE);
            exit(0);
            break;
        case 'f': // listen-port
            filename = optarg;
            break;
        }
    }


    if ((portno < 1025) || (portno > 65535))
    {
        fprintf(stderr, "%s @ %d: invalid port number (%d)\n", __FILE__, __LINE__, portno);
        exit(1);
    }
    
    if (NULL == filename)
    {
        fprintf(stderr, "%s @ %d: invalid filename\n", __FILE__, __LINE__);
        exit(1);
    }

    /* Socket Code Here */
    int sockfd, newsockfd, clilen;
    socklen_t sock_len;
    ssize_t len;
    struct sockaddr_in server_addr, cli_addr;
    int filefd;
    int sent_bytes = 0;
    char file_size[256];
    struct stat file_stat;
    int offset;
    int remain_data;
    printf("here1");
    /* Create server socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
            fprintf(stderr, "Error creating socket --> %s", strerror(errno));

            exit(EXIT_FAILURE);
    }

    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int)) < 0)
        error("setsockopt(SO_REUSEADDR) failed");
    printf("here1");

    /* Zeroing server_addr struct */
    memset(&server_addr, 0, sizeof(server_addr));
    /* Construct server_addr struct */
    server_addr.sin_family = AF_INET;
    // inet_pton(AF_INET, SERVER_ADDRESS, &(server_addr.sin_addr));
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(portno);
    printf("here1");

    /* Bind */
    if ((bind(sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr))) == -1)
    {
            fprintf(stderr, "Error on bind --> %s", strerror(errno));

            exit(EXIT_FAILURE);
    }
    printf("here1");

    /* Listening to incoming connections */
    if ((listen(sockfd, 5)) == -1)
    {
            fprintf(stderr, "Error on listen --> %s", strerror(errno));

            exit(EXIT_FAILURE);
    }
    printf("here1");

    filefd = open(filename, S_IRUSR | S_IWUSR);
    if (filefd == -1)
    {
            fprintf(stderr, "Error opening file --> %s", strerror(errno));

            exit(EXIT_FAILURE);
    }
    printf("here1");

    /* Get file stats */
    if (fstat(filefd, &file_stat) < 0)
    {
            fprintf(stderr, "Error fstat --> %s", strerror(errno));

            exit(EXIT_FAILURE);
    }
    printf("here1");

    fprintf(stdout, "File Size: \n%d bytes\n", file_stat.st_size);

    sock_len = sizeof(struct sockaddr_in);
    /* Accepting incoming peers */
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &sock_len);
    if (newsockfd == -1)
    {
            fprintf(stderr, "Error on accept --> %s", strerror(errno));

            exit(EXIT_FAILURE);
    }
    fprintf(stdout, "Accept peer --> %s\n", inet_ntoa(cli_addr.sin_addr));
    printf("here1");

    sprintf(file_size, "%d", file_stat.st_size);

    /* Sending file size */
    len = send(newsockfd, file_size, sizeof(file_size), 0);
    if (len < 0)
    {
          fprintf(stderr, "Error on sending greetings --> %s", strerror(errno));

          exit(EXIT_FAILURE);
    }

    printf("here1");
    fprintf(stdout, "Server sent %d bytes for the size\n", len);

    offset = 0;
    remain_data = file_stat.st_size;
    /* Sending file data */
    while (((sent_bytes = sendfile(newsockfd, filefd, &offset, BUFSIZE)) > 0) && (remain_data > 0))
    {
    printf("file");
            fprintf(stdout, "1. Server sent %d bytes from file's data, offset is now : %d and remaining data = %d\n", sent_bytes, offset, remain_data);
            remain_data -= sent_bytes;
            fprintf(stdout, "2. Server sent %d bytes from file's data, offset is now : %d and remaining data = %d\n", sent_bytes, offset, remain_data);
    }

    close(newsockfd);
    close(sockfd);

    return 0;
}



























