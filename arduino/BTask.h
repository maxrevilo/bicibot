#ifndef BTASK_H
#define BTASK_H
#include <Arduino.h>
#include <SoftTimer.h>

class BTask : public Task
{
    public:
        BTask(
            unsigned long periodMs,
            void (*callback)(Task* me)
        );

        BTask(
            unsigned long periodMs,
            void (*callback)(Task* me),
            void *context
        );

        void setContext(void *context);
        void *getContext();
    private:
        void *_context;
};

#endif
