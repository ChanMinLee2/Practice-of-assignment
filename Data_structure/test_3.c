#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUM 100

typedef struct sinfo sinfo;  // �л������� �����ϴ� ����ü
struct sinfo
{
    char name[10];        // 4��
    char gender[8];
    char city[10];        // 4��
    char dept[20];        // 8��
    char gpa[10];
    char height[10];
    char weight[10];
};

// ���� ����ü Ÿ�� set ���� ���⿡ ����ü ���� �� ��������. 
typedef struct sset sset;
struct sset
{
    sinfo svalues[100];
    int count;
};

typedef struct smap smap;
struct smap
{
    char keys[MAX_NUM][MAX_NUM]; // Q3������ dept Q4������ city
    int values[MAX_NUM]; // Q3������ dept������ �л� ��
    int count;
};

typedef struct smap_Q5 smap_Q5;
struct smap_Q5
{
    char keys[MAX_NUM][MAX_NUM];
    sinfo svalues[MAX_NUM]; 
    int count;
};

// �׸��� 3,4�� ������ ����ü Ÿ�� map����. �̰ɷδ� Ű : �� ������ ��� 

// �Ƹ� Ű���� �а� ������ ���� �Ǵ� �а��� �л� �� �̷��� ������?

void set_print(struct sset *mySet) {
    for (int i = 0; i < mySet -> count; i++) {
        printf("%s ", mySet -> svalues[i].name);
        printf("%s ", mySet -> svalues[i].gender);
        printf("%s ", mySet -> svalues[i].city);  
        printf("%s ", mySet -> svalues[i].dept);  
        printf("%s ", mySet -> svalues[i].gpa);  
        printf("%s ", mySet -> svalues[i].height);  
        printf("%s\n", mySet -> svalues[i].weight);
    }
}

void Q1(sset sset)
{
    for(int i = 0; i < sset.count; i++)
    {
        if(strcmp(sset.svalues[i].name, "�蹮��") == 0) // �� �񱳰� ����� �ȵǴ°���?
        {
            printf("�蹮�� ��� ���� %s�Դϴ�. \n", sset.svalues[i].city);
        }
    }
}

void Q2(sset sset)
{
    sinfo chun;
    for(int i = 0; i < sset.count; i++)
    {
        if(strcmp(sset.svalues[i].name, "õ����") == 0)
        {
            chun = sset.svalues[i];
        }
    }

    int count_Q2 = 0;
    for(int i = 0; i < sset.count; i++)
    {
        if((atof(sset.svalues[i].gpa)) > atof(chun.gpa)) // �� for������ ����� ���� ����. 
        {
            count_Q2++;
        }
    }
    printf("õ�������� ������ ������� �� : %d \n", count_Q2);
}

void Q3(sset sset)
{
    int max = 0; // Q3���� �� �ִ� ���� �� �ʱ�ȭ
    smap smap; // Q3���� �� �� ����

    // smap �ʱ�ȭ
    for (int i = 0; i < MAX_NUM; i++)
    {
        smap.values[i] = 0;
        //printf("%d\n", smap.values[i]);
    }
    smap.count = 0;

    // while ����������
    int process = 0;
    
    // set�� ���ҵ��� ���������� �д� while loop 
    while (process < sset.count )
    {
        if (process == 0) // ù �߰�
        {
            strcpy(smap.keys[process], sset.svalues[process].dept);
            smap.values[smap.count] = 0;
            (smap.values[smap.count])++;
            (smap.count)++;
            process++;
            //printf("first %s %d %d %d\n\n", smap.keys[0] , smap.count, process, sset.count);
        }
        
        else // ù �߰� ���� (process > 0 �� ��)
        {
            // smap�� ���Ҹ� ������ for loop
            for (int i = 0; i <= smap.count; i++) 
            {
                // printf("%s \n", smap.values[process].name);
                
                // process index�� dept�� map�� ��� Ű�� ���ص� ���� ��. >> map Ű�� �߰��ؾ� ��
                if ( i == smap.count && strcmp(smap.keys[i-1], sset.svalues[process].dept) != 0 )
                {
                    strcpy(smap.keys[smap.count], sset.svalues[process].dept);  // Ű �߰�
                    (smap.values[smap.count])++;                                // ���ο� Ű�� �� ++
                    smap.count++;  // Ű �߰������� count�� ��
                    //printf("%s\n", smap.keys[smap.count]);
                    //printf("good insert new key\n");
                    break;
                }
                // process index�� dept�� map�� �� Ű�� �Ȱ��� �� >> map �ش��ϴ� Ű�� ���� ++�ؾ���
                else if ( strcmp(smap.keys[i], sset.svalues[process].dept) == 0 ) // �̰� �� �Ȱɸ���? �蹮��
                {
                    (smap.values[i])++;
                    //printf("good increse value\n");
                    break;
                }
                // �� �ΰ��� ��찡 �ƴ� = ��ġ�� Ű�� ������, ���� map�� Ű�� �� Ȯ�������� �� ��.
            }

            process++; // while loop�� ��Ʈ���ϴ� process�� 1 ������Ŵ. (loop 1ȸ)
        }
    }

    // for (int i = 0; i < smap.count; i++)
    // {
    //     printf("%d\n", smap.values[i]);
    // }
    
    max = smap.values[0]; // smap�� ù ������ �񱳽���.
    
    for (int i = 0; i < smap.count; i++)
    {
        if (smap.values[i+1] > smap.values[i])
        {
            max = smap.values[i+1];
        }
        
    }

    printf("�л� ���� ���� ���� �а��� �л� �� : %d \n", max);
    
}

void Q4(sset sset, smap smap)
{
    int max = 0; // Q3���� �� �ִ� ���� �� �ʱ�ȭ
    smap smap; // Q3���� �� �� ����

    // smap �ʱ�ȭ
    for (int i = 0; i < MAX_NUM; i++)
    {
        smap.values[i] = 0;
        //printf("%d\n", smap.values[i]);
    }
    smap.count = 0;

    // while ����������
    int process = 0;
    
    // set�� ���ҵ��� ���������� �д� while loop 
    while (process < sset.count )
    {
        if (process == 0) // ù �߰�
        {
            strcpy(smap.keys[process], sset.svalues[process].dept);
            smap.values[smap.count] = 0;
            (smap.values[smap.count])++;
            (smap.count)++;
            process++;
            //printf("first %s %d %d %d\n\n", smap.keys[0] , smap.count, process, sset.count);
        }
        
        else // ù �߰� ���� (process > 0 �� ��)
        {
            // smap�� ���Ҹ� ������ for loop
            for (int i = 0; i <= smap.count; i++) 
            {
                // printf("%s \n", smap.values[process].name);
                
                // process index�� dept�� map�� ��� Ű�� ���ص� ���� ��. >> map Ű�� �߰��ؾ� ��
                if ( i == smap.count && strcmp(smap.keys[i-1], sset.svalues[process].dept) != 0 )
                {
                    strcpy(smap.keys[smap.count], sset.svalues[process].dept);  // Ű �߰�
                    (smap.values[smap.count])++;                                // ���ο� Ű�� �� ++
                    smap.count++;  // Ű �߰������� count�� ��
                    //printf("%s\n", smap.keys[smap.count]);
                    //printf("good insert new key\n");
                    break;
                }
                // process index�� dept�� map�� �� Ű�� �Ȱ��� �� >> map �ش��ϴ� Ű�� ���� ++�ؾ���
                else if ( strcmp(smap.keys[i], sset.svalues[process].dept) == 0 ) // �̰� �� �Ȱɸ���? �蹮��
                {
                    (smap.values[i])++;
                    //printf("good increse value\n");
                    break;
                }
                // �� �ΰ��� ��찡 �ƴ� = ��ġ�� Ű�� ������, ���� map�� Ű�� �� Ȯ�������� �� ��.
            }

            process++; // while loop�� ��Ʈ���ϴ� process�� 1 ������Ŵ. (loop 1ȸ)
        }
    }

    // for (int i = 0; i < smap.count; i++)
    // {
    //     printf("%d\n", smap.values[i]);
    // }
    
    max = smap.values[0]; // smap�� ù ������ �񱳽���.
    
    for (int i = 0; i < smap.count; i++)
    {
        if (smap.values[i+1] > smap.values[i])
        {
            max = smap.values[i+1];
        }
        
    }
}
void Q5(sset sset, smap_Q5 smap_Q5, char* name)
{
    int search_index = 0;
    int check_same = 0;
    for(int i = 0; i < sset.count; i++)
    {
        smap_Q5.svalues[i] = sset.svalues[i];
        smap_Q5.count++;
        strcpy(smap_Q5.keys[i], sset.svalues[i].name);
    }

    for (int j = 0; j < smap_Q5.count; j++)
    {
        if(strcmp(name, smap_Q5.keys[j]) == 0)
        {
            search_index = j;
            check_same++;
        }
    }
    if(check_same == 1)
    {
        printf("%s, %s, %s, %s, %s, %s, %s \n", smap_Q5.svalues[search_index].name,
            smap_Q5.svalues[search_index].gender, smap_Q5.svalues[search_index].city,
            smap_Q5.svalues[search_index].dept, smap_Q5.svalues[search_index].gpa,
            smap_Q5.svalues[search_index].height, smap_Q5.svalues[search_index].weight);
    }
    else if (check_same == 2)
    {
        printf("�� Ű�� �ߺ��Դϴ�.");
    }

    else
    {
        printf("�Է��Ͻ� Ű�� map�� �����ϴ�.");
    }
    
}

int main() 
{
    FILE *fp;
    char line[256];  // �ִ� ���ڿ� ����
    int num_records = 0;
    sset my_sset;       // ���� ����
    sinfo temp;
    smap my_smap_Q3;
    smap my_smap_Q4;
    int check_same = 0;
    smap_Q5 smap_Q5;

    // Open file for reading
    fp = fopen("list.txt", "r+t");
    if (fp == NULL) 
    {
        printf("������ �� �� �����ϴ�. \n");
        return 0;
    }

    // ���� �б�
    while (fgets(line, sizeof(line), fp))
    {
        check_same = 0; 
        sscanf(line, "%s%s%s%s%s%s%s", temp.name, temp.gender, temp.city, temp.dept, temp.gpa, temp.height, temp.weight);
        if (my_sset.count == 0)
        {
            my_sset.svalues[0] = temp; // �߰��� ��ġ�� �߰�
            my_sset.count++; 
            continue;
        }
        for(int j = 0; j <= my_sset.count; j++)
        {
            if(strcmp(temp.name, my_sset.svalues[j].name) == 0)
            {
                check_same = 1;
            }
        }
        if (check_same == 0) // �ߺ� �ƴ� ��� -- �ٷ� �߰�(����)
        {
            int index = 0;   // while���� �� ���������, �߰��� ��ġ�� ����Ŵ
            while(index <= my_sset.count) 
            {
                if (index == my_sset.count-1)
                {
                    if ((index + 1) < MAX_NUM )
                    {
                        my_sset.svalues[index+1] = temp;
                    }

                    else
                    {
                        printf("������ �� �̻� �߰��� �� �����ϴ�.");
                    }
                    
                }
                
                if(strcmp(my_sset.svalues[index].name,temp.name) >= 0 ) // 0���� index�� �߰��� ��
                {
                    for(int index2 = my_sset.count; index2 >= index; index2-- )  //  �� ���� �߰��ɶ��� �����ؼ� ���� ���� �ؿ��� ��ħ
                        my_sset.svalues[index2 + 1] = my_sset.svalues[index2];   // �ڷ� �б�
                    my_sset.svalues[index] = temp; // �߰��� ��ġ�� �߰� 
                    my_sset.count++; // ���� ������
                    break;
                }
                index++; // ���� ������
            }
        }
    }
    
    // q1. �蹮�� ��°�

    set_print(&my_sset);
    Q1(my_sset);
    printf("============== process Q1 is good ===============\n");

    // q2. õ�������� ������ ��������� �� ������
    
    Q2(my_sset);
    printf("============== process Q2 is good ===============\n");

    // q3. ���� �л��� �����а���?
    Q3(my_sset);
    printf("============== process Q3 is good ===============\n");

    // q4. ���� ���� �л��� �����ϴ� ���� ������� ������ ����϶�.
    Q4(my_sset, my_smap_Q4);
    printf("============== process Q4 is good ===============\n");
    
    // q5. �л����� �̸��� id�� ����� �� �ִ°�? 
    // x -> ���������� �ֱ� ������ �л����� �̸��� id�� ����� ���� ����.
    Q5(my_sset, smap_Q5, "����");
    printf("============== process Q5 is good ===============\n");
}