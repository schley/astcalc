#if !defined TB_AST_TREE_HXX_
#define      TB_AST_TREE_HXX_

#include <iostream>
#include <sstream>
#include "AstNode.hxx"

namespace Tb
{

class AstTree
{
public:
    AstTree();
    explicit AstTree(AstNode::ShPtr rootPtr);
    ~AstTree();
    void setRoot(AstNode::ShPtr rootPtr);
    int listnodes() const;
    void inorder(AstNode::ShPtr currptr) const;
    void preorder(AstNode::ShPtr currptr) const;
    void postorder(AstNode::ShPtr currPtr) const;
    void print(std::ostream& treeOss) const;
private:
    AstNode::ShPtr root_;
}; // class AstTree

std::ostream& operator<<(std::ostream& treeOss, const Tb::AstTree& astTree);

} // namespace Tb

#endif    // TB_AST_TREE_HXX_