#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <string.h>

void io_and_string_cheat_sheet()
{
    // --- 1. 基础输入输出 (stdio.h) ---
    int a;
    double d;
    char str[100];
    char c;

    // scanf 技巧：
    // %d: 读整数 (需要 &)
    // %lf: 读 double (必须用 %lf，不能用 %f)
    // %s: 读单词 (遇到空格或回车停止，不需要 &)
    // %c: 读字符 (会读入空格和回车，前面加个空格 " %c" 可以跳过空白符)
    scanf("%d %lf %s", &a, &d, str);

    // printf 技巧：
    // %.2f: 保留两位小数
    // %5d: 宽度为5，右对齐
    // %-5d: 宽度为5，左对齐
    // %02d: 宽度为2，不足补0 (适合输出时间 09:05)
    printf("Int: %02d, Double: %.2f, String: %s\n", a, d, str);

    // --- 2. 字符串处理 (string.h) ---
    char s1[100] = "Hello";
    char s2[100] = "World";

    // (1) 求长度 (strlen)
    // 考试陷阱：strlen 不包含结尾的 '\0'，sizeof 包含
    int len = strlen(s1);

    // (2) 字符串复制 (strcpy)
    // 用法：strcpy(目标, 源); 会覆盖目标的内容
    strcpy(s1, s2); // s1 变成了 "World"

    // (3) 字符串连接 (strcat)
    // 用法：strcat(目标, 源); 把源拼接到目标后面
    strcat(s1, "!"); // s1 变成了 "World!"

    // (4) 字符串比较 (strcmp) - 排序必考！
    // 规则：s1 == s2 返回 0; s1 > s2 返回正数; s1 < s2 返回负数
    if (strcmp(s1, s2) == 0)
    {
        printf("Equal\n");
    }
    else if (strcmp(s1, s2) > 0)
    {
        printf("s1 is larger (字典序靠后)\n");
    }

    // (5) 内存初始化 (memset) - 数组清零神器
    int arr[10];
    memset(arr, 0, sizeof(arr)); // 把 arr 全部置为 0
}

#include <math.h>
#include <stdlib.h>

void math_and_stdlib_cheat_sheet()
{
    // --- 1. 数学函数 (math.h) ---
    double x = 9.0, y = 2.0;

    // (1) 平方根 (sqrt) - 素数判断必用
    double root = sqrt(x); // 3.0

    // (2) 幂运算 (pow) - 也就是 x 的 y 次方
    // 考试陷阱：不要用 ^ (那是异或位运算)，要用 pow
    double p = pow(x, y); // 9^2 = 81.0

    // (3) 绝对值 (fabs vs abs)
    // fabs: 用于浮点数 (math.h)
    // abs:  用于整数 (stdlib.h)
    double f_abs = fabs(-3.14); // 3.14
    int i_abs = abs(-10);       // 10

    // --- 2. 通用工具 (stdlib.h) ---

    /*int *A = (int *)malloc(n * sizeof(int));
    二维数组分配内存
    int **matrix = (int **)malloc(rows * sizeof(int *));

    // 第二步：循环为每一行申请具体的空间
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
    } */

    // (1) 字符串转数字 (atoi, atof)
    char numStr[] = "123";
    int num = atoi(numStr);     // "123" -> 123
    double dnum = atof("3.14"); // "3.14" -> 3.14

    // (2) [补充] 数字转字符串 (sprintf) - 万能转换
    // 技巧：用法和 printf 一模一样，只是前面多了一个目标字符串数组
    // 它可以把整数、浮点数甚至多个变量拼接成一个字符串
    char buffer[50];
    int myInt = 2023;
    double myDouble = 3.14159;

    sprintf(buffer, "%d", myInt);                // buffer 变成 "2023"
    sprintf(buffer, "%.2f", myDouble);           // buffer 变成 "3.14"
    sprintf(buffer, "%d-%.2f", myInt, myDouble); // 拼接：buffer 变成 "2023-3.14"
    // (3) 随机数 (rand) - 猜数游戏用
    // srand(time(NULL)); // 一般配合 time.h 使用，如果不能用 time.h 就省略
    int random_val = rand() % 100 + 1; // 生成 1~100 的随机数
}

#include <iostream>
#include <iomanip> // 必带！用于控制小数位数
#include <string>
using namespace std; // 必写！否则要一直写 std::cin, std::cout

void io_cheat_sheet() {
    // 1. 基础输入输出
    int a;
    double b;
    string s;

    ios::sync_with_stdio(false);
    cin.tie(0);

    // cin 读入 (自动识别类型，不需要 %d %lf)
    // 注意：cin >> s 读字符串遇到空格会停止
    cin >> a >> b >> s; 

    // 2. 读取整行字符串 (带空格的，例如 "Hello World")
    // C语言用 gets/fgets，C++ 用 getline
    // 注意：如果在 getline 之前用了 cin >> a，需要先吃掉回车
    string line;
    // cin.ignore(); // 如果前面有 cin 读取数字，取消这行注释
    getline(cin, line);

    // 3. 输出 (cout)
    // endl 代表换行
    cout << "Int: " << a << ", String: " << s << endl;

    // 4. 小数格式化 (替代 printf("%.2f"))
    // fixed + setprecision(2)
    cout << fixed << setprecision(2) << b << endl;
}

void string_cheat_sheet() {
    string s1 = "Hello";
    string s2 = "World";

    // 1. 字符串连接 (直接用 +)
    // C语言要用 strcat，C++ 直接加
    string s3 = s1 + " " + s2; // "Hello World"

    // 2. 字符串比较 (直接用 ==, <, >)
    // C语言要用 strcmp，C++ 直接比
    if (s1 == s2) {
        cout << "Equal" << endl;
    } else if (s1 < s2) {
        cout << "s1 comes first" << endl; // 字典序
    }

    // 3. 获取长度
    int len = s1.length(); // 或者 s1.size()

    // 4. 查找子串 (find)
    // 查找 "ll" 在 s1 中的位置
    int pos = s1.find("ll");
    if (pos != string::npos) { // string::npos 表示“没找到”
        cout << "Found at index: " << pos << endl;
    }

    // 5. 截取子串 (substr)
    // s1.substr(起始下标, 长度)
    string sub = s1.substr(1, 3); // 从下标1开始取3个 -> "ell"
    
    // 6. 字符串转数字 (需包含 <string>)
    // stoi (string to int), stod (string to double)
    string numStr = "123";
    int num = stoi(numStr);
}

void memory_cheat_sheet() {
    int n;
    cin >> n;

    // --- 1. 一维数组动态分配 ---
    // C语言: int *arr = (int*)malloc(n * sizeof(int));
    // C++:
    int *arr = new int[n]; 

    // 使用数组
    for (int i = 0; i < n; i++) {
        arr[i] = i * 2;
    }

    // 释放数组 (注意 delete 后面要加 [])
    delete[] arr;

    // --- 2. 二维数组动态分配 (m行 n列) ---
    int m = 5;
    // 第一步：开辟行指针数组
    int **matrix = new int*[m];
    // 第二步：给每一行开辟空间
    for (int i = 0; i < m; i++) {
        matrix[i] = new int[n];
    }

    // 使用
    matrix[0][0] = 99;

    // 释放 (顺序相反)
    for (int i = 0; i < m; i++) {
        delete[] matrix[i]; // 删行
    }
    delete[] matrix; // 删头
}

void IO_Traps_Solution() {
    // ---------------------------------------------------------
    // 场景 A: C语言 scanf 后读取字符串 (缓冲区回车残留)
    // ---------------------------------------------------------
    int n;
    char str[100];
    
    // 错误写法：scanf("%d", &n); fgets(str, ...); 
    // 后果：fgets 读到了 scanf 剩下的 '\n'，str 变为空行。
    
    // 【正确写法】
    scanf("%d", &n);
    getchar(); // <--- 关键！手动吃掉数字后面的回车符
    fgets(str, 100, stdin); 

    // ---------------------------------------------------------
    // 场景 B: C语言 fgets 去除末尾换行符 (必考！)
    // ---------------------------------------------------------
    // 问题：fgets 会把回车也读进来，导致 strcmp 失败或输出多空一行。
    
    if (fgets(str, 100, stdin) != NULL) {
        // 【万能去回车法】建议直接背下来
        for (int i = 0; str[i] != '\0'; i++) {
            if (str[i] == '\n') {
                str[i] = '\0'; // 找到换行符，强制截断
                break;
            }
        }
    }

    // ---------------------------------------------------------
    // 场景 C: C++ cin 后读取 getline (同 scanf 问题)
    // ---------------------------------------------------------
    string s;
    
    // 错误写法：cin >> n; getline(cin, s);
    
    // 【正确写法】
    cin >> n;
    cin.ignore(); // <--- C++ 专用吃回车函数
    // 或者更稳健的写法（清空整行缓冲区）：
    // cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    getline(cin, s);
}

/* * ============================================================
 * 模块二：数值与逻辑避坑指南 (Math & Logic)
 * ============================================================
 */

#include <math.h>
#include <stdio.h>

void Math_Logic_Traps() {
    // ---------------------------------------------------------
    // 陷阱 1: 整数除法 (最容易丢分！)
    // ---------------------------------------------------------
    int a = 1, b = 2;
    double ans_wrong = a / b;       // 结果是 0.0 (错！)
    
    // 【正确写法】强制转换其中一个为 double
    double ans_right = (double)a / b; // 结果是 0.5 (对)
    // 或者写成 1.0 / 2

    // ---------------------------------------------------------
    // 陷阱 2: 浮点数比较 (不要用 ==)
    // ---------------------------------------------------------
    double d = 0.000000001;
    
    // 错误：if (d == 0) ... 计算机可能认为它不等于0
    
    // 【正确写法】判断绝对值是否极小
    if (fabs(d) < 1e-6) { 
        printf("可以认为 d 等于 0\n");
    }

    // ---------------------------------------------------------
    // 陷阱 3: 数组与字符串大小 (宁大勿小)
    // ---------------------------------------------------------
    // 题目要求：字符串最大长度 100
    // 错误：char s[100]; -> 如果输入满100个字，\0 没地方放，崩！
    
    // 【正确写法】
    char s[105]; // 多给 5 个空间保平安
    
    // ---------------------------------------------------------
    // 陷阱 4: 局部变量初始化 (防止垃圾值)
    // ---------------------------------------------------------
    // 错误：int sum; for(int i=0;i<10;i++) sum += i; -> sum 初始值随机
    
    // 【正确写法】
    int sum = 0;       // 累加器初始化为 0
    long long prod = 1; // 累乘器初始化为 1
}

/* * ============================================================
 * 模块三：内存与指针操作 (Memory & Pointers)
 * ============================================================
 */

#include <iostream>
using namespace std;

void Memory_Traps() {
    // ---------------------------------------------------------
    // 难点 1: 动态二维数组 (m行 n列) - C++ new 写法
    // ---------------------------------------------------------
    int m = 5, n = 4;
    
    // 1. 开辟行指针数组 (指向 int* 的指针)
    int **matrix = new int*[m]; 
    
    // 2. 为每一行开辟空间
    for(int i = 0; i < m; i++) {
        matrix[i] = new int[n];
    }
    
    // 3. 初始化 (重要！new 出来的数据是随机的)
    for(int i=0; i<m; i++)
        for(int j=0; j<n; j++)
            matrix[i][j] = 0;

    // 4. 释放 (考试不写可能不扣分，但写了显专业)
    // 先删里层，再删外层
    for(int i = 0; i < m; i++) delete[] matrix[i];
    delete[] matrix;

    // ---------------------------------------------------------
    // 难点 2: 链表操作口诀 (防止断链)
    // ---------------------------------------------------------
    /* 场景：在节点 A 和 B 之间插入新节点 New
       错误：A->next = New; (完蛋，B 找不到了)
       
       【正确口诀】：先连后断（先连后面，再断前面）
       New->next = A->next; // 1. New 先抓住 B
       A->next = New;       // 2. A 再抓住 New
    */
}