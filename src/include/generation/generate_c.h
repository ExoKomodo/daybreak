#pragma once

#include <stdbool.h>

#include <parser/prelude.h>
#include <macros/helpers.h>

int generate_c_code(struct ProgramNode*, const char*);
int generate_c_from_binding_expression(FILE*, struct BindingExpressionNode*);
int generate_c_from_call_expression(FILE*, struct CallExpressionNode*);
int generate_c_from_declaration(FILE*, struct DeclarationNode*);
int generate_c_from_declaration_list(FILE*, struct DeclarationListNode*);
int generate_c_from_expression(FILE*, struct ExpressionNode*);
int generate_c_from_expression_list(FILE*, struct ExpressionListNode*, bool);
int generate_c_from_function_declaration(FILE*, struct FunctionDeclarationNode*);
int generate_c_from_identifier(FILE*, struct IdentifierNode*);
int generate_c_from_identifier_expression(FILE*, struct IdentifierExpressionNode*);
int generate_c_from_parameter(FILE*, struct ParameterNode*);
int generate_c_from_parameter_list(FILE*, struct ParameterListNode*);
int generate_c_from_numeric_expression(FILE*, struct NumericExpressionNode*);
int generate_c_from_program(FILE*, struct ProgramNode*);
int generate_c_from_return_expression(FILE*, struct ReturnExpressionNode*);
int generate_c_from_string_expression(FILE*, struct StringExpressionNode*);
int generate_c_include_prelude(FILE*);
int generate_c_macros(FILE*);
FILE* _open_output_file(const char*);

int generate_c_code(
	struct ProgramNode* program,
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

	return 0;
}

int generate_c_include_prelude(FILE* output_file) {
	fputs("#include <stdbool.h>\n", output_file);
	fputs("#include <stdlib.h>\n", output_file);
	fputs("#include <stdio.h>\n\n", output_file);
	return 0;
}

int generate_c_from_binding_expression(
	FILE* output_file,
	struct BindingExpressionNode* binding_expression
) {
	if (!binding_expression) {
		LOG_ERROR("Failed to generate C code from BindingExpressionNode. NULL BindingExpressionNode.");
		return 1;
	}

	fprintf(output_file, "const %s %s = ", binding_expression->type->name, binding_expression->binding->name);
	const int error = generate_c_from_expression(output_file, binding_expression->expression);
	return error;
}

int generate_c_from_call_expression(FILE* output_file, struct CallExpressionNode* call_expression) {
	if (!call_expression) {
		LOG_ERROR("Failed to generate C code from CallExpressionNode. NULL CallExpressionNode.");
		return 1;
	}

	fprintf(output_file, "%s(", call_expression->function->name);
	const int error = generate_c_from_expression_list(output_file, call_expression->arguments, false);
	fputs(")", output_file);
	return error;
}

int generate_c_from_declaration(
	FILE* output_file,
	struct DeclarationNode* declaration
) {
	if (!declaration) {
		LOG_ERROR("Failed to generate C code from DeclarationNode. NULL DeclarationNode.");
		return 1;
	}
	switch (declaration->kind) {
		case AstFunctionDeclaration: {
			return generate_c_from_function_declaration(
				output_file,
				declaration->value.function_declaration
			);
		} break;
		default: {
			LOG_ERROR(
				"Failed to generate C code from DeclarationNode. Unknown DeclarationNode kind %d",
				declaration->kind
			);
			return 1;
		} break;
	}
}

int generate_c_from_declaration_list(
	FILE* output_file,
	struct DeclarationListNode* declaration_list
) {
	if (!declaration_list) {
		LOG_ERROR("Failed to generate C code from DeclarationListNode. NULL DeclarationListNode.");
		return 1;
	}
	struct DeclarationNode** declarations = declaration_list->declarations;
	for (size_t i = 0; i < declaration_list->length; i++) {
		const int error = generate_c_from_declaration(output_file, declarations[i]);
		if (error != 0) {
			return error;
		}
	}
	return 0;
}

int generate_c_from_expression(FILE* output_file, struct ExpressionNode* expression) {
	if (!expression) {
		LOG_ERROR("Failed to generate C code from ExpressionNode. NULL ExpressionNode.");
		return 1;
	}

	switch (expression->kind) {
		case AstBindingExpression: {
			return generate_c_from_binding_expression(output_file, expression->value.binding_expression);
		} break;
		case AstCallExpression: {
			return generate_c_from_call_expression(output_file, expression->value.call_expression);
		} break;
		case AstIdentifierExpression: {
			return generate_c_from_identifier_expression(output_file, expression->value.identifier_expression);
		} break;
		case AstNumericExpression: {
			return generate_c_from_numeric_expression(output_file, expression->value.numeric_expression);
		} break;
		case AstReturnExpression: {
			return generate_c_from_return_expression(output_file, expression->value.return_expression);
		} break;
		case AstStringExpression: {
			return generate_c_from_string_expression(output_file, expression->value.string_expression);
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
	struct ExpressionListNode* expression_list,
	bool is_function_body
) {
	if (!expression_list) {
		LOG_ERROR("Failed to generate C code from ExpressionListNode. NULL ExpressionListNode.");
		return 1;
	}

	for (size_t i = 0; i < expression_list->length; i++) {
		const int error = generate_c_from_expression(output_file, expression_list->expressions[i]);
		if (error != 0) {
			return error;
		}
		if (is_function_body) {
			fputs(";\n", output_file);
		} else if (i < expression_list->length - 1) {
			fputs(", ", output_file);
		}
	}

	return 0;
}

int generate_c_from_function_declaration(
	FILE* output_file,
	struct FunctionDeclarationNode* function_declaration
) {
	if (!function_declaration) {
		LOG_ERROR("Failed to generate C code from FunctionDeclarationNode. NULL FunctionDeclarationNode.");
		return 1;
	}
	int error = generate_c_from_identifier(output_file, function_declaration->return_type);
	if (error != 0) {
		return error;
	}
	fputs(" ", output_file);
	error = generate_c_from_identifier(output_file, function_declaration->identifier);
	if (error != 0) {
		return error;
	}
	fputs("(", output_file);
	error = generate_c_from_parameter_list(output_file, function_declaration->parameters);
	if (error != 0) {
		return error;
	}
	fputs(") {\n", output_file);
	struct ExpressionListNode* expressions = function_declaration->expressions;
	error = generate_c_from_expression_list(output_file, expressions, true);
	if (error != 0) {
		return error;
	}
	fputs("}\n", output_file);

	return 0;
}

int generate_c_from_identifier(FILE* output_file, struct IdentifierNode* identifier) {
	if (!identifier) {
		LOG_ERROR("Failed to generate C code from IdentifierNode. NULL IdentifierNode.");
		return 1;
	}
	fprintf(output_file, "%s", identifier->name);
	return 0;
}

int generate_c_from_identifier_expression(FILE* output_file, struct IdentifierExpressionNode* identifier_expression) {
	if (!identifier_expression) {
		LOG_ERROR("Failed to generate C code from IdentifierExpressionNode. NULL IdentifierExpressionNode.");
		return 1;
	}
	const int error = generate_c_from_identifier(output_file, identifier_expression->identifier);
	if (error != 0) {
		return error;
	}
	return 0;
}

int generate_c_from_numeric_expression(FILE* output_file, struct NumericExpressionNode* numeric_expression) {
	if (!numeric_expression) {
		LOG_ERROR("Failed to generate C code from NumericExpressionNode. NULL NumericExpressionNode.");
		return 1;
	}

	fprintf(output_file, "%d", numeric_expression->value);

	return 0;
}

int generate_c_from_parameter(FILE* output_file, struct ParameterNode* parameter) {
	if (!parameter) {
		LOG_ERROR("Failed to generate C code from ParameterNode. NULL ParameterNode.");
		return 1;
	}
	fprintf(output_file, "%s %s", parameter->type->name, parameter->identifier->name);

	return 0;
}

int generate_c_from_parameter_list(FILE* output_file, struct ParameterListNode* parameter_list) {
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
	struct ProgramNode* program
) {
	if (!program) {
		LOG_ERROR("Failed to generate C code from ProgramNode. NULL ProgramNode.");
		return 1;
	}
	if (!program->declarations) {
		LOG_ERROR("Failed to generate C code. No declarations found. At minimum, a main function must be provided as an entrypoint.");
		return 3;
	}
	const int error = generate_c_from_declaration_list(
		output_file,
		program->declarations
	);
	if (error != 0) {
		return error;
	}
	fputs("\n", output_file);
	return 0;
}

int generate_c_from_string_expression(FILE* output_file, struct StringExpressionNode* string_expression) {
	if (!string_expression) {
		LOG_ERROR("Failed to generate C code from StringExpressionNode. NULL StringExpressionNode.");
		return 1;
	}
	fprintf(output_file, "%s", string_expression->value);

	return 0;
}

int generate_c_from_return_expression(FILE* output_file, struct ReturnExpressionNode* return_expression) {
	if (!return_expression) {
		LOG_ERROR("Failed to generate C code from ReturnExpressionNode. NULL ReturnExpressionNode.");
		return 1;
	}
	fputs("return ", output_file);
	const int error = generate_c_from_expression(output_file, return_expression->expression);
	if (error != 0) {
		return error;
	}

	return 0;
}

int generate_c_macros(FILE* output_file) {
	fputs("#define ccstring const char *\n", output_file);
	fputs("#define cstring char *\n", output_file);
	fputs("#define add(x, y) ((x) + (y))\n", output_file);
	fputs("#define sub(x, y) ((x) - (y))\n", output_file);
	fputs("#define mul(x, y) ((x) * (y))\n", output_file);
	fputs("#define div(x, y) ((x) / (y))\n", output_file);
	fputs("#define mod(x, y) ((x) % (y))\n\n", output_file);

	return 0;
}

FILE* _open_output_file(const char* output_file_path) {
	FILE* file = fopen(output_file_path, "w+");
	if (file == NULL) {
		LOG_ERROR("Could not open file %s", output_file_path);
		return NULL;
	}
	return file;
}
