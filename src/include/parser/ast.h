#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdint.h>

#include <lex/token.h>
#include <log/prelude.h>
#include <macros/helpers.h>

#define _CHECK_TOKENS() do { \
  if (!tokens || !*tokens) { \
    return NULL; \
  } \
} while (0);

#define _ADVANCE_TOKEN(tokens) do { \
  token_chomp(tokens); \
} while (0);


/*********************/
/* Type Declarations */
/*********************/

typedef enum {
  AstBlank,
  AstBindingStatement,
  AstCallExpression,
  AstDoStatement,
  AstDoubleExpression,
  AstEnumTypeDeclaration,
  AstEnumField,
  AstEnumFieldList,
  AstEnumTypeExpression,
  AstExpression,
  AstExpressionList,
  AstField,
  AstFieldBinding,
  AstFieldBindingList,
  AstFieldList,
  AstFunctionDeclaration,
  AstIdentifier,
  AstIdentifierExpression,
  AstImportStatement,
  AstIntegerExpression,
  AstLetBinding,
  AstListExpression,
  AstMatchCase,
  AstMatchCaseList,
  AstMatchStatement,
  AstModuleStatement,
  AstModuleStatementList,
  AstMutBinding,
  AstMutExpression,
  AstNewAlloc,
  AstNumericExpression,
  AstParameter,
  AstParameterList,
  AstProgram,
  AstReturnStatement,
  AstShebang,
  AstStatement,
  AstStatementList,
  AstStringExpression,
  AstStructTypeDeclaration,
  AstStructuredTypeExpression,
  AstTypeDeclaration,
  AstTypeExpression,
  AstTypeIdentifier,
  AstUnionTypeDeclaration,
} AstNodeKind;

typedef enum {
  ImportStatement,
  ImportCStatement
} ImportNodeKind;

struct AstNode;

struct BindingStatementNode;
struct CallExpressionNode;
struct DoStatementNode;
struct EnumTypeDeclarationNode;
struct EnumFieldNode;
struct EnumFieldListNode;
struct EnumTypeExpressionNode;
struct ExpressionListNode;
struct ExpressionNode;
struct FieldNode;
struct FieldListNode;
struct FunctionDeclarationNode;
struct IdentifierNode;
struct IdentifierExpressionNode;
struct ImportStatementNode;
struct LetBindingNode;
struct ListExpressionNode;
struct MatchCaseNode;
struct MatchCaseListNode;
struct MatchStatementNode;
struct ModuleStatementListNode;
struct ModuleStatementNode;
struct MutBindingNode;
struct MutExpressionNode;
struct NewAllocNode;
struct NumericExpressionNode;
struct ParameterListNode;
struct ParameterNode;
struct ProgramNode;
struct ReturnStatementNode;
struct ShebangNode;
struct StatementNode;
struct StatementListNode;
struct StringExpressionNode;
struct StructTypeDeclarationNode;
struct StructuredTypeExpressionNode;
struct TypeDeclarationNode;
struct TypeExpressionNode;
struct TypeIdentifierNode;
struct UnionTypeDeclarationNode;

union AstNodeUnion;
union BindingStatementNodeUnion;
union ExpressionNodeUnion;
union ModuleStatementNodeUnion;
union MutExpressionNodeUnion;
union NumericExpressionNodeUnion;
union StatementNodeUnion;
union TypeDeclarationNodeUnion;
union TypeExpressionNodeUnion;

union AstNodeUnion {
  struct BindingStatementNode* binding_statement;
  struct CallExpressionNode* call_expression;
  struct DoStatementNode* do_statement;
  struct DoubleExpressionNode* double_expression;
  struct EnumTypeDeclarationNode* enum_type_declaration;
  struct EnumFieldNode* enum_field;
  struct EnumFieldListNode* enum_field_list;
  struct EnumTypeExpressionNode* enum_type_expression;
  struct ExpressionListNode* expression_list;
  struct ExpressionNode* expression;
  struct FieldBindingNode* field_binding;
  struct FieldBindingListNode* field_binding_list;
  struct FieldNode* field;
  struct FieldListNode* field_list;
  struct FunctionDeclarationNode* function_declaration;
  struct IdentifierNode* identifier;
  struct IdentifierExpressionNode* identifier_expression;
  struct IntegerExpressionNode* integer_expression;
  struct ImportStatementNode* import_statement;
  struct LetBindingNode* let_binding;
  struct ListExpressionNode* list_expression;
  struct MatchCaseNode* match_case;
  struct MatchCaseListNode* match_case_list;
  struct MatchStatementNode* match_expression;
  struct ModuleStatementListNode* module_statement_list;
  struct ModuleStatementNode* module_statement;
  struct MutBindingNode* mut_binding;
  struct MutExpressionNode* mut_expression;
  struct NewAllocNode* new_alloc;
  struct NumericExpressionNode* numeric_expression;
  struct ParameterListNode* parameter_list;
  struct ParameterNode* parameter;
  struct ProgramNode* program;
  struct ReturnStatementNode* return_statement;
  struct ShebangNode* shebang;
  struct StatementNode* statement;
  struct StatementListNode* statement_list;
  struct StringExpressionNode* string_expression;
  struct StructTypeDeclarationNode* struct_type_declaration;
  struct StructuredTypeExpressionNode* structured_type_expression;
  struct TypeDeclarationNode* type_declaration;
  struct TypeExpressionNode* type_expression;
  struct TypeIdentifierNode* type_identifier;
  struct UnionTypeDeclarationNode* union_type_declaration;
};

union BindingStatementNodeUnion {
  struct LetBindingNode* let_binding;
  struct MutBindingNode* mut_binding;
};

union ExpressionNodeUnion {
  struct CallExpressionNode* call_expression;
  struct IdentifierExpressionNode* identifier_expression;
  struct ListExpressionNode* list_expression;
  struct NumericExpressionNode* numeric_expression;
  struct StringExpressionNode* string_expression;
  struct TypeExpressionNode* type_expression;
};

union ModuleStatementNodeUnion {
  struct FunctionDeclarationNode* function_declaration;
  struct ImportStatementNode* import_statement;
  struct LetBindingNode* let_binding;
  struct TypeDeclarationNode* type_declaration;
};

union MutExpressionNodeUnion {
  struct NewAllocNode* new_alloc;
  struct ExpressionNode* expression;
};

union NumericExpressionNodeUnion {
  struct DoubleExpressionNode* double_expression;
  struct IntegerExpressionNode* integer_expression;
};

union StatementNodeUnion {
  struct BindingStatementNode* binding_statement;
  struct DoStatementNode* do_statement;
  struct ExpressionNode* expression;
  struct MatchStatementNode* match_statement;
  struct ReturnStatementNode* return_statement;
};

union TypeDeclarationNodeUnion {
  struct EnumTypeDeclarationNode* enum_type_declaration;
  struct StructTypeDeclarationNode* struct_type_declaration;
  struct UnionTypeDeclarationNode* union_type_declaration;
};

union TypeExpressionNodeUnion {
  struct EnumTypeExpressionNode* enum_type_expression;
  struct StructuredTypeExpressionNode* structured_type_expression;
};


/********************/
/* Type Definitions */
/********************/

struct AstNode {
  AstNodeKind kind;
  union AstNodeUnion value;
};

struct BindingStatementNode {
  AstNodeKind kind;
  union BindingStatementNodeUnion value;
};

struct CallExpressionNode {
  AstNodeKind kind;
  struct IdentifierNode* function;
  struct ExpressionListNode* arguments;
};

struct DoStatementNode {
  AstNodeKind kind;
  struct StatementListNode* statements;
};

struct DoubleExpressionNode {
  AstNodeKind kind;
  double value;
};

struct EnumFieldListNode {
  AstNodeKind kind;
  struct EnumFieldNode** fields;
  size_t length;
};

struct EnumFieldNode {
  AstNodeKind kind;
  struct IdentifierNode* identifier;
  struct IntegerExpressionNode* integer_expression;
};

struct EnumTypeDeclarationNode {
  AstNodeKind kind;
  struct IdentifierNode* identifier;
  struct EnumFieldListNode* fields;
};

struct EnumTypeExpressionNode {
  AstNodeKind kind;
  struct TypeIdentifierNode* type;
  struct IdentifierNode* value;
};

struct ExpressionListNode {
  AstNodeKind kind;
  struct ExpressionNode** expressions;
  size_t length;
};

struct ExpressionNode {
  AstNodeKind kind;
  union ExpressionNodeUnion value;
};

struct FieldBindingListNode {
  AstNodeKind kind;
  struct FieldBindingNode** field_bindings;
  size_t length;
};

struct FieldBindingNode {
  AstNodeKind kind;
  struct IdentifierNode* identifier;
  struct ExpressionNode* expression;
};

struct FieldListNode {
  AstNodeKind kind;
  struct FieldNode** fields;
  size_t length;
};

struct FieldNode {
  AstNodeKind kind;
  struct IdentifierNode* identifier;
  struct TypeIdentifierNode* type_identifier;
};

struct FunctionDeclarationNode {
  AstNodeKind kind;
  struct IdentifierNode* identifier;
  struct TypeIdentifierNode* return_type;
  struct ParameterListNode* parameters;
  struct DoStatementNode* body;
};

struct IdentifierNode {
  AstNodeKind kind;
  char* name;
};

struct IdentifierExpressionNode {
  AstNodeKind kind;
  struct IdentifierNode* identifier;
  struct IdentifierExpressionNode* next;
};

struct ImportStatementNode {
  AstNodeKind kind;
  ImportNodeKind import_kind;
  struct StringExpressionNode* module_name;
};

struct IntegerExpressionNode {
  AstNodeKind kind;
  int64_t value;
};

struct LetBindingNode {
  AstNodeKind kind;
  struct IdentifierNode* binding;
  struct TypeIdentifierNode* type;
  struct ExpressionNode* expression;
};

struct ListExpressionNode {
  AstNodeKind kind;
  struct ExpressionListNode* expressions;
};

struct MatchCaseNode {
  AstNodeKind kind;
  struct CallExpressionNode* condition;
  struct StatementNode* statement;
};

struct MatchCaseListNode {
  AstNodeKind kind;
  struct MatchCaseNode** cases;
  size_t length;
};

struct MatchStatementNode {
  AstNodeKind kind;
  struct MatchCaseListNode* case_list;
};

struct ModuleStatementListNode {
  AstNodeKind kind;
  struct ModuleStatementNode** module_statements;
  size_t length;
};

struct ModuleStatementNode {
  AstNodeKind kind;
  union ModuleStatementNodeUnion value;
};

struct MutBindingNode {
  AstNodeKind kind;
  struct IdentifierNode* binding;
  struct TypeIdentifierNode* type;
  struct MutExpressionNode* mut_expression;
};

struct MutExpressionNode {
  AstNodeKind kind;
  union MutExpressionNodeUnion value;
};

struct NewAllocNode {
  AstNodeKind kind;
  struct StructuredTypeExpressionNode* structured_type_expression;
};

struct NumericExpressionNode {
  AstNodeKind kind;
  union NumericExpressionNodeUnion value;
};

struct ParameterListNode {
  AstNodeKind kind;
  struct ParameterNode** parameters;
  size_t length;
};

struct ParameterNode {
  AstNodeKind kind;
  struct IdentifierNode* identifier;
  struct TypeIdentifierNode* type_identifier;
};

typedef struct ProgramNode {
  AstNodeKind kind;
  struct ShebangNode* shebang;
  struct ModuleStatementListNode* module_statements;
} ProgramNode;

struct ReturnStatementNode {
  AstNodeKind kind;
  struct ExpressionNode* expression;
};

typedef struct ShebangNode {
  AstNodeKind kind;
} ShebangNode;

struct StatementNode {
  AstNodeKind kind;
  union StatementNodeUnion value;
};

struct StatementListNode {
  AstNodeKind kind;
  struct StatementNode** statements;
  size_t length;
};

struct StringExpressionNode {
  AstNodeKind kind;
  char* value;
};

struct StructTypeDeclarationNode {
  AstNodeKind kind;
  struct IdentifierNode* identifier;
  struct FieldListNode* fields;
};

struct StructuredTypeExpressionNode {
  AstNodeKind kind;
  struct TypeIdentifierNode* type;
  struct FieldBindingListNode* field_bindings;
};

struct TypeDeclarationNode {
  AstNodeKind kind;
  union TypeDeclarationNodeUnion value;
};

struct TypeExpressionNode {
  AstNodeKind kind;
  union TypeExpressionNodeUnion value;
};

struct TypeIdentifierNode {
  AstNodeKind kind;
  struct IdentifierNode* identifier;
  struct TypeIdentifierNode* contained_type;
};

struct UnionTypeDeclarationNode {
  AstNodeKind kind;
  struct IdentifierNode* identifier;
  struct FieldListNode* fields;
};


/*************************/
/* Function Declarations */
/*************************/

struct AstNode* ast_new_node(AstNodeKind, union AstNodeUnion);
void ast_free_node(struct AstNode*);

struct BindingStatementNode* ast_new_binding_statement_node(AstNodeKind, union BindingStatementNodeUnion);
void ast_free_binding_statement_node(struct BindingStatementNode*);
struct BindingStatementNode* ast_parse_binding_statement(struct Token**);
bool ast_binding_statement_token_matches_first_set(struct Token);

struct CallExpressionNode* ast_new_call_expression_node(struct IdentifierNode*, struct ExpressionListNode*);
void ast_free_call_expression_node(struct CallExpressionNode*);
struct CallExpressionNode* ast_parse_call_expression(struct Token**);
bool ast_call_expression_token_matches_first_set(struct Token);

struct DoStatementNode* ast_new_do_statement_node(struct StatementListNode*);
void ast_free_do_statement_node(struct DoStatementNode*);
struct DoStatementNode* ast_parse_do_statement(struct Token**);
bool ast_do_statement_token_matches_first_set(struct Token);

struct DoubleExpressionNode* ast_new_double_expression_node(double);
void ast_free_double_expression_node(struct DoubleExpressionNode*);
struct DoubleExpressionNode* ast_parse_double_expression(struct Token**);
bool ast_double_expression_token_matches_first_set(struct Token);

struct EnumTypeDeclarationNode* ast_new_enum_type_declaration_node(struct IdentifierNode*, struct EnumFieldListNode*);
void ast_free_enum_type_declaration_node(struct EnumTypeDeclarationNode*);
struct EnumTypeDeclarationNode* ast_parse_enum_type_declaration(struct IdentifierNode*, struct Token**);
bool ast_enum_type_declaration_token_matches_first_set(struct Token);

struct EnumFieldListNode* ast_new_enum_field_list_node(struct EnumFieldNode**);
void ast_add_enum_field_node(struct EnumFieldListNode*, struct EnumFieldNode*);
void ast_free_enum_field_list_node(struct EnumFieldListNode*);
struct EnumFieldListNode* ast_parse_enum_field_list(struct Token** tokens);
bool ast_enum_field_list_token_matches_first_set(struct Token);

struct EnumFieldNode* ast_new_enum_field_node(struct IdentifierNode*, struct IntegerExpressionNode*);
void ast_free_enum_field_node(struct EnumFieldNode*);
struct EnumFieldNode* ast_parse_enum_field(struct Token**);
bool ast_enum_field_token_matches_first_set(struct Token);

struct EnumTypeExpressionNode* ast_new_enum_type_expression_node(struct TypeIdentifierNode*, struct IdentifierNode*);
void ast_free_enum_type_expression_node(struct EnumTypeExpressionNode*);
struct EnumTypeExpressionNode* ast_parse_enum_type_expression(struct Token**);
bool ast_enum_type_expression_token_matches_first_set(struct Token);

struct ExpressionListNode* ast_new_expression_list_node(struct ExpressionNode**);
void ast_free_expression_list_node(struct ExpressionListNode*);
void ast_add_expression_node(struct ExpressionListNode*, struct ExpressionNode*);
struct ExpressionListNode* ast_parse_expression_list(struct Token**);
bool ast_expression_list_token_matches_first_set(struct Token);

struct ExpressionNode* ast_new_expression_node(AstNodeKind, union ExpressionNodeUnion);
void ast_free_expression_node(struct ExpressionNode*);
struct ExpressionNode* ast_parse_expression(struct Token**);
bool ast_expression_token_matches_first_set(struct Token);

struct FieldBindingListNode* ast_new_field_binding_list_node(struct FieldBindingNode**);
void ast_add_field_binding_node(struct FieldBindingListNode*, struct FieldBindingNode*);
void ast_free_field_binding_list_node(struct FieldBindingListNode*);
struct FieldBindingListNode* ast_parse_field_binding_list(struct Token** tokens);
bool ast_field_binding_list_token_matches_first_set(struct Token);

struct FieldBindingNode* ast_new_field_binding_node(struct IdentifierNode*, struct ExpressionNode*);
void ast_free_field_binding_node(struct FieldBindingNode*);
struct FieldBindingNode* ast_parse_field_binding(struct Token**);
bool ast_field_binding_token_matches_first_set(struct Token);

struct FieldListNode* ast_new_field_list_node(struct FieldNode**);
void ast_free_field_list_node(struct FieldListNode*);
void ast_add_field_node(struct FieldListNode*, struct FieldNode*);
struct FieldListNode* ast_parse_field_list(struct Token**);
bool ast_field_list_token_matches_first_set(struct Token);

struct FieldNode* ast_new_field_node(struct IdentifierNode*, struct TypeIdentifierNode*);
void ast_free_field_node(struct FieldNode*);
struct FieldNode* ast_parse_field(struct Token** tokens);
bool ast_field_token_matches_first_set(struct Token);

struct FunctionDeclarationNode* ast_new_function_declaration_node(struct IdentifierNode*, struct TypeIdentifierNode*, struct ParameterListNode*, struct DoStatementNode*);
void ast_free_function_declaration_node(struct FunctionDeclarationNode*);
struct FunctionDeclarationNode* ast_parse_function_declaration(struct Token**);
bool ast_function_declaration_token_matches_first_set(struct Token);

struct IdentifierNode* ast_new_identifier_node(char*);
void ast_free_identifier_node(struct IdentifierNode*);
struct IdentifierNode* ast_parse_identifier(struct Token**);
bool ast_identifier_token_matches_first_set(struct Token);

struct IdentifierExpressionNode* ast_new_identifier_expression_node(struct IdentifierNode*, struct IdentifierExpressionNode*);
void ast_free_identifier_expression_node(struct IdentifierExpressionNode*);
struct IdentifierExpressionNode* ast_parse_identifier_expression(struct Token**);
bool ast_identifier_expression_token_matches_first_set(struct Token);

struct ImportStatementNode* ast_new_import_statement_node(ImportNodeKind, struct StringExpressionNode*);
void ast_free_import_statement_node(struct ImportStatementNode*);
struct ImportStatementNode* ast_parse_import_statement(struct Token**);
bool ast_import_statement_token_matches_first_set(struct Token);

struct IntegerExpressionNode* ast_new_integer_expression_node(int64_t);
void ast_free_integer_expression_node(struct IntegerExpressionNode*);
struct IntegerExpressionNode* ast_parse_integer_expression(struct Token**);
bool ast_integer_expression_token_matches_first_set(struct Token);

struct LetBindingNode* ast_new_let_binding_node(struct IdentifierNode*, struct TypeIdentifierNode*, struct ExpressionNode*);
void ast_free_let_binding_node(struct LetBindingNode*);
struct LetBindingNode* ast_parse_let_binding(struct Token**);
bool ast_let_binding_token_matches_first_set(struct Token);

struct ListExpressionNode* ast_new_list_expression_node(struct ExpressionListNode*);
void ast_free_list_expression_node(struct ListExpressionNode*);
struct ListExpressionNode* ast_parse_list_expression(struct Token**);
bool ast_list_expression_token_matches_first_set(struct Token);

struct MatchCaseNode* ast_new_match_case_node(struct CallExpressionNode*, struct StatementNode*);
void ast_free_match_case_node(struct MatchCaseNode*);
struct MatchCaseNode* ast_parse_match_case(struct Token**);
bool ast_match_case_token_matches_first_set(struct Token);

struct MatchCaseListNode* ast_new_match_case_list_node(struct MatchCaseNode**);
void ast_free_match_case_list_node(struct MatchCaseListNode*);
struct MatchCaseListNode* ast_parse_match_case_list(struct Token**);
void ast_add_match_case_node(struct MatchCaseListNode*, struct MatchCaseNode*);
bool ast_match_case_list_token_matches_first_set(struct Token);

struct MatchStatementNode* ast_new_match_statement_node(struct MatchCaseListNode*);
void ast_free_match_statement_node(struct MatchStatementNode*);
struct MatchStatementNode* ast_parse_match_statement(struct Token**);
bool ast_match_statement_token_matches_first_set(struct Token);

struct ModuleStatementListNode* ast_new_module_statement_list_node(struct ModuleStatementNode**);
void ast_free_module_statement_list_node(struct ModuleStatementListNode*);
void ast_add_module_statement_node(struct ModuleStatementListNode*, struct ModuleStatementNode*);
struct ModuleStatementListNode* ast_parse_module_statement_list(struct Token**);
bool ast_module_statement_list_token_matches_first_set(struct Token);

struct ModuleStatementNode* ast_new_module_statement_node(AstNodeKind, union ModuleStatementNodeUnion);
void ast_free_module_statement_node(struct ModuleStatementNode*);
struct ModuleStatementNode* ast_parse_module_statement(struct Token** tokens);
bool ast_module_statement_token_matches_first_set(struct Token);

struct MutBindingNode* ast_new_mut_binding_node(struct IdentifierNode*, struct TypeIdentifierNode*, struct MutExpressionNode*);
void ast_free_mut_binding_node(struct MutBindingNode*);
struct MutBindingNode* ast_parse_mut_binding(struct Token**);
bool ast_mut_binding_token_matches_first_set(struct Token);

struct MutExpressionNode* ast_new_mut_expression_node(AstNodeKind, union MutExpressionNodeUnion);
void ast_free_mut_expression_node(struct MutExpressionNode*);
struct MutExpressionNode* ast_parse_mut_expression(struct Token**);
bool ast_mut_expression_token_matches_first_set(struct Token);

struct NewAllocNode* ast_new_new_alloc_node(struct StructuredTypeExpressionNode*);
void ast_free_new_alloc_node(struct NewAllocNode*);
struct NewAllocNode* ast_parse_new_alloc(struct Token**);
bool ast_new_alloc_token_matches_first_set(struct Token);

struct NumericExpressionNode* ast_new_numeric_expression_node(AstNodeKind, union NumericExpressionNodeUnion);
void ast_free_numeric_expression_node(struct NumericExpressionNode*);
struct NumericExpressionNode* ast_parse_numeric_expression(struct Token**);
bool ast_numeric_expression_token_matches_first_set(struct Token);

struct ParameterListNode* ast_new_parameter_list_node(struct ParameterNode**);
void ast_free_parameter_list_node(struct ParameterListNode*);
void ast_add_parameter_node(struct ParameterListNode*, struct ParameterNode*);
struct ParameterListNode* ast_parse_parameter_list(struct Token**);
bool ast_parameter_list_token_matches_first_set(struct Token);

struct ParameterNode* ast_new_parameter_node(struct IdentifierNode*, struct TypeIdentifierNode*);
void ast_free_parameter_node(struct ParameterNode*);
struct ParameterNode* ast_parse_parameter(struct Token** tokens);
bool ast_parameter_token_matches_first_set(struct Token);

struct ProgramNode* ast_new_program_node(struct ShebangNode*, struct ModuleStatementListNode*);
void ast_free_program_node(struct ProgramNode*);
struct ProgramNode* ast_parse_program(struct Token**);
bool ast_program_token_matches_first_set(struct Token);

struct ReturnStatementNode* ast_new_return_statement_node(struct ExpressionNode*);
void ast_free_return_statement_node(struct ReturnStatementNode*);
struct ReturnStatementNode* ast_parse_return_statement(struct Token**);
bool ast_return_statement_token_matches_first_set(struct Token);

struct ShebangNode* ast_new_shebang_node();
void ast_free_shebang_node(struct ShebangNode*);
struct ShebangNode* ast_parse_shebang(struct Token**);
bool ast_shebang_token_matches_first_set(struct Token);

struct StatementNode* ast_new_statement_node(AstNodeKind, union StatementNodeUnion);
void ast_free_statement_node(struct StatementNode*);
struct StatementNode* ast_parse_statement(struct Token**);
bool ast_statement_token_matches_first_set(struct Token);

struct StatementListNode* ast_new_statement_list_node(struct StatementNode**);
void ast_free_statement_list_node(struct StatementListNode*);
void ast_add_statement_node(struct StatementListNode*, struct StatementNode*);
struct StatementListNode* ast_parse_statement_list(struct Token**);
bool ast_statement_list_token_matches_first_set(struct Token);

struct StringExpressionNode* ast_new_string_expression_node(char*);
void ast_free_string_expression_node(struct StringExpressionNode*);
struct StringExpressionNode* ast_parse_string_expression(struct Token**);
bool ast_string_expression_token_matches_first_set(struct Token);

struct StructTypeDeclarationNode* ast_new_struct_type_declaration_node(struct IdentifierNode*, struct FieldListNode*);
void ast_free_struct_type_declaration_node(struct StructTypeDeclarationNode*);
struct StructTypeDeclarationNode* ast_parse_struct_type_declaration(struct IdentifierNode*, struct Token**);
bool ast_struct_type_declaration_token_matches_first_set(struct Token);

struct StructuredTypeExpressionNode* ast_new_structured_type_expression_node(struct TypeIdentifierNode*, struct FieldBindingListNode*);
void ast_free_structured_type_expression_node(struct StructuredTypeExpressionNode*);
struct StructuredTypeExpressionNode* ast_parse_structured_type_expression(struct Token**);
bool ast_structured_type_expression_token_matches_first_set(struct Token);

struct TypeDeclarationNode* ast_new_type_declaration_node(AstNodeKind, union TypeDeclarationNodeUnion);
void ast_free_type_declaration_node(struct TypeDeclarationNode*);
struct TypeDeclarationNode* ast_parse_type_declaration(struct Token**);
bool ast_type_declaration_token_matches_first_set(struct Token);

struct TypeExpressionNode* ast_new_type_expression_node(AstNodeKind kind, union TypeExpressionNodeUnion);
void ast_free_type_expression_node(struct TypeExpressionNode*);
struct TypeExpressionNode* ast_parse_type_expression(struct Token**);
bool ast_type_expression_token_matches_first_set(struct Token);

struct TypeIdentifierNode* ast_new_type_identifier_node(struct IdentifierNode*, struct TypeIdentifierNode*);
void ast_free_type_identifier_node(struct TypeIdentifierNode*);
struct TypeIdentifierNode* ast_parse_type_identifier(struct Token**);
bool ast_type_identifier_token_matches_first_set(struct Token);

struct UnionTypeDeclarationNode* ast_new_union_type_declaration_node(struct IdentifierNode*, struct FieldListNode*);
void ast_free_union_type_declaration_node(struct UnionTypeDeclarationNode*);
struct UnionTypeDeclarationNode* ast_parse_union_type_declaration(struct IdentifierNode*, struct Token**);
bool ast_union_type_declaration_token_matches_first_set(struct Token);

/***********/
/* AstNode */
/***********/
struct AstNode* ast_new_node(
  AstNodeKind kind,
  union AstNodeUnion value
) {
  struct AstNode* node = malloc(sizeof(struct AstNode));
  node->kind = kind;
  node->value = value;
  return node;
}

void ast_free_node(struct AstNode* node) {
  switch (node->kind) {
    case AstBindingStatement: {
      ast_free_binding_statement_node(node->value.binding_statement);
    } break;
    case AstCallExpression: {
      ast_free_call_expression_node(node->value.call_expression);
    } break;
    case AstDoStatement: {
      ast_free_do_statement_node(node->value.do_statement);
    } break;
    case AstDoubleExpression: {
      ast_free_double_expression_node(node->value.double_expression);
    } break;
    case AstEnumField: {
      ast_free_enum_field_node(node->value.enum_field);
    } break;
    case AstEnumFieldList: {
      ast_free_enum_field_list_node(node->value.enum_field_list);
    } break;
    case AstEnumTypeDeclaration: {
      ast_free_enum_type_declaration_node(node->value.enum_type_declaration);
    } break;
    case AstEnumTypeExpression: {
      ast_free_enum_type_expression_node(node->value.enum_type_expression);
    } break;
    case AstExpression: {
      ast_free_expression_node(node->value.expression);
    } break;
    case AstExpressionList: {
      ast_free_expression_list_node(node->value.expression_list);
    } break;
    case AstField: {
      ast_free_field_node(node->value.field);
    } break;
    case AstFieldBinding: {
      ast_free_field_binding_node(node->value.field_binding);
    } break;
    case AstFieldBindingList: {
      ast_free_field_binding_list_node(node->value.field_binding_list);
    } break;
    case AstFieldList: {
      ast_free_field_list_node(node->value.field_list);
    } break;
    case AstFunctionDeclaration: {
      ast_free_function_declaration_node(node->value.function_declaration);
    } break;
    case AstIdentifier: {
      ast_free_identifier_node(node->value.identifier);
    } break;
    case AstIdentifierExpression: {
      ast_free_identifier_expression_node(node->value.identifier_expression);
    } break;
    case AstImportStatement: {
      ast_free_import_statement_node(node->value.import_statement);
    } break;
    case AstIntegerExpression: {
      ast_free_integer_expression_node(node->value.integer_expression);
    } break;
    case AstLetBinding: {
      ast_free_let_binding_node(node->value.let_binding);
    } break;
    case AstListExpression: {
      ast_free_list_expression_node(node->value.list_expression);
    } break;
    case AstMatchCase: {
      ast_free_match_case_node(node->value.match_case);
    } break;
    case AstMatchCaseList: {
      ast_free_match_case_list_node(node->value.match_case_list);
    } break;
    case AstMatchStatement: {
      ast_free_match_statement_node(node->value.match_expression);
    } break;
    case AstModuleStatement: {
      ast_free_module_statement_node(node->value.module_statement);
    } break;
    case AstModuleStatementList: {
      ast_free_module_statement_list_node(node->value.module_statement_list);
    } break;
    case AstMutBinding: {
      ast_free_mut_binding_node(node->value.mut_binding);
    } break;
    case AstMutExpression: {
      ast_free_mut_expression_node(node->value.mut_expression);
    } break;
    case AstNewAlloc: {
      ast_free_new_alloc_node(node->value.new_alloc);
    } break;
    case AstNumericExpression: {
      ast_free_numeric_expression_node(node->value.numeric_expression);
    } break;
    case AstParameter: {
      ast_free_parameter_node(node->value.parameter);
    } break;
    case AstParameterList: {
      ast_free_parameter_list_node(node->value.parameter_list);
    } break;
    case AstProgram: {
      ast_free_program_node(node->value.program);
    } break;
    case AstReturnStatement: {
      ast_free_return_statement_node(node->value.return_statement);
    } break;
    case AstShebang: {
      ast_free_shebang_node(node->value.shebang);
    } break;
    case AstStatement: {
      ast_free_statement_node(node->value.statement);
    } break;
    case AstStatementList: {
      ast_free_statement_list_node(node->value.statement_list);
    } break;
    case AstStringExpression: {
      ast_free_string_expression_node(node->value.string_expression);
    } break;
    case AstStructTypeDeclaration: {
      ast_free_struct_type_declaration_node(node->value.struct_type_declaration);
    } break;
    case AstStructuredTypeExpression: {
      ast_free_structured_type_expression_node(node->value.structured_type_expression);
    } break;
    case AstTypeDeclaration: {
      ast_free_type_declaration_node(node->value.type_declaration);
    } break;
    case AstTypeExpression: {
      ast_free_type_expression_node(node->value.type_expression);
    } break;
    case AstTypeIdentifier: {
      ast_free_type_identifier_node(node->value.type_identifier);
    } break;
    case AstUnionTypeDeclaration: {
      ast_free_union_type_declaration_node(node->value.union_type_declaration);
    } break;
    default: {
      LOG_ERROR("Invalid AstNode kind");
      exit(1);
    }
  }

  free(node);
}

/*************************/
/* BindingStatementNode */
/*************************/
struct BindingStatementNode* ast_new_binding_statement_node(
  AstNodeKind kind,
  union BindingStatementNodeUnion value
) {
  struct BindingStatementNode* node = malloc(sizeof(struct BindingStatementNode));
  node->kind = kind;
  node->value = value;
  return node;
}

void ast_free_binding_statement_node(struct BindingStatementNode* node) {
  switch (node->kind) {
    case AstLetBinding: {
      ast_free_let_binding_node(node->value.let_binding);
    } break;
    case AstMutBinding: {
      ast_free_mut_binding_node(node->value.mut_binding);
    } break;
    default: {
      LOG_ERROR("Invalid AstNode kind");
      exit(1);
    }
  }

  free(node);
}

struct BindingStatementNode* ast_parse_binding_statement(struct Token** tokens) {
  _CHECK_TOKENS();
  LOG_DEBUG("Parsing Binding Expression: %s", (*tokens)->name);

  if (ast_let_binding_token_matches_first_set(**tokens)) {
    return ast_new_binding_statement_node(
      AstLetBinding,
      (union BindingStatementNodeUnion) {
        .let_binding = ast_parse_let_binding(tokens)
      }
    );
  } else if (ast_mut_binding_token_matches_first_set(**tokens)) {
    return ast_new_binding_statement_node(
      AstMutBinding,
      (union BindingStatementNodeUnion) {
        .mut_binding = ast_parse_mut_binding(tokens)
      }
    );
  } else {
    LOG_ERROR("Expected BindingStatement got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }
}

inline bool ast_binding_statement_token_matches_first_set(struct Token token) {
  return (
    ast_let_binding_token_matches_first_set(token) ||
    ast_mut_binding_token_matches_first_set(token)
  );
}

/**********************/
/* CallExpressionNode */
/**********************/
struct CallExpressionNode* ast_new_call_expression_node(
  struct IdentifierNode* function,
  struct ExpressionListNode* arguments
) {
  struct CallExpressionNode* node = malloc(sizeof(struct CallExpressionNode));
  node->kind = AstCallExpression;
  node->function = function;
  node->arguments = arguments;
  return node;
}

void ast_free_call_expression_node(struct CallExpressionNode* node) {
  ast_free_identifier_node(node->function);
  node->function = NULL;
  ast_free_expression_list_node(node->arguments);
  node->arguments = NULL;

  free(node);
}

struct CallExpressionNode* ast_parse_call_expression(struct Token** tokens) {
  _CHECK_TOKENS();
  LOG_DEBUG("Parsing Call Expression: %s", (*tokens)->name);

  if (!ast_call_expression_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected '(' got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }
  _ADVANCE_TOKEN(tokens);
  struct IdentifierNode* function = ast_parse_identifier(tokens);
  struct ExpressionListNode* arguments = ast_parse_expression_list(tokens);
  if (!token_is_close_paren(**tokens)) {
    LOG_ERROR("Expected ')' got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }
  _ADVANCE_TOKEN(tokens);
  return ast_new_call_expression_node(function, arguments);
}

inline bool ast_call_expression_token_matches_first_set(struct Token token) {
  return token_is_open_paren(token);
}

/*******************/
/* DoStatementNode */
/*******************/
struct DoStatementNode* ast_new_do_statement_node(struct StatementListNode* statements) {
  struct DoStatementNode* node = malloc(sizeof(struct DoStatementNode));
  node->kind = AstFunctionDeclaration;
  node->statements = statements;
  return node;
}

void ast_free_do_statement_node(struct DoStatementNode* node) {
  ast_free_statement_list_node(node->statements);
  node->statements = NULL;

  free(node);
}

struct DoStatementNode* ast_parse_do_statement(struct Token** tokens) {
  _CHECK_TOKENS();
  LOG_DEBUG("Parsing Do Statement: %s", (*tokens)->name);

  if (!ast_do_statement_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected '%s' got '%s' - %s:%d:%d", HELPERS_STRINGIFY(TOKEN_DO), (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }

  _ADVANCE_TOKEN(tokens);
  
  struct StatementListNode* statements = ast_parse_statement_list(tokens);
  if (!token_is_end(**tokens)) {
    LOG_ERROR("Expected '%s' got '%s' - %s:%d:%d", HELPERS_STRINGIFY(TOKEN_END), (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }
  _ADVANCE_TOKEN(tokens);
  return ast_new_do_statement_node(statements);
}

inline bool ast_do_statement_token_matches_first_set(struct Token token) {
  return token_is_do(token);
}

/************************/
/* DoubleExpressionNode */
/************************/
struct DoubleExpressionNode* ast_new_double_expression_node(double value) {
  struct DoubleExpressionNode* node = malloc(sizeof(struct DoubleExpressionNode));
  node->kind = AstDoubleExpression;
  node->value = value;
  return node;
}

void ast_free_double_expression_node(struct DoubleExpressionNode* node) {
  free(node);
}

struct DoubleExpressionNode* ast_parse_double_expression(struct Token** tokens) {
  _CHECK_TOKENS();
  LOG_DEBUG("Parsing Double Expression: %s", (*tokens)->name);

  if (!ast_double_expression_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected double got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }

  const double value = atof((*tokens)->name);
  _ADVANCE_TOKEN(tokens);
  return ast_new_double_expression_node(value);
}

inline bool ast_double_expression_token_matches_first_set(struct Token token) {
  return token_is_double(token);
}

/*********************/
/* EnumFieldListNode */
/*********************/
struct EnumFieldListNode* ast_new_enum_field_list_node(struct EnumFieldNode** fields) {
  struct EnumFieldListNode* node = malloc(sizeof(struct EnumFieldListNode));
  node->kind = AstEnumFieldList;
  node->fields = fields;
  node->length = 0;
  while (fields && *fields) {
    node->length++;
    fields++;
  }
  return node;
}

void ast_free_enum_field_list_node(struct EnumFieldListNode* node) {
  for (size_t i = 0; i < node->length; i++) {
    ast_free_enum_field_node(node->fields[i]);
  }
  free(node->fields);
  node->fields = NULL;

  free(node);
}

void ast_add_enum_field_node(struct EnumFieldListNode* node, struct EnumFieldNode* field) {
  if (!field) {
    return;
  }
  if (!node->fields) {
    node->fields = malloc(sizeof(struct EnumFieldNode*));
  } else {
    node->fields = realloc(node->fields, sizeof(struct EnumFieldNode*) * (node->length + 1));
  }
  node->fields[node->length++] = field;
}

struct EnumFieldListNode* ast_parse_enum_field_list(struct Token** tokens) {
  _CHECK_TOKENS();
  LOG_DEBUG("Parsing Enum Field List: %s", (*tokens)->name);

  struct EnumFieldListNode* field_list = ast_new_enum_field_list_node(NULL);
  if (!ast_enum_field_list_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected identifier got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }

  while (!token_is_end(**tokens)) {
    ast_add_enum_field_node(field_list, ast_parse_enum_field(tokens));
  }
  return field_list;
}

inline bool ast_enum_field_list_token_matches_first_set(struct Token token) {
  return ast_identifier_token_matches_first_set(token);
}

/*****************/
/* EnumFieldNode */
/*****************/
struct EnumFieldNode* ast_new_enum_field_node(
  struct IdentifierNode* identifier,
  struct IntegerExpressionNode* integer_expression
) {
  struct EnumFieldNode* node = malloc(sizeof(struct EnumFieldNode));
  node->kind = AstEnumField;
  node->identifier = identifier;
  node->integer_expression = integer_expression;
  return node;
}

void ast_free_enum_field_node(struct EnumFieldNode* node) {
  ast_free_identifier_node(node->identifier);
  node->identifier = NULL;
  if (node->integer_expression) {
    ast_free_integer_expression_node(node->integer_expression);
    node->integer_expression = NULL;
  }

  free(node);
}

struct EnumFieldNode* ast_parse_enum_field(struct Token** tokens) {
  _CHECK_TOKENS();
  LOG_DEBUG("Parsing Enum Field: %s", (*tokens)->name);

  if (!ast_enum_field_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected Identifier got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }

  struct IdentifierNode* identifier = ast_parse_identifier(tokens);
  struct IntegerExpressionNode* integer_expression = NULL;
  if (token_is_binding_arrow(**tokens)) {
    _ADVANCE_TOKEN(tokens);
    integer_expression = ast_parse_integer_expression(tokens);
  }
  return ast_new_enum_field_node(identifier, integer_expression);
}

inline bool ast_enum_field_token_matches_first_set(struct Token token) {
  return ast_identifier_token_matches_first_set(token);
}

/***************************/
/* EnumTypeDeclarationNode */
/***************************/
struct EnumTypeDeclarationNode* ast_new_enum_type_declaration_node(struct IdentifierNode* identifier, struct EnumFieldListNode* fields) {
  struct EnumTypeDeclarationNode* node = malloc(sizeof(struct EnumTypeDeclarationNode));
  node->kind = AstEnumTypeDeclaration;
  node->identifier = identifier;
  node->fields = fields;
  return node;
}

void ast_free_enum_type_declaration_node(struct EnumTypeDeclarationNode* enum_type_declaration) {
  ast_free_identifier_node(enum_type_declaration->identifier);
  enum_type_declaration->identifier = NULL;
  ast_free_enum_field_list_node(enum_type_declaration->fields);
  enum_type_declaration->fields = NULL;

  free(enum_type_declaration);
}

struct EnumTypeDeclarationNode* ast_parse_enum_type_declaration(
  struct IdentifierNode* identifier,
  struct Token** tokens
) {
  _CHECK_TOKENS();
  LOG_DEBUG("Parsing Enum Type Declaration: %s", (*tokens)->name);

  if (!ast_enum_type_declaration_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected enum type declaration got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }
  _ADVANCE_TOKEN(tokens);
  if (!token_is_is(**tokens)) {
    LOG_ERROR("Expected 'is' got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }
  _ADVANCE_TOKEN(tokens);
  struct EnumFieldListNode* fields = ast_parse_enum_field_list(tokens);
  if (!token_is_end(**tokens)) {
    LOG_ERROR("Expected 'end' got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }
  _ADVANCE_TOKEN(tokens);
  return ast_new_union_type_declaration_node(identifier, fields);
}

inline bool ast_enum_type_declaration_token_matches_first_set(struct Token token) {
  return token_is_enum(token);
}

/********************************/
/* StructuredTypeExpressionNode */
/********************************/
struct EnumTypeExpressionNode* ast_new_enum_type_expression_node(
  struct TypeIdentifierNode* type,
  struct IdentifierNode* value
) {
  struct EnumTypeExpressionNode* node = malloc(sizeof(struct EnumTypeExpressionNode));
  node->kind = AstEnumTypeExpression;
  node->type = type;
  node->value = value;
  return node;
}

void ast_free_enum_type_expression_node(struct EnumTypeExpressionNode* node) {
  ast_free_type_identifier_node(node->type);
  node->type = NULL;
  ast_free_identifier_node(node->value);
  node->value = NULL;

  free(node);
}

struct EnumTypeExpressionNode* ast_parse_enum_type_expression(struct Token** tokens) {
  _CHECK_TOKENS();
  LOG_DEBUG("Parsing Enum Type Expression: %s", (*tokens)->name);

  if (!ast_enum_type_expression_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected '#' got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }
  _ADVANCE_TOKEN(tokens);
  struct TypeIdentifierNode* type = ast_parse_type_identifier(tokens);
  if (!token_is_period(**tokens)) {
    LOG_ERROR("Expected '.' got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }
  _ADVANCE_TOKEN(tokens);
  struct IdentifierNode* value = ast_parse_identifier(tokens);
  return ast_new_enum_type_expression_node(type, value);
}

inline bool ast_enum_type_expression_token_matches_first_set(struct Token token) {
  return token_is_hash(token);
}

/**********************/
/* ExpressionListNode */
/**********************/
struct ExpressionListNode* ast_new_expression_list_node(
  struct ExpressionNode** expressions
) {
  struct ExpressionListNode* node = malloc(sizeof(struct ExpressionListNode));
  node->kind = AstExpressionList;
  node->expressions = expressions;
  node->length = 0;
  while (expressions && *expressions) {
    node->length++;
    expressions++;
  }
  return node;
}

void ast_free_expression_list_node(struct ExpressionListNode* node) {
  for (size_t i = 0; i < node->length; i++) {
    ast_free_expression_node(node->expressions[i]);
  }
  free(node->expressions);
  node->expressions = NULL;

  free(node);
}

void ast_add_expression_node(struct ExpressionListNode* node, struct ExpressionNode* expression) {
  if (!expression) {
    return;
  }
  if (!node->expressions) {
    node->expressions = malloc(sizeof(struct ExpressionNode*));
  } else {
    node->expressions = realloc(node->expressions, sizeof(struct ExpressionNode*) * (node->length + 1));
  }
  node->expressions[node->length++] = expression;
}

struct ExpressionListNode* ast_parse_expression_list(struct Token** tokens) {
  _CHECK_TOKENS();
  LOG_DEBUG("Parsing Expression List: %s", (*tokens)->name);

  struct ExpressionListNode* expression_list = ast_new_expression_list_node(NULL);
  while (ast_expression_list_token_matches_first_set(**tokens)) {
    ast_add_expression_node(expression_list, ast_parse_expression(tokens));
  }
  return expression_list;
}

inline bool ast_expression_list_token_matches_first_set(struct Token token) {
  return ast_expression_token_matches_first_set(token);
}

/******************/
/* ExpressionNode */
/******************/
struct ExpressionNode* ast_new_expression_node(
  AstNodeKind kind,
  union ExpressionNodeUnion value
) {
  struct ExpressionNode* node = malloc(sizeof(struct ExpressionNode));
  node->kind = kind;
  node->value = value;
  return node;
}

void ast_free_expression_node(struct ExpressionNode* node) {
  switch (node->kind) {
    case AstCallExpression: {
      ast_free_call_expression_node(node->value.call_expression);
    } break;
    case AstIdentifierExpression: {
      ast_free_identifier_expression_node(node->value.identifier_expression);
    } break;
    case AstListExpression: {
      ast_free_list_expression_node(node->value.list_expression);
    } break;
    case AstNumericExpression: {
      ast_free_numeric_expression_node(node->value.numeric_expression);
    } break;
    case AstStringExpression: {
      ast_free_string_expression_node(node->value.string_expression);
    } break;
    case AstTypeExpression: {
      ast_free_type_expression_node(node->value.type_expression);
    } break;
    default: {
      LOG_ERROR("Invalid ExpressionNode kind");
      exit(1);
    }
  }

  free(node);
}

struct ExpressionNode* ast_parse_expression(struct Token** tokens) {
  _CHECK_TOKENS();
  LOG_DEBUG("Parsing Expression: %s", (*tokens)->name);

  if (!ast_expression_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected an expression got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }
  if (ast_string_expression_token_matches_first_set(**tokens)){
    struct StringExpressionNode* expression = ast_parse_string_expression(tokens);
    return ast_new_expression_node(
      AstStringExpression,
      (union ExpressionNodeUnion) {
        .string_expression = expression
      }
    );
  } else if (ast_numeric_expression_token_matches_first_set(**tokens)) {
    struct NumericExpressionNode* expression = ast_parse_numeric_expression(tokens);
    return ast_new_expression_node(
      AstNumericExpression,
      (union ExpressionNodeUnion) {
        .numeric_expression = expression
      }
    );
  } else if (ast_call_expression_token_matches_first_set(**tokens)) {
    struct CallExpressionNode* expression = ast_parse_call_expression(tokens);
    return ast_new_expression_node(
      AstCallExpression,
      (union ExpressionNodeUnion) {
        .call_expression = expression
      }
    );
  } else if (ast_list_expression_token_matches_first_set(**tokens)) {
    struct ListExpressionNode* expression = ast_parse_list_expression(tokens);
    return ast_new_expression_node(
      AstListExpression,
      (union ExpressionNodeUnion) {
        .list_expression = expression
      }
    );
  } else if (ast_type_expression_token_matches_first_set(**tokens)) {
    struct TypeExpressionNode* expression = ast_parse_type_expression(tokens);
    return ast_new_expression_node(
      AstTypeExpression,
      (union ExpressionNodeUnion) {
        .type_expression = expression
      }
    );
  } else if (ast_identifier_token_matches_first_set(**tokens)) {
    struct IdentifierExpressionNode* expression = ast_parse_identifier_expression(tokens);
    return ast_new_expression_node(
      AstIdentifierExpression,
      (union ExpressionNodeUnion) {
        .identifier_expression = expression
      }
    );
  } else {
    LOG_ERROR("Invalid ExpressionNode kind");
    exit(1);
  }
}

inline bool ast_expression_token_matches_first_set(struct Token token) {
  return (
    ast_call_expression_token_matches_first_set(token) ||
    ast_identifier_token_matches_first_set(token) ||
    ast_list_expression_token_matches_first_set(token) ||
    ast_numeric_expression_token_matches_first_set(token) ||
    ast_string_expression_token_matches_first_set(token) ||
    ast_type_expression_token_matches_first_set(token)
  );
}

/************************/
/* FieldBindingListNode */
/************************/
struct FieldBindingListNode* ast_new_field_binding_list_node(
  struct FieldBindingNode** field_bindings
) {
  struct FieldBindingListNode* node = malloc(sizeof(struct FieldBindingListNode));
  node->kind = AstFieldBindingList;
  node->field_bindings = field_bindings;
  node->length = 0;
  while (field_bindings && *field_bindings) {
    node->length++;
    field_bindings++;
  }
  return node;
}

void ast_free_field_binding_list_node(struct FieldBindingListNode* node) {
  for (size_t i = 0; i < node->length; i++) {
    ast_free_field_binding_node(node->field_bindings[i]);
  }
  free(node->field_bindings);
  node->field_bindings = NULL;

  free(node);
}

void ast_add_field_binding_node(struct FieldBindingListNode* node, struct FieldBindingNode* field_binding) {
  if (!field_binding) {
    return;
  }
  if (!node->field_bindings) {
    node->field_bindings = malloc(sizeof(struct FieldBindingNode*));
  } else {
    node->field_bindings = realloc(node->field_bindings, sizeof(struct FieldBindingNode*) * (node->length + 1));
  }
  node->field_bindings[node->length++] = field_binding;
}

struct FieldBindingListNode* ast_parse_field_binding_list(struct Token** tokens) {
  _CHECK_TOKENS();
  LOG_DEBUG("Parsing Field Binding List: %s", (*tokens)->name);

  struct FieldBindingListNode* field_binding_list = ast_new_field_binding_list_node(NULL);
  while (ast_field_binding_list_token_matches_first_set(**tokens)) {
    if (token_is_close_brace(**tokens)) {
      break;
    }
    ast_add_field_binding_node(field_binding_list, ast_parse_field_binding(tokens));
  }
  return field_binding_list;
}

inline bool ast_field_binding_list_token_matches_first_set(struct Token token) {
  return ast_field_binding_token_matches_first_set(token);
}

/********************/
/* FieldBindingNode */
/********************/
struct FieldBindingNode* ast_new_field_binding_node(
  struct IdentifierNode* identifier,
  struct ExpressionNode* expression
) {
  struct FieldBindingNode* node = malloc(sizeof(struct FieldBindingNode));
  node->kind = AstFieldBinding;
  node->identifier = identifier;
  node->expression = expression;
  return node;
}

void ast_free_field_binding_node(struct FieldBindingNode* node) {
  ast_free_identifier_node(node->identifier);
  node->identifier = NULL;
  ast_free_expression_node(node->expression);
  node->expression = NULL;

  free(node);
}

struct FieldBindingNode* ast_parse_field_binding(struct Token** tokens) {
  _CHECK_TOKENS();
  LOG_DEBUG("Parsing Field Binding: %s", (*tokens)->name);

  if (!ast_field_binding_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected an identifier got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }
  struct IdentifierNode* identifier = ast_parse_identifier(tokens);
  if (!token_is_binding_arrow(**tokens)) {
    LOG_ERROR("Expected a '<-' got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }
  _ADVANCE_TOKEN(tokens);
  struct ExpressionNode* expression = ast_parse_expression(tokens);
  return ast_new_field_binding_node(identifier, expression);
}

inline bool ast_field_binding_token_matches_first_set(struct Token token) {
  return ast_identifier_token_matches_first_set(token);
}

/*****************/
/* FieldListNode */
/*****************/
struct FieldListNode* ast_new_field_list_node(struct FieldNode** fields) {
  struct FieldListNode* node = malloc(sizeof(struct FieldListNode));
  node->kind = AstFieldList;
  node->fields = fields;
  node->length = 0;
  while (fields && *fields) {
    node->length++;
    fields++;
  }
  return node;
}

void ast_free_field_list_node(struct FieldListNode* node) {
  for (size_t i = 0; i < node->length; i++) {
    ast_free_field_node(node->fields[i]);
  }
  free(node->fields);
  node->fields = NULL;

  free(node);
}

void ast_add_field_node(struct FieldListNode* node, struct FieldNode* field) {
  if (!field) {
    return;
  }
  if (!node->fields) {
    node->fields = malloc(sizeof(struct FieldNode*));
  } else {
    node->fields = realloc(node->fields, sizeof(struct FieldNode*) * (node->length + 1));
  }
  node->fields[node->length++] = field;
}

struct FieldListNode* ast_parse_field_list(struct Token** tokens) {
  _CHECK_TOKENS();
  LOG_DEBUG("Parsing Field List: %s", (*tokens)->name);

  struct FieldListNode* field_list = ast_new_field_list_node(NULL);
  if (!ast_field_list_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected identifier got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }

  while (!token_is_end(**tokens)) {
    ast_add_field_node(field_list, ast_parse_field(tokens));
  }
  return field_list;
}

inline bool ast_field_list_token_matches_first_set(struct Token token) {
  return ast_identifier_token_matches_first_set(token);
}

/*************/
/* FieldNode */
/*************/
struct FieldNode* ast_new_field_node(
  struct IdentifierNode* identifier,
  struct TypeIdentifierNode* type_identifier
) {
  struct FieldNode* node = malloc(sizeof(struct FieldNode));
  node->kind = AstField;
  node->identifier = identifier;
  node->type_identifier = type_identifier;
  return node;
}

void ast_free_field_node(struct FieldNode* node) {
  ast_free_identifier_node(node->identifier);
  node->identifier = NULL;
  ast_free_type_identifier_node(node->type_identifier);
  node->type_identifier = NULL;

  free(node);
}

struct FieldNode* ast_parse_field(struct Token** tokens) {
  _CHECK_TOKENS();
  LOG_DEBUG("Parsing Field: %s", (*tokens)->name);

  if (!ast_field_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected an identifier got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }

  struct IdentifierNode* identifier = ast_parse_identifier(tokens);
  if (!token_is_colon(**tokens)) {
    LOG_ERROR("Expected ':' got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }
  _ADVANCE_TOKEN(tokens);
  struct TypeIdentifierNode* type = ast_parse_type_identifier(tokens);
  return ast_new_field_node(identifier, type);
}

inline bool ast_field_token_matches_first_set(struct Token token) {
  return ast_identifier_token_matches_first_set(token);
}

/***************************/
/* FunctionDeclarationNode */
/***************************/
struct FunctionDeclarationNode* ast_new_function_declaration_node(
  struct IdentifierNode* identifier,
  struct TypeIdentifierNode* return_type,
  struct ParameterListNode* parameters,
  struct DoStatementNode* body
) {
  struct FunctionDeclarationNode* node = malloc(sizeof(struct FunctionDeclarationNode));
  node->kind = AstFunctionDeclaration;
  node->identifier = identifier;
  node->return_type = return_type;
  node->parameters = parameters;
  node->body = body;
  return node;
}

void ast_free_function_declaration_node(struct FunctionDeclarationNode* node) {
  ast_free_identifier_node(node->identifier);
  node->identifier = NULL;
  ast_free_type_identifier_node(node->return_type);
  node->return_type = NULL;
  ast_free_parameter_list_node(node->parameters);
  node->parameters = NULL;
  ast_free_do_statement_node(node->body);
  node->body = NULL;

  free(node);
}

struct FunctionDeclarationNode* ast_parse_function_declaration(struct Token** tokens) {
  _CHECK_TOKENS();
  LOG_DEBUG("Parsing Function Declaration: %s", (*tokens)->name);

  if (!ast_function_declaration_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected '%s' got '%s' - %s:%d:%d", HELPERS_STRINGIFY(TOKEN_FUN), (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }

  _ADVANCE_TOKEN(tokens);
  struct IdentifierNode* identifier = ast_parse_identifier(tokens);
  struct ParameterListNode* parameters = ast_parse_parameter_list(tokens);
  struct TypeIdentifierNode* return_type = ast_parse_type_identifier(tokens);
  if (!token_is_do(**tokens)) {
    LOG_ERROR("Expected '%s' got '%s' - %s:%d:%d", HELPERS_STRINGIFY(TOKEN_DO), (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }
  
  struct DoStatementNode* body = ast_parse_do_statement(tokens);
  return ast_new_function_declaration_node(
    identifier,
    return_type,
    parameters,
    body
  );
}

inline bool ast_function_declaration_token_matches_first_set(struct Token token) {
  return token_is_fun(token);
}

/******************/
/* IdentifierNode */
/******************/
struct IdentifierNode* ast_new_identifier_node(char* name) {
  struct IdentifierNode* node = malloc(sizeof(struct IdentifierNode));
  node->kind = AstIdentifier;
  node->name = name;
  return node;
}

void ast_free_identifier_node(struct IdentifierNode* node) {
  free(node->name);
  node->name = NULL;

  free(node);
}

struct IdentifierNode* ast_parse_identifier(struct Token** tokens) {
  _CHECK_TOKENS();
  LOG_DEBUG("Parsing Identifier: %s", (*tokens)->name);

  if (!ast_identifier_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected identifier got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }

  size_t name_length = (strlen((*tokens)->name) + 1);
  char* name = malloc(sizeof(char) * name_length);
  memset(name, '\0', sizeof(char) * name_length);
  strcpy(name, (*tokens)->name);
  _ADVANCE_TOKEN(tokens);
  return ast_new_identifier_node(name);
}

inline bool ast_identifier_token_matches_first_set(struct Token token) {
  return token_is_identifier(token);
}

/****************************/
/* IdentifierExpressionNode */
/****************************/
struct IdentifierExpressionNode* ast_new_identifier_expression_node(
  struct IdentifierNode* identifier,
  struct IdentifierExpressionNode* next
) {
  struct IdentifierExpressionNode* node = malloc(sizeof(struct IdentifierExpressionNode));
  node->kind = AstIdentifierExpression;
  node->identifier = identifier;
  node->next = next;
  return node;
}
void ast_free_identifier_expression_node(struct IdentifierExpressionNode* node) {
  ast_free_identifier_node(node->identifier);
  node->identifier = NULL;
  if (node->next) {
    ast_free_identifier_expression_node(node->next);
    node->next = NULL;
  }
  free(node);
}

struct IdentifierExpressionNode* ast_parse_identifier_expression(struct Token** tokens) {
  _CHECK_TOKENS();
  LOG_DEBUG("Parsing Identifier Expression: %s", (*tokens)->name);

  if (!ast_identifier_expression_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected identifier expression got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }
  struct IdentifierNode* identifier = ast_parse_identifier(tokens);
  struct IdentifierExpressionNode* next = NULL;
  if (token_is_period(**tokens)) {
    _ADVANCE_TOKEN(tokens);
    next = ast_parse_identifier_expression(tokens);
  }
  return ast_new_identifier_expression_node(identifier, next);
}

inline bool ast_identifier_expression_token_matches_first_set(struct Token token) {
  return ast_identifier_token_matches_first_set(token);
}

/***********************/
/* ImportStatementNode */
/***********************/
struct ImportStatementNode* ast_new_import_statement_node(
  ImportNodeKind import_kind,
  struct StringExpressionNode* module_name
) {
  struct ImportStatementNode* node = malloc(sizeof(struct ImportStatementNode));
  node->kind = AstImportStatement;
  node->import_kind = import_kind;
  node->module_name = module_name;
  return node;
}

void ast_free_import_statement_node(struct ImportStatementNode* node) {
  ast_free_string_expression_node(node->module_name);
  node->module_name = NULL;
  free(node);
}

struct ImportStatementNode* ast_parse_import_statement(struct Token** tokens) {
  _CHECK_TOKENS();
  LOG_DEBUG("Parsing Import Statement: %s", (*tokens)->name);

  if (!ast_import_statement_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected import statement got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }
  ImportNodeKind import_kind = ImportStatement;
  if (token_is_importc(**tokens)) {
    import_kind = ImportCStatement;
  }
  _ADVANCE_TOKEN(tokens);
  struct StringExpressionNode* module_name = ast_parse_string_expression(tokens);
  return ast_new_import_statement_node(import_kind, module_name);
}

inline bool ast_import_statement_token_matches_first_set(struct Token token) {
  return (
    token_is_import(token) || 
    token_is_importc(token)
  );
}

/*************************/
/* IntegerExpressionNode */
/*************************/
struct IntegerExpressionNode* ast_new_integer_expression_node(int64_t value) {
  struct IntegerExpressionNode* node = malloc(sizeof(struct IntegerExpressionNode));
  node->kind = AstIntegerExpression;
  node->value = value;
  return node;
}

void ast_free_integer_expression_node(struct IntegerExpressionNode* node) {
  free(node);
}

struct IntegerExpressionNode* ast_parse_integer_expression(struct Token** tokens) {
  _CHECK_TOKENS();
  LOG_DEBUG("Parsing Integer Expression: %s", (*tokens)->name);

  if (!ast_integer_expression_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected integer got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }
  const int64_t value = atoll((*tokens)->name);
  _ADVANCE_TOKEN(tokens);
  return ast_new_integer_expression_node(value);
}

inline bool ast_integer_expression_token_matches_first_set(struct Token token) {
  return token_is_integer(token);
}

/******************/
/* LetBindingNode */
/******************/
struct LetBindingNode* ast_new_let_binding_node(
  struct IdentifierNode* binding,
  struct TypeIdentifierNode* type,
  struct ExpressionNode* expression
) {
  struct LetBindingNode* node = malloc(sizeof(struct LetBindingNode));
  node->kind = AstLetBinding;
  node->binding = binding;
  node->type = type;
  node->expression = expression;
  return node;
}

void ast_free_let_binding_node(struct LetBindingNode* node) {
  ast_free_identifier_node(node->binding);
  node->binding = NULL;
  if (node->type) {
    ast_free_type_identifier_node(node->type);
    node->type = NULL;
  }
  ast_free_expression_node(node->expression);
  node->expression = NULL;

  free(node);
}

struct LetBindingNode* ast_parse_let_binding(struct Token** tokens) {
  _CHECK_TOKENS();
  LOG_DEBUG("Parsing Let Binding: %s", (*tokens)->name);

  if (!ast_let_binding_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected 'let' got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }
  _ADVANCE_TOKEN(tokens);
  struct IdentifierNode* binding = ast_parse_identifier(tokens);
  struct TypeIdentifierNode* type = NULL;
  if (token_is_colon(**tokens)) {
    _ADVANCE_TOKEN(tokens);
    type = ast_parse_type_identifier(tokens);
  }
  if (!token_is_binding_arrow(**tokens)) {
    LOG_ERROR("Expected '->' got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }
  
  _ADVANCE_TOKEN(tokens);
  struct ExpressionNode* expression = ast_parse_expression(tokens);
  return ast_new_let_binding_node(binding, type, expression);
}

inline bool ast_let_binding_token_matches_first_set(struct Token token) {
  return token_is_let(token);
}

/**********************/
/* ListExpressionNode */
/**********************/
struct ListExpressionNode* ast_new_list_expression_node(
  struct ExpressionListNode* expressions
) {
  struct ListExpressionNode* node = malloc(sizeof(struct ListExpressionNode));
  node->kind = AstListExpression;
  node->expressions = expressions;
  return node;
}

void ast_free_list_expression_node(struct ListExpressionNode* node) {
  ast_free_expression_list_node(node->expressions);
  node->expressions = NULL;

  free(node);
}

struct ListExpressionNode* ast_parse_list_expression(struct Token** tokens) {
  _CHECK_TOKENS();
  LOG_DEBUG("Parsing List Expression: %s", (*tokens)->name);

  if (!ast_list_expression_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected '[' got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }
  _ADVANCE_TOKEN(tokens);
  struct ExpressionListNode* expressions = ast_parse_expression_list(tokens);
  if (!token_is_close_bracket(**tokens)) {
    LOG_ERROR("Expected ']' got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }
  _ADVANCE_TOKEN(tokens);
  return ast_new_list_expression_node(expressions);
}

inline bool ast_list_expression_token_matches_first_set(struct Token token) {
  return token_is_open_bracket(token);
}

/*********************/
/* MatchCaseListNode */
/*********************/
struct MatchCaseListNode* ast_new_match_case_list_node(struct MatchCaseNode** cases) {
  struct MatchCaseListNode* node = malloc(sizeof(struct MatchCaseListNode));
  node->kind = AstMatchCaseList;
  node->cases = cases;
  node->length = 0;
  while (cases && *cases) {
    node->length++;
    cases++;
  }
  return node;
}

void ast_free_match_case_list_node(struct MatchCaseListNode* node) {
  for (size_t i = 0; i < node->length; i++) {
    ast_free_match_case_node(node->cases[i]);
  }
  free(node->cases);
  node->cases = NULL;

  free(node);
}

struct MatchCaseListNode* ast_parse_match_case_list(struct Token** tokens) {
  _CHECK_TOKENS();
  LOG_DEBUG("Parsing Match Case List: %s", (*tokens)->name);

  struct MatchCaseListNode* case_list = ast_new_match_case_list_node(NULL);
  while (ast_match_case_list_token_matches_first_set(**tokens)) {
    ast_add_match_case_node(case_list, ast_parse_match_case(tokens));
  }
  return case_list;
}

inline bool ast_match_case_list_token_matches_first_set(struct Token token) {
  return ast_match_case_token_matches_first_set(token);
}

void ast_add_match_case_node(struct MatchCaseListNode* node, struct MatchCaseNode* match_case) {
  if (!match_case) {
    return;
  }
  if (!node->cases) {
    node->cases = malloc(sizeof(struct MatchCaseNode*));
  } else {
    node->cases = realloc(node->cases, sizeof(struct MatchCaseNode*) * (node->length + 1));
  }
  node->cases[node->length++] = match_case;
}

/*****************/
/* MatchCaseNode */
/*****************/
struct MatchCaseNode* ast_new_match_case_node(struct CallExpressionNode* condition, struct StatementNode* statement) {
  struct MatchCaseNode* node = malloc(sizeof(struct MatchCaseNode));
  node->kind = AstMatchCase;
  node->condition = condition;
  node->statement = statement;
  return node;
}

void ast_free_match_case_node(struct MatchCaseNode* node) {
  ast_free_call_expression_node(node->condition);
  node->condition = NULL;
  ast_free_statement_node(node->statement);
  node->statement = NULL;

  free(node);
}

struct MatchCaseNode* ast_parse_match_case(struct Token** tokens) {
  _CHECK_TOKENS();
  LOG_DEBUG("Parsing Match Case: %s", (*tokens)->name);

  if (!ast_match_case_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected '(' got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }

  struct CallExpressionNode* condition = ast_parse_call_expression(tokens);
  if (!token_is_fat_arrow(**tokens)) {
    LOG_ERROR("Expected '=>' got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }
  _ADVANCE_TOKEN(tokens);
  struct StatementNode* statement = ast_parse_statement(tokens);
  return ast_new_match_case_node(condition, statement);
}

inline bool ast_match_case_token_matches_first_set(struct Token token) {
  return ast_call_expression_token_matches_first_set(token);
}

/**********************/
/* MatchStatementNode */
/**********************/
struct MatchStatementNode* ast_new_match_statement_node(struct MatchCaseListNode* case_list) {
  struct MatchStatementNode* node = malloc(sizeof(struct MatchStatementNode));
  node->kind = AstMatchStatement;
  node->case_list = case_list;
  return node;
}

void ast_free_match_statement_node(struct MatchStatementNode* node) {
  ast_free_match_case_list_node(node->case_list);
  node->case_list = NULL;

  free(node);
}

struct MatchStatementNode* ast_parse_match_statement(struct Token** tokens) {
  _CHECK_TOKENS();
  LOG_DEBUG("Parsing Match Statement: %s", (*tokens)->name);

  if (!ast_match_statement_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected match got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }
  _ADVANCE_TOKEN(tokens);

  struct MatchCaseListNode* match_case_list = ast_parse_match_case_list(tokens);
  if (!token_is_end(**tokens)) {
    LOG_ERROR("Expected '" HELPERS_STRINGIFY(TOKEN_END) "' got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }
  _ADVANCE_TOKEN(tokens);
  return ast_new_match_statement_node(match_case_list);
}

inline bool ast_match_statement_token_matches_first_set(struct Token token) {
  return token_is_match(token);
}

/***************************/
/* ModuleStatementListNode */
/**************************/
struct ModuleStatementListNode* ast_new_module_statement_list_node(
  struct ModuleStatementNode** module_statements
) {
  struct ModuleStatementListNode* node = malloc(sizeof(struct ModuleStatementListNode));
  node->kind = AstModuleStatementList;
  node->module_statements = module_statements;
  node->length = 0;
  while (module_statements && *module_statements) {
    node->length++;
    module_statements++;
  }
  return node;
}

void ast_free_module_statement_list_node(struct ModuleStatementListNode* node) {
  for (size_t i = 0; i < node->length; i++) {
    ast_free_module_statement_node(node->module_statements[i]);
  }
  free(node->module_statements);
  node->module_statements = NULL;

  free(node);
}

void ast_add_module_statement_node(struct ModuleStatementListNode* node, struct ModuleStatementNode* module_statement) {
  if (!module_statement) {
    return;
  }
  if (!node->module_statements) {
    node->module_statements = malloc(sizeof(struct ModuleStatementNode*));
  } else {
    node->module_statements = realloc(node->module_statements, sizeof(struct ModuleStatementNode*) * (node->length + 1));
  }
  node->module_statements[node->length++] = module_statement;
}

struct ModuleStatementListNode* ast_parse_module_statement_list(struct Token** tokens) {
  _CHECK_TOKENS();
  LOG_DEBUG("Parsing Module Statement List: %s", (*tokens)->name);

  if (!ast_module_statement_list_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected module statement for list got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }

  struct ModuleStatementListNode* module_statement_list = ast_new_module_statement_list_node(NULL);
  while (tokens && *tokens && ast_module_statement_list_token_matches_first_set(**tokens)) {
    ast_add_module_statement_node(
      module_statement_list,
      ast_parse_module_statement(tokens)
    );
  }
  return module_statement_list;
}

inline bool ast_module_statement_list_token_matches_first_set(struct Token token) {
  return ast_module_statement_token_matches_first_set(token);
}

/***********************/
/* ModuleStatementNode */
/***********************/
struct ModuleStatementNode* ast_new_module_statement_node(AstNodeKind kind, union ModuleStatementNodeUnion value) {
  struct ModuleStatementNode* node = malloc(sizeof(struct ModuleStatementNode));
  switch (kind) {
    case AstFunctionDeclaration: {
    } break;
    case AstImportStatement: {
    } break;
    case AstLetBinding: {
    } break;
    case AstTypeDeclaration: {
    } break;
    default:
      LOG_ERROR("Invalid ModuleStatementNode kind");
      exit(1);
  }
  node->kind = kind;
  node->value = value;
  return node;
}

void ast_free_module_statement_node(struct ModuleStatementNode* node) {
  switch (node->kind) {
    case AstFunctionDeclaration: {
      ast_free_function_declaration_node(node->value.function_declaration);
    } break;
    case AstImportStatement: {
      ast_free_import_statement_node(node->value.import_statement);
    } break;
    case AstLetBinding: {
      ast_free_let_binding_node(node->value.let_binding);
    } break;
    case AstTypeDeclaration: {
      ast_free_type_declaration_node(node->value.type_declaration);
    } break;
    default: {
      LOG_ERROR("Invalid ModuleStatementNode kind");
      exit(1);
    }
  }

  free(node);
}

struct ModuleStatementNode* ast_parse_module_statement(struct Token** tokens) {
  _CHECK_TOKENS();
  LOG_DEBUG("Parsing Module Statement: %s", (*tokens)->name);

  if (ast_function_declaration_token_matches_first_set(**tokens)) {
    return ast_new_module_statement_node(
      AstFunctionDeclaration,
      (union ModuleStatementNodeUnion) {
        .function_declaration = ast_parse_function_declaration(tokens)
      }
    );
  } else if (ast_type_declaration_token_matches_first_set(**tokens)) {
    return ast_new_module_statement_node(
      AstTypeDeclaration,
      (union ModuleStatementNodeUnion) {
        .type_declaration = ast_parse_type_declaration(tokens)
      }
    );
  } else if (ast_let_binding_token_matches_first_set(**tokens)) {
    return ast_new_module_statement_node(
      AstLetBinding,
      (union ModuleStatementNodeUnion) {
        .let_binding = ast_parse_let_binding(tokens)
      }
    );
  } else if (ast_import_statement_token_matches_first_set(**tokens)) {
    return ast_new_module_statement_node(
      AstImportStatement,
      (union ModuleStatementNodeUnion) {
        .import_statement = ast_parse_import_statement(tokens)
      }
    );
  } else {
    LOG_ERROR("Expected Module Statement got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }
}

inline bool ast_module_statement_token_matches_first_set(struct Token token) {
  return (
    ast_function_declaration_token_matches_first_set(token) ||
    ast_let_binding_token_matches_first_set(token) ||
    ast_type_declaration_token_matches_first_set(token) ||
    ast_import_statement_token_matches_first_set(token)
  );
}

/******************/
/* MutBindingNode */
/******************/
struct MutBindingNode* ast_new_mut_binding_node(
  struct IdentifierNode* binding,
  struct TypeIdentifierNode* type,
  struct MutExpressionNode* expression
) {
  struct MutBindingNode* node = malloc(sizeof(struct MutBindingNode));
  node->kind = AstMutBinding;
  node->binding = binding;
  node->type = type;
  node->mut_expression = expression;
  return node;
}

void ast_free_mut_binding_node(struct MutBindingNode* node) {
  ast_free_identifier_node(node->binding);
  node->binding = NULL;
  if (node->type) {
    ast_free_type_identifier_node(node->type);
    node->type = NULL;
  }
  ast_free_mut_expression_node(node->mut_expression);
  node->mut_expression = NULL;

  free(node);
}

struct MutBindingNode* ast_parse_mut_binding(struct Token** tokens) {
  _CHECK_TOKENS();
  LOG_DEBUG("Parsing Mut Binding: %s", (*tokens)->name);

  if (!ast_mut_binding_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected 'mut' got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }
  _ADVANCE_TOKEN(tokens);
  struct IdentifierNode* binding = ast_parse_identifier(tokens);
  struct TypeIdentifierNode* type = NULL;
  if (token_is_colon(**tokens)) {
    _ADVANCE_TOKEN(tokens);
    type = ast_parse_type_identifier(tokens); 
  }
  if (!token_is_binding_arrow(**tokens)) {
    LOG_ERROR("Expected '->' got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }
  _ADVANCE_TOKEN(tokens);
  struct MutExpressionNode* mut_expression = ast_parse_mut_expression(tokens);
  return ast_new_mut_binding_node(binding, type, mut_expression);
}

inline bool ast_mut_binding_token_matches_first_set(struct Token token) {
  return token_is_mut(token);
}

/*********************/
/* MutExpressionNode */
/*********************/
struct MutExpressionNode* ast_new_mut_expression_node(
  AstNodeKind kind,
  union MutExpressionNodeUnion value
) {
  struct MutExpressionNode* node = malloc(sizeof(struct MutExpressionNode));
  node->kind = kind;
  node->value = value;
  return node;
}

void ast_free_mut_expression_node(struct MutExpressionNode* node) {
  switch (node->kind) {
    case AstNewAlloc: {
      ast_free_new_alloc_node(node->value.new_alloc);
    } break;
    case AstExpression: {
      ast_free_expression_node(node->value.expression);
    } break;
    default: {
      LOG_ERROR("Invalid MutExpressionNode kind");
      exit(1);
    }
  }

  free(node);
}

struct MutExpressionNode* ast_parse_mut_expression(struct Token** tokens) {
  _CHECK_TOKENS();
  LOG_DEBUG("Parsing Mut Expression: %s", (*tokens)->name);

  if (!ast_mut_expression_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected a mut expression got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }
  if (ast_new_alloc_token_matches_first_set(**tokens)){
    struct NewAllocNode* new_alloc = ast_parse_new_alloc(tokens);
    return ast_new_mut_expression_node(
      AstNewAlloc,
      (union MutExpressionNodeUnion) {
        .new_alloc = new_alloc
      }
    );
  } else if (ast_expression_token_matches_first_set(**tokens)) {
    struct ExpressionNode* expression = ast_parse_expression(tokens);
    return ast_new_mut_expression_node(
      AstExpression,
      (union MutExpressionNodeUnion) {
        .expression = expression
      }
    );
  } else {
    LOG_ERROR("Invalid ExpressionNode kind");
    exit(1);
  }
}

inline bool ast_mut_expression_token_matches_first_set(struct Token token) {
  return (
    ast_new_alloc_token_matches_first_set(token) ||
    ast_expression_token_matches_first_set(token)
  );
}

/****************/
/* NewAllocNode */
/****************/
struct NewAllocNode* ast_new_new_alloc_node(struct StructuredTypeExpressionNode* structured_type_expression) {
  struct NewAllocNode* node = malloc(sizeof(struct NewAllocNode));
  node->kind = AstNewAlloc;
  node->structured_type_expression = structured_type_expression;
  return node;
}

void ast_free_new_alloc_node(struct NewAllocNode* new_alloc) {
  ast_free_structured_type_expression_node(new_alloc->structured_type_expression);
  new_alloc->structured_type_expression = NULL;

  free(new_alloc);
}

struct NewAllocNode* ast_parse_new_alloc(struct Token** tokens) {
  _CHECK_TOKENS();
  LOG_DEBUG("Parsing New Alloc Node: %s", (*tokens)->name);

  if (!ast_new_alloc_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected new alloc got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }
  _ADVANCE_TOKEN(tokens);
  struct StructuredTypeExpression* structured_type_expression = ast_parse_structured_type_expression(tokens);
  return ast_new_new_alloc_node(structured_type_expression);
}

inline bool ast_new_alloc_token_matches_first_set(struct Token token) {
  return token_is_new(token);
}

/*************************/
/* NumericExpressionNode */
/*************************/
struct NumericExpressionNode* ast_new_numeric_expression_node(
  AstNodeKind kind,
  union NumericExpressionNodeUnion value
) {
  struct NumericExpressionNode* node = malloc(sizeof(struct NumericExpressionNode));
  node->kind = kind;
  node->value = value;
  return node;
}

void ast_free_numeric_expression_node(struct NumericExpressionNode* node) {
  switch (node->kind) {
    case AstDoubleExpression: {
      ast_free_double_expression_node(node->value.double_expression);
    } break;
    case AstIntegerExpression: {
      ast_free_integer_expression_node(node->value.integer_expression);
    } break;
    default: {
      LOG_ERROR("Invalid NumericExpressionNode kind: %d", node->kind);
      exit(1);
    }
  }

  free(node);
}

struct NumericExpressionNode* ast_parse_numeric_expression(struct Token** tokens) {
  _CHECK_TOKENS();
  LOG_DEBUG("Parsing Numeric Expression: %s", (*tokens)->name);

  if (ast_double_expression_token_matches_first_set(**tokens)) {
    return ast_new_numeric_expression_node(
      AstDoubleExpression,
      (union NumericExpressionNodeUnion) {
        .double_expression = ast_parse_double_expression(tokens)
      }
    );
  } else if (ast_integer_expression_token_matches_first_set(**tokens)) {
    return ast_new_numeric_expression_node(
      AstIntegerExpression,
      (union NumericExpressionNodeUnion) {
        .integer_expression = ast_parse_integer_expression(tokens)
      }
    );
  }

  LOG_ERROR("Expected number got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
  exit(1);
}

inline bool ast_numeric_expression_token_matches_first_set(struct Token token) {
  return (
    ast_double_expression_token_matches_first_set(token) ||
    ast_integer_expression_token_matches_first_set(token)
  );
}

/*********************/
/* ParameterListNode */
/*********************/
struct ParameterListNode* ast_new_parameter_list_node(
  struct ParameterNode** parameters
) {
  struct ParameterListNode* node = malloc(sizeof(struct ParameterListNode));
  node->kind = AstParameterList;
  node->parameters = parameters;
  node->length = 0;
  while (parameters && *parameters) {
    node->length++;
    parameters++;
  }
  return node;
}

void ast_free_parameter_list_node(struct ParameterListNode* node) {
  for (size_t i = 0; i < node->length; i++) {
    ast_free_parameter_node(node->parameters[i]);
  }
  free(node->parameters);
  node->parameters = NULL;

  free(node);
}

void ast_add_parameter_node(struct ParameterListNode* node, struct ParameterNode* parameter) {
  if (!parameter) {
    return;
  }
  if (!node->parameters) {
    node->parameters = malloc(sizeof(struct ParameterNode*));
  } else {
    node->parameters = realloc(node->parameters, sizeof(struct ParameterNode*) * (node->length + 1));
  }
  node->parameters[node->length++] = parameter;
}

struct ParameterListNode* ast_parse_parameter_list(struct Token** tokens) {
  _CHECK_TOKENS();
  LOG_DEBUG("Parsing Parameter List: %s", (*tokens)->name);

  struct ParameterListNode* parameter_list = ast_new_parameter_list_node(NULL);
  if (!ast_parameter_list_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected '(' got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }

  _ADVANCE_TOKEN(tokens);

  while (!token_is_close_paren(**tokens)) {
    ast_add_parameter_node(parameter_list, ast_parse_parameter(tokens));
  }
  _ADVANCE_TOKEN(tokens);

  return parameter_list;
}

inline bool ast_parameter_list_token_matches_first_set(struct Token token) {
  return token_is_open_paren(token);
}

/*****************/
/* ParameterNode */
/*****************/
struct ParameterNode* ast_new_parameter_node(
  struct IdentifierNode* identifier,
  struct TypeIdentifierNode* type_identifier
) {
  struct ParameterNode* node = malloc(sizeof(struct ParameterNode));
  node->kind = AstParameter;
  node->identifier = identifier;
  node->type_identifier = type_identifier;
  return node;
}

void ast_free_parameter_node(struct ParameterNode* node) {
  ast_free_identifier_node(node->identifier);
  node->identifier = NULL;
  ast_free_type_identifier_node(node->type_identifier);
  node->type_identifier = NULL;

  free(node);
}

struct ParameterNode* ast_parse_parameter(struct Token** tokens) {
  _CHECK_TOKENS();
  LOG_DEBUG("Parsing Parameter: %s", (*tokens)->name);

  if (!ast_parameter_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected an identifier got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }

  struct IdentifierNode* identifier = ast_parse_identifier(tokens);
  if (!token_is_colon(**tokens)) {
    LOG_ERROR("Expected ':' got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }
  _ADVANCE_TOKEN(tokens);
  struct TypeIdentifierNode* type = ast_parse_type_identifier(tokens);
  return ast_new_parameter_node(identifier, type);
}

inline bool ast_parameter_token_matches_first_set(struct Token token) {
  return ast_identifier_token_matches_first_set(token);
}

/***************/
/* ProgramNode */
/***************/
struct ProgramNode* ast_new_program_node(
  struct ShebangNode* shebang,
  struct ModuleStatementListNode* module_statements
) {
  struct ProgramNode* node = malloc(sizeof(struct ProgramNode));
  node->kind = AstProgram;
  node->shebang = shebang;
  node->module_statements = module_statements;
  return node;
}

void ast_free_program_node(struct ProgramNode* node) {
  ast_free_shebang_node(node->shebang);
  node->shebang = NULL;
  ast_free_module_statement_list_node(node->module_statements);
  node->module_statements = NULL;

  free(node);
}

struct ProgramNode* ast_parse_program(struct Token** tokens) {
  _CHECK_TOKENS();
  LOG_DEBUG("Parsing Program: %s", (*tokens)->name);

  if (!ast_program_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected '#!' or module statement got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }
  struct ShebangNode* shebang = NULL;
  if (ast_shebang_token_matches_first_set(**tokens)) {
    shebang = ast_parse_shebang(tokens);
  }
  struct ModuleStatementListNode* module_statement_list = ast_parse_module_statement_list(tokens);
  return ast_new_program_node(shebang, module_statement_list);
}

inline bool ast_program_token_matches_first_set(struct Token token) {
  return (
    ast_shebang_token_matches_first_set(token) ||
    ast_module_statement_list_token_matches_first_set(token)
  );
}

/************************/
/* ReturnStatementNode */
/************************/
struct ReturnStatementNode* ast_new_return_statement_node(struct ExpressionNode* expression) {
  struct ReturnStatementNode* node = malloc(sizeof(struct ReturnStatementNode));
  node->kind = AstReturnStatement;
  node->expression = expression;
  return node;
}

void ast_free_return_statement_node(struct ReturnStatementNode* node) {
  ast_free_expression_node(node->expression);
  node->expression = NULL;

  free(node);
}

struct ReturnStatementNode* ast_parse_return_statement(struct Token** tokens) {
  _CHECK_TOKENS();
  LOG_DEBUG("Parsing Return Statement: %s", (*tokens)->name);

  if (!ast_return_statement_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected return got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }
  _ADVANCE_TOKEN(tokens);
  struct ExpressionNode* expression = ast_parse_expression(tokens);
  return ast_new_return_statement_node(expression);
}

inline bool ast_return_statement_token_matches_first_set(struct Token token) {
  return token_is_return(token);
}

/***************/
/* ShebangNode */
/***************/
struct ShebangNode* ast_new_shebang_node() {
  struct ShebangNode* node = malloc(sizeof(struct ShebangNode));
  node->kind = AstShebang;
  return node;
}

void ast_free_shebang_node(struct ShebangNode* node) {
  if (!node) {
    return;
  }
  free(node);
}

struct ShebangNode* ast_parse_shebang(struct Token** tokens) {
  _CHECK_TOKENS();
  LOG_DEBUG("Parsing shebang: %s", (*tokens)->name);

  if (!ast_shebang_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected '#!' got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }
  _ADVANCE_TOKEN(tokens);
  return ast_new_shebang_node();
}

inline bool ast_shebang_token_matches_first_set(struct Token token) {
  return token_is_shebang(token);
}

/*****************/
/* StatementNode */
/*****************/
struct StatementNode* ast_new_statement_node(
  AstNodeKind kind,
  union StatementNodeUnion value
) {
  struct StatementNode* node = malloc(sizeof(struct StatementNode));
  node->kind = kind;
  node->value = value;
  return node;
}

void ast_free_statement_node(struct StatementNode* node) {
  switch (node->kind) {
    case AstBindingStatement: {
      ast_free_binding_statement_node(node->value.binding_statement);
    } break;
    case AstDoStatement: {
      ast_free_do_statement_node(node->value.do_statement);
    } break;
    case AstMatchStatement: {
      ast_free_match_statement_node(node->value.match_statement);
    } break;
    case AstReturnStatement: {
      ast_free_return_statement_node(node->value.return_statement);
    } break;
    case AstExpression: {
      ast_free_expression_node(node->value.expression);
    } break;
    default: {
      LOG_ERROR("Invalid StatementNode kind: %d", node->kind);
      exit(1);
    }
  }

  free(node);
}

struct StatementNode* ast_parse_statement(struct Token** tokens) {
  _CHECK_TOKENS();
  LOG_DEBUG("Parsing Statement: %s", (*tokens)->name);

  if (!ast_statement_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected a statement got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }

  if (ast_match_statement_token_matches_first_set(**tokens)) {
    struct MatchStatementNode* statement = ast_parse_match_statement(tokens);
    return ast_new_statement_node(
      AstMatchStatement,
      (union StatementNodeUnion) {
        .match_statement = statement
      }
    );
  } else if (ast_return_statement_token_matches_first_set(**tokens)) {
    struct ReturnStatementNode* statement = ast_parse_return_statement(tokens);
    return ast_new_statement_node(
      AstReturnStatement,
      (union StatementNodeUnion) {
        .return_statement = statement
      }
    );
  } else if (ast_binding_statement_token_matches_first_set(**tokens)) {
    struct BindingStatementNode* statement = ast_parse_binding_statement(tokens);
    return ast_new_statement_node(
      AstBindingStatement,
      (union StatementNodeUnion) {
        .binding_statement = statement
      }
    );
  } else if (ast_do_statement_token_matches_first_set(**tokens)) {
    struct DoStatementNode* statement = ast_parse_do_statement(tokens);
    return ast_new_statement_node(
      AstDoStatement,
      (union StatementNodeUnion) {
        .do_statement = statement
      }
    );
  } else {
    struct ExpressionNode* expression = ast_parse_expression(tokens);
    return ast_new_statement_node(
      AstExpression,
      (union StatementNodeUnion) {
        .expression = expression
      }
    );
  }
}

inline bool ast_statement_token_matches_first_set(struct Token token) {
  return (
    ast_do_statement_token_matches_first_set(token) ||
    ast_match_statement_token_matches_first_set(token) ||
    ast_return_statement_token_matches_first_set(token) ||
    ast_binding_statement_token_matches_first_set(token) ||
    ast_expression_token_matches_first_set(token)
  );
}

/*********************/
/* StatementListNode */
/*********************/
struct StatementListNode* ast_new_statement_list_node(struct StatementNode** statements) {
  struct StatementListNode* node = malloc(sizeof(struct StatementListNode));
  node->kind = AstStatementList;
  node->statements = statements;
  node->length = 0;
  while (statements && *statements) {
    node->length++;
    statements++;
  }
  return node;
}

void ast_free_statement_list_node(struct StatementListNode* node) {
  for (size_t i = 0; i < node->length; i++) {
    ast_free_statement_node(node->statements[i]);
  }
  free(node->statements);
  node->statements = NULL;

  free(node);
}

void ast_add_statement_node(struct StatementListNode* node, struct StatementNode* statement) {
  if (!statement) {
    return;
  }
  if (!node->statements) {
    node->statements = malloc(sizeof(struct StatementNode*));
  } else {
    node->statements = realloc(node->statements, sizeof(struct StatementNode*) * (node->length + 1));
  }
  node->statements[node->length++] = statement;
}

struct StatementListNode* ast_parse_statement_list(struct Token** tokens) {
  _CHECK_TOKENS();
  LOG_DEBUG("Parsing Statement List: %s", (*tokens)->name);

  struct StatementListNode* statement_list = ast_new_statement_list_node(NULL);
  if (!ast_statement_list_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected statement got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }

  while (ast_statement_list_token_matches_first_set(**tokens)) {
    ast_add_statement_node(statement_list, ast_parse_statement(tokens));
  }
  return statement_list;
}

inline bool ast_statement_list_token_matches_first_set(struct Token token) {
  return ast_statement_token_matches_first_set(token);
}

/************************/
/* StringExpressionNode */
/************************/
struct StringExpressionNode* ast_new_string_expression_node(char* value) {
  struct StringExpressionNode* node = malloc(sizeof(struct StringExpressionNode));
  node->kind = AstStringExpression;
  node->value = value;
  return node;
}
void ast_free_string_expression_node(struct StringExpressionNode* node) {
  free(node->value);
  node->value = NULL;

  free(node);
}

struct StringExpressionNode* ast_parse_string_expression(struct Token** tokens) {
  _CHECK_TOKENS();
  LOG_DEBUG("Parsing String Expression: %s", (*tokens)->name);

  if (!ast_string_expression_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected string got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }
  const size_t token_length = (*tokens)->length + 1;
  char* value = malloc(sizeof(char) * token_length);
  memset(value, '\0', sizeof(char) * token_length);
  strncpy(value, (*tokens)->name, token_length - 1);
  _ADVANCE_TOKEN(tokens);
  return ast_new_string_expression_node(value);
}

inline bool ast_string_expression_token_matches_first_set(struct Token token) {
  return token_is_string_literal(token);
}

/*****************************/
/* StructTypeDeclarationNode */
/*****************************/
struct StructTypeDeclarationNode* ast_new_struct_type_declaration_node(struct IdentifierNode* identifier, struct FieldListNode* fields) {
  struct StructTypeDeclarationNode* node = malloc(sizeof(struct StructTypeDeclarationNode));
  node->kind = AstStructTypeDeclaration;
  node->identifier = identifier;
  node->fields = fields;
  return node;
}

void ast_free_struct_type_declaration_node(struct StructTypeDeclarationNode* struct_type_declaration) {
  ast_free_identifier_node(struct_type_declaration->identifier);
  struct_type_declaration->identifier = NULL;
  ast_free_field_list_node(struct_type_declaration->fields);
  struct_type_declaration->fields = NULL;

  free(struct_type_declaration);
}

struct StructTypeDeclarationNode* ast_parse_struct_type_declaration(
  struct IdentifierNode* identifier,
  struct Token** tokens
) {
  _CHECK_TOKENS();
  LOG_DEBUG("Parsing Struct Type Declaration: %s", (*tokens)->name);

  if (!ast_struct_type_declaration_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected struct type declaration got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }
  _ADVANCE_TOKEN(tokens);
  if (!token_is_is(**tokens)) {
    LOG_ERROR("Expected 'is' got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }
  _ADVANCE_TOKEN(tokens);
  struct FieldListNode* fields = ast_parse_field_list(tokens);
  if (!token_is_end(**tokens)) {
    LOG_ERROR("Expected 'end' got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }
  _ADVANCE_TOKEN(tokens);
  return ast_new_struct_type_declaration_node(identifier, fields);
}

inline bool ast_struct_type_declaration_token_matches_first_set(struct Token token) {
  return token_is_struct(token);
}

/********************************/
/* StructuredTypeExpressionNode */
/********************************/
struct StructuredTypeExpressionNode* ast_new_structured_type_expression_node(
  struct TypeIdentifierNode* type,
  struct FieldBindingListNode* field_bindings
) {
  struct StructuredTypeExpressionNode* node = malloc(sizeof(struct StructuredTypeExpressionNode));
  node->kind = AstStructuredTypeExpression;
  node->type = type;
  node->field_bindings = field_bindings;
  return node;
}

void ast_free_structured_type_expression_node(struct StructuredTypeExpressionNode* node) {
  ast_free_type_identifier_node(node->type);
  node->type = NULL;
  ast_free_field_binding_list_node(node->field_bindings);
  node->field_bindings = NULL;

  free(node);
}

struct StructuredTypeExpressionNode* ast_parse_structured_type_expression(struct Token** tokens) {
  _CHECK_TOKENS();
  LOG_DEBUG("Parsing Struct Type Expression: %s", (*tokens)->name);

  if (!ast_structured_type_expression_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected '{' got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }
  _ADVANCE_TOKEN(tokens);
  struct TypeIdentifierNode* type = ast_parse_type_identifier(tokens);
  struct FieldBindingListNode* field_bindings = ast_parse_field_binding_list(tokens);
  if (!token_is_close_brace(**tokens)) {
    LOG_ERROR("Expected '}' got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }
  _ADVANCE_TOKEN(tokens);
  return ast_new_structured_type_expression_node(type, field_bindings);
}

inline bool ast_structured_type_expression_token_matches_first_set(struct Token token) {
  return token_is_open_brace(token);
}

/***********************/
/* TypeDeclarationNode */
/***********************/
struct TypeDeclarationNode* ast_new_type_declaration_node(
  AstNodeKind kind,
  union TypeDeclarationNodeUnion value
) {
  struct TypeDeclarationNode* node = malloc(sizeof(struct TypeDeclarationNode));
  node->kind = kind;
  node->value = value;
  return node;
}

void ast_free_type_declaration_node(struct TypeDeclarationNode* node) {
  switch (node->kind) {
    case AstEnumTypeDeclaration: {
      ast_free_enum_type_declaration_node(node->value.enum_type_declaration);
    } break;
    case AstStructTypeDeclaration: {
      ast_free_struct_type_declaration_node(node->value.struct_type_declaration);
    } break;
    case AstUnionTypeDeclaration: {
      ast_free_union_type_declaration_node(node->value.union_type_declaration);
    } break;
    default: {
      LOG_ERROR("Invalid TypeDeclarationNode kind");
      exit(1);
    } break;
  }
  free(node);
}

struct TypeDeclarationNode* ast_parse_type_declaration(struct Token** tokens) {
  _CHECK_TOKENS();
  LOG_DEBUG("Parsing Type Declaration: %s", (*tokens)->name);

  if (!ast_type_declaration_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected type declaration got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }
  _ADVANCE_TOKEN(tokens);
  struct IdentifierNode* identifier = ast_parse_identifier(tokens);
  if (token_is_enum(**tokens)) {
    struct EnumTypeDeclarationNode* declaration = ast_parse_enum_type_declaration(identifier, tokens);
    return ast_new_type_declaration_node(
      AstEnumTypeDeclaration,
      (union TypeDeclarationNodeUnion) {
        .enum_type_declaration = declaration
      }
    );
  } else if (token_is_struct(**tokens)) {
    struct StructTypeDeclarationNode* declaration = ast_parse_struct_type_declaration(identifier, tokens);
    return ast_new_type_declaration_node(
      AstStructTypeDeclaration,
      (union TypeDeclarationNodeUnion) {
        .struct_type_declaration = declaration
      }
    );
  } else if (token_is_union(**tokens)) {
    struct UnionTypeDeclarationNode* declaration = ast_parse_union_type_declaration(identifier, tokens);
    return ast_new_type_declaration_node(
      AstUnionTypeDeclaration,
      (union TypeDeclarationNodeUnion) {
        .union_type_declaration = declaration
      }
    );
  } else {
    LOG_ERROR("Invalid TypeDeclarationNode kind");
    exit(1);
  }
}

inline bool ast_type_declaration_token_matches_first_set(struct Token token) {
  return token_is_type(token);
}

/**********************/
/* TypeExpressionNode */
/**********************/
struct TypeExpressionNode* ast_new_type_expression_node(
  AstNodeKind kind,
  union TypeExpressionNodeUnion value
) {
  struct TypeExpressionNode* node = malloc(sizeof(struct TypeExpressionNode));
  node->kind = kind;
  node->value = value;
  return node;
}

void ast_free_type_expression_node(struct TypeExpressionNode* node) {
  switch (node->kind) {
    case AstEnumTypeExpression: {
      ast_free_enum_type_expression_node(node->value.enum_type_expression);
    } break;
    case AstStructuredTypeExpression: {
      ast_free_structured_type_expression_node(node->value.structured_type_expression);
    } break;
    default: {
      LOG_ERROR("Invalid TypeExpressionNode kind");
      exit(1);
    } break;
  }
  free(node);
}

struct TypeExpressionNode* ast_parse_type_expression(struct Token** tokens) {
  _CHECK_TOKENS();
  LOG_DEBUG("Parsing Type Expression: %s", (*tokens)->name);

  if (!ast_type_expression_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected type expression got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }
  if (ast_enum_type_expression_token_matches_first_set(**tokens)) {
    struct EnumTypeExpressionNode* expression = ast_parse_enum_type_expression(tokens);
    return ast_new_type_expression_node(
      AstEnumTypeExpression,
      (union TypeExpressionNodeUnion) {
        .enum_type_expression = expression
      }
    );
  } else if (ast_structured_type_expression_token_matches_first_set(**tokens)) {
    struct StructuredTypeExpressionNode* expression = ast_parse_structured_type_expression(tokens);
    return ast_new_type_expression_node(
      AstStructuredTypeExpression,
      (union TypeExpressionNodeUnion) {
        .structured_type_expression = expression
      }
    );
  } else {
    LOG_ERROR("Invalid TypeExpressionNode kind got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }
}

inline bool ast_type_expression_token_matches_first_set(struct Token token) {
  return (
    token_is_open_brace(token) ||
    token_is_hash(token)
  );
}

/**********************/
/* TypeIdentifierNode */
/**********************/
struct TypeIdentifierNode* ast_new_type_identifier_node(struct IdentifierNode* identifier, struct TypeIdentifierNode* contained_type) {
  struct TypeIdentifierNode* node = malloc(sizeof(struct TypeIdentifierNode));
  node->kind = AstTypeIdentifier;
  node->identifier = identifier;
  node->contained_type = contained_type;
  return node;
}

void ast_free_type_identifier_node(struct TypeIdentifierNode* type_identifier) {
  ast_free_identifier_node(type_identifier->identifier);
  type_identifier->identifier = NULL;
  if (type_identifier->contained_type != NULL) {
    ast_free_type_identifier_node(type_identifier->contained_type);
    type_identifier->contained_type = NULL;
  }
  free(type_identifier);
}

struct TypeIdentifierNode* ast_parse_type_identifier(struct Token** tokens) {  
  _CHECK_TOKENS();
  LOG_DEBUG("Parsing TypeIdentifier: %s", (*tokens)->name);

  if (!ast_type_identifier_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected type identifier got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }
  struct IdentifierNode* identifier = ast_parse_identifier(tokens);
  struct TypeIdentifierNode* contained_type = NULL;
  if (token_is_left_angle(**tokens)) {
    _ADVANCE_TOKEN(tokens);
    contained_type = ast_parse_type_identifier(tokens);
    if (!token_is_right_angle(**tokens)) {
      LOG_ERROR("Expected '>' got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
      exit(1);
    }
    _ADVANCE_TOKEN(tokens);
  }
  return ast_new_type_identifier_node(identifier, contained_type);
}

inline bool ast_type_identifier_token_matches_first_set(struct Token token) {
  return ast_identifier_token_matches_first_set(token);
}

/****************************/
/* UnionTypeDeclarationNode */
/****************************/
struct UnionTypeDeclarationNode* ast_new_union_type_declaration_node(struct IdentifierNode* identifier, struct FieldListNode* fields) {
  struct UnionTypeDeclarationNode* node = malloc(sizeof(struct UnionTypeDeclarationNode));
  node->kind = AstUnionTypeDeclaration;
  node->identifier = identifier;
  node->fields = fields;
  return node;
}

void ast_free_union_type_declaration_node(struct UnionTypeDeclarationNode* union_type_declaration) {
  ast_free_identifier_node(union_type_declaration->identifier);
  union_type_declaration->identifier = NULL;
  ast_free_field_list_node(union_type_declaration->fields);
  union_type_declaration->fields = NULL;

  free(union_type_declaration);
}

struct UnionTypeDeclarationNode* ast_parse_union_type_declaration(
  struct IdentifierNode* identifier,
  struct Token** tokens
) {
  _CHECK_TOKENS();
  LOG_DEBUG("Parsing Union Type Declaration: %s", (*tokens)->name);

  if (!ast_union_type_declaration_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected union type declaration got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }
  _ADVANCE_TOKEN(tokens);
  if (!token_is_is(**tokens)) {
    LOG_ERROR("Expected 'is' got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }
  _ADVANCE_TOKEN(tokens);
  struct FieldListNode* fields = ast_parse_field_list(tokens);
  if (!token_is_end(**tokens)) {
    LOG_ERROR("Expected 'end' got '%s' - %s:%d:%d", (*tokens)->name, (*tokens)->filename, (*tokens)->line_number, (*tokens)->column);
    exit(1);
  }
  _ADVANCE_TOKEN(tokens);
  return ast_new_union_type_declaration_node(identifier, fields);
}

inline bool ast_union_type_declaration_token_matches_first_set(struct Token token) {
  return token_is_union(token);
}
