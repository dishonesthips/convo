/**
 * @brief: convolves a matrix of a given size with a cosntant filter 
 * To execute: ./<executable> <rows> <columns>
 * EXAMPLE: ./convo 10 10
 */

#include <unistd.h>
#include <stdio.h>  
#include <stdlib.h>
#include <sys/time.h>

#define K_LEN 3
#define K_WIDTH 1
#define K_DEF {-1, 0 , 1}

void print_uchar_matrix(int rows, int cols, unsigned char mat[rows][cols]);
void print_short_matrix(int rows, int cols, short mat[rows][cols]);
void convolve_K(int rows, int cols, unsigned char source[rows][cols], short out[rows][cols], char dirn);

const int K[K_LEN] = K_DEF;

int main(int argc, char ** argv) 
{
    // INPUT CHECKING /////////////////////////////////////////////////////////////
    if (argc != 3){
        fprintf(stderr, "Usage: %s <pos int rows> <pos int cols>\n", argv[0]);
        exit(1);
    }

    int rows = atoi(argv[1]);
    int cols = atoi(argv[2]);

    // CREATE & POPULATE M ////////////////////////////////////////////////////////
    unsigned char M[rows][cols];
    short Dx[rows][cols];
    short Dy[rows][cols];

    srand((unsigned int) time(0));

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            M[i][j] = rand();
        }
    }

    // INIT TIMER /////////////////////////////////////////////////////////////////
    double times[2];
    struct timeval tv;

    if (gettimeofday(&tv, NULL) != 0) {
        perror("gettimeofday");
        abort();
    }
    times[0] = (tv.tv_sec) + tv.tv_usec/1000000.;

    // COMPUTE ////////////////////////////////////////////////////////////////////
    convolve_K(rows, cols, M, Dx, 'H');
    convolve_K(rows, cols, M, Dy, 'V');

    // END TIMER //////////////////////////////////////////////////////////////////
    if (gettimeofday(&tv, NULL) != 0) {
        perror("gettimeofday");
        abort();
    }
    times[1] = (tv.tv_sec) + tv.tv_usec/1000000.;
    printf("computing Dx and Dy execution time: %.10lf seconds\n",  times[1] - times[0]);

    // DBG STATEMENTS ////////////////////////////////////////////////////////////
    #ifdef DEBUG
        printf("M\n");
        print_uchar_matrix( rows, cols, M );

        printf("Dx\n");
        print_short_matrix( rows, cols, Dx );

        printf("Dy\n");
        print_short_matrix( rows, cols, Dy );
    #endif

    return 0;
}

void convolve_K(int rows, int cols, unsigned char source[rows][cols], short out[rows][cols], char dirn){
    int sum;
    int mod_ind;
    int mod;
    // upper bound for selection index depends on direction of convolution
    int bound = (dirn == 'H') ? cols : rows;

    // iterate over source with i and j
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            sum = 0;
            // the direction in which we adjust based on the filter
            // depends on if we're going vertical or horizontal
            mod_ind = (dirn == 'H') ? j : i;

            // k+=2 being a hard coded optimization since 
            // the middle element of the filter is 0 
            for (int k = -K_WIDTH; k <= K_WIDTH; k+=2){ 
                int pick = mod_ind + k;

                if (pick < 0) pick = 0;
                if (pick >= bound) pick = bound-1;

                mod = (dirn == 'H') ? source[i][pick] : source[pick][j] ;

                sum += mod * K[k + K_WIDTH];

                // #ifdef DEBUG1
                //     printf("%d + ", mod * K[k + K_WIDTH]);
                // #endif
            }
            out[i][j] = sum;

            // #ifdef DEBUG1
            //     printf(" = %d\n", sum);
            // #endif
        }
    }

}

void print_uchar_matrix(int rows, int cols, unsigned char mat[rows][cols]){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            printf("%d\t", mat[i][j]);
        }
        printf("\n");
    }
}

void print_short_matrix(int rows, int cols, short mat[rows][cols]){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            printf("%d\t", mat[i][j]);
        }
        printf("\n");
    }
}
