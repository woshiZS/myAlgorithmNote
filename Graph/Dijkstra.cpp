#include<cstdio>
const int infinity=999999;
int n,m,book[50]={0},dis[50],e[50][50];
int main(){
    freopen("input2.txt","r",stdin);
    scanf("%d%d",&n,&m);
    //initialize
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j){
            if(i==j)e[i][j]=0;
            else e[i][j]=infinity;
        }
    }
    book[1]=1;
    printf("There is no exception!\n");
    for(int i=1;i<=m;++i){
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        e[a][b]=c;
    }
    for(int i=1;i<=n;++i)dis[i]=e[1][i];
    printf("input is okay!\n");
    for(int i=1;i<n;++i){
        int min=infinity,u;
        for(int j=1;j<=n;++j){
            if(!book[j]&&dis[j]<min){min=dis[j];u=j;}
        }
        book[u]=1;
        for(int j=1;j<=n;++j){
            if(e[u][j]!=infinity&&dis[j]>dis[u]+e[u][j])dis[j]=dis[u]+e[u][j];
        }
    }

    for(int i=1;i<=n;++i)printf("%10d",dis[i]);
    printf("\n");    
    return 0;
}