#ifndef __SHARED_STRUCTS_H__
#define __SHARED_STRUCTS_H__

/** Implement your structs here */
/**
 * This defines the lock structure
 */
typedef struct lock_state {
	int locked;
	process_t *process;
} lock_t;

/**
 * This structure holds the process structure information
 */
struct process_state {
	unsigned int *sp;
	unsigned int *orig_sp;
	int waiting;
	lock_t *lock;
	int n;
	struct process_state *next;
	struct process_state *next_block;
};

/**
 * This defines the conditional variable structure
 */
/* typedef struct cond_var {

} cond_t; */

#endif
