#include "BTask.h"

BTask::BTask(unsigned long periodMs, void (*callback)(Task* me)):
    Task(periodMs, callback)
{
    _context=(void *)NULL;
}

BTask::BTask(unsigned long periodMs, void (*callback)(Task* me), void *context):
    Task(periodMs, callback)
{
    _context=context;
}


void *BTask::getContext() {
    return _context;
}

void BTask::setContext(void *context) {
    _context = context;
}