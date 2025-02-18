/*Oscar Linkedlist*/
//#include "pch.h";
#include <iostream>
#include"Linkedlist.h"

using namespace std;

// 顯式實例化模板以便在 DLL 中包含特定類型
template class DLL_API MyLinkedlist<int>;
template class DLL_API MyLinkedlist<std::string>;

#ifndef NOBUILDING_DLL  //#ifdef BUILDING_DLL
int main()
{
    MyLinkedlist<int>* list1 = new MyLinkedlist<int>();
    MyLinkedlist<int>* list2;
    std::cout << "Hello World!\n";
}
#endif

/// <summary>
/// Contructor
/// </summary>
/// <param name="_MyLinkedlist"></param>
template <typename T>
MyLinkedlist<T>::MyLinkedlist()
{
    Header = nullptr;  // 開始時設置為空
};

/// <summary>
/// DeepCopy
/// </summary>
/// <param name="_MyLinkedlist"></param>
template <typename T>
MyLinkedlist<T>::MyLinkedlist(const ::MyLinkedlist<T>& _MyLinkedlist)
{
    Header = nullptr;  // 開始時設置為空

    Node<T>* temp = _MyLinkedlist.Header; // 遍歷原鏈表
    // 添加到新鏈表的尾部
    while (temp != nullptr) {
        Append(temp->val); //裡面會把Header指向new出來的新節點
        temp = temp->next;
    }
    cout << "Linked List Deep Copied" << endl;
};

/// <summary>
/// 在list末端增加元素 
/// </summary>
/// <param name="_val"></param>
template <typename T>
void MyLinkedlist<T>::Append(T _val) {
    Node<T>* newNode = new Node<T>(_val); //創建記憶體
    if (Header == nullptr) {
        Header = newNode;  // 如果鏈表是空的，將新節點設為頭節點
    }
    else {
        Node<T>* temp = Header;
        // 找到鏈表的最後一個節點
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;  // 將新節點連接到最後
    }
}

/// <summary>
/// 刪除最後一個元素
/// </summary>
template <typename T>
void MyLinkedlist<T>::pop() {
    //無節點
    if (!Header) return;

    //如果只有一個節點
    if (!Header->next)
    {
        delete Header;
        Header = nullptr;
        return;
    }

    //刪除最後一個節點
    Node<T>* temp = Header;
    while (temp->next && temp->next->next) {
        temp = temp->next;
    }

    delete temp->next;
    temp->next = nullptr;
}

/// <summary>
/// 刪除節點
/// </summary>
/// <param name="_val"></param>
/// <param name="IsAll(delete all)"></param>
template <typename T>
void MyLinkedlist<T>::DeleteNode(T _val, bool IsAll) {
    if (!Header) return;

    // 先刪除開頭的匹配節點
    while (Header && Header->val == _val) {
        Node<T>* temp = Header;
        Header = Header->next;
        delete temp;
        if (!IsAll) return;  // 若 IsAll 為 false，刪除第一個匹配值後立即返回
    }

    // 刪除其他匹配節點
    Node<T>* temp = Header;
    while (temp && temp->next) {
        if (temp->next->val == _val) {
            Node<T>* delnode = temp->next;
            temp->next = temp->next->next;
            delete delnode;
            if (!IsAll) return;
        }
        else {
            temp = temp->next;
        }
    }
}

/// <summary>
/// 插入值
/// </summary>
/// <param name="_location"></param>
/// <param name="_val"></param>
template <typename T>
void MyLinkedlist<T>::Insert(int _location, T _val) {
    // 檢查 _location 是否有效
    if (_location < 0) {
        std::cout << "Invalid location!" << std::endl;
        throw std::out_of_range("Location cannot be negative.");
    }

    Node<T>* NewNode = new Node<T>(_val);

    // 插入到頭部的位置 (_location == 0)(容易忘記想到)
    if (_location == 0) {
        NewNode->next = Header;
        Header = NewNode;
        return;
    }

    // 插入到非頭部位置 (_location > 0)
    Node<T>* temp = Header;
    int iStep = 0;

    // 遍歷到插入位置的前一個節點
    while (temp && ++iStep != _location) {
        temp = temp->next;
    }

    // 如果遍歷完了還找不到位置，表示位置超出了鏈表的長度，應拋出異常
    if (!temp) {
        std::cout << "Invalid location!" << std::endl;
        throw std::out_of_range("Location out of bounds.");
    }

    // 插入新節點
    NewNode->next = temp->next;
    temp->next = NewNode;
}

template <typename T>
void MyLinkedlist<T>::RemoveAt(int _location) {
    if (_location < 0) throw std::out_of_range("Invalid location!");

    Node<T>* temp = Header;
    if (_location == 0) {
        if (Header) Header = Header->next;
        delete temp;
        temp = nullptr;
        return;
    }

    int istep = 0;
    while (temp && ++istep != _location) {
        temp = temp->next;
    }

    if (!temp || !temp->next) throw std::out_of_range("Invalid location!");
    Node<T>* deltemp = temp->next;
    temp->next = temp->next->next;
    delete deltemp;
}

template <typename T>
string MyLinkedlist<T>::printstringAll() {
    if (!Header) return "";

    if constexpr (!std::is_same<T, std::string>::value) {
        // 其他情況，返回一個預設的字符串表示
        return "Unsupported type";
    }

    Node<T>* temp = Header; string _sAns = "";
    while (temp) {
        _sAns += temp->val;
        temp = temp->next;
    }
    return _sAns;
}

string MyLinkedlist<int>::printfIntAll() {
    if (!Header) return "";

    if constexpr (!std::is_arithmetic<int>::value) {
        // 其他情況，返回一個預設的字符串表示
        return "Unsupported type";
    }

    Node<int>* temp = Header; string _sAns = "";
    while (temp) {
        _sAns += to_string(temp->val);//前面有namespace後面就不用加std::
        temp = temp->next;
    }
    return _sAns;
}

template <typename T>
T MyLinkedlist<T>::GetCopyValueAt(int position) {
    if (position < 0) {
        throw std::out_of_range("Position cannot be negative.");
    }

    Node<T>* temp = Header;
    int currentPosition = 0;

    // 遍歷鏈表，直到找到指定位置的節點
    while (temp != nullptr) {
        if (currentPosition == position) {
            return temp->val;
        }
        temp = temp->next;
        currentPosition++;
    }

    // 如果位置超出了鏈表範圍，拋出異常
    throw std::out_of_range("Position out of bounds.");
}

template <typename T>
const T& MyLinkedlist<T>::GetValueAt(int position) {
    if (position < 0) {
        throw std::out_of_range("Position cannot be negative.");
    }

    Node<T>* temp = Header;
    int currentPosition = 0;

    // 遍歷鏈表，直到找到指定位置的節點
    while (temp != nullptr) {
        if (currentPosition == position) {
            return temp->val;  // 直接返回節點內的值，避免拷貝
        }
        temp = temp->next;
        currentPosition++;
    }

    throw std::out_of_range("Position out of bounds.");
}

template <typename T>
MyLinkedlist<T>::~MyLinkedlist() {
    Node<T>* temp = Header;
    while (temp) {
        Node<T>* nextNode = temp->next;  // 保存下一個節點的指標
        delete temp;  // 釋放當前節點
        temp = nextNode;  // 移動到下一個節點
    }
    // 最後將Header設為nullptr，確保指針被清空，防止懸空指標
    Header = nullptr;
}

template <typename T>
void* MyLinkedlist<T>::GetNextNode() {
    if (!Header) return nullptr;
        return Header->next;
}
    
//Reverse
