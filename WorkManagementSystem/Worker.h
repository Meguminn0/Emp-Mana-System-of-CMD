#pragma once

#include <iostream>

#define BOSS 1
#define MANAGER 2
#define EMPLOYEE 3

using namespace std;

class worker{
    public:
        // 显示职工信息
        void virtual show_Info() = 0;

        // 获得部门信息
        string virtual show_Dept() = 0;

        void setName(string name){
            this->name = name;
        }

        string getName(){
            return this->name;
        }

        void setId(int id){
            this->id = id;
        }

        int getId(){
            return this->id;
        }

        void setDept_Id(int dept_Id){
            this->dept_Id = dept_Id;
        }

        int getDept_Id(){
            return this->dept_Id;
        }

    private:
        string name;    // 姓名
        int id;         // 职工编号
        int dept_Id;    // 部门编号
};