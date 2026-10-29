#pragma once
#ifndef UNO_INTERFACES_IDECK_HPP
#define UNO_INTERFACES_IDECK_HPP

#include "ICard.hpp"

class IDeck {
    public:
    virtual ~IDeck() = default;
    virtual int size() const = 0;
    //virtual const ICard& operator[](int index) const = 0;

    virtual void shuffle() = 0;
    //virtual void swap(IDeck& other) = 0;

    //virtual void move(IDeck& other,int destination=-1) = 0;
    //virtual void move(IDeck& other,int origin, int destination=-1) = 0;
};

#endif // UNO_INTERFACES_IDECK_HPP
