#pragma once
#include <iostream>
#include "Worker.h"

#define FILEADDR "WorkersFile.txt"
#define ISEMPTY true
#define NOTEMPTY false

// 职工管理系统
class workermanager{
    public:
        
        // 显示菜单
        void show_Menu();

        // 退出管理系统
        void exitSys();

        // 保存职工信息到文件中
        void save();

        // 增加职工信息
        void add_Emp();

        // 显示职工信息
        void show_Emp();

        // 获取文件中的职工人数
        int get_EmpNum();

        // 初始化职工数组
        void init_EmpArr();

        // 删除职工信息
        void delete_Emp();

        // 查找对应id号职工在数组中的下标
        int find_Id(int id);

        // 修改职工信息
        void edit_Emp();

        // 查找职工信息
        void find_Emp();

        // 按编号排序
        void sort_Id();

        // 清空所有文件
        void clear_Emp();

        // 回收站(退出后永久删除)
        void recycleBin();
        
        // 构造函数
        workermanager();

        // 析构函数
        ~workermanager();

        void setWorkerArr(worker **workerArr){
            this->workerArr = workerArr;
        }
        
        worker **getWorkerArr(){
            return this->workerArr;
        }

        void setWorkerNum(int WorkerNum){
            this->workerNum = WorkerNum;
        }

        int getWorkerNum(){
            return this->workerNum;
        }

    private:
        worker **workerArr;     // 存放职工信息的数组
        int workerNum;          // 记录职工数量
        int recycleNum;         // 回收站中职工信息的数量
        bool FileisEmpty;       // 标记文件是否为空
};