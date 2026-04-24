static interpretResult run() {
  for (;;) {
    switch (instruction = READ_BYTE()) {
      case OP_DUP: 
        push(peek(0)); 
        break;
    }
  }
}
