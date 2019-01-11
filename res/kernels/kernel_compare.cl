void kernel compare(global const char* A, global char* B, global char* C)
{
  /*
  if (A[get_global_id(0)] == B[get_global_id(0)])
    C[get_global_id(0)] = 1;
  else
    C[get_global_id(0)] = 0;*/
  int id = get_global_id(0);
  if (A[id] != B[id])
    C[0] &= 0;
}
