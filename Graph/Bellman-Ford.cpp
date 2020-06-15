#include<cstdio>
const int NoEdge=999999;
int n,m,u[10],v[10],w[10],dis[10];
int main(){
    freopen("input3.txt","r",stdin);
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;++i)scanf("%d%d%d",&u[i],&v[i],&w[i]);
    for(auto& num:dis)num=NoEdge;
    dis[1]=0;
    // printf("No exception here!\n");
    for(int k=1;k<n;++k){
        int check=0;
        for(int i=0;i<m;++i){
            if(dis[v[i]]>dis[u[i]]+w[i]){dis[v[i]]=dis[u[i]]+w[i];check=1;}
        }
        if(!check)break;//cut branch!
    }
    for(int i=1;i<=n;++i)printf("%10d",dis[i]);
    //test if there is a minus loop.
    for(int i=0;i<m;++i)if(dis[v[i]]>dis[u[i]]+w[i]){printf("There is at least one minus loop!\n");break;}
    
    return 0;
}