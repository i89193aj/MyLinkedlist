/*Oscar Linkedlist*/
//#include "pch.h";
#include <iostream>
#include <cstdlib>  // rand(), srand()
#include <ctime>    // time()
#include <random>   // C++11 亂數庫
#include <vector>   // std::vector
#include <numeric>  // std::iota
#include"Linkedlist.h"
#include <map>      //std::map
#include <unordered_map>  //std::unordered_map
using namespace std;

// 顯式實例化模板以便在 DLL 中包含特定類型
template class DLL_API MyLinkedlist<int>;
template class DLL_API MyLinkedlist<std::string>;

enum LeetcodeExam {
    Leetcode138_CopyListwithRandomPointer,



    None,
};

#ifndef NOBUILDING_DLL  //#ifdef BUILDING_DLL
int main()
{
    #pragma region Leetcode program Test
    /*
       要寫的題目只要改：
       1.ExamEnum(題號).2.LinkedlistInput1、LinkedlistInput2(輸入)
    */
    LeetcodeExam ExamEnum = Leetcode138_CopyListwithRandomPointer;//ChangeForExam
    MyLinkedlist<int>* list1 = new MyLinkedlist<int>();
    MyLinkedlist<int>* list2 = new MyLinkedlist<int>();
    vector<int> LinkedlistInput1 = { 7,13,11,10,1 }; //ChangeForExam
    vector<int> LinkedlistInput2 = { 7,13,11,10,1 }; //ChangeForExam

    Node<int>* Dummy = new Node<int>(-1); Node<int>* prev = Dummy;
    Node<int>* headerInput1 = new Node<int>(LinkedlistInput1[0]); Node<int>* current1 = headerInput1;// current1 = list1->Header;(也可以用寫好的物件)
    Node<int>* headerInput2 = new Node<int>(LinkedlistInput1[0]); Node<int>* current2 = headerInput1;
    Node<int>* pointer = headerInput1; Node<int>* ans;
    CopyWithVector(headerInput1, LinkedlistInput1);
    CopyWithVector(headerInput2, LinkedlistInput2);

    switch (ExamEnum)
    {
    #pragma region Leetcode 138. Copy List with Random Pointer
    case Leetcode138_CopyListwithRandomPointer: {
        int* shift_138 = new int[] {5, 0, 4, 2, 0};//0 7 1 11 7 補充：C++的case不能在裡面宣告：解法1.外面加"{}" 解法2.把宣告定義弄在外面
        for (auto num : LinkedlistInput1) {
            int j = *shift_138;
            while (j > 0) {
                pointer = pointer->next;
                j--;
            }
            current1->random = pointer;
            current1 = current1->next;
            pointer = headerInput1;
            shift_138++;
        }
        current1 = headerInput1;
        PrintLinkedlist(current1);
        ans = list1->Leetcode_Sol_138(headerInput1, 1); //copyRandomList(node1);
        PrintLinkedlist(current1);
        PrintLinkedlist(ans);

        break; 
    }
    #pragma endregion

        
        default:
            break;
    }  
    #pragma endregion



    #pragma region random_device
    //srand(time(nullptr)); // 用目前時間作為隨機種子
    int randomNumber = rand() % 100 + 1; // 產生 1~100 之間的數字

    //比 rand() 更隨機，適合密碼學、模擬等需求。
    std::random_device rd;  // 取得隨機種子（硬體隨機數）
    std::mt19937 gen(rd()); // 使用 Mersenne Twister 演算法
    std::uniform_int_distribution<int> dist(1, 100); // 產生範圍 1~100
    int randomNumber2 = dist(gen);
    #pragma endregion

    #pragma region vector
    std::vector<int>vec1(10);               // 建立 100 個元素未初始化
    std::vector<int> vec2(10, 0);           // 建立 100 個元素，每個都是 0
    std::vector<int> vec3(10);
    std::iota(vec3.begin(), vec3.end(), 0);  // 填入 0 到 99 (也可以)
    #pragma endregion

    #pragma region Map
    // 自訂比較函數（降序排列）
    struct Descending {
        bool operator()(int a, int b) const {
            return a > b; // 讓 key 由大到小排序
        }
    };
    std::map<int, std::string, Descending> m1;

    // 自訂相等函數
    struct MyEqual {
        bool operator()(const std::pair<int, int>& a, const std::pair<int, int>& b) const {
            return a.first == b.first && a.second == b.second; //first 是key，second是value
        }
    };

    // 自訂 hash 函數
    /* size_t：
    size_t 是 C/C++ 裡的一種 無符號整數類型，專門用來表示物件的大小或索引。它的具體大小取決於你的系統架構：
    32 位元系統：size_t 是 4 bytes（32 位元），範圍是 0 ~ 4,294,967,295
    64 位元系統：size_t 是 8 bytes（64 位元），範圍是 0 ~ 18,446,744,073,709,551,615
    📝 重點：
    無符號：保證為正數，因為負的大小沒有意義
    跨平台：根據編譯器與硬體架構自動調整大小
    */
    struct MyHash {
        std::size_t operator()(const std::pair<int, int>& p) const {
            return std::hash<int>()(p.first) ^ std::hash<int>()(p.second);//^ 是 XOR（異或運算）
        }
    };

    /*
    ✅XOR (^)：用來混合 p.first 和 p.second 的哈希值，使得 unordered_map 的 key 分佈更均勻。
    ✅ << 1 左移：讓 p.second 的 bit pattern 變化，降低碰撞機率。
    ✅ 可能的進一步優化：可以用 * 31 等技巧來減少模式碰撞。
    ✅ 效果：這樣的設計可以讓 unordered_map<std::pair<int, int>> 減少哈希碰撞，提升存取速度。
    */
    struct PairHash {
        size_t operator()(const std::pair<int, int>& p) const {
            return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
        }
    };

    std::unordered_map<std::pair<int, int>, std::string, MyHash, MyEqual> umap;
    umap[std::make_pair(1, 2)] = "apple";
    umap[std::make_pair(3, 4)] = "banana";

    for (const auto& [key, value] : umap) {
        std::cout << "(" << key.first << ", " << key.second << "): " << value << '\n';
    }

    //Lambda 排序
    auto cmp = [](int a, int b) { return a > b; };
    std::map<int, std::string, decltype(cmp)> m(cmp);//decltype 精確獲取表達式的原始類型，不會調整型別。

    //插入(insert / operator[] / emplace)
    m.insert({ 4, "dog" });  // 插入 (不覆蓋)
    m[5] = "elephant";     // 插入 (會覆蓋舊值)
    m.emplace(6, "fox");   // 插入 (更高效)

    //查找(find / count)
    if (m.find(3) != m.end()) std::cout << "找到 key 3\n";
    if (m.count(3)) std::cout << "key 3 存在\n";

    //遍歷(for / iterator)
    for (const auto& [key, value] : m) { std::cout << key << ": " << value << '\n'; }
    for (auto it = m.begin(); it != m.end(); ++it) { std::cout << it->first << ": " << it->second << '\n'; }

    //刪除(erase)
    m.erase(2); // 刪除 key 為 2 的元素
    m.clear();  // 清空整個 map
    #pragma endregion

    #pragma region Set

    #pragma endregion

    #pragma region for
    //1.基本 for 迴圈 (經典寫法)
    for(int i = 0;i < vec1.size();i++)
        std::cout << vec1[i] << " ";  // 輸出每個元素
    //2.範圍 for 迴圈 (range-based for loop)
    for (int n : vec1) 
        std::cout << n << " ";        // 輸出每個元素
    //3.使用 auto 自動推導型別
    //只讀取並遍歷 (不修改)
    for (auto n : vec1) 
        std::cout << n << " ";        // 輸出每個元素

    //讀取並修改每個元素(使用 & 參考)
    for (auto& n : vec1) 
        std::cout << n << " ";        // 輸出每個元素

    //讀取並使用 const (避免修改)
    for (const auto& n : vec1) 
        std::cout << n << " ";        // 輸出每個元素
    //4.使用 auto 搭配迭代器(iterator)
    for (auto it = vec1.begin(); it != vec1.end(); ++it) { // ✅ 使用迭代器遍歷
        std::cout << *it << " ";
    }
#pragma endregion


}
#endif
template <typename T>/*請在.h檔也加入*/
void PrintLinkedlist(Node<T>* _node) {
    while (_node) {
        cout << "Value: " << _node->val << ", Address:" << _node;
        if (_node->random)
            cout << ", Random: " << _node->random->val << ", Address:" << _node->random;
        else
            cout << ", Random: NULL";
        cout << endl;
        _node = _node->next;
    }
    cout << endl;
}
template <typename T>/*請在.h檔也加入*/
void CopyWithVector(Node<T>* _node,const vector<T>& _vector) {
    for (size_t i = 1; i < _vector.size(); i++) {
        Node<int>* newnode = new Node<int>(_vector[i]);
        _node->next = newnode;
        _node = _node->next;
    }
}



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
 
#pragma region Leetcode 206. Reverse Linked List
//Leetcode 206. Reverse Linked List
template<typename T>
Node<T>* Leetcode_Sol_206(Node<T>* head) {
    if (!head || !head->next)  return head;

    Node<T>* temp = head->next;
    Node<T>* newnode = reverseList(temp);
    temp->next = head;
    head->next = nullptr;
    return newnode;

#pragma region Iterator

    //if (!head) return nullptr;

    //Node<T>* current = head;
    //Node<T>* prev = nullptr;
    //while (current) {
    //    Node<T>* nextNode = current->next;  // 暫存下一個節點
    //    current->next = prev;               // 反轉指向
    //    prev = current;                     // 更新 prev
    //    current = nextNode;                 // 移動到下一個節點
    //}
    //return prev;
#pragma endregion
}
#pragma endregion


#pragma region Leetcode 92. Reverse Linked List II
//Leetcode 92. Reverse Linked List II
template<typename T>
Node<T>* Leetcode_Sol_92(Node<T>* Head, int _left, int _Right) {
    if (!Head) return nullptr;
    if (!Head->next) return Head;

    Node<T>* current = Head; Node<T>* prev = nullptr; Node<T>* Leftnode = nullptr;
    int iStep = 1;
    if (_left != 1)
    {
        while (current) {
            if (iStep == _left - 1) {
                prev = current;
                Leftnode = current; //紀錄要反轉左節點的前一個節點
                current = current->next;
                break;
            }
            //else if (iStep == _Right-1) {
            //    Rightnode = newnode;//紀錄要反轉的左節點的前一個節點(沒屁用)
            //    break;
            //}
            current = current->next;
            iStep++;
        }
    }

    iStep = _left;
    while (iStep != _Right + 1) {
        Node<T>* temp = current->next;//紀錄本節點的下節點
        current->next = prev;       //本次節點指回上節點
        prev = current;               //上節點移動到本節點
        current = temp;               //本節點移動到下節點
        iStep++;
    }
    //prev會在當前_Right上面，newnode會在_Right下一個
    if (Leftnode)//left!=1
    {
        Leftnode->next->next = current;
        Leftnode->next = prev;
    }
    else//left == 1
    {
        Head->next = current;
        Head = prev;
    }

    return Head;
}
#pragma endregion


#pragma region Leetcode 21. Merge Two Sorted Lists
//Leetcode 21. Merge Two Sorted Lists
template<typename T>
Node<T>* MyLinkedlist<T>::Leetcode_Sol_21(Node<T>* list1, Node<T>* list2,int _Soluttion_idx) {
    switch (_Soluttion_idx)
    {
    case 1:
        return mergeTwoLists1(list1, list2);
    case 2:
        return mergeTwoLists2(list1, list2);
    case 3:
        return mergeTwoLists3(list1, list2);
    default:
        break;
    }

    return nullptr;
}
//Select Sort(list1 list2 is Sorted)
template<typename T>
Node<T>* mergeTwoLists1(Node<T>* list1, Node<T>* list2) {
    if (!list1 && !list2) return list1;
    int iTotalNode = 0;  Node<T>* templist = nullptr;
    Node<T>* Header1 = list1 ? list1 : list2;
    Node<T>* Header2 = Header1 == list1 ? list2 : list1;
    templist = Countlist(Header1, iTotalNode);
    templist->next = Header2;
    Countlist(Header2, iTotalNode);
    SortLinkedlist(Header1, ++iTotalNode);
    return Header1;
}

template<typename T>
Node<T>* SortLinkedlist(Node<T>* Srclist, int _iTotal) {
    Node<T>* current = Srclist;
    T swap{};

    while (_iTotal > 0) {
        while (current && current->next) {
            if (current->val <= current->next->val) {
                current = current->next;
            }
            else {
                swap = current->next->val;
                current->next->val = current->val;
                current->val = swap;
                current = current->next;
            }
        }
        current = Srclist;
        _iTotal--;
    }
    return Srclist;
}

template<typename T>
Node<T>* Countlist(Node<T>* Srclist, int& _iTotalNode) {
    Node<T>* templist = Srclist;
    if (!templist) return templist;

    while (templist->next) {
        templist = templist->next;
        _iTotalNode++;
    }
    return templist;
}

//MergeSort(list1 list2 is Sorted)
template<typename T>
Node<T>* mergeTwoLists2(Node<T>* list1, Node<T>* list2) {
    T val{};
    Node<T>* Dummy = new Node<T>(val);
    Node<T>* Ptr = Dummy;

    while (list1 && list2) {
        if (list1->val >= list2->val) {
            Ptr->next = list1;
            list1 = list1->next;
        }
        else {
            Ptr->next = list2;
            list2 = list2->next;
        }
        Ptr = Ptr->next;
    }
    Ptr->next = list1 ? list1 : list2;
    return Dummy->next;
}

//Recursion(list1 list2 is Sorted)
template<typename T>
Node<T>* mergeTwoLists3(Node<T>* list1, Node<T>* list2) {
    //Base Case：list1 or list2 = nullptr
    if (!list1) return list2;
    if (!list2) return list1;
    //先判斷條件是什麼：比較大小值 => list1->val < list2->val
    //比贏的節點會進入下一個節點 => list1->next = mergeTwoLists3(list1->next,list2);
    //然後把然本比贏的節點輸出 => return list1;
    if (list1->val < list2->val) {
        list1->next = mergeTwoLists3(list1->next,list2);
        return list1;
    }
    else {
        list2->next = mergeTwoLists3(list1,list2->next);
        return list2;
    }
}
#pragma endregion

#pragma region Leetcode 19. Remove Nth Node From End of List
//Leetcode 19. Remove Nth Node From End of List
template<typename T>
Node<T>* MyLinkedlist<T>::Leetcode_Sol_19(Node<T>* head, int n,int _solution) {
    switch (_solution)
    {
    case 1:
        return FindLenToSol_19(head, n);
    case 2:
        return FastSlowPointer_19(head, n);

    default:
        break;
    }

    return nullptr;
}


/*
在單向鏈表中，如何有效地刪除「倒數第 N 個節點」？
如果不考慮效率，我們的直覺解法可能是：
先遍歷一次整個鏈表，記錄長度 L。
再遍歷一次，找到 (L - N) 處，刪除對應節點。
這樣的時間複雜度是 O(2n) ≈ O(n)，雖然不是特別差，
但我們可以透過 快慢指標（Two Pointer） 把它優化成 O(n) 內只遍歷一次。
*/
template<typename T>
Node<T>* FindLenToSol_19(Node<T>* head, int n) {
    //先遍歷一次，找到total(從1開始)
    //找到從正面過去的位置(total-n)
    //因為要連接：所以total-n-1的位置要連接total-n+1
    Node<T>* Ptr = head; int iTotal = 1;
    //Step.1
    while (Ptr) {
        Ptr = Ptr->next;
        iTotal++;
    }
    //Step.2
    int iFront_Location = iTotal - n;
    //Step.3 
    //因為要連接(須知total-n-1)，所以創一個prev，還有一個是要記錄刪除的下一個位置
    Node<T>* prev = nullptr; Node<T>* follow = nullptr;
    Ptr = head; int step = 1;
    while (Ptr) {
        if (step == iFront_Location) {
            if (step == 1) {        //imp：刪除第一個的話直接往前推就好
                head = head->next;
                break;
            }
            else {
                follow = Ptr->next;
                prev->next = follow;//防stackflow，因為prev = nullptr不能指向
            }

            delete Ptr;//要刪除的原因：head可能只有一個節點，要回傳null                         
            break;
        }
        prev = Ptr;
        Ptr = Ptr->next;
        step++;
    }

    return head;
}

/*
我們不知道總長度 L，但需要快速找到「倒數第 N 個」節點。
單向鏈表 不能直接從尾巴數回來（不像陣列 arr[arr.length - N]）。
我們希望一次遍歷就解決問題，而不是兩次。
如何設計「快慢指標」來找到倒數第 N 個節點？
我們可以讓 快指標 fast 先走 N 步，然後讓 慢指標 slow 再一起開始走，
這樣當 fast 走到尾巴時，slow 剛好停在「倒數第 N + 1 個節點」，這樣就能直接刪除 slow->next。

這樣，我們的時間複雜度就是 O(n)，只需要 遍歷一次。
*/
template<typename T>
Node<T>* FastSlowPointer_19(Node<T>* head, int n) {
    if (n <= 0) throw std::out_of_range("Please Out Of index!");
    T val{};
    Node<T>* Dummy = new Node<T>(val, head);// 重要：虛擬頭節點，避免刪除第一個節點的特判
    Node<T>* fast = Dummy;
    Node<T>* slow = Dummy;

    //我們需要知道被截掉的前一段，所以差距需要+1
    for (int i = 0; i <= n/*i < n + 1*/; i++)
        fast = fast->next;

    //因為她是往回刪除，所以利用最後的間距(把這個間距平移到最前面 =>相當於間距的平移)
    while (fast) {
        fast = fast->next;
        slow = slow->next;
    }
    //這時候的slow是他的前一個節點(刪除 slow->next（即倒數第 N 個節點）)
    Node<T>* nodeToDelete = slow->next;
    slow->next = slow->next->next;
    delete nodeToDelete;
    
    return Dummy->next;
    //不能用return head;
    //原因:因為萬一剛好頭部被刪除，那這樣會直接傳回nullptr
    //ex：[0,1,2,7] 如果刪除的是0，那回傳會直接變成nullptr，而不是[1,2,7]
}

#pragma endregion

#pragma region Leetcode 141. Linked List Cycle
//Leetcode 141. Linked List Cycle
//考快慢指標
template<typename T>
bool MyLinkedlist<T>::Leetcode_Sol_141(Node<T>* head) {
    Node<T>* fast = head;
    Node<T>* slow = head;

    while (fast && fast->next) {
        fast = fast->next->next;
        slow = slow->next;
        if (fast == slow)
            return true;
    }

    return false;
}
#pragma endregion

#pragma region Leetcode 876. Middle of the Linked List
//Leetcode 876. Middle of the Linked List
template<typename T>
Node<T>* MyLinkedlist<T>::Leetcode_Sol_876(Node<T>* head, int _solution) {
    switch (_solution) 
    {
    case 1:
        return FindCount_876(head); 
    case 2:
        return FastSlowPointer_876(head); 
    default:
        return nullptr; // 確保所有路徑都有回傳值
    }

    return nullptr;
}

template <typename T>
Node<T>* FindCount_876(Node<T>* head) {
    Node<T>* current = head; int iTotalNode = 0;
    while (current)
    {
        current = current->next;
        iTotalNode++;
    }

    int middleIndex = iTotalNode >> 1;
    current = head;
    while (middleIndex > 0) {
        current = current->next;
        middleIndex--;
    }
    return current;
}

template <typename T>
Node<T>* FastSlowPointer_876(Node<T>* head) {
    Node<T>* fast = head;
    Node<T>* slow = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}
#pragma endregion

#pragma region Leetcode 160. Intersection of Two Linked Lists
//Leetcode 160. Intersection of Two Linked Lists
template<typename T>
Node<T>* MyLinkedlist<T>::Leetcode_Sol_160(Node<T>* headA, Node<T>* headB, int _solution) {
    switch (_solution)
    {
    case 1:
        return Unordered_map_160(headA, headB);
    case 2:
        return TwoPointer1_160(headA, headB);
    case 3:
        return TwoPointer2_160(headA, headB);
    default:
        return nullptr; // 確保所有路徑都有回傳值
    }

    return nullptr;
}

//Unordered_map
template<typename T>
Node<T>* Unordered_map_160(Node<T>* headA, Node<T>* headB) {
    // 創建 unordered_map，將指針作為鍵，值為整數
    unordered_map<Node<T>*, T> map;
    Node<T>* pointer = headA;
    while (pointer) {
        map[pointer] = pointer->val;
        pointer = pointer->next;
    }
    pointer = headB;
    while (pointer) {
        if (pointer->val == map[pointer])
            return pointer;

        pointer = pointer->next;
    }

    return nullptr;
}

//TwoPointer1
template<typename T>
Node<T>* TwoPointer1_160(Node<T>* headA, Node<T>* headB) {
    Node<T>* p1 = headA;
    Node<T>* p2 = headB;
    int iCountA = 0; int iCountB = 0; int iLength = 0;
    while (p1) {
        p1 = p1->next;
        iCountA++;
    }
    while (p2) {
        p2 = p2->next;
        iCountB++;
    }
    p2 = headB; p1 = headA;
    if (iCountA > iCountB)
    {
        iLength = iCountA - iCountB;
        for (int i = 0; i < iLength; i++)
            p1 = p1->next;
    }
    else
    {
        iLength = iCountB - iCountA;
        for (int i = 0; i < iLength; i++)
            p2 = p2->next;
    }

    while (p1) {
        if (p1 == p2) return p1;
        p1 = p1->next;
        p2 = p2->next;
    }

    return nullptr;
}

/*
[A1 Common A1' B1 Common]
[B1 Common B1' A1 Common]
Because[A1'=B1']，So it can meet at the second time common.
That's why We can do the both line at the same step.
*/
//TwoPointer2
template<typename T>
Node<T>* TwoPointer2_160(Node<T>* headA, Node<T>* headB) {
    Node<T>* p1 = headA;
    Node<T>* p2 = headB;

      while(p1!=p2){
          p1 = p1? p1->next:headB;
          p2 = p2? p2->next:headA;
      }
      return p1;
}
#pragma endregion

#pragma region Leetcode 142. Linked List Cycle II
//Leetcode 142. Linked List Cycle II
template<typename T>
Node<T>* MyLinkedlist<T>::Leetcode_Sol_142(Node<T>* head, int _solution) {
    switch (_solution)
    {
    case 1:
        return OnePointer_142(head);
    case 2:
        return Floyd_Cycle_Detection_142(head);
    default:
        return nullptr; // 確保所有路徑都有回傳值
    }

    return nullptr;
}

template <typename T>
Node<T>* OnePointer_142(Node<T>* head) {
    Node<T>* current = head; int iTotalNode = 0;
    Node<T>* slow = head;
    unordered_map<Node<T>*, T> map;


    while (slow) {
        map[slow] = slow->val;
        slow = slow->next;
        if (map.find(slow) != map.end())
            return slow;
    }

    return nullptr;
}


/*
Floyd’s Cycle Detection Algorithm
進入圈圈的起始點：k 所求
圈數：C
第一次遇到的位置：n已知
步伐：1步、2步
1(k + (n-k))、2(k + (n-k))
2(k + (n-k)) - 1(k + (n-k)) = mC
2n - n = mC
條件：
1.n = mC(代表n是圈圈的倍數)
2.又因n-k是兩個的公同位置
所以：
一個人從起始位置走k
另一個人從剛剛第一次相遇的位置開始走k則會相遇
(有人會問說那n如果是很大，n = 4C(4圈)，
但k已經限定是進入圈圈的起始點，代表n-k會把剩下的圈數補齊)
*/
//Floyd’s Cycle Detection Algorithm
template <typename T>
Node<T>* Floyd_Cycle_Detection_142(Node<T>* head) {
    Node<T>* slow = head;
    Node<T>* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            slow = head;
            while (slow != fast) {
                slow = slow->next;
                fast = fast->next;
            }
            return slow;
        }
    }
    return nullptr;
}
#pragma endregion

#pragma region Leetcode 138. Copy List with Random Pointer
//Leetcode 138. Copy List with Random Pointer
template<typename T>
Node<T>* MyLinkedlist<T>::Leetcode_Sol_138(Node<T>* head, int _solution) {
    switch (_solution)
    {
    case 1:
        return DeepCopy_138(head);
    case 2:
        return Floyd_Cycle_Detection_142(head);
    default:
        return nullptr; // 確保所有路徑都有回傳值
    }

    return nullptr;
}

template <typename T>
Node<T>* DeepCopy_138(Node<T>* head) {
    //創暫存點指向要複製的那個點(複製其所有的屬性，除了random)，最後會變成一條鏈
    //unordered_map紀錄點(Src)的random的<currentRdm->next,index> = <位置pointer,index(哪個pointer指向我)>
    //這樣就知道是第幾個位置指向我現在的pointer
    //如果index小於or等於當前pointer的位置，那就可以直接做，如果index大於我現在的pointer先不做(這樣可以省下每次當下指向自己又位置小於的自己而需要額外行走到自己的距離，下一次返回來走同理)
    //最後會有一個兩個移動暫存指標再移回來一次就完成了!
    if (!head) return head;
    Node<T>* currentSrc = head; unordered_map<Node<T>*, Node<T>*> map;
    Node<T>* Dst = new Node<T>(head->val); Node<T>* currentDst = Dst;

    while (currentSrc) {
        if (currentSrc->next) {
            Node<T>* DstNext = new Node(currentSrc->next->val);
            currentDst->next = DstNext;
        }
        map[currentSrc] = currentDst;

        currentDst = currentDst->next;
        currentSrc = currentSrc->next;
    }
    currentDst = Dst; currentSrc = head; int iLocation = 0;
    //map這個節點匹配他的random
    // 第二遍：設置隨機指標
    currentSrc = head;
    currentDst = Dst;
    while (currentSrc) {
        if (currentSrc->random) {
            currentDst->random = map[currentSrc->random];
        }
        currentSrc = currentSrc->next;
        currentDst = currentDst->next;
    }
    
    return Dst;
}

#pragma endregion











