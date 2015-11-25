#include "oset/oset.hpp"
#include <iostream>
using std::cout;
using std::endl;
using std::flush;
using std::string;

template<typename T>
bool ge(const T& a, const T& b){
    return a>=b;
}

bool str_insensitive_ge(const string & a, const string & b){
    for(int i=0;i<a.size() && i<b.size();i++){
        char ca = tolower(a[i]);
        char cb = tolower(b[i]);
        if(ca < cb) return false;
    }
    if(a.size() < b.size()) return false;
    return true;
}


void int_tests(){
    cout << "*****************************" <<endl;
    cout << "*       Tests for int       *" <<endl;
    cout << "*****************************" <<endl;

    //Pass comparator through constructor
    oset<int> S(ge<int>);     // empty set
    S += 3;     // now should contain 3

    cout << S[3] << " ";            // should print 1 (true) : 3 is in S
    S += 3;                         // should be a no-op
    cout << S[5] << endl;           // should print 0 (false) : 5 not in S

    (S += 5) += 7;
    print(S);                       // should print 3 5 7

    oset<int> T(3);                      // singleton
    print(T);              // should print 3

    oset<int> U(S);                      // copy of S
    oset<int> V(S);                      // copy of S

    oset<int> W(ge<int>); W = S;  print(W);      // 3 5 7

    S -= 4;                         // should be a no-op
    S -= 3;
    U -= 5;
    V -= 7;
    print(S);                       // 5 7
    print(U);                       // 3 7
    print(V);                       // 3 5

    oset<int> A;  ((A += 5) += 3) += 4;  print(A);       // 3 4 5
    oset<int> B;  ((B += 6) += 5) += 7;  print(B);       // 5 6 7

    oset<int> AuB(A);  AuB += B;  print(AuB);            // 3 4 5 6 7
    oset<int> AmB(A);  AmB -= B;  print(AmB);            // 3 4
    oset<int> AiB(A);  AiB *= B;  print(AiB);            // 5
}

void double_tests(){
    cout << "********************************" <<endl;
    cout << "*       Tests for double       *" <<endl;
    cout << "********************************" <<endl;
    oset<double> S(ge<double>);
    S += 3.3;     // now should contain 3

    cout << S[3.3] << " ";            // should print 1 (true) : 3 is in S
    S += 3.3;                         // should be a no-op
    cout << S[5.5] << endl;           // should print 0 (false) : 5 not in S

    (S += 5.5) += 7.7;
    print(S);                       // should print 3 5 7

    oset<double> T(3.0);                      // singleton
    print(T);              // should print 3

    oset<double> U(S, ge<double>);                      // copy of S
    oset<double> V(S);                      // copy of S

    oset<double> W; W = S;  print(W);      // 3 5 7

    S -= 4.4;                         // should be a no-op
    S -= 3.3;
    U -= 5.5;
    V -= 7.7;
    print(S);                       // 5 7
    print(U);                       // 3 7
    print(V);                       // 3 5

    oset<double> A;  ((A += 5.5) += 3.3) += 4.4;  print(A);       // 3 4 5
    oset<double> B;  ((B += 6.6) += 5.5) += 7.7;  print(B);       // 5 6 7

    oset<double> AuB(A);  AuB += B;  print(AuB);            // 3 4 5 6 7
    oset<double> AmB(A);  AmB -= B;  print(AmB);            // 3 4
    oset<double> AiB(A);  AiB *= B;  print(AiB);            // 5

}

void string_tests(){
    cout << "**********************************" <<endl;
    cout << "*        Tests for string        *" <<endl;
    cout << "**********************************" <<endl;
    oset<string> S(ge<string>);
    cout << "Case sensitive:" <<endl;
    S += "Hello";
    S += "hello";
    print(S); // should have both

    cout << "Case insensitive:" <<endl;
    oset<string> U(str_insensitive_ge);
    U += "Hello";
    U += "hello";
    print(U);// should only have one

    cout << endl;
    oset<string> A(str_insensitive_ge); ((A += "Apple") += "Pear") += "Watermelon"; print(A);
    oset<string> B; ((B += "Watermelon") += "strawberry") += "orange"; print(B);

    cout << endl;
    oset<string> AuB(A); AuB += B; print(AuB);
    oset<string> AmB(A);  AmB -= B;  print(AmB);
    oset<string> AiB(A);  AiB *= B;  print(AiB);
}

int main() {
    int_tests();
    double_tests();
    string_tests();
    return 0;
}
