#define LOCALS_MAX 65536
Local locals[LOCALS_MAX];

typedef struct Compiler {
    struct Compiler* enclosing;
    ObjFunction* function;
    FunctionType type;
    Local locals[LOCALS_MAX];
    int localCount;
    Upvalue upvalues[UPVALUE_COUNT];
    int scopeDepth;
} Compiler;

static void addLocal(Token name) {
    if (current->localCount == LOCALS_MAX) {
        error("Too many local variables in function.");
        return;
    }
    Local* local = &current->locals[current->localCount++];
    local->name = name;
    local->depth = -1;
    local->isCaptured = false;
}

static void emitShort(int16_t value) {
    emitByte((value >> 8) & 0xff);
    emitByte(value & 0xff);
}

static void emitLocalInstruction(uint8_t shortOp,
                                  uint8_t longOp,
                                  int slot) {
    if (slot <= UINT8_MAX) {
        emitBytes(shortOp, (uint8_t)slot);
    } else if (slot <= UINT16_MAX) {
        emitByte(longOp);
        emitShort((int16_t)slot);
    } else {
        error("Too many local variables in function.");
    }
}

static void namedVariable(Token name, bool canAssign) {
    int arg = resolveLocal(current, &name);

    if (canAssign && match(TOKEN_EQUAL)) {
        expression();

        if (arg != -1) {
            emitLocalInstruction(OP_SET_LOCAL, OP_SET_LOCAL_LONG, arg);
        } else if ((arg = resolveUpvalue(current, &name)) != -1) {
            emitBytes(OP_SET_UPVALUE, (uint8_t)arg);
        } else {
            arg = identifierConstant(&name);
            emitBytes(OP_SET_GLOBAL, (uint8_t)arg);
        }
    } else {
        if (arg != -1) {
            emitLocalInstruction(OP_GET_LOCAL, OP_GET_LOCAL_LONG, arg);
        } else if ((arg = resolveUpvalue(current, &name)) != -1) {
            emitBytes(OP_GET_UPVALUE, (uint8_t)arg);
        } else {
            arg = identifierConstant(&name);
            emitBytes(OP_GET_GLOBAL, (uint8_t)arg);
        }
    }
}

emitBytes(get0P, (uint8_t)arg);

typedef struct {
    Token name;
    int depth;
    bool isCaptured;
} Local;

if (current->localCount == LOCALS_MAX) {
    error("Too many local variables in function.");
    return;
}

