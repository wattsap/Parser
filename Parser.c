#include <iostream>
#include <cstdlib>
#include <cctype>

using namespace std;
void error();
void match(char& curr);
void Expr(char& curr);
void Term(char& curr);
void Factor(char& curr);
void Number(char& curr);
void Digit(char& curr);
void AddOp(char& curr);
void MulOp(char& curr);
void F(char& curr);
void G(char& curr);
void H(char& curr);
void I(char& curr);
void Space(char& curr);

/*
 * main method.
 * says if string is in language or says error
 */
int main(void) {
    char curr;
    cout << "Enter a string for parsing: ";
    cin.get(curr);
    Expr(curr);
    if (curr == '\n') {
        cout << "String is in the language." << endl;
    } else {
        error();
    }
}
/*
 * print an error if incorrect
 * modified to remove exit(i) and inserted
 * print statements under every call to error
 * to debug and see exactly which method was 
 * throwing a "syntax error" from error method
 * being reached.
 */
void error() {
    cout << "syntax error" << endl;
   // exit(1);
}

/*
 * takes lookahead character as input
 */
void match(char lookahead, char& curr) {
    if (curr == lookahead)
        cin.get(curr);
    else {
         error();
         cout <<"Match"<<endl;
    }
}

/*
 * expr -> F Term G
 */
void Expr(char& curr) {
    F(curr);
    Term(curr);
    G(curr);
}
/* 
 * F -> AddOp
 */
void F(char& curr) {
    if (curr == '+' || curr == '-') {
        AddOp(curr);
    }
}
/*
 *g -> AddOp Term G | lambda
 */
void G(char& curr) { 
    if (curr == '+' || curr == '-') {
        AddOp(curr);
        Term(curr);
        G(curr);
    }
}
/*
 *Term -> Factor H
 */
void Term(char& curr) { 
    Factor(curr);
    H(curr);
}
/*
 * H -> MulOp Factor H | lambda
 */
void H(char& curr) {
    if (curr == '*' || curr == '/') {
        MulOp(curr);
        Factor(curr);
        H(curr);
    }
}
/*
 * Factor -> Number | '('Expr')'
 */
void Factor(char& curr) {
    if (isdigit(curr)) {
        Number(curr);
    }
    else if (curr == '(') {
        match('(', curr);
        Expr(curr);
        match(')', curr);
    }
    else {
        error();
        cout<<"Factor"<<endl;
    }
}
/*
 *AddOp -> '+' | '-'
 */
void AddOp(char& curr) {
    if (curr == '+') {
        match('+', curr);
    }
    else if (curr == '-') {
        match('-', curr);
    }
    else {
        error();
        cout<<"AddOp"<<endl;
    }
}
/*
 *MulOp -> '*' | '/'
 */
void MulOp(char& curr) {
    if (curr == '*') {
        match('*', curr);
    }
    else if (curr == '/') {
        match('/', curr);
    }
    else {
        error();
        cout<<"MulOp"<<endl;
    }
}
/*
 * Number -> Digit I
 */
void Number(char& curr) {
    if (isdigit(curr)) {
        Digit(curr);
        I(curr);
    }
    else {
        error();
        cout<<"Number"<<endl;
    }
}
/*
 * I -> Digit I | lambda
 */
void I(char& curr) {
    if (isdigit(curr)) {
        Digit(curr);
        I(curr);
    }
}
/*
 * Digit -> '0'....'9'
 */
void Digit(char& curr) {
    if (isdigit(curr)) {
        match(curr, curr);
    }
    else {
        error();
        cout<<"Digit"<<endl;
    }
}
/*
 * handling allowance of spaces in string
 * not working yet!
 */
void Space(char& curr) {
    if (curr == ' ') {
        Expr(curr);
    }
    else if (curr == '\t') {
        Expr(curr);
    }
}

