#include<iostream>
#include<math.h>
#include<bitset>
#include<stdio.h>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include  <string.h>
#include  <sys/types.h>
using namespace std;
 unsigned long long int TABLE_SIZE = 107374185;

class HashNode
{
    public:
        long long int key;
        long long int value;
        HashNode(long long int key, long long int value)
        {
            this->key = key;
            this->value = value;
        }
};
class DeletedNode:public HashNode
{
    private:
        static DeletedNode *entry;
        DeletedNode():HashNode(-1, -1)
        {}
    public:
        static DeletedNode *getNode()
        {
            if (entry == NULL)
                entry = new DeletedNode();
            return entry;
        }
};
DeletedNode *DeletedNode::entry = NULL;

class HashMap
{
    private:
        HashNode **htable;
    public:
        HashMap()
        {
            htable = new HashNode* [TABLE_SIZE];
            for (int i = 0; i < TABLE_SIZE; i++)
            {
                htable[i] = NULL;
            }
        }

        ~HashMap()
        {
            for (long long int i = 0; i < TABLE_SIZE; i++)
            {
                if (htable[i] != NULL && htable[i] != DeletedNode::getNode())
                    delete htable[i];
            }
            delete[] htable;
        }
        /*
         * Hash Function
         */
        int HashFunc(long long int key)
        {
            return key % TABLE_SIZE;
        }
        /*
         * Insert Element at a key
         */
        void Insert(long long int key,long long  int value)
        {
            long long int hash_val = HashFunc(key);
            long long int init = -1;
            long long  int deletedindex = -1;
            while (hash_val != init && (htable[hash_val]
                            == DeletedNode::getNode() || htable[hash_val]
                            != NULL && htable[hash_val]->key != key))
            {
                if (init == -1)
                    init = hash_val;
                if (htable[hash_val] == DeletedNode::getNode())
                    deletedindex = hash_val;
                hash_val = HashFunc(hash_val + 1);
            }
            if (htable[hash_val] == NULL || hash_val == init)
            {
                if(deletedindex != -1)
                    htable[deletedindex] = new HashNode(key, value);
                else
                    htable[hash_val] = new HashNode(key, value);
            }
            if(init != hash_val)
            {
                if (htable[hash_val] != DeletedNode::getNode())
                {
                    if (htable[hash_val] != NULL)
                    {
                        if (htable[hash_val]->key == key)
                            htable[hash_val]->value = value;
                    }
                }
                else
                    htable[hash_val] = new HashNode(key, value);
            }
        }
        /*
         * Search Element at a key
         */
        int Search(int key)
        {
            long long int hash_val = HashFunc(key);
            long long int init = -1;
            while (hash_val != init && (htable[hash_val]
                            == DeletedNode::getNode() || htable[hash_val]
                            != NULL && htable[hash_val]->key != key))
            {
                if (init == -1)
                    init = hash_val;
                hash_val = HashFunc(hash_val + 1);
            }
            if (htable[hash_val] == NULL || hash_val == init)
                return -1;
            else
                return htable[hash_val]->value;
        }
        void Remove(int key)
        {
            long long int hash_val = HashFunc(key);
            long long int init = -1;
            while (hash_val != init && (htable[hash_val]
                            == DeletedNode::getNode() || htable[hash_val]
                            != NULL && htable[hash_val]->key != key))
            {
                if (init == -1)
                    init = hash_val;
                hash_val = HashFunc(hash_val + 1);
            }
            if (hash_val != init && htable[hash_val] != NULL)
            {
                delete htable[hash_val];
                htable[hash_val] = DeletedNode::getNode();
            }
        }


};
void entry();
void exit();
long long int search1(long long int n);
 void array_entries();
 void add_page(long long int n);
 void wait(long long int n,long long int i);
 void signal(long long int n,long long int i);
 long long int search_frame(long long int n);
 long long int search_unique(long long int n);
long long int p_size,choice,value,number1=0,number2=0,number3=0,number4=0,x,i,j,k,flag=0,f=0,frame[100000]={0},flag3=0,index=0;
long long int p_table1[1000000],p_table2[2][1024][1024],a[10000000];
int main()
{
     HashMap hash;
     long long int key=0;
     array_entries();
    printf("\t\t---Logical Address Space is 32 Kb----- \n");

    printf("\t\t---Physical Address Space is 44 Kb-----\n");
    printf("\t\t---Page Size is 4Kb----\n\n");

while(1)
{

    flag=0;
    printf("\nEnter integer value of 32-bit Logical binary address ");
    scanf("%lld",&value);
    if(hash.Search(value)==-1)
{
     for(i=0;i<1024;i++)
     {
         frame[i]=0;
     }

  for(index=0;index<2;index++)
{

     //printf("\t\t PROCESS%d IS EXECUTING\n",index);


     long long int LA[32];//The output array
    bitset<32> A=value;//A will hold the binary representation of N
     for( i=0,j=31;i<32;i++,j--)
    {
     //Assigning the bits one by one.
     LA[i]=A[j];
    }
    printf("\nAdress in bits is \n");
    for(i=0;i<32;i++)
    {
        printf("%lld",LA[i]);
    }
    for(i=0;i<10;i++)
    {
        number1=number1+pow(2,(9-i))*LA[i];
    }
    printf("\nFirst 10 bits which represent outer page table and corrosponding page-no are \n");
    for(i=0;i<10;i++)
    {
        printf("%lld",LA[i]);
    }
    printf(" -> %lld",number1);

    long long int h=9;
    for(j=10;j<20;j++)
    {
        number2=number2+(pow(2,h))*LA[j];
        h--;
    }
    
    long long int l=11;
    for(k=20;k<32;k++)
    {

         number3=number3+pow(2,l)*LA[k];
         l--;
    }

    for(i=0;i<20;i++)
    {
         number4=number4+(2^(19-i))*LA[i];
    }
    
        printf("\nSecondary Page table to be accessed is %lld ",number1);
        printf("\n Now the offset which we have to access inside secondary-page -> %lld is ->%lld ",number1,number2);
    
	      if(frame[p_table2[index][number1][number2]]==0)
          {
              printf("\nProcess P%d is executing \n",index);

            printf("\n Frame-no is %lld -> ",p_table2[index][number1][number2]);
            printf("\n Offset is -> %lld ",number3);
            printf("\n Complete Physical Address is -> %lld ",p_table2[index][number1][number2]+number3);

            wait(frame[p_table2[index][number1][number2]],index);

           hash.Insert(value,(p_table2[index][number1][number2]+number3));
          }
          else
          {
              printf("%lld  ",frame[p_table2[index][number1][number2]]);
              printf("\nFrame %d is already occupied by Process %d \n",p_table2[1-index][number1][number2],(1-index));
              printf("\nEnter 1 for ending Process's %d time\n Enter 2 for Continuing with Process   \n ",(1-index));
              scanf("%d",&choice);
              switch(choice)
              {
                  case 1:signal(frame[p_table2[1-index][number1][number2]],1-index);
                  printf("\nProcess%d is freed ",1-index);
                         wait(frame[p_table2[index][number1][number2]],index);
                         printf("\nProcess %d is executing \n",index);
                         printf("\n All Process Ends \n");
                        break;
                  case 2: printf("\n Still Process %d is executing %d ",(1-index));
                          break;
                  default: printf("\nWrong Choice Entered \n");
              }
          }

}
}
else
{
    printf("\nAddress Found in TLB \n");
    printf("Physical Address is -> %lld ",hash.Search(value));
}
}
}


void array_entries()
{

    for(i=0;i<1024;i++)
    {
        p_table1[i]=i;
        a[i]=-1;
        frame[i]=0;


    }
    srand((unsigned)time(NULL));

    for(i=0;i<1024;i++)
    {
        for(j=0;j<1024;j++)
        {
            long int random=rand()%1024;
            
                 p_table2[0][i][j]=random;
                
                 p_table2[1][i][j]=random;
            


        }
    }
}



void wait(long long int n,long long int i)
{
    frame[p_table2[i][number1][number2]]=1;// 1 indicates semaphore is locked
}
void signal(long long int n,long long int i )
{
    frame[p_table2[i][number1][number2]]=0;// 0 indicates semaphore is unlocked

}

