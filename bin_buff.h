#pragma once

#ifndef BIN_BUFF_H
# define BIN_BUFF_H

# define ERR_OPEN "Can't open first file\n"
# define ERR_CREATE "Can't create second file\n"
# define ERR_ARGS "Error count arguments\n"


struct MyStruct
{
	struct MyStruct* next;
	uint16_t data;
};

class cycle_buff
{
	int my_size;
	MyStruct* cycle;
	MyStruct* head;
	bool boolean;
public:
	cycle_buff()
	{
		my_size = 0;
		cycle = new MyStruct;
		head = cycle;
		boolean = false;
		for (int i = 0; i < 100; i++)
		{
			cycle->next = new MyStruct;
			cycle = cycle->next;
		}
		cycle->next = head;
	}
	int size() { return (my_size); }
	bool is_good_file() { return (boolean); }
	MyStruct* begin() const { return (cycle); }
	void	push(uint16_t val)
	{
		if (my_size < 101)
		{
			cycle->data = val;
			cycle = cycle->next;
			my_size++;
		}
		else
		{
			boolean = true;
			cycle = cycle->next;
			cycle->data = val;
		}
	}
	~cycle_buff()
	{
		MyStruct* temp;

		for (int i = 0; i < 101; i++)
		{
			temp = cycle;
			cycle = cycle->next;
			delete temp;
		}
	}
};

#endif