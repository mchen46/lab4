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
	l->process = NULL;
	l->locked = 0;
}

/**
 * Grab the lock or block the process until lock is available
 *
 * @param l pointer to lock to be grabbed
 */
void l_lock(lock_t* l) {
	PIT->CHANNEL[0].TCTRL = 0x1;
	if (l->locked) {
		current_process->waiting = 1;
		current_process->lock = l;
		process_blocked();
	}
	else {
		current_process->waiting = 0;
		current_process->lock = l;
		l->process = current_process;
		l->locked = 1;
	}
	PIT->CHANNEL[0].TCTRL = 0x3;
}

/**
 * Release the lock along with the first process that may be waiting on
 * the lock. This ensures fairness wrt lock acquisition.
 *
 * @param l pointer to lock to be unlocked
 */
void l_unlock(lock_t* l) {
	PIT->CHANNEL[0].TCTRL = 0x1;
	if (!current_process->next_block) {
		l->locked = 0;
	}
	current_process->lock = NULL;
	l->process = current_process->next_block;
	PIT->CHANNEL[0].TCTRL = 0x3;
}
