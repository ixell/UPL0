#include "all_expressions.hpp"
#include "all_statements.hpp"

static bool to_bool(Expression* expr) {
	switch (expr->get_type()) {
	case ExpressionType::BooleanExpression:
		return static_cast<BooleanExpression*>(expr)->get_value();
	case ExpressionType::IntegerExpression:
        return static_cast<IntegerExpression*>(expr)->get_value() == 0U;
	case ExpressionType::FloatExpression:
        return static_cast<FloatExpression*>(expr)->get_value() == 0.f;
	case ExpressionType::StringExpression:
        return !static_cast<StringExpression*>(expr)->get_value().empty();
	default: throw;
	}
}

Jump BlockStatement::exec(Variables& variables) {
    for (Statement* statement : statements) {
        if (statement->get_type() == StatementType::ReturnStatement) {
            return statement->exec(variables);
        }
        Jump jump = statement->exec(variables);
        if (jump != Jump::none) return jump;
    }
    return Jump::none;
}

Jump DoStatement::exec(Variables& variables) {
    expr->eval(variables);
    return Jump::none;
}

Jump ForStatement::exec(Variables& variables) {
    for (initializer->eval(variables); to_bool(condition->eval(variables)); changer->eval(variables)) {
        Jump jump = code->exec(variables);
        switch (jump) {
        case Jump::none:
        case Jump::return_:
            return jump;
        case Jump::continue_:
            continue;
        case Jump::break_:
            break;
        }
    }
    return Jump::none;
}

Jump IfElseStatement::exec(Variables& variables) {
    if (to_bool(condition->eval(variables)))
        return condition_met->exec(variables);
    else
        return condition_not_met->exec(variables);
}

Jump InitStatement::exec(Variables& variables) {
//     const std::wstring& type = get_variable()->get_variable_type()->get_type_value();
//     if (type == L"int") {
//         variables[get_variable()->get_name()] = std::pair<Expression*, Statement*>(
//             new VariableStatement(*get_variable()),
//             new IntegerExpression(get_args()[0]->eval(variables)) //...
//         );
//     } else if (type == L"float") {
//         variables[get_variable()->get_name()] = std::pair<Expression*, Statement*>(
//             new VariableStatement(*get_variable()),
//             new FloatExpression(get_args()[0]->eval(variables)) //...
//         );
//     } else if (type == L"bool") {
//         variables[get_variable()->get_name()] = std::pair<Expression*, Statement*>(
//             new VariableStatement(*get_variable()),
//             new BooleanExpression(to_bool(get_args()[0]->eval(variables)))
//         );
//     } else if (type == L"string") {
//         variables[get_variable()->get_name()] = std::pair<Expression*, Statement*>(
//             new VariableStatement(*get_variable()),
//             new StringExpression(get_args()[0]->eval(variables)) //...
//         );
//     } else throw; //...
    return Jump::none;
}

Jump SwitchCaseStatement::exec(Variables& variables) {
    //...
    for (std::pair<Expression*, BlockStatement*> case_ : cases) {
        Expression* item = get_item()->eval(variables);
        Expression* value = case_.first->eval(variables);
        if (value->get_type() != item->get_type()) throw;
        switch (item->get_type()) {
        case ExpressionType::IntegerExpression:
            if (static_cast<IntegerExpression*>(item)->get_value() ==
                    static_cast<IntegerExpression*>(item)->get_value()) {
                return case_.second->exec(variables);
            }
            continue;
        case ExpressionType::FloatExpression:
            if (static_cast<FloatExpression*>(item)->get_value() ==
                    static_cast<FloatExpression*>(item)->get_value()) {
                return case_.second->exec(variables);
            }
            continue;
        case ExpressionType::BooleanExpression:
            if (static_cast<BooleanExpression*>(item)->get_value() ==
                    static_cast<BooleanExpression*>(item)->get_value()) {
                return case_.second->exec(variables);
            }
            continue;
        case ExpressionType::StringExpression:
            if (static_cast<StringExpression*>(item)->get_value() ==
                    static_cast<StringExpression*>(item)->get_value()) {
                return case_.second->exec(variables);
            }
            continue;
        }
    }
    return Jump::none;
}

Jump WhileStatement::exec(Variables& variables) {
    while (to_bool(condition->eval(variables))) {
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
    return Jump::none;
}

Jump DoWhileStatement::exec(Variables& variables) {
    do {
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
    } while (to_bool(condition->eval(variables)));
    return Jump::none;
}

Jump ReturnStatement::exec(Variables& variables) {
    variables.local().set_return(get_expression()->eval(variables));
    return Jump::return_;
}

Jump TypeStatement::exec(Variables& variables) { throw; }
Jump VariableStatement::exec(Variables& variables) { throw; }
Jump FunctionStatement::exec(Variables& variables) { throw; }
Jump ClassStatement::exec(Variables& variables) { throw; }
Jump ClassStatement::ClassVariableStatement::exec(Variables& variables) { throw; }
Jump ClassStatement::MethodStatement::exec(Variables& variables) { throw; }
