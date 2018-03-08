/*!
* @file IAssetsOperator.h
* @date 2017/08/18 14:56
*
* @author ����(qq:395942144)
*
* @brief ������Դ���ļ��Ľӿڣ���ϵͳ�ļ��򽻵�����
*
*/
#ifndef IASSETS_OPERATOR_H
#define IASSETS_OPERATOR_H
#include "Macros.h"
#include <set>
#pragma pack(1)
// ��Դ��ͷ����Ϣ
typedef struct tagPackHead
{
    uint nFileEntryOffset; // �ļ����ƫ��
    uint nFileAmount; // ���ļ�����
} PackHead;

// �ļ������Ϣ
typedef struct tagFileEntry
{
    uint nOffset;                   // �ļ����ڵ�ƫ��
    uint nNameHash;         // �ļ�����ϣֵ
    uint nFileSize;             // �ļ���С
    uchar ucFlag;               // �ļ���־
	bool operator < (const tagFileEntry &_Target) const
	{
		return _Target.nFileSize > nFileSize;
	}
} FileEntry;
#pragma pack()
class IAssetsOperator
{
public:
    virtual bool OpenAssetsPackFile(const char*) = 0;
    virtual void ReadPackHead(PackHead&) = 0;
    virtual void ReadFileEntry(std::set<FileEntry>&) = 0;
    virtual uint Read(uchar* pBuffer, uint nOffset, uint nLen) = 0;
    virtual uint Write(const uchar* pBuffer, uint nOffset, uint nLen) = 0;
    virtual void Close() = 0;
};
#endif // !IASSETS_OPERATOR_H
