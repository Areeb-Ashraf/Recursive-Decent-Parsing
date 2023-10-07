#include <iostream>
#include <fstream>
#include <string>
#include <memory>

using namespace std;

// Base class for abstract syntax tree (AST) nodes
class ASTNode
{
public:
    virtual ~ASTNode() {}
};

// Node representing binary operators
class BinaryOperatorNode : public ASTNode
{
public:
    BinaryOperatorNode(char op, shared_ptr<ASTNode> left, shared_ptr<ASTNode> right)
        : op(op), left(left), right(right) {}

    char getOperator() const { return op; }
    shared_ptr<ASTNode> getLeft() const { return left; }
    shared_ptr<ASTNode> getRight() const { return right; }

private:
    char op;
    shared_ptr<ASTNode> left;
    shared_ptr<ASTNode> right;
};

// Node representing integer values
class IntegerNode : public ASTNode
{
public:
    IntegerNode(int value) : value(value) {}

    int getValue() const { return value; }

private:
    int value;
};

// Recursive Descent Parser class for parsing expressions
class RecursiveDescentParser
{
public:
    RecursiveDescentParser(const string &input) : input(input), index(0) {}

    shared_ptr<ASTNode> parse()
    {
        auto root = parseExpression();
        if (index != input.length())
        {
            cerr << "Error: Unexpected characters after the expression." << endl;
        }
        return root;
    }

private:
    // Parsing methods for different parts of the expression
    shared_ptr<ASTNode> parseExpression()
    {
        auto left = parseTerm();
        while (match('+') || match('-'))
        {
            char op = input[index - 1];
            auto right = parseTerm();
            left = make_shared<BinaryOperatorNode>(op, left, right);
        }
        return left;
    }

    shared_ptr<ASTNode> parseTerm()
    {
        auto left = parseFactor();
        while (match('*') || match('/'))
        {
            char op = input[index - 1];
            auto right = parseFactor();
            left = make_shared<BinaryOperatorNode>(op, left, right);
        }
        return left;
    }

    shared_ptr<ASTNode> parseFactor()
    {
        if (match('('))
        {
            auto expression = parseExpression();
            if (!match(')'))
            {
                cerr << "Error: Expected closing parenthesis ')'." << endl;
            }
            return expression;
        }
        int startPos = index;
        if (parseInteger())
        {
            int length = index - startPos;
            int value = stoi(input.substr(startPos, length));
            return make_shared<IntegerNode>(value);
        }
        cerr << "Error: Invalid character '" << input[index] << "' found." << endl;
        return nullptr;
    }

    // Helper methods for parsing integers
    bool parseInteger()
    {
        int startPos = index;
        if (parseDigit() && parseIntegerSuffix())
        {
            return true;
        }
        cerr << "Error: Invalid integer at position " << startPos << "." << endl;
        return false;
    }

    bool parseIntegerSuffix()
    {
        if (parseDigit() && parseIntegerSuffix())
        {
            return true;
        }
        return true; // ε (epsilon) production
    }

    bool parseDigit()
    {
        if (index < input.length() && isdigit(input[index]))
        {
            index++;
            return true;
        }
        return false;
    }

    bool match(char expected)
    {
        if (index < input.length() && input[index] == expected)
        {
            index++;
            return true;
        }
        return false;
    }

private:
    const string &input;
    size_t index;
};

// Helper function to print the AST
void printAST(shared_ptr<ASTNode> node, int indent = 0)
{
    if (node)
    {
        if (auto binOpNode = dynamic_pointer_cast<BinaryOperatorNode>(node))
        {
            cout << string(indent, ' ') << binOpNode->getOperator() << " ("
                 << (binOpNode->getOperator() == '+' ? "Add" : (binOpNode->getOperator() == '-' ? "Minus" : (binOpNode->getOperator() == '*' ? "Multiply" : "Divide")))
                 << ")" << endl;
            printAST(binOpNode->getLeft(), indent + 4);
            printAST(binOpNode->getRight(), indent + 4);
        }
        else if (auto intNode = dynamic_pointer_cast<IntegerNode>(node))
        {
            cout << string(indent, ' ') << intNode->getValue() << " (Integer)" << endl;
        }
    }
}

int main()
{
    ifstream inputFile("lex_output.txt"); // Open the input file
    string line;
    string input;

    if (inputFile.is_open())
    {
        while (getline(inputFile, line))
        {
            if (!line.empty())
            {
                char firstChar = line[0];
                input += firstChar;
            }
        }
        inputFile.close(); // Close the input file
    }
    else
    {
        cerr << "Unable to open input file" << endl;
        return 1; // Exit with an error code
    }

    RecursiveDescentParser parser(input);
    shared_ptr<ASTNode> root = parser.parse();

    cout << "Abstract Syntax Tree (AST):" << endl;
    printAST(root);

    return 0;
}
