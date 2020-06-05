//
// Created by steve-urbit on 4/6/20.
//

#include <stdio.h>
#include <signal.h>
#include <ulfius.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

//#define PORT 8080

/**
 * Callback function for the web application on /helloworld url call
 */
int callback_hello_world (const struct _u_request * request, struct _u_response * response, void * user_data) {
    ulfius_set_string_body_response(response, 200, "Hello World!");
    return U_CALLBACK_CONTINUE;
}

/**
 * main function
 */
int main(void) {
    struct _u_instance instance;
    sigset_t myset;
    printf("version");
    // Initialize instance with the port number
    struct sockaddr_in bind_address;
    memset(&bind_address,0,sizeof(bind_address));
    bind_address.sin_family = AF_INET;
    bind_address.sin_port = htons(8080);
    //bind_address.sin_addr.s_addr = inet_addr("0.0.0.0");
    inet_aton("0.0.0.0", (struct in_addr *) &bind_address.sin_addr.s_addr);
    if (ulfius_init_instance(&instance, PORT, &bind_address, NULL) != U_OK) {
        fprintf(stderr, "Error ulfius_init_instance, abort\n");
        return(1);
    }
    // Endpoint list declaration
    ulfius_add_endpoint_by_val(&instance, "GET", "/api/stats", NULL, 0, &callback_hello_world, NULL);

    // Start the framework
    if (ulfius_start_framework(&instance) == U_OK) {
        printf("Start framework on port %d\n", instance.port);
        fflush(stdout);
        sigemptyset(&myset);
        sigsuspend(&myset);
    } else {
        fprintf(stderr, "Error starting framework\n");
    }
    printf("End framework\n");

    ulfius_stop_framework(&instance);
    ulfius_clean_instance(&instance);

    return 0;
}