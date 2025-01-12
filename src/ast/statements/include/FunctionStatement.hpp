#include <vector>
#include "Statement.hpp"
#include "TypeExpression.hpp"
#include "BlockStatement.hpp"

class FunctionStatement : public Statement {
private:
    ptr_t<TypeExpression> type;
    std::wstring name;
    std::vector<ptr_t<Expression>> args;
    ptr_t<BlockStatement> code;
public:
    FunctionStatement(
        ptr_t<TypeExpression> type,
        const std::wstring& name,
        const std::vector<ptr_t<Expression>>& args,
        ptr_t<BlockStatement> code;
    );
    
    virtual get_type() const override;
    virtual ~FunctionStatement();

    ptr_t<Expression> get_return_type() const;
    const std::wstring& get_name() const;
    const std::vector<ptr_t<Expression>>& get_args() const;
    ptr_t<BlockStatement> get_code() const;
}
