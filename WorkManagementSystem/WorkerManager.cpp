#include <iostream>
#include <fstream>

#include "WorkerManager.h"
#include "Boss.h"
#include "Employee.h"
#include "Manager.h"
#include "Worker.h"

using namespace std;


// 构造函数
workermanager::workermanager(){
    // 先判断文件是否存在
    ifstream ifs;
    ifs.open(FILEADDR, ios::in);
    
    if(!ifs.is_open()){
        // 如果无法打开文件，说明这个文件不存在
        // cout << "文件不存在" << endl;   // 测试

        // 初始化成员属性
        this->FileisEmpty = ISEMPTY;
        this->workerArr = NULL;
        this->workerNum = 0;
        this->recycleNum = 0;

        ifs.close();
        return;
    }

    char ch;
    ifs >> ch;
    // 去走一个字符后，如果这个字符为空，则会设置文件结束符 EOF
    if(ifs.eof()){
        // 文件内容为空
        // cout << "文件为空" << endl;     // 测试

        // 初始化成员属性
        this->FileisEmpty = ISEMPTY;
        this->workerArr = NULL;
        this->workerNum = 0;
        this->recycleNum = 0;

        ifs.close();
        return;
    }

    // 文件存在，且不为空
    this->recycleNum = 0;
    this->workerNum = this->get_EmpNum();
    this->workerArr = new worker*[this->workerNum];
    this->init_EmpArr();
    this->FileisEmpty = NOTEMPTY;

    ifs.close();
}

// 析构函数
workermanager::~workermanager(){
    // 回收数组中的数据
    if(workerArr != NULL){
        delete[] this->workerArr;
        workerArr = NULL;
    }
}

// 显示菜单
void workermanager::show_Menu(){
    cout << "=============================================" << endl;
    cout << "===========      0. 退出管理系统      ========" << endl;
    cout << "===========      1. 增加职工信息      ========" << endl;
    cout << "===========      2. 显示职工信息      ========" << endl;
    cout << "===========      3. 删除离职员工      ========" << endl;
    cout << "===========      4. 修改职工信息      ========" << endl;
    cout << "===========      5. 查找职工信息      ========" << endl;
    cout << "===========      6. 按照编号排序      ========" << endl;
    cout << "===========      7. 清空所有文档      ========" << endl;
    cout << "=========== 8. 回收站(退出后永久删除) ========" << endl;
    cout << "=============================================" << endl;
    cout << endl;
}

// 退出管理系统
void workermanager::exitSys(){
    int choice;
    cout << "确定退出？？？" << endl;
    
    while(true){
        cout << "1. 确定" << endl;
        cout << "2. 取消" << "\n: ";
        cin >> choice;

        if(choice == 2){
            cout << "取消退出" << endl;
            break;
        }else if(choice == 1){
            cout << "欢迎下次使用！" << endl;
            system("pause");
            exit(0);
        }else{
            cout << "输入如错误！请重新输入" << endl;
        }
    }

    system("pause");
}

// 保存职工信息到文件中
void workermanager::save(){
    ofstream ofs;
    ofs.open(FILEADDR, ios::out);
    
    // 写入数据
    for(int i = 0; i < this->workerNum; i++){
        ofs << this->workerArr[i]->getId() << " "
            << this->workerArr[i]->getName() << " "
            << this->workerArr[i]->getDept_Id() << endl;
    }

    ofs.close();
}

// 增加职工信息
void workermanager::add_Emp(){
    int addNum;
    int newSize;
    string name;
    int id;
    int dept_Id;
    worker *newWorker;

    worker **newWorkerArr;
    
    cout << "请输入新增职工数量(输入 -1 取消操作):";
    while (1)
    {
        cin >> addNum;
        // 输入为-1 时，退出
        if(addNum == -1){
            return;
        }
        if(addNum > 0){
            break;
        }
        cout << "新增员工数量必须大于0，请重新输入(输入 -1 取消操作):";
    }

    newSize = this->workerNum + this->recycleNum + addNum;
    newWorkerArr = new worker*[newSize];

    // 将之前数组中的数据拷贝到新数组中
    for(int i = 0; i < this->getWorkerNum(); i++){
        newWorkerArr[i] = this->workerArr[i];
    }
    
    // 将回收站中的数据保存到新数组中
    for(int i = 0 ; i < this->recycleNum; i++){
        newWorkerArr[newSize - i - 1] = this->workerArr[this->workerNum + this->recycleNum - i - 2];
    }

    // 回收数组中的数据
    delete[] this->workerArr;
    
    // 更新数组
    this->workerArr = newWorkerArr;

    // 输入新增职工的信息并保存到新数组中
    for(int i = 0; i < addNum; i++){
        cout << "请输入第 " << i+1 << " 位职工的姓名:";
        cin >> name;
        cout << "请输入第 " << i+1 << " 位职工的id:";

        // 确保所有职工的id号是唯一的
        while(1){
            // int ret;
            cin >> id;

            // 确保输入的id号为正数
            if(id < 0){
                cout << "id号必须为正数，请重新输入:";
                continue;
            }

            if(this->find_Id(id) == -1){
                // 数组中没有找到相同id的职工
                break;
            }else{
                cout << "该id号已被占用，请重新输入新的id号:";
            }
        }

        cout << "请输入第 " << i+1 << " 位职工的部门编号" << endl;;
        while(1){
            cout << "1. 老板" << endl;
            cout << "2. 经理" << endl;
            cout << "3. 普通职工\n:";
            cin >> dept_Id;

            if(dept_Id == BOSS){
                newWorker = new boss(id, name, dept_Id);
                break;
            }else if(dept_Id == MANAGER){
                newWorker = new manager(id, name, dept_Id);
                break;
            }else if(dept_Id == EMPLOYEE){
                newWorker = new employee(id, name, dept_Id);
                break;
            }else{
                cout << "输入错误，请重新输入!!" << endl;;
            }
        }

        this->workerArr[this->workerNum] = newWorker;
        // 更新职工人数
        this->workerNum++;
    }

    // 保存职工信息到文件中
    this->save();

    // 修改文件标记
    this->FileisEmpty = NOTEMPTY;
}

// 显示职工信息
void workermanager::show_Emp(){
    // 先判断文件是否存在
    if(this->FileisEmpty){
        cout << "文件不存在或数据为空" << endl;
        system("pause");
        return;
    }
    
    if(this->workerNum != 0){
        cout << "---------------------------------------------------------------------" << endl;
        for(int i = 0; i < this->workerNum; i++){
            this->workerArr[i]->show_Info();
        }
        cout << "---------------------------------------------------------------------" << endl;
        cout << "职工全部显示完毕，职工数量：" << this->workerNum << endl;
    }else{
        cout << "系统中职工数量为0" << endl;
    }
    
    system("pause");
}

// 获取文件中的职工人数
int workermanager::get_EmpNum(){
    string name;
    int id;
    int dept_Id;
    int empNum = 0;
    ifstream ifs;
    ifs.open(FILEADDR, ios::in);

    while(ifs >> id && ifs >> name && ifs >> dept_Id){
        empNum++;
    }

    return empNum;
}

// 初始化职工数组
void workermanager::init_EmpArr(){
    string name;
    int id;
    int dept_Id;
    int index = 0;
    ifstream ifs;
    ifs.open(FILEADDR, ios::in);

    while(ifs >> id && ifs >> name && ifs >> dept_Id){
        worker *newWorker = NULL;
        if(dept_Id == 1){
            newWorker = new boss(id, name, dept_Id);
        }else if(dept_Id == 2){
            newWorker = new manager(id, name, dept_Id);
        }else if(dept_Id == 3){
            newWorker = new employee(id, name, dept_Id);
        }

        this->workerArr[index++] = newWorker;
    }

    ifs.close();
}

// 查找对应id号职工在数组中的下标，找到返回下标，没找到返回-1
int workermanager::find_Id(int id){
    int ret;
    
    for(ret = 0; ret < this->workerNum; ret++){
        if(id == this->workerArr[ret]->getId()){
            return ret;
        }
    }

    return -1;
}

// 删除职工信息
void workermanager::delete_Emp(){
    int id;
    int index;

    // 先检查文件是否位空
    if(this->FileisEmpty){
        cout << "文件为空或数据不存在" << endl;
        system("pause");
    }else{
        cout << "请输入你要删除职工的id号(输入 -1 取消操作):";
        cin >> id;

        if(id == -1){
            cout << "操作取消" << endl;
            system("pause");
            return;
        }
        // 查找删除职工在数组中的位置
        index = this->find_Id(id);

        if(index == -1){
            cout << "id号为 " << id << " 的职工不存在" << endl;;
        }else{
            // 将被删除职工的信息放入数组最后
            worker *tmp = this->workerArr[index];
            for(int i = index; i < this->workerNum - 1; i++){
                this->workerArr[i] = this->workerArr[i+1];
            }
            this->workerArr[this->workerNum - 1] = tmp;

            this->workerNum--;
            this->recycleNum++;

            // 同步文件数据
            this->save();

            cout << "已将id号为 " << id << " 的职工删除,其信息如下：" << endl;
            cout << "------------------------------------------------------------------" << endl;
            this->workerArr[this->workerNum]->show_Info();
            cout << "------------------------------------------------------------------" << endl;
            cout << "该职工信息已加入回收站！" << endl;
        }
    }

    system("pause");
}

// 修改职工信息
void workermanager::edit_Emp(){
    // 先判断文件是否存在
    if(this->FileisEmpty){
        cout << "文件不存在或数据为空" << endl;
        system("pause");
        return;
    }

    int findId;
    int index;
    cout << "请输入你要修改的职工id号:";
    cin >> findId;
    index = this->find_Id(findId);

    if(index == -1){
        cout << "id号为" << findId << " 的职工不存在" << endl; 
    }else{
        string name;
        int id;
        int dept_Id;

        cout << "id号为 " << findId << " 的职工的原信息如下:" << endl;
        cout << "--------------------------------------------------------" << endl;
        this->workerArr[index]->show_Info();
        cout << "--------------------------------------------------------" << endl;

        cout << "请输入新的姓名:";
        cin >> name;
        this->workerArr[index]->setName(name);

        cout << "请输入新的id号:";
        // 确保所有职工的id号是唯一的
        while(1){
            cin >> id;

            // 确保输入的id号为正数
            if(id < 0){
                cout << "id号必须为正数，请重新输入:";
                continue;
            }

            if(this->find_Id(id) == -1 || this->workerArr[index]->getId() == id){
                this->workerArr[index]->setId(id);
                break;
            }else{
                cout << "该id号已被占用，请重新输入新的id号:";
            }
        }

        cout << "请输入新的职工编号\n";
        while(1){
            cout << "1. 老板" << endl;
            cout << "2. 经理" << endl;
            cout << "3. 普通职工\n:";
            cin >> dept_Id;
            if(dept_Id == BOSS || dept_Id == MANAGER || dept_Id == EMPLOYEE){
                this->workerArr[index]->setDept_Id(dept_Id);
                break;
            }else{
                cout << "输入错误，请重新输入!!" << endl;;
            }
        }

        cout << "修改成功！id号为 " << id << " 的职工的新信息如下:" << endl;
        cout << "--------------------------------------------------------" << endl;
        this->workerArr[index]->show_Info();
        cout << "--------------------------------------------------------" << endl;

        // 同步文件数据
        this->save();
    }
    
    system("pause");
}

// 查找职工信息
void workermanager::find_Emp(){
    // 先判断文件是否存在
    if(this->FileisEmpty){
        cout << "文件不存在或数据为空" << endl;
        system("pause");
        return;
    }

    int choice;
    cout << "请选择查找方式" << endl;
    cout << "1. 按id号查找" << endl;
    cout << "2. 按姓名查找" << endl;
    cin >> choice;

    if(choice == 1){
        // 按id号查找
        int findId;
        int index;
        cout << "请输入需要查找的职工id号:";
        cin >> findId;
        index = this->find_Id(findId);

        if(index == -1){
            cout << "id号为 " << findId << " 的职工不存在" << endl;
        }else{
            cout << "id号为 " << findId << " 的职工信息如下:" << endl;
            cout << "-------------------------------------------------------------" << endl;
            this->workerArr[index]->show_Info();
            cout << "-------------------------------------------------------------" << endl;
        }

    }else if(choice == 2){
        // 按姓名查找
        string findString;
        bool flag = true;
        cout << "请输入需要查找的职工姓名:";
        cin >> findString;

        cout << "-------------------------------------------------------------" << endl;
        for(int i = 0; i < this->workerNum; i++){
            if(this->workerArr[i]->getName() == findString){
                cout << "姓名为 " << findString << " 的职工信息如下:" << endl;
                this->workerArr[i]->show_Info();
                flag = false;
            }
        }

        if(flag){
            cout << "没有找到姓名为 " << findString << " 的职工" << endl;
        }
        cout << "-------------------------------------------------------------" << endl;

    }else{
        cout << "输入错误" << endl;
    }
    
    system("pause");
}

// 快排
// worker **arr ：待排数组指针
// int first：排序起始下标
// int end：排序末尾下标
// int cmp：排序方式，1为正序(从小到大)，2为反序(从大到小)
void quikSort(worker **arr, int first, int end, int cmp){
    int i = first;
    int j = end;
    worker *tmp = arr[i];

    while(i < j){
        if(cmp == 1){
            // 正序：由小到大
            while(tmp->getId() < arr[j]->getId() && i < j){
                j--;
            }
            arr[i] = arr[j];
            while(tmp->getId() > arr[i]->getId() && i < j){
                i++;
            }
            arr[j] = arr[i];
            arr[i] = tmp;
        }else if(cmp == 2){
            // 反序：由大到小
            while(tmp->getId() > arr[j]->getId() && i < j){
                j--;
            }
            arr[i] = arr[j];
            while(tmp->getId() < arr[i]->getId() && i < j){
                i++;
            }
            arr[j] = arr[i];
            arr[i] = tmp;
        }else{
            return;
        }
    }

    if(first < i - 1){
        quikSort(arr, first, i - 1, cmp);
    }

    if(end > j + 1){
        quikSort(arr, j + 1, end, cmp);
    }
}

// 按编号排序
void workermanager::sort_Id(){
    // 先判断文件是否存在
    if(this->FileisEmpty){
        cout << "文件不存在或数据为空" << endl;
        system("pause");
        return;
    }

    int choice;

    cout << "选择排序方式" << endl;
    cout << "1. 正序(从小到大)" << endl;
    cout << "2. 反序(从大到小)" << endl;
    cin >> choice;

    if(choice == 1){
        quikSort(this->workerArr, 0, this->workerNum - 1, 1);
    }else if(choice == 2){
        quikSort(this->workerArr, 0, this->workerNum - 1, 2);
    }else{
        cout << "输入错误" << endl;
        system("pause");
        return;
    }
    cout << "排序完成" << endl;
    
    // 同步文件数据
    this->save();

    system("pause");
}

// 清空所有文件
void workermanager::clear_Emp(){
    // 先判断文件是否存在
    if(this->FileisEmpty){
        cout << "文件不存在或数据为空" << endl;
        system("pause");
        return;
    }

    // 判断系统中是否有数据
    if(this->workerArr == NULL){
        cout << "数据为空，无需清空操作" << endl;
        system("pause");
        return;
    }

    int choice;
    cout << "你确认要清空所有文件吗？清空所有文件意味着你将永久失去所有数据，无法恢复" << endl;
    cout << "1. 确认" << endl;
    cout << "2. 取消" << endl;
    cin >> choice;

    if(choice == 1){
        // 清空文件
        // 打开模式：ios::trunc 如果存在，则删除文件并重新创建
        ofstream ofs(FILEADDR, ios::trunc);
        ofs.close();

        // 清空数组
        if(this->workerArr != NULL){
            for(int i = 0; i < this->workerNum; i++){
                delete this->workerArr[i];
                this->workerArr[i] = NULL; 
            }

            delete[] this->workerArr;
            this->workerArr = NULL;
            this->workerNum = 0;
            this->FileisEmpty = ISEMPTY;
        }

        cout << "操作成功" << endl;
    }else if(choice == 2){
        cout << "操作取消" << endl;
    }else{
        cout << "输入错误，操作取消" << endl;
    }

    system("pause");
}

// 回收站(退出后永久删除)
void workermanager::recycleBin(){
    while(1){
        system("cls");
        cout << "回收站：保留已删除数据，退出系统后将永久删除" << endl;
        cout << "========================================" << endl;

        if(this->recycleNum == 0){
            cout << "回收站为空" << endl;
            system("pause");
            return;
        }

        cout << "------------------------------------------------------------------------" << endl;
        for(int i = 0; i < this->recycleNum; i++){
            this->workerArr[this->workerNum + i]->show_Info();
        }
        cout << "------------------------------------------------------------------------" << endl;

        int choice;
        cout << "请输入你的选择" << endl;
        cout << "1. 恢复全部数据" << endl;
        cout << "2. 恢复部分数据" << endl;
        cout << "3. 清空回收站" << endl;
        cout << "4. 退出回收站" << endl;
    
        cin >> choice;

        if(choice == 1){        // 1. 恢复全部数据
            system("cls");
            this->workerNum += this->recycleNum;
            this->recycleNum = 0;

            // 同步文件数据
            this->save();

            cout << "操作成功！！" << endl;
            system("pause");

        }else if(choice == 2){  // 2. 恢复部分数据
            int id;
            int index = -1;
            
            cout << "请输入需要恢复数据的id号:";
            cin >> id;

            for(int i = 0; i < this->recycleNum; i++){
                // int n = ;
                if(this->workerArr[this->workerNum + i]->getId() == id){
                    index = this->recycleNum + i;
                    break;
                }
            }

            if(index == -1){
                cout << "需要恢复数据的id号不存在" << endl;
                system("pause");
            }else{
                // 将恢复的数据放到数组中最后一个位置
                worker *tmp = this->workerArr[this->workerNum];
                this->workerArr[this->workerNum] = this->workerArr[index];
                this->workerArr[index] = tmp;

                // 增加职工数量，减少回收站中的人数
                this->workerNum++;
                this->recycleNum--;

                // 同步文件数据
                this->save();

                cout << "操作成功！！" << endl;
                system("pause");
            }

        }else if(choice == 3){  // 3. 清空回收站
            system("cls");
            int choice;

            cout << "确定要清空回收站吗！！" << endl;
            cout << "1. 确定" << endl;
            cout << "2. 取消" << endl;
            cin >> choice;

            if(choice == 1){
                for(int i = 0; i < this->recycleNum; i++){
                    delete this->workerArr[this->workerNum + i];
                    this->workerArr[this->workerNum + i] = NULL;
                }

                // 更新回收站中的人数
                this->recycleNum = 0;

                cout << "操作成功！！" << endl;
            }else if(choice == 2){
                cout << "取消操作" << endl;
                system("pause");
            }

        }else if(choice == 4){  // 4. 退出回收站
            cout << "退出成功！！" << endl;
            system("pause");

            break;
        }else{
            cout << "输入错误，请重新输入:";
            system("puase");
        }
    }
}