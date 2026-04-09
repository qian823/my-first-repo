#include <iostream>
#include <string>

using namespace std;

int main() {
    int month, day;
    char dot;  // 用于读取点号

    cout << "========== 星座查询 ==========" << endl;
    cout << "请输入你的生日（格式：月.日，如 10.15）：";
    cin >> month >> dot >> day;

    // 验证月份
    if (cin.fail() || month < 1 || month > 12) {
        cout << "输入无效！月份必须在1-12之间。" << endl;
        return 1;
    }

    // 验证日期（根据月份判断天数）
    int maxDays;
    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            maxDays = 31;
            break;
        case 4: case 6: case 9: case 11:
            maxDays = 30;
            break;
        case 2:
            maxDays = 28;  // 暂不考虑闰年
            break;
        default:
            cout << "输入无效！" << endl;
            return 1;
    }

    if (day < 1 || day > maxDays) {
        cout << "输入无效！" << month << "月只有 " << maxDays << " 天。" << endl;
        return 1;
    }

    // 将日期转换为便于比较的数字格式（月*100 + 日）
    int date = month * 100 + day;
    string zodiac;

    // 判断星座
    if ((date >= 321 && date <= 419)) {
        zodiac = "白羊座";
    } else if ((date >= 420 && date <= 520)) {
        zodiac = "金牛座";
    } else if ((date >= 521 && date <= 621)) {
        zodiac = "双子座";
    } else if ((date >= 622 && date <= 722)) {
        zodiac = "巨蟹座";
    } else if ((date >= 723 && date <= 822)) {
        zodiac = "狮子座";
    } else if ((date >= 823 && date <= 922)) {
        zodiac = "处女座";
    } else if ((date >= 923 && date <= 1023)) {
        zodiac = "天秤座";
    } else if ((date >= 1024 && date <= 1122)) {
        zodiac = "天蝎座";
    } else if ((date >= 1123 && date <= 1221)) {
        zodiac = "射手座";
    } else if ((date >= 1222 && date <= 1231) || (date >= 101 && date <= 119)) {
        zodiac = "摩羯座";
    } else if ((date >= 120 && date <= 218)) {
        zodiac = "水瓶座";
    } else {
        zodiac = "双鱼座";
    }

    cout << "\n你的生日是 " << month << "月" << day << "日" << endl;
    cout << "你的星座是：" << zodiac << endl;
    cout << "=============================" << endl;

    return 0;
}
