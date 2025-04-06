#include "all_expressions.hpp"
#include "all_statements.hpp"

#define INT_E     IntegerExpression
#define FLOAT_E   FloatExpression
#define BOOL_E    BooleanExpression
#define STRING_E  StringExpression

#define INT_ET    ExpressionType::IntegerExpression
#define FLOAT_ET  ExpressionType::FloatExpression
#define BOOL_ET   ExpressionType::BooleanExpression
#define STRING_ET ExpressionType::StringExpression

#define GET_VALUE(EXPRESSION_TYPE, VARIABLE) (static_cast<const EXPRESSION_TYPE*>(VARIABLE)->get_value())
#define INT(VARIABLE) GET_VALUE(IntegerExpression, VARIABLE)
#define FLOAT(VARIABLE) GET_VALUE(FloatExpression, VARIABLE)
#define BOOL(VARIABLE) GET_VALUE(BooleanExpression, VARIABLE)
#define STRING(VARIABLE) GET_VALUE(StringExpression, VARIABLE)

static bool to_bool(const Expression* expr) {
	switch (expr->get_type()) {
	case ExpressionType::BooleanExpression:
		return static_cast<const BooleanExpression*>(expr)->get_value();
	case ExpressionType::IntegerExpression:
        return static_cast<const IntegerExpression*>(expr)->get_value() == 0U;
	case ExpressionType::FloatExpression:
        return static_cast<const FloatExpression*>(expr)->get_value() == 0.f;
	case ExpressionType::StringExpression:
        return !static_cast<const StringExpression*>(expr)->get_value().empty();
	default: throw;
	}
}

static const wchar_t* to_type(const Expression* expr) {
    switch (expr->get_type()) {
    case INT_ET:    return L"int";
    case FLOAT_ET:  return L"float";
    case BOOL_ET:   return L"bool";
    case STRING_ET: return L"string";
    default:        throw;
    }
}

Jump BlockStatement::exec(Variables& variables) {
    for (Statement* statement : statements) {
        Jump jump = statement->exec(variables);
        if (jump != Jump::none) return jump;
    }
    return Jump::none;
}

Jump DoStatement::exec(Variables& variables) {
    delete expr->eval(variables);
    return Jump::none;
}

Jump ForStatement::exec(Variables& variables) {
    variables.local().add_subspace();
    initializer->exec(variables);
    for (Expression* expr = condition->eval(variables);
         to_bool(expr);
         expr = condition->eval(variables)) {
        delete expr;
        Jump jump = code->exec(variables);
        switch (jump) {
        case Jump::none:
        case Jump::continue_:
            break;
        case Jump::break_:
            return Jump::none;
        case Jump::return_:
            return jump;
        }
        delete changer->eval(variables);
    }
    variables.local().pop_subspace();
    return Jump::none;
}

Jump IfElseStatement::exec(Variables& variables) {
    Jump jump;
    Expression* expr = condition->eval(variables);
    bool value = to_bool(expr);
    delete expr;
    variables.local().add_subspace();
    if (value)
        jump = condition_met->exec(variables);
    else if (condition_not_met != nullptr)
        jump = condition_not_met->exec(variables);
    else jump = Jump::none;
    variables.local().pop_subspace();
    return jump;
}

Jump InitStatement::exec(Variables& variables) {
    if (get_args().size() != 1) throw;
    Expression* value = get_args()[0]->eval(variables);
    const std::wstring& type = get_variable()->get_variable_type()->get_type_value();
    if (type != to_type(value)) throw;
    variables.top()[get_variable()->get_name()] = Space::Variable(get_variable()->copy(), value);
    return Jump::none;
}

Jump SwitchCaseStatement::exec(Variables& variables) {
    //...
    Expression* item = get_item()->eval(variables);
    for (std::pair<Expression*, BlockStatement*> case_ : cases) {
        Expression* value = case_.first->eval(variables);
        if (value->get_type() != item->get_type()) throw;
        switch (item->get_type()) {
        case ExpressionType::IntegerExpression:
            if (static_cast<IntegerExpression*>(item)->get_value() ==
                    static_cast<IntegerExpression*>(value)->get_value()) {
                delete item, value;
                variables.local().add_subspace();
                Jump jump = case_.second->exec(variables);
                variables.local().pop_subspace();
                return jump;
            }
            continue;
        case ExpressionType::FloatExpression:
            if (static_cast<FloatExpression*>(item)->get_value() ==
                    static_cast<FloatExpression*>(value)->get_value()) {
                delete item, value;
                variables.local().add_subspace();
                Jump jump = case_.second->exec(variables);
                variables.local().pop_subspace();
                return jump;
            }
            continue;
        case ExpressionType::BooleanExpression:
            if (static_cast<BooleanExpression*>(item)->get_value() ==
                    static_cast<BooleanExpression*>(value)->get_value()) {
                delete item, value;
                variables.local().add_subspace();
                Jump jump = case_.second->exec(variables);
                variables.local().pop_subspace();
                return jump;
            }
            continue;
        case ExpressionType::StringExpression:
            if (static_cast<StringExpression*>(item)->get_value() ==
                    static_cast<StringExpression*>(value)->get_value()) {
                delete item, value;
                variables.local().add_subspace();
                Jump jump = case_.second->exec(variables);
                variables.local().pop_subspace();
                return jump;
            }
            continue;
        }
        delete value;
    }
    delete item;
    return Jump::none;
}

Jump WhileStatement::exec(Variables& variables) {
    variables.local().add_subspace();
    for (Expression* expr = condition->eval(variables);
         to_bool(expr);
         expr = condition->eval(variables)) {
        delete expr;
        Jump jump = code->exec(variables);
        switch (jump) {
        case Jump::none:
        case Jump::continue_:
            continue;
        case Jump::break_:
            break;
            case Jump::return_:
                return jump;
        }
    }
    variables.local().pop_subspace();
    return Jump::none;
}

Jump DoWhileStatement::exec(Variables& variables) {
    variables.local().add_subspace();
    Jump jump = code->exec(variables);
    switch (jump) {
    case Jump::none:
    case Jump::continue_:
        break;
    case Jump::break_:
        variables.local().pop_subspace();
        return Jump::none;
    case Jump::return_:
        variables.local().pop_subspace();
        return jump;
    }
    for (Expression* expr = condition->eval(variables);
         to_bool(expr);
         expr = condition->eval(variables)) {
        delete expr;
        Jump jump = code->exec(variables);
        switch (jump) {
        case Jump::none:
        case Jump::continue_:
            continue;
        case Jump::break_:
            break;
        case Jump::return_:
            variables.local().pop_subspace();
            return jump;
        }
    }
    variables.local().pop_subspace();
    return Jump::none;
}

Jump ReturnStatement::exec(Variables& variables) {
    variables.local().set_return(get_expression()->eval(variables));
    return Jump::return_;
}

Jump ContinueStatement::exec(Variables& variables) {
    return Jump::continue_;
}

Jump BreakStatement::exec(Variables& variables) {
    return Jump::break_;
}

Jump TypeStatement::exec(Variables& variables) { throw; }
Jump VariableStatement::exec(Variables& variables) { throw; }
Jump FunctionStatement::exec(Variables& variables) { throw; }
Jump ClassStatement::exec(Variables& variables) { throw; }
Jump ClassStatement::ClassVariableStatement::exec(Variables& variables) { throw; }
Jump ClassStatement::MethodStatement::exec(Variables& variables) { throw; }
Jump SystemFunctionStatement::exec(Variables& variables) { throw; }
Jump SpecialStatement::exec(Variables& variables) { throw; }

Expression* FunctionStatement::call(Variables& variables, const std::vector<Expression*>& args) {
    size_t count = args.size();
    if (count > get_args().size()) throw;
    variables.add_local();
    variables.local().add_subspace();
    std::map<std::wstring, Space::Variable>& subspace = variables.local().top();
    for (size_t i = 0; i != count; ++i) {
        const Statement* f_arg = get_args()[i];
        Expression* arg = args[i]->eval(variables);
        switch (f_arg->get_type()) {
        case StatementType::InitStatement:
            f_arg = static_cast<const Statement*>(static_cast<const InitStatement*>(f_arg)->get_variable());
            [[fallthrough]];
        case StatementType::VariableStatement:
            if (static_cast<const VariableStatement*>(f_arg)->get_variable_type()->get_type_value() != to_type(arg)) throw; //...
            subspace[static_cast<const VariableStatement*>(f_arg)->get_name()] = Space::Variable(f_arg->copy(), arg);
            continue;
        case StatementType::TypeStatement:
            if (static_cast<const VariableStatement*>(f_arg)->get_variable_type()->get_type_value() != to_type(arg)) throw;
            continue;
        default: throw;
        }
    }
    //...
    get_code()->exec(variables);
    if (
        get_return_type() != nullptr &&
        variables.local().get_return() != nullptr &&
        get_return_type()->get_type_value() != to_type(variables.local().get_return()) //...
    ) throw;
    Expression* result = variables.local().get_return();
    variables.local().set_return(nullptr);
    variables.pop_local();
    return result;
}

Expression* SystemFunctionStatement::call(Variables& variables, const std::vector<Expression*>& args) {
    size_t count = args.size();
    std::vector<Expression*> arguments;
    variables.local().add_subspace();
    variables.add_local();
    for (size_t i = 0; i < count; ++i) {
        if (i == count) throw;
        const Statement* f_arg = get_args()[i];
        Expression* arg = args[i]->eval(variables);
        switch (f_arg->get_type()) {
        case StatementType::InitStatement:
            f_arg = static_cast<const Statement*>(static_cast<const InitStatement*>(f_arg)->get_variable());
            [[fallthrough]];
        case StatementType::VariableStatement:
            if (static_cast<const VariableStatement*>(f_arg)->get_variable_type()->get_type_value() != to_type(arg)) throw;
            arguments.push_back(arg);
            continue;
        case StatementType::TypeStatement:
            if (static_cast<const VariableStatement*>(f_arg)->get_variable_type()->get_type_value() != to_type(arg)) throw;
            continue;
        case StatementType::SpecialStatement:
            if (static_cast<const SpecialStatement*>(f_arg)->get_messgae() != L"...") throw;
            if (count < get_args().size()) throw;
            for (; i != args.size(); ++i) {
                arguments.push_back(arg);
            }
            continue;
        default: throw;
        }
        //...
    }
    Expression* result = code(arguments);
    for (Expression* arg : arguments) {
        delete arg;
    }
    return result;
}
