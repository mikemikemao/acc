//
// Created by pirate
// 门禁 SDK 接口测试程序
// 功能：通过菜单选择要测试的接口，每个接口对应一个独立的测试用例函数
//

#include <cstdio>
#include <cstring>
#include <string>
#include "iostream"
#include <unistd.h>
using namespace std;

#ifdef __cplusplus
extern "C" {
#endif

#define DOOR_USER_NAME_LEN          (32)    // 门禁回路人员姓名最大长度
#define NAME_LEN                    (32)    // 用户名长度
#define TIME_LEN                    (32)
#define PASSWD_LEN                  (16)    // 密码长度

// 门禁卡片信息, 对应数据库表 ACS_CARD_INFO_S
typedef struct
{
    char cardNo[32 + 4];
    unsigned int cardType;
    char employeeNo[32 + 4];   // 工号
    unsigned int userId;       // 人员信息数据库id
} DOOR_CARD_INFO_S;

typedef struct
{
    int id;
    char aEmployeeNo[NAME_LEN + 4];          // 员工工号
    char aUserName[DOOR_USER_NAME_LEN + 4];  // 姓名
    int  eUserInfoType;                      // 人员类型 (USERINFO_TYPE_E)
    char aBeginTime[TIME_LEN];               // 有效期开始时间
    char aEndTime[TIME_LEN];                 // 有效期结束时间
    int  eTimeType;                          // 时间类型 (TIME_TYPE_E)
    char aPassWord[PASSWD_LEN];              // 密码开门
    int  sdwMaxOpenDoorTime;                 // 最长开门时间，0为无该参数
    int  sdwDoorNoMin;                       // 门编号最小值
    int  sdwDoorNoMax;                       // 门编号最大值
} DOOR_VISITOR_USERINFO_T;

// 数据加密参数
typedef struct
{
    int  sdwSecurity;   // 0:不加密 1:AES128 2:AES256
    char aIv[32 + 4];    // iv参数
} SECURITY_IV_INFO_T;

int sdk_client_get_door_capture_card_info_cap(const char *username, const char *password, const char *device_ip);
int sdk_client_get_door_capture_card_info(const char *username, const char *password, const char *device_ip,
    DOOR_CARD_INFO_S *cardInfo, int timeout);
int sdk_client_login_psw_check(const char *username, const char *password, const char *device_ip, char *rerbuf, int size2, int cardIdx);
int check_iot_intercom_door_scene(const char *username, const char *password, const char *device_ip);
int sdk_client_search_door_userinfo(const char *username, const char *password, const char *device_ip,
    char *pUserEmployeeNo, int *pOpenDoorTime, char *pDevName, int *totalNum);
int sdk_client_add_door_userinfo(const char *username, const char *password, const char *device_ip,
    DOOR_VISITOR_USERINFO_T *pstUserInfo, SECURITY_IV_INFO_T *pstSecy);
int sdk_client_add_door_card_info(const char *username, const char *password, const char *device_ip,
    DOOR_CARD_INFO_S *cardInfo, SECURITY_IV_INFO_T *pstSecy);

// 增加人员信息接口
int sdk_client_add_door_userinfo_wrap(const char *username, const char *password, const char *device_ip, const char *strUserInfo);

// 修改人员信息接口
int sdk_client_modify_door_userinfo_wrap(const char *username, const char *password, const char *device_ip, const char* strUserInfo);
//删除 清空
int sdk_client_del_door_userinfo_wrap(const char *username, const char *password, const char *device_ip, const char* strUserInfo);
#ifdef __cplusplus
}
#endif

//==============================================================
// 测试环境配置（按需修改）
//==============================================================
static const char *g_username   = "admin";
static const char *g_password   = "hik12345";
static const char *g_device_ip  = "10.6.126.29";
static const char *g_employee_no = "94a57d4e2202ad7e81bfac757f06b735"; // 测试用员工工号
static const int   g_timeout    = 300;   // 超时时间（秒）

//==============================================================
// 工具函数
//==============================================================
static void print_header(const char *name)
{
    cout << "\n========================================" << endl;
    cout << "测试项: " << name << endl;
    cout << "设备: " << g_device_ip << endl;
    cout << "========================================" << endl;
}

static void print_result(const char *name, int ret)
{
    cout << "----------------------------------------" << endl;
    if (ret == 0)
        cout << "[PASS] " << name << " ret=" << ret << endl;
    else
        cout << "[FAIL] " << name << " ret=" << ret << endl;
}

static void input_str(const char *prompt, char *buf, int size, const char *default_val)
{
    cout << prompt << " (默认: " << default_val << "): ";
    cin.getline(buf, size);
    if (buf[0] == '\0')
        snprintf(buf, size, "%s", default_val);
}

//==============================================================
// 测试用例
//==============================================================

// 1. 检查对讲门禁场景
static void test_check_door_scene()
{
    print_header("check_iot_intercom_door_scene 对讲门禁场景检查");
    int ret = check_iot_intercom_door_scene(g_username, g_password, g_device_ip);
    print_result("check_iot_intercom_door_scene", ret);
}

// 2. 获取刷卡能力 刷卡时间
static void test_get_card_cap()
{
    print_header("sdk_client_get_door_capture_card_info_cap 获取刷卡能力");
    int ret = sdk_client_get_door_capture_card_info_cap(g_username, g_password, g_device_ip);
    print_result("sdk_client_get_door_capture_card_info_cap", ret);
}

// 3. 获取抓拍刷卡信息（模拟刷卡，需现场刷卡配合）
static void test_get_capture_card_info()
{
    print_header("sdk_client_get_door_capture_card_info 获取抓拍刷卡信息");
    cout << "请在 " << g_timeout << "s 内在设备上刷卡..." << endl;

    DOOR_CARD_INFO_S cardInfo;
    memset(&cardInfo, 0, sizeof(cardInfo));
    int ret = sdk_client_get_door_capture_card_info(g_username, g_password, g_device_ip, &cardInfo, g_timeout);
    cout << "cardNo:     " << cardInfo.cardNo << endl;
    cout << "cardType:   " << cardInfo.cardType << endl;
    cout << "employeeNo: " << cardInfo.employeeNo << endl;
    cout << "userId:     " << cardInfo.userId << endl;
    print_result("sdk_client_get_door_capture_card_info", ret);
}

// 4. 查询门禁用户信息
static void test_search_door_userinfo()
{
    print_header("sdk_client_search_door_userinfo 查询门禁用户信息");
    char employeeNo[128] = {0};
    input_str("请输入员工工号", employeeNo, sizeof(employeeNo), g_employee_no);

    int openDoorTime = 0;
    char devName[512] = {0};
    int totalNum = 0;

    int ret = sdk_client_search_door_userinfo(g_username, g_password, g_device_ip,
                                             employeeNo, &openDoorTime, devName, &totalNum);
    cout << "OpenDoorTime: " << openDoorTime << endl;
    cout << "DevName:      " << devName << endl;
    cout << "TotalNum:     " << totalNum << endl;
    print_result("sdk_client_search_door_userinfo", ret);
}

// 5. 添加门禁卡片信息
static void test_add_door_card_info()
{
    print_header("sdk_client_add_door_card_info 添加门禁卡片信息");

    char employeeNo[128] = {0};
    char cardNo[64] = {0};
    input_str("请输入员工工号", employeeNo, sizeof(employeeNo), g_employee_no);
    input_str("请输入卡号",     cardNo,     sizeof(cardNo),     "1874538798");

    SECURITY_IV_INFO_T stSecy;
    memset(&stSecy, 0, sizeof(stSecy));   // 不加密

    DOOR_CARD_INFO_S cardInfo;
    memset(&cardInfo, 0, sizeof(cardInfo));
    strcpy(cardInfo.employeeNo, employeeNo);
    strcpy(cardInfo.cardNo, cardNo);

    int ret = sdk_client_add_door_card_info(g_username, g_password, g_device_ip, &cardInfo, &stSecy);
    print_result("sdk_client_add_door_card_info", ret);
}

// 6. 添加门禁用户信息（字符串接口）
static void test_add_door_userinfo_wrap()
{
    print_header("sdk_client_add_door_userinfo_wrap 添加门禁用户信息(JSON)");

    // 接口要求的 JSON 格式：
    // {"UserInfo":{"employeeNo":"","name":"","userType":"normal",
    //   "Valid":{"enable":true,"beginTime":"...","endTime":"..."},
    //   "doorRight":"1"}}
    string userInfo =
        "{\"UserInfo\":{"
        "\"employeeNo\":\"" + string(g_employee_no) + "\","
        "\"name\":\"pirate\","
        "\"userType\":\"normal\","
        "\"Valid\":{"
        "\"enable\":true,"
        "\"beginTime\":\"2026-10-27T00:00:00\","
        "\"endTime\":\"2036-10-26T23:59:59\""
        "},"
        "\"doorRight\":\"1\""
        "}}";


    cout << "UserInfo: " << userInfo << endl;
    int ret = sdk_client_add_door_userinfo_wrap(g_username, g_password, g_device_ip, userInfo.c_str());
    print_result("sdk_client_add_door_userinfo_wrap", ret);
}

// 7. 修改门禁用户信息（字符串接口）
static void test_modify_door_userinfo_wrap()
{
    print_header("test_del_door_userinfo_wrap 添加门禁用户信息(JSON)");

    // 接口要求的 JSON 格式：
    // {"UserInfo":{"employeeNo":"","name":"","userType":"normal",
    //   "Valid":{"enable":true,"beginTime":"...","endTime":"..."},
    //   "doorRight":"1"}}
    string userInfo =
        "{\"UserInfo\":{"
        "\"employeeNo\":\"" + string(g_employee_no) + "\","
        "\"name\":\"pirate1\","
        "\"userType\":\"normal\","
        "\"Valid\":{"
        "\"enable\":true,"
        "\"beginTime\":\"2026-10-27T00:00:00\","
        "\"endTime\":\"2036-10-26T23:59:59\""
        "},"
        "\"doorRight\":\"1\""
        "}}";


    cout << "UserInfo: " << userInfo << endl;
    int ret = sdk_client_modify_door_userinfo_wrap(g_username, g_password, g_device_ip, userInfo.c_str());
    print_result("sdk_client_add_door_userinfo_wrap", ret);
}

// 8. 修改门禁用户信息（字符串接口）
static void test_del_door_userinfo_wrap()
{
    print_header("sdk_client_modify_door_userinfo_wrap 添加门禁用户信息(JSON)");

    // 接口要求的 JSON 格式：
	//{"UserInfoDelCond":{"EmployeeNoList":[{"employeeNo":""}]}}
    string userInfo ="{\"UserInfoDelCond\":{\"EmployeeNoList\":[{\"employeeNo\":\"" + string(g_employee_no) + "\"}]}}";
    cout << "UserInfo: " << userInfo << endl;
    int ret = sdk_client_del_door_userinfo_wrap(g_username, g_password, g_device_ip, userInfo.c_str());
    print_result("sdk_client_del_door_userinfo_wrap", ret);
}

// 9. 清空用户信息（字符串接口）
static void test_clear_door_userinfo_wrap()
{
    print_header("sdk_client_modify_door_userinfo_wrap 添加门禁用户信息(JSON)");

    // 接口要求的 JSON 格式：
	//{"UserInfoDelCond":{"EmployeeNoList":[{"employeeNo":""}]}}
    string userInfo ="{\"UserInfoDelCond\":{\"EmployeeNoList\":[]}}";
    cout << "UserInfo: " << userInfo << endl;
    int ret = sdk_client_del_door_userinfo_wrap(g_username, g_password, g_device_ip, userInfo.c_str());
    print_result("sdk_client_del_door_userinfo_wrap", ret);
}




//==============================================================
// 菜单
//==============================================================
typedef struct
{
    int id;
    const char *name;
    void (*func)(void);
} TEST_CASE_S;

static TEST_CASE_S g_test_cases[] = {
    {1, "对讲门禁场景检查",           test_check_door_scene},
    {2, "获取刷卡能力",               test_get_card_cap},
    {3, "获取抓拍刷卡信息(需现场刷卡)", test_get_capture_card_info},
    {4, "查询门禁用户信息",           test_search_door_userinfo},
    {5, "添加门禁卡片信息",           test_add_door_card_info},
    {6, "添加门禁用户信息(JSON)",     test_add_door_userinfo_wrap},
	{7, "修改门禁用户信息(JSON)",     test_modify_door_userinfo_wrap},
	{8, "删除指定门禁用户信息(JSON)",  test_del_door_userinfo_wrap},
	{9, "清空用户信息(JSON)",          test_clear_door_userinfo_wrap},
};
static const int g_test_case_num = sizeof(g_test_cases) / sizeof(g_test_cases[0]);

static void print_menu()
{
    cout << "\n=========== 门禁SDK测试菜单 ===========" << endl;
    for (int i = 0; i < g_test_case_num; i++)
        cout << "  " << g_test_cases[i].id << ". " << g_test_cases[i].name << endl;
    cout << "  0. 退出" << endl;
    cout << "  a. 执行全部测试" << endl;
    cout << "=======================================" << endl;
    cout << "请选择: ";
}

int main()
{
    char input[64] = {0};

    while (1) {
        print_menu();
        cin.getline(input, sizeof(input));

        // 退出
        if (input[0] == '0' || input[0] == 'q' || input[0] == 'Q')
            break;

        // 执行全部
        if (input[0] == 'a' || input[0] == 'A') {
            for (int i = 0; i < g_test_case_num; i++)
                g_test_cases[i].func();
            continue;
        }

        // 执行单个
        int sel = atoi(input);
        if (sel >= 1 && sel <= g_test_case_num) {
            g_test_cases[sel - 1].func();
        } else {
            cout << "无效选择: " << input << endl;
        }
    }

    cout << "测试程序退出" << endl;
    return 0;
}
