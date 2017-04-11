#ifndef __SHARED_STRUCTS_H__
#define __SHARED_STRUCTS_H__

/** Implement your structs here */
process_t *process_queue;
process_t *process_tail;
process_t *current_process;
void push_tail_process(process_t *proc);
process_t *pop_front_process(void);

/**
 * This defines the lock structure
 */
typedef struct lock_state {
	int locked;
	process_t *blocked_queue;
	process_t *blocked_tail;
} lock_t;


void push_tail_blocked(process_t *proc);
process_t *pop_front_blocked(lock_t *l);

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
