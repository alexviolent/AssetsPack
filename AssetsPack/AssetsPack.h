/*!
* @file Macros.h
* @date 2017/08/18 13:13
*
* @author 阿力(qq:395942144)
*
* @brief 资源包类
*
*/
#ifndef ASSETS_PACK_H
#define ASSETS_PACK_H

#include "Macros.h"
#include <vector>
#include "IAssetsOperator.h"

class IFile;

// 资源包类
class CAssetsPack
{
public:
    CAssetsPack(IAssetsOperator* pAssetsOperator);
    ~CAssetsPack();
public:
    bool LoadPackFile(const char* pszAssetsPackFile); // 载入资源包文件,没有会新建

    IFile* OpenFile(const char* pszFileName); // 通过文件名打开文件
    bool IsFileExist(const char* pszFileName); // 文件是否存在
    bool DelFile(const char* pszFileName); // 通过文件名删除文件
    bool AddFile(const char* pszFileName, const uchar* pBuffer, uint nFileSize); // 通过文件名添加文件

    void SavePack(); // 保存文件信息到打包的文件
    void Close();

    bool IsLoaded()
    {
        return m_bLoaded;
    };

private:
    FileEntry* GetDirtyEntry(uint nFileSize);

private:
    bool m_bLoaded; // 是否已经加载资源包文件了
    IAssetsOperator* m_pAssetsOperator;
    PackHead m_packHead; // 资源包头部信息
    std::vector<FileEntry> m_vecFileEntry; // 所有文件入口列表
};



#endif // !ASSETS_PACK_H



