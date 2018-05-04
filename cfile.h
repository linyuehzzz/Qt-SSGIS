/**************************************
Author:胡超、林?
Date:2017/12/23
Update:2018/1/6
Description:数据源类
***************************************/
#ifndef CFILE_H
#define CFILE_H
#define CONVERT(start, end, code, letter) if(code >= start && code <= end) return letter

#include "CHMap.h"
#include "CSSCity.h"
#include "CHPolyline.h"
#include "CHPolygon.h"
#include "CSSNameIndex.h"
#include "CSSSpatialIndex.h"
#include <fstream>
#include <list>

class CFile
{
public:
    CFile(const char* readFilePath1,const char* readFilePath2,
          const char* readFilePath3);
    ~CFile();

    CHMap *map;//图形绘制数据
    list<CSSCity* >citySet;//省会城市数据集
    string strPinyin;//用户输入的城市拼音首字母

    /* 读取图形绘制文件 */
    void FileOpenDat();

    /* 读取绘制信息文件 */
    void FileOpenOpt();

    /* 获取省会城市数据集 */
    void GetCitySet();

    /* 提取单个汉字词的拼音首字母缩写
    name:待转换城市名称 */
    string  GetFirstLetters(string name);

private:
    const char* readFilePath1;//图形绘制文件路径
    const char* readFilePath2;//绘制信息文件路径
    const char* readFilePath3;//省会城市文件路径

    /* 读取省会城市文件 */
    void ReadTxtFile();

    /* 将字符串转换为单条记录
    str:待转换字符串
    size:字符串长度*/
    void StringToRecord(CSSCity* city,string str,int size);

    /* 将省会城市数据集和用户输入的城市名转换为城市拼音首字母缩写 */
    void GetPinYin();

};

#endif // CFILE_H
