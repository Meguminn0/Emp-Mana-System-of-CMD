#pragma once
#include "Worker.h"

class manager : public worker{
    public:
        // 显示职工信息
        void show_Info();

        // 获得部门信息
        string show_Dept();

        // 构造函数
        manager(int id, string name, int dept_Id);
};