#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "functions.h"
#define MAXINDIVIDUAL 1500
#define CMAX 10000
#define NORMPATHLENGTH 115100
#define MUTATE 0.8
#define ELITENUM 5

/*** ランダムにノードの座標を生成する関数 ***/
void random_location( int n, Location loc[] ) {
  srand((unsigned)time(NULL));
  int i;
  for(i=0; i<n; i++ ) {
    /* 作成する */
    loc[i].x=(double)rand()/RAND_MAX;
    loc[i].y=(double)rand()/RAND_MAX;
 }
}

/*** 経路順を表示する関数 ***/
double show_path( int p[], double d[N][N], Location city[], int n ) {
  int t;
  double sum=0.0;
   /* 作成する */
   /*
   ｐ[]は訪問順配列
   d[N][N]は経路長
   nはノード数
   */
  for(t=0; t<n-1; t++){
    printf(" %d →",p[t]);
    sum += d[t][t+1];
  }
  printf(" %d→",p[n-1]);
  printf("\n");
  return sum;
}

/*** 訪問チェック関数 ***/
int is_in_path( int p[], int s, int n ) {
  int t, r=0;
  for(t=0; t<n; t++ ){
     /* 作成する */
    if(s==p[t])r=1;
  }
  return r;
}

/*** 近傍法 ***/
double solve_neighborhoods(int p[], double d[N][N], int n) {
  double sum=0.0, min;
  int i,j,k;
  p[0]=0;
  for( i=0; i<n-1; i++ ) {
    min=d[0][0];
    for( j=1; j<n; j++ ){
      if ( ! is_in_path(p, j, i) )
	if ( min > d[p[i]][j] ) {
	  min = d[p[i]][j];
	  k=j;
	}
    }
    sum += d[p[i]][k];
    p[i+1]=k;
  }
  sum += d[p[n-1]][0];
  return sum;
}

/*ここから*/

/*Individual[MAXINDIVIDUAL][N]の中で、行ごとに上からnumOfIndividuals行、
0~size-1を被りなくランダムに敷き詰める関数(clear)*/
void InitializeIndividuals(int array[MAXINDIVIDUAL][N],int size,int numOfIndividuals){
    for(int i=0;i<numOfIndividuals;i++){
        for(int j=0;j<size;j++){
            array[i][j]=j;
        }
        int tmp;
        int tmpLocate;
        int last=size-1;
        while(last>0){
            tmpLocate=rand()%(last+1);
            tmp=array[i][tmpLocate];
            array[i][tmpLocate]=array[i][last];
            array[i][last]=tmp;
            last--;
        }
    }
}

/*Individual配列(実践の中で確認)*/
void calcTotalroute(const int Individual[][N],const double d[][N],int size,int NumOfIndividual,double totalPath[]){
  double sum;
  for(int i=0;i<NumOfIndividual;i++){
    sum=0;
    for(int j=0;j<size-1;j++){
      sum+=d[Individual[i][j]][Individual[i][j+1]];
    }
    sum+=d[Individual[i][0]][Individual[i][size-1]];

    totalPath[i]=sum;
  }
}

/*totalPathから適応度を計算し、Fitnessに代入する(clear)*/
void calcFitness(const double totalPath[],int size,double Fitness[]){
  for(int k=0;k<size;k++){
    Fitness[k]=totalPath[k];
  }
}

//*suffixをArrayの降順に変える(clear)*//
void sortSuffix(double Fitness[],int Suffix[],int len){
  int i,j,stmp;
  double tmp;
  for (i=0; i<len; ++i) {
    for (j=i+1; j<len; ++j) {
      if (Fitness[i] > Fitness[j]) {
        tmp =  Fitness[i];
        stmp = Suffix[i];

        Fitness[i] = Fitness[j];
        Suffix[i]=Suffix[j];

        Fitness[j] = tmp;
        Suffix[j]=stmp;
      }
    }
  }
}

/*要素数sizeの配列を逆転させる(clear)*/
void reverseArray(int Array[],int size){
  int count = size/2;
  int tmp;
  for(int k=0;k<count;k++){
    tmp=Array[size-k-1];
    Array[size-k-1]=Array[k];
    Array[k]=tmp;
  }
}
/*要素数sizeの配列のうち
startReverseからendReverseまでの一部分を逆転させる(clear)*/
void reverseArrayPart(int Array[],int size,int startReverse,
int endReverse){
  int tmp[2*N];
  if(startReverse<endReverse){
    for(int k=0;k<endReverse-startReverse+1;k++){
      tmp[k]=Array[k+startReverse];
    }
    reverseArray(tmp,endReverse-startReverse+1);
    for(int k=0;k<endReverse-startReverse+1;k++){
      Array[k+startReverse]=tmp[k];
    }
  }else if(endReverse<startReverse){
    for(int k=0;k<size-startReverse;k++){
      tmp[k]=Array[startReverse+k];
    }
    for(int k=0;k<endReverse+1;k++){
      tmp[size-startReverse+k]=Array[k];
    }
    reverseArray(tmp,size-startReverse+endReverse+1);

    for(int k=0;k<size-startReverse;k++){
      Array[startReverse+k]=tmp[k];
    }
    for(int k=0;k<endReverse+1;k++){
      Array[k]=tmp[size-startReverse+k];
    }
  }

}
/*染色体はsize個のマクロ遺伝子(size個のノード)を持つとする。
この染色体の遺伝子座i,jのマクロ遺伝子
の間にある全ての遺伝子を逆順にする。(clear)*/
void reverseChromosomePart(int Chmosome[],int i,int j,int size){
  int startReverse,endReverse;
  int endOfChromosomeSuffix=2*size-1;

  startReverse=2*i+2;
  endReverse=2*j-1;
  if(i==size-1)startReverse=0;
  if(j==0)endReverse=2*size-1; 
  reverseArrayPart(Chmosome,2*size,startReverse,endReverse);
}

//デバッグ用関数
void observeIntArray(const int Array[],int size){
  printf("[DEBUG]");
  for(int i=0;i<size;i++){
    printf("%d ",Array[i]);
  }
  printf("\n");
}
void observeDoubleArray(const double Array[],int size){
  printf("[DEBUG]");
  for(int i=0;i<size;i++){
    printf("%lf ",Array[i]);
  }
  printf("\n");
}


/*経路を染色体に符号化する(clear)*/
void encodeChromosome(int Path[],int Chromosome[],int size){
  Chromosome[0]=Path[0];
  Chromosome[(2*size)-1]=Path[0];
  for(int k=0;k<size-1;k++){
    Chromosome[2*k+1]=Path[k+1];
    Chromosome[2*k+2]=Path[k+1];
  }
}
/*染色体を経路に復号化する(clear)*/
void decodeChromosome(int Path[],int Chmosome[],int size){
    for(int k=0;k<size;k++){
        Path[k]=Chmosome[2*k];
    }
}
/*子供を枝交換交叉で作る　node数n(clear)
*/
int createChild(int Father[],int Mother[],int Child[],int size)
{
  int i1,i2,j1,j2;
  int i1secondCodon,i2secondCodon;
  int i1firstCodon,i2firstCodon;
  int FatherChromosome[2*N];
  int MotherChromosome[2*N];
  int tmp1,tmp2;
  
  //経路を染色体に符号化
  encodeChromosome(Father,FatherChromosome,size);
  encodeChromosome(Mother,MotherChromosome,size);
  //父親の遺伝子座i1をランダムに決定
  i1=rand()%size;
  //i1の第一コドンに対応する母親の遺伝子座i2を決定
  for(int k=0;k<size;k++){
    if(Mother[k]==Father[i1]){
      i2=k;
      break;
    }
  }

  while(1){
    //i1のコドンを決定
    i1firstCodon=FatherChromosome[2*i1];  
    i1secondCodon=FatherChromosome[2*i1+1];  
    i2firstCodon=MotherChromosome[2*i2];
    i2secondCodon=MotherChromosome[2*i2+1];

    //i1,i2の第二コドンと同じ第一コドンをもつ遺伝子座j2,j1を決定
    for(int k=0;k<size;k++){
      if(MotherChromosome[2*k]==i1secondCodon){
        j2=k;
        break;
      }
    }
    for(int k=0;k<size;k++){
      if(FatherChromosome[2*k]==i2secondCodon){
        j1=k;
        break;
      }
    }

    //遺伝子座i1,i2のマクロ遺伝子を交換
    FatherChromosome[2*i1]=i2firstCodon;
    FatherChromosome[2*i1+1]=i2secondCodon;
    MotherChromosome[2*i2]=i1firstCodon;
    MotherChromosome[2*i2+1]=i1secondCodon;

    if(i1secondCodon==i2secondCodon)break;

    //遺伝子座i1,j1間にあるマクロ遺伝子の訪問順序を逆にする
    reverseChromosomePart(FatherChromosome,i1,j1,size);
    //遺伝子座i2,j2間にあるマクロ遺伝子の訪問順序を逆にする
    reverseChromosomePart(MotherChromosome,i2,j2,size);

    i1=j1;
    i2=j2;
  }
  decodeChromosome(Father,FatherChromosome,size);
  decodeChromosome(Mother,MotherChromosome,size);

  for(int k=0;k<size;k++){
    Child[k]=Father[k];
  }
}

/*突然変異*/
void mutation(int Individual[],int size){
  int i,j;
  do{
    i=rand()%size;
    j=rand()%size;
  }while(i==j);
  reverseArrayPart(Individual,size,i,j);
}
//*遺伝的アルゴリズム(GA) ある程度以上の最適化に弱い*//
double solve_geneticAlgorithm(int p[],double d[N][N],int n)
{
  int generationNum=10000000;//世代の数
  int eliteNum=ELITENUM;//親の数
  int numOfIndivisuals=MAXINDIVIDUAL;//世代の個体の数
  double normPathLength=NORMPATHLENGTH;
  double percentOfMutation=MUTATE;
  int Individual[MAXINDIVIDUAL][N];//個体の経路を記録
  int newIndividual[MAXINDIVIDUAL][N];//子世代の個体の経路を記録
  double Fitness[MAXINDIVIDUAL],totalPath[MAXINDIVIDUAL];//個体ごとの適応度、総経路を記録
  int suffixOfFitness[MAXINDIVIDUAL];//tatalPathに付けられた添字で、今何番目かを記録
  int MotherRank,FatherRank;//親となる個体の順位
  int Mother[N],Father[N],Child[N];//親と子の経路
  double bestPathLength=100000000;


  //初期化
  InitializeIndividuals(Individual,n,numOfIndivisuals);
  for(int k=0;k<numOfIndivisuals;k++)
    totalPath[k]=bestPathLength;

  for(int g=0;g<generationNum;g++){
  //合計、適応度の計算
  calcTotalroute(Individual,d,n,numOfIndivisuals,totalPath);
  calcFitness(totalPath,numOfIndivisuals,Fitness);
  //添字の初期化
  for(int i=0;i<numOfIndivisuals;i++){
    suffixOfFitness[i]=i;
  }

  //添字をソート
  sortSuffix(Fitness,suffixOfFitness,numOfIndivisuals);
 
  //現世代での最高適応度の個体を記録  
  printf("generation:%d :%lf\n",g,totalPath[suffixOfFitness[0]]);
  if(totalPath[suffixOfFitness[0]]<bestPathLength){
    bestPathLength=totalPath[suffixOfFitness[0]];
  for(int i=0;i<n;i++){
    p[i]=Individual[suffixOfFitness[0]][i];
  }
  }

  //親の選択と次世代の個体の生成
  for(int i=0;i<numOfIndivisuals;i++){
    MotherRank=rand()%eliteNum;
    FatherRank=rand()%eliteNum;
    for(int j=0;j<n;j++){
      Father[j]=Individual[suffixOfFitness[FatherRank]][j];//ここなにかある
      Mother[j]=Individual[suffixOfFitness[MotherRank]][j];
    }
    createChild(Father,Mother,Child,n);
    if(rand()/RAND_MAX<percentOfMutation)mutation(Child,n);

    for(int j=0;j<n;j++){
      newIndividual[i][j]=Child[j];
    }
  }
  //世代交代
  for(int i=0;i<numOfIndivisuals;i++)
    for(int j=0;j<n;j++)
      Individual[i][j]=newIndividual[i][j]; 

    if(bestPathLength<normPathLength){
      save_path("mk_neighbor.path", p,n);
      break;
    }
  }
  return bestPathLength;
}


void Usage(char *s) {
  printf("Usage: %s file or num\n", s);
  exit(0);
}

int main( int argc, char *argv[]) {
  int n, i,j;
  Location location[N];
  double dist[N][N], len;
  int    path[N];
  
  time_t tp; 
  time(&tp); srand48(tp);

  if ( argc < 2 ) Usage(argv[0]);
  /** ノード数 n **/
  n = atoi(argv[1]);
  if ( n>0 ) {
    n = atoi(argv[1]);
    random_location( n, location);
  } else {
    n = load_location(argv[1], location);
  }

  /*** 都市の座標表示：デバッグ用 ***/
  for(i=0; i<n ; i++ )
    printf("%d (%f, %f)\n", i, location[i].x, location[i].y);

  /*** 距離行列の計算 ***/
  calc_distance(location, dist, n);

  /*** GAで解く ***/
  srand((unsigned int)time(NULL));
  len = solve_geneticAlgorithm( path, dist, n);//seedの初期化
  printf("length= %f\n", len);
  show_path( path, dist, location, n);

  save_location("path.data",location,path,n);

  /*gnuplotとのパイプ*/
  FILE *gp;
  gp=popen("gnuplot -persist","w");
  fprintf(gp,"unset key\n");
  fprintf(gp,"set size square\n");
  fprintf(gp,"set title \"NodeNum=%d IndNum=%d MutateRate=%lf EliteNum=%d \\n totalPathLength=%lf \"\n"
        ,N,MAXINDIVIDUAL,MUTATE,ELITENUM,len);

  fprintf(gp,"plot \"path.data\" with lines\n");

  fprintf(gp,"set term png\n");
  fprintf(gp,"set output \"%s.png\"\n",argv[1]);
  fprintf(gp,"replot\n");
  fprintf(gp,"set output\n");
  fprintf(gp,"set term x11\n");

  pclose(gp);

  return 0;
}
