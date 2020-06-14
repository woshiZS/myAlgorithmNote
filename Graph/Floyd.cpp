#include<cstdio>

const int infinity=999999;
int e[20][20];
int main(){
    int n,m;
    freopen("input.txt","r",stdin);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j){
            if(i==j)e[i][j]=0;
            else e[i][j]=infinity;
        }
    }
    printf("There is no exception!\n");
    for(int i=0;i<m;++i){
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);e[a][b]=c;//you cant confirm the pos at runtime!!!
    }

    for(int k=1;k<=n;++k){
        for(int i=1;i<=n;++i){
            for(int j=1;j<=n;++j){
                if(e[i][j]>e[i][k]+e[k][j])e[i][j]=e[i][k]+e[k][j];
            }
        }
    }

    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j)printf("%10d",e[i][j]);printf("\n");
    }

    return 0;
}