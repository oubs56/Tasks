#ifndef __TASK_H__
#define __TASK_H__

typedef void (*runnable)(void);

class task {
public:
	struct task *next;
	jmp_buf context;

	unsigned long wake;

	void create(void *stack, runnable entry);
};

template<unsigned N>
class Task: public task {
public:
	Task(runnable entry) {
		create(&_stack[N-1], entry);
	}

private:
	unsigned _stack[N];
};

class task_queue {
public:
	task_queue() { _head = _tail = 0; }

	task *remove();

	void add(task *t);

	inline bool empty() { return _head == 0; }

	inline task *head() { return _head; }

	void insert(task *p, task *t);

private:
	task *_head, *_tail;
};

class Tasks {
public:
	/*
	 * initialises the task library: call from setup().
	 */
	static void init(void);

	/*
	 * makes a task runnable.
	 */
	static inline void ready(task *t) {
		_ready.add(t);
	}

	static inline task *current(void) {
		return _curr;
	}

	static void reschedule(void);

	/*
	 * sets a handler to be called when no task is runnable,
	 * by default (on ATtiny at least) the processor will jump
	 * to the reset vector.
	 */
	static inline void set_idle_handler(runnable idle_handler) {
		_idle_handler = idle_handler;
	}
private:
	static task *_curr;
	static task_queue _ready;
	static runnable _idle_handler;
};

#endif