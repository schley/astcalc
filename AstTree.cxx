#include "AstTree.hxx"
#include "AstNodeVisitor.hxx"

Tb::AstTree::AstTree()
    : root_(nullptr) 
{
}

Tb::AstTree::AstTree(Tb::AstNode::ShPtr rootPtr) 
    : root_(rootPtr)
{
}

Tb::AstTree::~AstTree()
{
}

void Tb::AstTree::setRoot(Tb::AstNode::ShPtr rootval)
{
    root_ = rootval;
}

void Tb::AstTree::preorder(Tb::AstNode::ShPtr currNode) const
{
    static const std::string LOCATION {"AstTree::preorder"};
    std::cout << LOCATION << ": " << *currNode << "\n";
    if (currNode->left_)
    {
        preorder(currNode->left_);
    }

    if (currNode->right_)
    {
        preorder(currNode->right_);
    }
}

void Tb::AstTree::postorder(Tb::AstNode::ShPtr currNode) const
{
    static const std::string LOCATION {"AstTree::postorder"};
    std::unique_ptr<AstNodePrintVisitor> printVisit = std::make_unique<AstNodePrintVisitor>(AstNodePrintVisitor() );
    std::unique_ptr<AstNodeCalculateVisitor> calcVisit = std::make_unique<AstNodeCalculateVisitor>(AstNodeCalculateVisitor() );
    if (currNode->left_)
    {
        postorder(currNode->left_);
    }
    if (currNode->right_)
    {
        postorder(currNode->right_);
    }
    // std::cout << LOCATION << ": " << *currNode << "\n";
    // uncomment to use print visitor (to stdout) --> currNode->accept(printVisit.get());
    currNode->accept(calcVisit.get() );

}

void Tb::AstTree::inorder(Tb::AstNode::ShPtr currNode) const
{
    static const std::string LOCATION {"AstTree::inorder"};
    std::unique_ptr<AstNodePrintVisitor> printVisit = std::make_unique<AstNodePrintVisitor>(AstNodePrintVisitor() );
    std::unique_ptr<AstNodeCalculateVisitor> calcVisit = std::make_unique<AstNodeCalculateVisitor>(AstNodeCalculateVisitor() );
    if (currNode->left_)
    {
        inorder(currNode->left_);
    }
    // std::cout << LOCATION << ": " << *currNode << "\n";
    // uncomment to see stack on stdout --> currNode->accept(printVisit.get() );
    currNode->accept(calcVisit.get());
    if (currNode->right_)
    {
        inorder(currNode->right_);
    }
}



int Tb::AstTree::listnodes() const
{
    int nodeCounter = 0;
    return nodeCounter;
}

void Tb::AstTree::print(std::ostream& treeOss) const
{
    // treeOss << "AstTree::print";
    treeOss << "\ninorder:\n";
    inorder(root_);
    treeOss << "\n\npreorder: \n";
    preorder(root_);
    treeOss << "\n\npostorder: \n";
    postorder(root_);
    treeOss << "\n\n";
}

std::ostream& Tb::operator<<(std::ostream& treeOss, const Tb::AstTree& astTree)
{
    astTree.print(treeOss);
    return treeOss;
}
