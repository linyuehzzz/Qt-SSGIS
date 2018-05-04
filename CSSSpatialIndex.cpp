#include "CSSSpatialIndex.h"

CSSSpatialIndex::CSSSpatialIndex()
{
    root = 0x00;
    target = 0x00;
}

CSSSpatialIndex::~CSSSpatialIndex()
{
    if (root != 0x00)
    {
        delete root;//销毁结点
        root = 0x00;
    }

    if (target != 0x00)
    {
        delete target;//销毁结点
        target = 0x00;
    }
}


/// <summary>
/// 创建四叉树
/// </summary>
/// <param name="citySet">省会城市数据集</param>
void CSSSpatialIndex::CreateQuadTree(list<CSSCity* > citySet)
{
    CSSCity* city;
    for(list<CSSCity* >::iterator iter = citySet.begin(); iter != citySet.end();iter++)
    {
        city = (*iter);
        Insert(city);
    }
}


/// <summary>
/// 插入一条城市记录
/// </summary>
/// <param name="city">待插入城市记录</param>
void CSSSpatialIndex::Insert(CSSCity* city)
{
    CHPoint pos = city->geoPt;
    target = MakeNode(pos);
    target->city = city;

    if(root == 0x00)
    {
        root = new CSSSpatialIndexNode();
        root->city = city;
        root = target;
        root->LN = 0;
        root->LS = 500;
        root->LW = 0;
        root->LE = 500;
        return ;
    }

    CSSSpatialIndexNode* temp = root;
    while(temp != 0x00 && !IsEqualCoordinates(temp, target))
    {
        CSSSpatialIndexNode* quadrant = GetQuadrant(temp, target);
        if(quadrant == 0x00)
        {
            InsertPointInFinalQuadrant(temp, target);
            temp = 0x00;
            return ;
        }
        else
        {
            temp = quadrant;
        }
    }
    return ;
}


/// <summary>
/// 生成节点
/// </summary>
/// <param name="city">待生成节点的屏幕坐标</param>
CSSSpatialIndexNode* CSSSpatialIndex::MakeNode(CHPoint pos)
{
    CSSSpatialIndexNode* temp = new CSSSpatialIndexNode();
    temp->pos = pos;
    temp->NW = 0x00;
    temp->NE = 0x00;
    temp->SE = 0x00;
    temp->SW = 0x00;
    return temp;
}


/// <summary>
/// 比较点坐标是否相等
/// </summary>
/// <param name="temp">树节点</param>
/// <param name="target">目标点</param>
bool CSSSpatialIndex::IsEqualCoordinates(CSSSpatialIndexNode* temp, CSSSpatialIndexNode* target)
{
    if((temp->pos.x == target->pos.x)&&(temp->pos.y == target->pos.y))
        return true;
    else
        return false;
}


/// <summary>
/// 判断目标点所处象限
/// </summary>
/// <param name="temp">树节点</param>
/// <param name="target">目标点</param>
CSSSpatialIndexNode* CSSSpatialIndex::GetQuadrant(CSSSpatialIndexNode* temp, CSSSpatialIndexNode* target)
{
    if(temp->pos.x < target->pos.x)
    {
        if(temp->pos.y < target->pos.y)
        {
            return temp->SE;
        }
        else
        {
            return temp->NE;
        }
    }

    else if(temp->pos.y < target->pos.y)
    {
        return temp->SW;
    }
    else
    {
        return temp->NW;
    }
}


/// <summary>
/// 将目标点插入相应叶子节点中
/// </summary>
/// <param name="temp">树节点</param>
/// <param name="target">目标点</param>
void CSSSpatialIndex::InsertPointInFinalQuadrant(CSSSpatialIndexNode* temp, CSSSpatialIndexNode* target)
{
    if(temp->pos.x < target->pos.x)
    {
        if(temp->pos.y < target->pos.y)
        {
            temp->SE = target;
            target->LN = temp->pos.y;
            target->LW = temp->pos.x;
            target->LS = temp->LS;
            target->LE = temp->LE;
        }
        else
        {
            temp->NE = target;
            target->LN = temp->LN;
            target->LW = temp->pos.x;
            target->LS = temp->pos.y;
            target->LE = temp->LE;
        }
    }

    else if(temp->pos.y < target->pos.y)
    {
        temp->SW = target;
        target->LN = temp->pos.y;
        target->LW = temp->LW;
        target->LS = temp->LS;
        target->LE = temp->pos.x;
    }
    else
    {
        temp->NW = target;
        target->LN = temp->LN;
        target->LW = temp->LW;
        target->LS = temp->pos.y;
        target->LE = temp->pos.x;
    }
}


/// <summary>
/// 查找一条城市记录
/// </summary>
/// <param name="pt">屏幕坐标</param>
/// <returns>查询城市记录</returns>
bool CSSSpatialIndex::Search(CHPoint pt,CSSCity* city)
{
    CSSSpatialIndexNode* target = MakeNode(pt);

    if(root == 0x00)
    {
        cout << "Empty Quad Tree.\n" << endl;
        return false;
    }

    if(IsEqualCoordinates(root, target))
    {
        city = root->city;
        return true;
    }

    CSSSpatialIndexNode* temp = root;
    while(temp != 0x00)
    {
        if(IsEqualCoordinates(temp, target))
        {
            city = temp->city;
            return true;
        }
        else
        {
            temp = GetQuadrant(temp, target);
        }
    }
    return false;
}


/// <summary>
/// 不精确查找城市记录
/// </summary>
/// <param name="pt">屏幕坐标</param>
/// <param name="r">缓冲区半径</param>
bool CSSSpatialIndex::CheckCircle(CHPoint pt, int r)
{
    queue<CSSSpatialIndexNode*> q;
    if(q.empty())
        q.push(root);

    while(!q.empty())
    {
        CSSSpatialIndexNode* popped = q.front();
        q.pop();
        if(IsInCircle(pt, r, popped))
        {
            cityResult = popped->city;
            return true;
        }
        if(popped->NE != 0x00)
            q.push(popped->NE);
        if(popped->NW != 0x00)
            q.push(popped->NW);
        if(popped->SW != 0x00)
            q.push(popped->SW);
        if(popped->SE != 0x00)
            q.push(popped->SE);
    }
    return false;
}


/// <summary>
/// 目标点是否落于缓冲区内
/// </summary>
/// <param name="pt">屏幕坐标</param>
/// <param name="r">缓冲区半径</param>
/// <param name="r">目标点</param>
bool CSSSpatialIndex::IsInCircle(CHPoint pt, int r, CSSSpatialIndexNode* target)
{
    return(Dist(pt.x,pt.y,target->pos.x,target->pos.y)<r);
}


/// <summary>
/// 距离计算
/// </summary>
int CSSSpatialIndex::Dist(int x1, int y1, int x2, int y2)
{
    double distx = (double)pow((x2-x1)/100,2);
    double disty = (double)pow((y2-y1)/100,2);
    double dist = sqrt(distx+disty);
    return (int)dist;
}

