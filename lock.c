#include "lock.h"
#include "3140_concur.h"
#include <stdlib.h>
#include <fsl_device_registers.h>

process_t *blocked_queue = NULL;

void add_to_block (process_t *new_process) 
{
	// list is empty, add to beginning
	if (blocked_queue == NULL) {
		blocked_queue = new_process;
		new_process->next = NULL;
	} 
	// list is not empty, add to end
	else {
		process_t *tmp = blocked_queue;
		// traverse the list to the end
		while (tmp->next != NULL) {
			tmp = tmp->next;
		}
		// add new_process as the next of the current last
		tmp->next = new_process;
		new_process->next = NULL;
		//tmp->next->next = NULL;
	}
}

process_t *remove_from_block (void) {
	if (blocked_queue == NULL) return NULL;
	process_t *elem = blocked_queue;
	blocked_queue = blocked_queue->next;
	return elem;
}

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
	if (l->locked == 1) {
		add_to_block(current_process);
		process_blocked();
	}
	else {
		l->process = current_process;
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
	if (blocked_queue == NULL) {
		l->process = NULL;
		l->locked = 0;
	}
	else {
		l->process = remove_from_block();
	}
}
