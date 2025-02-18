#include "pch.h";
#include "Linkedlist.h"
#include <vector>
#include <string>

template class MyLinkedlist<int>;
template class MyLinkedlist<std::string>;

// 創建鏈表
void* CreateLinkedListInt() {
    return new MyLinkedlist<int>();  // 返回新建的 MyLinkedlist<int> 對象
}

void* CreateLinkedListString() {
    return new MyLinkedlist<std::string>();  // 返回新建的 MyLinkedlist<std::string> 對象
}

// 插入整數
void AppendInt(void* list, int value) {
    static_cast<MyLinkedlist<int>*>(list)->Append(value);
}

// 插入字串
void AppendString(void* list, const char* value) {
    static_cast<MyLinkedlist<std::string>*>(list)->Append(std::string(value));
}

// 取得指定索引的整數
int GetIntAt(void* list, int index) {
    return static_cast<MyLinkedlist<int>*>(list)->GetValueAt(index);
}

// 取得指定索引的字串
const char* GetStringAt(void* list, int index) {
    try {
        return static_cast<MyLinkedlist<std::string>*>(list)->GetValueAt(index).c_str();
    }
    catch (const std::out_of_range& e) {
        return nullptr;  // 如果索引超出範圍，返回空指標
    }
}

const char* GetStringCopyAt(void* list, int index) {
    try {
        std::string result = static_cast<MyLinkedlist<std::string>*>(list)->GetCopyValueAt(index);
        char* copy = new char[result.size() + 1];
        //strncpy_s(dest, sizeof(dest), source, sizeof(dest) - 1)
        strncpy_s(copy, sizeof(copy), result.c_str(), sizeof(copy) - 1);  // 確保不會超過目標大小
        //copy[sizeof(copy) - 1] = '\0';  // 確保字符串以終止符結尾
        //strcpy(copy, result.c_str()); 用這個有機會stackflow
        return copy;  // 讓 C# 來 `free()`
    }
    catch (const std::out_of_range& e) {
        return nullptr;
    }
}

//DeepCopy Int
void* CreateLinkedListIntFromExisting(void* list) {
    // 先將 void* 類型轉換成 MyLinkedlist<std::string>* 類型
    MyLinkedlist<int>* existingList = static_cast<MyLinkedlist<int>*>(list);

    // 使用深度複製構造函數創建新的鏈表
    return new MyLinkedlist<int>(*existingList);
}
//DeepCopy string
void* CreateLinkedListStringFromExisting(void* list) {
    // 先將 void* 類型轉換成 MyLinkedlist<std::string>* 類型
    MyLinkedlist<std::string>* existingList = static_cast<MyLinkedlist<std::string>*>(list);

    // 使用深度複製構造函數創建新的鏈表
    return new MyLinkedlist<std::string>(*existingList);
}

//Pop刪除末端 Int
void PopListInt(void* list) {
    static_cast<MyLinkedlist<int>*>(list)->pop();
}
//Pop刪除末端 string
void PopListstring(void* list) {
    static_cast<MyLinkedlist<std::string>*>(list)->pop();
}

//刪除值 Int
void DeleteInt(void* list, int _val, bool IsAll = false) {
    static_cast<MyLinkedlist<int>*>(list)->DeleteNode(_val, IsAll);
}
//刪除值 string
void Deletestring(void* list, const char* _val, bool IsAll = false) {
    std::string val(_val);  // 將 const char* 轉換為 std::string
    static_cast<MyLinkedlist<std::string>*>(list)->DeleteNode(val, IsAll);
}

//Insert位置  
void InsertInt(void* list, int _location, int _val) {
    static_cast<MyLinkedlist<int>*>(list)->Insert(_location, _val);
}
//刪除值 string
void Insertstring(void* list, int _location, const char* _val) {
    std::string val(_val);  // 將 const char* 轉換為 std::string
    static_cast<MyLinkedlist<std::string>*>(list)->Insert(_location, val);
}

//移除哪個位置
void RemoveAtInt(void* list, int _location) {
    static_cast<MyLinkedlist<int>*>(list)->RemoveAt(_location);
}
//移除哪個位置
void RemoveAtString(void* list, int _location) {
    static_cast<MyLinkedlist<std::string>*>(list)->RemoveAt(_location);
}

const char* PrintAllInt(void* list) {
    std::string result = static_cast<MyLinkedlist<int>*>(list)->printfIntAll();//.c_str()用這個會變成野指標（Dangling Pointer）
    char* copy = new char[result.size() + 1];
    strncpy_s(copy, result.size() + 1, result.c_str(), result.size());  // 正確拷貝整個字串

    //strcpy(copy, result.c_str());
    return copy;  // 讓 C# 來 `free()`
}

const char* PrintAllIstring(void* list) {
    std::string result = static_cast<MyLinkedlist<std::string>*>(list)->printstringAll();

    char* copy = new char[result.size() + 1];  // 分配正確大小
    strncpy_s(copy, result.size() + 1, result.c_str(), result.size());  // 正確拷貝整個字串

    return copy;  // 讓 C# 來 `free()`
}


// 釋放鏈表記憶體( ~MyLinkedlist()) 會自動呼叫
void DeleteLinkedListInt(void* list) {
    delete static_cast<MyLinkedlist<int>*>(list);
}

void DeleteLinkedListString(void* list) {
    delete static_cast<MyLinkedlist<std::string>*>(list);
}

void FreeString(char* str) {
    delete[] str;  // 假設是使用 new[] 分配的內存
}

void* GetNextNode(void* list){
    if (!list) return nullptr;
    return static_cast<MyLinkedlist<int>*>(list)->GetNextNode();
}


