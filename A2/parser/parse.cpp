/* Complete recursive descent parser for the calculator language.
   Builds on figure 2.17.  Prints a trace of productions predicted and
   tokens matched.  Does no error recovery: prints "syntax error" and
   dies on invalid input.
   */

#include "stdio.h"
#include "stdlib.h"
#include "iostream"
#include "map"
#include "set"

#include "scan.h"

using namespace std;

const char* names[] = {
    "equal", "n_equal", "less_than", "greater_than", "less_equal", "greater_equal", 
    "while", "if", "end",  "read", "write", "id", "literal", "gets",
    "add", "sub", "mul", "div", "lparen", "rparen", "eof"};

map<string, set<token> > first_sets; 
map<string, set<token> > follow_sets; 
map<string, bool> EPS;

static token input_token;

struct syntax_error{
    string err_orig;
    syntax_error (){}
    syntax_error(string orig):err_orig(orig){}
};

bool isInSet(token t, set<token> given_set){
    if(given_set.find(t) != given_set.end ()) return true;
    else return false;
}

void init_follow_sets (){
    token follow_stmt_list[] = {t_eof, t_end};
    follow_sets["stmt_list"] = (set<token> (follow_stmt_list, follow_stmt_list + 2));

    token follow_stmt[] = {t_id, t_read, t_write, t_if, t_while, t_eof };
    follow_sets["stmt"] = (set<token> (follow_stmt, follow_stmt + sizeof(follow_stmt)/sizeof(token)));

    token follow_expr[] = {t_equal, t_nequal, t_lt, t_gt, t_le, t_ge, t_rparen};
    follow_sets["expr"] = (set<token> (follow_expr, follow_expr + 7));

    token follow_cond[] = {t_id, t_read, t_write, t_if, t_while, t_end};
    follow_sets["cond"] = (set<token> (follow_cond, follow_cond + 6));
}

//TODO:
//code up aux function make_set
void init_first_sets (){
    token first_stmt_list[] = {t_id, t_read, t_write, t_if, t_while};
    first_sets["stmt_list"] = (set<token> (first_stmt_list, first_stmt_list + 5));

    token first_stmt[] = {t_id, t_read, t_write, t_if, t_while};
    first_sets["stmt"] = (set<token> (first_stmt, first_stmt + 5));

    token first_expr[] = {t_id, t_lparen, t_literal};
    first_sets["expr"] = (set<token> (first_expr, first_expr + 3));

    token first_cond[] = {t_id, t_lparen, t_literal};
    first_sets["cond"] = (set<token> (first_cond, first_cond + 3));
}

void init_EPS (){
    EPS["stmt_list"] = true;
}

void match (token expected) {
    if (input_token == expected) {
        cout << "matched " <<  names[input_token];
        if (input_token == t_id || input_token == t_literal)
            cout << ": " << token_image; 
        cout << endl;
        input_token = scan ();
    }else{
        throw syntax_error("From match");
    }
}

void program ();
void stmt_list (const set<token>&);
void stmt (const set<token>&);
void cond (const set<token>&);
void expr (const set<token>&);
void term_tail (const set<token>&);
void term (const set<token>&);
void factor_tail (const set<token>&);
void factor (const set<token>&);
void add_op ();
void mul_op ();
void r_op ();


void program () {
    try{
        switch (input_token) {
            case t_id:
            case t_read:
            case t_write:
            case t_if:
            case t_while:
            case t_eof:
                cout << "predict program --> stmt_list eof" << endl;
                stmt_list (follow_sets["stmt_list"]);
                match (t_eof);
                break;
            default: 
                throw syntax_error("From program");
        }
    }
    catch(const struct syntax_error &e){
        cout << "Syntax error ";
        cout <<  e.err_orig << endl;
    }
}

void stmt_list (const set<token> &follow_set) {
    switch (input_token) {
        case t_id:
        case t_read:
        case t_write:
        case t_if:
        case t_while:
            cout << "predict stmt_list --> stmt stmt_list" << endl;
            stmt ( follow_sets["stmt"] );
            stmt_list (follow_set);
            break;
        case t_eof:
        case t_end:
            cout << "predict stmt_list --> epsilon" << endl;
            break;          /*  epsilon production */
        default: 
            throw syntax_error("From stmt_list");
    }
}

void stmt (const set<token>& follow_set) {
    try{
        switch (input_token) {
            case t_id:
                cout << "predict stmt --> id gets expr" << endl;
                match (t_id);
                match (t_gets);
                expr (follow_set);
                break;
            case t_read:
                cout << "predict stmt --> read id" << endl;
                match (t_read);
                match (t_id);
                break;
            case t_write:
                cout << "predict stmt --> write expr" << endl;
                match (t_write);
                expr (follow_set);
                break;
            case t_if:
                cout << "predict stmt --> if cond stmt_list end" << endl;
                match (t_if);
                cond ( follow_sets["cond"] );
                stmt_list (follow_set);
                match (t_end);
                break;
            case t_while:
                cout << "predict stmt --> while cond stmt_list end" << endl;
                match (t_while);
                cond ( follow_sets["cond"]);
                stmt_list (follow_set);
                match (t_end);
                break;
            case t_lparen:
            case t_literal:
            case t_add:
            case t_mul:
            case t_eof:
                cout << "predict stmt --> epsilon" << endl;
                return;
            default:
                throw syntax_error ();
        }
    } catch (const struct syntax_error &e) {
        cout << "Recover statement: " << e.err_orig << endl;
        do{
            if (isInSet(input_token, first_sets["stmt"])){
                //TODO add local follow set
                stmt (follow_set);
                return;
            }else if(isInSet(input_token, follow_sets["stmt"])){
                return;
            }
        }while(input_token = scan ());
    }
}

// non-terminal for condition
// this is one of the tricky part
void cond (const set<token>& follow_set) {
    try{
        switch (input_token){
            case t_id:
            case t_literal:
            case t_lparen:
                cout << "predict cond --> expr r_op expr" << endl;
                expr (follow_set);
                r_op ();
                expr (follow_set);
                break;
            default:
                throw syntax_error("From cond"); 
        }
    }
    catch(const struct syntax_error &e){
        cout << "Reocver cond: " << e.err_orig << endl;
        do{
            if (isInSet(input_token, first_sets["cond"])){
                cond (follow_set);
                return;
            }else if(isInSet(input_token, follow_sets["cond"])){
                return;
            }
        }while(input_token = scan ());
    }
}

void expr (const set<token> &follow_set) {
    try{
        switch (input_token) {
            case t_id:
            case t_literal:
            case t_lparen:
                cout << "predict expr --> term term_tail" << endl;
                term (follow_set);
                term_tail (follow_set);
                break;
            default: 
                throw syntax_error ("From expr");
        }
    }
    catch(const struct syntax_error &e){
        cout << "Recover expr: " << e.err_orig << endl;
        do{
            if (isInSet(input_token, first_sets["expr"])){
                expr (follow_set);
                return;
            }else if(isInSet(input_token, follow_sets["expr"])){
                return;
            }
        }while(input_token = scan ());
    }
}

void term_tail (const set<token> &follow_set) {
    switch (input_token) {
        case t_add:
        case t_sub:
            cout << "predict term_tail --> add_op term term_tail" << endl;
            add_op ();
            term (follow_set);
            term_tail (follow_set);
            break;
        case t_rparen:
        case t_id:
        case t_read:
        case t_write:
        case t_eof:
        case t_if:
        case t_while:
        case t_equal:
        case t_nequal:
        case t_lt:
        case t_gt:
        case t_le:
        case t_ge:
        case t_end:
            cout << "predict term_tail --> epsilon" << endl;
            break;          /*  epsilon production */
        default: 
            throw syntax_error ("From term_tail");
    }
}

void term (const set<token> &follow_set) {
    switch (input_token) {
        case t_id:
        case t_literal:
        case t_lparen:
            cout << "predict term --> factor factor_tail" << endl;
            factor (follow_set);
            factor_tail (follow_set);
            break;
        default: 
            throw syntax_error ("From term");
    }
}

void factor_tail (const set<token> &follow_set) {
    switch (input_token) {
        case t_mul:
        case t_div:
            cout << "predict factor_tail --> mul_op factor factor_tail" << endl;
            mul_op ();
            factor (follow_set);
            factor_tail (follow_set);
            break;
        case t_add:
        case t_sub:
        case t_rparen:
        case t_id:
        case t_read:
        case t_write:
        case t_eof:
        case t_if:
        case t_while:
        case t_equal:
        case t_nequal:
        case t_lt:
        case t_gt:
        case t_le:
        case t_ge:
        case t_end:
            cout << "predict factor_tail --> epsilon" << endl;
            break;          /*  epsilon production */
        default: 
            throw syntax_error("From factor tail");
    }
}

void factor (const set<token> &follow_set) {
    switch (input_token) {
        case t_id :
            cout << "predict factor --> id" << endl;
            match (t_id);
            break;
        case t_literal:
            cout << "predict factor --> literal" << endl;
            match (t_literal);
            break;
        case t_lparen:
            cout << "predict factor --> lparen expr rparen" << endl;
            match (t_lparen);
            expr (follow_set);
            match (t_rparen);
            break;
        default: 
            throw syntax_error("From factor");
    }
}

void add_op () {
    switch (input_token) {
        case t_add:
            cout << "predict add_op --> add" << endl;
            match (t_add);
            break;
        case t_sub:
            cout << "predict add_op --> sub" << endl;
            match (t_sub);
            break;
        default: 
            throw syntax_error("From add_op");
    }
}

void mul_op () {
    switch (input_token) {
        case t_mul:
            cout << "predict mul_op --> mul" << endl;
            match (t_mul);
            break;
        case t_div:
            cout << "predict mul_op --> div" << endl;
            match (t_div);
            break;
        default: 
            throw syntax_error("From mul_op");
    }
}

void r_op () {
    switch (input_token) {
        case t_equal:
            cout << "predict r_op --> equal" << endl;
            match (t_equal);
            break;
        case t_nequal:
            cout << "predict r_op --> not_equal" << endl;
            match (t_nequal);
            break;
        case t_lt:
            cout << "predict r_op --> less_than" << endl;
            match (t_lt);
            break;
        case t_gt:
            cout << "predict r_op --> greater_than" << endl;
            match (t_gt);
            break;
        case t_le:
            cout << "predict r_op --> less_equal" << endl;
            match (t_le);
            break;
        case t_ge:
            cout << "predict r_op --> greater_equal" << endl;
            break;
        default: 
            throw syntax_error("From r_op");
    }
}

//Initialize aux sets for non-terminals
void init (){
    init_follow_sets ();
    init_first_sets ();
    init_EPS ();
}

int main () {
    init ();
    input_token = scan ();
    program ();
    return 0;
}
