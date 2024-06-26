#include <stdio.h>

#include "common.h"
#include "server.h"


void on_ipv4_server_start(int communication_socketd, struct sockaddr_in client_address) {

    int byte_read;
    char* result = read_until_terminator_found(communication_socketd, "\n---\n", 5, 0, &byte_read); // no zero-term
    result = zero_term(result, byte_read);

    char* filepath = get_nth_str(result, ":", 1);

    receive_and_save_file(communication_socketd, filepath, NULL, 0, 0);
}


int main(int argc, char *argv[]) {

    require_n_params_or_fail(1, argc);

    short port = parse_to_long_or_fail(argv[1]);

    int socketd = new_tcp_ipv4_server("127.0.0.1", port);       // automatic htons

    start_singlethread_server(socketd, 6);
    // start_multiprocess_server(socketd, 6);


    return 0;
}
