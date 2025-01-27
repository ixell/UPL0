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

StatementType TypeStatement::get_type() const {
	return StatementType::Unknown;
}

TypeStatement::~TypeStatement() {
	for (Statement* statement : template_)
		delete statement;
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