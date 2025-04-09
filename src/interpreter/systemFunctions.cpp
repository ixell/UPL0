#include "systemFunctions.hpp"
#include "SpecialStatement.hpp"

namespace systemFunctions {
    Expression* print_function(std::vector<Expression*>& args) {
        for (auto iter = args.begin(); iter != args.end() - 1; ++iter) {
            switch ((*iter)->get_type()) {
            case ExpressionType::IntegerExpression:
                std::wcout << static_cast<IntegerExpression*>(*iter)->get_value();
                break;
            case ExpressionType::FloatExpression:
                std::wcout << static_cast<FloatExpression*>(*iter)->get_value();
                break;
            case ExpressionType::BooleanExpression:
                std::wcout << static_cast<BooleanExpression*>(*iter)->get_value();
                break;
            case ExpressionType::StringExpression:
                std::wcout << static_cast<StringExpression*>(*iter)->get_value();
                break;
            default: throw;
            }
            std::wcout << L" ";
        }
        if (args.size() != 0) {
            switch (args.back()->get_type()) {
            case ExpressionType::IntegerExpression:
                std::wcout << static_cast<IntegerExpression*>(args.back())->get_value();
                break;
            case ExpressionType::FloatExpression:
                std::wcout << static_cast<FloatExpression*>(args.back())->get_value();
                break;
            case ExpressionType::BooleanExpression:
                std::wcout << static_cast<BooleanExpression*>(args.back())->get_value();
                break;
            case ExpressionType::StringExpression:
                std::wcout << static_cast<StringExpression*>(args.back())->get_value();
                break;
            default: throw;
            }
        }
        return nullptr;
    }

    SystemFunctionStatement print (
        static_cast<TypeStatement*>(nullptr),
        L"print",
        {static_cast<Statement*>(new SpecialStatement(L"..."))},
        &print_function
    );

    Expression* input_string_function(std::vector<Expression*>& args) {
        std::wstring str;
        std::wcin >> str;
        return static_cast<Expression*>(new StringExpression(str));
    }

    SystemFunctionStatement input_string (
        static_cast<TypeStatement*>(nullptr),
        L"input_string",
        std::vector<Statement*>(),
        &input_string_function
    );

    Expression* input_int_function(std::vector<Expression*>& args) {
        int64_t integer;
        std::wcin >> integer;
        return static_cast<Expression*>(new IntegerExpression(integer));
    }

    SystemFunctionStatement input_int (
        static_cast<TypeStatement*>(nullptr),
        L"input_int",
        {},
        &input_int_function
    );

    Expression* input_float_function(std::vector<Expression*>& args) {
        float float_;
        std::wcin >> float_;
        return static_cast<Expression*>(new FloatExpression(float_));
    }

    SystemFunctionStatement input_float (
        static_cast<TypeStatement*>(nullptr),
        L"input_float",
        {},
        &input_float_function
    );
}

std::vector<SystemFunctionStatement*> system_functions = {
    &systemFunctions::print,
    &systemFunctions::input_string,
    &systemFunctions::input_int,
    &systemFunctions::input_float,
};
