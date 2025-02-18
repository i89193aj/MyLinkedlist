#include "pch.h";
#include "Linkedlist.h"
#include <vector>
#include <string>

template class MyLinkedlist<int>;
template class MyLinkedlist<std::string>;

// �Ы����
void* CreateLinkedListInt() {
    return new MyLinkedlist<int>();  // ��^�s�ت� MyLinkedlist<int> ��H
}

void* CreateLinkedListString() {
    return new MyLinkedlist<std::string>();  // ��^�s�ت� MyLinkedlist<std::string> ��H
}

// ���J���
void AppendInt(void* list, int value) {
    static_cast<MyLinkedlist<int>*>(list)->Append(value);
}

// ���J�r��
void AppendString(void* list, const char* value) {
    static_cast<MyLinkedlist<std::string>*>(list)->Append(std::string(value));
}

// ���o���w���ު����
int GetIntAt(void* list, int index) {
    return static_cast<MyLinkedlist<int>*>(list)->GetValueAt(index);
}

// ���o���w���ު��r��
const char* GetStringAt(void* list, int index) {
    try {
        return static_cast<MyLinkedlist<std::string>*>(list)->GetValueAt(index).c_str();
    }
    catch (const std::out_of_range& e) {
        return nullptr;  // �p�G���޶W�X�d��A��^�ū���
    }
}

const char* GetStringCopyAt(void* list, int index) {
    try {
        std::string result = static_cast<MyLinkedlist<std::string>*>(list)->GetCopyValueAt(index);
        char* copy = new char[result.size() + 1];
        //strncpy_s(dest, sizeof(dest), source, sizeof(dest) - 1)
        strncpy_s(copy, sizeof(copy), result.c_str(), sizeof(copy) - 1);  // �T�O���|�W�L�ؼФj�p
        //copy[sizeof(copy) - 1] = '\0';  // �T�O�r�Ŧ�H�פ�ŵ���
        //strcpy(copy, result.c_str()); �γo�Ӧ����|stackflow
        return copy;  // �� C# �� `free()`
    }
    catch (const std::out_of_range& e) {
        return nullptr;
    }
}

//DeepCopy Int
void* CreateLinkedListIntFromExisting(void* list) {
    // ���N void* �����ഫ�� MyLinkedlist<std::string>* ����
    MyLinkedlist<int>* existingList = static_cast<MyLinkedlist<int>*>(list);

    // �ϥβ`�׽ƻs�c�y��ƳЫطs�����
    return new MyLinkedlist<int>(*existingList);
}
//DeepCopy string
void* CreateLinkedListStringFromExisting(void* list) {
    // ���N void* �����ഫ�� MyLinkedlist<std::string>* ����
    MyLinkedlist<std::string>* existingList = static_cast<MyLinkedlist<std::string>*>(list);

    // �ϥβ`�׽ƻs�c�y��ƳЫطs�����
    return new MyLinkedlist<std::string>(*existingList);
}

//Pop�R������ Int
void PopListInt(void* list) {
    static_cast<MyLinkedlist<int>*>(list)->pop();
}
//Pop�R������ string
void PopListstring(void* list) {
    static_cast<MyLinkedlist<std::string>*>(list)->pop();
}

//�R���� Int
void DeleteInt(void* list, int _val, bool IsAll = false) {
    static_cast<MyLinkedlist<int>*>(list)->DeleteNode(_val, IsAll);
}
//�R���� string
void Deletestring(void* list, const char* _val, bool IsAll = false) {
    std::string val(_val);  // �N const char* �ഫ�� std::string
    static_cast<MyLinkedlist<std::string>*>(list)->DeleteNode(val, IsAll);
}

//Insert��m  
void InsertInt(void* list, int _location, int _val) {
    static_cast<MyLinkedlist<int>*>(list)->Insert(_location, _val);
}
//�R���� string
void Insertstring(void* list, int _location, const char* _val) {
    std::string val(_val);  // �N const char* �ഫ�� std::string
    static_cast<MyLinkedlist<std::string>*>(list)->Insert(_location, val);
}

//�������Ӧ�m
void RemoveAtInt(void* list, int _location) {
    static_cast<MyLinkedlist<int>*>(list)->RemoveAt(_location);
}
//�������Ӧ�m
void RemoveAtString(void* list, int _location) {
    static_cast<MyLinkedlist<std::string>*>(list)->RemoveAt(_location);
}

const char* PrintAllInt(void* list) {
    std::string result = static_cast<MyLinkedlist<int>*>(list)->printfIntAll();//.c_str()�γo�ӷ|�ܦ������С]Dangling Pointer�^
    char* copy = new char[result.size() + 1];
    strncpy_s(copy, result.size() + 1, result.c_str(), result.size());  // ���T������Ӧr��

    //strcpy(copy, result.c_str());
    return copy;  // �� C# �� `free()`
}

const char* PrintAllIstring(void* list) {
    std::string result = static_cast<MyLinkedlist<std::string>*>(list)->printstringAll();

    char* copy = new char[result.size() + 1];  // ���t���T�j�p
    strncpy_s(copy, result.size() + 1, result.c_str(), result.size());  // ���T������Ӧr��

    return copy;  // �� C# �� `free()`
}


// �������O����( ~MyLinkedlist()) �|�۰ʩI�s
void DeleteLinkedListInt(void* list) {
    delete static_cast<MyLinkedlist<int>*>(list);
}

void DeleteLinkedListString(void* list) {
    delete static_cast<MyLinkedlist<std::string>*>(list);
}

void FreeString(char* str) {
    delete[] str;  // ���]�O�ϥ� new[] ���t�����s
}

void* GetNextNode(void* list){
    if (!list) return nullptr;
    return static_cast<MyLinkedlist<int>*>(list)->GetNextNode();
}


