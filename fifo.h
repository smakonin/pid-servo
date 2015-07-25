/*
    ELEX 8030 - PID Servo Project
    Copyright (C) 2009 Stephen Makonin
*/

#ifndef FIFO_H
#define FIFO_H

#include "task.h"

template<typename T> class fifo
{
	private:
		T *buf_ptr;
		T *end_ptr;
		T *put_ptr;
		T *get_ptr;
		semaphore space;
		semaphore items;

	public:
		fifo(int len) : buf_ptr(new T[len]), end_ptr(buf + len), put_ptr(buf), get_ptr(buf), space(len), items(0)
		{
		}

		~fifo()
		{
			delete buf_ptr;
		}

		void put(const T &t)
		{
			space.wait();
			*put_ptr++ = t;
			put_ptr = put_ptr < end_ptr ? put_ptr : buf_ptr;
			items.signal();
		}		

		T get()
		{
			items.wait();
			T t = *get_ptr++;
			get_ptr = get_ptr < end_ptr ? get_ptr : buf_ptr;
			space.signal();
			return t;
		}
};

#endif

