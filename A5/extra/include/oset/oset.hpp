#ifndef OSET_HPP_
#define OSET_HPP_

#include <iostream>
#include <functional>
using std::cout;
using std::endl;
using std::function;

template<typename T, typename GE = std::greater_equal<T> >
class oset {
    public: //DEBUG, need to be private
    class node {
        public:
            const T val;
            node *next;
            node *prev;
            node() : val(), next(NULL), prev(NULL) { }
            node(T v) : val(v), next(NULL), prev(NULL) { }
    };
    node head;
    // NB: _not_ node*.  There's a dummy node here, with garbage val;
    // Existence of this node avoids several special cases in the
    // methods below.
    node beyond;
    // to simplify iterator.

    //--------------------------------------
    // Iterator support

    public:
    class iter {
        node *pos;          // node _before_ the one with this->operator*
        // constructor is private:
        iter(node* n) : pos(n) { }
        //qqiu 11/22/2015: should I have this template parameter <T>?
        friend class oset;      // so oset can call the (private) constructor
        public:   
        const T& operator*() {
            return pos->next->val;
        }
        // support forward iteration.  This is prefix version (++p).
        iter& operator++() {
            if (pos != NULL) pos = pos->next;
            return *this;
        }
        // and this is the postfix version (p++).
        // Note that it returns a copy, _not_ a reference.
        iter operator++(int) {
            iter rtn = *this;
            if (pos != NULL) pos = pos->next;
            return rtn;
        }
        bool operator==(iter other) {return pos->next == other.pos->next;}
        bool operator!=(iter other) {return pos->next != other.pos->next;}
    };

    class riter {
        node *pos;          // node _before_ the one with this->operator*
        // constructor is private:
        riter(node* n) : pos(n) { }
        friend class oset;      // so oset can call the (private) constructor
        public:   
        const T& operator*() {
            return pos->prev->val;
        }
        // support forward iteration.  This is prefix version (++p).
        riter& operator++() {
            if (pos != NULL) pos = pos->prev;
            return *this;
        }
        // and this is the postfix version (p++).
        // Note that it returns a copy, _not_ a reference.
        riter operator++(int) {
            riter rtn = *this;
            if (pos != NULL) pos = pos->prev;
            return rtn;
        }
        bool operator==(riter other) {return pos->prev == other.pos->prev;}
        bool operator!=(riter other) {return pos->prev != other.pos->prev;}
    };

    private:
    iter start;         // initialized in the constructors below
    iter finish;        // initialized in the constructors below
    riter rstart;
    riter rfinish;
    GE ge;

    public:
    iter begin() {
        return start;
    }
    iter end() {
        return finish;
    }

    riter rbegin(){
        return rstart;
    }

    riter rend() {
        return rfinish;
    }

    //--------------------------------------
    // Constructors and destructor

    bool eq(const T& a, const T& b) const{
        return ge(a, b) && ge(b, a);
    }

    // new empty set:
    oset() :  start(&head), finish(&beyond), rstart(&beyond), rfinish(&head), ge() {
        head.next = NULL;
        beyond.prev = NULL;
    }

    // new singleton set:
    oset(T v) :  start(&head), finish(&beyond),rstart(&beyond), rfinish(&head), ge() {
        node *n = new node(v);
        head.next = n;
        beyond.prev = n;
    }

    // copy constructor:
    oset(oset& other) : start(&head), finish(&beyond), rstart(&beyond), rfinish(&head), ge(){
        for(auto &&it : other){
            operator+=(it);
        }
    }

    private:
    void clear() {
        node *n = head.next;
        while (n) {
            node* t = n->next;
            delete n;
            n = t;
        }
        head.next = NULL;
        beyond.prev = NULL;
    }

    public:
    // destructor -- clean up nodes:
    ~oset() {
        clear();
    }
    // assignment
    oset& operator=(oset& other) {
        clear();
        operator+=(other);      // union (see below)
    }

    //--------------------------------------
    // Find, insert, and remove

    private:
    // Return pointer to last node with val < v
    //
    // *** THIS CODE IMPLICITLY REQUIRES A >= OPERATOR FOR THE SET
    // *** ELEMENT TYPE.  YOU NEED TO MAKE THAT EXPLICIT
    // *** (IN DIFFERENT WAYS IN DIFFERENT VERSIONS OF THE CODE).
    //
    node* find_prev(const T v) {
        node* p = &head;
        while (true) {
            if (p->next == NULL) return p;
            if (ge(p->next->val, v)) return p;
            p = p->next;
        }
    }

    public:
    // find -- return true iff present:
    bool operator[](const T v) {
        node* p = find_prev(v);
        return (p->next != NULL && eq(p->next->val,v));
    }

    // insert v if not already present; return ref to self
    oset& operator+=(const T v) {
        node* p = find_prev(v);
        if (p->next && !eq(p->next->val, v)) {
            node* n = new node(v);
            n->next = p->next;
            p->next->prev = n;
            p->next = n;
            if(p != &head)
                n->prev = p;
        }else if(p->next == NULL){
            //special case, do not have n->next point to beyond
            //because node beyond is not part of the list it is not
            //actual node

            node* n = new node(v);
            p->next = n;
            if(p != &head)
                n->prev = p;
            beyond.prev = n;
        }else{
        }
        return *this;
    }

    // remove v if present; return ref to self
    oset& operator-=(const T v) {
        node* p = find_prev(v);
        node* t = p->next;
        if( t != NULL && eq(p->next->val, v)){
            if ((p != &head) && t != beyond.prev) {
                // already present and in the middle
                p->next = t->next;
                t->next->prev = p;
                delete t;
            }else if(p == &head  && t != beyond.prev){
                //delete first element
                p->next = t->next;
                t->next->prev = NULL;
                delete t;
            }else if(p != &head && t == beyond.prev){
                //delete last element
                p->next = t->next;
                beyond.prev = p;
                delete t;
            }else{
                // t is the only element
                head.next = NULL;
                beyond.prev = NULL;
                delete t;
            }
        }
        return *this;
    }


    //--------------------------------------
    // Union, intersection and difference.
    // These are operator assignments, to simplify management of space:
    // programmer is forced to manage temporaries explicitly
    // (as illustrated in the code for intersection below).

    // Union.
    oset& operator+=(oset& other) {
        for (iter i = other.begin(); i != other.end(); ++i) {
            operator+=(*i);
        }
        return *this;
    }

    // Set difference.
    oset& operator-=(oset& other) {
        for (iter i = other.begin(); i != other.end(); ++i) {
            operator-=(*i);
        }
        return *this;
    }

    // Intersection.
    oset& operator*=(oset& other) {
        oset temp;      // empty
        for (iter i = begin(); i != end(); ++i) {
            if (other[*i]) temp+=(*i);
        }
        clear();
        operator+=(temp);   // union
        // NB: temp is destructed as we leave this scope
        return *this;
    }

    // Find the size of oset
    size_t size(){
        int count = 0;
        for(auto &&it : *this){
            count++;
        }
        return count;
    }

    bool empty(){
        return size() == 0;
    }
};


template<typename T, typename GE=std::greater_equal<T> >
void print(oset<T, GE>& OS) {
    using iter = typename oset<T, GE>::iter;
    for (iter i = OS.begin(); i != OS.end(); ++i) {
        cout << *i << " ";
    }
    cout << endl;
}

template<typename T, typename GE=std::greater_equal<T> >
void rprint(oset<T, GE>& OS) {
    using riter = typename oset<T, GE>::riter;
    for (riter i = OS.rbegin(); i != OS.rend(); ++i) {
        cout << *i << " ";
    }
    cout << endl;
}
#endif
