#include "lock.h"
#include "3140_concur.h"
#include "shared_structs.h"
#include <stdlib.h>
#include <fsl_device_registers.h>


/**
 * Initialises the lock structure
 *
 * @param l pointer to lock to be initialised
 */
void l_init(lock_t* l) {
	l->locked = 0;
}

/**
 * Grab the lock or block the process until lock is available
 *
 * @param l pointer to lock to be grabbed
 */
void l_lock(lock_t* l) {
	if (l->locked) {
		current_process->waiting = 1;
		process_blocked();
	}
	else {
		current_process->waiting = 0;
		l->locked = 1;
	}
}

/**
 * Release the lock along with the first process that may be waiting on
 * the lock. This ensures fairness wrt lock acquisition.
 *
 * @param l pointer to lock to be unlocked
 */
void l_unlock(lock_t* l) {
	if (!current_process->next_block) {
		l->locked = 0;
	}
	else {
		move_to_ready();
	}
}
