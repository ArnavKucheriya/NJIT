// Arnav Kucheriya - script_1.c

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(void){
    FILE *fp = fopen("matrix.bin","rb");
    if(!fp){ perror("matrix.bin"); return 1; }

    uint32_t n=0, m=0;
    if(fread(&n, sizeof(uint32_t), 1, fp)!=1 || fread(&m, sizeof(uint32_t), 1, fp)!=1){
        fprintf(stderr,"Failed to read dimensions\n"); fclose(fp); return 1;
    }
    if(n==0 || m==0 || n>1000 || m>1000){ fprintf(stderr,"Invalid dims: %u x %u\n", n, m); fclose(fp); return 1; }

    size_t total = (size_t)n * (size_t)m;
    uint32_t *A = (uint32_t*)malloc(total * sizeof(uint32_t));
    if(!A){ fprintf(stderr,"OOM\n"); fclose(fp); return 1; }
    if(fread(A, sizeof(uint32_t), total, fp)!=total){ fprintf(stderr,"Failed to read data\n"); free(A); fclose(fp); return 1; }
    fclose(fp);

    // Count non-zeros
    size_t nnz = 0;
    for(size_t i=0;i<total;i++) if(A[i]!=0) nnz++;

    uint32_t *values = nnz? (uint32_t*)malloc(nnz*sizeof(uint32_t)) : NULL;
    uint32_t *colidx = nnz? (uint32_t*)malloc(nnz*sizeof(uint32_t)) : NULL;
    size_t *rowstart  = (size_t*)malloc(((size_t)n+1)*sizeof(size_t));
    if((nnz && (!values || !colidx)) || !rowstart){
        fprintf(stderr,"OOM\n"); free(A); free(values); free(colidx); free(rowstart); return 1;
    }

    size_t k=0;
    for(uint32_t i=0;i<n;i++){
        rowstart[i] = k;
        for(uint32_t j=0;j<m;j++){
            uint32_t v = A[(size_t)i*m + j];
            if(v){ values[k]=v; colidx[k]=j; k++; }
        }
    }
    rowstart[n] = k;

    FILE *out = fopen("matrix.txt","w");
    if(!out){ perror("matrix.txt"); free(A); free(values); free(colidx); free(rowstart); return 1; }

    fprintf(out,"dimensions %u %u\n", n, m);

    fprintf(out,"values");
    for(size_t i=0;i<nnz;i++) fprintf(out," %u", values[i]);
    fputc('\n', out);

    fprintf(out,"column_indices");
    for(size_t i=0;i<nnz;i++) fprintf(out," %u", colidx[i]);
    fputc('\n', out);

    fprintf(out,"row_start");
    for(uint32_t i=0;i<=n;i++) fprintf(out," %zu", rowstart[i]);
    fputc('\n', out);

    fclose(out);
    free(A); free(values); free(colidx); free(rowstart);
    return 0;
}
