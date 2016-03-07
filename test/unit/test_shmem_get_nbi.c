/*
 *
 * Copyright (c) 2011 - 2015
 *   University of Houston System and UT-Battelle, LLC.
 * Copyright (c) 2009 - 2015
 *   Silicon Graphics International Corp.  SHMEM is copyrighted
 *   by Silicon Graphics International Corp. (SGI) The OpenSHMEM API
 *   (shmem) is released by Open Source Software Solutions, Inc., under an
 *   agreement with Silicon Graphics International Corp. (SGI).
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * o Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 *
 * o Neither the name of the University of Houston System, UT-Battelle, LLC
 *   nor the names of its contributors may be used to endorse or promote
 *   products derived from this software without specific prior written
 *   permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */


/*
 * Calls tested
 * shmem_short_get_nbi, shmem_int_get_nbi, shmem_long_get_nbi,
 * shmem_longdouble_get_nbi, shmem_longlong_get_nbi, shmem_double_get_nbi,
 * shmem_float_get_nbi, shmem_getmem_nbi, shmem_char_get_nbi,
 * shmem_get8_nbi, shmem_get16_nbi, shmem_get32_nbi,
 * shmem_get64_nbi, shmem_get128_nbi
 *
 *
 * All PEs get an array from right neighbor
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include <shmem.h>

#define N 7

int
main (int argc, char **argv)
{
    int i;
    int nextpe;
    int me, npes;
    int success1, success2, success3, success4, success5, success6, success7,
        success8, success9, success10, success11;

    short dest1[N];
    int dest2[N];
    long dest3[N];
    long double dest4[N];
    long long dest5[N];
    double dest6[N];
    float dest7[N];
    char *dest8;
    char dest9[N];
    int8_t dest10[N];
    int16_t dest11[N];

    short *src1;
    int *src2;
    long *src3;
    long double *src4;
    long long *src5;
    double *src6;
    float *src7;
    char *src8;
    char *src9;
    int8_t *src10;
    int16_t *src11;

    int fail_count = 0;

    shmem_init ();
    me = shmem_my_pe ();
    npes = shmem_n_pes ();

    if (npes > 1) {

        success1 = 0;
        success2 = 0;
        success3 = 0;
        success4 = 0;
        success5 = 0;
        success6 = 0;
        success7 = 0;
        success8 = 0;
	success9 = 0;
        dest8 = (char *) malloc (N * sizeof (char));

        for (i = 0; i < N; i += 1) {
            dest1[i] = -9;
            dest2[i] = -9;
            dest3[i] = -9;
            dest4[i] = -9;
            dest5[i] = -9;
            dest6[i] = -9;
            dest7[i] = -9.0;
            dest8[i] = -9;
	    dest9[i] = -9;
        }

        src1 = (short *) shmem_malloc (N * sizeof (*src1));
        src2 = (int *) shmem_malloc (N * sizeof (*src2));
        src3 = (long *) shmem_malloc (N * sizeof (*src3));
        src4 = (long double *) shmem_malloc (N * sizeof (*src4));
        src5 = (long long *) shmem_malloc (N * sizeof (*src5));
        src6 = (double *) shmem_malloc (N * sizeof (*src6));
        src7 = (float *) shmem_malloc (N * sizeof (*src7));
        src8 = (char *) shmem_malloc (4 * sizeof (*src8));
	src9 = (char *) shmem_malloc (N * sizeof (*src9));
	src10 = (int8_t *) shmem_malloc (N * sizeof (*src10));
	src11 = (int16_t *) shmem_malloc (N * sizeof (*src11));

        for (i = 0; i < N; i += 1) {
            src1[i] = (short) me;
            src2[i] = me;
            src3[i] = (long) me;
            src4[i] = (long double) me;
            src5[i] = (long long) me;
            src6[i] = (double) me;
            src7[i] = (float) me;
            src8[i] = (char) me;
	    src9[i] = (char) me;
	    src10[i] = (int8_t) me;
	    src11[i] = (int8_t) me;
        }

        nextpe = (me + 1) % npes;

        /* Testing shmem_short_get_nbi, shmem_short_get_nbi, shmem_int_get_nbi,
           shmem_long_get_nbi, shmem_longdouble_get_nbi, shmem_longlong_get_nbi,
           shmem_double_get_nbi, shmem_float_get_nbi, shmem_getmem_nbi,
           shmem_char_get_nbi */
        shmem_barrier_all ();

        shmem_short_get_nbi (dest1, src1, N, nextpe);
        shmem_int_get_nbi (dest2, src2, N, nextpe);
        shmem_long_get_nbi (dest3, src3, N, nextpe);
        shmem_longdouble_get_nbi (dest4, src4, N, nextpe);
        shmem_longlong_get_nbi (dest5, src5, N, nextpe);
        shmem_double_get_nbi (dest6, src6, N, nextpe);
        shmem_float_get_nbi (dest7, src7, N, nextpe);
        shmem_getmem_nbi (dest8, src8, N * sizeof (char), nextpe);
	shmem_char_get_nbi (dest9, src9, N, nextpe);

        shmem_barrier_all ();

        if (me == 0) {
            for (i = 0; i < N; i += 1) {
                if (dest1[i] != (1)) {
                    success1 = 1;
                }
                if (dest2[i] != (1)) {
                    success2 = 1;
                }
                if (dest3[i] != (1)) {
                    success3 = 1;
                }
                if (dest4[i] != (1)) {
                    success4 = 1;
                }
                if (dest5[i] != (1)) {
                    success5 = 1;
                }
                if (dest6[i] != (1)) {
                    success6 = 1;
                }
                if (dest7[i] != (1)) {
                    success7 = 1;
                }
                if (dest8[i] != (1)) {
                    success8 = 1;
                }
		if (dest9[i] != (1)) {
		    success9 = 1;
		}
            }

            if (success1 == 0)
                printf ("Test shmem_short_get_nbi: Passed\n");
            else {
                printf ("Test shmem_short_get_nbi: Failed\n");
		fail_count++;
	    }
            if (success2 == 0)
                printf ("Test shmem_int_get_nbi: Passed\n");
            else {
                printf ("Test shmem_int_get_nbi: Failed\n");
		fail_count++;
	    }
            if (success3 == 0)
                printf ("Test shmem_long_get_nbi: Passed\n");
            else {
                printf ("Test shmem_long_get_nbi: Failed\n");
		fail_count++;
	    }
            if (success4 == 0)
                printf ("Test shmem_longdouble_get_nbi: Passed\n");
            else {
                printf ("Test shmem_longdouble_get_nbi: Failed\n");
		fail_count++;
	    }
            if (success5 == 0)
                printf ("Test shmem_longlong_get_nbi: Passed\n");
            else {
                printf ("Test shmem_longlong_get_nbi: Failed\n");
		fail_count++;
	    }
            if (success6 == 0)
                printf ("Test shmem_double_get_nbi: Passed\n");
            else {
                printf ("Test shmem_double_get_nbi: Failed\n");
		fail_count++;
	    }
            if (success7 == 0)
                printf ("Test shmem_float_get_nbi: Passed\n");
            else {
                printf ("Test shmem_float_get_nbi: Failed\n");
		fail_count++;
	    }
            if (success8 == 0)
                printf ("Test shmem_getmem_nbi: Passed\n");
            else {
                printf ("Test shmem_getmem_nbi: Failed\n");
		fail_count++;
	    }
	    if (success9 == 0)
	        printf ("Test shmem_char_get_nbi: Passed\n");
	    else {
	        printf("Test shmem_char_get_nbi: Failed\n");
	        fail_count++;
	    }

        }
        shmem_barrier_all ();

        /* Testing shmem_get8_nbi, shmem_get16_nbi, shmem_get32_nbi,
           shmem_get64_nbi, shmem_get128_nbi */
        if (sizeof (int) == 4) {
            for (i = 0; i < N; i += 1) {
	        dest10[i] = -9;
	        dest1[i] = -9;
                dest2[i] = -9;
                dest3[i] = -9;
                dest4[i] = -9;
            }
	    success10 = 0;
	    success1 = 0;
            success2 = 0;
            success3 = 0;
            success4 = 0;

            shmem_barrier_all ();

	    shmem_get8_nbi (dest10, src10, N, nextpe);
	    shmem_get16_nbi (dest1, src1, N, nextpe);
            shmem_get32_nbi (dest2, src2, N, nextpe);
            shmem_get64_nbi (dest3, src3, N, nextpe);
            shmem_get128_nbi (dest4, src4, N, nextpe);

            shmem_barrier_all ();

            if (me == 0) {
                for (i = 0; i < N; i += 1) {
		    if (dest10[i] != (1)) {
		        success10 = 1;
		    }
		    if (dest1[i] != (1)) {
		        success11 = 1;
		    }
                    if (dest2[i] != (1)) {
                        success2 = 1;
                    }
                    if (dest3[i] != (1)) {
                        success3 = 1;
                    }
                    if (dest4[i] != (1)) {
                        success4 = 1;
                    }
                }
		if (success10 == 0)
		    printf ("Test shmem_get8_nbi: Passed\n");
		else {
		    printf ("Test shmem_get8_nbi: Failed\n");
		    fail_count++;
		}

		if (success1 == 0)
		    printf ("Test shmem_get16_nbi: Passed\n");
		else {
		    printf ("Test shmem_get16_nbi: Failed\n");
		    fail_count++;
		}

                if (success2 == 0)
                    printf ("Test shmem_get32_nbi: Passed\n");
                else {
                    printf ("Test shmem_get32_nbi: Failed\n");
		    fail_count++;
		}

                if (success3 == 0)
                    printf ("Test shmem_get64_nbi: Passed\n");
                else {
                    printf ("Test shmem_get64_nbi: Failed\n");
		    fail_count++;
		}

                if (success4 == 0)
                    printf ("Test shmem_get128_nbi: Passed\n");
                else {
                    printf ("Test shmem_get128_nbi: Failed\n");
		    fail_count++;
		}
            }
        }
        else if (sizeof (int) == 8) {
            for (i = 0; i < N; i += 1) {
	        dest10[i] = -9;
	        dest11[i] = -9;
                dest1[i] = -9;
                dest2[i] = -9;
                dest3[i] = -9;
            }
	    success10 = 0;
	    success11 = 0;
            success1 = 0;
            success2 = 0;
            success3 = 0;

            shmem_barrier_all ();

	    shmem_get8_nbi (dest10, src10, N, nextpe);
	    shmem_get16_nbi (dest11, src11, N, nextpe);
            shmem_get32_nbi (dest1, src1, N, nextpe);
            shmem_get64_nbi (dest2, src2, N, nextpe);
            shmem_get128_nbi (dest3, src3, N, nextpe);

            shmem_barrier_all ();

            if (me == 0) {
                for (i = 0; i < N; i += 1) {
		    if (dest10[i] != (1)) {
		        success10 = 1;
		    }
		    if (dest11[i] != (1)) {
		        success11 = 1;
		    }
                    if (dest1[i] != (1)) {
                        success1 = 1;
                    }
                    if (dest2[i] != (1)) {
                        success2 = 1;
                    }
                    if (dest3[i] != (1)) {
                        success3 = 1;
                    }

                }
		if (success10 == 0)
		    printf ("Test shmem_get8_nbi: Passed\n");
		else {
		    printf ("Test shmem_get8_nbi: Failed\n");
		    fail_count++;
		}

		if (success11 == 0)
		    printf ("Test shmem_get16_nbi: Passed\n");
		else {
		    printf ("Test shmem_get16_nbi: Failed\n");
		    fail_count++;
		}

                if (success1 == 0)
                    printf ("Test shmem_get32_nbi: Passed\n");
                else {
                    printf ("Test shmem_get32_nbi: Failed\n");
		    fail_count++;
		}

                if (success2 == 0)
                    printf ("Test shmem_get64_nbi: Passed\n");
                else {
                    printf ("Test shmem_get64_nbi: Failed\n");
		    fail_count++;
		}

                if (success3 == 0)
                    printf ("Test shmem_get128_nbi: Passed\n");
                else {
                    printf ("Test shmem_get128_nbi: Failed\n");
		    fail_count++;
		}
            }
        }

        shmem_barrier_all ();

	if (me == 0) {
	  if (fail_count == 0)
              printf("All Tests Passed\n");
	  else
	      printf("%d Tests Failed\n", fail_count);
        }

        shmem_free (src1);
        shmem_free (src2);
        shmem_free (src3);
        shmem_free (src4);
        shmem_free (src5);
        shmem_free (src6);
        shmem_free (src7);
        shmem_free (src8);
	shmem_free (src9);
	shmem_free (src10);
	shmem_free (src11);
    }
    else {
        printf ("Number of PEs must be > 1 to test shmem get, test skipped\n");
    }

    shmem_finalize ();

    return 0;
}
