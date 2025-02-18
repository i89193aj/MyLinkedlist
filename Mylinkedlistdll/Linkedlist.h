#pragma once
// 定義宏區區分 DLL 的導入與導出
#define BUILDING_DLL

#ifdef BUILDING_DLL
#define DLL_API __declspec(dllexport)  // 導出符號
#else
#define DLL_API __declspec(dllimport)  // 導入符號
#endif

#include <iostream>
#include <string>

// 节点类定义
template<typename T>
class DLL_API Node {
public:
    T val;
    Node<T>* next;

    Node(T val) : val(val), next(nullptr) {}
};

// MyLinkedlist 類定義
template <typename T>
class DLL_API MyLinkedlist {
private:
    Node<T>* Header;

    enum MyType {
        arithmetic,
        MyString,
        Other,
    };

public:
    MyLinkedlist();
    MyLinkedlist(const MyLinkedlist& _MyLinkedlist);
    void Append(T _val);
    void pop();
    void DeleteNode(T _val, bool IsAll = true);
    void Insert(int _location, T _val);
    void RemoveAt(int _location);
    T GetCopyValueAt(int position);
    const T& GetValueAt(int position);
    void* GetNextNode();

    std::string printfIntAll();
    std::string printstringAll();

    ~MyLinkedlist();
};

// 顯示實例化模板，以便在 DLL 中生成特定類型
extern template class DLL_API MyLinkedlist<int>;
extern template class DLL_API MyLinkedlist<std::string>;
