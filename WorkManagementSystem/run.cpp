#include "WorkerManager.h"

using namespace std;

int main(){
    int choice;
    workermanager wm;

    while(true){
        system("cls");
        wm.show_Menu();
        cout << "请输入你的选择：";
        cin >> choice;
        system("cls");

        switch (choice)
        {
        case 0:     // 退出
            wm.exitSys();
            break;

        case 1:     // 增加职工信息
            wm.add_Emp();
            break;

        case 2:     // 显示职工信息
            wm.show_Emp();
            break;

        case 3:     // 删除职工信息
            wm.delete_Emp();
            break;

        case 4:     // 修改职工信息
            wm.edit_Emp();
            break;

        case 5:     // 查找职工信息
            wm.find_Emp();
            break;

        case 6:     // 按编号排序
            wm.sort_Id();
            break;

        case 7:     // 清空所有文件
            wm.clear_Emp();
            break;

        case 8:     // 回收站(退出后永久删除)
            wm.recycleBin();

            break;
        
        default:
            cout << "输入错误" << endl; 
            system("pause");
            break;
        }
    }


    system("pause");
    return 0;
} 