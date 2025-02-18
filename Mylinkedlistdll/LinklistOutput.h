#pragma once
#define BUILDING_DLL
#ifdef BUILDING_DLL
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif
extern "C" {
    DLL_API void* CreateLinkedListInt();
    DLL_API void* CreateLinkedListString();
    DLL_API void AppendInt(void* list, int value);
    DLL_API void AppendString(void* list, const char* value);
    DLL_API int GetIntAt(void* list, int index);
    DLL_API const char* GetStringCopyAt(void* list, int index);
    DLL_API void* CreateLinkedListIntFromExisting(void* existingList);
    DLL_API void* CreateLinkedListStringFromExisting(void* existingList);
    DLL_API void PopListInt(void* list);
    DLL_API void PopListstring(void* list);
    DLL_API void DeleteInt(void* list, int _val, bool IsAll);
    DLL_API void Deletestring(void* list, const char* _val, bool IsAll);
    DLL_API void InsertInt(void* list, int _location, int _val);
    DLL_API void Insertstring(void* list, int _location, const char* _val);
    DLL_API void RemoveAtInt(void* list, int _location);
    DLL_API void RemoveAtString(void* list, int _location);
    DLL_API const char* PrintAllInt(void* list);
    DLL_API const char* PrintAllIstring(void* list);
    DLL_API void DeleteLinkedListInt(void* list);
    DLL_API void DeleteLinkedListString(void* list);
    DLL_API void* GetNextNode(void* node);
    DLL_API void FreeString(char* str);  // 新增釋放函式
}

//extern "C" {
//    DLL_API void* CreateLinkedListInt();
//    DLL_API void* CreateLinkedListString();
//    DLL_API void AppendInt(void* list, int value);
//    DLL_API void AppendString(void* list, const char* value);
//    DLL_API int GetIntAt(void* list, int index);
//    DLL_API const char* GetStringAt(void* list, int index);
//    DLL_API const char* GetStringCopyAt(void* list, int index);
//    DLL_API void* CreateLinkedListIntFromExisting(const MyLinkedlist<int>& _MyLinkedlist);
//    DLL_API void* CreateLinkedListStringFromExisting(const MyLinkedlist<std::string>& _MyLinkedlist);
//    DLL_API void PopListInt(void* list);
//    DLL_API void PopListstring(void* list);
//    DLL_API void DeleteInt(void* list, int _val, bool IsAll = true);
//    DLL_API void Deletestring(void* list, std::string _val, bool IsAll = true);
//    DLL_API void InsertInt(void* list, int _location, int _val);
//    DLL_API void Insertstring(void* list, int _location, std::string _val);
//    DLL_API void RemoveAtInt(void* list, int _location);
//    DLL_API void RemoveAtString(void* list, int _location);
//    DLL_API std::string PrintAllInt(void* list);
//    DLL_API std::string PrintAllIstring(void* list);
//    DLL_API void DeleteLinkedListInt(void* list);
//    DLL_API void DeleteLinkedListString(void* list);
//}
