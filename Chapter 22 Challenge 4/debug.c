static int shortInstruction(const char* name, Chunk* chunk,
                             int offset) {
    uint16_t slot = (uint16_t)(chunk->code[offset + 1] << 8);
    slot |= chunk->code[offset + 2];
    printf("%-16s %4d\n", name, slot);
    return offset + 3;
}

case OP_GET_LOCAL:
    return byteInstruction("OP_GET_LOCAL", chunk, offset);
case OP_SET_LOCAL:
    return byteInstruction("OP_SET_LOCAL", chunk, offset);
case OP_GET_LOCAL_LONG:
    return shortInstruction("OP_GET_LOCAL_LONG", chunk, offset);
case OP_SET_LOCAL_LONG:
    return shortInstruction("OP_SET_LOCAL_LONG", chunk, offset);
