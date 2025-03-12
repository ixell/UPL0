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
#define VARIABLE(VARIABLE) ()

#define COMBINE_TYPES(LEFT, RIGHT) (uint64_t(LEFT) << 32 & (RIGHT))
#define CT(LEFT, RIGHT) COMBINE_TYPES(LEFT, RIGHT)

#define SWITCH_LEFT switch (left->get_type())
#define SWITCH_RIGHT switch (right->get_type())
#define SWITCH_VALUE switch (value->get_type())

static Expression* copy(const Expression* expression) {
	switch (expression->get_type()) {
	case INT_ET: return static_cast<Expression*>(new INT_E(*static_cast<const INT_E*>(expression)));
	case FLOAT_ET: return static_cast<Expression*>(new FLOAT_E(*static_cast<const FLOAT_E*>(expression)));
	case BOOL_ET: return static_cast<Expression*>(new BOOL_E(*static_cast<const BOOL_E*>(expression)));
	case STRING_ET: return static_cast<Expression*>(new STRING_E(*static_cast<const STRING_E*>(expression)));
	}
}

static bool to_bool(const Expression* expr) {
	switch (expr->get_type()) {
	case BOOL_ET: return BOOL(expr);
	case INT_ET: return INT(expr) != 0LL;
	case FLOAT_ET: return FLOAT(expr) != 0.f;
	case STRING_ET: return STRING(expr).size() != 0;
	default: throw;
	}
}

Expression* IntegerExpression::eval(Variables& variables) const {
	return new IntegerExpression(value);
}

Expression* FloatExpression::eval(Variables& variables) const {
	return new FloatExpression(value);
}

Expression* BooleanExpression::eval(Variables& variables) const {
	return new BooleanExpression(value);
}

Expression* StringExpression::eval(Variables& variables) const {
	return new StringExpression(value);
}

Expression* BinaryExpression::eval(Variables& variables) const {
	Expression* result;
	Expression* left = this->left->eval(variables);
	Expression* right = this->right->eval(variables);
    switch (operation) {
	case Operation::plus:
		SWITCH_LEFT {
		case INT_ET:
			SWITCH_RIGHT {
			case INT_ET: result = new INT_E(INT(left) + INT(right)); break;
			case FLOAT_ET: result = new INT_E(INT(left) + int64_t(FLOAT(right))); break;
			default: throw;
			} break;
		case FLOAT_ET:
			SWITCH_RIGHT {
			case INT_ET: result = new FLOAT_E(FLOAT(left) + float(INT(right))); break;
			case FLOAT_ET: result = new FLOAT_E(FLOAT(left) + FLOAT(right)); break;
			default: throw;
			} break;
		default: throw;
		} break;
	case Operation::minus:
		SWITCH_LEFT {
		case INT_ET:
			SWITCH_RIGHT {
			case INT_ET: result = new INT_E(INT(left) - INT(right)); break;
			case FLOAT_ET: result = new INT_E(INT(left) - int64_t(FLOAT(right))); break;
			default: throw;
			} break;
		case FLOAT_ET:
			SWITCH_RIGHT {
			case INT_ET: result = new FLOAT_E(FLOAT(left) - float(INT(right))); break;
			case FLOAT_ET: result = new FLOAT_E(FLOAT(left) - FLOAT(right)); break;
			default: throw;
			} break;
		default: throw;
		} break;
	case Operation::multiply:
		SWITCH_LEFT {
		case INT_ET:
			SWITCH_RIGHT {
			case INT_ET: result = new INT_E(INT(left) * INT(right)); break;
			case FLOAT_ET: result = new INT_E(INT(left) * int64_t(FLOAT(right))); break;
			default: throw;
			} break;
		case FLOAT_ET:
			SWITCH_RIGHT {
			case INT_ET: result = new FLOAT_E(FLOAT(left) * float(INT(right))); break;
			case FLOAT_ET: result = new FLOAT_E(FLOAT(left) * FLOAT(right)); break;
			default: throw;
			} break;
		default: throw;
		} break;
	case Operation::divide:
		SWITCH_LEFT {
		case INT_ET:
			SWITCH_RIGHT {
			case INT_ET: result = new INT_E(INT(left) / INT(right)); break;
			case FLOAT_ET: result = new INT_E(INT(left) / int64_t(FLOAT(right))); break;
			default: throw;
			} break;
		case FLOAT_ET:
			SWITCH_RIGHT {
			case INT_ET: result = new FLOAT_E(FLOAT(left) / float(INT(right))); break;
			case FLOAT_ET: result = new FLOAT_E(FLOAT(left) / FLOAT(right)); break;
			default: throw;
			} break;
		default: throw;
		} break;
	case Operation::modulus:
		SWITCH_LEFT {
		case INT_ET:
			SWITCH_RIGHT {
			case INT_ET: result = new INT_E(INT(left) % INT(right)); break;
			default: throw;
			} break;
		default: throw;
		} break;
	case Operation::logical_and:
		result = new BOOL_E(to_bool(left) && to_bool(right)); break;
	case Operation::logical_or:
		result = new BOOL_E(to_bool(left) || to_bool(right)); break;
	case Operation::binary_or: // ...
		SWITCH_LEFT {
		case INT_ET:
			SWITCH_RIGHT {
			//case BYTES_ET: result = new BYTES_E(BYTES(left) | BYTES(right));
			default: throw;
			} break;
		default: throw;
		} break;
	case Operation::equal:
		SWITCH_LEFT {
		case INT_ET:
			SWITCH_RIGHT {
			case INT_ET: result = new BOOL_E(INT(left) == INT(right)); break;
			case FLOAT_ET: result = new BOOL_E(INT(left) == FLOAT(right)); break;
			case BOOL_ET: result = new BOOL_E(bool(INT(left)) == BOOL(right)); break;
			default: throw;
			} break;
		case FLOAT_ET:
			SWITCH_RIGHT {
			case INT_ET: result = new BOOL_E(FLOAT(left) == INT(right)); break;
			case FLOAT_ET: result = new BOOL_E(FLOAT(left) == FLOAT(right)); break;
			default: throw;
			} break;
		case BOOL_ET:
			SWITCH_RIGHT {
			case BOOL_ET: result = new BOOL_E(BOOL(left) == BOOL(right)); break;
			case INT_ET: result = new BOOL_E(BOOL(left) == bool(INT(right))); break;
			default: throw;
			} break;
		} break;
	case Operation::lessThan:
		SWITCH_LEFT {
		case INT_ET:
			SWITCH_RIGHT {
			case INT_ET: result = new BOOL_E(INT(left) < INT(right)); break;
			case FLOAT_ET: result = new BOOL_E(INT(left) < FLOAT(right)); break;
			default: throw;
			} break;
		case FLOAT_ET:
			SWITCH_RIGHT {
			case INT_ET: result = new BOOL_E(FLOAT(left) < INT(right)); break;
			case FLOAT_ET: result = new BOOL_E(FLOAT(left) < FLOAT(right)); break;
			default: throw;
			} break;
		} break;
	case Operation::lessThanEq:
		SWITCH_LEFT {
		case INT_ET:
			SWITCH_RIGHT {
			case INT_ET: result = new BOOL_E(INT(left) <= INT(right)); break;
			case FLOAT_ET: result = new BOOL_E(INT(left) <= FLOAT(right)); break;
			default: throw;
			} break;
		case FLOAT_ET:
			SWITCH_RIGHT {
			case INT_ET: result = new BOOL_E(FLOAT(left) <= INT(right)); break;
			case FLOAT_ET: result = new BOOL_E(FLOAT(left) <= FLOAT(right)); break;
			default: throw;
			} break;
		} break;
	case Operation::greaterThan:
		SWITCH_LEFT {
		case INT_ET:
			SWITCH_RIGHT {
			case INT_ET: result = new BOOL_E(INT(left) > INT(right)); break;
			case FLOAT_ET: result = new BOOL_E(INT(left) > FLOAT(right)); break;
			default: throw;
			} break;
		case FLOAT_ET:
			SWITCH_RIGHT {
			case INT_ET: result = new BOOL_E(FLOAT(left) > INT(right)); break;
			case FLOAT_ET: result = new BOOL_E(FLOAT(left) > FLOAT(right)); break;
			default: throw;
			} break;
		} break;
	case Operation::greaterThanEq:
		SWITCH_LEFT {
		case INT_ET:
			SWITCH_RIGHT {
			case INT_ET: result = new BOOL_E(INT(left) >= INT(right)); break;
			case FLOAT_ET: result = new BOOL_E(INT(left) >= FLOAT(right)); break;
			default: throw;
			} break;
		case FLOAT_ET:
			SWITCH_RIGHT {
			case INT_ET: result = new BOOL_E(FLOAT(left) >= INT(right)); break;
			case FLOAT_ET: result = new BOOL_E(FLOAT(left) >= FLOAT(right)); break;
			default: throw;
			} break;
		} break;
	case Operation::assign: {
		if (left->get_type() != ExpressionType::VariableGetterExpression)
			throw;
		result = right;
		Space::Variable& var = static_cast<VariableGetterExpression*>(left)->get_variable(variables);
		delete var.value;
		var.value = right->copy();
		break;
		}
	case Operation::plus_assign:
	case Operation::minus_assign:
	case Operation::multiply_assign:
	case Operation::divide_assign:
	case Operation::binary_and_assign:
	case Operation::binary_xor_assign:
	case Operation::leftShift_assign:
	case Operation::rightShift_assign:
		throw; //...
	}
	delete left, right;
	return result;
}

Expression* UnaryExpression::eval(Variables& variables) const {
    Expression* result;
    Expression* value = value->eval(variables);
    switch (operation) {
    case Operation::plus:
        SWITCH_VALUE {
        case INT_ET:
        case FLOAT_ET:
			return value;
        default: throw;
        } break;
    case Operation::minus:
        SWITCH_VALUE {
        case INT_ET: result = new INT_E(-INT(value));
        case FLOAT_ET: result = new FLOAT_E(-FLOAT(value));
        default: throw;
        } break;
    }
    delete value;
    return result;
}

Expression* ArgumentedExpression::eval(Variables& variables) const {
    Expression* result;
	switch (get_operation()) {
	case Operation::call: {
		if (this->main->get_type() != ExpressionType::VariableGetterExpression) throw;
		VariableGetterExpression* main = static_cast<VariableGetterExpression*>(this->main);
		FunctionStatement* function = nullptr;
		function = static_cast<FunctionStatement*>(variables.find_variable(main->get_name()).var);
		if (function == nullptr) throw;
		size_t count = get_args().size();
		if (count > function->get_args().size()) throw;
		variables.local().add_subspace();
		std::map<std::wstring, Space::Variable>& subspace = variables.local().top();
		for (size_t i = 0; i != count; ++i) {
			const Statement* f_arg = function->get_args()[i];
			const Expression* arg = get_args()[i];
			switch (f_arg->get_type()) {
			case StatementType::InitStatement:
				f_arg = static_cast<const Statement*>(static_cast<const InitStatement*>(f_arg)->get_variable());
				[[fallthrough]];
			case StatementType::VariableStatement:
				const VariableStatement* var = static_cast<const VariableStatement*>(
					static_cast<const VariableGetterExpression*>(arg)->get_variable(variables).var);
				if (static_cast<const VariableStatement*>(f_arg) != var) throw;
				subspace[static_cast<const VariableStatement*>(f_arg)->get_name()]
					= Space::Variable(var->copy(), arg->copy());
			}
		}
		//...
		function->get_code()->exec(variables);
		if (
			function->get_return_type() != nullptr &&
			variables.local().get_return() != nullptr//...
			//static_cast<TypeStatement*>(function->get_return_type()) !=
			//	static_cast<VariableStatement*>(variables.local().get_return().first)->get_variable_type()
		) throw;
		result = variables.local().get_return();
		variables.local().set_return(nullptr);
		for (std::pair<const std::wstring, Space::Variable>& var : variables.local().top()) {//...
			delete var.second.var;
			if (var.second.value != nullptr)
				delete var.second.value;
		}
	}
	}
}

Expression* VariableGetterExpression::eval(Variables& variables) const {
	return get_variable(variables).value->copy();
}
