/*
    ELEX 8030 - PID Servo Project
    Copyright (C) 2009 Stephen Makonin
*/

#include "task.h"

task initial_task(0, priority_idle);
task *task::current(&initial_task);
//task_list ready_list;
priority_task_list _ready_list;
task_list &ready_list(_ready_list); //polymorphism in  static object 

register void **register_sp asm("s");

void task::dispatch(task *t)
{
	//note pc is on stack d,x,y not assumed to servive a call to any func so do not need to be saved
	current->sp = register_sp;
	current = t;
	register_sp = current->sp;
	//note called by 1 taks but returned to another task
}

void task::slice()
{
	ready_list.unblock();
}

task_list::task_list()
: first(0)
{
}

task_list::~task_list()
{
}

void task_list::insert(node *n)
{
	gmask stop_all_interrupts;
	
	if(n)
	{
		if(first == 0)
		{
			first = n;
		}
		else
		{
			for(node *m = first; m; m = m->next)		
			{
				if(m->next == 0)
				{
					m->next = n;
					break;
				}
			}	
		}

		n->list = this;
	}
}

task_list::node *task_list::remove(node *n)
{
	gmask stop_all_interrupts;
	
	if(n)
	{
		if(n == first)
		{
			first =  n->next;
		}
		else
		{
			for(node *m = first; m; m = m->next)
			{
				if(m->next == n)
				{
					m->next = n->next;
					break;
				}
			}
		}

		n->list = 0;
		n->next = 0;	
	}
	
	return n;		
}

void task_list::block(int millisec)
{
	node n(this, millisec);
	task::dispatch(ready_list.first->ptask);
}

// if first->node->task is higher pri then current pri then invariant will be false
void task_list::unblock()
{
	gmask stop_all_interrupts;

	node n(&ready_list); //put running task on ready list
	ready_list.insert(remove(first));
	task::dispatch(ready_list.first->ptask);
}

void task::yield()
{
	ready_list.block();
}

void task::main()
{
}

void task::start()
{
	yield();
	
	asm("cli");
	current->main();
	asm("sei");
	
	task_list forever;
	forever.block();
}

task::task(size_t size, int p)
: stack(new (void *)[size / sizeof(void *)]), sp(&stack[size / sizeof(void *)]), priority(p)
{	
	if(size)
	{
		*--sp = 0;
		*--sp = 0; //terminate frame chain for debugger
		*--sp = &start; // hack: fake a return address to return to
	}
}

task::~task()
{
	delete[] stack;
}

void task::fork()
{
	//call at end of derived class constructor
	task_list::node n(&ready_list);
	dispatch(this);
}

void delta_task_list::insert(task_list::node *n)
{
	gmask stop_all_interrupts;
	
	if(n)
	{
		if(first == 0)
		{
			first = n;
		}
		else
		{
			if(n->time < first->time)
			{
				first->time -= n->time;
				n->next = first;		
				first = n;		
			}
			else			{	
				node *p = first;
				node *m = p->next;
				int sum = first->time;

				while(m)
				{		
					if(n->time < sum + m->time)
						break;

					sum += m->time;
					p = m;
					m = p->next;
				}	
		
				n->time -= sum;
				if(m)
					m->time -= n->time;

				p->next = n;
				n->next = m;
			}		
		}

		n->list = this;
	}
}

void delta_task_list::deincroment()
{
    gmask stop_all_interrupts;
    
	if(first)
		first->time--;
}

bool delta_task_list::zero()
{
    gmask stop_all_interrupts;
    
	return first && first->time <= 0;
		
}

void priority_task_list::insert(task_list::node *n)
{
	gmask stop_all_interrupts;
	
	if(n)
	{
		if(first == 0)
		{
			first = n;
		}
		else
		{
			if(first->next->ptask->lower_than(n->ptask))
			{
				n->next = first;		
				first = n;
			}
			else
			{
				node *p = first;
				node *m = p->next;

				while(m)
				{
					if(m->next->ptask->lower_than(n->ptask))
						break;

					p = m;
					m = p->next;
				}	
		
				p->next = n;
				n->next = m;
			}
		}

		n->list = this;	
	}
}

mutex::mutex()
: holder(0)
{
}

void mutex::acquire()
{
    gmask stop_all_interrupts;
    
    while(holder)	// while another task holds mutex
	    block();
    
    holder = task::get_current();
}

void mutex::release()
{
    gmask stop_all_interrupts;
    holder = 0;
    unblock(); // wake up to 1 task to r
}

semaphore::semaphore(int v)
: value(v)
{
}

void semaphore::wait()
{
	gmask stop_all_interrupts;
	while(value <= 0)
		block();

	--value;
}

void semaphore::signal()
{
	gmask stop_all_interrupts;
	++value;
	unblock();
}
