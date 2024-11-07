#pragma once
#include "LinkedListSmart.h"
#include "UnqPtr.h"
#include "Sequence.h"

template<typename T>
class LinkedListSequence : public Sequence<T>
{
private:
    UnqPtr<LinkedListSmart<T>> list;

    LinkedListSequence(UnqPtr<LinkedListSmart<T>>&& other) : list(std::move(other)) {}

    const UnqPtr<LinkedListSmart<T>>& GetLinkedList() const
    {
        return list;
    }

public:
    LinkedListSequence() : list(new LinkedListSmart<T>()) {}
    LinkedListSequence(const T* items, int count) : list(new LinkedListSmart<T>(items, count)) {}
    LinkedListSequence(const LinkedListSmart <T>& other) : list(new LinkedListSmart<T>(other)) {}

    size_t GetLength() const override
    {
        return list->GetLength();
    }

    T GetFirst() const override
    {
        return list->GetFirst();
    }

    T GetLast() const override
    {
        return list->GetLast();
    }

    T Get(int index) const override
    {
        return list->Get(index);
    }

    UnqPtr<Sequence<T>> GetSubsequence(int startIndex, int endIndex) const override
    {
        return UnqPtr<Sequence<T>>(new LinkedListSequence<T>(std::move(list->GetSubsequence(startIndex, endIndex))));
    }

    void Append(const T& item) override
    {
        list->Append(item);
    }

    void Prepend(const T& item) override
    {
        list->Prepend(item);
    }

    void InsertAt(const T& item, int index) override
    {
        list->InsertAt(item, index);
    }

    UnqPtr<Sequence<T>> Concat(const UnqPtr<Sequence<T>>& other) const override
    {
        UnqPtr<LinkedListSmart<T>> resultList = list->Concat(other->GetLinkedList());
        return UnqPtr<Sequence<T>>(new LinkedListSequence<T>(std::move(resultList)));
    }
};
