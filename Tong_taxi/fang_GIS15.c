#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define rr(a,b) (RR[(a)*R+(b)])
#define rd(a,b) (RD[(b)*R+(a)])
#define dd(a,b) (DD[(a)*D+(b)])
/*#define rr(a,b) (RR[(a)*4+(b)])
#define rd(a,b) (RD[(b)*4+(a)])
#define dd(a,b) (DD[(a)*4+(b)])*/
#define MAX_WAIT_PICK 1000000
#define ARRI_DDL 1000000//1000000
#define WINDOW 100
#define THRE_VAL 200
#define MAX_DIS 23//两个点之间可能存在边的最大直线距离

struct order{
    double time;
    int rid;
    int did;
};
struct path{
    int RorD;//1代表小区，0代表餐厅，2表示这只是一个表示路径中的转折点的结点
    double atime;//派送员到达时间
    double ltime;//派送员离开时间
    double dtime;//对应的订单下单时间
    int id;//这个点所对应的id
    int num;//当前身上的外卖数
    int number;//对应的订单的订单号
	double x;//当前结点的x坐标
	double y;//当前结点的y坐标
	double ddl;//能容忍的到达这个点的最晚时间
    struct path *next;
};

struct current//记录当前时刻快递员所处状态的信息
{
	double x;//当前时刻快递员的x坐标
	double y;//当前时刻快递员的y坐标
	double time;//处于当前状态的时刻，即为离开这一点的时刻
	int num;//当前快递员身上的外卖数
};

struct courier{
    struct path *first;
    struct path *tmp;
    double maxtime;
    double distance;
    int num;//number of places in this courier's route
    int c;//这个司机的车上坐了几个人，只有当这个人下车了，这个值才会减少
    int key_place;//这个司机路上经过了多少个点
};

struct init_place
{
	int i;
	double x;
	double y;
};

struct ws_ts
{
    int number;
    struct ws_ts *next;
};

struct partition
{
    int *worker;
    int *task;
    int workload;
    int *label;//用来记录这个划分处于划分树的哪一个位置
    int end;//用来记录label中共有多少位有效数字，end是最后一个有效数字的下标
    struct partition *next;
};

struct route
{
    struct path *first;
    struct path *p;
};

//变量定义
int SIZE;
int R,D,M,C,N;
int *Q;//存储每一个司机的初始容量
int *region;//二维数组，记录worker和任务之间从距离的角度来看是否存在有边相连的可能性
double MAX,MAXDIR;
double *RR,*RD,*DD;
struct courier *cous;
struct current *curren;
struct order *Nplace;
int *Rplace,*Dplace,*COLOR;
FILE *ff;//
struct init_place *initp;
struct route *final_route;



//这个函数用来计算残余图
//c是容量
//f是流量
//n,m分别是原图邻接矩阵的行数和列数
void residual(int *c,int *f,int *resi,int *resi_c,int n,int *E)
{
    int i,j;
    int r;

    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            //先进行初始化
            resi[i*n+j]=0;
            resi_c[i*n+j]=0;

            if(E[i*n+j])//如果这条边在原图中存在，则计算其残余流量
            {
                r=c[i*n+j]-f[i*n+j];

                resi[i*n+j]=r>0?1:0;
                resi_c[i*n+j]=r;

                resi[j*n+i]=f[i*n+j]>0?1:0;
                resi_c[j*n+i]=f[i*n+j];
            }
        }
    }
}

//这个函数用来对残余图resi进行深度优先搜索，当找到终点t（编号为0）时，中止计算
//path用来存储路径,n是图中顶点数，ind是当前搜索点的编号
void visit(int *resi,int *path,int n,int ind)
{
    int i;
    int j;

    if(ind==0)//如果当前结点是终点
        return ;

    for(i=0;i<n;i++)
    {
        if(resi[ind*n+i]&&(path[i]==-1))//如果残余图中存在边（ind，i）,且顶点i未被访问过
        {
            path[i]=ind;
            if(i==0)
                return ;
                ////////////////////////////
            //printf("\nthis is path:::");
            //计算增广路径中的瓶颈值min
            /*for(j=0;j<n;j++)//对边（head，tail）进行操作
            {

                printf("%d ",path[j]);

            }*/
            //printf("\n");
            /////////////////////////
            visit(resi,path,n,i);
            if(path[0]!=-1)//找到了一条增广路径
                return ;
            path[i]=-1;
        }
    }

    path[ind]=-1;//将当前节点恢复成可以访问状态，因为这条路径找不到终点
    return ;
}

//这个函数用来在残留图中寻找增光路径
//resi是残留图的邻接矩阵
//n是行数
//所有顶点的编号顺序为t，二分图左侧顶点，s，二分图右侧顶点
//如果能找到增光路径，返回1；否则，返回0
int find_augmenting_path(int *resi,int *path,int n,int w)
{
    int i;
    int j;
    /////////


    //初始化path
    for(i=0;i<n;i++)
    {
        path[i]=-1;
    }
    path[w]=w;//编号为w的顶点为起始点s

    //对s的所有邻接点进行DFS搜索
    for(i=0;i<n;i++)
    {
        if(resi[w*n+i])//如果残余图中存在这条边
        {
            path[i]=w;
            /////////////////
            /*printf("\nthis maybe path:::");
            //计算增广路径中的瓶颈值min
            for(j=0;j<n;j++)//对边（head，tail）进行操作
            {

                printf("%d ",path[j]);

            }
            printf("\n");*/
////////////////
            visit(resi,path,n,i);
            if(path[0]!=-1)//找到了一条增广路径
                break;
            path[i]=-1;
        }
    }

    //////////


    if(path[0]!=-1)//找到了一条增广路径
       {///////////

            /*printf("\nthis is path:::");
            //计算增广路径中的瓶颈值min
            for(i=0;i<n;i++)//对边（head，tail）进行操作
            {

                printf("%d ",path[i]);

            }
            printf("\n");*/

        return 1;
       }
    else
        return 0;
}

//这个函数用来对流进行扩增
//f是当前流，c是容量，path是找到的增广路径
//n是矩阵的行数
void augment(int *f,int *c,int *path,int n,int w,int *resi_c,int *E)
{
    int tail,head;
    int min=1000000;

    tail=0;//从终点开始寻找边

    //计算增广路径中的瓶颈值min
    while(tail!=w)//对边（head，tail）进行操作
    {
        head=path[tail];
        min=resi_c[head*n+tail]<min?resi_c[head*n+tail]:min;
        tail=head;
    }

    //对流进行修改
    tail=0;//从终点开始寻找边
    while(tail!=w)//对边（head，tail）进行操作
    {
        head=path[tail];
        if(E[head*n+tail])//如果这条边与原边同向
            f[head*n+tail]=f[head*n+tail]+min;
        else
            f[head*n+tail]=f[head*n+tail]-min;
        tail=head;
    }
}

//这个函数用来求一个给定的图的最大流
//old_E是待匹配的二分图的邻接矩阵，矩阵是一个方阵，顶点编号顺序为t，二分图左侧顶点，s，二分图右侧顶点
//n是邻接矩阵的行数
//w是二分图左侧的顶点数（包含起始点s）
//c是每条边的容量，c也是一个方阵
//f表示图中每条边的流量
void max_flow(int *old_E,int n,int *c,int w,int *f)
{
    int *resi,*resi_c;//resi存储残余图,resi_c储存残余图的容量
    int *path;//用来存储增广路径
    int i,j;
    /*temp=(int *)malloc(old_n*old_n*sizeof(int));*/

    resi=(int *)malloc(n*n*sizeof(int));
    resi_c=(int *)malloc(n*n*sizeof(int));
    path=(int *)malloc(n*sizeof(int));

    /*//将old_E中的内容复制到temp矩阵中来
    for(i=0;i<old_n;i++)
    {
        for(j=0;j<old_m;j++)
        {
            temp[i*old_n+j]=old_E[i*old_n+j];
        }
    }*/

    //初始化图中流量为0
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            f[i*n+j]=0;
        }
    }

    //得到残余图
    residual(c,f,resi,resi_c,n,old_E);
///////////////////////
    /*printf("resi:::\n");
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            printf("%d ",resi[i*n+j]);
        }
        printf("\n");
    }*/

    while(find_augmenting_path(resi,path,n,w))
    {
        augment(f,c,path,n,w,resi_c,old_E);
        residual(c,f,resi,resi_c,n,old_E);

        /////////////
        /*printf("flow:::\n");
        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {
                printf("%d ",f[i*n+j]);
            }
            printf("\n");
        }*/
    }
    free(resi);
    free(resi_c);
    free(path);
}


//这个函数用来计算司机w当前位置到结点pick的距离
double curr_dis(int w,struct path *pick)
{
    double distance;
    double x1,x2,y1,y2;
    int ind;//记录pick对应地点的编号

    if(pick==NULL)//如果路线里面目前没东西
        return 0;

    ind=pick->id;
    x1=(curren+w)->x;
    y1=(curren+w)->y;
    if(pick->RorD==0)//是接人地点
    {
        x2=Rplace[2*ind];
        y2=Rplace[2*ind+1];
    }
    else if(pick->RorD==1)//是下车地点
    {
        x2=Dplace[2*ind];
        y2=Dplace[2*ind+1];
    }

    distance=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
    //printf("cur_dis:::%d %d %f %f %f %f %f\n",w,pick->number,distance,x1,x2,y1,y2);
    return distance;
}


//这个函数用来计算两个给定结点之间的距离
double dis(struct path *A,struct path *B)
{
    if((A==NULL)||(B==NULL))
        return 0;
    if(A->RorD==0&&B->RorD==0)
    {
        //printf("dis:::%d %d %f \n",A->number,B->number,rr(A->id,B->id));
        return rr(A->id,B->id);
    }
    if(A->RorD==0&&B->RorD==1)
    {
        //printf("dis:::%d %d %f \n",A->number,B->number,rd(A->id,B->id));
        return rd(A->id,B->id);
    }

    if(A->RorD==1&&B->RorD==0)
    {
        //printf("dis:::%d %d %f \n",A->number,B->number,rd(B->id,A->id));
        return rd(B->id,A->id);
    }

    if(A->RorD==1&&B->RorD==1)
    {
        //printf("dis:::%d %d %f \n",A->number,B->number,dd(A->id,B->id));
        return dd(A->id,B->id);
    }

	return 0;
}


//这个函数用来检查任务s的某插入位置对于司机w的已有路线来说是不是feasible的
//par_rou是w的在插入位置之后剩余的已有路线，node是待插结点，td是插入结点后引起的时间延误
//如果feasible，返回1；否则，返回0
int check_feasible(struct path *par_rou,struct path *node,double td)
{
    struct path *p;

    //先检查结点node本身是否feasible
    if((node->atime)>(node->ddl))
        return 0;

    //检查node插入位置后的结点是否feasible
    for(p=par_rou;p!=NULL;p=p->next)
    {
        if((p->atime)+td>(p->ddl))
            return 0;
    }
    return 1;
}


//这个函数用来为任务s在工作者w的已有队列中寻找最优的插入位置
//任务s又分为两个子任务，接收任务s和完成任务s，计算cost的时候，将它们捆绑计算
//当s对于w来说是feasible时，返回1；否则，返回0
int find_best_insertion_place(int w,int s,double *min_cost,double *subcost,int *best_pos_start, int *best_pos_end)
{
    int i,j;
    struct courier *driver;
    struct order *serve;
    struct path *left,*right,*start,*end,*left2,*right2,*p;//start存储任务s的接人结点，end存储s的终点结点
    double cost,cost1;
    int flag=0;//用来记录能否找到一种feasible的插入情况

    *min_cost=1000000;
    driver=cous+w;
    serve=Nplace+s;

    //初始化接人结点和终点结点
    start=(struct path *)malloc(sizeof(struct path));
    end=(struct path *)malloc(sizeof(struct path));

    start->RorD=0;//1代表终点，0代表起点（接人地点），2表示这只是一个表示路径中的转折点的结点
    start->dtime=serve->time;//对应的订单下单时间
    start->id=serve->rid;//这个点所对应的id
    start->number=s;//对应的订单的订单号
    start->ddl=(serve->time)+MAX_WAIT_PICK;
    end->RorD=1;//1代表终点，0代表起点（接人地点），2表示这只是一个表示路径中的转折点的结点
    end->dtime=serve->time;//对应的订单下单时间
    end->id=serve->did;//这个点所对应的id
    end->number=s;//对应的订单的订单号
    end->ddl=(serve->time)+ARRI_DDL;

    //对w已有规划中的每一个可能位置进行插入尝试
    for(i=0; i<=driver->num; i++,left=right,right=((right==NULL)?NULL:right->next))
    {
        cost=0;

        //计算在此位置插入之后，增加的路程开销
        if(i==0)//首段
        {
            right=driver->first;
            cost=curr_dis(w,start)+dis(start,driver->first)-curr_dis(w,driver->first);
            start->atime=(curren+w)->time+curr_dis(w,start);
        }
        else if(i==driver->num)//尾段
        {
            cost=dis(left,start);
            start->atime=left->atime+cost;
        }
        else
        {
            cost=dis(left,start)+dis(start,right)-dis(left,right);
            start->atime=left->atime+dis(left,start);
        }
        /////////////////////////////////////////////////////
        if(cost<0&&w==22)
            printf("\nERROR::::::::::%f,%d,%d\n",cost,w,s);
        /////////////////////////////////////////////////////
        //如果此位置是feasible的
        if(check_feasible(right,start,cost))
        {
            cost1=cost;

            //对终点接点进行插入尝试
            for(j=i,left2=start,right2=right; j<=driver->num; j++,left2=right2,right2=((right2==NULL)?NULL:right2->next))
            {
                ////////////////////////////////////////////////////////////
                /*printf("%d's route::::::\n",w);
                for(p=driver->first; p!=NULL; p=p->next)
                {
                    printf("%d ",p->number);
                }
                printf("\n");*/
                ///////////////////////////////////////////////////////////
                if(i<driver->num)//如果start未到尾段
                {
                    if(j==i)
                    {
                        cost=cost1+dis(start,end)+dis(end,right2)-dis(start,right2);
                        end->atime=start->atime+dis(start,end);
                    }
                    else if(j==driver->num)
                    {
                        cost=cost1+dis(left2,end);
                        end->atime=left2->atime+cost1+dis(left2,end);
                    }
                    else
                    {
                        cost=cost1+dis(left2,end)+dis(end,right2)-dis(left2,right2);
                        end->atime=left2->atime+cost1+dis(left2,end);
                    }
                }
                else//start在尾段
                {
                    cost=cost1+dis(start,end);
                    end->atime=start->atime+dis(start,end);
                }

                /////////////////////////////////////////////////////
                if(cost<0&&w==22)
                    printf("\nERROR::::::::::%f,%d,%d\n",cost,w,s);
                /////////////////////////////////////////////////////

                //检查这个插入位置是否feasible
                if(check_feasible(right2,end,cost))
                {

                    //更新最小开销
                    if(cost<(*min_cost))
                    {
                        flag=1;
                        *min_cost=cost;
                        *best_pos_start=i;
                        *best_pos_end=j;
                        *subcost=cost1;
                    }
                }
            }
        }

    }

    free(start);
    free(end);

    //返回相应值
    if(flag)
        return 1;
    else
        return 0;
}


//这个函数用来在司机w的已有路线中插入结点
//w是司机编号，s是任务编号，pos_start是接人结点应插入的位置，pos_end是终点结点应插入的位置
void insert_s(int w,int s,int pos_start,int pos_end,double cost,double subcost)
{
    struct courier *driver;
    struct path *start,*end,*left,*right;
    struct order *serve;
    int i,j;

    //初始化
    driver=cous+w;
    serve=Nplace+s;
    start=(struct path *)malloc(sizeof(struct path));
    end=(struct path *)malloc(sizeof(struct path));

    start->RorD=0;//1代表终点，0代表起点（接人地点），2表示这只是一个表示路径中的转折点的结点
    start->dtime=serve->time;//对应的订单下单时间
    start->id=serve->rid;//这个点所对应的id
    start->number=s;//对应的订单的订单号
    start->ddl=(serve->time)+MAX_WAIT_PICK;
    end->RorD=1;//1代表终点，0代表起点（接人地点），2表示这只是一个表示路径中的转折点的结点
    end->dtime=serve->time;//对应的订单下单时间
    end->id=serve->did;//这个点所对应的id
    end->number=s;//对应的订单的订单号
    end->ddl=(serve->time)+ARRI_DDL;

    //将接人结点插入
    for(i=0,right=driver->first; i<=driver->num; i++,left=right,right=((right==NULL)?NULL:right->next))
    {
        if(pos_start==i)
        {
            if(i==0)//首段
            {
                //将结点挂上
                start->next=driver->first;
                driver->first=start;
                //更新到达时间
                start->atime=(curren+w)->time+curr_dis(w,start);
                //更新到此结点车上有几个人
                start->num=(curren+w)->num+1;
                break;
            }
            else
            {
                //将结点挂上
                start->next=right;
                left->next=start;
                //更新到达时间
                start->atime=left->atime+dis(left,start);
                //更新到此结点车上有几个人
                start->num=left->num+1;
                break;
            }
        }
    }

    //将终点结点插入
    for(j=i,left=start; j<=driver->num; j++,left=right,right=((right==NULL)?NULL:right->next))
    {
        if(j==pos_end)//找到了要插入的边
        {
            //将结点挂上
            end->next=right;
            left->next=end;
            //更新到达时间以及到此结点车上有几个人
            end->atime=left->atime+dis(left,end);
            end->num=left->num-1;
            if(right!=NULL)
            {
                right->atime=right->atime+cost;
            }

        }
        else if(j<pos_end)//还没有到要插入的边
        {
            //更新到达时间以及到此结点车上有几个人
            if(right!=NULL)
            {
                right->atime=right->atime+subcost;
                right->num=right->num+1;
            }
        }
        else//已经过了要插入的边
        {
            //更新到达时间
            if(right!=NULL)
            {
                right->atime=right->atime+cost;
            }
        }
    }

    //更新司机路线上的结点数
    driver->num=driver->num+2;
    driver->c=driver->c+1;
    driver->key_place=driver->key_place+2;
}

//这个函数用来对每一个w（worker）所分配到的任务集进行最优插入方案的选择与实施，同时还要对RWS，RTS，forbidden进行更新
//w是worker的总数，此处定义与求最大流时不同
//n是f的矩阵纬度
//RWS是可工作的司机集，RTS是还需分配的任务集合，forbidden是禁止边集
void insert_scheduling(int *f,int w,int n,int *RWS,int *RTS,int *forbidden)
{
    int i,j;
    int pos_start,pos_end,min_pos_start,min_pos_end;
    int min_s;
    double cost,min_cost,subcost,min_subcost;
    int flag=0;//用以记录对于worker i而言，是否还有任务可分配的未分配（排除无法分配成功的情况）

    for(i=1;i<w+1;i++)
    {
        //对worker i-1 的路线进行更新
        while(1)
        {
            flag=0;
            min_cost=1000000;

            for(j=w+2;j<n;j++)
            {
                if(f[i*n+j]>0)//如果j-(w+2)任务是被分配给了i-1(编号)工作人员的话
                {
                    //printf("enter:%d %d\n",i-1,j-(w+2));
                    if(find_best_insertion_place(i-1,j-(w+2),&cost,&subcost,&pos_start,&pos_end))//如果能找到最优位置
                    {
                        //printf("can insert:%d %d\n",i-1,j-(w+2));
                        flag=1;

                        //更新最小开销时的情况
                        if(cost<min_cost)
                        {
                            min_s=j;
                            min_pos_start=pos_start;
                            min_pos_end=pos_end;
                            min_cost=cost;
                            min_subcost=subcost;
                        }
                    }
                }
            }

            if(flag)
                insert_s(i-1,min_s-(w+2),min_pos_start,min_pos_end,min_cost,min_subcost);
            else
                break;

            f[i*n+min_s]=0;//将任务插入之后，就可以把相应的边删除了
            RTS[min_s-(w+2)]=0;//将任务min_s-(w+2)从RTS中删去
            (cous+i-1)->distance=(cous+i-1)->distance+min_cost;
            //if(i-1==0)
                //printf("%f :::%f:::\n",min_cost,(cous+i-1)->distance);
        }

        //已经没有任务能够插入到worker i-1 的队列中了
        //更新forbidden
        for(j=w+2;j<n;j++)
        {
            if(f[i*n+j]>0)//如果j-(w+2)任务是被分配给了i-1(编号)工作人员的话
            {
                forbidden[i*n+j]=1;
            }
        }
        //更新RWS
        if((Q[i-1]-(cous+(i-1))->c)<=0)
            RWS[i-1]=0;//如果司机车上已经没有空位，将该司机从RWS中删除
    }
}


//这个函数用来在每一次GALS的迭代完成之后进行更新，构造一个新的二分图
//RWS 是还可以再被分配任务的worker集，是一个一维矩阵
//RTS 是还需要分配到worker手上的任务集，是一个一维矩阵
//forbidden 是禁止边集合
//E 是生成一个更新后的二分图
//c 是以及相应的容量分配情况
//E,c,forbidden 都是矩阵，维度为n
//n 是所有顶点数，和求最大流时定义一样
//w 是司机的数量
void update_flow_network_and_assignment(int *RWS,int *RTS,int *forbidden,int n,int w,int *E,int *c)
{
    int i,j;

    //初始化E,c矩阵
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            E[i*n+j]=0;
            c[i*n+j]=0;
        }
    }

    //构造一个新的二分图
    for(i=1;i<=w;i++)//对所有从worker出发的边进行操作
    {
        if(RWS[i-1])//如果司机i-1在RWS中
        {
            for(j=w+2;j<n;j++)//对所有任务进行操作
            {
                if(RTS[j-(w+2)]&&(forbidden[i*n+j]!=1)&&region[i*n+j])
                {
                    E[i*n+j]=1;
                    c[i*n+j]=1;
                }
            }
        }
    }

    for(j=1;j<=w;j++)//对所有从起点s出发的边进行处理
    {
        E[(w+1)*n+j]=RWS[j-1];
        c[(w+1)*n+j]=Q[j-1]-((cous+j-1)->c);//司机的车上还剩多少座位
    }

    for(i=w+2;i<n;i++)//对所有从任务出发到终点t的边进行操作
    {
        E[i*n]=RTS[i-(w+2)];
        c[i*n]=RTS[i-(w+2)];
    }
}


//这个函数用来执行一次GALS算法，能够产生一个路径规划方案
//输入变量：RWS，RTS, num_n, num_s, Q
//RWS: 参与的worker的集合，是一个一维数组，某一项为1表示编号为这个的worker在RWS中
//RTS：参与的任务的集合，是一个一维数组，某一项为1表示编号为这个的任务在RTS中
//num_w：是RWT内元素的个数
//num_s：是RST内元素的个数
//forbidden: 已有的禁止边集合
//路径规划方案存储在cous数组里，这是一个全局变量
void GALS(int *RWS,int *RTS,int num_w,int num_s,int *forbidden)
{
    int i,j;
    int n;
    int *E,*f,*c;
    //int c[1000][1000];
    int flag=0;//用以记录是否达到了终止条件
    struct path *p;

    n=2+num_s+num_w;

    //申请空间
    f=(int *)malloc(n*n*sizeof(int));//为流图申请空间
    E=(int *)malloc(n*n*sizeof(int));//为二分图邻接矩阵申请空间
    c=(int *)malloc(n*n*sizeof(int));//为图中各边容量申请空间
    //forbidden=(int *)malloc(n*n*sizeof(int));//为禁止边集申请空间

    update_flow_network_and_assignment(RWS,RTS,forbidden,n,num_w,E,c);//根据剩余的worker和任务更新二分图和各边容量

    /*//初始化forbidden集合
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            forbidden[i*n+j]=0;//初始情况，没有一条边被禁止
        }
    }*/

    //计算最大流来做匹配
    max_flow(E,n,c,num_w+1,f);

    //重复地scheduling直到可以停止
    while(1)
    {
        flag=0;

        insert_scheduling(f,num_w,n,RWS,RTS,forbidden);//做插入操作

        update_flow_network_and_assignment(RWS,RTS,forbidden,n,num_w,E,c);//根据剩余的worker和任务更新二分图和各边容量

        //确认是否达到了终止条件：每一个在RTS中的任务，是否在E中还与worker有边相连
        for(j=num_w+2; j<n; j++)
        {
            for(i=1; i<=num_w; i++)
            {
                if(E[i*n+j])
                {
                    flag=1;//至少有一个任务还有可能被安排给某个司机
                    break;
                }
            }
            if(flag)
                break;
        }
        if(flag)
            max_flow(E,n,c,num_w+1,f);//计算最大流，从而分配任务
        else
        {
            ////////////////////////
            for(i=0;i<M;i++)
            {
                p=(cous+i)->first;
                //fprintf(ff,"%d's route::::::\n",i);
                printf("%d's route::::::\n",i);
                while(p!=NULL)
                {
                    //fprintf(ff,"%d ",p->number);
                    printf("%d ",p->number);
                    p=p->next;
                }
                //fprintf(ff,"\n");
                printf("\n");
            }
            //fprintf(ff,"\n");
            printf("\n");
        ////////////////////////
            //释放空间
            free(f);
            free(E);
            free(c);
            //free(forbidden);
            return ;
        }
    }
}

//这个函数用来找出tmp_s集合中和seed距离最近的点，这里的距离指的是订单的接人结点之间的距离
int find_next_close_task(int seed,int *tmp_s)
{
    double min_dis=1000000;
    double distance;
    int s,i,ind1,ind2;
    int flag=0;

    ind1=(Nplace+seed)->rid;

    for(i=0; i<N; i++)
    {
        if(tmp_s[i]&&(i!=seed))
        {
            ind2=(Nplace+i)->rid;
            distance=rr(ind1,ind2);
            if(distance<min_dis)
            {
                flag=1;
                min_dis=distance;
                s=i;
            }
        }
    }
    if(flag)
        return s;
    else
        return -1;
}


//这个函数用来对给定的worker集和任务集进行任务导向的划分
//输入变量：
//cur_w: 现在的worker集，维数为M，是一个一维数组，某项为1表示这个worker在worker集中
//cur_s: 现在的任务集，维数为N，是一个一维数组，某项为1 表示这个任务在任务集中
//threshold: 阈值，每一个划分之后的集合中边的数量不能超过的值
//forbidden：禁止边，即在二分图中不会出现的边，是一个二维矩阵，为1，表示该边被禁止了
/////////////region：一个二维矩阵，表示单从距离的远近上来说，worker和任务之间是否存在有边相连的可能性，为1，表示可以存在边，即任务在worker的范围内
//输出：
//w_A:划分出的两个结果之一的A的worker集，是一个一维数组
//s_A:划分出的两个结果之一的A的任务集，是一个一维数组
//同理有w_B，s_B
//s_A,w_A,...,cur_w,cur_s的空间的申请和释放在调用此函数的函数里做，worker集的维数为M，server集的维数为N
void task_oriented_partition_generation(int *cur_w,int *cur_s,int threshold,int *forbidden,int *w_A,int *s_A,int *w_B,int *s_B)
{
    int i;
    struct ws_ts *WS,*TS,*p,*q,*p1,*q1;//做成动态链表
    int s,d,seed;//seed用来存储这一次划分算法的种子任务编号
    int workload=0;
    int n=M+N+2;//二分图中的顶点总数，司机数+订单数+起始点+终止点
    int w=M;//司机总数
    //int tmp_w[100];//用来记录对cur_w中的司机的划分情况，是不是还有司机可以考虑加入w_A中
    //int tmp_s[100];//用来记录对cur_s中的任务的划分情况，同上
    int *tmp_w;//用来记录对cur_w中的司机的划分情况，是不是还有司机可以考虑加入w_A中
    int *tmp_s;//用来记录对cur_s中的任务的划分情况，同上
    int n_tmp_s=0;//记录tmp_s中1的数量
    int n_tmp_w=0;//记录tmp_w中1的数量

    //初始化tmp_w,tmp_s
    tmp_w=(int *)malloc(M*sizeof(int));
    tmp_s=(int *)malloc(N*sizeof(int));

    for(i=0; i<M; i++)
    {
        tmp_w[i]=cur_w[i];
        n_tmp_w=n_tmp_w+cur_w[i];
    }
    for(i=0; i<N; i++)
    {
        tmp_s[i]=cur_s[i];
        n_tmp_s=n_tmp_s+cur_s[i];
    }

    //初始化PWS，PTS，WS，TS都为空
    for(i=0; i<M; i++)
    {
        w_A[i]=0;
    }
    for(i=0; i<N; i++)
    {
        s_A[i]=0;
    }
    WS=(struct ws_ts *)malloc(sizeof(struct ws_ts));
    TS=(struct ws_ts *)malloc(sizeof(struct ws_ts));
    WS->next=NULL;
    TS->next=NULL;

    //将任务集中的第一个任务放入TS中,并将此任务标记为s
    for(i=0; i<N; i++)
    {
        if(cur_s[i])
        {
            s=i;
            seed=s;
            TS->next=(struct ws_ts *)malloc(sizeof(struct ws_ts));
            p=TS->next;
            p->number=s;
            p->next=NULL;
            tmp_s[s]=0;//表示任务s已经被划分了
            n_tmp_s--;
            break;
        }
    }

    while(1)
    {
        q=WS;

        //对每一个TS中的任务s执行如下操作：
        for(p=TS->next; p!=NULL; p=p->next)
        {
            s=p->number;
            for(i=1; i<=w; i++)
            {
                if(region[i*n+s+(w+2)]&&(forbidden[i*n+s+(w+2)]!=1))//如果这个worker可以完成任务s
                {
                    if(cur_w[i-1]&&(w_A[i-1]!=1))//如果司机i-1还未被加入到w_A中，是这一轮新发现的
                    {
                        //将司机i-1加入到WS链表中
                        q->next=(struct ws_ts *)malloc(sizeof(struct ws_ts));
                        q=q->next;
                        q->number=i-1;
                        q->next=NULL;
                        //将司机i-1加入到w_A中
                        w_A[i-1]=1;
                        //将workload加1
                        workload=workload+1;
                        //将司机i-1从tmp_w中去除
                        tmp_w[i-1]=0;
                        n_tmp_w--;
                    }
                }
            }
        }
        //清空TS
        if(TS->next!=NULL)
        {
            for(p=TS->next,p1=p->next; p1!=NULL; p=p1,p1=p1->next)
                free(p);
            free(p);
        }
        TS->next=NULL;

        p=TS;

        //对所有WS中的司机进行如下操作
        for(q=WS->next; q!=NULL; q=q->next)
        {
            d=q->number;//d存储司机的编号

{

}            for(i=w+2; i<n; i++)
            {
                if(region[(d+1)*n+i]&&(forbidden[(d+1)*n+i]!=1))//如果这个任务在司机能到达的范围内//这里我自己加了一点改动
                {
                    if(cur_s[i-(w+2)]&&(s_A[i-(w+2)]!=1))//如果任务i-（w+2）是这一轮迭代新发现的
                    {
                        //将任务i-(w+2)加入TS链表中
                        p->next=(struct ws_ts *)malloc(sizeof(struct ws_ts));
                        p=p->next;
                        p->number=i-(w+2);
                        p->next=NULL;
                        //将任务i-(w+2)加入s_A中
                        s_A[i-(w+2)]=1;
                        //将任务i-(w+2)从tmp_s中去除
                        if(tmp_s[i-(w+2)]!=0)
                        {
                            n_tmp_s--;
                            tmp_s[i-(w+2)]=0;
                        }
                    }
                }
            }
        }
        //清空WS
        if(WS->next!=NULL)
        {
            for(q=WS->next,q1=q->next; q1!=NULL; q=q1,q1=q1->next)
                free(q);
            free(q);
        }
        WS->next=NULL;

        //检查退出条件
        if((workload>=threshold)||(n_tmp_s==0)||(n_tmp_w==0))
        {
            //将w_B,s_B设置好
            for(i=0; i<M; i++)
            {
                w_B[i]=cur_w[i]-w_A[i];
                //printf("i:%d w_B[i]:%d::: cur_w[i]:%d w_A[i]:%d\n",i,w_B[i],cur_w[i],w_A[i]);
                //printf("%d::::\n",cur_w[i]-w_A[i]);
            }
            for(i=0; i<N; i++)
            {
                s_B[i]=cur_s[i]-s_A[i];
                //printf("i:%d s_B[i]:%d::: cur_s[i]:%d s_A[i]:%d\n",i,s_B[i],cur_s[i],s_A[i]);
                //printf("%d::::\n",cur_s[i]-s_A[i]);
            }
            //清空TS
            if(TS->next!=NULL)
            {
                for(p=TS->next,p1=p->next; p1!=NULL; p=p1,p1=p1->next)
                    free(p);
                free(p);
            }
            TS->next=NULL;
            free(TS);
            free(WS);
            free(tmp_s);
            free(tmp_w);
            return ;
        }
        //如果TS目前是空的
        if(TS->next==NULL)
        {
            s=find_next_close_task(seed,tmp_s);
            TS->next=(struct ws_ts *)malloc(sizeof(struct ws_ts));
            p=TS->next;
            p->number=s;
            p->next=NULL;
            tmp_s[s]=0;//表示任务s已经被划分了
            n_tmp_s--;
        }

    }
}


//这个函数用来计算二分图中边的数目，不包含起点到worker的边和task到终点的边
//输入变量：
//W: worker集合
//S：任务集合
//forbidden：禁止边集合
///////////////region：定义同上
//输出：
//计算出来的workload
int cal_workload(int *W,int *S,int *forbidden)
{
    int n,i,j,num,w;

    n=N+M+2;//输入的矩阵的行数
    w=M;//司机数量

    for(num=0,i=1; i<=w; i++)//司机i-1
    {
        for(j=w+2; j<n; j++)//任务j-(w+2)
        {
            if(W[i-1]&&S[j-(w+2)]&&region[i*n+j]&&(forbidden[i*n+j]!=1))
                num++;
        }
    }
    return num;
}

//这个函数用来递归地对cur_w,cur_s进行划分
//输入变量：
//cur_w: 现有的司机集合，一个一维数组，维数为M
//cur_s：现有的任务集合，一个一维数组，维数为N
//cur_workload：现有的二分图中边的数量，不包含起点到worker的边和任务到终点的边
//threshold：阈值，要求划分后的每一个子集中边的数量不超过这个值
//forbidden：禁止边集合，一个二维数组，列数为M+N+2
//////////////region：同task_oriented_partition_generation函数中的定义，一个二维矩阵，行数为N+M+2
//part：是将partition插入的链表的地址
//label: 一维数组，用来记录partition在划分数中的位置，第一次调用的时候，label只存了一个0在首位
//end: 用来记录label中最后一位有效数字的下标。第一次调用的时候，传进来的是0
//输出结果存在part这一链表中，part并非链表的首地址
void recursive_bisection(int *label,int end,struct partition *part_addr,struct partition **new_part_addr,int *cur_w,int *cur_s,int cur_workload,int threshold,int *forbidden)
{
    int theta;//用来做task_oriented_partition_generation函数的界
    int *w_A,*w_B,*s_A,*s_B;
    //int w_A[100],w_B[100],s_A[100],s_B[100];
    int workload_A,workload_B;
    int i;
    int *label_A,*label_B;
    //int label_A[100],label_B[100];
    struct partition *part,*new_part;

    part=part_addr;

    w_A=(int *)malloc(M*sizeof(int));
    w_B=(int *)malloc(M*sizeof(int));
    s_A=(int *)malloc(N*sizeof(int));
    s_B=(int *)malloc(N*sizeof(int));
    label_A=(int *)malloc(N*sizeof(int));
    label_B=(int *)malloc(N*sizeof(int));

    //更新label
    for(i=0; i<=end; i++)
    {
        label_A[i]=label[i];
        label_B[i]=label[i];
    }
    label_A[end+1]=1;//表示A在树的左侧
    label_B[end+1]=2;//表示B在数的右侧

    //////////////////////
    /*printf("\nbefore run label_A:::");
    for(i=0; i<=end+1; i++)
        printf("%d",label_A[i]);
    printf("\n");
    printf("\nbefore run label_B:::");
    for(i=0; i<=end+1; i++)
        printf("%d",label_B[i]);
    printf("\n");

    printf("%d:::\n",label_A);
    printf("%d:::\n",label_B);*/
    //////////////////////

    theta=cur_workload/2;

    if(cur_workload>threshold)
    {
        //printf("111111111111\n");
        //将现有集合划分成两份
        task_oriented_partition_generation(cur_w,cur_s,theta,forbidden,w_A,s_A,w_B,s_B);

        //printf("222222222222\n");
        /////////////////////////////////
        /*printf("\nw_A:worker:::\n");
        for(i=0; i<M; i++)
        {
            if(w_A[i])
                printf("%d ",i);
        }
        printf("\ns_A:task:::\n");
        for(i=0; i<N; i++)
        {
            if(s_A[i])
                printf("%d ",i);
        }
        printf("\nw_B:worker:::\n");
        for(i=0; i<M; i++)
        {
            if(w_B[i])
                printf("%d ",i);
        }
        printf("\ns_B:task:::\n");
        for(i=0; i<N; i++)
        {
            if(s_B[i])
                printf("%d ",i);
        }*/
        /////////////////////////////////

        workload_A=cal_workload(w_A,s_A,forbidden);//计算workload
        /////////////////////////////////
        //printf("workload:::%d\n",workload_A);
        /////////////////////////////////
        if((workload_A>threshold)&&(workload_A<cur_workload))
        {
            /////////////
            /*printf("\nlabel_A:::");
            for(i=0; i<=end+1; i++)
                printf("%d",label_A[i]);
            printf("\n");*/
            /////////////

            recursive_bisection(label_A,end+1,part,&new_part,w_A,s_A,workload_A,threshold,forbidden);
            part=new_part;
        }
        else
        {
            //将划分A插入划分队列  add_into_partition(part,w_A,s_A,workload_A);
            part->next=(struct partition *)malloc(sizeof(struct partition));
            part=part->next;

            part->worker=(int *)malloc(M*sizeof(int));
            part->task=(int *)malloc(N*sizeof(int));
            part->label=(int *)malloc(N*sizeof(int));
            //将w_A的内容进行复制
            for(i=0; i<M; i++)
                (part->worker)[i]=w_A[i];
            //将s_A的内容复制
            for(i=0; i<N; i++)
                (part->task)[i]=s_A[i];
            //复制workload_A
            part->workload=workload_A;
            //复制label_A
            for(i=0; i<=(end+1); i++)
                (part->label)[i]=label_A[i];
            //更新end
            part->end=end+1;
            part->next=NULL;
            *new_part_addr=part;

            /////////////////////////////////////
            /*printf("worker:::\n");
            for(i=0; i<M; i++)
            {
                if((part->worker)[i])
                    printf("%d ",i);
            }
            printf("\ntask:::\n");
            for(i=0; i<N; i++)
            {
                if((part->task)[i])
                    printf("%d ",i);
            }
            printf("\nlabel:::\n");
            for(i=0; i<=part->end; i++)
            {
                printf("%d ",(part->label)[i]);
            }
            printf("\n");*/
        }

        workload_B=cal_workload(w_B,s_B,forbidden);//计算workload
        /////////////////////////////////
        //printf("workload:::%d\n",workload_B);
        /////////////////////////////////
        if((workload_B>threshold)&&(workload_B<cur_workload))
        {
            /////////////
            /*printf("\nlabel_B:::");
            for(i=0; i<=end+1; i++)
                printf("%d",label_B[i]);
            printf("\n");*/
            /////////////
            recursive_bisection(label_B,end+1,part,&new_part,w_B,s_B,workload_B,threshold,forbidden);
            part=new_part;
        }
        else
        {
            //printf("3333333333333333\n");
            //printf("%d\n",part);
            /*printf("worker:::\n");
            for(i=0; i<M; i++)
            {
                if((part->worker)[i])
                    printf("%d ",i);
            }
            printf("\ntask:::\n");
            for(i=0; i<N; i++)
            {
                if((part->task)[i])
                    printf("%d ",i);
            }
            printf("\nlabel:::\n");
            for(i=0; i<=part->end; i++)
            {
                printf("%d ",(part->label)[i]);
            }
            printf("\n");*/
            //将划分B插入划分队列
            part->next=(struct partition *)malloc(sizeof(struct partition));
            //printf("666666666666666\n");
            part=part->next;
//printf("444444444444444\n");
            part->worker=(int *)malloc(M*sizeof(int));
            part->task=(int *)malloc(N*sizeof(int));
            part->label=(int *)malloc(N*sizeof(int));
//printf("5555555555555555\n");
            //将w_B的内容进行复制
            for(i=0; i<M; i++)
                (part->worker)[i]=w_B[i];
            //将s_B的内容复制
            for(i=0; i<N; i++)
                (part->task)[i]=s_B[i];
            //复制workload_B
            part->workload=workload_B;
            //复制label_B
            for(i=0; i<=(end+1); i++)
                (part->label)[i]=label_B[i];
            //更新end
            part->end=end+1;
            part->next=NULL;
            *new_part_addr=part;
            ////////////////////////////////////
            /*printf("worker:::\n");
            for(i=0; i<M; i++)
            {
                if((part->worker)[i])
                    printf("%d ",i);
            }
            printf("\ntask:::\n");
            for(i=0; i<N; i++)
            {
                if((part->task)[i])
                    printf("%d ",i);
            }
            printf("\nlabel:::\n");
            for(i=0; i<=part->end; i++)
            {
                printf("%d ",(part->label)[i]);
            }
            printf("\n");*/
        }
    }
    //////////////////////
    /*printf("\nbefore free label_A:::");
    for(i=0; i<=end+1; i++)
        printf("%d",label_A[i]);
    printf("\n");
    printf("\nbefore free label_B:::");
    for(i=0; i<=end+1; i++)
        printf("%d",label_B[i]);
    printf("\n");
    printf("%d:::\n",label_A);
    printf("%d:::\n",label_B);*/
    //////////////////////


    free(w_A);
    free(w_B);
    free(s_A);
    free(s_B);
    free(label_A);
    free(label_B);
    /*printf("\nafter free label_B:::");
    for(i=0; i<=end+1; i++)
        printf("%d",label_B[i]);
    printf("\n");*/
    return ;
}


//这个函数用来判断两个partition是否是可以合并的
//输入变量：left，right都是partition
//如果可以合并，返回1；否则，返回0
int compare(struct partition *left,struct partition *right)
{
    int i;

    if(left->end==right->end)//如果二者的label位数相等
    {
        for(i=0; i<left->end; i++)
        {
            if((left->label)[i]!=(right->label)[i])
                return 0;
        }
        return 1;
    }
    else
        return 0;
}

//这个函数用来将各个partition进行合并
//输入变量：
//part：存储partition的链表的头结点，这一定义与recursive_bisection中的不同
//threshold：阈值，每一个partition的workload不能超过这一值
//forbidden：禁止边集
//////////////region：定义同之前的函数，二维矩阵
//输出：
//一个合并后的partition，存储在part指向的链表的首位
void bottom_up_merging(struct partition *part,int threshold,int *forbidden)
{
    struct partition *left,*right,*last,*p;
    //int merge_w[100],merge_s[100],merge_workload;
    int *merge_w,*merge_s,merge_workload;
    int i;
    int end;

    merge_w=(int *)malloc(M*sizeof(int));
    merge_s=(int *)malloc(N*sizeof(int));

    p=part->next;
    while(((part->next)->next)!=NULL)//当列表中至少还存在两个划分的时候
    {
        last=part;

        //寻找可以进行合并的两个partition
        left=part->next;
        right=left->next;
        while(right!=NULL)
        {
            if(compare(left,right))//如果left，right这两个partition的label符合合并的要求
                break;
            last=left;
            left=right;
            right=right->next;
        }
        //合并worker集和任务集
        for(i=0; i<M; i++)
        {
            merge_w[i]=(left->worker)[i]||(right->worker)[i];
        }
        for(i=0; i<N; i++)
        {
            merge_s[i]=(left->task)[i]||(right->task)[i];
        }
        //计算workload，并检查是否符合要求
        merge_workload=cal_workload(merge_w,merge_s,forbidden);
        if(merge_workload>threshold)
        {
            //////////////////////////////////////////////
            printf("left:::::\n");
            for(i=0; i<M; i++)
            {
                if((left->worker)[i])
                    printf("%d ",i);
            }
            printf("\n");
            printf("right:::::\n");
            for(i=0; i<M; i++)
            {
                if((right->worker)[i])
                    printf("%d ",i);
            }
            printf("\n");
            printf("left task:::::\n");
            for(i=0; i<N; i++)
            {
                if((left->task)[i])
                    printf("%d ",i);
            }
            printf("\n");
            printf("right task:::::\n");
            for(i=0; i<N; i++)
            {
                if((right->task)[i])
                    printf("%d ",i);
            }
            printf("\n");
            printf("left workload :::%d\n",left->workload);
            printf("right workload :::%d\n",right->workload);
            //////////////////////////////////////////////
            GALS(left->worker,left->task,M,N,forbidden);
            GALS(right->worker,right->task,M,N,forbidden);
            //构造新的合并后的partition
            //合并worker集和任务集
            for(i=0; i<M; i++)
            {
                merge_w[i]=(left->worker)[i]||right->worker[i];
            }
            for(i=0; i<N; i++)
            {
                merge_s[i]=(left->task)[i]||(right->task)[i];
            }
            merge_workload=cal_workload(merge_w,merge_s,forbidden);
        }
        //将新的partition插入划分链表，并更新合并后的label和end
        last->next=(struct partition *)malloc(sizeof(struct partition));
        p=last->next;
        p->next=right->next;

        p->worker=(int *)malloc(M*sizeof(int));
        p->task=(int *)malloc(N*sizeof(int));
        p->label=(int *)malloc(N*sizeof(int));
        end=left->end-1;
        for(i=0; i<=end; i++)
        {
            (p->label)[i]=(left->label)[i];
        }
        p->end=end;
        p->workload=merge_workload;
        for(i=0; i<M; i++)
        {
            (p->worker)[i]=merge_w[i];
        }
        for(i=0; i<N; i++)
        {
            (p->task)[i]=merge_s[i];
        }
        //释放空间
        free(left->task);
        free(left->worker);
        free(left->label);
        free(right->task);
        free(right->worker);
        free(right->label);
        free(left);
        free(right);
    }
    free(merge_s);
    free(merge_w);
}


//这个函数是用来实现BisectionLALS算法的
//W：worker集，一维数组，维数为M
//S: 任务集，一维数组，维数为N
//threshold：阈值，用于GALS算法的partition的workload不能超过这一值
//forbidden: 禁止边集
void BisectionLALS(int *W,int *S,int threshold,int *forbidden,int *cur_w,int *cur_s)
{
    //int cur_w[100],cur_s[100];
    //int *cur_w,*cur_s;
    int i;
    int cur_workload;
    struct partition part,*new_part;
    struct partition *p;
    //int label[100],end=0;
    int *label,end=0;

    /*cur_w=(int *)malloc(M*sizeof(int));
    cur_s=(int *)malloc(N*sizeof(int));*/
    label=(int *)malloc(N*sizeof(int));

    //初始化
    cur_workload=cal_workload(W,S,forbidden);
    for(i=0; i<M; i++)
        cur_w[i]=W[i];
    for(i=0; i<N; i++)
        cur_s[i]=S[i];
    label[0]=0;

    while(cur_workload>threshold)
    {
        recursive_bisection(label,end,&part,&new_part,cur_w,cur_s,cur_workload,threshold,forbidden);
        //////////////////////////
        for(p=part.next; p!=NULL; p=p->next)
        {
            printf(":::::::partition::::\n");
            //fprintf(ff,":::::::partition::::\n");
            printf("worker:::\n");
            //fprintf(ff,":::::::partition::::\n");
            for(i=0; i<M; i++)
            {
                if((p->worker)[i])
                {
                    printf("%d ",i);
                    //fprintf(ff,"%d ",i);
                }
            }
            printf("\ntask:::\n");
            //fprintf(ff,"\ntask:::\n");
            for(i=0; i<N; i++)
            {
                if((p->task)[i])
                {
                    printf("%d ",i);
                    //fprintf(ff,"%d ",i);
                }
            }
            printf("\nlabel:::\n");
            //fprintf(ff,"\nlabel:::\n");
            for(i=0; i<=p->end; i++)
            {
                printf("%d ",(p->label)[i]);
                //fprintf(ff,"%d ",(p->label)[i]);
            }
            printf("\nworkload:::\n");
            //fprintf(ff,"\nworkload:::\n");
            printf("%d\n",p->workload);
            //fprintf(ff,"%d\n",p->workload);
        }
        //////////////////////////
        bottom_up_merging(&part,threshold,forbidden);

        //////////////////////////
        /*for(p=part.next; p!=NULL; p=p->next)
        {
            printf("worker:::\n");
            for(i=0; i<M; i++)
            {
                if((p->worker)[i])
                    printf("%d ",i);
            }
            printf("\ntask:::\n");
            for(i=0; i<N; i++)
            {
                if((p->task)[i])
                    printf("%d ",i);
            }
            printf("\nlabel:::\n");
            for(i=0; i<=p->end; i++)
            {
                printf("%d ",(p->label)[i]);
            }
            printf("\n");
        }*/

        //////////////////////////


        //更新cur_w，cur_s，cur_workload
        p=part.next;
        for(i=0; i<M; i++)
        {
            cur_w[i]=(p->worker)[i];
        }
        for(i=0; i<N; i++)
        {
            cur_s[i]=(p->task)[i];
        }
        cur_workload=cal_workload(cur_w,cur_s,forbidden);
        free(p->task);
        free(p->worker);
        free(p->label);
        free(p);
    }

    if(cur_workload>0)
        GALS(cur_w,cur_s,M,N,forbidden);

    //释放空间
    //free(cur_s);
    //free(cur_w);
    free(label);
}


///////////////////////////////////////////////////////////////////////////
//这一部分用来初始化司机位置，无关计算
double* gravity(int n)
{
    int i,all;
    double *result;
    result=(double *)malloc(2*sizeof(double));
    for(i=0,result[0]=0,result[1]=0,all=0;i<R;i++)
    {
        if(COLOR[i]==n)
        {
            result[0]=result[0]+Rplace[2*i];
            result[1]=result[1]+Rplace[2*i+1];
            all=all+1;
        }
    }
    result[0]=result[0]/(all*1.00);
    result[1]=result[1]/(all*1.00);
    return result;
}

int renovate(double k,double b,int n,int m)
{
    int i;
    int all;
    for(i=0;i<R;i++)
    {
        if(COLOR[i]==(n+1))
        {
            COLOR[i]=n;
        }
    }
    for(i=0,all=0;i<R;i++)
    {
        if(COLOR[i]==n)
        {
            if(Rplace[2*i+1]>k*Rplace[2*i]+b)
            {
                COLOR[i]=m;
                all=all+1;
            }
        }
    }
    return all;
}

void separate(double xg,double yg,int n,int num,int Rnum)
{
    int k,num1,num2;
    double tmpnum;
    double i,b,a,x1,y1,dis,max,maxnum,x2,y2;
    double *tmp;
    int l;
    max=0;
    if(num==1)
    {
        tmp=gravity(n);
        initp[n].x=tmp[0];
        initp[n].y=tmp[1];
        initp[n].i=n;
        return;
    }
    for(i=0;i<10;i++)
    {
        b=yg-i*xg;
        k=renovate(i,b,n,n+1);
        tmp=gravity(n+1);
        x1=tmp[0];
        y1=tmp[1];
        x2=(xg-x1)*k/(num-k)+xg;
        y2=(yg-y1)*k/(num-k)+yg;
        dis=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
        if(dis>max)
        {
            max=dis;
            maxnum=i;
        }
        free(tmp);
    }
    for(i=1;i<10;i++)
    {
        b=yg-1/i*xg;
        k=renovate(1/i,b,n,n+1);
        tmp=gravity(n+1);
        x1=tmp[0];
        y1=tmp[1];
        x2=(xg-x1)*k/(num-k)+xg;
        y2=(yg-y1)*k/(num-k)+yg;
        dis=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
        if(dis>max)
        {
            max=dis;
            maxnum=1/i;
        }
        free(tmp);
    }
    for(i=0;i<10;i++)
    {
        b=yg+i*xg;
        k=renovate(-i,b,n,n+1);
        tmp=gravity(n+1);
        x1=tmp[0];
        y1=tmp[1];
        x2=(xg-x1)*k/(num-k)+xg;
        y2=(yg-y1)*k/(num-k)+yg;
        dis=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
        if(dis>max)
        {
            max=dis;
            maxnum=-i;
        }
        free(tmp);
    }
    for(i=1;i<10;i++)
    {
        b=yg+1/i*xg;
        k=renovate(-1/i,b,n,n+1);
        tmp=gravity(n+1);
        x1=tmp[0];
        y1=tmp[1];
        x2=(xg-x1)*k/(num-k)+xg;
        y2=(yg-y1)*k/(num-k)+yg;
        dis=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
        if(dis>max)
        {
            max=dis;
            maxnum=-1/i;
        }
        free(tmp);
    }
    b=yg-maxnum*xg;
    k=renovate(maxnum,b,n,n);
    tmpnum=(k*1.00/Rnum*num);
    num1=(tmpnum-(int)tmpnum)*2+(int)tmpnum;
    num2=num-num1;
    if(num1==0)
    {
        num1++;
        num2--;
    }
    if(num2==0)
    {
        num1--;
        num2++;
    }
    k=renovate(maxnum,b,n,n+num2);
    tmp=gravity(n+num2);
    separate(tmp[0],tmp[1],n+num2,num1,k);
    free(tmp);
    tmp=gravity(n);
    separate(tmp[0],tmp[1],n,num2,Rnum-k);
    free(tmp);

}
void init_x_y()
{
    int i;
    double *tmp;
    for(i=0;i<R;i++)
    {
        COLOR[i]=0;
    }
    tmp=gravity(0);
    separate(tmp[0],tmp[1],0,M,R);
    free(tmp);
    return;
}

///////////////////////////////////////////////////////////////////////////
//这一部分用来寻找司机的当前位置
void get_x_y(struct path *last, struct path *temp_start, int i,int time)//得到当前时刻骑士i的具体位置
{
	double x0,x1,y0,y1;
	int id0,id1;
	double time0,time1,time2;

	time1=time;

	if(last!=NULL)
	{
		time0=last->atime;
		if(last->RorD==0)//餐厅
		{
			id0=last->id;//以下是为了获取前一个结点的x,y坐标
			x0=(double)(Rplace[2*id0]);
			y0=(double)(Rplace[2*id0+1]);
		}
		else if(last->RorD==1)//小区
		{
			id0=last->id;//以下是为了获取前一个结点的x,y坐标
			x0=(double)(Dplace[2*id0]);
			y0=(double)(Dplace[2*id0+1]);
		}
		else//路径中的转折点
		{
			x0=last->x;
			y0=last->y;
		}
	}
	else//骑士上一时刻的当前位置出发
	{
		time0=(curren+i)->time;
		//init_x_y(i, &x0, &y0);
		x0=(curren+i)->x;
		y0=(curren+i)->y;
	}

	if(temp_start==NULL)//说明此时正在从某一个结点回骑士的初始位置的路上
	{
		//init_x_y(i, &x1, &y1);
		x1=(initp+i)->x;
		y1=(initp+i)->y;
		time2=sqrt((x1-x0)*(x1-x0)+(y1-y0)*(y1-y0));
		if(time2>(time1-time0))//如果回到最初点的时间大于目前的时间间隔，说明还未回到最初点
		{
			(curren+i)->x=((x1-x0)/time2)*(time1-time0)+x0;
			(curren+i)->y=((y1-y0)/time2)*(time1-time0)+y0;
		}
		else//如果回到最初点的时间<=目前的时间间隔，说明已经回到最初点，正在等待订单
		{
			//init_x_y(i,&(curren->x),&(curren->y));
			(curren+i)->x=(initp+i)->x;
			(curren+i)->y=(initp+i)->y;
		}
	}
	else//说明此时正在从某一个结点或初始点到另一个结点的路上
	{

		if(temp_start->RorD==0)//如果下一个要去的结点是餐馆
		{
			id1=temp_start->id;
			x1=(double)(Rplace[2*id1]);
			y1=(double)(Rplace[2*id1+1]);
		}
		else if(temp_start->RorD==1)//下一个要去的结点是小区
		{
			id1=temp_start->id;
			x1=(double)(Dplace[2*id1]);
			y1=(double)(Dplace[2*id1+1]);
		}
		//if(last!=NULL)
		//	time2=distance(last,temp_start);
		//else//从初始点出发
		time2=sqrt((x1-x0)*(x1-x0)+(y1-y0)*(y1-y0));
		(curren+i)->x=((x1-x0)/time2)*(time1-time0)+x0;
		(curren+i)->y=((y1-y0)/time2)*(time1-time0)+y0;
	}
}


int find_start(int i,int time)//从骑士路径的头部开始，寻找当前时刻骑士i未经过的第一个结点，time是当前时刻
{
	struct path *last=NULL;
	struct path *temp_start=(cous+i)->first;
	struct path *p,*q;
	int j=0;
	double x1,y1,distance=1;

	if(temp_start==NULL)//这个骑士路径中并无订单
	{
	    (cous+i)->num=0;
	    (cous+i)->c=0;
		//init_x_y(i,&(curren->x),&(curren->y));
		if(time==WINDOW)//是初始的情况
		{
		    (curren+i)->x=(initp+i)->x;//initp是一个结构体数组，里面存的是每一个骑士应有的初始位置
            (curren+i)->y=(initp+i)->y;
            (curren+i)->num=0;//初始的情况车上坐了0个人
            //(curren+i)->x=0;//initp是一个结构体数组，里面存的是每一个骑士应有的初始位置
            //(curren+i)->y=0;
        }
        else//这个司机在上一轮迭代中没有接到单
        {
            x1=(curren+i)->x;
            y1=(curren+i)->y;
            //则司机正在赶回初始地点的路上
            get_x_y(last,temp_start,i,time);
            distance=sqrt((x1-(curren+i)->x)*(x1-(curren+i)->x)+(y1-(curren+i)->y)*(y1-(curren+i)->y));
            (cous+i)->distance=(cous+i)->distance+distance;

            (curren+i)->num=0;//目前车上没有人
        }
        (curren+i)->time=time;
        //将表示现在状态的结点插入到最终路线中
        if(distance!=0)
        {
            if((final_route+i)->first==NULL)//如果最终路线中还没有点
            {
                (final_route+i)->first=(struct path *)malloc(sizeof(struct path));
                (final_route+i)->p=(final_route+i)->first;
                q=(final_route+i)->p;

                //对表示现在状况的结点进行赋值
                q->atime=time;
                q->next=NULL;
                q->num=(curren+i)->num;
                q->x=(curren+i)->x;
                q->y=(curren+i)->y;
                q->RorD=2;
            }
            else
            {
                q=(final_route+i)->p;
                q->next=(struct path *)malloc(sizeof(struct path));
                q=q->next;
                (final_route+i)->p=q;

                //对表示现在状况的结点进行赋值
                q->atime=time;
                q->next=NULL;
                q->num=(curren+i)->num;
                q->x=(curren+i)->x;
                q->y=(curren+i)->y;
                q->RorD=2;
            }

            (cous+i)->key_place++;
        }

        //(cous+i)->key_place++;

        //printf("find start::cur time%f\n",(curren+i)->time);
		return 0;//表示第一个未经过的结点是第0个结点
	}

	while((temp_start!=NULL)&&((temp_start->atime)<=time))//过滤掉已经到达的点
	{
	    if((temp_start->RorD)==1)//如果经过的是一个终点，就表示下了一个人，车上的乘客减少了一人，空位多了一个
        {
            (cous+i)->c=((cous+i)->c)-1;
        }
        (cous+i)->num=((cous+i)->num)-1;

		last=temp_start;
		temp_start=temp_start->next;
		j++;//加完之后，表示temp_start现在是骑士已有路线中的第j个结点
	}

	if(temp_start==NULL)//说明当前时刻，骑士已经走完已有路线中的所有结点
	{
		(cous+i)->num=0;
		(cous+i)->c=0;
		get_x_y(last,temp_start,i,time);

		distance=curr_dis(i,last);
		(cous+i)->distance=(cous+i)->distance+distance;

		(curren+i)->time=time;
		(curren+i)->num=0;

		//释放空间,,现在变为将空间移到最终路线中
		if((final_route+i)->first==NULL)//如果最终路线中还没有点
        {
            (final_route+i)->first=(cous+i)->first;

        }
        else
        {
            ((final_route+i)->p)->next=(cous+i)->first;
        }

        for(p=(cous+i)->first; p!=temp_start; )
        {
            last=p;
            p=p->next;
            //free(last);
        }
        (final_route+i)->p=last;

		/*for(p=(cous+i)->first; p!=temp_start; )
        {
            if((final_route+i)->first==NULL)//如果最终路线中还没有点
            {
                (final_route+i)->first=p;
            }
            else
            {
                q=(final_route+i)->p;
                q->next=(struct path *)malloc(sizeof(struct path));
                q=q->next;
                (final_route+i)->p=q;

                //对表示现在状况的结点进行赋值
                q->atime=p->atime;
                q->ddl=p->ddl;
                q->id=p->id;
                q->next=p->next;
                q->number=p->number;
                q->num=p->num;
                q->RorD=p->RorD;
                q->x=p->x;
                q->y=p->y;
            }

            last=p;
            p=p->next;
            free(last);
        }*/

        //将表示现在状态的结点插入到最终路线中
        if((final_route+i)->first==NULL)//如果最终路线中还没有点
        {
            (final_route+i)->first=(struct path *)malloc(sizeof(struct path));
            (final_route+i)->p=(final_route+i)->first;
            q=(final_route+i)->p;

            //对表示现在状况的结点进行赋值
            q->atime=time;
            q->next=NULL;
            q->num=(curren+i)->num;
            q->x=(curren+i)->x;
            q->y=(curren+i)->y;
            q->RorD=2;
        }
        else
        {
            q=(final_route+i)->p;
            q->next=(struct path *)malloc(sizeof(struct path));
            q=q->next;
            (final_route+i)->p=q;

            //对表示现在状况的结点进行赋值
            q->atime=time;
            q->next=NULL;
            q->num=(curren+i)->num;
            q->x=(curren+i)->x;
            q->y=(curren+i)->y;
            q->RorD=2;
        }
        (cous+i)->key_place++;

        (cous+i)->first=temp_start;
		return j;//j表示这个空结点是当前路径中的第几个结点
	}

	get_x_y(last,temp_start,i,time);
    (curren+i)->time=time;

    //计算司机在当前位置车上的乘客数
    if(last!=NULL)
        (curren+i)->num=last->num;


    //释放空间，，，先改为将要释放的空间移动到最终路线中，而不释放
    if((final_route+i)->first==NULL)//如果最终路线中还没有点
    {
        if(last!=NULL)
            (final_route+i)->first=(cous+i)->first;

    }
    else
    {
        if(last!=NULL)
            ((final_route+i)->p)->next=(cous+i)->first;
    }

    for(p=(cous+i)->first; p!=temp_start; )
    {
        last=p;
        p=p->next;
        //free(last);
    }
    if(last!=NULL)
        (final_route+i)->p=last;

    //将表示现在状态的结点插入到最终路线中
    if((final_route+i)->first==NULL)//如果最终路线中还没有点
    {
        (final_route+i)->first=(struct path *)malloc(sizeof(struct path));
        (final_route+i)->p=(final_route+i)->first;
        q=(final_route+i)->p;

        //对表示现在状况的结点进行赋值
        q->atime=time;
        q->next=NULL;
        q->num=(curren+i)->num;
        q->x=(curren+i)->x;
        q->y=(curren+i)->y;
        q->RorD=2;
    }
    else
    {
        q=(final_route+i)->p;
        q->next=(struct path *)malloc(sizeof(struct path));
        q=q->next;
        (final_route+i)->p=q;

        //对表示现在状况的结点进行赋值
        q->atime=time;
        q->next=NULL;
        q->num=(curren+i)->num;
        q->x=(curren+i)->x;
        q->y=(curren+i)->y;
        q->RorD=2;
    }
    (cous+i)->key_place++;

    /*for(p=(cous+i)->first; p!=temp_start; )
    {
        //last=p;
        //p=p->next;
        //free(last);
    }*/

    (cous+i)->first=temp_start;
	//if(i==35)
	//	fprintf(ff,"%lf %lf %lf\n",curren->time,curren->x,curren->y);
	return j;//j表示当前路径中的第j个结点是骑士未经过的第一个结点
}

//w是worker的编号，从0开始
void printpath(int w)
{
    struct route *cour;
    struct path *temp;
    int *food;
    int i;

    cour=final_route+w;
    food=(int *)malloc(C*sizeof(int));

    for(i=0;i<C;i++)
        food[i]=-1;
    printf("%d %d\n",w+1,(cous+w)->key_place);
	fprintf(ff,"%d %d\n",w+1,(cous+w)->key_place);////////////

    for(temp=cour->first;temp!=NULL;temp=temp->next)
    {
        if(temp->RorD==0)//restaurant
        {
            printf("%d %d ",Rplace[(temp->id)*2],Rplace[(temp->id)*2+1]);
			fprintf(ff,"%d %d ",Rplace[(temp->id)*2],Rplace[(temp->id)*2+1]);////////////////
            for(i=0;i<C;i++)//store C orders in food[]
                if(food[i]==-1)
                {
                    food[i]=temp->number+1;
                    break;
                }
        }
        else if(temp->RorD==1)//communnity
        {
            printf("%d %d ",Dplace[(temp->id)*2],Dplace[(temp->id)*2+1]);
			fprintf(ff,"%d %d ",Dplace[(temp->id)*2],Dplace[(temp->id)*2+1]);//////////////////////////
            for(i=0;i<C;i++)
                if(food[i]==temp->number+1)//take the order out of food[]
                {
                    food[i]=-1;
                    break;
                }

        }
		else//只是路径中的转折点
		{
			printf("%lf %lf ",temp->x,temp->y);
			fprintf(ff,"%lf %lf ",temp->x,temp->y);//////////////////////////
		}

        printf("%lf %lf %d ",temp->atime,temp->atime,temp->num);
		fprintf(ff,"%lf %lf %d ",temp->atime,temp->atime,temp->num);///////////////////////
        for(i=0;i<C;i++)
            if(food[i]!=-1)
            {
				printf("%d ",food[i]);
				fprintf(ff,"%d ",food[i]);///////////////////
			}
        printf("\n");
		fprintf(ff,"\n");/////////////////
    }
    free(food);
}


int umain(char *s)
{
    FILE *fp;
    int *forbidden;
    int threshold;
    int *W,*S,*cur_w,*cur_s;
    int i,j;
    int n,num_w;
    int ind;
    double x1,x2,y1,y2,distance,sum=0;
    int time=WINDOW;//记录时刻，用于迭代
    int time1;
    int flag=0;//用来检查是否满足程序退出的条件
    //int flag1=0;//用来判断是否有bisection partition的必要
    int *startplace;
    struct path *p,*last;

    //打开文件
    //ff=fopen("result.txt","w");
    fp=fopen(s,"r");

    //初始化个数
    fscanf(fp,"%d %d %d %d %d",&R,&D,&M,&C,&N);
    n=N+M+2;
    num_w=M;
    //申请空间
    cous=(struct courier *)malloc(M*sizeof(struct courier));
    Nplace=(struct order *)malloc(N*sizeof(struct order));
    Rplace=(int *)malloc(2*R*sizeof(int));
    Dplace=(int *)malloc(2*D*sizeof(int));
    RR=(double *)malloc(R*R*sizeof(double));
    RD=(double *)malloc(R*D*sizeof(double));
    DD=(double *)malloc(D*D*sizeof(double));
    Q=(int *)malloc(M*sizeof(int));
    region=(int *)malloc((N+M+2)*(N+M+2)*sizeof(int));
    forbidden=(int *)malloc((N+M+2)*(N+M+2)*sizeof(int));
    W=(int *)malloc(M*sizeof(int));
    S=(int *)malloc(N*sizeof(int));
    cur_w=(int *)malloc(M*sizeof(int));
    cur_s=(int *)malloc(N*sizeof(int));
    curren=(struct current *)malloc(M*sizeof(struct current));
    startplace=(int *)malloc(M*sizeof(int));//
	COLOR=(int *)malloc(R*sizeof(int));
    initp=(struct init_place *)malloc(M*sizeof(struct init_place));
    final_route=(struct route *)malloc(M*sizeof(struct route));

    MAX=0;
    MAXDIR=0;

    //初始化
    for(i=0; i<M; i++)
    {
        Q[i]=C;
        W[i]=0;
    }
    for(i=0; i<N; i++)
    {
        S[i]=0;
    }

    for(i=0;i<R;i++){
        fscanf(fp,"%d %d",Rplace+2*i,Rplace+2*i+1);
    }
    for(i=0;i<D;i++)//store communities' position
        fscanf(fp,"%d %d",Dplace+2*i,Dplace+2*i+1);
    for(i=0;i<N;i++)//store orders'information
    {
        fscanf(fp,"%lf %d %d",&((Nplace+i)->time),&((Nplace+i)->rid),&((Nplace+i)->did));/////////改了time的读入格式
        (Nplace+i)->rid--;//restaurant id
        (Nplace+i)->did--;//community id
        (Nplace+i)->time=(Nplace+i)->time;//when an order appears
    }

    for(i=0;i<R;i++)//calculate the distance between 2 res
        for(j=i;j<R;j++)
        {
            rr(i,j)=sqrt((Rplace[2*i]-Rplace[2*j])*(Rplace[2*i]-Rplace[2*j])+(Rplace[2*i+1]-Rplace[2*j+1])*(Rplace[2*i+1]-Rplace[2*j+1]));
            rr(j,i)=rr(i,j);
        }
    for(i=0;i<D;i++)//calculate the distance between 2 com
        for(j=i;j<D;j++)
        {
            dd(i,j)=sqrt((Dplace[2*i]-Dplace[2*j])*(Dplace[2*i]-Dplace[2*j])+(Dplace[2*i+1]-Dplace[2*j+1])*(Dplace[2*i+1]-Dplace[2*j+1]));
            dd(j,i)=dd(i,j);
        }
    for(i=0;i<R;i++)//calculate the distance between a res and a com
        for(j=0;j<D;j++)
            rd(i,j)=sqrt((Rplace[2*i]-Dplace[2*j])*(Rplace[2*i]-Dplace[2*j])+(Rplace[2*i+1]-Dplace[2*j+1])*(Rplace[2*i+1]-Dplace[2*j+1]));

    for(i=0;i<M;i++)//init a courier's route, and the longest waiting time of his customers
    {
        (cous+i)->num=0;
        (cous+i)->first=NULL;
        (cous+i)->c=0;
        (cous+i)->distance=0;
        (cous+i)->key_place=0;
        //(cous+i)->maxtime=0;
    }

    for(i=0; i<M; i++)
    {
        (final_route+i)->first=NULL;
        (final_route+i)->p=NULL;
    }

    //计算每个司机的初始位置
    //if(M<R)
        //init_x_y();
    //else
    //{
        for(i=0;i<M;i++)
        {
            initp[i].x=Rplace[2*(i%R)];
            initp[i].y=Rplace[2*(i%R)+1];
            initp[i].i=i;
        }
    //}


    //设置threshold
    threshold=THRE_VAL;//需要解一个方程来算出具体的值，这里假设订单总数为3000，司机数为50，因此workload最初为50*3000，再仿照论文中结果的比例，定出了200的值

    while(1)//每隔一段时间（一个时间窗口）进行一次迭代计算，时间窗口的大小为WINDOW
    {
        flag=0;
        //flag1=0;

        //每一个司机当前状态的计算，如果是WINDOW时刻，就初始化司机位置，否则，就根据司机的路径进行更新
        for(i=0; i<M; i++)
            find_start(i,time);

        ////////////////////////////////////////////
        /*for(i=0; i<M; i++)
        {
            printf("curren_%d:::::::\n",i);
            printf("x::%f\n",(curren+i)->x);
            printf("y::%f\n",(curren+i)->y);
            printf("time::%f\n",(curren+i)->time);
        }*/

        ////////////////////////////////////////////

        //更新worker集和任务集
        for(i=0; i<M; i++)
        {
            if((cous+i)->c<Q[i])
                W[i]=1;
        }

        for(i=0; i<N; i++)
        {
            time1=(Nplace+i)->time;
            if(time==WINDOW)
            {
                if(time1<=time)
                    S[i]=1;
            }
            else
            {
                if((time1>time-WINDOW)&&(time1<=time))
                    S[i]=1;
            }
        }

        /*printf("worker before cal::::::::::::::::\n");
        for(i=0; i<M; i++)
        {
            if(W[i])
                printf("%d ",i);
        }
        printf("\n");

        printf("task before cal::::::::::::::::\n");
        for(i=0; i<N; i++)
        {
            if(S[i])
                printf("%d ",i);
        }
        printf("\n");*/

        //检查是否还有任务没有被schedule，如果没有任务剩下了，就break，结束程序
        for(i=0; i<N; i++)
        {
            if((Nplace+i)->time>time)//还有单没下
            {
                flag=1;
                break;
            }
            if(S[i]&&(time<=(Nplace+i)->time+MAX_WAIT_PICK))//该用户还在等待
            {
                flag=1;
                break;
            }
        }
        if(flag==0)
            break;

        //forbidden的初始化
        for(i=0; i<n; i++)
        {
            for(j=0; j<n; j++)
            {
                forbidden[i*n+j]=0;//初始情况下没有任何边被禁止
                region[i*n+j]=0;
            }
        }
        //region的初始化
        for(i=1; i<=num_w; i++)
        {
            for(j=num_w+2; j<n; j++)
            {
                if(W[i-1]&&S[j-(num_w+2)])
                {
                    ind=(Nplace+j-(num_w+2))->rid;
                    x1=(curren+i-1)->x;
                    y1=(curren+i-1)->y;
                    x2=Rplace[2*ind];
                    y2=Rplace[2*ind+1];

                    distance=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
                    //printf("\nregion building:::%f %f; %f %f %f %d\n",x1,y1,x2,y2,distance,MAX_WAIT_PICK);
                    if(distance<=MAX_DIS)
                        region[i*n+j]=1;
                }
            }
        }
        /*printf("region:::\n");
        for(i=0; i<n; i++)
            {
                for(j=0;j<n;j++)
                {
                    printf("%d ",region[i*n+j]);
                }
                printf("\n");
            }*/

        /*for(i=0; i<n; i++)
        {
            for(j=0; j<n; j++)
            {
                if(region[i*n+j])
                {
                    flag1=1;
                    break;
                }
            }
            if(flag1)
                break;
        }
        if(flag1==0)
        {
            //更新当前时间
            time=time+WINDOW;
            continue;
        }*/

        //调用LALS
        BisectionLALS(W,S,threshold,forbidden,cur_w,cur_s);
        //更新S
        for(i=0; i<N; i++)
        {
            S[i]=cur_s[i];
            //printf("\ncur_s:::::\n");
            //if(cur_s[i])
                //printf("%d ",i);
        }
        //更新当前时间
        time=time+WINDOW;
    }

    //输出最终的路程加和值
    for(i=0; i<M; i++)
    {
        //fprintf(ff,"%d :: %f\n",i,(cous+i)->distance);
        sum=sum+(cous+i)->distance;
    }

    for(i=0; i<M; i++)
    {
        if((cous+i)->first!=NULL)//还有司机没走完该走的路线
        {
            if((final_route+i)->first==NULL)
                (final_route+i)->first=(cous+i)->first;
            else
            {
                p=(final_route+i)->p;
                p->next=(cous+i)->first;
            }
        }
    }

    for(i=0; i<M; i++)
        printpath(i);

    printf("\ntotal distance::::%f\n",sum);
    fprintf(ff,"%f\n",sum);

    //释放空间
    for(i=0; i<M; i++)
    {
        /*for(p=(cous+i)->first; p!=NULL; )
        {
            last=p;
            p=p->next;
            free(last);
        }*/
        for(p=(final_route+i)->first; p!=NULL; )
        {
            last=p;
            p=p->next;
            free(last);
        }
    }

    fclose(fp);
    //fclose(ff);
	free(DD);
	free(RR);
	free(RD);
	free(Nplace);
	free(Rplace);
	free(Dplace);
	free(COLOR);
	free(startplace);
	free(cous);
	free(initp);
	free(curren);
	free(Q);
	free(region);
	free(forbidden);
    free(W);
    free(S);
    free(cur_s);
    free(cur_w);

    return 0;
}


int main()
{
    ff=fopen("result.txt","w");
    //umain("data1.txt");
    umain("data2.txt");
    /*umain("data00.txt");
    umain("data01.txt");
    umain("data02.txt");
    umain("data03.txt");
    umain("data04.txt");
    umain("data05.txt");
    umain("data06.txt");
    umain("data07.txt");
    umain("data08.txt");
    umain("data09.txt");
    umain("data10.txt");
    umain("data11.txt");
    umain("data12.txt");
    umain("data13.txt");
    umain("data14.txt");
    umain("data15.txt");
    umain("data16.txt");
    umain("data17.txt");
    umain("data18.txt");
    umain("data19.txt");*/
    fclose(ff);
    return 0;
}
