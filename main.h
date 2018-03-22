#ifndef VERTEILTESYSTEME_PRAKTIKUM2_MAIN_H
#define VERTEILTESYSTEME_PRAKTIKUM2_MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

#include "http_protocol.h"

#define HEADER_BUFFER_SIZE 256

#define ERR_PARAM 2
#define ERR_DIR 3
#define ERR_SOCK_SET_OPT 5
#define ERR_SOCK_NO_BIND 6
#define ERR_ALLOC 7

typedef struct
{
    int sock_fd;
    int addr_len;
    struct sockaddr_in addr;
} socket_info;

typedef struct {
    char method[16];
    char file[256];
} client_header;

typedef struct{
    long long file_size;
    char content_type[32];
    char modify_date[32];
} file_info;

void process_request(const char* request_header, socket_info* client_info, const char* doc_root);

void read_dir(const char* file_path, char** content, file_info* file_meta);

int server_start(const char* dir, int port, socket_info* si);

void read_header_data(client_header* src, const char* input_string, const char* doc_root);

char* gen_response(const char* file_path, int is_dir, int statuscode, long* resp_size);

void gen_header(char** header, int status_response, file_info* file_data);

void read_file(const char* file_path, char** content, file_info* file_meta);

void read_error(int statuscode, char** content, file_info* file_meta);

#endif //VERTEILTESYSTEME_PRAKTIKUM2_MAIN_H
