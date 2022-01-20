#pragma once

#include <stdio.h>

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

typedef enum {
  AstBlank,
  AstBindingExpression,
  AstCallExpression,
  AstDeclaration,
  AstDeclarationList,
  AstExpression,
  AstExpressionList,
  AstFunctionDeclaration,
  AstIdentifier,
  AstIdentifierExpression,
  AstMatchCase,
  AstMatchCaseList,
  AstMatchExpression,
  AstNumericExpression,
  AstParameter,
  AstParameterList,
  AstProgram,
  AstReturnExpression,
  AstStringExpression,
  AstTypeIdentifier,
} AstNodeKind;

struct AstNode;

struct BindingExpressionNode;
struct CallExpressionNode;
struct DeclarationListNode;
struct DeclarationNode;
struct ExpressionListNode;
struct ExpressionNode;
struct FunctionDeclarationNode;
struct IdentifierNode;
struct IdentifierExpressionNode;
struct MatchCaseNode;
struct MatchCaseListNode;
struct MatchExpressionNode;
struct NumericExpressionNode;
struct ParameterListNode;
struct ParameterNode;
struct ProgramNode;
struct ReturnExpressionNode;
struct StringExpressionNode;
struct TypeIdentifierNode;

union AstNodeUnion;
union ExpressionNodeUnion;
union DeclarationNodeUnion;

union AstNodeUnion {
  struct BindingExpressionNode* binding_expression;
  struct CallExpressionNode* call_expression;
  struct DeclarationListNode* declaration_list;
  struct DeclarationNode* declaration;
  struct ExpressionListNode* expression_list;
  struct ExpressionNode* expression;
  struct FunctionDeclarationNode* function_declaration;
  struct IdentifierNode* identifier;
  struct IdentifierExpressionNode* identifier_expression;
  struct MatchCaseNode* match_case;
  struct MatchCaseListNode* match_case_list;
  struct MatchExpressionNode* match_expression;
  struct NumericExpressionNode* numeric_expression;
  struct ParameterListNode* parameter_list;
  struct ParameterNode* parameter;
  struct ProgramNode* program;
  struct ReturnExpressionNode* return_expression;
  struct StringExpressionNode* string_expression;
  struct TypeIdentifierNode* type_identifier;
};

union DeclarationNodeUnion {
  struct FunctionDeclarationNode* function_declaration;
};

union ExpressionNodeUnion {
  struct BindingExpressionNode* binding_expression;
  struct CallExpressionNode* call_expression;
  struct IdentifierExpressionNode* identifier_expression;
  struct MatchExpressionNode* match_expression;
  struct NumericExpressionNode* numeric_expression;
  struct ReturnExpressionNode* return_expression;
  struct StringExpressionNode* string_expression;
};

struct AstNode* ast_new_node(AstNodeKind, union AstNodeUnion);
void ast_free_node(struct AstNode*);

struct BindingExpressionNode* ast_new_binding_expression_node(struct IdentifierNode*, struct IdentifierNode*, struct ExpressionNode*);
void ast_free_binding_expression_node(struct BindingExpressionNode*);
struct BindingExpressionNode* ast_parse_binding_expression(struct Token**);
bool ast_binding_expression_token_matches_first_set(struct Token);

struct CallExpressionNode* ast_new_call_expression_node(struct IdentifierNode*, struct ExpressionListNode*);
void ast_free_call_expression_node(struct CallExpressionNode*);
struct CallExpressionNode* ast_parse_call_expression(struct Token**);
bool ast_call_expression_token_matches_first_set(struct Token);

struct DeclarationListNode* ast_new_declaration_list_node(struct DeclarationNode**);
void ast_free_declaration_list_node(struct DeclarationListNode*);
void ast_add_declaration_node(struct DeclarationListNode*, struct DeclarationNode*);
struct DeclarationListNode* ast_parse_declaration_list(struct Token**);
bool ast_declaration_list_token_matches_first_set(struct Token);

struct DeclarationNode* ast_new_declaration_node(AstNodeKind, union DeclarationNodeUnion);
void ast_free_declaration_node(struct DeclarationNode*);
struct DeclarationNode* ast_parse_declaration(struct Token** tokens);
bool ast_declaration_token_matches_first_set(struct Token);

struct ExpressionListNode* ast_new_expression_list_node(struct ExpressionNode**);
void ast_free_expression_list_node(struct ExpressionListNode*);
void ast_add_expression_node(struct ExpressionListNode*, struct ExpressionNode*);
struct ExpressionListNode* ast_parse_expression_list(struct Token**);
bool ast_expression_list_token_matches_first_set(struct Token);

struct ExpressionNode* ast_new_expression_node(AstNodeKind, union ExpressionNodeUnion);
void ast_free_expression_node(struct ExpressionNode*);
struct ExpressionNode* ast_parse_expression(struct Token**);
bool ast_expression_token_matches_first_set(struct Token);

struct FunctionDeclarationNode* ast_new_function_declaration_node(struct IdentifierNode*, struct TypeIdentifierNode*, struct ParameterListNode*, struct ExpressionListNode*);
void ast_free_function_declaration_node(struct FunctionDeclarationNode*);
struct FunctionDeclarationNode* ast_parse_function_declaration(struct Token**);
bool ast_function_declaration_token_matches_first_set(struct Token);

struct IdentifierNode* ast_new_identifier_node(char*);
void ast_free_identifier_node(struct IdentifierNode*);
struct IdentifierNode* ast_parse_identifier(struct Token**);
bool ast_identifier_token_matches_first_set(struct Token);

struct IdentifierExpressionNode* ast_new_identifier_expression_node(struct IdentifierNode*);
void ast_free_identifier_expression_node(struct IdentifierExpressionNode*);
struct IdentifierExpressionNode* ast_parse_identifier_expression(struct Token**);
bool ast_identifier_expression_token_matches_first_set(struct Token);

struct MatchCaseNode* ast_new_match_case_node(struct CallExpressionNode*, struct ExpressionNode*);
void ast_free_match_case_node(struct MatchCaseNode*);
struct MatchCaseNode* ast_parse_match_case(struct Token**);
bool ast_match_case_token_matches_first_set(struct Token);

struct MatchCaseListNode* ast_new_match_case_list_node(struct MatchCaseNode**);
void ast_free_match_case_list_node(struct MatchCaseListNode*);
struct MatchCaseListNode* ast_parse_match_case_list(struct Token**);
void ast_add_match_case_node(struct MatchCaseListNode*, struct MatchCaseNode*);
bool ast_match_case_list_token_matches_first_set(struct Token);

struct MatchExpressionNode* ast_new_match_expression_node(struct MatchCaseListNode*);
void ast_free_match_expression_node(struct MatchExpressionNode*);
struct MatchExpressionNode* ast_parse_match_expression(struct Token**);
bool ast_match_expression_token_matches_first_set(struct Token);

struct NumericExpressionNode* ast_new_numeric_expression_node(int);
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

struct ProgramNode* ast_new_program_node(struct DeclarationListNode*);
void ast_free_program_node(struct ProgramNode*);
struct ProgramNode* ast_parse_program(struct Token**);
bool ast_program_token_matches_first_set(struct Token);

struct ReturnExpressionNode* ast_new_return_expression_node(struct ExpressionNode*);
void ast_free_return_expression_node(struct ReturnExpressionNode*);
struct ReturnExpressionNode* ast_parse_return_expression(struct Token**);
bool ast_return_expression_token_matches_first_set(struct Token);

struct StringExpressionNode* ast_new_string_expression_node(char*);
void ast_free_string_expression_node(struct StringExpressionNode*);
struct StringExpressionNode* ast_parse_string_expression(struct Token**);
bool ast_string_expression_token_matches_first_set(struct Token);

struct TypeIdentifierNode* ast_new_type_identifier_node(struct IdentifierNode*, struct TypeIdentifierNode*);
void ast_free_type_identifier_node(struct TypeIdentifierNode*);
struct TypeIdentifierNode* ast_parse_type_identifier(struct Token**);
bool ast_type_identifier_token_matches_first_set(struct Token);

struct AstNode {
  AstNodeKind kind;
  union AstNodeUnion value;
};

struct BindingExpressionNode {
  AstNodeKind kind;
  struct IdentifierNode* binding;
  struct IdentifierNode* type;
  struct ExpressionNode* expression;
};

struct CallExpressionNode {
  AstNodeKind kind;
  struct IdentifierNode* function;
  struct ExpressionListNode* arguments;
};

struct DeclarationListNode {
  AstNodeKind kind;
  struct DeclarationNode** declarations;
  size_t length;
};

struct DeclarationNode {
  AstNodeKind kind;
  union DeclarationNodeUnion value;
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

struct FunctionDeclarationNode {
  AstNodeKind kind;
  struct IdentifierNode* identifier;
  struct TypeIdentifierNode* return_type;
  struct ParameterListNode* parameters;
  struct ExpressionListNode* expressions;
};

struct IdentifierNode {
  AstNodeKind kind;
  char* name;
};

struct IdentifierExpressionNode {
  AstNodeKind kind;
  struct IdentifierNode* identifier;
};

struct MatchCaseNode {
  AstNodeKind kind;
  struct CallExpressionNode* condition;
  struct ExpressionNode* expression;
};

struct MatchCaseListNode {
  AstNodeKind kind;
  struct MatchCaseNode** cases;
  size_t length;
};

struct MatchExpressionNode {
  AstNodeKind kind;
  struct MatchCaseListNode* case_list;
};

struct NumericExpressionNode {
  AstNodeKind kind;
  int value;
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

struct ProgramNode {
  AstNodeKind kind;
  struct DeclarationListNode* declarations;
};

struct ReturnExpressionNode {
  AstNodeKind kind;
  struct ExpressionNode* expression;
};

struct StringExpressionNode {
  AstNodeKind kind;
  char* value;
};

struct TypeIdentifierNode {
  AstNodeKind kind;
  struct IdentifierNode* identifier;
  struct TypeIdentifierNode* contained_type;
};

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
    case AstBindingExpression: {
      ast_free_binding_expression_node(node->value.binding_expression);
    } break;
    case AstCallExpression: {
      ast_free_call_expression_node(node->value.call_expression);
    } break;
    case AstDeclarationList: {
      ast_free_declaration_list_node(node->value.declaration_list);
    } break;
    case AstDeclaration: {
      ast_free_declaration_node(node->value.declaration);
    } break;
    case AstExpressionList: {
      ast_free_expression_list_node(node->value.expression_list);
    } break;
    case AstExpression: {
      ast_free_expression_node(node->value.expression);
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
    case AstMatchCase: {
      ast_free_match_case_node(node->value.match_case);
    } break;
    case AstMatchExpression: {
      ast_free_match_expression_node(node->value.match_expression);
    } break;
    case AstMatchCaseList: {
      ast_free_match_case_list_node(node->value.match_case_list);
    } break;
    case AstNumericExpression: {
      ast_free_numeric_expression_node(node->value.numeric_expression);
    } break;
    case AstParameterList: {
      ast_free_parameter_list_node(node->value.parameter_list);
    } break;
    case AstParameter: {
      ast_free_parameter_node(node->value.parameter);
    } break;
    case AstProgram: {
      ast_free_program_node(node->value.program);
    } break;
    case AstStringExpression: {
      ast_free_string_expression_node(node->value.string_expression);
    } break;
    default: {
      LOG_ERROR("Invalid AstNode kind");
      exit(1);
    }
  }

  free(node);
}

/*************************/
/* BindingExpressionNode */
/*************************/
struct BindingExpressionNode* ast_new_binding_expression_node(
  struct IdentifierNode* binding,
  struct IdentifierNode* type,
  struct ExpressionNode* expression
) {
  struct BindingExpressionNode* node = malloc(sizeof(struct BindingExpressionNode));
  node->kind = AstBindingExpression;
  node->binding = binding;
  node->type = type;
  node->expression = expression;
  return node;
}

void ast_free_binding_expression_node(struct BindingExpressionNode* node) {
  ast_free_identifier_node(node->binding);
  node->binding = NULL;
  ast_free_identifier_node(node->type);
  node->type = NULL;
  ast_free_expression_node(node->expression);
  node->expression = NULL;

  free(node);
}

struct BindingExpressionNode* ast_parse_binding_expression(struct Token** tokens) {
  LOG_DEBUG("Parsing Binding Expression");
  _CHECK_TOKENS();

  if (!ast_binding_expression_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected 'let' got '%s'", (*tokens)->name);
    exit(1);
  }
  _ADVANCE_TOKEN(tokens);
  struct IdentifierNode* binding = ast_parse_identifier(tokens);
  if (!token_is_colon(**tokens)) {
    LOG_ERROR("Expected ':' got '%s'", (*tokens)->name);
    exit(1);
  }
  _ADVANCE_TOKEN(tokens);
  struct IdentifierNode* type = ast_parse_identifier(tokens);
  if (!token_is_binding_arrow(**tokens)) {
    LOG_ERROR("Expected '->' got '%s'", (*tokens)->name);
    exit(1);
  }
  _ADVANCE_TOKEN(tokens);
  struct ExpressionNode* expression = ast_parse_expression(tokens);
  return ast_new_binding_expression_node(binding, type, expression);
}

inline bool ast_binding_expression_token_matches_first_set(struct Token token) {
  return token_is_let(token);
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
  LOG_DEBUG("Parsing Call Expression");
  _CHECK_TOKENS();

  if (!ast_call_expression_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected '(' got '%s'", (*tokens)->name);
    exit(1);
  }
  _ADVANCE_TOKEN(tokens);
  struct IdentifierNode* function = ast_parse_identifier(tokens);
  struct ExpressionListNode* arguments = ast_parse_expression_list(tokens);
  if (
    !token_is_close_paren(**tokens) &&
    !token_is_end(**tokens) &&
    !token_is_return(**tokens) &&
    !token_is_match(**tokens)
  ) {
    LOG_ERROR("Expected ')' got '%s'", (*tokens)->name);
    exit(1);
  }
  _ADVANCE_TOKEN(tokens);
  return ast_new_call_expression_node(function, arguments);
}

inline bool ast_call_expression_token_matches_first_set(struct Token token) {
  return token_is_open_paren(token);
}

/***********************/
/* DeclarationListNode */
/***********************/
struct DeclarationListNode* ast_new_declaration_list_node(
  struct DeclarationNode** declarations
) {
  struct DeclarationListNode* node = malloc(sizeof(struct DeclarationListNode));
  node->kind = AstDeclarationList;
  node->declarations = declarations;
  node->length = 0;
  while (declarations && *declarations) {
    node->length++;
    declarations++;
  }
  return node;
}

void ast_free_declaration_list_node(struct DeclarationListNode* node) {
  for (size_t i = 0; i < node->length; i++) {
    ast_free_declaration_node(node->declarations[i]);
  }
  free(node->declarations);
  node->declarations = NULL;

  free(node);
}

void ast_add_declaration_node(struct DeclarationListNode* node, struct DeclarationNode* declaration) {
  if (!declaration) {
    return;
  }
  if (!node->declarations) {
    node->declarations = malloc(sizeof(struct DeclarationNode*));
  } else {
    node->declarations = realloc(node->declarations, sizeof(struct DeclarationNode*) * (node->length + 1));
  }
  node->declarations[node->length++] = declaration;
}

struct DeclarationListNode* ast_parse_declaration_list(struct Token** tokens) {
  LOG_DEBUG("Parsing Declaration List");
  _CHECK_TOKENS();

  if (!ast_declaration_list_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected '%s' got '%s'", HELPERS_STRINGIFY(TOKEN_FUN), (*tokens)->name);
    exit(1);
  }

  struct DeclarationListNode* declaration_list = ast_new_declaration_list_node(NULL);
  while (tokens && *tokens && ast_declaration_list_token_matches_first_set(**tokens)) {
    ast_add_declaration_node(
      declaration_list,
      ast_parse_declaration(tokens)
    );
  }
  return declaration_list;
}

inline bool ast_declaration_list_token_matches_first_set(struct Token token) {
  return token_is_fun(token);
}

/*******************/
/* DeclarationNode */
/*******************/
struct DeclarationNode* ast_new_declaration_node(AstNodeKind kind, union DeclarationNodeUnion value) {
  struct DeclarationNode* node = malloc(sizeof(struct DeclarationNode));
  switch (kind) {
    case AstFunctionDeclaration: {
    } break;
    default:
      LOG_ERROR("Invalid DeclarationNode kind");
      exit(1);
  }
  node->kind = kind;
  node->value = value;
  return node;
}

void ast_free_declaration_node(struct DeclarationNode* node) {
  switch (node->kind) {
    case AstFunctionDeclaration: {
      ast_free_function_declaration_node(node->value.function_declaration);
    } break;
    default: {
      LOG_ERROR("Invalid DeclarationNode kind");
      exit(1);
    }
  }

  free(node);
}

struct DeclarationNode* ast_parse_declaration(struct Token** tokens) {
  LOG_DEBUG("Parsing Declaration");
  _CHECK_TOKENS();

  if (!ast_declaration_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected '%s' got '%s'", HELPERS_STRINGIFY(TOKEN_FUN), (*tokens)->name);
    exit(1);
  }

  if (token_is_fun(**tokens)) {
    return ast_new_declaration_node(
      AstFunctionDeclaration,
      (union DeclarationNodeUnion) {
        .function_declaration = ast_parse_function_declaration(tokens)
      }
    );
  }
  
  LOG_ERROR("'%s' not yet implemented for parsing DeclarationNode", (*tokens)->name);
  exit(1);
}

inline bool ast_declaration_token_matches_first_set(struct Token token) {
  return token_is_fun(token);
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
  LOG_DEBUG("Parsing Expression List");
  _CHECK_TOKENS();

  struct ExpressionListNode* expression_list = ast_new_expression_list_node(NULL);
  while (ast_expression_list_token_matches_first_set(**tokens)) {
    if (
      !tokens ||
      !*tokens || 
      token_is_end(**tokens) ||
      token_is_close_paren(**tokens)
    ) {
      break;
    }
    ast_add_expression_node(expression_list, ast_parse_expression(tokens));
  }
  return expression_list;
}

inline bool ast_expression_list_token_matches_first_set(struct Token token) {
  UNUSED(token);
  return true;
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
    case AstBindingExpression: {
      ast_free_binding_expression_node(node->value.binding_expression);
    } break;
    case AstCallExpression: {
      ast_free_call_expression_node(node->value.call_expression);
    } break;
    case AstIdentifierExpression: {
      ast_free_identifier_expression_node(node->value.identifier_expression);
    } break;
    case AstMatchExpression: {
      ast_free_match_expression_node(node->value.match_expression);
    } break;
    case AstNumericExpression: {
      ast_free_numeric_expression_node(node->value.numeric_expression);
    } break;
    case AstReturnExpression: {
      ast_free_return_expression_node(node->value.return_expression);
    } break;
    case AstStringExpression: {
      ast_free_string_expression_node(node->value.string_expression);
    } break;
    default: {
      LOG_ERROR("Invalid ExpressionNode kind");
      exit(1);
    }
  }

  free(node);
}

struct ExpressionNode* ast_parse_expression(struct Token** tokens) {
  LOG_DEBUG("Parsing Expression");
  _CHECK_TOKENS();

  if (!ast_expression_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected something else");
    exit(1);
  }
  if (ast_string_expression_token_matches_first_set(**tokens)){
    struct StringExpressionNode* expression = ast_parse_string_expression(tokens);
    return ast_new_expression_node(
      expression->kind,
      (union ExpressionNodeUnion) {
        .string_expression = expression
      }
    );
  } else if (ast_numeric_expression_token_matches_first_set(**tokens)) {
    struct NumericExpressionNode* expression = ast_parse_numeric_expression(tokens);
    return ast_new_expression_node(
      expression->kind,
      (union ExpressionNodeUnion) {
        .numeric_expression = expression
      }
    );
  } else if (ast_call_expression_token_matches_first_set(**tokens)) {
    struct CallExpressionNode* expression = ast_parse_call_expression(tokens);
    return ast_new_expression_node(
      expression->kind,
      (union ExpressionNodeUnion) {
        .call_expression = expression
      }
    );
  } else if (ast_binding_expression_token_matches_first_set(**tokens)) {
    struct BindingExpressionNode* expression = ast_parse_binding_expression(tokens);
    return ast_new_expression_node(
      expression->kind,
      (union ExpressionNodeUnion) {
        .binding_expression = expression
      }
    );
  } else if (ast_return_expression_token_matches_first_set(**tokens)) {
    struct ReturnExpressionNode* expression = ast_parse_return_expression(tokens);
    return ast_new_expression_node(
      expression->kind,
      (union ExpressionNodeUnion) {
        .return_expression = expression
      }
    );
  } else if (ast_match_expression_token_matches_first_set(**tokens)) {
    struct MatchExpressionNode* expression = ast_parse_match_expression(tokens);
    return ast_new_expression_node(
      expression->kind,
      (union ExpressionNodeUnion) {
        .match_expression = expression
      }
    );
  } else if (ast_identifier_token_matches_first_set(**tokens)) {
    struct IdentifierExpressionNode* expression = ast_parse_identifier_expression(tokens);
    return ast_new_expression_node(
      expression->kind,
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
  UNUSED(token);
  return true;
}

/***************************/
/* FunctionDeclarationNode */
/***************************/
struct FunctionDeclarationNode* ast_new_function_declaration_node(
  struct IdentifierNode* identifier,
  struct TypeIdentifierNode* return_type,
  struct ParameterListNode* parameters,
  struct ExpressionListNode* expression
) {
  struct FunctionDeclarationNode* node = malloc(sizeof(struct FunctionDeclarationNode));
  node->kind = AstFunctionDeclaration;
  node->identifier = identifier;
  node->return_type = return_type;
  node->parameters = parameters;
  node->expressions = expression;
  return node;
}

void ast_free_function_declaration_node(struct FunctionDeclarationNode* node) {
  ast_free_identifier_node(node->identifier);
  node->identifier = NULL;
  ast_free_type_identifier_node(node->return_type);
  node->return_type = NULL;
  ast_free_parameter_list_node(node->parameters);
  node->parameters = NULL;
  ast_free_expression_list_node(node->expressions);
  node->expressions = NULL;

  free(node);
}

struct FunctionDeclarationNode* ast_parse_function_declaration(struct Token** tokens) {
  LOG_DEBUG("Parsing Function Declaration");
  _CHECK_TOKENS();

  if (!ast_function_declaration_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected '%s' got '%s'", HELPERS_STRINGIFY(TOKEN_FUN), (*tokens)->name);
    exit(1);
  }

  _ADVANCE_TOKEN(tokens);
  struct IdentifierNode* identifier = ast_parse_identifier(tokens);
  struct ParameterListNode* parameters = ast_parse_parameter_list(tokens);
  
  // TODO: Add follow set function
  if (!token_is_fat_arrow(**tokens)) {
    LOG_ERROR("Expected '=>' got '%s'", (*tokens)->name);
    exit(1);
  }
  _ADVANCE_TOKEN(tokens);
  struct TypeIdentifierNode* return_type = ast_parse_type_identifier(tokens);
  if (!token_is_is(**tokens)) {
    LOG_ERROR("Expected '%s' got '%s'", HELPERS_STRINGIFY(TOKEN_IS), (*tokens)->name);
    exit(1);
  }
  _ADVANCE_TOKEN(tokens);
  
  struct ExpressionListNode* expression = ast_parse_expression_list(tokens);
  if (!token_is_end(**tokens)) {
    LOG_ERROR("Expected '%s' got '%s'", HELPERS_STRINGIFY(TOKEN_END), (*tokens)->name);
    exit(1);
  }
  _ADVANCE_TOKEN(tokens);
  return ast_new_function_declaration_node(
    identifier,
    return_type,
    parameters,
    expression
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
  LOG_DEBUG("Parsing Identifier");
  _CHECK_TOKENS();

  if (!ast_identifier_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected identifier got '%s'", (*tokens)->name);
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
  UNUSED(token);
  return true;
}

/****************************/
/* IdentifierExpressionNode */
/****************************/
struct IdentifierExpressionNode* ast_new_identifier_expression_node(struct IdentifierNode* identifier) {
  struct IdentifierExpressionNode* node = malloc(sizeof(struct IdentifierExpressionNode));
  node->kind = AstIdentifierExpression;
  node->identifier = identifier;
  return node;
}
void ast_free_identifier_expression_node(struct IdentifierExpressionNode* node) {
  ast_free_identifier_node(node->identifier);
  node->identifier = NULL;

  free(node);
}

struct IdentifierExpressionNode* ast_parse_identifier_expression(struct Token** tokens) {
  LOG_DEBUG("Parsing Identifier Expression");
  _CHECK_TOKENS();

  if (!ast_identifier_expression_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected identifier got '%s'", (*tokens)->name);
    exit(1);
  }
  return ast_new_identifier_expression_node(ast_parse_identifier(tokens));
}

inline bool ast_identifier_expression_token_matches_first_set(struct Token token) {
  return ast_identifier_token_matches_first_set(token);
}

/*****************/
/* MatchCaseNode */
/*****************/
struct MatchCaseNode* ast_new_match_case_node(struct CallExpressionNode* condition, struct ExpressionNode* expression) {
  struct MatchCaseNode* node = malloc(sizeof(struct MatchCaseNode));
  node->kind = AstMatchCase;
  node->condition = condition;
  node->expression = expression;
  return node;
}

void ast_free_match_case_node(struct MatchCaseNode* node) {
  ast_free_call_expression_node(node->condition);
  node->condition = NULL;
  ast_free_expression_node(node->expression);
  node->expression = NULL;

  free(node);
}

struct MatchCaseNode* ast_parse_match_case(struct Token** tokens) {
  LOG_DEBUG("Parsing Match Case");
  _CHECK_TOKENS();

  if (!ast_match_case_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected '(' got '%s'", (*tokens)->name);
    exit(1);
  }

  struct CallExpressionNode* condition = ast_parse_call_expression(tokens);
  if (!token_is_fat_arrow(**tokens)) {
    LOG_ERROR("Expected '=>' got '%s'", (*tokens)->name);
    exit(1);
  }
  _ADVANCE_TOKEN(tokens);
  struct ExpressionNode* expression = ast_parse_expression(tokens);
  return ast_new_match_case_node(condition, expression);
}

inline bool ast_match_case_token_matches_first_set(struct Token token) {
  return ast_call_expression_token_matches_first_set(token);
}

/***********************/
/* MatchExpressionNode */
/***********************/
struct MatchExpressionNode* ast_new_match_expression_node(struct MatchCaseListNode* case_list) {
  struct MatchExpressionNode* node = malloc(sizeof(struct MatchExpressionNode));
  node->kind = AstMatchExpression;
  node->case_list = case_list;
  return node;
}

void ast_free_match_expression_node(struct MatchExpressionNode* node) {
  ast_free_match_case_list_node(node->case_list);
  node->case_list = NULL;

  free(node);
}

struct MatchExpressionNode* ast_parse_match_expression(struct Token** tokens) {
  LOG_DEBUG("Parsing Match Expression");
  _CHECK_TOKENS();

  if (!ast_match_expression_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected match got '%s'", (*tokens)->name);
    exit(1);
  }
  _ADVANCE_TOKEN(tokens);

  struct MatchCaseListNode* match_case_list = ast_parse_match_case_list(tokens);
  _ADVANCE_TOKEN(tokens);
  return ast_new_match_expression_node(match_case_list);
}

inline bool ast_match_expression_token_matches_first_set(struct Token token) {
  return token_is_match(token);
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
  LOG_DEBUG("Parsing Match Case List");
  _CHECK_TOKENS();

  struct MatchCaseListNode* case_list = ast_new_match_case_list_node(NULL);
  while (ast_match_case_list_token_matches_first_set(**tokens)) {
    ast_add_match_case_node(case_list, ast_parse_match_case(tokens));
    // TODO: Add follow set function
    if (
      !tokens ||
      !*tokens ||
      token_is_end(**tokens)
    ) {
      break;
    }
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

/*************************/
/* NumericExpressionNode */
/*************************/
struct NumericExpressionNode* ast_new_numeric_expression_node(int value) {
  struct NumericExpressionNode* node = malloc(sizeof(struct NumericExpressionNode));
  node->kind = AstNumericExpression;
  node->value = value;
  return node;
}

void ast_free_numeric_expression_node(struct NumericExpressionNode* node) {
  free(node);
}

struct NumericExpressionNode* ast_parse_numeric_expression(struct Token** tokens) {
  LOG_DEBUG("Parsing Numeric Expression");
  _CHECK_TOKENS();

  if (!ast_numeric_expression_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected number got '%s'", (*tokens)->name);
    exit(1);
  }

  const int value = atoi((*tokens)->name);
  _ADVANCE_TOKEN(tokens);
  return ast_new_numeric_expression_node(value);
}

inline bool ast_numeric_expression_token_matches_first_set(struct Token token) {
  return token_is_numeric(token);
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
  LOG_DEBUG("Parsing Parameter List");
  _CHECK_TOKENS();

  struct ParameterListNode* parameter_list = ast_new_parameter_list_node(NULL);
  if (!ast_parameter_list_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected '(' got '%s'", (*tokens)->name);
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
  LOG_DEBUG("Parsing Parameter");
  _CHECK_TOKENS();

  if (!ast_parameter_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected an identifier");
    exit(1);
  }

  struct IdentifierNode* identifier = ast_parse_identifier(tokens);
  if (!token_is_colon(**tokens)) {
    LOG_ERROR("Expected ':' got '%s'", (*tokens)->name);
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
  struct DeclarationListNode* declarations
) {
  struct ProgramNode* node = malloc(sizeof(struct ProgramNode));
  node->kind = AstProgram;
  node->declarations = declarations;
  return node;
}

void ast_free_program_node(struct ProgramNode* node) {
  ast_free_declaration_list_node(node->declarations);
  node->declarations = NULL;

  free(node);
}

struct ProgramNode* ast_parse_program(struct Token** tokens) {
  LOG_DEBUG("Parsing Program");
  _CHECK_TOKENS();

  if (!ast_program_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected '%s' got '%s'", HELPERS_STRINGIFY(TOKEN_FUN), (*tokens)->name);
    exit(1);
  }
  return ast_new_program_node(ast_parse_declaration_list(tokens));
}

inline bool ast_program_token_matches_first_set(struct Token token) {
  return token_is_fun(token);
}

/************************/
/* ReturnExpressionNode */
/************************/
struct ReturnExpressionNode* ast_new_return_expression_node(struct ExpressionNode* expression) {
  struct ReturnExpressionNode* node = malloc(sizeof(struct ReturnExpressionNode));
  node->kind = AstReturnExpression;
  node->expression = expression;
  return node;
}

void ast_free_return_expression_node(struct ReturnExpressionNode* node) {
  ast_free_expression_node(node->expression);
  node->expression = NULL;

  free(node);
}

struct ReturnExpressionNode* ast_parse_return_expression(struct Token** tokens) {
  LOG_DEBUG("Parsing Return Expression");
  _CHECK_TOKENS();

  if (!ast_return_expression_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected return got '%s'", (*tokens)->name);
    exit(1);
  }
  _ADVANCE_TOKEN(tokens);
  struct ExpressionNode* expression = ast_parse_expression(tokens);
  return ast_new_return_expression_node(expression);
}

inline bool ast_return_expression_token_matches_first_set(struct Token token) {
  return token_is_return(token);
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
  LOG_DEBUG("Parsing String Expression");
  _CHECK_TOKENS();

  if (!ast_string_expression_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected string got '%s'", (*tokens)->name);
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
  LOG_DEBUG("Parsing TypeIdentifier");
  _CHECK_TOKENS();

  if (!ast_type_identifier_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected type identifier got '%s'", (*tokens)->name);
    exit(1);
  }
  struct IdentifierNode* identifier = ast_parse_identifier(tokens);
  struct TypeIdentifierNode* contained_type = NULL;
  if (token_is_left_angle(**tokens)) {
    _ADVANCE_TOKEN(tokens);
    contained_type = ast_parse_type_identifier(tokens);
    if (!token_is_right_angle(**tokens)) {
      LOG_ERROR("Expected '>' got '%s'", (*tokens)->name);
      exit(1);
    }
    _ADVANCE_TOKEN(tokens);
  }
  return ast_new_type_identifier_node(identifier, contained_type);
}

inline bool ast_type_identifier_token_matches_first_set(struct Token token) {
  return ast_identifier_token_matches_first_set(token);
}
