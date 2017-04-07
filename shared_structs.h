#ifndef __SHARED_STRUCTS_H__
#define __SHARED_STRUCTS_H__

/** Implement your structs here */
void move_to_ready(void);
/**
 * This structure holds the process structure information
 */
typedef struct process_state {
	unsigned int *sp;
	unsigned int *orig_sp;
	int waiting;
	int n;
	struct process_state *next;
	struct process_state *next_block;
} process_t;

/**
 * This defines the lock structure
 */
typedef struct lock_state {
	int locked;
} lock_t;

/**
 * This defines the conditional variable structure
 */
/* typedef struct cond_var {

} cond_t; */

#endif
