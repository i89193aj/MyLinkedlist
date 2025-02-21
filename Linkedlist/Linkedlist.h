#pragma once
// 定義宏區區分 DLL 的導入與導出
#define BUILDING_DLL

#ifdef BUILDING_DLL
#define DLL_API __declspec(dllexport)  // 導出符號
#else
#define DLL_API __declspec(dllimport)  // 導入符號
#endif

#include <string>
#include <iostream>
#include <vector>       // 若成員變數用到 std::vector
#include <map>          // 若有 std::map 變數
#include <unordered_map>// 若有 std::unordered_map 變數



// 節點類定義
template<typename T>
class DLL_API Node {
public:
    T val;
    Node<T>* next;
    Node<T>* random;

    Node(T val) : val(val), next(nullptr), random(nullptr) {}
    Node(T val, Node<T>* next) : val(val), next(next), random(nullptr) {}
    Node(T val, Node<T>* next, Node<T>* random) : val(val), next(next), random(random) {}

};

// MyLinkedlist 類定義
template <typename T>
class DLL_API MyLinkedlist {
private:
    //Node<T>* Header;

    enum MyType {
        arithmetic,
        MyString,
        Other,
    };

public:
    Node<T>* Header;
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

    // ======= Leetcode Solutions =======
    Node<T>* Leetcode_Sol_21(Node<T>* list1, Node<T>* list2, int _Soluttion_idx);
    Node<T>* Leetcode_Sol_19(Node<T>* head, int n, int _solution);
    bool Leetcode_Sol_141(Node<T>* head);
    Node<T>* Leetcode_Sol_876(Node<T>* head, int _solution);
    Node<T>* Leetcode_Sol_160(Node<T>* headA, Node<T>* headB, int _solution);
    Node<T>* Leetcode_Sol_142(Node<T>* head, int _solution);
    Node<T>* Leetcode_Sol_138(Node<T>* head, int _solution);
    Node<T>* Leetcode_Sol_61(Node<T>* head,int k, int _solution);
    Node<T>* Leetcode_Sol_2(Node<T>* list1, Node<T>* list2, int _Soluttion_idx);
    bool Leetcode_Sol_234(Node<T>* head, int _solution);
    Node<T>* Leetcode_Sol_203(Node<T>* head, T val, int _solution);
    Node<T>* Leetcode_Sol_83(Node<T>* head, int _solution);
    void Leetcode_Sol_237(Node<T>* node, int _solution);



    // ======= Leetcode Solutions =======
};

template <typename T>
void PrintLinkedlist(Node<T>* _node);
template <typename T> void CopyWithVector(Node<T>* _node,const std::vector <T>& _vector);

// 顯示實例化模板，以便在 DLL 中生成特定類型
extern template class DLL_API MyLinkedlist<int>;
extern template class DLL_API MyLinkedlist<std::string>;

#pragma region OOP
/*
class Base {
public:
    virtual void foo() = 0;  // 純虛擬函式
};

class Derived : public Base {
    // ❌ 沒有覆寫 foo()，所以仍然是抽象類別
};

class MoreDerived : public Derived {
public:
    void foo() override {  // ✅ MoreDerived 有覆寫 foo()
        std::cout << "MoreDerived foo()" << std::endl;
    }
};

如果你想建立該類的物件，子類就「一定要」覆寫純虛擬函式。
如果子類仍然是抽象類別，就不一定要覆寫純虛擬函式。
C++11 之後允許純虛擬函式 = 0 但仍提供函式體，可作為預設行為。
*/
#pragma endregion


