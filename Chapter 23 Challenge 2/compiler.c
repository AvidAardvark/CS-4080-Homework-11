int innermostLoopStart = -1;
int innermostLoopScopeDepth = 0;

static void forStatement() {
  beginScope();

  consume(TOKEN_LEFT_PAREN, "Expect '(' after 'for'.");
  if (match(TOKEN_VAR)) {
    varDeclaration();
  } else if (match(TOKEN_SEMICOLON)) {
  } else {
    expressionStatement();
  }

  int surroundingLoopStart = innermostLoopStart; 
  int surroundingLoopScopeDepth = innermostLoopScopeDepth; 
  innermostLoopStart = currentChunk()->count; 
  innermostLoopScopeDepth = current->scopeDepth; 

  int exitJump = -1;
  if (!match(TOKEN_SEMICOLON)) {
    expression();
    consume(TOKEN_SEMICOLON, "Expect ';' after loop condition.");

    exitJump = emitJump(OP_JUMP_IF_FALSE);
    emitByte(OP_POP); 
  }

  if (!match(TOKEN_RIGHT_PAREN)) {
    int bodyJump = emitJump(OP_JUMP);

    int incrementStart = currentChunk()->count;
    expression();
    emitByte(OP_POP);
    consume(TOKEN_RIGHT_PAREN, "Expect ')' after for clauses.");

    emitLoop(innermostLoopStart); 
    innermostLoopStart = incrementStart; 
    patchJump(bodyJump);
  }

  statement();

  emitLoop(innermostLoopStart); 

  if (exitJump != -1) {
    patchJump(exitJump);
    emitByte(OP_POP);
  }

  innermostLoopStart = surroundingLoopStart; 
  innermostLoopScopeDepth = surroundingLoopScopeDepth; 

  endScope();
}



static void continueStatement() {
  if (innermostLoopStart == -1) {
    error("Can't use 'continue' outside of a loop.");
  }

  consume(TOKEN_SEMICOLON, "Expect ';' after 'continue'.");

  for (int i = current->localCount - 1;
       i >= 0 && current->locals[i].depth > innermostLoopScopeDepth;
       i--) {
    emitByte(OP_POP);
  }

  emitLoop(innermostLoopStart);
}
