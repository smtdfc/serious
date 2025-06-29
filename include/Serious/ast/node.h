#pragma once

#include <variant>
#include <vector>
#include <string>
#include <memory>

namespace Serious {

  using NumberType = std::variant<int, double>;

  enum class NodeType {
    NUMBER_NODE,
    STRING_NODE,
    ID_NODE,
    CALL_EXPR_NODE,
    MEMBER_EXPR_NODE,
    EXPR_STATEMENT,
    UNARY_OP_NODE,
    BINARY_OP_NODE
  };

  struct NumberNode;
  struct StringNode;
  struct IdentifierNode;
  struct BinaryOpNode;
  struct UnaryOpNode ;
  using NodePtr = std::shared_ptr<struct NodeBase>;

  struct NodeBase {
    NodeType type;
    virtual ~NodeBase() = default;
  };

  struct NumberNode : public NodeBase {
    NumberType value;
    NumberNode(const NumberType& val) {
      type = NodeType::NUMBER_NODE;
      value = val;
    }
  };

  struct StringNode : public NodeBase {
    std::string value;
    StringNode(const std::string& val) {
      type = NodeType::STRING_NODE;
      value = val;
    }
  };

  struct IdentifierNode : public NodeBase {
    std::string name;
    IdentifierNode(const std::string& val) {
      type = NodeType::ID_NODE;
      name = val;
    }
  };

  struct UnaryOpNode : public NodeBase {
      char op;
      NodePtr right;
  
      UnaryOpNode(char o, NodePtr r) {
          type = NodeType::UNARY_OP_NODE;
          op = o;
          right = r;
      }
  };

  struct BinaryOpNode : public NodeBase {
    char op;
    NodePtr left;
    NodePtr right;

    BinaryOpNode(char o, NodePtr l, NodePtr r) {
      type = NodeType::BINARY_OP_NODE;
      op = o;
      left = l;
      right = r;
    }
  };

  struct MemberExpressionNode : public NodeBase {
    NodePtr object;
    NodePtr property;
  
    MemberExpressionNode(NodePtr obj, NodePtr prop) {
      type = NodeType::MEMBER_EXPR_NODE;
      object = obj;
      property = prop;
    }
  };

  struct CallExpressionNode : public NodeBase {
    NodePtr callee;
    std::vector<NodePtr> arguments;
  
    CallExpressionNode(NodePtr calleeExpr, const std::vector<NodePtr>& args) {
      type = NodeType::CALL_EXPR_NODE;
      callee = calleeExpr;
      arguments = args;
    }
  };

  using NodeList = std::vector<NodePtr>;

  struct ExpressionStatement: public NodeBase {
    NodePtr expression;
    ExpressionStatement(NodePtr expr){
      type = NodeType::EXPR_STATEMENT;
      expression = expr;
    }
  };
  
  struct AbstractSyntaxTree {
    NodeList nodes;
  };

  void printNode(const NodePtr& node, int indent = 0);
  void printAST(const AbstractSyntaxTree& ast);
}