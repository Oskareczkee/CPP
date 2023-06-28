//this list should work as well as in C as in C++
//I compiled this using C++ compiler, so it works in C++
//EDIT: I compiled this in C compiler and works as well

#ifdef __cplusplus
#pragma once
#include <iostream>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

struct Link
{
	struct Link* pre;
	struct Link* suc;
};

struct List
{
	struct Link* first;
	struct Link* last;
};

void init(struct List* lst);
struct List* create();
void clear(struct List* lst);
void destroy(struct List* lst);

void push_back(struct List* lst, struct Link* p);
void push_front(struct List* lst, struct Link* p);

void insert(struct List* lst, struct Link* p, struct Link* q);
struct Link* erase(struct List* lst, struct Link* p);

struct Link* advance(struct Link* lst, int n);


/*---------------------------------------------------------------------------------------*/

void init(struct List* lst)
{
	assert(lst);
	lst->first = lst->last = 0;
}

struct List* create()
{
	struct List* lst = (struct List*)malloc(sizeof(struct List));
	init(lst);
	return lst;
}

void clear(struct List* lst)
{
	assert(lst);
	{
		struct Link* curr = lst->first;

		while (curr)
		{
			struct Link* next = curr->suc;
			free(curr);
			curr = next;
		}
		lst->first = lst->last = 0;
	}
}

void destroy(struct List* lst)
{
	assert(lst);
	clear(lst);
	free(lst);
}


//check p is null case
void push_back(struct List* lst, struct Link* p)
{
	assert(lst);
	{
		struct Link* last = lst->last;
		if (last)
		{
			last->suc = p;
			p->pre = last;
		}
		else
		{
			lst->first = p;
			p->pre = 0;
		}

		lst->last = p;
		p->suc = 0;
	}
}

void push_front(struct List* lst, struct Link* p)
{
	assert(lst);
	{
		struct Link* first = lst->first;
		if (first)
		{
			lst->first = p;
			p->suc = first;
		}
		else
		{
			lst->first = p;
			p->pre = 0;
		}
	}
}


//inserts q before p
void insert(struct List* lst, struct Link* p, struct Link* q)
{
	assert(lst);
	assert(p);
	assert(q);
	{
		q->suc = p;

		if (p == lst->first)			// ref is first
		{
			q->pre = 0;

			lst->first = q;
		}
		else if (p == lst->last)		// ref is last
		{
			if (p->pre)
			{
				q->pre = p->pre;

				p->pre->suc = q;
			}
			else
			{
				q->pre = 0;
			}
		}
		else							// ref is in between
		{
			q->pre = p->pre;

			p->pre->suc = q;
		}

		p->pre = q;
	}
}

struct Link* erase(struct List* lst, struct Link* p)
{
	assert(lst);
	if (p == 0) return 0;

	if (p == lst->first)
	{
		if (p->suc)
		{
			lst->first = p->suc;
			p->suc->pre = 0;
			return p->suc;
		}
		else
		{
			lst->first = 0;
			lst->last = 0;
			return 0;
		}
	}
	else if (p == lst->last)
	{
		if (p->pre)
		{
			lst->last = p->pre;
			p->pre->suc = 0;
		}
		else
		{
			lst->first = 0;
			lst->last = 0;
			return 0;
		}
	}
	else
	{
		p->suc->pre = p->pre;
		p->pre->suc = p->suc;
		return p->suc;
	}
}

//advances link n times, if cannot advance n time it just returns the last element it could advance to
struct Link* advance(struct Link* lst, int n)
{
	assert(lst);

	{
		struct Link* curr = lst;

		if (n > 0)
		{
			while (n)
			{
				curr = curr->suc;
				n--;
			}
		}
		else
		{
			while (n)
			{
				curr = curr->pre;
				n++;
			}
		}
		return curr;
	}

}

struct Name_test
{
	struct Link lnk;
	char* name;
};

struct Name_test* make_name(const char* name)
{
	struct Name_test* p = (struct Name_test*)malloc(sizeof(struct Name_test));
	p->name = (char*)name;
	return p;
}

void intrusive_list_test()
{
	int count = 0;
	struct List names;
	struct Link* curr;
	init(&names);

	//cout << "aaa\n";
	push_back(&names, (struct Link*)make_name("Oskar"));
	push_back(&names, (struct Link*)make_name("Oliwia"));
	push_back(&names, (struct Link*)make_name("Olgierd"));
	push_front(&names, (struct Link*)make_name("Olaf"));
	//cout << "aab\n";

	//idk, but this does not work for 0 and 1 value in advance, maybe i missed something
	insert(&names, advance(names.first, 2),(struct Link*)make_name("Olek"));
	//cout<< "aac\n";
	erase(&names, advance(names.first, 0));
	//cout << "aad\n";

	curr = names.first;

	for (; curr != 0; curr = curr->suc)
		printf("Element: %s\n", ((struct Name_test*)curr)->name);

}

