#include <shmem.h>
#include <string.h>
#include <stdio.h>

int
main(int argc, char* argv[])
{
    long source[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    long *target;
    int *flag;

    shmem_init();

    if (shmem_n_pes() == 1) {
        printf("%s: Requires number of PEs > 1\n", argv[0]);
        shmem_finalize();
        return 0;
    }

    target = (long*) shmem_malloc(sizeof(long) * 10);
    flag = (int*) shmem_malloc(sizeof(int));
    flag[0] = 0;

    shmem_barrier_all();

    if (shmem_my_pe() == 0) {
        /* put 10 elements into target on PE 1 */
        shmem_long_put_nbi(target, source, 10, 1);
	shmem_quiet();
	shmem_int_inc(&flag[0], 1);
    }

    if (shmem_my_pe() == 1) {
      shmem_int_wait_until(&flag[0], SHMEM_CMP_EQ, 1);

        if (0 != memcmp(source, target, sizeof(long) * 10)) {
            int i;
            fprintf(stderr,"[%d] Src & Target mismatch?\n",shmem_my_pe());
            for (i = 0 ; i < 10 ; ++i) {
                printf("%ld,%ld ", source[i], target[i]);
            }
            printf("\n");
            shmem_global_exit(1);
        }
    }

    shmem_free(target);
    shmem_free(flag);

    shmem_finalize();

    return 0;
}
