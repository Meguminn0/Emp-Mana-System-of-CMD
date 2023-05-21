#include "Employee.h"

// 显示职工信息
void employee::show_Info(){
    cout << "职工编号:" << this->getId()
         << "\t\t姓名:" << this->getName()
         << "\t部门:" << this->show_Dept()
         << "\t 工作:完成经理下达的任务" << endl;
}


// 获得部门信息
string employee::show_Dept()
{
    return string("普通员工");
}

// 构造函数
employee::employee(int id, string name, int dept_Id){
    this->setId(id);
    this->setName(name);
    this->setDept_Id(dept_Id);
}