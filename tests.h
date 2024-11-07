#pragma once
#pragma once
#include "LinkedListSmart.h"
#include "LinkedListSequence.h"
#include <cassert> 

int array1[5] = { 1, 2, 3, 4, 5 };
int array2[3] = { 2, 3, 4 };
int array3[6] = { 1, 2, 3, 4, 5 ,6 };
int array4[6] = { 0, 1, 2, 3, 4, 5 };
int array5[8] = { 11, 1, 33, 2, 3, 4, 5, 22 };
int array6[10] = { 1, 2, 3, 4, 5, 1, 2, 3, 4, 5 };
int array7[6] = { 11, 1, 2, 3, 4, 5 };
int array8[7] = { 11, 1, 2, 3, 4, 5, 22 };
int array9[2] = { 1, 2 };
int array10[2] = { 2, 1 };
int array11[1] = { 1 };

void Test_of_GetLastLinkedListSmart()
{
	LinkedListSmart<int>list(array1, 5);
	assert(list.GetLast() == array1[4]);
}

void Test_of_GetFirst_LinkedListSmart()
{
	LinkedListSmart<int>list(array1, 5);
	assert(list.GetFirst() == array1[0]);
}

void Test_of_GetLength_LinkedListSmart()
{
	LinkedListSmart<int>list(array1, 5);
	assert(list.GetLength() == 5);
}

void Test_of_Get_LinkedListSmart()
{
	LinkedListSmart<int>list(array1, 5);
	for (int i = 0; i != list.GetLength(); i++)
	{
		assert(list.Get(i) == array1[i]);
	}
}

void Test_of_GetSubList_LinkedListSmart()
{
	LinkedListSmart<int>list(array1, 5);

	for (int i = 0; i != 5; i++)
	{
		for (int j = i + 1; j != 5; j++)
		{
			LinkedListSmart<int> sub = *(list.GetSubsequence(i, j));
			assert(sub.GetLength() == j - i + 1);
			for (int x = i; x < j; x++)
			{

				assert(array1[x] == sub.Get(x - i));
			}
		}
	}
}

void Test_of_Append_LinkedListSmart()
{
	LinkedListSmart<int>list(array1, 5);

	list.Append(6);
	assert(list.GetLength() == 6);
	for (int i = 0; i != list.GetLength(); i++)
	{
		assert(list.Get(i) == array3[i]);
	}

}

void Test_of_Prepend_LinkedListSmart()
{
	LinkedListSmart<int>list(array1, 5);
	list.Prepend(0);
	assert(list.GetLength() == 6);
	for (int i = 0; i != list.GetLength(); i++)
	{
		assert(list.Get(i) == array4[i]);
	}
}

void Test_of_InsertAt_LinkedListSmart()
{
	LinkedListSmart<int> empty_list;
	empty_list.InsertAt(1, 0);
	assert(empty_list.GetLength() == 1);
	assert(empty_list.Get(0) == 1);

	LinkedListSmart<int>list1(array11, 1);
	list1.InsertAt(2, 0);
	assert(list1.GetLength() == 2);
	for (int i = 0; i != list1.GetLength(); i++)
	{
		assert(list1.Get(i) == array10[i]);
	}

	LinkedListSmart<int>list2(array11, 1);
	list2.InsertAt(2, 1);
	assert(list2.GetLength() == 2);
	for (int i = 0; i != list2.GetLength(); i++)
	{
		assert(list2.Get(i) == array9[i]);
	}

	LinkedListSmart<int>list(array1, 5);
	list.InsertAt(11, 0);
	assert(list.GetLength() == 6);
	for (int i = 0; i != list.GetLength(); i++)
	{
		assert(list.Get(i) == array7[i]);
	}

	list.InsertAt(22, list.GetLength());
	assert(list.GetLength() == 7);
	for (int i = 0; i != list.GetLength(); i++)
	{
		assert(list.Get(i) == array8[i]);
	}

	list.InsertAt(33, 2);
	assert(list.GetLength() == 8);
	for (int i = 0; i != list.GetLength(); i++)
	{
		assert(list.Get(i) == array5[i]);
	}


}

void Test_of_Concat_LinkedListSmart()
{
	UnqPtr<LinkedListSmart<int>>list(new LinkedListSmart<int>(array1, 5));
	UnqPtr<LinkedListSmart<int>>list1(new LinkedListSmart<int>(array1, 5));
	
	UnqPtr<LinkedListSmart<int>> con_list = list->Concat(std::move(list1));
	assert(con_list->GetLength() == 10);

	for (int i = 0; i != 10; i++)
	{
		assert(array6[i] == con_list->Get(i));
	}
}

//LinkedListSequence

void Test_of_GetLastLinkedListSequence()
{
	LinkedListSequence<int>list(array1, 5);
	assert(list.GetLast() == array1[4]);
}

void Test_of_GetFirst_LinkedListSequence()
{
	LinkedListSequence<int>list(array1, 5);
	assert(list.GetFirst() == array1[0]);
}

void Test_of_GetLength_LinkedListSequence()
{
	LinkedListSequence<int>list(array1, 5);
	assert(list.GetLength() == 5);
}

void Test_of_Get_LinkedListSequence()
{
	LinkedListSequence<int>list(array1, 5);
	for (int i = 0; i != list.GetLength(); i++)
	{
		assert(list.Get(i) == array1[i]);
	}
}

void Test_of_GetSubList_LinkedListSequence()
{
	LinkedListSequence<int>list(array1, 5);

	for (int i = 0; i != 5; i++)
	{
		for (int j = i + 1; j != 5; j++)
		{
			UnqPtr<Sequence<int>> sub = list.GetSubsequence(i, j);
			assert(sub->GetLength() == j - i + 1);
			for (int x = i; x < j; x++)
			{

				assert(array1[x] == sub->Get(x - i));
			}
		}
	}
}

void Test_of_Append_LinkedListSequence()
{
	LinkedListSequence<int>list(array1, 5);

	list.Append(6);
	assert(list.GetLength() == 6);
	for (int i = 0; i != list.GetLength(); i++)
	{
		assert(list.Get(i) == array3[i]);
	}

}

void Test_of_Prepend_LinkedListSequence()
{
	LinkedListSequence<int>list(array1, 5);
	list.Prepend(0);
	assert(list.GetLength() == 6);
	for (int i = 0; i != list.GetLength(); i++)
	{
		assert(list.Get(i) == array4[i]);
	}
}

void Test_of_InsertAt_LinkedListSequence()
{
	LinkedListSequence<int> empty_list;
	empty_list.InsertAt(1, 0);
	assert(empty_list.GetLength() == 1);
	assert(empty_list.Get(0) == 1);

	LinkedListSequence<int>list1(array11, 1);
	list1.InsertAt(2, 0);
	assert(list1.GetLength() == 2);
	for (int i = 0; i != list1.GetLength(); i++)
	{
		assert(list1.Get(i) == array10[i]);
	}

	LinkedListSequence<int>list2(array11, 1);
	list2.InsertAt(2, 1);
	assert(list2.GetLength() == 2);
	for (int i = 0; i != list2.GetLength(); i++)
	{
		assert(list2.Get(i) == array9[i]);
	}

	LinkedListSequence<int>list(array1, 5);
	list.InsertAt(11, 0);
	assert(list.GetLength() == 6);
	for (int i = 0; i != list.GetLength(); i++)
	{
		assert(list.Get(i) == array7[i]);
	}

	list.InsertAt(22, list.GetLength());
	assert(list.GetLength() == 7);
	for (int i = 0; i != list.GetLength(); i++)
	{
		assert(list.Get(i) == array8[i]);
	}

	list.InsertAt(33, 2);
	assert(list.GetLength() == 8);
	for (int i = 0; i != list.GetLength(); i++)
	{
		assert(list.Get(i) == array5[i]);
	}


}

void Test_of_ConcatLinkedListSequence()
{
	LinkedListSequence<int>list(array1, 5);
	LinkedListSequence<int>list5(array1, 5);
	UnqPtr<Sequence<int>> con_list = list.Concat(UnqPtr<Sequence<int>>(new LinkedListSequence<int>(std::move(list5))));

	//UnqPtr<Sequence<int>> con_list = list.Concat(&list);
	assert(con_list->GetLength() == 10);

	for (int i = 0; i != 10; i++)
	{
		assert(array6[i] == con_list->Get(i));
	}

	LinkedListSequence<int>list1;
	UnqPtr<Sequence<int>> con_list1 = list.Concat(UnqPtr<Sequence<int>>(new LinkedListSequence<int>(std::move(list1))));
	//UnqPtr<Sequence<int>> con_list1 = list.Concat(&list1);
	for (int i = 0; i != 5; i++)
	{
		assert(array1[i] == con_list1->Get(i));
	}
}

// ShrdPtr

void Test_of_ShrdPtrCreation()
{
	ShrdPtr<int> ptr(new int(10));
	assert(*ptr == 10);
}

void Test_of_ShrdPtrCopy()
{
	ShrdPtr<int> ptr1(new int(20));
	ShrdPtr<int> ptr2(ptr1);
	assert(*ptr2 == 20);
	assert(ptr1.use_count() == 2);
	assert(ptr2.use_count() == 2);
}

void Test_of_ShrdPtrAssignment()
{
	ShrdPtr<int> ptr1(new int(30));
	ShrdPtr<int> ptr2;
	ptr2 = ptr1;
	assert(*ptr2 == 30);
	assert(ptr1.use_count() == 2);
	assert(ptr2.use_count() == 2);
}

void Test_of_ShrdPtrNullAssignment()
{
	ShrdPtr<int> ptr(new int(40));
	ptr = nullptr;
	assert(ptr.use_count() == 0);
	assert(!ptr);
}

void Test_of_ShrdPtrReset()
{
	ShrdPtr<int> ptr(new int(50));
	ptr.reset();
	assert(ptr.use_count() == 0);
	assert(!ptr);
}

void Test_of_ShrdPtrRefCount()
{
	ShrdPtr<int> ptr1(new int(60));
	ShrdPtr<int> ptr2(ptr1);
	assert(ptr1.use_count() == 2);
	ptr2.reset();
	assert(ptr1.use_count() == 1);
}

// UnqPtr

void Test_of_UnqPtr_Creation()
{
	UnqPtr<int> ptr(new int(10));
	assert(*ptr == 10);
}

void Test_of_UnqPtr_Nullptr()
{
	UnqPtr<int> ptr;
	assert(!ptr);
}

void Test_of_UnqPtr_Reset()
{
	UnqPtr<int> ptr(new int(10));

	int* value2 = new int(20);
	ptr.reset(value2);
	assert(*ptr == 20);
}

void Test_of_UnqPtr_Release()
{
	UnqPtr<int> ptr(new int(10));
	ptr.release();
	assert(!ptr);
}

void Test_of_UnqPtr_MoveAssignment()
{
	UnqPtr<int> ptr1(new int(30));
	UnqPtr<int> ptr2;

	ptr2 = std::move(ptr1);
	assert(!ptr1);
	assert(*ptr2 == 30);
}

