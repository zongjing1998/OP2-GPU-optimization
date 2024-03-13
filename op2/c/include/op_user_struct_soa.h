#ifndef __OP_USER_STRUCT_SOA_H
#define __OP_USER_STRUCT_SOA_H

op_dat op_decl_dat_char_soa(op_set set, int dim, char const *type, int size,
                        char *data, char const *name);

template <class T>
op_dat op_decl_dat_soa(op_set set, int dim, char const *type, T *data,
                   char const *name)
{

  if (type_error(data, type))
  {
    printf("incorrect type specified for dataset \"%s\" \n", name);
    exit(1);
  }

  return op_decl_dat_char_soa(set, dim, type, sizeof(T), (char *)data, name);
}

#endif