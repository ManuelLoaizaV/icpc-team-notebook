Long GetBit(Long mask, Long bit) { return (mask >> bit) & 1LL; }
void TurnOn(Long& mask, Long bit) { mask = mask | (1LL << bit); }
void TurnOff(Long& mask, Long bit) { mask = mask & (~(1 << bit)); }
