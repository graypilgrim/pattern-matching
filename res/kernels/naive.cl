void kernel naive(global const char* document, global char* pattern, unsigned long patternLen, global char* result)
{
  int id = get_global_id(0);
  global char *documentPart = document + id;

  for (unsigned long k = 0; k < patternLen; ++k)
    if (*documentPart++ != *pattern++) return;

  result[id] = 1;
}
