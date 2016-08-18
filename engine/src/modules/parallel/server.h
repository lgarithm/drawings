#ifndef SERVER_H
#define SERVER_H

#include <string>

struct server {
    const std::string hostname;
    int port;
    int fd;
    bool fast_fail;

    server(int port, const std::string &_ = "localhost");
    ~server();

    void operator()();
};

template <typename T> struct wrapper {
    T *d;
    bool done;

    wrapper(T *d) : d(d), done(false) {}

    ~wrapper()
    {
        if (done && d != nullptr)
            delete d;
    }

    void operator()()
    {
        if (!done) {
            done = true;
            (*d)();
            delete d;
            d = nullptr;
        }
    }
};

template <typename T> wrapper<T> wrap(T *d) { return wrapper<T>(d); }

#endif // SERVER_H
