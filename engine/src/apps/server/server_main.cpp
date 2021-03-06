#include <cstdio>
#include <cstring>

#include <signal.h>
#include <unistd.h>



#include <rey/parallel/server.h>

auto serve = wrap<server>(nullptr);
void term(int) {}

int main(int argc, char *argv[])
{
    int port = 7778;
    if (argc > 1) {
        int p;
        if (sscanf(argv[1], "%d", &p) == 1 && 1000 < p && p <= 65535) {
            port = p;
        } else {
            printf("Usage:\n\t%s [port]\n", argv[0]);
            return 1;
        }
    }
    serve = wrap(new server(port));
    {
        struct sigaction action;
        memset(&action, 0, sizeof(struct sigaction));
        action.sa_handler = term;
        sigaction(SIGINT, &action, NULL);
    }
    signal(SIGPIPE, SIG_IGN);
    printf("\e[1;42mrender server running at %s:%d\e[m\n", "localhost", port);
    serve();
    return 0;
}
