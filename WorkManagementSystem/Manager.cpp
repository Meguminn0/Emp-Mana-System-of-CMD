#include "Manager.h"

// 显示职工信息
void manager::show_Info(){
    cout << "职工编号:" << this->getId()
         << "\t\t姓名:" << this->getName()
         << "\t部门:" << this->show_Dept()
         << "\t 工作:完成老板下达的任务，并给普通员工下达任务" << endl;
}

// 获得部门信息
string manager::show_Dept()
{
    return string("经理");
}

// 构造函数
manager::manager(int id, string name, int dept_Id){
    this->setId(id);
    this->setName(name);
    this->setDept_Id(dept_Id);
}