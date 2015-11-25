#ifndef OSET_HPP_
#define OSET_HPP_

#include <iostream>
#include <functional>
using std::cout;
using std::endl;
using std::function;

template<typename T>
class oset {
    class node {
     public:
        const T val;
        node *next;
        node() : val(), next(NULL) {}
        node(T v) : val(v), next(NULL) { }
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

 private:
    iter start;         // initialized in the constructors below
    iter finish;        // initialized in the constructors below

    bool(*ge)(const T&, const T&);

 public:
    iter begin() {
        return start;
    }
    iter end() {
        return finish;
    }

    //--------------------------------------
    // Constructors and destructor
    static bool default_ge(const T& a, const T& b){
        return a >= b;
    }

    bool default_eq(const T& a, const T&b){
        return default_ge(a, b) && default_ge(b, a);
    }

    bool eq(const T& a, const T& b){
        return ge(a, b) && ge(b, a);
    }

    // new empty set:
    oset( bool(*op_ge)(const T&, const T&)=oset::default_ge)
        :  start(&head), finish(&beyond), ge(op_ge) {
        head.next = NULL;
    }

    // new singleton set:
    oset(T v, bool(*op_ge)(const T&, const T&)=oset::default_ge)
        :  start(&head), finish(&beyond), ge(op_ge){
        head.next = new node(v);
    }

    // copy constructor:
    oset(oset& other, bool(*op_ge)(const T&, const T&)=oset::default_ge)
        : start(&head), finish(&beyond), ge(op_ge){
        node *o = other.head.next;
        node *n = &head;
        while (o) {
            n->next = new node(o->val);
            o = o->next;
            n = n->next;
        }
        n->next = NULL;
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
        if (p->next == NULL || !eq(p->next->val, v)) {
            node* n = new node(v);
            n->next = p->next;
            p->next = n;
        }
        return *this;
    }

    // remove v if present; return ref to self
    oset& operator-=(const T v) {
        node* p = find_prev(v);
        node* t;
        if ((t = p->next) != NULL && eq(p->next->val, v)) {
            // already present
            p->next = t->next;
            delete t;
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
        if(this->ge == other.ge){
            //Same comparator operation
            cout << "DEBUG same operator, use O(N)." << endl;

            if(other.begin() == other.end()) return *this;
            //qqiu 11/22/2015: why I cannot return other as the new reference?
            //if(this->begin() == this->end()) return other;
            node* p = find_prev(*(other.begin()));
            for(iter it = other.begin(); it != other.end(); it++){
                // go to the next node whose val < *it
                while(p->next && (!ge(p->next->val, *it))){
                    p = p->next;
                }

                if(p->next == NULL && it != other.end()){
                    node* new_node = new node(*it);
                    p->next = new_node;
                } else if(p->next && (ge(p->next->val, *it) && !eq(p->next->val, *it) )){
                    node* p_nxt = p->next;
                    node* new_node = new node(*it);
                    p->next = new_node;
                    new_node->next=p_nxt;
                }
            }
            return *this;
        }else{
            cout << "DEBUG _NOT_ same operator, use O(N^2)" << endl;
            //Not the same comparator, use O(N^2) version
            for (iter i = other.begin(); i != other.end(); ++i) {
                operator+=(*i);
            }
            return *this; 
        }
    }

    // Set difference.
    oset& operator-=(oset& other) {
        if(this->ge == other.ge){
            //have same comparator, use O(N) version
            cout << "DEBUG same operator, use O(N)." << endl;
            if(other.begin() == other.end()) return *this;
            if(this->begin() == this->end()) return *this;

            node* p = find_prev(*(other.begin()));
            for(iter it = other.begin(); it != other.end(); it++){
                while(p->next && !ge(p->next->val, *it))
                    p = p->next;
                if(p->next == NULL){
                    return *this;
                } else if(p->next && eq(*it, p->next->val)){
                    node* p_nxt = p->next;
                    p->next = p_nxt->next;
                    delete p_nxt;
                }
            }
            return *this;
        }else{
            cout << "DEBUG _NOT_ same operator, use O(N^2)." << endl;
            for (iter i = other.begin(); i != other.end(); ++i) {
                operator-=(*i);
            }
            return *this;
        }
    }

    // Intersection.
    oset& operator*=(oset& other) {
        if(this->ge == other.ge){
            cout << "DEBUG same operator, use O(N)." << endl;
            if(other.begin() == other.end()) {
                clear();
                return *this;
            }
            if(this->begin() == this->end()) return *this;
            node *ans, *q;
            //dummy node for ans array
            q = ans = new node;

            node* p = find_prev(*(other.begin()));
            for(iter it = other.begin(); it != other.end(); it++){
                while(p->next && !ge(p->next->val, *it))
                    p = p->next;
                if(p->next && eq(*it, p->next->val)){
                    q->next = new node(*it);
                    q = q->next;
                }
            }
            clear();
            (&head)->next = ans->next;
            delete ans;
            return *this;
        }else{
            cout << "DEBUG _NOT_ same operator, use O(N^2)." << endl;
            oset temp;      // empty
            for (iter i = begin(); i != end(); ++i) {
                if (other[*i]) temp+=(*i);
            }
            clear();
            operator+=(temp);   // union
            // NB: temp is destructed as we leave this scope
            return *this;
        }
    }
};


template<typename T>
void print(oset<T>& OS) {
    using iter = typename oset<T>::iter;
    for (iter i = OS.begin(); i != OS.end(); ++i) {
        cout << *i << " ";
    }
    cout << endl;
}

#endif
