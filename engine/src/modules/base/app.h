#ifndef APP_H
#define APP_H

#include "model.h"
#include "task.h"

int app(int, const char * const argv[],
        const atlas& _=atlas(), world_gen=nullptr);
void run(const image_task&);
int ret_size(const image_task&);

#endif  // APP_H