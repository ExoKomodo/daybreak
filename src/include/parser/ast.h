#pragma once

#include <lex/token.h>
#include <log/prelude.h>
#include <macros/helpers.h>

#define _CHECK_TOKENS() do { \
  if (!tokens || !*tokens) { \
    return NULL; \
  } \
} while (0);

#define _ADVANCE_TOKEN(tokens, token) do { \
  token_advance(tokens); \
  token = *tokens; \
} while (0);

typedef enum {
  AstBlank,
  AstCallExpression,
  AstDeclaration,
  AstDeclarationList,
  AstExpression,
  AstExpressionList,
  AstFunctionDeclaration,
  AstIdentifier,
  AstNumericExpression,
  AstParameter,
  AstParameterList,
  AstProgram,
  AstStringExpression,
} AstNodeKind;

struct AstNode;

struct CallExpressionNode;
struct DeclarationListNode;
struct DeclarationNode;
struct ExpressionListNode;
struct ExpressionNode;
struct FunctionDeclarationNode;
struct IdentifierNode;
struct NumericExpressionNode;
struct ParameterListNode;
struct ParameterNode;
struct ProgramNode;
struct StringExpressionNode;

union AstNodeUnion;
union ExpressionNodeUnion;
union DeclarationNodeUnion;

union AstNodeUnion {
  struct CallExpressionNode* call_expression;
  struct DeclarationListNode* declaration_list;
  struct DeclarationNode* declaration;
  struct ExpressionListNode* expression_list;
  struct ExpressionNode* expression;
  struct FunctionDeclarationNode* function_declaration;
  struct IdentifierNode* identifier;
  struct NumericExpressionNode* numeric_expression;
  struct ParameterListNode* parameter_list;
  struct ParameterNode* parameter;
  struct ProgramNode* program;
  struct StringExpressionNode* string_expression;
};

union DeclarationNodeUnion {
  struct FunctionDeclarationNode* function_declaration;
};

union ExpressionNodeUnion {
  struct CallExpressionNode* call_expression;
  struct NumericExpressionNode* numeric_expression;
  struct StringExpressionNode* string_expression;
};

struct AstNode* ast_new_node(AstNodeKind, union AstNodeUnion);
void ast_free_node(struct AstNode*);

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

struct ExpressionListNode* ast_new_expression_list_node(struct ExpressionNode** expressions);
void ast_free_expression_list_node(struct ExpressionListNode*);
void ast_add_expression_node(struct ExpressionListNode*, struct ExpressionNode*);
struct ExpressionListNode* ast_parse_expression_list(struct Token**);
bool ast_expression_list_token_matches_first_set(struct Token);

struct ExpressionNode* ast_new_expression_node(AstNodeKind, union ExpressionNodeUnion);
void ast_free_expression_node(struct ExpressionNode*);
struct ExpressionNode* ast_parse_expression(struct Token**);
bool ast_expression_token_matches_first_set(struct Token);

struct FunctionDeclarationNode* ast_new_function_declaration_node(struct IdentifierNode*, struct ParameterListNode*, struct ExpressionListNode*);
void ast_free_function_declaration_node(struct FunctionDeclarationNode*);
struct FunctionDeclarationNode* ast_parse_function_declaration(struct Token**);
bool ast_function_declaration_token_matches_first_set(struct Token);

struct IdentifierNode* ast_new_identifier_node(char*);
void ast_free_identifier_node(struct IdentifierNode*);
struct IdentifierNode* ast_parse_identifier(struct Token**);
bool ast_identifier_token_matches_first_set(struct Token);

struct NumericExpressionNode* ast_new_numeric_expression_node(int);
void ast_free_numeric_expression_node(struct NumericExpressionNode*);
struct NumericExpressionNode* ast_parse_numeric_expression(struct Token**);
bool ast_numeric_expression_token_matches_first_set(struct Token);

struct ParameterListNode* ast_new_parameter_list_node(struct ParameterNode**);
void ast_free_parameter_list_node(struct ParameterListNode*);
void ast_add_parameter_node(struct ParameterListNode*, struct ParameterNode*);
struct ParameterListNode* ast_parse_parameter_list(struct Token**);
bool ast_parameter_list_token_matches_first_set(struct Token);

struct ParameterNode* ast_new_parameter_node(struct IdentifierNode*, struct IdentifierNode*);
void ast_free_parameter_node(struct ParameterNode*);

struct ProgramNode* ast_new_program_node(struct DeclarationListNode*);
void ast_free_program_node(struct ProgramNode*);
struct ProgramNode* ast_parse_program(struct Token**);
bool ast_program_token_matches_first_set(struct Token);

struct StringExpressionNode* ast_new_string_expression_node(char*);
void ast_free_string_expression_node(struct StringExpressionNode*);
struct StringExpressionNode* ast_parse_string_expression(struct Token**);
bool ast_string_expression_token_matches_first_set(struct Token);

struct AstNode {
  AstNodeKind kind;
  union AstNodeUnion value;
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
  struct ParameterListNode* parameters;
  struct ExpressionListNode* expressions;
};

struct IdentifierNode {
  AstNodeKind kind;
  char* name;
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
  struct IdentifierNode* type;
};

struct ProgramNode {
  AstNodeKind kind;
  struct DeclarationListNode* declarations;
};

struct StringExpressionNode {
  AstNodeKind kind;
  char* value;
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
  ast_free_expression_list_node(node->arguments);
  free(node);
}

struct CallExpressionNode* ast_parse_call_expression(struct Token** tokens) {
  LOG_DEBUG("Parsing Call Expression");
  _CHECK_TOKENS();

  struct Token* token = *tokens;
  if (!ast_call_expression_token_matches_first_set(*token)) {
    LOG_ERROR("Expected '(' got '%s'", token->name);
    exit(1);
  }
  _ADVANCE_TOKEN(tokens, token);
  struct IdentifierNode* function = ast_parse_identifier(tokens);
  struct ExpressionListNode* arguments = ast_parse_expression_list(tokens);
  token = *tokens;
  if (!token_is_close_paren(*token)) {
    LOG_ERROR("Expected ')' got '%s'", token->name);
    exit(1);
  }
  _ADVANCE_TOKEN(tokens, token);
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
  return node;
}

void ast_free_declaration_list_node(struct DeclarationListNode* node) {
  struct DeclarationNode** declarations = node->declarations;
  for (size_t i = 0; i < node->length; i++) {
    ast_free_declaration_node(declarations[i]);
  }
  free(node->declarations);
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
  struct Token* token = *tokens;

  if (!ast_declaration_list_token_matches_first_set(*token)) {
    LOG_ERROR("Expected '%s' got '%s'", HELPERS_STRINGIFY(TOKEN_FUN), token->name);
    exit(1);
  }

  struct DeclarationListNode* declaration_list = ast_new_declaration_list_node(NULL);
  while (token && ast_declaration_list_token_matches_first_set(*token)) {
    ast_add_declaration_node(
      declaration_list,
      ast_parse_declaration(tokens)
    );
    token = *tokens;
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
  struct Token* token = *tokens;

  if (!ast_declaration_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected '%s' got '%s'", HELPERS_STRINGIFY(TOKEN_FUN), token->name);
    exit(1);
  }

  if (token_is_fun(*token)) {
    return ast_new_declaration_node(
      AstFunctionDeclaration,
      (union DeclarationNodeUnion) {
        .function_declaration = ast_parse_function_declaration(tokens)
      }
    );
  }
  
  LOG_ERROR("'%s' not yet implemented for parsing DeclarationNode", token->name);
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
  return node;
}

void ast_free_expression_list_node(struct ExpressionListNode* node) {
  struct ExpressionNode** expressions = node->expressions;
  for (size_t i = 0; i < node->length; i++) {
    ast_free_expression_node(expressions[i]);
  }
  free(node->expressions);
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
  struct Token* token = *tokens;

  struct ExpressionListNode* expression_list = ast_new_expression_list_node(NULL);
  while (ast_expression_list_token_matches_first_set(*token)) {
    // ast_add_expression_node(
    //   expression_list,
    //   ast_parse_expression(tokens)
    // );
    // NOTE: Temporarily advance past expressions
    ast_add_expression_node(expression_list, ast_parse_expression(tokens));
    token = *tokens;
    // TODO: Add follow set function
    if (
      !token ||
      token_is_close_paren(*token) ||
      token_is_end(*token)
    ) {
      break;
    }
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
    case AstCallExpression: {
      ast_free_call_expression_node(node->value.call_expression);
    } break;
    case AstNumericExpression: {
      ast_free_numeric_expression_node(node->value.numeric_expression);
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
  struct Token* token = *tokens;

  if (!ast_expression_token_matches_first_set(*token)) {
    LOG_ERROR("Expected something else");
    exit(1);
  }
  if (token_is_string_literal(*token)){
    struct StringExpressionNode* expression = ast_parse_string_expression(tokens);
    return ast_new_expression_node(
      expression->kind,
      (union ExpressionNodeUnion) {
        .string_expression = expression
      }
    );
  } else if (token_is_numeric(*token)) {
    struct NumericExpressionNode* expression = ast_parse_numeric_expression(tokens);
    return ast_new_expression_node(
      expression->kind,
      (union ExpressionNodeUnion) {
        .numeric_expression = expression
      }
    );
  } else {
    struct CallExpressionNode* expression = ast_parse_call_expression(tokens);
    return ast_new_expression_node(
      expression->kind,
      (union ExpressionNodeUnion) {
        .call_expression = expression
      }
    );
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
  struct ParameterListNode* parameters,
  struct ExpressionListNode* expression
) {
  struct FunctionDeclarationNode* node = malloc(sizeof(struct FunctionDeclarationNode));
  node->kind = AstFunctionDeclaration;
  node->identifier = identifier;
  node->parameters = parameters;
  node->expressions = expression;
  return node;
}

void ast_free_function_declaration_node(struct FunctionDeclarationNode* node) {
  ast_free_identifier_node(node->identifier);
  ast_free_parameter_list_node(node->parameters);
  ast_free_expression_list_node(node->expressions);
  free(node);
}

struct FunctionDeclarationNode* ast_parse_function_declaration(struct Token** tokens) {
  LOG_DEBUG("Parsing Function Declaration");
  _CHECK_TOKENS();
  struct Token* token = *tokens;

  if (!ast_function_declaration_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected '%s' got '%s'", HELPERS_STRINGIFY(TOKEN_FUN), token->name);
    exit(1);
  }

  _ADVANCE_TOKEN(tokens, token);
  struct IdentifierNode* identifier = ast_parse_identifier(tokens);
  struct ParameterListNode* parameters = ast_parse_parameter_list(tokens);
  token = *tokens;
  
  // TODO: Add follow set function
  if (!token_is_fat_arrow(*token)) {
    LOG_ERROR("Expected '%s' got '%s'", HELPERS_STRINGIFY(TOKEN_FAT_ARROW), token->name);
    exit(1);
  }
  _ADVANCE_TOKEN(tokens, token);
  // TODO: Check for the identifier to be a non-reserved keyword
  if (!token_is_int(*token)) {
    LOG_ERROR("Expected '%s' got '%s'", HELPERS_STRINGIFY(TOKEN_INT), token->name);
    exit(1);
  }
  _ADVANCE_TOKEN(tokens, token);
  if (!token_is_is(*token)) {
    LOG_ERROR("Expected '%s' got '%s'", HELPERS_STRINGIFY(TOKEN_IS), token->name);
    exit(1);
  }
  _ADVANCE_TOKEN(tokens, token);
  
  struct ExpressionListNode* expression = ast_parse_expression_list(tokens);
  token = *tokens;
  if (!token_is_end(*token)) {
    LOG_ERROR("Expected '%s' got '%s'", HELPERS_STRINGIFY(TOKEN_END), token->name);
    exit(1);
  }
  _ADVANCE_TOKEN(tokens, token);
  return ast_new_function_declaration_node(
    identifier,
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
  free(node);
}

struct IdentifierNode* ast_parse_identifier(struct Token** tokens) {
  LOG_DEBUG("Parsing Identifier");
  _CHECK_TOKENS();
  struct Token* token = *tokens;

  if (!ast_identifier_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected '%s' got '%s'", HELPERS_STRINGIFY(TOKEN_IDENTIFIER), token->name);
    exit(1);
  }

  size_t name_length = (strlen(token->name) + 1);
  char* name = malloc(sizeof(char) * name_length);
  memset(name, 0, sizeof(char) * name_length);
  _ADVANCE_TOKEN(tokens, token);
  return ast_new_identifier_node(name);
}

inline bool ast_identifier_token_matches_first_set(struct Token token) {
  UNUSED(token);
  return true;
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
  struct Token* token = *tokens;

  if (!ast_numeric_expression_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected number got '%s'", token->name);
    exit(1);
  }

  const int value = atoi(token->name);
  _ADVANCE_TOKEN(tokens, token);
  return ast_new_numeric_expression_node(value);
}

bool ast_numeric_expression_token_matches_first_set(struct Token token) {
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
  struct ParameterNode** parameters = node->parameters;
  for (size_t i = 0; i < node->length; i++) {
    ast_free_parameter_node(parameters[i]);
  }
  free(node->parameters);
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
  struct Token* token = *tokens;

  struct ParameterListNode* parameter_list = ast_new_parameter_list_node(NULL);
  if (!ast_parameter_list_token_matches_first_set(*token)) {
    LOG_ERROR("Expected '(' got '%s'", token->name);
    exit(1);
  }
  _ADVANCE_TOKEN(tokens, token);
  if (!token_is_close_paren(*token)) {
    LOG_ERROR("Expected ')' got '%s'", token->name);
    exit(1);
  }
  _ADVANCE_TOKEN(tokens, token);
  return parameter_list;
}

bool ast_parameter_list_token_matches_first_set(struct Token token) {
  return token_is_open_paren(token);
}

/*****************/
/* ParameterNode */
/*****************/
struct ParameterNode* ast_new_parameter_node(
  struct IdentifierNode* identifier,
  struct IdentifierNode* type
) {
  struct ParameterNode* node = malloc(sizeof(struct ParameterNode));
  node->kind = AstParameter;
  node->identifier = identifier;
  node->type = type;
  return node;
}

void ast_free_parameter_node(struct ParameterNode* node) {
  ast_free_identifier_node(node->identifier);
  ast_free_identifier_node(node->type);
  free(node);
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
  free(node);
}

struct ProgramNode* ast_parse_program(struct Token** tokens) {
  LOG_DEBUG("Parsing Program");
  _CHECK_TOKENS();
  struct Token* token = *tokens;

  if (!ast_program_token_matches_first_set(**tokens)) {
    LOG_ERROR("Expected '%s' got '%s'", HELPERS_STRINGIFY(TOKEN_FUN), token->name);
    exit(1);
  }
  return ast_new_program_node(ast_parse_declaration_list(tokens));  
  
  // struct Token* token = *tokens;
  // struct DeclarationListNode* declaration_list = ast_new_declaration_list_node(NULL);
  // ast_parse_declaration_list(declaration_list, &token);
  // program->declarations = ast_parse_declaration_list()
  // struct DeclarationListNode* declarations = program->declarations;
  // LOG_DEBUG("Parsing ProgramNode with token %s", token->name);
  
  // size_t function_name_length = token->length + 1;
  // char* function_name = malloc(sizeof(char) * function_name_length);
  // memset(function_name, '\0', function_name_length);
  // strncpy(function_name, token->name, function_name_length);
  // struct FunctionDeclarationNode* function = ast_new_function_declaration_node(
  //   ast_new_identifier_node(function_name),
  //   ast_new_parameter_list_node(NULL),
  //   ast_new_expression_list_node(NULL)
  // );
  
  // struct DeclarationNode* declaration = ast_new_declaration_node(
  //   AstFunctionDeclaration,
  //   (union DeclarationNodeUnion) {
  //     .function_declaration = function
  //   }
  // );
  // ast_add_declaration_node(declarations, declaration);
}

inline bool ast_program_token_matches_first_set(struct Token token) {
  return token_is_fun(token);
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
  free(node);
}

struct StringExpressionNode* ast_parse_string_expression(struct Token** tokens) {
  LOG_DEBUG("Parsing String Expression");
  _CHECK_TOKENS();
  struct Token* token = *tokens;

  if (!ast_string_expression_token_matches_first_set(*token)) {
    LOG_ERROR("Expected string got '%s'", token->name);
    exit(1);
  }
  const size_t token_length = token->length + 1;
  char* value = malloc(sizeof(char) * token_length);
  memset(value, '\0', token_length);
  strncpy(value, token->name, token_length);
  _ADVANCE_TOKEN(tokens, token);
  return ast_new_string_expression_node(value);
}

bool ast_string_expression_token_matches_first_set(struct Token token) {
  return token_is_string_literal(token);
}
