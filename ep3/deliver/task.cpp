/* Nathan Benedetto Proença 8941276  **
** Victor Sena Molero 8941317        */
#include "task.h"

unsigned Task::quant;

/** Constructor recieving owner process **/
Task::Task (Process * owner) {
    process = owner;
}
