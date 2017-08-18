/*!
 * @file IFile.h
 * @date 2017/08/18 13:56
 *
 * @author ����(qq:395942144)
 *
 * @brief �ļ��ӿ�
 *
*/
#ifndef IFILE_H
#define IFILE_H
#include "Macros.h"
class IFile
{
public:
	virtual uint GetFileSize() = 0; // ��ȡ�ļ���С
	virtual uint Read(uchar* pBuffer) = 0; // ��ȡ�ļ��ֽ�
	virtual uchar* GetBuffer() = 0; // ��ȡ�ļ��ֽ�
};
#endif // !IFILE_H
