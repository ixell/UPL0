#include <string>
#include <vector>
#include "Statement.hpp"

class InitStatement : public Statement {
private:
    std::vector<std::wstring> type;
    std::wstring variable;
    std::vector<ptr_t<Expression>> args;
public:
    InitStatement(const std::vector<std::wstring type>&, const std::wstring& variable, const std::vector<ptr_t<Expression>>& args);

    virtual StatementType get_type() const override;
    virtual ~InitStatement() = default;

    const std::vector<std::wstring>& get_type();
    const std::wstring& get_variable();
    const std::vector<ptr_t<Expression>>& get_args();
}
