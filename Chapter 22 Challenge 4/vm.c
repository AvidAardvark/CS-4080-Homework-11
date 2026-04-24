#define READ_SLOT_LONG() \
    ((uint16_t)((READ_BYTE() << 8) | READ_BYTE()))

case OP_GET_LOCAL: {
    uint8_t slot = READ_BYTE();
    case OP_GET_LOCAL_LONG: {
        uint16_t slot = READ_SLOT_LONG();
        push(frame->slots[slot]);
        break;
}

case OP_SET_LOCAL: {
    uint8_t slot = READ_BYTE();
    case OP_SET_LOCAL_LONG: {
        uint16_t slot = READ_SLOT_LONG();
        frame->slots[slot] = peek(0);
        break;
}

#undef READ_SLOT_LONG
