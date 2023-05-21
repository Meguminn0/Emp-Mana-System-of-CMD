#include "Boss.h"

// 显示职工信息
void boss::show_Info(){
    cout << "职工编号:" << this->getId()
         << "\t\t姓名:" << this->getName()
         << "\t部门:" << this->show_Dept()
         << "\t 工作:给经理下达任务" << endl;
}

// 获得部门信息
string boss::show_Dept()
{
    return string("老板");
}

// 构造函数
boss::boss(int id, string name, int dept_Id){
    this->setId(id);
    this->setName(name);
    this->setDept_Id(dept_Id);
}