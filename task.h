/*
    ELEX 8030 - PID Servo Project
    Copyright (C) 2009 Stephen Makonin
*/

#ifndef TASK_H
#define TASK_H

#include "stddef.h"
#include "no_copy.h"
#include "gmask.h"

enum task_priority
{
	priority_timer,
	priority_adc,
	priority_servo,
	priority_shell,
	priority_idle
};

class task : private no_copy
{
	private:
		static task *current;
		static void start();
		void **stack;  //whole stack
		void **sp;	//task stack ptr when not running
		int priority; // 0 is highest priority
	
	private:
		static void dispatch(task *); //context switch
		friend class task_list;

	protected:
		void fork();
		virtual void main();
		
	public:
		task(size_t, int = ~0);
		virtual ~task();
		static void yield();
		void slice();

		static task * const get_current()
		{
			return current;
		}

		bool lower_than(task * const t) const
		{
			return priority > t->priority;
		}
};

class task_list : private no_copy
{
	protected:
		struct node
		{
			node(task_list *l, int millisec = 0) : list(l), next(0), ptask(task::get_current()), time(millisec)
			{
				list->insert(this);
			}

			~node()
			{
				list->remove(this);
			}
		
			task_list *list;
			node *next;
			task * const ptask;
			int time;
			gmask stop_all_interrupts;
		};
		
		node *first;
		
	private:
		virtual void insert(node *);
		node *remove(node *);
		
	private:
		friend node;

	public:
		task_list();
		virtual ~task_list();
		void block(int = 0);  //on that list
		void unblock(); //from list
};

class delta_task_list: public task_list
{
	private:
		virtual void insert(task_list::node *);

	public:
		delta_task_list()
		{
		}
		
		void deincroment();
		bool zero();
};

class priority_task_list: public task_list
{
	private:
		virtual void insert(task_list::node *);
		
	public:
		priority_task_list()
		{
		}
};

class mutex : public task_list
{
	private:
		/*const*/ task *holder;
		void acquire(); //WAITOP
		void release(); //SIGOP

	public:
		mutex();

		class lock : private no_copy
		{
			private:
				mutex &mx;

			public:
				lock(mutex &m) : mx(m)
				{
					mx.acquire();
				}

				~lock()
				{
					mx.release();
				}			
		};

		friend lock;
};

class semaphore : public task_list
{
	private:
		int value;

	public:
		semaphore(int = 0);
		void wait();
		void signal();
};

#endif

