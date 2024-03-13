#include <op_cuda_rt_support.h>

op_dat op_decl_dat_char_soa(op_set set, int dim, char const *type, int size,
                        char *data, char const *name)
{
  op_dat dat = op_decl_dat_core(set, dim, type, size, data, name);
  int diffadrr[8] = {0, 640, 960, 1280, 1920, 1928, 1932, 1936};
  int datalen[8] = {80, 40, 40, 80, 1, 1, 1, 4};
  int typelen[8] = {8, 8, 8, 8, 8, 4, 4, 8};

  char *out = (char *)malloc(dat->size * set->size * sizeof(char));

  // transpose data
  int L = 1968;
  int n = 64512;
  for (int ii = 0; ii < 8; ii++)
  {
    for (int i = 0; i < datalen[ii]; i++)
    {
      for (int j = 0; j < n; j++)
      {
        for (int k = 0; k < typelen[ii]; k++)
        {
          out[diffadrr[ii] * n + i * typelen[ii] * n + j * typelen[ii] + k] =
              data[j * L + diffadrr[ii] + i * typelen[ii] + k];
        }
      }
    }
  }
  op_cpHostToDevice((void **)&(dat->data_d), (void **)&(out),
                    dat->size * set->size);
  return dat;
}
