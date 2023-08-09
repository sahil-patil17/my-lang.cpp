#include <string>
#include <iostream>

//   STAGE 1:
//              CREATING A LEXER

// The lexer returns tokens [0-255] if it is an unknown character, otherwise one
// of these for known things.
enum Token
{
    tok_eof = -1,

    // commands or keywords that we'll be having
    tok_def = -2,
    tok_extern = -3,

    // primary
    tok_identifier = -4,
    tok_number = -5,
};

static std::string IdentifierStr; // Filled in if parser finds a string tok_identifier
static double NumVal;             // Filled in if parser finds a number tok_number

/// gettok - Return the next token from standard input.
static int gettok()
{
    static int LastChar = ' ';

    // Skip any whitespace.
    while (isspace(LastChar))
    {
        LastChar = getchar(); // getchar() reads a single character that you have typed in & stores it.
    }

    // 2) RECOGNIZING IDENTIFIERS

    if (isalpha(LastChar))
    {
        // identifier: [a-zA-Z][a-zA-Z0-9]*

        IdentifierStr = LastChar;

        while (isalnum((LastChar = getchar())))
            IdentifierStr += LastChar;

        // IF THE IDENTIFIER HAS 2 OF THE VARIABLES MENTIONED IN OUR LANGUAGE, CONVERT THEM TO TOKENS.
        if (IdentifierStr == "def")
            return tok_def; //
        if (IdentifierStr == "extern")
            return tok_extern;
        return tok_identifier;
    }

    // 3) RECOGNIZING DIGITS
    if (isdigit(LastChar) || LastChar == '.')
    { // Number: [0-9.]+
        std::string NumStr;
        do
        {
            NumStr += LastChar;
            LastChar = getchar();
        } while (isdigit(LastChar) || LastChar == '.');

        NumVal = strtod(NumStr.c_str(), 0);
        return tok_number;
    }

    // 4) RECOGNIZING COMMENTS
    if (LastChar == '#')
    {
        // Comment until end of line.
        do
            LastChar = getchar();
        while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');

        if (LastChar != EOF)
            return gettok(); // Recursive call
    }

    // Check for end of file.  Don't eat the EOF.
    if (LastChar == EOF)
    {
        return tok_eof;
    }

    // Otherwise, just return the character as its ascii value.
    int ThisChar = LastChar;
    LastChar = getchar();
    return ThisChar;
}

// Test main function for Lexer Tokenization Test.
// int main()
// {
//     while (true)
//     {
//         int tok = gettok();
//         std::cout << "Got Token: " << tok << std::endl;
//     }
//     return 0;
// }

//   STAGE 2:
//             ABSTRACT SYNTAX TREE

class ExprAST
{
public:
    virtual ~ExprAST() {}
};

class NumberExprAST : public ExprAST
{
    double Val;

public:
    NumberExprAST(double V) : Val(V) {} // initializer list in constructor
    // in Java, we would do this.Val = V
};

//   STAGE 3:
//             PARSING

//   STAGE 4:
//             CODE GENERATION PHASE

//   STAGE 5:
//             OPTIMIZING WITH JIT