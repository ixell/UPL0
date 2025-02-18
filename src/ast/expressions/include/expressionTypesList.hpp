#pragma once
enum class ExpressionType {
    unknown,
    BinaryExpression,
    UnaryExpression,
    IntegerExpression,
    BooleanExpression,
    FloatExpression,
    StringExpression,
    VariableGetterExpression
};
