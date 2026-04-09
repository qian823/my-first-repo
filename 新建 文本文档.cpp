#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>
using namespace std;

// 联系人结构体：存储单个联系人信息
struct Contact {
    string name;    // 姓名（唯一标识）
    string phone;   // 电话
    string email;   // 邮箱
    string address; // 地址
};

// 通讯录类：封装所有操作逻辑
class AddressBook {
private:
    vector<Contact> contacts; // 存储所有联系人的容器
    const string filename = "contacts.txt"; // 数据存储文件

    // 从文件加载联系人（私有辅助函数）
    void loadFromFile() {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "📁 未找到历史数据文件，将创建新通讯录" << endl;
            return;
        }

        Contact temp;
        // 按格式读取文件内容（姓名 电话 邮箱 地址，每行一个联系人）
        while (file >> temp.name >> temp.phone >> temp.email >> temp.address) {
            contacts.push_back(temp);
        }
        file.close();
        cout << "📥 成功加载 " << contacts.size() << " 个联系人" << endl;
    }

    // 保存联系人到文件（私有辅助函数）
    void saveToFile() {
        ofstream file(filename);
        if (!file.is_open()) {
            cout << "❌ 文件打开失败，数据未保存！" << endl;
            return;
        }

        // 按格式写入文件
        for (const auto& contact : contacts) {
            file << contact.name << " "
                 << contact.phone << " "
                 << contact.email << " "
                 << contact.address << endl;
        }
        file.close();
        cout << "✅ 数据已保存到 " << filename << endl;
    }

    // 查找联系人（返回迭代器，私有辅助函数）
    vector<Contact>::iterator findContact(const string& name) {
        return find_if(contacts.begin(), contacts.end(),
            [&](const Contact& c) { return c.name == name; });
    }

public:
    // 构造函数：初始化时加载文件
    AddressBook() {
        loadFromFile();
    }

    // 析构函数：退出时保存文件
    ~AddressBook() {
        saveToFile();
    }

    // 1. 添加联系人
    void addContact() {
        Contact newContact;
        cout << "\n===== 添加新联系人 =====" << endl;
        
        cout << "请输入姓名（不可重复）：";
        cin >> newContact.name;

        // 检查姓名是否重复
        if (findContact(newContact.name) != contacts.end()) {
            cout << "❌ 该姓名已存在，添加失败！" << endl;
            return;
        }

        cout << "请输入电话：";
        cin >> newContact.phone;
        cout << "请输入邮箱：";
        cin >> newContact.email;
        cout << "请输入地址：";
        cin.ignore(); // 忽略之前的换行符
        getline(cin, newContact.address); // 支持地址含空格

        contacts.push_back(newContact);
        cout << "✅ 联系人添加成功！" << endl;
    }

    // 2. 查询联系人（按姓名）
    void queryContact() {
        string name;
        cout << "\n===== 查询联系人 =====" << endl;
        cout << "请输入要查询的姓名：";
        cin >> name;

        auto it = findContact(name);
        if (it == contacts.end()) {
            cout << "❌ 未找到该联系人！" << endl;
            return;
        }

        // 格式化输出联系人信息
        cout << "\n📋 联系人信息：" << endl;
        cout << "姓名：" << it->name << endl;
        cout << "电话：" << it->phone << endl;
        cout << "邮箱：" << it->email << endl;
        cout << "地址：" << it->address << endl;
    }

    // 3. 修改联系人
    void modifyContact() {
        string name;
        cout << "\n===== 修改联系人 =====" << endl;
        cout << "请输入要修改的姓名：";
        cin >> name;

        auto it = findContact(name);
        if (it == contacts.end()) {
            cout << "❌ 未找到该联系人！" << endl;
            return;
        }

        // 显示原信息
        cout << "当前信息：" << endl;
        cout << "电话：" << it->phone << " | 邮箱：" << it->email << " | 地址：" << it->address << endl;

        // 输入新信息（支持部分修改，直接回车保留原信息）
        string newPhone, newEmail, newAddress;
        cout << "请输入新电话（回车保留原信息）：";
        cin >> newPhone;
        if (!newPhone.empty()) it->phone = newPhone;

        cout << "请输入新邮箱（回车保留原信息）：";
        cin >> newEmail;
        if (!newEmail.empty()) it->email = newEmail;

        cout << "请输入新地址（回车保留原信息）：";
        cin.ignore();
        getline(cin, newAddress);
        if (!newAddress.empty()) it->address = newAddress;

        cout << "✅ 联系人信息修改成功！" << endl;
    }

    // 4. 删除联系人
    void deleteContact() {
        string name;
        cout << "\n===== 删除联系人 =====" << endl;
        cout << "请输入要删除的姓名：";
        cin >> name;

        auto it = findContact(name);
        if (it == contacts.end()) {
            cout << "❌ 未找到该联系人！" << endl;
            return;
        }

        // 二次确认
        char confirm;
        cout << "确定要删除 " << name << " 的信息吗？(y/n)：";
        cin >> confirm;
        if (confirm == 'y' || confirm == 'Y') {
            contacts.erase(it);
            cout << "✅ 联系人删除成功！" << endl;
        } else {
            cout << "🚫 删除操作已取消" << endl;
        }
    }

    // 5. 显示所有联系人
    void showAllContacts() {
        cout << "\n===== 所有联系人列表 =====" << endl;
        if (contacts.empty()) {
            cout << "📭 通讯录为空，暂无联系人信息" << endl;
            return;
        }

        // 格式化表格输出
        cout << left;
        cout << setw(10) << "姓名" 
             << setw(15) << "电话" 
             << setw(25) << "邮箱" 
             << setw(30) << "地址" << endl;
        cout << string(80, '-') << endl;

        for (const auto& contact : contacts) {
            cout << setw(10) << contact.name
                 << setw(15) << contact.phone
                 << setw(25) << contact.email
                 << setw(30) << contact.address << endl;
        }
        cout << "\n总计：" << contacts.size() << " 个联系人" << endl;
    }

    // 显示菜单
    void showMenu() {
        cout << "\n=====================================" << endl;
        cout << "          C++ 通讯录系统 v1.0         " << endl;
        cout << "=====================================" << endl;
        cout << "1. 添加联系人    2. 查询联系人" << endl;
        cout << "3. 修改联系人    4. 删除联系人" << endl;
        cout << "5. 显示所有联系人  0. 退出系统" << endl;
        cout << "=====================================" << endl;
        cout << "请选择操作（0-5）：";
    }
};

// 主函数：程序入口
int main() {
    AddressBook addressBook;
    int choice;

    while (true) {
        addressBook.showMenu();
        cin >> choice;

        switch (choice) {
            case 1: addressBook.addContact(); break;
            case 2: addressBook.queryContact(); break;
            case 3: addressBook.modifyContact(); break;
            case 4: addressBook.deleteContact(); break;
            case 5: addressBook.showAllContacts(); break;
            case 0: 
                cout << "\n👋 感谢使用，再见！" << endl;
                return 0;
            default: 
                cout << "❌ 输入错误，请选择 0-5 之间的数字！" << endl;
        }

        // 暂停一下，方便查看结果（按任意键继续）
        cout << "\n按 Enter 键返回菜单...";
        cin.ignore();
        cin.get();
    }
}