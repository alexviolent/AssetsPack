/*!
* @file Macros.h
* @date 2017/08/18 13:13
*
* @author ����(qq:395942144)
*
* @brief ��Դ����
*
*/
#ifndef ASSETS_PACK_H
#define ASSETS_PACK_H

#include "Macros.h"
#include <vector>
#include "IAssetsOperator.h"

class IFile;

// ��Դ����
class CAssetsPack
{
public:
    CAssetsPack(IAssetsOperator* pAssetsOperator);
    ~CAssetsPack();
public:
    bool LoadPackFile(const char* pszAssetsPackFile); // ������Դ���ļ�,û�л��½�

    IFile* OpenFile(const char* pszFileName); // ͨ���ļ������ļ�
    bool IsFileExist(const char* pszFileName); // �ļ��Ƿ����
    bool DelFile(const char* pszFileName); // ͨ���ļ���ɾ���ļ�
    bool AddFile(const char* pszFileName, const uchar* pBuffer, uint nFileSize); // ͨ���ļ�������ļ�

    void SavePack(); // �����ļ���Ϣ��������ļ�
    void Close();

    bool IsLoaded()
    {
        return m_bLoaded;
    };

private:
    FileEntry* GetDirtyEntry(uint nFileSize);

private:
    bool m_bLoaded; // �Ƿ��Ѿ�������Դ���ļ���
    IAssetsOperator* m_pAssetsOperator;
    PackHead m_packHead; // ��Դ��ͷ����Ϣ
    std::vector<FileEntry> m_vecFileEntry; // �����ļ�����б�
};



#endif // !ASSETS_PACK_H



