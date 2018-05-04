#include "CSSNameIndexNode.h"

CSSNameIndexNode::CSSNameIndexNode()
{
    this->city = 0x00;
    this->word = 0x00;
    memset(nextBranch,0x00,sizeof(CSSNameIndexNode*) * MaxBranchNum);
}


CSSNameIndexNode::~CSSNameIndexNode()
{
}
