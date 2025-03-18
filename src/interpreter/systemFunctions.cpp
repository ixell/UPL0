#include "systemFunctions.hpp"
#include "SpecialStatement.hpp"

namespace systemFunctions {
    Expression* print_function(std::vector<Expression*> args) {
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
        std::wcout << L"\n";
        return nullptr;
    }

    SystemFunctionStatement print (
        static_cast<TypeStatement*>(nullptr),
        L"print",
        {static_cast<Statement*>(new SpecialStatement(L"..."))},
        &print_function
    );
}

std::vector<SystemFunctionStatement*> system_functions = {
    &systemFunctions::print
};
