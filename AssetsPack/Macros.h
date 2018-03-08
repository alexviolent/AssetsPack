/*!
 * @file Macros.h
 * @date 2017/08/18 12:13
 *
 * @author ����(qq:395942144)
 *
 * @brief �궨��
 *
*/
#ifndef MACROS_H
#define MACROS_H

typedef unsigned char uchar;
typedef unsigned int uint;

// �ļ���־FileFlag
static const uchar FF_NORMAL = 1;     // ��ͨ�ļ�
static const uchar FF_DELETE = 2;        // ��ɾ�����ļ�
static const uchar FF_COMPRESS = 3;  // ��ѹ�����ļ�
//
#define XXHASH32(_STR_) XXH32(_STR_, strlen(_STR_), 0x123ABC89)
//
#define BREAK_IF(_COND_) if (_COND_) break;
//
#define FE_FOREACH(_VAR_, _T_) FileEntry* _VAR_ = NULL; \
for (std::set<FileEntry>::iterator it = _T_.begin(); it != _T_.end() ? _VAR_ = (FileEntry*)&(*it) : _VAR_ = NULL; it++)

#endif // !MACROS_H
