//========================================================================
//
// Array.cc
//
// Copyright 1996-2003 Glyph & Cog, LLC
//
//========================================================================

#include <aconf.h>

#ifdef USE_GCC_PRAGMAS
#pragma implementation
#endif

#include <stdlib.h>
#include <stddef.h>
#include "gmem.h"
#include "gmempp.h"
#include "Object.h"
#include "Array.h"

//------------------------------------------------------------------------
// Array
//------------------------------------------------------------------------

Array::Array(XRef *xrefA) {
  xref = xrefA;
  elems = NULL;
  size = length = 0;
  ref = 1;
}

Array::~Array() {
  int i;

  for (i = 0; i < length; ++i)
    elems[i].free();
  gfree(elems);
}

void Array::add(Object *elem) {
  if (length == size) {
    if (length == 0) {
      size = 8;
    } else {
      size *= 2;
    }
    elems = (Object *)greallocn(elems, size, sizeof(Object));
  }
  elems[length] = *elem;
  ++length;
}

Object *Array::get(int i, Object *obj, int recursion) {
  if (i < 0 || i >= length) {
#ifdef DEBUG_MEM
    abort();
#else
    return obj->initNull();
#endif
  }
  return elems[i].fetch(xref, obj, recursion);
}

Object *Array::getNF(int i, Object *obj) {
  if (i < 0 || i >= length) {
#ifdef DEBUG_MEM
    abort();
#else
    return obj->initNull();
#endif
  }
  return elems[i].copy(obj);
}

/*Modification Begin*/
void Array::insert(int i, Object *elem) 
{
  if(i > this->length || i < 0)
    i = this->length;
  if (length == size) {
    if (length == 0) {
      size = 8;
    } else {
      size *= 2;
    }
    elems = (Object *)greallocn(elems, size, sizeof(Object));
  }
  int j;
  for(j = length - 1; j >= i; j--)
  {
    elems[j + 1] = elems[j];
  }
  elems[i] = *elem;
  ++length;
}

Object* Array::getPointer(int i)
{
    if(i >= this->length)
        return NULL;
    return &this->elems[i];
}

Object* Array::getDup(int i)
{
  if(i >= this->length)
    return NULL;
  return this->elems[i].dup();
}

void Array::remove(int i)
{
    if(i >= this->length || i < 0)
      return ;
    int j;
    Object obj = elems[i];
    for(j = i; j < length - 1; j++)
    {
      elems[j] = elems[j + 1];
    }
    obj.free();
    length--;
}

Array* Array::dup()
{
    int i;
    Object val;
    Object *tmp;
    Array *arr = new Array((XRef*) NULL);
    
    for(i = 0; i < getLength(); i++)
    {
        getNF(i, &val);
        tmp = val.dup();
        arr->add(tmp);
        delete tmp;
        val.free();
    }
    return arr;
}

int compare(const Array& lhs, const Array& rhs)
{
    int i;
    int val;
    if(lhs.length != rhs.length)
        return lhs.length < rhs.length ? -1 : 1;
    for(i = 0; i < lhs.length; i++)
    {
        val = compare(lhs.elems[i], rhs.elems[i]);
        if(val == 0)
            continue;
        else
            return val;
    }
    return 0;
}

bool equal(const Array& lhs, const Array& rhs)
{
    return compare(lhs, rhs) == 0;
}

bool operator<(const Array& lhs, const Array& rhs)
{
    return compare(lhs, rhs) < 0;
}
    
/*Modification End*/
