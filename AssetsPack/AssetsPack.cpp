#include "AssetsPack.h"
#include "xxhash.h"
#include "IFile.h"
#include "IAssetsOperator.h"
#include "AssetsFile.h"
#include <string.h>


CAssetsPack::CAssetsPack(IAssetsOperator* pAssetsOperator)
    : m_pAssetsOperator(pAssetsOperator)
    , m_bLoaded(false)
{
    m_packHead.nFileAmount = 0;
    m_packHead.nFileEntryOffset = sizeof(PackHead);
    m_vecFileEntry.clear();
}


CAssetsPack::~CAssetsPack()
{
}

bool CAssetsPack::LoadPackFile(const char* pszAssetsPackFile)
{
    if(!m_pAssetsOperator)
    {
        return false;
    }

    bool ret = m_pAssetsOperator->OpenAssetsPackFile(pszAssetsPackFile);

    if(!ret)
    {
        return false;
    }

    m_vecFileEntry.clear();
    m_pAssetsOperator->ReadPackHead(m_packHead);
    m_pAssetsOperator->ReadFileEntry(m_vecFileEntry);

    m_bLoaded = true;

    return true;
}

IFile* CAssetsPack::OpenFile(const char* pszFileName)
{
    uint nNameHash = XXHASH32(pszFileName);

    FE_FOREACH(pEntry, m_vecFileEntry)
    {
        if(pEntry->ucFlag != FF_DELETE && pEntry->nNameHash == nNameHash)
        {
            IFile* file = new CAssetsFile(m_pAssetsOperator, pEntry->nOffset, pEntry->nFileSize);
            return file;
        }
    }

    return NULL;
}

bool CAssetsPack::IsFileExist(const char* pszFileName)
{
    uint nNameHash = XXHASH32(pszFileName);

    FE_FOREACH(pEntry, m_vecFileEntry)
    {
        if(pEntry->ucFlag != FF_DELETE && pEntry->nNameHash == nNameHash)
        {
            return true;
        }
    }

    return false;
}

bool CAssetsPack::DelFile(const char* pszFileName)
{
    uint nNameHash = XXHASH32(pszFileName);

    FE_FOREACH(pEntry, m_vecFileEntry)
    {
        if(pEntry->ucFlag != FF_DELETE && pEntry->nNameHash == nNameHash)
        {
            pEntry->ucFlag = FF_DELETE;
            return true;
        }
    }

    return false;
}

bool CAssetsPack::AddFile(const char* pszFileName, const uchar* pBuffer, uint nFileSize)
{
    // 添加文件前先把同名文件给删了
    DelFile(pszFileName);

    uint nNameHash = XXHASH32(pszFileName);

    FileEntry newEntry;
    newEntry.ucFlag = FF_NORMAL;
    newEntry.nFileSize = nFileSize;
    newEntry.nNameHash = nNameHash;

    FileEntry* pDirtyEntry = GetDirtyEntry(nFileSize);

    // 如果刚好要增加的文件小于其中某个已删除文件的大小，那么直接写入到那个位置
    if(pDirtyEntry)
    {
        pDirtyEntry->ucFlag = FF_NORMAL;
        pDirtyEntry->nFileSize = nFileSize;
        newEntry.nOffset = pDirtyEntry->nOffset;
    }

    else
    {
        // 文件偏移放到末尾
        newEntry.nOffset = m_packHead.nFileEntryOffset;
        m_packHead.nFileEntryOffset += nFileSize;
        m_vecFileEntry.push_back(newEntry);
        m_packHead.nFileAmount++;
    }

    return nFileSize == m_pAssetsOperator->Write(pBuffer, newEntry.nOffset, nFileSize);

}

// 获取适合大小的已删除的文件位置信息
FileEntry* CAssetsPack::GetDirtyEntry(uint nFileSize)
{
    FE_FOREACH(pEntry, m_vecFileEntry)
    {
        if(pEntry->ucFlag == FF_DELETE && pEntry->nFileSize >= nFileSize)
        {
            return pEntry;
        }
    }

    return NULL;
}

void CAssetsPack::SavePack()
{
    if(!m_pAssetsOperator)
    {
        return;
    }

    // 写入文件头信息
    m_pAssetsOperator->Write((const uchar*)&m_packHead, 0, sizeof(PackHead));

    // 写入文件列表信息
    uint nEntryOffset = m_packHead.nFileEntryOffset;
    uint nEntrySize = sizeof(FileEntry);
    FE_FOREACH(pEntry, m_vecFileEntry)
    {
        m_pAssetsOperator->Write((const uchar*)pEntry, nEntryOffset, nEntrySize);
        nEntryOffset += nEntrySize;
    }

    // 关闭文件
    m_pAssetsOperator->Close();
}

void CAssetsPack::Close()
{
    m_pAssetsOperator->Close();
}
