#include "TypeStatement.hpp"
#include "typeModificators.hpp"

TypeStatement::TypeStatement(
	const std::wstring& type,
	const std::vector<Modificator>& modificators,
	const std::vector<Statement*>& template_
) :
	type(type), modificators(modificators), template_(template_) {}

TypeStatement::TypeStatement(
	const std::wstring& type,
	const std::vector<Modificator>& modificators
) :
	type(type), modificators(modificators) {}

TypeStatement::TypeStatement(const std::wstring& type)
	: type(type) {}

TypeStatement::TypeStatement(const TypeStatement& other)
		: TypeStatement(other.type, other.modificators) {
	template_.reserve(other.template_.size());
	for (Statement* statement : other.template_) {
		template_.push_back(statement->copy());
	}
}

StatementType TypeStatement::get_type() const {
	return StatementType::TypeStatement;
}

TypeStatement::~TypeStatement() {
	for (Statement* statement : template_)
		delete statement;
}

Statement* TypeStatement::copy() const {
    return static_cast<Statement*>(new TypeStatement(*this));
}

const std::vector<Modificator>& TypeStatement::get_modificators() const {
	return modificators;
}

const std::vector<Statement*>& TypeStatement::get_template() const {
	return template_;
}

const std::wstring& TypeStatement::get_type_value() const {
	return type;
}

bool TypeStatement::operator==(const TypeStatement& other) const {
	if (type != other.type) return false;
	if (modificators.size() != other.modificators.size()) return false;
	if (template_.size() != other.template_.size()) return false;
	for (size_t i = 0; i != modificators.size(); ++i) {
		if (modificators[i] != other.modificators[i])
			return false;
	}
	for (size_t i = 0; i != template_.size(); ++i) {
		if (template_[i] != other.template_[i])
			return false;
	}
	return true;
}

bool TypeStatement::operator!=(const TypeStatement& other) const {
	return !(*this == other);
}
