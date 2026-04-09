#include <iostream>
using namespace std;

class Cube
{
public:
    void setCube(int a, int b, int c)
    {
        m_H = a;
        m_L = b;
        m_W = c;
    }
    void Cube_S()
    {
        cout << "立方体的表面积是：" << S() << endl;
    }
    void Cube_V()
    {
        cout << "立方体的体积是：" << V() << endl;
    }
    int getHeight() { return m_H; }
    int getLength() { return m_L; }
    int getWidth() { return m_W; }

private:
    int m_H;
    int m_L;
    int m_W;

    int S()
    {
        return 2 * m_L * m_H + 2 * m_W * m_H + 2 * m_L * m_W;
    }
    int V()
    {
        return m_L * m_H * m_W;
    }
};

// 全局函数判断两个立方体是否全等
bool areEqual(Cube& c1, Cube& c2)
{
    return c1.getHeight() == c2.getHeight() &&
           c1.getLength() == c2.getLength() &&
           c1.getWidth() == c2.getWidth();
}

int main()
{
    int a1, b1, c1, a2, b2, c2;

    // 输入第一个立方体的属性
    cout << "请输入第一个立方体的长、宽、高（用空格分隔）：";
    cin >> a1 >> b1 >> c1;

    // 输入第二个立方体的属性
    cout << "请输入第二个立方体的长、宽、高（用空格分隔）：";
    cin >> a2 >> b2 >> c2;

    // 创建两个立方体对象
    Cube cube1, cube2;
    cube1.setCube(a1, b1, c1);
    cube2.setCube(a2, b2, c2);

    // 显示两个立方体的表面积和体积
    cout << "\n第一个立方体：" << endl;
    cube1.Cube_S();
    cube1.Cube_V();

    cout << "\n第二个立方体：" << endl;
    cube2.Cube_S();
    cube2.Cube_V();

    // 使用全局函数判断是否全等
    if (areEqual(cube1, cube2))
    {
        cout << "\n这两个立方体全等（对应的长、宽、高分别相等）" << endl;
    }
    else
    {
        cout << "\n这两个立方体不全等" << endl;
    }

    return 0;
}