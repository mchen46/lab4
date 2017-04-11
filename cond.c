#include "lock.h"

/**
 * Initialises the conditional variable structure
 *
 * @param l ignored
 * @param c pointer to conditional variable to be initialised
 */
void c_init(lock_t* l, cond_t* c);


/**
 * wait until condition is true
 *
 * @param l pointer to lock/mutex for conditional variable
 * @param c pointer to conditional variable
 */
void c_wait(lock_t* l, cond_t* c);


/**
 * Check if processes are waiting on conditional variable
 *
 * @param l Pointer to lock/mutex. Not used, but mutex must be acquired
 * before calling to ensure atomicity
 * @param c pointer to conditional variable
 *
 * @return 0 if no processes waiting
 * @return 1 if processes waiting
 */
int c_waiting(lock_t* l, cond_t* c);


/**
 * Signal that condition is met
 *
 * @warning Will misbehave if no processes are waiting and is signalled
 * 
 * @param l pointer to lock (is released after signalling)
 * @param c pointer to conditional variable
 */
void c_signal(lock_t* l, cond_t* c);

#endif /* __LOCK_H_INCLUDED */
