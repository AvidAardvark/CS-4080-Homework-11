if (match(TOKEN_VAR)) {
    varDeclaration(false);
} else if (match(TOKEN_CONST)) {
    varDeclaration(true);
} else {
    statement();
}

static void declareVariable(bool isConst) {
  
}

typedef struct {
    Token name;
    int depth;
    bool isConst;
} Local;

if (match(TOKEN_EQUAL)) {
    expression();
} else {
    if (isConst) {
      error("Const variables must be initialized.");
    }
    emitByte(0P_NIL);
}

static bool isConstGlobal(Token* name);

if (canAssign && match(TOKEN_EQUAL)) {
    if (arg != -1) {
        if (current->locals[arg].isConst) {
            error("Can't assign to const variable.");
            expression();
            return;
        }
    } else {
        if (isConstGlobal(&name)) {
            error("Can't assign to const variable.");
            expression();
            return;
        }
    }
}
