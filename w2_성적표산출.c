#include <stdio.h>
#include <stdlib.h>
#define SIZE 30
#define SUM(stu) (stu.object+stu.subject)

struct info
{
    char name[SIZE];
    char major[SIZE];
    int num;
    float object;
    float subject;
    float score;
}info;

void rank(struct info* in, int n);
void View(struct info* in, int n);

void menu()
{
    printf("성균관대 성적표 프로그램입니다\n");
    printf("-------\n");
    printf("*사용방법*\n성적을 낼 학생들 수를 입력 후, 메뉴에 써져있는 학생들 정보를 입력해주세요. 프로그램을 통해서 학생들의 성적 및 등수를 확인할 수 있습니다.\n");
    printf(">> 시작 \n\n\n");

}
int main()
{
    int n = 0;

    int i = 0;
    menu();
    printf("학생 수를 입력해주세요:");
    scanf("%d", &n);

    struct info* in = malloc(sizeof(info) * n);
    printf("-----학생 정보 입력란-----\n");
    for (i = 0; i < n; i++)
    {
        printf("%d )\n", i + 1);

        printf("학과 :");
        scanf("%s", in[i].major);
        printf("학번 :");
        scanf("%d", &in[i].num);
        printf("이름 :");
        scanf("%s", in[i].name);
        printf("객관식 성적 :");
        scanf("%f", &in[i].object);
        printf("주관식 성적 :");
        scanf("%f", &in[i].subject);

        in[i].score = in[i].object + in[i].subject;
    }

    rank(in, n);
    View(in, n);

    free(in);
    return 0;
}
void rank(struct info* in, int n)
{
    struct info temp;
    int i = 0, j = 0;
    for (i = n; i > 1; i--)
    {
        for (j = 1; j < i; j++)
        {
            if (SUM(in[j - 1]) < SUM(in[j]))
            {
                temp = in[j - 1];
                in[j - 1] = in[j];
                in[j] = temp;
            }
        }
    }
}

void View(struct info* in, int n)
{
    printf("\n\n>>>성적표 산출결과\n\n");

    int i = 0;
    float average;
    float sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += in[i].score;
    }
    average = sum / n;
    printf("\n\n--------");
    printf("%s| %s| %s| %s| %s| %s|\n", "학과", "번호", "이름", "중간", "기말", "합계");

    for (int i = 0; i < n; i++)
    {
        printf("\n\n\n %d순위 : %s| %d| %s| %.1f| %.1f| %.1f| \n", i + 1, in[i].major, in[i].num, in[i].name, in[i].object, in[i].subject, in[i].score);
        if ((in[i].score) > average)
        {
            printf("result : A+");
        }
        else
        {
            printf("result : B+");
        }

    }
}

