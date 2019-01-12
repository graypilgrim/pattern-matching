unsigned long hash(global const char* str, unsigned long len) {
  unsigned long res = 0;
  for (unsigned long i = 0; i < len; ++i) {
    res += *str++;
    res += res << 10;
    res ^= res >> 6;
  }
  res += res << 3;
  res ^= res >> 11;
  res += res << 15;
  return res;
}

void kernel winnowing(global const char* document, unsigned long patternHash, unsigned long patternLen, global char* result)
{
  int id = get_global_id(0);
  global char *documentPart = document + id;

  if (hash(documentPart, patternLen) == patternHash)
    result[id] = 1;
}
