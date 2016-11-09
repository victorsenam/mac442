#include "task.h"

unsigned Task::quant;

/** Constructor recieving owner process **/
Task::Task (Process * owner) {
    process = owner;
}
