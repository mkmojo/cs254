#include "oset/oset.hpp"
#include <iostream>
using std::cout;
using std::endl;
using std::flush;
using std::string;

template<typename T>
struct ge {
    bool operator()(const T &a, const T &b) const{
        return a >= b;
    }
};

struct str_insensitive_ge {
    bool operator()(const string & a, const string & b) const{
        for(int i=0;i<a.size() && i<b.size();i++){
            char ca = tolower(a[i]);
            char cb = tolower(b[i]);
            if(ca < cb) return false;
        }
        if(a.size() < b.size()) return false;
        return true;
    }
};


void int_tests(){
    cout << "*****************************" <<endl;
    cout << "*       Tests for int       *" <<endl;
    cout << "*****************************" <<endl;

    //Pass comparator through constructor
    oset<int, ge<int>> S;     // empty set
    S += 3;     // now should contain 3

    cout << S[3] << " ";            // should print 1 (true) : 3 is in S
    S += 3;                         // should be a no-op
    cout << S[5] << endl;           // should print 0 (false) : 5 not in S

    (S += 5) += 7;
    print(S);                       // should print 3 5 7

    oset<int, ge<int>> T(3);                      // singleton
    print(T);              // should print 3

    oset<int, ge<int>> U(S);                      // copy of S
    oset<int, ge<int>> V(S);                      // copy of S

    oset<int, ge<int>> W; W = S;  print(W);      // 3 5 7

    S -= 4;                         // should be a no-op
    S -= 3;
    U -= 5;
    V -= 7;
    print(S);                       // 5 7
    print(U);                       // 3 7
    print(V);                       // 3 5

    oset<int, ge<int>> A;  ((A += 5) += 3) += 4;  print(A);       // 3 4 5
    oset<int, ge<int>> B;  ((B += 6) += 5) += 7;  print(B);       // 5 6 7

    oset<int, ge<int>> AuB(A);  AuB += B;  print(AuB);            // 3 4 5 6 7
    oset<int, ge<int>> AmB(A);  AmB -= B;  print(AmB);            // 3 4
    oset<int, ge<int>> AiB(A);  AiB *= B;  print(AiB);            // 5
}

void double_tests(){
    cout << "********************************" <<endl;
    cout << "*       Tests for double       *" <<endl;
    cout << "********************************" <<endl;
    oset<double, ge<double>> S;
    S += 3.3;     // now should contain 3

    cout << S[3.3] << " ";            // should print 1 (true) : 3 is in S
    S += 3.3;                         // should be a no-op
    cout << S[5.5] << endl;           // should print 0 (false) : 5 not in S

    (S += 5.5) += 7.7;
    print(S);                       // should print 3 5 7

    oset<double, ge<double>> T(3.0);                      // singleton
    print(T);              // should print 3

    oset<double, ge<double>> U(S);                      // copy of S
    oset<double, ge<double>> V(S);                      // copy of S

    oset<double, ge<double>> W; W = S;  print(W);      // 3 5 7

    S -= 4.4;                         // should be a no-op
    S -= 3.3;
    U -= 5.5;
    V -= 7.7;
    print(S);                       // 5 7
    print(U);                       // 3 7
    print(V);                       // 3 5

    oset<double, ge<double>> A;  ((A += 5.5) += 3.3) += 4.4;  print(A);       // 3 4 5
    oset<double, ge<double>> B;  ((B += 6.6) += 5.5) += 7.7;  print(B);       // 5 6 7

    oset<double, ge<double>> AuB(A);  AuB += B;  print(AuB);            // 3 4 5 6 7
    oset<double, ge<double>> AmB(A);  AmB -= B;  print(AmB);            // 3 4
    oset<double, ge<double>> AiB(A);  AiB *= B;  print(AiB);            // 5

}

void string_tests(){
    cout << "**********************************" <<endl;
    cout << "*        Tests for string        *" <<endl;
    cout << "**********************************" <<endl;
    oset<string> S;
    cout << "Case sensitive:" <<endl;
    S += "Hello";
    S += "hello";
    print(S); // should have both

    cout << "Case insensitive:" <<endl;
    oset<string, str_insensitive_ge> U;
    U += "Hello";
    U += "hello";
    print(U);// should only have one

    cout << endl;
    oset<string, str_insensitive_ge> A; ((A += "Apple") += "Pear") += "Watermelon"; print(A);
    oset<string, str_insensitive_ge> B; ((B += "watermelon") += "strawberry") += "orange"; print(B);

    cout << endl;
    oset<string, str_insensitive_ge> AuB(A); AuB += B; print(AuB);
    oset<string, str_insensitive_ge> AmB(A);  AmB -= B;  print(AmB);
    oset<string, str_insensitive_ge> AiB(A);  AiB *= B;  print(AiB);
}

int main() {
    int_tests();
    double_tests();
    string_tests();
    return 0;
}
