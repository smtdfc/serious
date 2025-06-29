#include "Serious/ast/node.h"
#include "Serious/debug.h"
#include <iostream>
#include <string>

namespace Serious {

  void printIndent(int indent) {
    for (int i = 0; i < indent; ++i) std::cout << " ";
  }

  void printNode(const NodePtr& node, int indent) {
    if (!node) return;
    printIndent(indent);

    switch (node->type) {
      
      case NodeType::NUMBER_NODE: {
        auto num = std::static_pointer_cast<NumberNode>(node);
        std::cout << "Number(";
        if (std::holds_alternative<int>(num->value))
          std::cout << std::get<int>(num->value);
        else
          std::cout << std::get<double>(num->value);
        std::cout << ")\n";
        break;
      }
      case NodeType::STRING_NODE: {
        auto str = std::static_pointer_cast<StringNode>(node);
        std::cout << "String(\"" << str->value << "\")\n";
        break;
      }
      case NodeType::ID_NODE: {
        auto id = std::static_pointer_cast<IdentifierNode>(node);
        std::cout << "Identifier(" << id->name << ")\n";
        break;
      }
      case NodeType::BINARY_OP_NODE: {
        auto bin = std::static_pointer_cast<BinaryOpNode>(node);
        std::cout << "BinaryOp(" << bin->op << ")\n";
        printNode(bin->left, indent + 4);
        printNode(bin->right, indent + 4);
        break;
      }
      case NodeType::UNARY_OP_NODE: {
        auto unary = std::static_pointer_cast<UnaryOpNode>(node);
        std::cout << "UnaryOp(" << unary->op << ")\n";
        printNode(unary->right, indent + 4);
        break;
      }
      
      case NodeType::EXPR_STATEMENT: {
        auto exprStat = std::static_pointer_cast<ExpressionStatement>(node);
        std::cout << "ExpressionStatement(\n";
        printNode(exprStat->expression, indent + 4);
        printIndent(indent);
        std::cout << ")\n";
        break;
      }

      case NodeType::MEMBER_EXPR_NODE: {
        auto memExpr = std::static_pointer_cast<MemberExpressionNode>(node);
        std::cout << "Member Expression(\n";
        printNode(memExpr->object, indent + 4);
        printNode(memExpr->property,indent+4);
        printIndent(indent);
        std::cout << ")\n";
        break;
      }

      case NodeType::CALL_EXPR_NODE: {
        auto call = std::static_pointer_cast<CallExpressionNode>(node);
        std::cout << "Call(\n";
        printNode(call->callee, indent + 4);
        for (auto& arg : call->arguments)
          printNode(arg, indent + 4);
        printIndent(indent);
        std::cout << ")\n";
        break;
      }
    }
  }

  void printAST(const AbstractSyntaxTree& ast) {
    for (const auto& node : ast.nodes) {
      std::cout<<"Node "<<std::endl;
      printNode(node, 2);
    }
  }

}