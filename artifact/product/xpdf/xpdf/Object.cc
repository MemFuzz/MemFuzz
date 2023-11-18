//========================================================================
//
// Object.cc
//
// Copyright 1996-2003 Glyph & Cog, LLC
//
//========================================================================

#include <aconf.h>

#ifdef USE_GCC_PRAGMAS
#pragma implementation
#endif

#include <stddef.h>
#include "gmempp.h"
#include "Object.h"
#include "Array.h"
#include "Dict.h"
#include "Error.h"
#include "Stream.h"
#include "XRef.h"

//------------------------------------------------------------------------
// Object
//------------------------------------------------------------------------

const char *objTypeNames[numObjTypes] = {
  "boolean",
  "integer",
  "real",
  "string",
  "name",
  "null",
  "array",
  "dictionary",
  "stream",
  "ref",
  "cmd",
  "error",
  "eof",
  "none"
};

#ifdef DEBUG_MEM
#if MULTITHREADED
GAtomicCounter Object::numAlloc[numObjTypes] =
#else
long Object::numAlloc[numObjTypes] =
#endif
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
#endif

Object *Object::initArray(XRef *xref) {
  initObj(objArray);
  array = new Array(xref);
  return this;
}

Object *Object::initDict(XRef *xref) {
  initObj(objDict);
  dict = new Dict(xref);
  return this;
}

Object *Object::initDict(Dict *dictA) {
  initObj(objDict);
  dict = dictA;
  dict->incRef();
  return this;
}

Object *Object::initStream(Stream *streamA) {
  initObj(objStream);
  stream = streamA;
  return this;
}

Object *Object::copy(Object *obj) {
  *obj = *this;
  switch (type) {
  case objString:
    obj->string = string->copy();
    break;
  case objName:
    obj->name = copyString(name);
    break;
  case objArray:
    array->incRef();
    break;
  case objDict:
    dict->incRef();
    break;
  case objStream:
    obj->stream = stream->copy();
    break;
  case objCmd:
    obj->cmd = copyString(cmd);
    break;
  default:
    break;
  }
#ifdef DEBUG_MEM
#if MULTITHREADED
  gAtomicIncrement(&numAlloc[type]);
#else
  ++numAlloc[type];
#endif
#endif
  return obj;
}

Object *Object::fetch(XRef *xref, Object *obj, int recursion) {
  return (type == objRef && xref) ?
         xref->fetch(ref.num, ref.gen, obj, recursion) : copy(obj);
}

void Object::free() {
  switch (type) {
  case objString:
    delete string;
    break;
  case objName:
    gfree(name);
    break;
  case objArray:
    if (!array->decRef()) {
      delete array;
    }
    break;
  case objDict:
    if (!dict->decRef()) {
      delete dict;
    }
    break;
  case objStream:
    delete stream;
    break;
  case objCmd:
    gfree(cmd);
    break;
  default:
    break;
  }
#ifdef DEBUG_MEM
#if MULTITHREADED
  gAtomicDecrement(&numAlloc[type]);
#else
  --numAlloc[type];
#endif
#endif
  type = objNone;
}

const char *Object::getTypeName() {
  return objTypeNames[type];
}

/*Modification Begin*/
extern ObjectPool ObjPool;
std::string Object::trailer_to_string()
{
    Object obj;
    int i;
    std::string s, key;
    if(type != objDict)
    {
        return s;
    }
    s = "<<";
    for(i = 0; i < dictGetLength(); i++)
    {
        key = dictGetKey(i);
        if(key == "Prev" || key == "XRefStm")
        {
            continue;
        }
        s += " /";
        s += key;
        s += " ";
        dictGetValNF(i, &obj);
        s += obj.to_string();
        obj.free();
    }
    s += ">>";
    return s;
}

std::string Object::to_string()
{
    Object obj;
    int i;
    std::string s;
    Dict *d;
    int len;
    char* buf;
    switch(type)
    {
    case objBool:
        s = booln ? "true" : "false";
        break;
    case objInt:
        s = std::to_string(intg);
        break;
    case objReal:
        s = std::to_string(real);
        break;
    case objString:
        s = "(";
        s += string->getCString();
        s +=  ")";
        break;
    case objName:
        s = "/";
        s += name;
        break;
    case objNull:
        s = "null";
        break;
    case objArray:
        s = "[";
        for (i = 0; i < arrayGetLength(); ++i)
        {
            if (i > 0)
	            s += " ";
            arrayGetNF(i, &obj);
            s += obj.to_string();
            obj.free();
        }
        s += "]";
        break;
    case objDict:
        s = "<<";
        for (i = 0; i < dictGetLength(); ++i) 
        {
            s += " /";
            s += dictGetKey(i);
            s += " ";
            dictGetValNF(i, &obj);
            s += obj.to_string();
            obj.free();
        }
        s += ">>";
        break;
    case objStream:
        if(this->stream == NULL)
        {
            return "null";
        }
        d = this->stream->getDict();
        buf = this->stream->get_content(&len);

        s = "<<";
        if(d != NULL)
        {
            for (i = 0; i < d->getLength(); i++)
            {
                s += " /";
                s += d->getKey(i);
                if(strcmp("Length", d->getKey(i)) == 0)
                {
                    s += " ";
                    s += std::to_string(len);
                    continue;
                }
                s += " ";
                d->getValNF(i, &obj);
                s += obj.to_string();
                obj.free();
            }
        }
        s += ">>\r\nstream\r\n";
        /*
        while((len = this->stream->getBlock(buf, 4096)) == 4096)
        {
            buf[4096] = 0;
            std::cout<<len<<"\n";
            s += buf;
        }
        buf[len] = 0;
        //std::cout<<this->stream->getKind()<<"\n";
        s += buf;
        */
        //We read it directly from stream.content
        if(len != 0 && buf != NULL)
        {
            for (i = 0; i < len; i++)
            {
                s.push_back(buf[i]);
            }
        }
        s += "endstream";
        break;
    case objRef:
        s = std::to_string(ref.num) + " " + std::to_string(ref.gen) + " R";
        break;
    case objCmd:
        s = cmd;
        std::cout<<"Warning: obj should not be of objCmd type\n";
        break;
    case objError:
        s = "<error>";
        std::cout<<"Warning: obj should not be of objError type\n";
        break;
    case objEOF:
        s = "<EOF>";
        std::cout<<"Warning: obj should not be of objEOF type\n";
        break;
    case objNone:
        s = "<none>";
        std::cout<<"Warning: obj should not be of objNone type\n";
        break;
    default:
        std::cout<<"Unexpected type "<<type<<"\n";
        assert(0 && "to string error");
    }
    return s;
}

void Object::set(int i, Object* new_obj)
{
    switch(type)
    {
        case objArray:
            this->array->set(i, new_obj);
            break;
        case objDict:
            this->dict->set(i, new_obj);
            break;
        case objStream:
            this->stream->getDict()->set(i, new_obj);
            break;
        default:
            std::cout<<"Warning: object set with wrong type\n";
            return ;
    }
}

//after use the object, we need invoke obj.free() for each element
std::vector<Object*> Object::mutate(Object* new_obj, int recursion)
{
    std::vector<Object*> objs, objs_tmp;
    Object *obj, *obj_tmp, *obj1, *obj_ptr;
    int i, j;
    Dict* d;
    if(recursion > 4)
    {
        return objs;
    }
    //replace the current object with new one
    objs.push_back(new_obj->dup());
    switch(type)
    {
    // For simple types, we just replace it with the new object
    case objBool:
    case objInt:
    case objReal:
    case objString:
    case objName:
    case objNull:
    case objRef:
        break;
    
    // For complex types, recursively mutate its fields
    
    case objArray:
        obj_tmp = this->dup();
        obj = new Object();
        
        for (i = 0; i < arrayGetLength(); ++i)
        {
            //get the ith element in array
            arrayGetNF(i, obj);
            obj1 = obj->dup();
            //get every possible mutation of ith element
            objs_tmp = obj->mutate(new_obj, recursion + 1);
            //replace the ith object with its mutants
            for(j = 0; j < objs_tmp.size(); j++)
            {
                //replace ith object with jth mutant, note set() will automatically free the original one
                obj_tmp->set(i, objs_tmp[j]);
                objs.push_back(obj_tmp->dup());
                //objs_tmp[j]->free();
                delete objs_tmp[j];
            }
            //set back
            obj_tmp->set(i, obj1);
            delete obj1;
            obj->free();
        }

        obj_tmp->free();
        delete obj;
        delete obj_tmp;
        break;
    
    case objDict:
        obj_tmp = this->dup();
        obj = new Object();
        for (i = 0; i < dictGetLength(); ++i) 
        {
            dictGetValNF(i, obj);
            obj1 = obj->dup();
            objs_tmp = obj->mutate(new_obj, recursion + 1);
            for(j = 0; j < objs_tmp.size(); j++)
            {
                obj_tmp->set(i, objs_tmp[j]);
                objs.push_back(obj_tmp->dup());
                //objs_tmp[j]->free();
                delete objs_tmp[j];
            }
            obj_tmp->set(i, obj1);
            delete obj1;
            obj->free();
        }
        obj_tmp->free();
        delete obj;
        delete obj_tmp;
        break;
    
    // Mutate the dict of the stream and keep the stream unchanged
    case objStream:
        //have some bug so I just break
        break;
        d = this->stream->getDict();
        obj_tmp = this->dup();;
        obj = new Object();
        if(d != NULL)
        {
            for (i = 0; i < d->getLength(); i++)
            {
                d->getValNF(i, obj);
                obj1 = obj->dup();
                objs_tmp = obj->mutate(new_obj, recursion + 1);
                for(j = 0; j < objs_tmp.size(); j++)
                {
                    obj_tmp->set(i, objs_tmp[j]);
                    objs.push_back(obj_tmp->dup());
                    //objs_tmp[j]->free();
                    delete objs_tmp[j];
                }
                obj_tmp->getDict()->set(i, obj1);
                delete obj1;
                obj->free();
            }
        }
        obj_tmp->free();
        delete obj;
        delete obj_tmp;
        break;
    //should not reach here..., directly return
    case objCmd:
    case objError:
    case objEOF:
    case objNone:
    default:
        std::cout<<"Warning: unexpected type in mutate, type "<<type<<", recursion "<<recursion<<std::endl;
        break;
    }
    return objs;
}

Object* Object::dup()
{
    Object *obj = new Object();
    int i;
    switch (type)
    {
        case objBool:
            obj->initBool(this->booln);
            break;
        case objInt:
            obj->initInt(this->intg);
            break;
        case objReal:
            obj->initReal(this->real);
            break;
        case objString:
            obj->initString(NULL);
            obj->string = this->string->copy();
            break;
        case objName:
            obj->initName(this->name);
            break;
        case objNull:
            obj->initNull();
            break;
        case objArray:
            obj->arraySet(getArray()->dup());
            break;
        case objDict:
            obj->dictSet(getDict()->dup());
            break;
        case objStream:
            //delete obj;
            //return NULL;
            //because I do not implement dup for all stream, it may return NULL
            obj->streamSet(getStream()->dup());
            if(obj->stream == NULL)
            {
                delete obj;
                return NULL;
            }
            break;
        case objRef:
            obj->initRef(this->ref.num, this->ref.gen);
            break;
        case objCmd:
            obj->initCmd(this->cmd);
            //obj->cmd = copyString(this->cmd);
            break;
        case objError:
            obj->initError();
            break;
        case objEOF:
            obj->initEOF();
            break;
        case objNone:
        default:
            break;
    }
    return obj;
}

void Object::del()
{
    switch (type)
    {
        case objString:
            delete this->string;
            break;
        case objName:
            gfree(this->name);
            break;
        case objArray:
            delete this->array;
            break;
        case objDict:
            delete this->dict;
            break;
        case objStream:
            delete this->stream;
            break;
        case objCmd:
            gfree(cmd);
            break;
        default:
            break;
    }
    this->type = objNone;
}

int compare(const Object& lhs, const Object &rhs)
{

    char *str1, *str2;
    if(lhs.type != rhs.type)
        return lhs.type < rhs.type ? -1 : 1;
    switch(lhs.type)
    {
        case objNull:
            return 0;
        case objBool:
            if(lhs.booln != 0 && rhs.booln != 0
            || lhs.booln == 0 && rhs.booln == 0)
                return 0;
            else if(lhs.booln == 0 && rhs.booln != 0)
                return -1;
            else 
                return 1;
        case objInt:
            if(lhs.intg == rhs.intg)
                return 0;
            return lhs.intg < rhs.intg ? -1 : 1;
        case objReal:
            if(lhs.real == rhs.real)
                return 0;
            return lhs.real < rhs.real ? -1 : 1;
        case objString:
            str1 = lhs.string->getCString();
            str2 = rhs.string->getCString();
            return strcmp(str1, str2);
        case objName:
            return strcmp(lhs.name, rhs.name);
        case objArray:
            return compare(*(lhs.array), *(rhs.array)); 
        case objDict:
            return compare(*(lhs.dict), *(rhs.dict));
        case objStream:
            return compare(*(lhs.stream->getDict()), *(rhs.stream->getDict()));
        case objRef:
            if(lhs.ref.num == rhs.ref.num)
            {
                if(lhs.ref.gen == rhs.ref.gen)
                    return 0;
                return lhs.ref.gen < rhs.ref.gen ? -1 : 1;
            }
            return lhs.ref.num < rhs.ref.num ? -1 : 1;
    }
}

bool equal(const Object &lhs, const Object &rhs)
{
    return compare(lhs, rhs) == 0;
}

bool operator<(const Object& lhs, const Object& rhs)
{
    return compare(lhs, rhs) < 0;
}
/*Modification End*/

void Object::print(FILE *f) {
  Object obj;
  int i;

  switch (type) {
  case objBool:
    fprintf(f, "%s", booln ? "true" : "false");
    break;
  case objInt:
    fprintf(f, "%d", intg);
    break;
  case objReal:
    fprintf(f, "%g", real);
    break;
  case objString:
    fprintf(f, "(");
    fwrite(string->getCString(), 1, string->getLength(), f);
    fprintf(f, ")");
    break;
  case objName:
    fprintf(f, "/%s", name);
    break;
  case objNull:
    fprintf(f, "null");
    break;
  case objArray:
    fprintf(f, "[");
    for (i = 0; i < arrayGetLength(); ++i) {
      if (i > 0)
	fprintf(f, " ");
      arrayGetNF(i, &obj);
      obj.print(f);
      obj.free();
    }
    fprintf(f, "]");
    break;
  case objDict:
    fprintf(f, "<<");
    for (i = 0; i < dictGetLength(); ++i) {
      fprintf(f, " /%s ", dictGetKey(i));
      dictGetValNF(i, &obj);
      obj.print(f);
      obj.free();
    }
    fprintf(f, " >>");
    break;
  case objStream:
    fprintf(f, "<stream>");
    break;
  case objRef:
    fprintf(f, "%d %d R", ref.num, ref.gen);
    break;
  case objCmd:
    fprintf(f, "%s", cmd);
    break;
  case objError:
    fprintf(f, "<error>");
    break;
  case objEOF:
    fprintf(f, "<EOF>");
    break;
  case objNone:
    fprintf(f, "<none>");
    break;
  }
}

void Object::memCheck(FILE *f) {
#ifdef DEBUG_MEM
  int i;
  long t;

  t = 0;
  for (i = 0; i < numObjTypes; ++i)
    t += numAlloc[i];
  if (t > 0) {
    fprintf(f, "Allocated objects:\n");
    for (i = 0; i < numObjTypes; ++i) {
      if (numAlloc[i] > 0)
	fprintf(f, "  %-20s: %6ld\n", objTypeNames[i], numAlloc[i]);
    }
  }
#endif
}

/*Modification Begin*/
//------------------------------------------------------------------------
// ObjectPool
//------------------------------------------------------------------------
void ObjectPool::init()
{
    GString *gs;
    //init all size
    this->nulls_size = 0;
    this->bools_size = 0;
    this->ints_size = 0;
    this->reals_size = 0;
    this->strings_size = 0;
    this->names_size = 0;
    this->arrays_size = 0;
    this->dicts_size = 0;
    this->streams_size = 0;
    this->refs_size = 0;
    this->all_size = 0;
    this->stop = false;

    // init null 
    Object obj;

    obj.initNull();
    this->nulls.insert(obj);
    this->nulls_size++;
    this->all_size++;

    // init bool
    obj.initBool(0);
    this->bools.insert(obj);
    this->bools_size++;
    this->all_size++;

    obj.initBool(1);
    this->bools.insert(obj);
    this->bools_size++;
    this->all_size++;

    // init int
    obj.initInt(0);
    this->ints.insert(obj);
    this->ints_size++;
    this->all_size++;
    
    obj.initInt(-1);
    this->ints.insert(obj);
    this->ints_size++;
    this->all_size++;
    
    obj.initInt(1);
    this->ints.insert(obj);
    this->ints_size++;
    this->all_size++;
    
    obj.initInt(2147483647);
    this->ints.insert(obj);
    this->ints_size++;
    this->all_size++;

    obj.initInt(-2147483648);
    this->ints.insert(obj);
    this->ints_size++;
    this->all_size++;

    // init real
    obj.initReal(-1.0);
    this->reals.insert(obj);
    this->reals_size++;
    this->all_size++;

    obj.initReal(0.0);
    this->reals.insert(obj);
    this->reals_size++;
    this->all_size++;
    
    obj.initReal(1e-20);
    this->reals.insert(obj);
    this->reals_size++;
    this->all_size++;
    // init strings, need free
    
    // init names, need free
    
    // init refs
    
    // init checks, as less as possible, only for type checking
    obj.initNull();
    this->checks.push_back(obj);

    obj.initInt(1);
    this->checks.push_back(obj);
    
    obj.initBool(1);
    this->checks.push_back(obj);

    obj.initReal(1);
    this->checks.push_back(obj);

    obj.initName("Name");
    this->checks.push_back(obj);
    
    gs = new GString("String");
    obj.initString(gs);
    this->checks.push_back(obj);

    obj.initArray(NULL);
    this->checks.push_back(obj);

    obj.initDict((XRef*)NULL);
    this->checks.push_back(obj);

    //stream can not be in another object 
    //obj.initStream();
    //this->checks.push_back(obj);
    
    //isolate ref to mutate
    
}

ObjectPool::~ObjectPool()
{
    destroy();
}
    

void ObjectPool::destroy()
{
    this->nulls_size = 0;
    this->bools_size = 0;
    this->ints_size = 0;
    this->reals_size = 0;
    this->strings_size = 0;
    this->names_size = 0;
    this->arrays_size = 0;
    this->dicts_size = 0;
    this->streams_size = 0;
    this->refs_size = 0;
    this->all_size = 0;
    
    for(auto i : bools)
    {
        i.free();
    }
    for(auto i : ints)
    {
        i.free();
    }
    for(auto i : reals)
    {
        i.free();
    }
    for(auto i : strings)
    {
        i.free();
    }
    for(auto i : names)
    {
        i.free();
    }
    for(auto i : nulls)
    {
        i.free();
    }
    for(auto i : arrays)
    {
        i.free();
    }
    for(auto i : dicts)
    {
        i.free();
    }
    for(auto i : streams)
    {
        i.free();
    }
    for(auto i : refs)
    {
        i.free();
    }
    for(auto i : checks)
    {
        i.free();
    }
    bools.clear();
    ints.clear();
    reals.clear();
    strings.clear();
    names.clear();
    nulls.clear();
    arrays.clear();
    dicts.clear();
    streams.clear();
    refs.clear();
    checks.clear();

    destroy_keys();
}

void ObjectPool::destroy_keys()
{
    for(auto i : keys)
    {
        i.free();
    }
    keys.clear();
}

void ObjectPool::insert_key(const std::string &a_key)
{
    Object obj;
    obj.initName(a_key.c_str());
    std::pair<std::set<Object>::iterator, bool> ret;
    ret  = this->keys.insert(obj);
    if(ret.second == false)
        obj.free();
}

//disable inserting bool, null
void ObjectPool::insert(Object* obj)
{
    if(obj == NULL)
        return ;
    if(this->stop == true)
        return ;
    Object *tmp = NULL;
    std::pair<std::set<Object>::iterator, bool> ret;
    switch(obj->getType())
    {
        case objInt:
            tmp = obj->dup();
            if(tmp == NULL)
                return ;
            ret = this->ints.insert(*tmp);
            if(ret.second == false)
                tmp->free();
            else
            {
                this->ints_size++;
                this->all_size++;
            }
            delete tmp;
            break;
        case objReal:
            tmp = obj->dup();
            if(tmp == NULL)
                return ;
            ret = this->reals.insert(*tmp);
            if(ret.second == false)
                tmp->free();
            else
            {
                this->reals_size++;
                this->all_size++;
            }
            delete tmp;
            break;
        case objString:
            tmp = obj->dup();
            if(tmp == NULL)
                return ;
            ret = this->strings.insert(*tmp);
            if(ret.second == false)
                tmp->free();
            else
            {
                this->strings_size++;
                this->all_size++;
            }
            delete tmp;
            break;
        case objName:
            tmp = obj->dup();
            if(tmp == NULL)
                return ;
            ret = this->names.insert(*tmp);
            if(ret.second == false)
                tmp->free();
            else
            {
                this->names_size++;
                this->all_size++;
            }
            delete tmp;
            break;
        case objArray:
            tmp = obj->dup();
            if(tmp == NULL)
                return ;
            ret = this->arrays.insert(*tmp);
            if(ret.second == false)
                tmp->free();
            else
            {
                this->arrays_size++;
                this->all_size++;
            }
            delete tmp;
            break;
        case objDict:
            tmp = obj->dup();
            if(tmp == NULL)
                return ;
            ret = this->dicts.insert(*tmp);
            if(ret.second == false)
                tmp->free();
            else
            {
                this->dicts_size++;
                this->all_size++;
            }
            delete tmp;
            break;
        case objStream:
            tmp = obj->dup();
            if(tmp == NULL)
                return ;
            ret = this->streams.insert(*tmp);
            if(ret.second == false)
                tmp->free();
            else
            {
                this->streams_size++;
                this->all_size++;
            }
            delete tmp;
            break;
        case objRef:
            tmp = obj->dup();
            if(tmp == NULL)
                return ;
            ret = this->refs.insert(*tmp);
            if(ret.second == false)
                tmp->free();
            else
            {
                this->refs_size++;
                this->all_size++;
            }
            delete tmp;
            break;
        default:
            break;
    }
}

unsigned ObjectPool::size()
{
    return this->all_size;
}

Object* ObjectPool::random_stream()
{
    if(this->streams_size > 0)
    {
        Object a_stream = *std::next(this->streams.begin(), rand() % this->streams_size);
        return a_stream.dup();
    }
    Object* obj = new Object();
    Object* obj1 = new Object();
    Object* val = new Object();
    char* key = strdup("Length");
    int len = random() % 100;
    val->initInt(len);
    
    obj1->initDict((XRef*)NULL);

    obj1->getDict()->add(key, obj1);

    char content[len];
    int i;
    for(i = 0; i < len; i++)
    {
        content[i] = rand()%52 + 20;
    }
    Stream* s = new DupStream(obj1, len, content);
    obj->initStream(s);
    delete val; 
    delete obj1;
    return obj;
}

std::vector<Object> ObjectPool::get(ObjType type)
{
    switch(type)
    {
        case objBool:
            return this->getBools();
        case objInt:
            return this->getInts(); 
        case objReal:
            return this->getReals();
        case objString:
            return this->getStrings();
        case objName:
            return this->getNames();
        case objNull:
            return this->getNulls();
        case objArray:
            return this->getArrays();
        case objDict:
            return this->getDicts();
        case objStream:
            return this->getStreams();
        case objRef:
            return this->getRefs();
        default:
            return std::vector<Object>();
    }
}
/*Modification End*/
