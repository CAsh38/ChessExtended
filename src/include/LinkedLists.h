#pragma once
#include <cstdlib>

namespace LinkedLists
{	
	template <typename T>
	/* When refering to Node struct not in a specific context, we understand its most simple form: */
	struct Node
	{
		struct Node* next;
		T data;
	};

	template <typename T>
	Node<T> *CreateNode(T value)
	{
		Node<T>* node = (Node<T>*)calloc(1, sizeof(Node<T>));
		if (node == NULL) return NULL;
		node->next = node;
		node->data = value;
		return node;
	}

	/*Herein it is defined one-way simple circular linked lists. The assumptions here are as follows:
	Access to the node next field is done only through dedicated functions
	The data inside the node can be anything you want, just typedef it
	Being more accustomed with C-style data structures programming, I chose to use struct and not class*/
	namespace SimpleCircular
	{
		template <typename T>
		struct CircularLinkedList
		{
			struct Node<T>* begin = NULL, * end = NULL;
			unsigned size = 0;

			CircularLinkedList() = default;

			int CheckIntegrity()
			{
				Node<T>* iter = begin;
				for (int i = 0; i < size; i++) iter = iter->next;
				if (iter == end) return 0;
				else return 1;
			}
			int CheckCircularity()
			{
				if (end->next == begin) return 0;
				else return 1;
			}

			void Init(T value)
			{
				Node<T>* node = CreateNode<T>(value);
				begin = node;
				end = begin;
				size = 1;
			}

			/*Assumption: the position argument can begin from 0 as with arrays*/
			Node<T>* GetAt(int pos)
			{
				pos = pos % size;
				int counter = 0;
				Node<T>* iter = begin;
				while (counter != pos)
				{
					iter = iter->next;
					counter++;
				}
				return iter;
			}
			/*Assumption: the new node will have the exact position in the returned linked list,
			meaning it is inserted behind the element in the position, resulting in
			never inserting T at the end. O(n) time in the worst case*/
			void InsertAt(unsigned pos, T value)
			{
				if (pos == size)
				{
					InsertBack(value);
					return;
				}
				Node<T>* newOne = CreateNode<T>(value);
				if (pos == 0)
				{
					begin = newOne;
					newOne->next = end->next;
					end->next = newOne;
				}
				else
				{
					Node<T>* thatNode = GetAt(pos - 1);
					newOne->next = thatNode->next;
					thatNode->next = newOne;
					
				}
				size++;
				return;
			}
			/*O(1) time*/
			void InsertBack(T value)
			{
				Node<T>* newOne = CreateNode<T>(value);
				end->next = newOne;
				newOne->next = begin;
				end = newOne;
				size++;
				return;
			}

			void Clear()
			{
				Node<T>* Iterator = begin, *obj = NULL;
				while (Iterator != end)
				{
					obj = Iterator;
					Iterator = Iterator->next;
					free(obj);
				}
				free(end);
				begin = end = nullptr;
				return;
			}

			~CircularLinkedList() { Clear(); }
			
			CircularLinkedList(const CircularLinkedList& other)
			{
				if (!other.begin) return;
				Node<T>* node = other.begin;
				Init(node->data);
				node = node->next;

				for (unsigned i = 1; i < other.size; i++)
				{
					InsertBack(node->data);
					node = node->next;
				}
			}

			CircularLinkedList& operator=(const CircularLinkedList& other)
			{
				if (this == &other)
					return *this;
				Clear(); // free existing nodes
				if (!other.begin)
					return *this;
				Node<T>* node = other.begin;
				Init(node->data);
				node = node->next;

				for (unsigned i = 1; i < other.size; i++)
				{
					InsertBack(node->data);
					node = node->next;
				}
				return *this;
			}
		};
	}
}