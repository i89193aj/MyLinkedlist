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

#ifndef NOBUILDING_DLL  //#ifdef BUILDING_DLL
int main()
{
    MyLinkedlist<int>* list1 = new MyLinkedlist<int>();//堆區 (heap)，list1 存的是該物件的記憶體位址
    MyLinkedlist<int>* list2 = new MyLinkedlist<int>();
    Node<int>* header = new Node<int>(1);
    Node<int>* follow = new Node<int>(2);

    header->next = follow;
    list1->Leetcode_Sol_19(header,2,1);
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
Node<T>* MyLinkedlist<T>::Leetcode_Sol_19(Node<T>* head, int n,int _Soluttion_idx) {
    switch (_Soluttion_idx)
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
        return TwoPointer_160(headA, headB);
    default:
        return nullptr; // 確保所有路徑都有回傳值
    }

    return nullptr;
}

//LUnordered_map
template<typename T>
Node<T>* Unordered_map_160(Node<T>* headA, Node<T>* headB) {
    // 創建 unordered_map，將指針作為鍵，值為整數
    unordered_map<ListNode*, int> map;
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

//TwoPointer
template<typename T>
Node<T>* TwoPointer_160(Node<T>* headA, Node<T>* headB) {
    // 創建 unordered_map，將指針作為鍵，值為整數
    unordered_map<ListNode*, int> map;
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
#pragma endregion











