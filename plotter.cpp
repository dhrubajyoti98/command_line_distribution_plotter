#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<cstring>

int main(int argc, char* argv[])
{
    //argv[1]: Datafile Name with extension [COMPULSORY]
    //argv[2]: Output plot file name with extension [COMPULSORY]
    //argv[3]: bin width [COMPULSORY]
    //argv[4]: plot y label [COMPULSORY]
    //argv[5]: plot x label [COMPULSORY]
    //argv[6]: label sizes for both x-axis and y-axis. [COMPULSORY]
    //argv[7]: tick sizes for both x-axis and y-axis. [COMPULSORY]
    //argv[8]: number which denotes which coloumn to use. Enter numbers like 1,2,3....

    double binw=atof(argv[3]);
    int size=(int)atof(argv[6]);
    int tsize=(int)atof(argv[7]);
    int col=(int)atof(argv[8]);
    
    printf("ARGC=%d\n",argc);

    FILE *fp = fopen("tmp_plot.plt","w");

    fprintf(fp,"set term png\n");
    fprintf(fp,"set output \"%s\"\n",argv[2]);
    //fprintf(fp,"stats \"%s\"u %d\n",argv[1],col);
    //fprintf(fp,"sum=floor(STATS_records/1.)\n");
    fprintf(fp,"set key off\nset border 3\n");
    fprintf(fp,"set boxwidth %lf absolute\nset style fill solid 1.0 noborder\n",binw);
    fprintf(fp,"bin_width=%lf\n",binw);
    fprintf(fp,"set xlabel \"%s\" font \",%d\"\n",argv[5],size);
    fprintf(fp,"set ylabel \"%s\" font \",%d\"\n",argv[4],size);
    fprintf(fp,"set xtics font \",%d\"\n",tsize);
    fprintf(fp,"set ytics font \",%d\"\n",tsize);
    fprintf(fp,"set grid\n");
    fprintf(fp,"bin_number(x) = floor(x/bin_width)\n");
    fprintf(fp,"rounded(x) = bin_width * ( bin_number(x) + 0.5 )\n");

    fprintf(fp,"plot \"%s\" using (rounded($%d)):(%d) smooth frequency with boxes\n",argv[1],col,col); 

    //Will Implement Normalization Later.
    /*if(strcmp(argv[8], "nn") == 0)
    {
        fprintf(fp,"plot \"%s\" using (rounded($%d)):(%d) smooth frequency with boxes\n",argv[1],col,col); 
    }
    else
    {
        fprintf(fp,"plot \"%s\" using (rounded($%d)):(%d./(sum*bin_width)) smooth frequency with boxes\n",argv[1],col,col); 
    }*/


    fclose(fp);

    system("gnuplot tmp_plot.plt");
    system("rm tmp_plot.plt");
    
    return 0; 
}
