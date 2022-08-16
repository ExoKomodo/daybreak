#pragma once

#include <limits.h>
#include <stdbool.h>

#include <helpers/system.h>
#include <lex/prelude.h>
#include <parser/prelude.h>
#include <macros/helpers.h>

int generate_c_code(const struct ProgramNode*, const char*);
int generate_c_from_binding_statement(FILE*, const struct BindingStatementNode*);
int generate_c_from_call_expression(FILE*, const struct CallExpressionNode*);
int generate_c_from_do_statement(FILE*, const struct DoStatementNode*);
int generate_c_from_double_expression(FILE*, const struct DoubleExpressionNode*);
int generate_c_from_(FILE*, const struct ExpressionNode*);
int generate_c_from_enum_declaration(FILE*, const struct EnumTypeDeclarationNode*);
int generate_c_from_enum_field(FILE*, const struct EnumFieldNode*);
int generate_c_from_enum_field_list(FILE*, const struct EnumFieldListNode*);
int generate_c_from_enum_type_expression(FILE*, const struct EnumTypeExpressionNode*);
int generate_c_from_expression(FILE*, const struct ExpressionNode*);
int generate_c_from_expression_list(FILE*, const struct ExpressionListNode*);
int generate_c_from_field(FILE*, const struct FieldNode*);
int generate_c_from_field_binding(FILE*, const struct FieldBindingNode*);
int generate_c_from_field_binding_list(FILE*, const struct FieldBindingListNode*);
int generate_c_from_field_list(FILE*, const struct FieldListNode*);
int generate_c_from_function_declaration(FILE*, const struct FunctionDeclarationNode*);
int generate_c_from_identifier(FILE*, const struct IdentifierNode*);
int generate_c_from_identifier_expression(FILE*, const struct IdentifierExpressionNode*);
int generate_c_from_import_statement(FILE*, const struct ImportStatementNode*);
int generate_c_from_integer_expression(FILE*, const struct IntegerExpressionNode*);
int generate_c_from_let_binding(FILE*, const struct LetBindingNode*);
int generate_c_from_list_expression(FILE*, const struct ListExpressionNode*);
int generate_c_from_match_case(FILE*, const struct MatchCaseNode*);
int generate_c_from_match_case_list(FILE*, const struct MatchCaseListNode*);
int generate_c_from_match_statement(FILE*, const struct MatchStatementNode*);
int generate_c_from_module_statement(FILE*, const struct ModuleStatementNode*);
int generate_c_from_module_statement_list(FILE*, const struct ModuleStatementListNode*);
int generate_c_from_mut_binding(FILE*, const struct MutBindingNode*);
int generate_c_from_numeric_expression(FILE*, const struct NumericExpressionNode*);
int generate_c_from_parameter(FILE*, const struct ParameterNode*);
int generate_c_from_parameter_list(FILE*, const struct ParameterListNode*);
int generate_c_from_program(FILE*, const struct ProgramNode*);
int generate_c_from_return_statement(FILE*, const struct ReturnStatementNode*);
int generate_c_from_shebang(FILE*, const struct ShebangNode*);
int generate_c_from_statement(FILE*, const struct StatementNode*, const bool);
int generate_c_from_statement_list(FILE*, const struct StatementListNode*);
int generate_c_from_string_expression(FILE*, const struct StringExpressionNode*);
int generate_c_from_struct_type_declaration(FILE*, const struct StructTypeDeclarationNode*);
int generate_c_from_structured_type_expression(FILE*, const struct StructuredTypeExpressionNode*);
int generate_c_from_type_declaration(FILE*, const struct TypeDeclarationNode*);
int generate_c_from_type_expression(FILE*, const struct TypeExpressionNode*);
int generate_c_from_type_identifier(FILE*, const struct TypeIdentifierNode*);
int generate_c_from_union_type_declaration(FILE*, const struct UnionTypeDeclarationNode*);
int generate_c_include_prelude(FILE*);
int generate_c_macros(FILE*);
int _generate_c_variable_declaration(FILE*, const struct TypeIdentifierNode*, const struct IdentifierNode*, const struct ExpressionNode*);
int _generate_c_function_definition(FILE*, const struct FunctionDeclarationNode*);
int _generate_c_function_declaration(FILE*, const struct FunctionDeclarationNode*);
int _generate_c_function_signature(FILE*, const struct FunctionDeclarationNode*, const bool);
int _generate_c_from_module_statement_list_by_kind(FILE*, const struct ModuleStatementListNode*, const AstNodeKind);
bool _is_file_imported(const char*);
bool _is_main(const struct FunctionDeclarationNode*);
bool _is_pointer_type(const struct TypeIdentifierNode*);
FILE* _open_output_file(const char*);
bool _should_inline(const struct FunctionDeclarationNode*);

#define IMPORTED_FILE_MAX 1024

char imported_file_paths[IMPORTED_FILE_MAX][MAX_PATH] = {{'\0'}};
int imported_file_count = 0;

int generate_c_code(
	const struct ProgramNode* program,
	const char* output_file_path
) {
	FILE* output_file = _open_output_file(output_file_path);
	if (!output_file) {
		LOG_ERROR("Failed to open output file");
		return 1;
	}

	int error;
	error = generate_c_include_prelude(output_file);
	if (error != 0) {
		LOG_ERROR("Failed to generate C include prelude");
		fclose(output_file);
		return error;
	}

	error = generate_c_macros(output_file);
	if (error != 0) {
		LOG_ERROR("Failed to generate C macros");
		fclose(output_file);
		return error;
	}

	error = generate_c_from_program(output_file, program);
	if (error != 0) {
		LOG_ERROR("Failed to generate C code");
		fclose(output_file);
		return error;
	}
	fclose(output_file);

	imported_file_count = 0;

	return 0;
}

int generate_c_include_prelude(FILE* output_file) {
	fputs("#include <assert.h>\n", output_file);
	fputs("#include <stdbool.h>\n", output_file);
	fputs("#include <stdint.h>\n", output_file);
	fputs("#include <stdlib.h>\n", output_file);
	fputs("#include <stdio.h>\n", output_file);
	fputc('\n', output_file);

	return 0;
}

int generate_c_from_binding_statement(
	FILE* output_file,
	const struct BindingStatementNode* binding_statement
) {
	if (!binding_statement) {
		LOG_ERROR("Failed to generate C code from BindingStatementNode. NULL BindingStatementNode.");
		return 1;
	}

	switch (binding_statement->kind) {
		case AstLetBinding: {
			return generate_c_from_let_binding(output_file, binding_statement->value.let_binding);
		} break;
		case AstMutBinding: {
			return generate_c_from_mut_binding(output_file, binding_statement->value.mut_binding);
		} break;
		default: {
			LOG_ERROR(
				"Failed to generate C code from BindingStatementNode. Unknown BindingStatementNode kind %d.",
				binding_statement->kind
			);
			return 3;
		} break;
	}
}

int generate_c_from_call_expression(FILE* output_file, const struct CallExpressionNode* call_expression) {
	if (!call_expression) {
		LOG_ERROR("Failed to generate C code from CallExpressionNode. NULL CallExpressionNode.");
		return 1;
	}

	int error = generate_c_from_identifier(output_file, call_expression->function);
	if (error != 0) {
		return error;
	}
	fputc('(', output_file);
	error = generate_c_from_expression_list(output_file, call_expression->arguments);
	fputc(')', output_file);
	return error;
}

int generate_c_from_do_statement(
	FILE* output_file,
	const struct DoStatementNode* do_statement
) {
	if (!do_statement) {
		LOG_ERROR("Failed to generate C do statement from DoStatementNode. NULL DoStatementNode.");
		return 1;
	}

	fputs("{\n", output_file);
	struct StatementListNode* statements = do_statement->statements;
	const int error = generate_c_from_statement_list(output_file, statements);
	if (error != 0) {
		LOG_ERROR("Failed to generate C do statement statements from Statement List: %d", error);
		return error;
	}
	fputs("}\n", output_file);

	return 0;
}

int generate_c_from_double_expression(FILE* output_file, const struct DoubleExpressionNode* double_expression) {
	if (!double_expression) {
		LOG_ERROR("Failed to generate C code from DoubleExpressionNode. NULL DoubleExpressionNode.");
		return 1;
	}

	fprintf(output_file, "%F", double_expression->value);

	return 0;
}

int generate_c_from_enum_declaration(FILE* output_file, const struct EnumTypeDeclarationNode* declaration) {
	if (!declaration) {
		LOG_ERROR("Failed to generate C code from EnumTypeDeclarationNode. NULL EnumTypeDeclarationNode.");
		return 1;
	}

	fputs("typedef enum {\n", output_file);
	int error = generate_c_from_enum_field_list(output_file, declaration->fields);
	if (error != 0) {
		return error;
	}
	fputs("} ", output_file);
	error = generate_c_from_identifier(output_file, declaration->identifier);
	if (error != 0) {
		return error;
	}
	fputs(";\n", output_file);

	return 0;	
}

int generate_c_from_enum_field(FILE* output_file, const struct EnumFieldNode* field) {
	if (!field) {
		LOG_ERROR("Failed to generate C code from EnumFieldNode. NULL EnumFieldNode.");
		return 1;
	}

	int error = generate_c_from_identifier(output_file, field->identifier);
	if (error != 0) {
		return error;
	}
	if (field->integer_expression) {
		fputc('=', output_file);
		error = generate_c_from_integer_expression(output_file, field->integer_expression);
		if (error != 0) {
			return error;
		}
	}
	fputs(";\n", output_file);
	return 0;
}

int generate_c_from_enum_field_list(FILE* output_file, const struct EnumFieldListNode* field_list) {
	if (!field_list) {
		LOG_ERROR("Failed to generate C code from EnumFieldListNode. NULL EnumFieldListNode.");
		return 1;
	}

	struct EnumFieldNode** fields = field_list->fields;
	for (size_t i = 0; i < field_list->length; i++) {
		const int error = generate_c_from_enum_field(output_file, fields[i]);
		if (error != 0) {
			return error;
		}
	}
	return 0;
}

int generate_c_from_enum_type_expression(FILE* output_file, const struct EnumTypeExpressionNode* expression) {
	if (!expression) {
		LOG_ERROR("Failed to generate C code from EnumTypeExpressionNode. NULL EnumTypeExpressionNode.");
		return 1;
	}

	fputs("((", output_file);
	int error = generate_c_from_type_identifier(output_file, expression->type);
	fputc(')', output_file);
	if (error != 0) {
		return error;
	}

	error = generate_c_from_identifier(output_file, expression->value);
	if (error != 0) {
		return error;
	}
	fputc(')', output_file);

	return 0;	
}

int generate_c_from_expression(FILE* output_file, const struct ExpressionNode* expression) {
	if (!expression) {
		LOG_ERROR("Failed to generate C code from ExpressionNode. NULL ExpressionNode.");
		return 1;
	}

	switch (expression->kind) {
		case AstCallExpression: {
			return generate_c_from_call_expression(output_file, expression->value.call_expression);
		} break;
		case AstIdentifierExpression: {
			return generate_c_from_identifier_expression(output_file, expression->value.identifier_expression);
		} break;
		case AstListExpression: {
			return generate_c_from_list_expression(output_file, expression->value.list_expression);
		} break;
		case AstNumericExpression: {
			return generate_c_from_numeric_expression(output_file, expression->value.numeric_expression);
		} break;
		case AstStringExpression: {
			return generate_c_from_string_expression(output_file, expression->value.string_expression);
		} break;
		case AstTypeExpression: {
			return generate_c_from_type_expression(output_file, expression->value.type_expression);
		} break;
		default: {
			LOG_ERROR(
				"Failed to generate C code from ExpressionNode. Unknown ExpressionNode kind %d.",
				expression->kind
			);
			return 3;
		} break;
	}
}

int generate_c_from_expression_list(
	FILE* output_file,
	const struct ExpressionListNode* expression_list
) {
	if (!expression_list) {
		LOG_ERROR("Failed to generate C code from ExpressionListNode. NULL ExpressionListNode.");
		return 1;
	}

	for (size_t i = 0; i < expression_list->length; i++) {
		struct ExpressionNode* expression = expression_list->expressions[i];
		const int error = generate_c_from_expression(output_file, expression);
		if (error != 0) {
			return error;
		}
		if (i < expression_list->length - 1) {
			fputs(", ", output_file);
		}
	}

	return 0;
}

int generate_c_from_field(FILE* output_file, const struct FieldNode* field) {
	if (!field) {
		LOG_ERROR("Failed to generate C code from FieldNode. NULL FieldNode.");
		return 1;
	}
	int error = generate_c_from_type_identifier(output_file, field->type_identifier);
	if (error != 0) {
		return error;
	}
	fputc(' ', output_file);
	error = generate_c_from_identifier(output_file, field->identifier);
	if (error != 0) {
		return error;
	}
	fputs(";\n", output_file);
	return 0;
}

int generate_c_from_field_binding(FILE* output_file, const struct FieldBindingNode* field_binding) {
	if (!field_binding) {
		LOG_ERROR("Failed to generate C code from FieldBindingNode. NULL FieldBindingNode.");
		return 1;
	}
	fputc('.', output_file);
	int error = generate_c_from_identifier(output_file, field_binding->identifier);
	if (error != 0) {
		return error;
	}
	fputc('=', output_file);
	error = generate_c_from_expression(output_file, field_binding->expression);
	if (error != 0) {
		return error;
	}
	return 0;
}

int generate_c_from_field_binding_list(FILE* output_file, const struct FieldBindingListNode* field_bindings) {
	if (!field_bindings) {
		LOG_ERROR("Failed to generate C code from FieldBindingListNode. NULL FieldBindingListNode.");
		return 1;
	}
	for (size_t i = 0; i < field_bindings->length; i++) {
		const int error = generate_c_from_field_binding(output_file, field_bindings->field_bindings[i]);
		if (error != 0) {
			return error;
		}
		if (i < field_bindings->length - 1) {
			fputs(", ", output_file);
		}
	}
	return 0;
}

int generate_c_from_field_list(FILE* output_file, const struct FieldListNode* field_list) {
	if (!field_list) {
		LOG_ERROR("Failed to generate C code from FieldListNode. NULL FieldListNode.");
		return 1;
	}
	struct FieldNode** fields = field_list->fields;
	for (size_t i = 0; i < field_list->length; i++) {
		const int error = generate_c_from_field(output_file, fields[i]);
		if (error != 0) {
			return error;
		}
	}
	return 0;
}

int _generate_c_function_signature(FILE* output_file, const struct FunctionDeclarationNode* function_declaration, const bool is_inline) {
	if (!function_declaration) {
		LOG_ERROR("Failed to generate function signature from FunctionDeclarationNode. NULL FunctionDeclarationNode.");
		return 1;
	}

	if (is_inline) {
		fputs(
			#if defined(_WIN32) || defined(_WIN64)
			"static "
			#endif
			"inline ",
			output_file
		);
	}

	if (strcmp("void", function_declaration->return_type->identifier->name) == 0) {
		LOG_ERROR("Unsupported return type: void");
		return 1;
	}
	int error = generate_c_from_type_identifier(output_file, function_declaration->return_type);
	if (error != 0) {
		return error;
	}
	fputc(' ', output_file);
	error = generate_c_from_identifier(output_file, function_declaration->identifier);
	if (error != 0) {
		return error;
	}
	fputc('(', output_file);
	error = generate_c_from_parameter_list(output_file, function_declaration->parameters);
	if (error != 0) {
		return error;
	}
	fputc(')', output_file);

	return 0;
}

int _generate_c_function_declaration(
	FILE* output_file,
	const struct FunctionDeclarationNode* function_declaration
) {
	if (!function_declaration) {
		LOG_ERROR("Failed to generate C function declaration from FunctionDeclarationNode. NULL FunctionDeclarationNode.");
		return 1;
	}

	if (!_is_main(function_declaration)) {
		const int error = _generate_c_function_signature(output_file, function_declaration, _should_inline(function_declaration));
		if (error != 0) {
			return error;
		}
		fputs(";\n", output_file);
	}
	return 0;
}

int _generate_c_function_definition(
	FILE* output_file,
	const struct FunctionDeclarationNode* function_declaration
) {
	if (!function_declaration) {
		LOG_ERROR("Failed to generate C function definition from FunctionDeclarationNode. NULL FunctionDeclarationNode.");
		return 1;
	}

	int error = _generate_c_function_signature(output_file, function_declaration, false);
	if (error != 0) {
		LOG_ERROR("Failed to generate C function signature from FunctionDeclarationNode: %d", error);
		return error;
	}
	fputs(" {\n", output_file);
	struct DoStatementNode* body = function_declaration->body;
	error = generate_c_from_do_statement(output_file, body);
	if (error != 0) {
		LOG_ERROR("Failed to generate C function body from Do Statement: %d", error);
		return error;
	}
	fputs("}\n", output_file);

	return 0;
}

int generate_c_from_function_declaration(
	FILE* output_file,
	const struct FunctionDeclarationNode* function_declaration
) {
	if (!function_declaration) {
		LOG_ERROR("Failed to generate C code from FunctionDeclarationNode. NULL FunctionDeclarationNode.");
		return 1;
	}

	int error = _generate_c_function_declaration(output_file, function_declaration);
	if (error != 0) {
		LOG_ERROR("Failed to generate C function definition from FunctionDeclarationNode: %d", error);
		return error;
	}
	error = _generate_c_function_definition(output_file, function_declaration);
	if (error != 0) {
		LOG_ERROR("Failed to generate C function declaration from FunctionDeclarationNode: %d", error);
		return error;
	}

	return 0;
}

int generate_c_from_identifier(FILE* output_file, const struct IdentifierNode* identifier) {
	if (!identifier) {
		LOG_ERROR("Failed to generate C code from IdentifierNode. NULL IdentifierNode.");
		return 1;
	}
	const size_t length = strlen(identifier->name) + 1;
	char* transformed_name = malloc(sizeof(char) * length);
	strncpy(transformed_name, identifier->name, length);
	for (size_t i = 0; i < length; i++) {
		const char c = transformed_name[i];
		switch (c) {
			case '/': 
			case '\\': {
				transformed_name[i] = '_';
			} break;
		}
	}
	fputs(transformed_name, output_file);
	free(transformed_name);
	return 0;
}

int generate_c_from_identifier_expression(FILE* output_file, const struct IdentifierExpressionNode* identifier_expression) {
	if (!identifier_expression) {
		LOG_ERROR("Failed to generate C code from IdentifierExpressionNode. NULL IdentifierExpressionNode.");
		return 1;
	}
	int error = generate_c_from_identifier(output_file, identifier_expression->identifier);
	if (error != 0) {
		return error;
	}
	if (identifier_expression->next) {
		fputc('.', output_file);
		error = generate_c_from_identifier_expression(output_file, identifier_expression->next);
		if (error != 0) {
			return error;
		}
	}

	return 0;
}

int generate_c_from_import_statement(FILE* output_file, const struct ImportStatementNode* import_statement) {
	if (!import_statement) {
		LOG_ERROR("Failed to generate C code from ImportStatementNode. NULL ImportStatementNode.");
		return 1;
	}

	const size_t length = (strlen(import_statement->module_name->value) - 1);
	char* source_file_path = malloc(sizeof(char) * length);
	memset(source_file_path, '\0', sizeof(char) * length);
	strncpy(source_file_path, (import_statement->module_name->value + 1), length - 1);
	switch (import_statement->import_kind) {
		case ImportStatement: {
			if (_is_file_imported(source_file_path)) {
				free(source_file_path);
				source_file_path = NULL;
				break;
			}
			FILE* source_file = lex_open_file(source_file_path, imported_file_paths[imported_file_count++]);
			if (!source_file) {
				free(source_file_path);
				source_file_path = NULL;
				return 1;
			}
			struct Token* tokens = lex_file(source_file_path, source_file);
			fclose(source_file);
			struct ProgramNode* imported_program = ast_parse_program(&tokens);
			if (!imported_program) {
				LOG_ERROR("Failed to parse imported program: %s", source_file_path);
				free(source_file_path);
				source_file_path = NULL;
				return 1;
			}

			free(source_file_path);
			source_file_path = NULL;

			const int error = generate_c_from_module_statement_list(
				output_file,
				imported_program->module_statements
			);
			ast_free_program_node(imported_program);
			imported_program = NULL;
			if (error != 0) {
				return error;
			}
		} break;
		case ImportCStatement: {
			fprintf(output_file, "#include \"%s\"\n", source_file_path);
			free(source_file_path);
		} break;
		default: {
			LOG_ERROR(
				"Failed to generate C code from ImportStatementNode. Invalid ImportKind %d",
				import_statement->import_kind
			);

			free(source_file_path);

			return 1;
		}
	}
	return 0;
}

int generate_c_from_integer_expression(FILE* output_file, const struct IntegerExpressionNode* integer_expression) {
	if (!integer_expression) {
		LOG_ERROR("Failed to generate C code from IntegerExpressionNode. NULL IntegerExpressionNode.");
		return 1;
	}

	fprintf(output_file, "%lld", integer_expression->value);

	return 0;
}

int generate_c_from_let_binding(
	FILE* output_file,
	const struct LetBindingNode* let_binding
) {
	if (!let_binding) {
		LOG_ERROR("Failed to generate C code from LetBindingNode. NULL LetBindingNode.");
		return 1;
	}

	fputs("const ", output_file);
	const int error = _generate_c_variable_declaration(
		output_file,
		let_binding->type,
		let_binding->binding,
		let_binding->expression
	);
	if (error != 0) {
		return error;
	}
	fputs(";\n", output_file);
	
	return 0;
}

int generate_c_from_list_expression(FILE* output_file, const struct ListExpressionNode* list_expression) {
	if (!list_expression) {
		LOG_ERROR("Failed to generate C code from ListExpressionNode. NULL ListExpressionNode.");
		return 1;
	}
	
	fputc('{', output_file);
	const int error = generate_c_from_expression_list(
		output_file,
		list_expression->expressions
	);
	if (error != 0) {
		return error;
	}
	fputc('}', output_file);

	return 0;	
}

int generate_c_from_match_statement(FILE* output_file, const struct MatchStatementNode* match_expression) {
	if (!match_expression) {
		LOG_ERROR("Failed to generate C code from MatchStatementNode. NULL MatchStatementNode.");
		return 1;
	}

	return generate_c_from_match_case_list(output_file, match_expression->case_list);
}

int generate_c_from_match_case_list(FILE* output_file, const struct MatchCaseListNode* case_list) {
	if (!case_list) {
		LOG_ERROR("Failed to generate C code from MatchCaseListNode. NULL MatchCaseListNode.");
		return 1;
	}

	for (size_t i = 0; i < case_list->length; i++) {
		const struct MatchCaseNode* match_case = case_list->cases[i];
		bool is_default = strcmp("default", match_case->condition->function->name) == 0;
		if (!is_default){
			fputs("if (", output_file);
			const int error = generate_c_from_call_expression(output_file, match_case->condition);
			if (error != 0) {
				return error;
			}
			fputs(")\n{\n", output_file);
		} else {
			if (i != case_list->length - 1) {
				LOG_ERROR("Default must be the last case in a match");
				return 1;
			}
			fputs("\n{\n", output_file);
		}
		const int error = generate_c_from_statement(output_file, match_case->statement, true);
		if (error != 0) {
			return error;
		}
		fputs(";\n}\n", output_file);
		if (i < case_list->length - 1) {
			fputs("else ", output_file);
		}
	}

	return 0;
}

int generate_c_from_module_statement(
	FILE* output_file,
	const struct ModuleStatementNode* declaration
) {
	if (!declaration) {
		LOG_ERROR("Failed to generate C code from ModuleStatementNode. NULL ModuleStatementNode.");
		return 1;
	}
	switch (declaration->kind) {
		case AstFunctionDeclaration: {
			return generate_c_from_function_declaration(
				output_file,
				declaration->value.function_declaration
			);
		} break;
		case AstImportStatement: {
			return generate_c_from_import_statement(
				output_file,
				declaration->value.import_statement
			);
		} break;
		case AstLetBinding: {
			return generate_c_from_let_binding(
				output_file,
				declaration->value.let_binding
			);
		} break;
		case AstTypeDeclaration: {
			return generate_c_from_type_declaration(
				output_file,
				declaration->value.type_declaration
			);
		} break;
		default: {
			LOG_ERROR(
				"Failed to generate C code from ModuleStatementNode. Unknown ModuleStatementNode kind %d",
				declaration->kind
			);
			return 1;
		} break;
	}
}

// TODO: Simplify by passing in a function to generate code
int _generate_c_from_module_statement_list_by_kind(
	FILE* output_file,
	const struct ModuleStatementListNode* module_statement_list,
	const AstNodeKind kind
) {
	if (!module_statement_list) {
		LOG_ERROR("Failed to generate C code from ModuleStatementListNode for AstNodeKind: %d. NULL ModuleStatementListNode.", kind);
		return 1;
	}
	struct ModuleStatementNode** module_statements = module_statement_list->module_statements;
	for (size_t i = 0; i < module_statement_list->length; i++) {
		const struct ModuleStatementNode* module_statement = module_statements[i];
		if (module_statement->kind != kind) {
			continue;
		}
		const int error = generate_c_from_module_statement(output_file, module_statement);
		if (error != 0) {
			return error;
		}
		fputc('\n', output_file);
	}
	return 0;
}

int generate_c_from_module_statement_list(
	FILE* output_file,
	const struct ModuleStatementListNode* module_statement_list
) {
	if (!module_statement_list) {
		LOG_ERROR("Failed to generate C code from ModuleStatementListNode. NULL ModuleStatementListNode.");
		return 1;
	}
	int error = _generate_c_from_module_statement_list_by_kind(output_file, module_statement_list, AstImportStatement);
	if (error != 0) {
		LOG_ERROR("Failed to generate C code for import statements");
		return error;
	}
	error = _generate_c_from_module_statement_list_by_kind(output_file, module_statement_list, AstTypeDeclaration);
	if (error != 0) {
		LOG_ERROR("Failed to generate C code for type declarations.");
		return error;
	}
	
	const struct ModuleStatementNode** module_statements = module_statement_list->module_statements;
	for (size_t i = 0; i < module_statement_list->length; i++) {
		const struct ModuleStatementNode* module_statement = module_statements[i];
		if (module_statement->kind != AstFunctionDeclaration) {
			continue;
		}
		error = _generate_c_function_declaration(output_file, module_statement->value.function_declaration);
		if (error != 0) {
			LOG_ERROR("Failed to generate C function declaration from module statement list: %d", error);
			return error;
		}
	}

	error = _generate_c_from_module_statement_list_by_kind(output_file, module_statement_list, AstLetBinding);
	if (error != 0) {
		LOG_ERROR("Failed to generate C code for let bindings.");
		return error;
	}

	for (size_t i = 0; i < module_statement_list->length; i++) {
		const struct ModuleStatementNode* module_statement = module_statements[i];
		if (module_statement->kind != AstFunctionDeclaration) {
			continue;
		}
		error = _generate_c_function_definition(output_file, module_statement->value.function_declaration);
		if (error != 0) {
			LOG_ERROR("Failed to generate C function definition from module statement list: %d", error);
			return error;
		}
	}
	return 0;
}

int generate_c_from_mut_binding(
	FILE* output_file,
	const struct MutBindingNode* mut_binding
) {
	if (!mut_binding) {
		LOG_ERROR("Failed to generate C code from MutBindingNode. NULL MutBindingNode.");
		return 1;
	}

	const int error = _generate_c_variable_declaration(
		output_file,
		mut_binding->type,
		mut_binding->binding,
		mut_binding->expression
	);
	if (error != 0) {
		return error;
	}
	fputs(";\n", output_file);

	return 0;
}

int generate_c_from_numeric_expression(FILE* output_file, const struct NumericExpressionNode* numeric_expression) {
	if (!numeric_expression) {
		LOG_ERROR("Failed to generate C code from NumericExpressionNode. NULL NumericExpressionNode.");
		return 1;
	}

	switch (numeric_expression->kind) {
		case AstDoubleExpression: {
			return generate_c_from_double_expression(output_file, numeric_expression->value.double_expression);
		} break;
		case AstIntegerExpression: {
			return generate_c_from_integer_expression(output_file, numeric_expression->value.integer_expression);
		} break;
		default: {
			LOG_ERROR(
				"Failed to generate C code from NumericExpressionNode. Unknown NumericExpressionNode kind %d.",
				numeric_expression->kind
			);
			return 2;
		} break;
	}
}

int generate_c_from_parameter(FILE* output_file, const struct ParameterNode* parameter) {
	if (!parameter) {
		LOG_ERROR("Failed to generate C code from ParameterNode. NULL ParameterNode.");
		return 1;
	}
	if (!_is_pointer_type(parameter->type_identifier)) {
		fputs("const ", output_file);
	}
	int error = generate_c_from_type_identifier(output_file, parameter->type_identifier);
	if (error != 0) {
		return error;
	}
	fputc(' ', output_file);
	error = generate_c_from_identifier(output_file, parameter->identifier);
	if (error != 0) {
		return error;
	}
	struct TypeIdentifierNode* current_type = parameter->type_identifier;
	while (
		current_type &&
		(strcmp(current_type->identifier->name, "array") == 0)
	 ) {
		fputs("[]", output_file);
		current_type = current_type->contained_type;
	}

	return 0;
}

int generate_c_from_parameter_list(FILE* output_file, const struct ParameterListNode* parameter_list) {
	if (!parameter_list) {
		LOG_ERROR("Failed to generate C code from ParameterListNode. NULL ParameterListNode.");
		return 1;
	}
	struct ParameterNode** parameters = parameter_list->parameters;
	for (size_t i = 0; i < parameter_list->length; i++) {
		const int error = generate_c_from_parameter(output_file, parameters[i]);
		if (error != 0) {
			return error;
		}
		if (i < parameter_list->length - 1) {
			fputs(", ", output_file);
		}
	}
	return 0;
}

int generate_c_from_program(
	FILE* output_file,
	const struct ProgramNode* program
) {
	if (!program) {
		LOG_ERROR("Failed to generate C code from ProgramNode. NULL ProgramNode.");
		return 1;
	}
	if (!program->module_statements) {
		LOG_ERROR("Failed to generate C code. No module statements found. At minimum, a main function must be provided as an entrypoint.");
		return 3;
	}
	int error = generate_c_from_shebang(
		output_file,
		program->shebang
	);
	if (error != 0) {
		return error;
	}
	error = generate_c_from_module_statement_list(
		output_file,
		program->module_statements
	);
	if (error != 0) {
		return error;
	}
	fputc('\n', output_file);
	return 0;
}

int generate_c_from_return_statement(FILE* output_file, const struct ReturnStatementNode* return_statement) {
	if (!return_statement) {
		LOG_ERROR("Failed to generate C code from ReturnStatementNode. NULL ReturnStatementNode.");
		return 1;
	}
	fputs("return ", output_file);
	const int error = generate_c_from_expression(output_file, return_statement->expression);
	if (error != 0) {
		return error;
	}

	return 0;
}

int generate_c_from_shebang(FILE* output_file, const struct ShebangNode* shebang) {
	if (!shebang) {
		LOG_DEBUG("NULL ShebangNode");
	}

	return 0;
}

int generate_c_from_statement(FILE* output_file, const struct StatementNode* statement, const bool will_return) {
	if (!statement) {
		LOG_ERROR("Failed to generate C code from StatementNode. NULL StatementNode.");
		return 1;
	}

	switch (statement->kind) {
		case AstBindingStatement: {
			if (will_return) {
				LOG_ERROR("A binding statement cannot be the final statement in a block");
				return 2;
			}
			return generate_c_from_binding_statement(output_file, statement->value.binding_statement);
		} break;
    case AstDoStatement: {
			return generate_c_from_do_statement(output_file, statement->value.do_statement);
		} break;
		case AstMatchStatement: {
			return generate_c_from_match_statement(output_file, statement->value.match_statement);
		} break;
		case AstReturnStatement: {
			return generate_c_from_return_statement(output_file, statement->value.return_statement);
		} break;
		case AstExpression: {
			if (will_return) {
				fputs("return ", output_file);
			}
			return generate_c_from_expression(output_file, statement->value.expression);
		} break;
		default: {
			LOG_ERROR(
				"Failed to generate C code from StatementNode. Unknown StatementNode kind %d.",
				statement->kind
			);
			return 2;
		} break;
	}
}

int generate_c_from_statement_list(
	FILE* output_file,
	const struct StatementListNode* statement_list
) {
	if (!statement_list) {
		LOG_ERROR("Failed to generate C code from StatementListNode. NULL StatementListNode.");
		return 1;
	}

	for (size_t i = 0; i < statement_list->length; i++) {
		struct StatementNode* statement = statement_list->statements[i];
		const int error = generate_c_from_statement(output_file, statement, (i == statement_list->length - 1));
		if (error != 0) {
			return error;
		}
		if (statement->kind == AstMatchStatement) {
			continue;
		}
		fputs(";\n", output_file);
	}

	return 0;
}

int generate_c_from_string_expression(FILE* output_file, const struct StringExpressionNode* string_expression) {
	if (!string_expression) {
		LOG_ERROR("Failed to generate C code from StringExpressionNode. NULL StringExpressionNode.");
		return 1;
	}
	fprintf(output_file, "%s", string_expression->value);

	return 0;
}

int generate_c_from_struct_type_declaration(FILE* output_file, const struct StructTypeDeclarationNode* struct_type_declaration) {
	if (!struct_type_declaration) {
		LOG_ERROR("Failed to generate C code from StructTypeDeclarationNode. NULL StructTypeDeclarationNode.");
		return 1;
	}

	fputs("typedef struct {\n", output_file);
	int error = generate_c_from_field_list(output_file, struct_type_declaration->fields);
	if (error != 0) {
		return error;
	}
	fputs("} ", output_file);
	error = generate_c_from_identifier(output_file, struct_type_declaration->identifier);
	if (error != 0) {
		return error;
	}
	fputs(";\n", output_file);

	return 0;	
}

int generate_c_from_structured_type_expression(FILE* output_file, const struct StructuredTypeExpressionNode* expression) {
	if (!expression) {
		LOG_ERROR("Failed to generate C code from StructuredTypeExpressionNode. NULL StructuredTypeExpressionNode.");
		return 1;
	}

	fputc('(', output_file);
	int error = generate_c_from_type_identifier(output_file, expression->type);
	fputc(')', output_file);
	if (error != 0) {
		return error;
	}
	
	fputc('{', output_file);
	error = generate_c_from_field_binding_list(
		output_file,
		expression->field_bindings
	);
	if (error != 0) {
		return error;
	}
	fputc('}', output_file);

	return 0;	
}

int generate_c_from_type_declaration(FILE* output_file, const struct TypeDeclarationNode* type_declaration) {
	if (!type_declaration) {
		LOG_ERROR("Failed to generate C code from TypeDeclarationNode. NULL TypeDeclarationNode.");
		return 1;
	}

	switch (type_declaration->kind) {
		case AstEnumTypeDeclaration: {
			return generate_c_from_enum_declaration(output_file, type_declaration->value.enum_type_declaration);
		} break;
		case AstStructTypeDeclaration: {
			return generate_c_from_struct_type_declaration(output_file, type_declaration->value.struct_type_declaration);
		} break;
		case AstUnionTypeDeclaration: {
			return generate_c_from_union_type_declaration(output_file, type_declaration->value.union_type_declaration);
		} break;
		default: {
			LOG_ERROR(
				"Failed to generate C code from TypeDeclarationNode. Unknown TypeDeclarationNode kind %d.",
				type_declaration->kind
			);
			return 2;
		} break;
	}
}

int generate_c_from_type_expression(FILE* output_file, const struct TypeExpressionNode* type_expression) {
	if (!type_expression) {
		LOG_ERROR("Failed to generate C code from TypeExpressionNode. NULL TypeExpressionNode.");
		return 1;
	}

	switch (type_expression->kind) {
		case AstEnumTypeExpression: {
			return generate_c_from_enum_type_expression(output_file, type_expression->value.enum_type_expression);
		} break;
		case AstStructuredTypeExpression: {
			return generate_c_from_structured_type_expression(output_file, type_expression->value.structured_type_expression);
		} break;
		default: {
			LOG_ERROR(
				"Failed to generate C code from TypeExpressionNode. Unknown TypeExpressionNode kind %d.",
				type_expression->kind
			);
			return 2;
		} break;
	}

	// fputc('(', output_file);
	// int error = generate_c_from_type_identifier(output_file, type_expression->type);
	// fputc(')', output_file);
	// if (error != 0) {
	// 	return error;
	// }
	
	// fputc('{', output_file);
	// error = generate_c_from_field_binding_list(
	// 	output_file,
	// 	type_expression->field_bindings
	// );
	// if (error != 0) {
	// 	return error;
	// }
	// fputc('}', output_file);

	// return 0;	
}

int generate_c_from_type_identifier(FILE* output_file, const struct TypeIdentifierNode* type_identifier) {
	if (!type_identifier) {
		LOG_ERROR("Failed to generate C code from TypeIdentifierNode. NULL TypeIdentifierNode.");
		return 1;
	}
	if (strcmp(type_identifier->identifier->name, "ptr") == 0) {
		if (type_identifier->contained_type) {
			const int error = generate_c_from_type_identifier(output_file, type_identifier->contained_type);
			if (error != 0) {
				return error;
			}
		}
		fputc('*', output_file);
		return 0;
	}
	if (strcmp(type_identifier->identifier->name, "array") == 0) {
		if (type_identifier->contained_type) {
			const int error = generate_c_from_type_identifier(output_file, type_identifier->contained_type);
			if (error != 0) {
				return error;
			}
		}
		return 0;
	}
	const int error = generate_c_from_identifier(output_file, type_identifier->identifier);
	if (error != 0) {
		return error;
	}
	return 0;
}

int generate_c_from_union_type_declaration(FILE* output_file, const struct UnionTypeDeclarationNode* union_type_declaration) {
	if (!union_type_declaration) {
		LOG_ERROR("Failed to generate C code from UnionTypeDeclarationNode. NULL UnionTypeDeclarationNode.");
		return 1;
	}

	fputs("typedef union {\n", output_file);
	int error = generate_c_from_field_list(output_file, union_type_declaration->fields);
	if (error != 0) {
		return error;
	}
	fputs("} ", output_file);
	error = generate_c_from_identifier(output_file, union_type_declaration->identifier);
	if (error != 0) {
		return error;
	}
	fputs(";\n", output_file);

	return 0;	
}

int generate_c_macros(FILE* output_file) {
	fputs("#define add(x, y) ((x) + (y))\n", output_file);
	fputs("#define and(x, y) ((x) && (y))\n", output_file);
	fputs("#define cast(type, x) ((type) x)\n", output_file);
	fputs("#define ccstring const char *\n", output_file);
	fputs("#define cstring char *\n", output_file);
	fputs("#define delete(x) { (free((void*)x)); x = NULL; }\n", output_file);
	fputs("#define deref(x) *(x)\n", output_file);
	fputs("#define div(x, y) ((x) / (y))\n", output_file);
	fputs("#define eq(x, y) ((x) == (y))\n", output_file);
	fputs("#define equals(x, y) ((x) == (y))\n", output_file);
	fputs("#define falsey(x) (!(x))\n", output_file);
	fputs("#define gt(x, y) ((x) > (y))\n", output_file);
	fputs("#define gte(x, y) ((x) >= (y))\n", output_file);
	fputs("#define interpolate_cstring(x, y) x y\n", output_file);
	fputs("#define lt(x, y) ((x) < (y))\n", output_file);
	fputs("#define lte(x, y) ((x) <= (y))\n", output_file);
	fputs("#define mod(x, y) ((x) % (y))\n", output_file);
	fputs("#define mul(x, y) ((x) * (y))\n", output_file);
	fputs("#define nand(x, y) (!((x) && (y)))\n", output_file);
	fputs("#define neg(x) (-(x))\n", output_file);
	fputs("#define nor(x, y) (!((x) || (y)))\n", output_file);
	fputs("#define not(x) (!(x))\n", output_file);
	fputs("#define or(x, y) ((x) || (y))\n", output_file);
	fputs("#define point(x) &(x)\n", output_file);
	fputs("#define sub(x, y) ((x) - (y))\n", output_file);
	fputs("#define truthy(x) (x)\n", output_file);
	fputs("#define xor(x, y) ((x) ^ (y))\n", output_file);
	fputs("#define xnor(x, y) (!((x) ^ (y)))\n", output_file);
	fputs("#define unsafe_index(arr, index) (arr)[(index)]\n", output_file);
	fputs("#define unused(x) (void)(x)\n", output_file);
	fputc('\n', output_file);

	return 0;
}

int _generate_c_variable_declaration(
	FILE* output_file,
	const struct TypeIdentifierNode* type,
	const struct IdentifierNode* binding,
	const struct ExpressionNode* expression
) {
	int error = generate_c_from_type_identifier(output_file, type);
	if (error != 0) {
		LOG_ERROR("Failed to generate C variable declaration. Failed to generate type identifier.");
		return error;
	}
	fputc(' ', output_file);
	error = generate_c_from_identifier(output_file, binding);
	if (error != 0) {
		LOG_ERROR("Failed to generate C variable declaration. Failed to generate binding identifier.");
		return error;
	
	}
	struct TypeIdentifierNode* current_type = type;
	while (
		current_type &&
		(strcmp(current_type->identifier->name, "array") == 0)
	 ) {
		fputs("[]", output_file);
		current_type = current_type->contained_type;
	}
	fputc('=', output_file);
	error = generate_c_from_expression(output_file, expression);
	if (error != 0) {
		LOG_ERROR("Failed to generate C variable declaration. Failed to generate expression.");
		return error;
	}
}

bool _is_file_imported(const char* source_file_path) {
        char* standard_library_directory = get_standard_library_directory();
	char* package_directory = malloc(sizeof(char) * (strlen(standard_library_directory) + strlen(PACKAGE_DIRECTORY) + 2));
	sprintf(package_directory, "%s" PACKAGE_DIRECTORY, standard_library_directory);
	free(standard_library_directory);
        standard_library_directory = NULL;
        char* full_package_path = malloc(strlen(package_directory) + strlen(source_file_path) + 2);
	sprintf(full_package_path, "%s/%s", package_directory, source_file_path);
	free(package_directory);
	package_directory = NULL;
	
	char* full_local_path = malloc(strlen("./") + strlen(source_file_path) + 2);
	sprintf(full_local_path, "./%s", source_file_path);
	
	for (int i = 0; i < imported_file_count; i++) {
		const char* imported_file_path = imported_file_paths[i];
		if (
			strcmp(imported_file_path, full_package_path) == 0 ||
			strcmp(imported_file_path, full_local_path) == 0
		) {
			free(full_local_path);
			free(full_package_path);
			full_local_path = NULL;
			full_package_path = NULL;
			return true;
		}
	}
	free(full_local_path);
	free(full_package_path);
	full_local_path = NULL;
	full_package_path = NULL;
	return false;
}

bool _is_main(const struct FunctionDeclarationNode* function_declaration) {
	return (
		function_declaration &&
		function_declaration->identifier &&
		function_declaration->identifier->name &&
		strcmp("main", function_declaration->identifier->name) == 0
	);
}

bool _is_pointer_type(const struct TypeIdentifierNode* type_identifier) {
	return (
		type_identifier &&
		type_identifier->identifier &&
		type_identifier->identifier->name &&
		strcmp("ptr", type_identifier->identifier->name) == 0
	);
}

FILE* _open_output_file(const char* output_file_path) {
	FILE* file = fopen(output_file_path, "w+");
	if (file == NULL) {
		LOG_ERROR("Could not open file %s", output_file_path);
		return NULL;
	}
	return file;
}

bool _should_inline(const struct FunctionDeclarationNode* function_declaration) {
	return !_is_main(function_declaration);
}
