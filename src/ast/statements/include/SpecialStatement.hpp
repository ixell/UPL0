#pragma once
#include "Statement.hpp"

class SpecialStatement : public Statement {
private:
    std::wstring message;
public:
    explicit SpecialStatement(const std::wstring& message);
    SpecialStatement(const SpecialStatement& other);

    virtual StatementType get_type() const override;
    virtual ~SpecialStatement() override;
    virtual Statement* copy() const override;

    const std::wstring& get_messgae();

    virtual Jump exec(Variables& variables) override;
};
