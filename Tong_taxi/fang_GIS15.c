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
#define MAX_DIS 23//������֮����ܴ��ڱߵ����ֱ�߾���

struct order{
    double time;
    int rid;
    int did;
};
struct path{
    int RorD;//1����С����0���������2��ʾ��ֻ��һ����ʾ·���е�ת�۵�Ľ��
    double atime;//����Ա����ʱ��
    double ltime;//����Ա�뿪ʱ��
    double dtime;//��Ӧ�Ķ����µ�ʱ��
    int id;//���������Ӧ��id
    int num;//��ǰ���ϵ�������
    int number;//��Ӧ�Ķ����Ķ�����
	double x;//��ǰ����x����
	double y;//��ǰ����y����
	double ddl;//�����̵ĵ�������������ʱ��
    struct path *next;
};

struct current//��¼��ǰʱ�̿��Ա����״̬����Ϣ
{
	double x;//��ǰʱ�̿��Ա��x����
	double y;//��ǰʱ�̿��Ա��y����
	double time;//���ڵ�ǰ״̬��ʱ�̣���Ϊ�뿪��һ���ʱ��
	int num;//��ǰ���Ա���ϵ�������
};

struct courier{
    struct path *first;
    struct path *tmp;
    double maxtime;
    double distance;
    int num;//number of places in this courier's route
    int c;//���˾���ĳ������˼����ˣ�ֻ�е�������³��ˣ����ֵ�Ż����
    int key_place;//���˾��·�Ͼ����˶��ٸ���
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
    int *label;//������¼������ִ��ڻ���������һ��λ��
    int end;//������¼label�й��ж���λ��Ч���֣�end�����һ����Ч���ֵ��±�
    struct partition *next;
};

struct route
{
    struct path *first;
    struct path *p;
};

//��������
int SIZE;
int R,D,M,C,N;
int *Q;//�洢ÿһ��˾���ĳ�ʼ����
int *region;//��ά���飬��¼worker������֮��Ӿ���ĽǶ������Ƿ�����б������Ŀ�����
double MAX,MAXDIR;
double *RR,*RD,*DD;
struct courier *cous;
struct current *curren;
struct order *Nplace;
int *Rplace,*Dplace,*COLOR;
FILE *ff;//
struct init_place *initp;
struct route *final_route;



//������������������ͼ
//c������
//f������
//n,m�ֱ���ԭͼ�ڽӾ��������������
void residual(int *c,int *f,int *resi,int *resi_c,int n,int *E)
{
    int i,j;
    int r;

    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            //�Ƚ��г�ʼ��
            resi[i*n+j]=0;
            resi_c[i*n+j]=0;

            if(E[i*n+j])//�����������ԭͼ�д��ڣ���������������
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

//������������Բ���ͼresi��������������������ҵ��յ�t�����Ϊ0��ʱ����ֹ����
//path�����洢·��,n��ͼ�ж�������ind�ǵ�ǰ������ı��
void visit(int *resi,int *path,int n,int ind)
{
    int i;
    int j;

    if(ind==0)//�����ǰ������յ�
        return ;

    for(i=0;i<n;i++)
    {
        if(resi[ind*n+i]&&(path[i]==-1))//�������ͼ�д��ڱߣ�ind��i��,�Ҷ���iδ�����ʹ�
        {
            path[i]=ind;
            if(i==0)
                return ;
                ////////////////////////////
            //printf("\nthis is path:::");
            //��������·���е�ƿ��ֵmin
            /*for(j=0;j<n;j++)//�Աߣ�head��tail�����в���
            {

                printf("%d ",path[j]);

            }*/
            //printf("\n");
            /////////////////////////
            visit(resi,path,n,i);
            if(path[0]!=-1)//�ҵ���һ������·��
                return ;
            path[i]=-1;
        }
    }

    path[ind]=-1;//����ǰ�ڵ�ָ��ɿ��Է���״̬����Ϊ����·���Ҳ����յ�
    return ;
}

//������������ڲ���ͼ��Ѱ������·��
//resi�ǲ���ͼ���ڽӾ���
//n������
//���ж���ı��˳��Ϊt������ͼ��ඥ�㣬s������ͼ�Ҳඥ��
//������ҵ�����·��������1�����򣬷���0
int find_augmenting_path(int *resi,int *path,int n,int w)
{
    int i;
    int j;
    /////////


    //��ʼ��path
    for(i=0;i<n;i++)
    {
        path[i]=-1;
    }
    path[w]=w;//���Ϊw�Ķ���Ϊ��ʼ��s

    //��s�������ڽӵ����DFS����
    for(i=0;i<n;i++)
    {
        if(resi[w*n+i])//�������ͼ�д���������
        {
            path[i]=w;
            /////////////////
            /*printf("\nthis maybe path:::");
            //��������·���е�ƿ��ֵmin
            for(j=0;j<n;j++)//�Աߣ�head��tail�����в���
            {

                printf("%d ",path[j]);

            }
            printf("\n");*/
////////////////
            visit(resi,path,n,i);
            if(path[0]!=-1)//�ҵ���һ������·��
                break;
            path[i]=-1;
        }
    }

    //////////


    if(path[0]!=-1)//�ҵ���һ������·��
       {///////////

            /*printf("\nthis is path:::");
            //��������·���е�ƿ��ֵmin
            for(i=0;i<n;i++)//�Աߣ�head��tail�����в���
            {

                printf("%d ",path[i]);

            }
            printf("\n");*/

        return 1;
       }
    else
        return 0;
}

//�����������������������
//f�ǵ�ǰ����c��������path���ҵ�������·��
//n�Ǿ��������
void augment(int *f,int *c,int *path,int n,int w,int *resi_c,int *E)
{
    int tail,head;
    int min=1000000;

    tail=0;//���յ㿪ʼѰ�ұ�

    //��������·���е�ƿ��ֵmin
    while(tail!=w)//�Աߣ�head��tail�����в���
    {
        head=path[tail];
        min=resi_c[head*n+tail]<min?resi_c[head*n+tail]:min;
        tail=head;
    }

    //���������޸�
    tail=0;//���յ㿪ʼѰ�ұ�
    while(tail!=w)//�Աߣ�head��tail�����в���
    {
        head=path[tail];
        if(E[head*n+tail])//�����������ԭ��ͬ��
            f[head*n+tail]=f[head*n+tail]+min;
        else
            f[head*n+tail]=f[head*n+tail]-min;
        tail=head;
    }
}

//�������������һ��������ͼ�������
//old_E�Ǵ�ƥ��Ķ���ͼ���ڽӾ��󣬾�����һ�����󣬶�����˳��Ϊt������ͼ��ඥ�㣬s������ͼ�Ҳඥ��
//n���ڽӾ��������
//w�Ƕ���ͼ���Ķ�������������ʼ��s��
//c��ÿ���ߵ�������cҲ��һ������
//f��ʾͼ��ÿ���ߵ�����
void max_flow(int *old_E,int n,int *c,int w,int *f)
{
    int *resi,*resi_c;//resi�洢����ͼ,resi_c�������ͼ������
    int *path;//�����洢����·��
    int i,j;
    /*temp=(int *)malloc(old_n*old_n*sizeof(int));*/

    resi=(int *)malloc(n*n*sizeof(int));
    resi_c=(int *)malloc(n*n*sizeof(int));
    path=(int *)malloc(n*sizeof(int));

    /*//��old_E�е����ݸ��Ƶ�temp��������
    for(i=0;i<old_n;i++)
    {
        for(j=0;j<old_m;j++)
        {
            temp[i*old_n+j]=old_E[i*old_n+j];
        }
    }*/

    //��ʼ��ͼ������Ϊ0
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            f[i*n+j]=0;
        }
    }

    //�õ�����ͼ
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


//���������������˾��w��ǰλ�õ����pick�ľ���
double curr_dis(int w,struct path *pick)
{
    double distance;
    double x1,x2,y1,y2;
    int ind;//��¼pick��Ӧ�ص�ı��

    if(pick==NULL)//���·������Ŀǰû����
        return 0;

    ind=pick->id;
    x1=(curren+w)->x;
    y1=(curren+w)->y;
    if(pick->RorD==0)//�ǽ��˵ص�
    {
        x2=Rplace[2*ind];
        y2=Rplace[2*ind+1];
    }
    else if(pick->RorD==1)//���³��ص�
    {
        x2=Dplace[2*ind];
        y2=Dplace[2*ind+1];
    }

    distance=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
    //printf("cur_dis:::%d %d %f %f %f %f %f\n",w,pick->number,distance,x1,x2,y1,y2);
    return distance;
}


//��������������������������֮��ľ���
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


//������������������s��ĳ����λ�ö���˾��w������·����˵�ǲ���feasible��
//par_rou��w���ڲ���λ��֮��ʣ�������·�ߣ�node�Ǵ����㣬td�ǲ�����������ʱ������
//���feasible������1�����򣬷���0
int check_feasible(struct path *par_rou,struct path *node,double td)
{
    struct path *p;

    //�ȼ����node�����Ƿ�feasible
    if((node->atime)>(node->ddl))
        return 0;

    //���node����λ�ú�Ľ���Ƿ�feasible
    for(p=par_rou;p!=NULL;p=p->next)
    {
        if((p->atime)+td>(p->ddl))
            return 0;
    }
    return 1;
}


//�����������Ϊ����s�ڹ�����w�����ж�����Ѱ�����ŵĲ���λ��
//����s�ַ�Ϊ���������񣬽�������s���������s������cost��ʱ�򣬽������������
//��s����w��˵��feasibleʱ������1�����򣬷���0
int find_best_insertion_place(int w,int s,double *min_cost,double *subcost,int *best_pos_start, int *best_pos_end)
{
    int i,j;
    struct courier *driver;
    struct order *serve;
    struct path *left,*right,*start,*end,*left2,*right2,*p;//start�洢����s�Ľ��˽�㣬end�洢s���յ���
    double cost,cost1;
    int flag=0;//������¼�ܷ��ҵ�һ��feasible�Ĳ������

    *min_cost=1000000;
    driver=cous+w;
    serve=Nplace+s;

    //��ʼ�����˽����յ���
    start=(struct path *)malloc(sizeof(struct path));
    end=(struct path *)malloc(sizeof(struct path));

    start->RorD=0;//1�����յ㣬0������㣨���˵ص㣩��2��ʾ��ֻ��һ����ʾ·���е�ת�۵�Ľ��
    start->dtime=serve->time;//��Ӧ�Ķ����µ�ʱ��
    start->id=serve->rid;//���������Ӧ��id
    start->number=s;//��Ӧ�Ķ����Ķ�����
    start->ddl=(serve->time)+MAX_WAIT_PICK;
    end->RorD=1;//1�����յ㣬0������㣨���˵ص㣩��2��ʾ��ֻ��һ����ʾ·���е�ת�۵�Ľ��
    end->dtime=serve->time;//��Ӧ�Ķ����µ�ʱ��
    end->id=serve->did;//���������Ӧ��id
    end->number=s;//��Ӧ�Ķ����Ķ�����
    end->ddl=(serve->time)+ARRI_DDL;

    //��w���й滮�е�ÿһ������λ�ý��в��볢��
    for(i=0; i<=driver->num; i++,left=right,right=((right==NULL)?NULL:right->next))
    {
        cost=0;

        //�����ڴ�λ�ò���֮�����ӵ�·�̿���
        if(i==0)//�׶�
        {
            right=driver->first;
            cost=curr_dis(w,start)+dis(start,driver->first)-curr_dis(w,driver->first);
            start->atime=(curren+w)->time+curr_dis(w,start);
        }
        else if(i==driver->num)//β��
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
        //�����λ����feasible��
        if(check_feasible(right,start,cost))
        {
            cost1=cost;

            //���յ�ӵ���в��볢��
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
                if(i<driver->num)//���startδ��β��
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
                else//start��β��
                {
                    cost=cost1+dis(start,end);
                    end->atime=start->atime+dis(start,end);
                }

                /////////////////////////////////////////////////////
                if(cost<0&&w==22)
                    printf("\nERROR::::::::::%f,%d,%d\n",cost,w,s);
                /////////////////////////////////////////////////////

                //����������λ���Ƿ�feasible
                if(check_feasible(right2,end,cost))
                {

                    //������С����
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

    //������Ӧֵ
    if(flag)
        return 1;
    else
        return 0;
}


//�������������˾��w������·���в�����
//w��˾����ţ�s�������ţ�pos_start�ǽ��˽��Ӧ�����λ�ã�pos_end���յ���Ӧ�����λ��
void insert_s(int w,int s,int pos_start,int pos_end,double cost,double subcost)
{
    struct courier *driver;
    struct path *start,*end,*left,*right;
    struct order *serve;
    int i,j;

    //��ʼ��
    driver=cous+w;
    serve=Nplace+s;
    start=(struct path *)malloc(sizeof(struct path));
    end=(struct path *)malloc(sizeof(struct path));

    start->RorD=0;//1�����յ㣬0������㣨���˵ص㣩��2��ʾ��ֻ��һ����ʾ·���е�ת�۵�Ľ��
    start->dtime=serve->time;//��Ӧ�Ķ����µ�ʱ��
    start->id=serve->rid;//���������Ӧ��id
    start->number=s;//��Ӧ�Ķ����Ķ�����
    start->ddl=(serve->time)+MAX_WAIT_PICK;
    end->RorD=1;//1�����յ㣬0������㣨���˵ص㣩��2��ʾ��ֻ��һ����ʾ·���е�ת�۵�Ľ��
    end->dtime=serve->time;//��Ӧ�Ķ����µ�ʱ��
    end->id=serve->did;//���������Ӧ��id
    end->number=s;//��Ӧ�Ķ����Ķ�����
    end->ddl=(serve->time)+ARRI_DDL;

    //�����˽�����
    for(i=0,right=driver->first; i<=driver->num; i++,left=right,right=((right==NULL)?NULL:right->next))
    {
        if(pos_start==i)
        {
            if(i==0)//�׶�
            {
                //��������
                start->next=driver->first;
                driver->first=start;
                //���µ���ʱ��
                start->atime=(curren+w)->time+curr_dis(w,start);
                //���µ��˽�㳵���м�����
                start->num=(curren+w)->num+1;
                break;
            }
            else
            {
                //��������
                start->next=right;
                left->next=start;
                //���µ���ʱ��
                start->atime=left->atime+dis(left,start);
                //���µ��˽�㳵���м�����
                start->num=left->num+1;
                break;
            }
        }
    }

    //���յ������
    for(j=i,left=start; j<=driver->num; j++,left=right,right=((right==NULL)?NULL:right->next))
    {
        if(j==pos_end)//�ҵ���Ҫ����ı�
        {
            //��������
            end->next=right;
            left->next=end;
            //���µ���ʱ���Լ����˽�㳵���м�����
            end->atime=left->atime+dis(left,end);
            end->num=left->num-1;
            if(right!=NULL)
            {
                right->atime=right->atime+cost;
            }

        }
        else if(j<pos_end)//��û�е�Ҫ����ı�
        {
            //���µ���ʱ���Լ����˽�㳵���м�����
            if(right!=NULL)
            {
                right->atime=right->atime+subcost;
                right->num=right->num+1;
            }
        }
        else//�Ѿ�����Ҫ����ı�
        {
            //���µ���ʱ��
            if(right!=NULL)
            {
                right->atime=right->atime+cost;
            }
        }
    }

    //����˾��·���ϵĽ����
    driver->num=driver->num+2;
    driver->c=driver->c+1;
    driver->key_place=driver->key_place+2;
}

//�������������ÿһ��w��worker�������䵽�����񼯽������Ų��뷽����ѡ����ʵʩ��ͬʱ��Ҫ��RWS��RTS��forbidden���и���
//w��worker���������˴��������������ʱ��ͬ
//n��f�ľ���γ��
//RWS�ǿɹ�����˾������RTS�ǻ����������񼯺ϣ�forbidden�ǽ�ֹ�߼�
void insert_scheduling(int *f,int w,int n,int *RWS,int *RTS,int *forbidden)
{
    int i,j;
    int pos_start,pos_end,min_pos_start,min_pos_end;
    int min_s;
    double cost,min_cost,subcost,min_subcost;
    int flag=0;//���Լ�¼����worker i���ԣ��Ƿ�������ɷ����δ���䣨�ų��޷�����ɹ��������

    for(i=1;i<w+1;i++)
    {
        //��worker i-1 ��·�߽��и���
        while(1)
        {
            flag=0;
            min_cost=1000000;

            for(j=w+2;j<n;j++)
            {
                if(f[i*n+j]>0)//���j-(w+2)�����Ǳ��������i-1(���)������Ա�Ļ�
                {
                    //printf("enter:%d %d\n",i-1,j-(w+2));
                    if(find_best_insertion_place(i-1,j-(w+2),&cost,&subcost,&pos_start,&pos_end))//������ҵ�����λ��
                    {
                        //printf("can insert:%d %d\n",i-1,j-(w+2));
                        flag=1;

                        //������С����ʱ�����
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

            f[i*n+min_s]=0;//���������֮�󣬾Ϳ��԰���Ӧ�ı�ɾ����
            RTS[min_s-(w+2)]=0;//������min_s-(w+2)��RTS��ɾȥ
            (cous+i-1)->distance=(cous+i-1)->distance+min_cost;
            //if(i-1==0)
                //printf("%f :::%f:::\n",min_cost,(cous+i-1)->distance);
        }

        //�Ѿ�û�������ܹ����뵽worker i-1 �Ķ�������
        //����forbidden
        for(j=w+2;j<n;j++)
        {
            if(f[i*n+j]>0)//���j-(w+2)�����Ǳ��������i-1(���)������Ա�Ļ�
            {
                forbidden[i*n+j]=1;
            }
        }
        //����RWS
        if((Q[i-1]-(cous+(i-1))->c)<=0)
            RWS[i-1]=0;//���˾�������Ѿ�û�п�λ������˾����RWS��ɾ��
    }
}


//�������������ÿһ��GALS�ĵ������֮����и��£�����һ���µĶ���ͼ
//RWS �ǻ������ٱ����������worker������һ��һά����
//RTS �ǻ���Ҫ���䵽worker���ϵ����񼯣���һ��һά����
//forbidden �ǽ�ֹ�߼���
//E ������һ�����º�Ķ���ͼ
//c ���Լ���Ӧ�������������
//E,c,forbidden ���Ǿ���ά��Ϊn
//n �����ж����������������ʱ����һ��
//w ��˾��������
void update_flow_network_and_assignment(int *RWS,int *RTS,int *forbidden,int n,int w,int *E,int *c)
{
    int i,j;

    //��ʼ��E,c����
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            E[i*n+j]=0;
            c[i*n+j]=0;
        }
    }

    //����һ���µĶ���ͼ
    for(i=1;i<=w;i++)//�����д�worker�����ı߽��в���
    {
        if(RWS[i-1])//���˾��i-1��RWS��
        {
            for(j=w+2;j<n;j++)//������������в���
            {
                if(RTS[j-(w+2)]&&(forbidden[i*n+j]!=1)&&region[i*n+j])
                {
                    E[i*n+j]=1;
                    c[i*n+j]=1;
                }
            }
        }
    }

    for(j=1;j<=w;j++)//�����д����s�����ı߽��д���
    {
        E[(w+1)*n+j]=RWS[j-1];
        c[(w+1)*n+j]=Q[j-1]-((cous+j-1)->c);//˾���ĳ��ϻ�ʣ������λ
    }

    for(i=w+2;i<n;i++)//�����д�����������յ�t�ı߽��в���
    {
        E[i*n]=RTS[i-(w+2)];
        c[i*n]=RTS[i-(w+2)];
    }
}


//�����������ִ��һ��GALS�㷨���ܹ�����һ��·���滮����
//���������RWS��RTS, num_n, num_s, Q
//RWS: �����worker�ļ��ϣ���һ��һά���飬ĳһ��Ϊ1��ʾ���Ϊ�����worker��RWS��
//RTS�����������ļ��ϣ���һ��һά���飬ĳһ��Ϊ1��ʾ���Ϊ�����������RTS��
//num_w����RWT��Ԫ�صĸ���
//num_s����RST��Ԫ�صĸ���
//forbidden: ���еĽ�ֹ�߼���
//·���滮�����洢��cous���������һ��ȫ�ֱ���
void GALS(int *RWS,int *RTS,int num_w,int num_s,int *forbidden)
{
    int i,j;
    int n;
    int *E,*f,*c;
    //int c[1000][1000];
    int flag=0;//���Լ�¼�Ƿ�ﵽ����ֹ����
    struct path *p;

    n=2+num_s+num_w;

    //����ռ�
    f=(int *)malloc(n*n*sizeof(int));//Ϊ��ͼ����ռ�
    E=(int *)malloc(n*n*sizeof(int));//Ϊ����ͼ�ڽӾ�������ռ�
    c=(int *)malloc(n*n*sizeof(int));//Ϊͼ�и�����������ռ�
    //forbidden=(int *)malloc(n*n*sizeof(int));//Ϊ��ֹ�߼�����ռ�

    update_flow_network_and_assignment(RWS,RTS,forbidden,n,num_w,E,c);//����ʣ���worker��������¶���ͼ�͸�������

    /*//��ʼ��forbidden����
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            forbidden[i*n+j]=0;//��ʼ�����û��һ���߱���ֹ
        }
    }*/

    //�������������ƥ��
    max_flow(E,n,c,num_w+1,f);

    //�ظ���schedulingֱ������ֹͣ
    while(1)
    {
        flag=0;

        insert_scheduling(f,num_w,n,RWS,RTS,forbidden);//���������

        update_flow_network_and_assignment(RWS,RTS,forbidden,n,num_w,E,c);//����ʣ���worker��������¶���ͼ�͸�������

        //ȷ���Ƿ�ﵽ����ֹ������ÿһ����RTS�е������Ƿ���E�л���worker�б�����
        for(j=num_w+2; j<n; j++)
        {
            for(i=1; i<=num_w; i++)
            {
                if(E[i*n+j])
                {
                    flag=1;//������һ�������п��ܱ����Ÿ�ĳ��˾��
                    break;
                }
            }
            if(flag)
                break;
        }
        if(flag)
            max_flow(E,n,c,num_w+1,f);//������������Ӷ���������
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
            //�ͷſռ�
            free(f);
            free(E);
            free(c);
            //free(forbidden);
            return ;
        }
    }
}

//������������ҳ�tmp_s�����к�seed��������ĵ㣬����ľ���ָ���Ƕ����Ľ��˽��֮��ľ���
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


//������������Ը�����worker�������񼯽���������Ļ���
//���������
//cur_w: ���ڵ�worker����ά��ΪM����һ��һά���飬ĳ��Ϊ1��ʾ���worker��worker����
//cur_s: ���ڵ����񼯣�ά��ΪN����һ��һά���飬ĳ��Ϊ1 ��ʾ���������������
//threshold: ��ֵ��ÿһ������֮��ļ����бߵ��������ܳ�����ֵ
//forbidden����ֹ�ߣ����ڶ���ͼ�в�����ֵıߣ���һ����ά����Ϊ1����ʾ�ñ߱���ֹ��
/////////////region��һ����ά���󣬱�ʾ���Ӿ����Զ������˵��worker������֮���Ƿ�����б������Ŀ����ԣ�Ϊ1����ʾ���Դ��ڱߣ���������worker�ķ�Χ��
//�����
//w_A:���ֳ����������֮һ��A��worker������һ��һά����
//s_A:���ֳ����������֮һ��A�����񼯣���һ��һά����
//ͬ����w_B��s_B
//s_A,w_A,...,cur_w,cur_s�Ŀռ��������ͷ��ڵ��ô˺����ĺ���������worker����ά��ΪM��server����ά��ΪN
void task_oriented_partition_generation(int *cur_w,int *cur_s,int threshold,int *forbidden,int *w_A,int *s_A,int *w_B,int *s_B)
{
    int i;
    struct ws_ts *WS,*TS,*p,*q,*p1,*q1;//���ɶ�̬����
    int s,d,seed;//seed�����洢��һ�λ����㷨������������
    int workload=0;
    int n=M+N+2;//����ͼ�еĶ���������˾����+������+��ʼ��+��ֹ��
    int w=M;//˾������
    //int tmp_w[100];//������¼��cur_w�е�˾���Ļ���������ǲ��ǻ���˾�����Կ��Ǽ���w_A��
    //int tmp_s[100];//������¼��cur_s�е�����Ļ��������ͬ��
    int *tmp_w;//������¼��cur_w�е�˾���Ļ���������ǲ��ǻ���˾�����Կ��Ǽ���w_A��
    int *tmp_s;//������¼��cur_s�е�����Ļ��������ͬ��
    int n_tmp_s=0;//��¼tmp_s��1������
    int n_tmp_w=0;//��¼tmp_w��1������

    //��ʼ��tmp_w,tmp_s
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

    //��ʼ��PWS��PTS��WS��TS��Ϊ��
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

    //�������еĵ�һ���������TS��,������������Ϊs
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
            tmp_s[s]=0;//��ʾ����s�Ѿ���������
            n_tmp_s--;
            break;
        }
    }

    while(1)
    {
        q=WS;

        //��ÿһ��TS�е�����sִ�����²�����
        for(p=TS->next; p!=NULL; p=p->next)
        {
            s=p->number;
            for(i=1; i<=w; i++)
            {
                if(region[i*n+s+(w+2)]&&(forbidden[i*n+s+(w+2)]!=1))//������worker�����������s
                {
                    if(cur_w[i-1]&&(w_A[i-1]!=1))//���˾��i-1��δ�����뵽w_A�У�����һ���·��ֵ�
                    {
                        //��˾��i-1���뵽WS������
                        q->next=(struct ws_ts *)malloc(sizeof(struct ws_ts));
                        q=q->next;
                        q->number=i-1;
                        q->next=NULL;
                        //��˾��i-1���뵽w_A��
                        w_A[i-1]=1;
                        //��workload��1
                        workload=workload+1;
                        //��˾��i-1��tmp_w��ȥ��
                        tmp_w[i-1]=0;
                        n_tmp_w--;
                    }
                }
            }
        }
        //���TS
        if(TS->next!=NULL)
        {
            for(p=TS->next,p1=p->next; p1!=NULL; p=p1,p1=p1->next)
                free(p);
            free(p);
        }
        TS->next=NULL;

        p=TS;

        //������WS�е�˾���������²���
        for(q=WS->next; q!=NULL; q=q->next)
        {
            d=q->number;//d�洢˾���ı��

{

}            for(i=w+2; i<n; i++)
            {
                if(region[(d+1)*n+i]&&(forbidden[(d+1)*n+i]!=1))//������������˾���ܵ���ķ�Χ��//�������Լ�����һ��Ķ�
                {
                    if(cur_s[i-(w+2)]&&(s_A[i-(w+2)]!=1))//�������i-��w+2������һ�ֵ����·��ֵ�
                    {
                        //������i-(w+2)����TS������
                        p->next=(struct ws_ts *)malloc(sizeof(struct ws_ts));
                        p=p->next;
                        p->number=i-(w+2);
                        p->next=NULL;
                        //������i-(w+2)����s_A��
                        s_A[i-(w+2)]=1;
                        //������i-(w+2)��tmp_s��ȥ��
                        if(tmp_s[i-(w+2)]!=0)
                        {
                            n_tmp_s--;
                            tmp_s[i-(w+2)]=0;
                        }
                    }
                }
            }
        }
        //���WS
        if(WS->next!=NULL)
        {
            for(q=WS->next,q1=q->next; q1!=NULL; q=q1,q1=q1->next)
                free(q);
            free(q);
        }
        WS->next=NULL;

        //����˳�����
        if((workload>=threshold)||(n_tmp_s==0)||(n_tmp_w==0))
        {
            //��w_B,s_B���ú�
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
            //���TS
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
        //���TSĿǰ�ǿյ�
        if(TS->next==NULL)
        {
            s=find_next_close_task(seed,tmp_s);
            TS->next=(struct ws_ts *)malloc(sizeof(struct ws_ts));
            p=TS->next;
            p->number=s;
            p->next=NULL;
            tmp_s[s]=0;//��ʾ����s�Ѿ���������
            n_tmp_s--;
        }

    }
}


//������������������ͼ�бߵ���Ŀ����������㵽worker�ıߺ�task���յ�ı�
//���������
//W: worker����
//S�����񼯺�
//forbidden����ֹ�߼���
///////////////region������ͬ��
//�����
//���������workload
int cal_workload(int *W,int *S,int *forbidden)
{
    int n,i,j,num,w;

    n=N+M+2;//����ľ��������
    w=M;//˾������

    for(num=0,i=1; i<=w; i++)//˾��i-1
    {
        for(j=w+2; j<n; j++)//����j-(w+2)
        {
            if(W[i-1]&&S[j-(w+2)]&&region[i*n+j]&&(forbidden[i*n+j]!=1))
                num++;
        }
    }
    return num;
}

//������������ݹ�ض�cur_w,cur_s���л���
//���������
//cur_w: ���е�˾�����ϣ�һ��һά���飬ά��ΪM
//cur_s�����е����񼯺ϣ�һ��һά���飬ά��ΪN
//cur_workload�����еĶ���ͼ�бߵ���������������㵽worker�ıߺ������յ�ı�
//threshold����ֵ��Ҫ�󻮷ֺ��ÿһ���Ӽ��бߵ��������������ֵ
//forbidden����ֹ�߼��ϣ�һ����ά���飬����ΪM+N+2
//////////////region��ͬtask_oriented_partition_generation�����еĶ��壬һ����ά��������ΪN+M+2
//part���ǽ�partition���������ĵ�ַ
//label: һά���飬������¼partition�ڻ������е�λ�ã���һ�ε��õ�ʱ��labelֻ����һ��0����λ
//end: ������¼label�����һλ��Ч���ֵ��±ꡣ��һ�ε��õ�ʱ�򣬴���������0
//����������part��һ�����У�part����������׵�ַ
void recursive_bisection(int *label,int end,struct partition *part_addr,struct partition **new_part_addr,int *cur_w,int *cur_s,int cur_workload,int threshold,int *forbidden)
{
    int theta;//������task_oriented_partition_generation�����Ľ�
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

    //����label
    for(i=0; i<=end; i++)
    {
        label_A[i]=label[i];
        label_B[i]=label[i];
    }
    label_A[end+1]=1;//��ʾA���������
    label_B[end+1]=2;//��ʾB�������Ҳ�

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
        //�����м��ϻ��ֳ�����
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

        workload_A=cal_workload(w_A,s_A,forbidden);//����workload
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
            //������A���뻮�ֶ���  add_into_partition(part,w_A,s_A,workload_A);
            part->next=(struct partition *)malloc(sizeof(struct partition));
            part=part->next;

            part->worker=(int *)malloc(M*sizeof(int));
            part->task=(int *)malloc(N*sizeof(int));
            part->label=(int *)malloc(N*sizeof(int));
            //��w_A�����ݽ��и���
            for(i=0; i<M; i++)
                (part->worker)[i]=w_A[i];
            //��s_A�����ݸ���
            for(i=0; i<N; i++)
                (part->task)[i]=s_A[i];
            //����workload_A
            part->workload=workload_A;
            //����label_A
            for(i=0; i<=(end+1); i++)
                (part->label)[i]=label_A[i];
            //����end
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

        workload_B=cal_workload(w_B,s_B,forbidden);//����workload
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
            //������B���뻮�ֶ���
            part->next=(struct partition *)malloc(sizeof(struct partition));
            //printf("666666666666666\n");
            part=part->next;
//printf("444444444444444\n");
            part->worker=(int *)malloc(M*sizeof(int));
            part->task=(int *)malloc(N*sizeof(int));
            part->label=(int *)malloc(N*sizeof(int));
//printf("5555555555555555\n");
            //��w_B�����ݽ��и���
            for(i=0; i<M; i++)
                (part->worker)[i]=w_B[i];
            //��s_B�����ݸ���
            for(i=0; i<N; i++)
                (part->task)[i]=s_B[i];
            //����workload_B
            part->workload=workload_B;
            //����label_B
            for(i=0; i<=(end+1); i++)
                (part->label)[i]=label_B[i];
            //����end
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


//������������ж�����partition�Ƿ��ǿ��Ժϲ���
//���������left��right����partition
//������Ժϲ�������1�����򣬷���0
int compare(struct partition *left,struct partition *right)
{
    int i;

    if(left->end==right->end)//������ߵ�labelλ�����
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

//�����������������partition���кϲ�
//���������
//part���洢partition�������ͷ��㣬��һ������recursive_bisection�еĲ�ͬ
//threshold����ֵ��ÿһ��partition��workload���ܳ�����һֵ
//forbidden����ֹ�߼�
//////////////region������֮ͬǰ�ĺ�������ά����
//�����
//һ���ϲ����partition���洢��partָ����������λ
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
    while(((part->next)->next)!=NULL)//���б������ٻ������������ֵ�ʱ��
    {
        last=part;

        //Ѱ�ҿ��Խ��кϲ�������partition
        left=part->next;
        right=left->next;
        while(right!=NULL)
        {
            if(compare(left,right))//���left��right������partition��label���Ϻϲ���Ҫ��
                break;
            last=left;
            left=right;
            right=right->next;
        }
        //�ϲ�worker��������
        for(i=0; i<M; i++)
        {
            merge_w[i]=(left->worker)[i]||(right->worker)[i];
        }
        for(i=0; i<N; i++)
        {
            merge_s[i]=(left->task)[i]||(right->task)[i];
        }
        //����workload��������Ƿ����Ҫ��
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
            //�����µĺϲ����partition
            //�ϲ�worker��������
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
        //���µ�partition���뻮�����������ºϲ����label��end
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
        //�ͷſռ�
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


//�������������ʵ��BisectionLALS�㷨��
//W��worker����һά���飬ά��ΪM
//S: ���񼯣�һά���飬ά��ΪN
//threshold����ֵ������GALS�㷨��partition��workload���ܳ�����һֵ
//forbidden: ��ֹ�߼�
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

    //��ʼ��
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


        //����cur_w��cur_s��cur_workload
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

    //�ͷſռ�
    //free(cur_s);
    //free(cur_w);
    free(label);
}


///////////////////////////////////////////////////////////////////////////
//��һ����������ʼ��˾��λ�ã��޹ؼ���
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
//��һ��������Ѱ��˾���ĵ�ǰλ��
void get_x_y(struct path *last, struct path *temp_start, int i,int time)//�õ���ǰʱ����ʿi�ľ���λ��
{
	double x0,x1,y0,y1;
	int id0,id1;
	double time0,time1,time2;

	time1=time;

	if(last!=NULL)
	{
		time0=last->atime;
		if(last->RorD==0)//����
		{
			id0=last->id;//������Ϊ�˻�ȡǰһ������x,y����
			x0=(double)(Rplace[2*id0]);
			y0=(double)(Rplace[2*id0+1]);
		}
		else if(last->RorD==1)//С��
		{
			id0=last->id;//������Ϊ�˻�ȡǰһ������x,y����
			x0=(double)(Dplace[2*id0]);
			y0=(double)(Dplace[2*id0+1]);
		}
		else//·���е�ת�۵�
		{
			x0=last->x;
			y0=last->y;
		}
	}
	else//��ʿ��һʱ�̵ĵ�ǰλ�ó���
	{
		time0=(curren+i)->time;
		//init_x_y(i, &x0, &y0);
		x0=(curren+i)->x;
		y0=(curren+i)->y;
	}

	if(temp_start==NULL)//˵����ʱ���ڴ�ĳһ��������ʿ�ĳ�ʼλ�õ�·��
	{
		//init_x_y(i, &x1, &y1);
		x1=(initp+i)->x;
		y1=(initp+i)->y;
		time2=sqrt((x1-x0)*(x1-x0)+(y1-y0)*(y1-y0));
		if(time2>(time1-time0))//����ص�������ʱ�����Ŀǰ��ʱ������˵����δ�ص������
		{
			(curren+i)->x=((x1-x0)/time2)*(time1-time0)+x0;
			(curren+i)->y=((y1-y0)/time2)*(time1-time0)+y0;
		}
		else//����ص�������ʱ��<=Ŀǰ��ʱ������˵���Ѿ��ص�����㣬���ڵȴ�����
		{
			//init_x_y(i,&(curren->x),&(curren->y));
			(curren+i)->x=(initp+i)->x;
			(curren+i)->y=(initp+i)->y;
		}
	}
	else//˵����ʱ���ڴ�ĳһ�������ʼ�㵽��һ������·��
	{

		if(temp_start->RorD==0)//�����һ��Ҫȥ�Ľ���ǲ͹�
		{
			id1=temp_start->id;
			x1=(double)(Rplace[2*id1]);
			y1=(double)(Rplace[2*id1+1]);
		}
		else if(temp_start->RorD==1)//��һ��Ҫȥ�Ľ����С��
		{
			id1=temp_start->id;
			x1=(double)(Dplace[2*id1]);
			y1=(double)(Dplace[2*id1+1]);
		}
		//if(last!=NULL)
		//	time2=distance(last,temp_start);
		//else//�ӳ�ʼ�����
		time2=sqrt((x1-x0)*(x1-x0)+(y1-y0)*(y1-y0));
		(curren+i)->x=((x1-x0)/time2)*(time1-time0)+x0;
		(curren+i)->y=((y1-y0)/time2)*(time1-time0)+y0;
	}
}


int find_start(int i,int time)//����ʿ·����ͷ����ʼ��Ѱ�ҵ�ǰʱ����ʿiδ�����ĵ�һ����㣬time�ǵ�ǰʱ��
{
	struct path *last=NULL;
	struct path *temp_start=(cous+i)->first;
	struct path *p,*q;
	int j=0;
	double x1,y1,distance=1;

	if(temp_start==NULL)//�����ʿ·���в��޶���
	{
	    (cous+i)->num=0;
	    (cous+i)->c=0;
		//init_x_y(i,&(curren->x),&(curren->y));
		if(time==WINDOW)//�ǳ�ʼ�����
		{
		    (curren+i)->x=(initp+i)->x;//initp��һ���ṹ�����飬��������ÿһ����ʿӦ�еĳ�ʼλ��
            (curren+i)->y=(initp+i)->y;
            (curren+i)->num=0;//��ʼ�������������0����
            //(curren+i)->x=0;//initp��һ���ṹ�����飬��������ÿһ����ʿӦ�еĳ�ʼλ��
            //(curren+i)->y=0;
        }
        else//���˾������һ�ֵ�����û�нӵ���
        {
            x1=(curren+i)->x;
            y1=(curren+i)->y;
            //��˾�����ڸϻس�ʼ�ص��·��
            get_x_y(last,temp_start,i,time);
            distance=sqrt((x1-(curren+i)->x)*(x1-(curren+i)->x)+(y1-(curren+i)->y)*(y1-(curren+i)->y));
            (cous+i)->distance=(cous+i)->distance+distance;

            (curren+i)->num=0;//Ŀǰ����û����
        }
        (curren+i)->time=time;
        //����ʾ����״̬�Ľ����뵽����·����
        if(distance!=0)
        {
            if((final_route+i)->first==NULL)//�������·���л�û�е�
            {
                (final_route+i)->first=(struct path *)malloc(sizeof(struct path));
                (final_route+i)->p=(final_route+i)->first;
                q=(final_route+i)->p;

                //�Ա�ʾ����״���Ľ����и�ֵ
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

                //�Ա�ʾ����״���Ľ����и�ֵ
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
		return 0;//��ʾ��һ��δ�����Ľ���ǵ�0�����
	}

	while((temp_start!=NULL)&&((temp_start->atime)<=time))//���˵��Ѿ�����ĵ�
	{
	    if((temp_start->RorD)==1)//�����������һ���յ㣬�ͱ�ʾ����һ���ˣ����ϵĳ˿ͼ�����һ�ˣ���λ����һ��
        {
            (cous+i)->c=((cous+i)->c)-1;
        }
        (cous+i)->num=((cous+i)->num)-1;

		last=temp_start;
		temp_start=temp_start->next;
		j++;//����֮�󣬱�ʾtemp_start��������ʿ����·���еĵ�j�����
	}

	if(temp_start==NULL)//˵����ǰʱ�̣���ʿ�Ѿ���������·���е����н��
	{
		(cous+i)->num=0;
		(cous+i)->c=0;
		get_x_y(last,temp_start,i,time);

		distance=curr_dis(i,last);
		(cous+i)->distance=(cous+i)->distance+distance;

		(curren+i)->time=time;
		(curren+i)->num=0;

		//�ͷſռ�,,���ڱ�Ϊ���ռ��Ƶ�����·����
		if((final_route+i)->first==NULL)//�������·���л�û�е�
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
            if((final_route+i)->first==NULL)//�������·���л�û�е�
            {
                (final_route+i)->first=p;
            }
            else
            {
                q=(final_route+i)->p;
                q->next=(struct path *)malloc(sizeof(struct path));
                q=q->next;
                (final_route+i)->p=q;

                //�Ա�ʾ����״���Ľ����и�ֵ
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

        //����ʾ����״̬�Ľ����뵽����·����
        if((final_route+i)->first==NULL)//�������·���л�û�е�
        {
            (final_route+i)->first=(struct path *)malloc(sizeof(struct path));
            (final_route+i)->p=(final_route+i)->first;
            q=(final_route+i)->p;

            //�Ա�ʾ����״���Ľ����и�ֵ
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

            //�Ա�ʾ����״���Ľ����и�ֵ
            q->atime=time;
            q->next=NULL;
            q->num=(curren+i)->num;
            q->x=(curren+i)->x;
            q->y=(curren+i)->y;
            q->RorD=2;
        }
        (cous+i)->key_place++;

        (cous+i)->first=temp_start;
		return j;//j��ʾ����ս���ǵ�ǰ·���еĵڼ������
	}

	get_x_y(last,temp_start,i,time);
    (curren+i)->time=time;

    //����˾���ڵ�ǰλ�ó��ϵĳ˿���
    if(last!=NULL)
        (curren+i)->num=last->num;


    //�ͷſռ䣬�����ȸ�Ϊ��Ҫ�ͷŵĿռ��ƶ�������·���У������ͷ�
    if((final_route+i)->first==NULL)//�������·���л�û�е�
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

    //����ʾ����״̬�Ľ����뵽����·����
    if((final_route+i)->first==NULL)//�������·���л�û�е�
    {
        (final_route+i)->first=(struct path *)malloc(sizeof(struct path));
        (final_route+i)->p=(final_route+i)->first;
        q=(final_route+i)->p;

        //�Ա�ʾ����״���Ľ����и�ֵ
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

        //�Ա�ʾ����״���Ľ����и�ֵ
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
	return j;//j��ʾ��ǰ·���еĵ�j���������ʿδ�����ĵ�һ�����
}

//w��worker�ı�ţ���0��ʼ
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
		else//ֻ��·���е�ת�۵�
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
    int time=WINDOW;//��¼ʱ�̣����ڵ���
    int time1;
    int flag=0;//��������Ƿ���������˳�������
    //int flag1=0;//�����ж��Ƿ���bisection partition�ı�Ҫ
    int *startplace;
    struct path *p,*last;

    //���ļ�
    //ff=fopen("result.txt","w");
    fp=fopen(s,"r");

    //��ʼ������
    fscanf(fp,"%d %d %d %d %d",&R,&D,&M,&C,&N);
    n=N+M+2;
    num_w=M;
    //����ռ�
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

    //��ʼ��
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
        fscanf(fp,"%lf %d %d",&((Nplace+i)->time),&((Nplace+i)->rid),&((Nplace+i)->did));/////////����time�Ķ����ʽ
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

    //����ÿ��˾���ĳ�ʼλ��
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


    //����threshold
    threshold=THRE_VAL;//��Ҫ��һ����������������ֵ��������趩������Ϊ3000��˾����Ϊ50�����workload���Ϊ50*3000���ٷ��������н���ı�����������200��ֵ

    while(1)//ÿ��һ��ʱ�䣨һ��ʱ�䴰�ڣ�����һ�ε������㣬ʱ�䴰�ڵĴ�СΪWINDOW
    {
        flag=0;
        //flag1=0;

        //ÿһ��˾����ǰ״̬�ļ��㣬�����WINDOWʱ�̣��ͳ�ʼ��˾��λ�ã����򣬾͸���˾����·�����и���
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

        //����worker��������
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

        //����Ƿ�������û�б�schedule�����û������ʣ���ˣ���break����������
        for(i=0; i<N; i++)
        {
            if((Nplace+i)->time>time)//���е�û��
            {
                flag=1;
                break;
            }
            if(S[i]&&(time<=(Nplace+i)->time+MAX_WAIT_PICK))//���û����ڵȴ�
            {
                flag=1;
                break;
            }
        }
        if(flag==0)
            break;

        //forbidden�ĳ�ʼ��
        for(i=0; i<n; i++)
        {
            for(j=0; j<n; j++)
            {
                forbidden[i*n+j]=0;//��ʼ�����û���κα߱���ֹ
                region[i*n+j]=0;
            }
        }
        //region�ĳ�ʼ��
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
            //���µ�ǰʱ��
            time=time+WINDOW;
            continue;
        }*/

        //����LALS
        BisectionLALS(W,S,threshold,forbidden,cur_w,cur_s);
        //����S
        for(i=0; i<N; i++)
        {
            S[i]=cur_s[i];
            //printf("\ncur_s:::::\n");
            //if(cur_s[i])
                //printf("%d ",i);
        }
        //���µ�ǰʱ��
        time=time+WINDOW;
    }

    //������յ�·�̼Ӻ�ֵ
    for(i=0; i<M; i++)
    {
        //fprintf(ff,"%d :: %f\n",i,(cous+i)->distance);
        sum=sum+(cous+i)->distance;
    }

    for(i=0; i<M; i++)
    {
        if((cous+i)->first!=NULL)//����˾��û������ߵ�·��
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

    //�ͷſռ�
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
