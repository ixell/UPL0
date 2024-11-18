#pragma once
#include <string>
#include <memory>
using std::unique_ptr;

class Expression {
public:
	virtual std::wstring to_string() const = 0;
	virtual ~Expression() = default;
};