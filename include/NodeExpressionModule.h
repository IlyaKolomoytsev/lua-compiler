#ifndef LUA_COMPILER_NODEMODULE_H
#define LUA_COMPILER_NODEMODULE_H
#include "ExpressionNode.h"
#include "LiteralExprNode.h"
#include "ExpressionNodeOf.h"
#include "TwoOperandsExprNode.h"
#include "OneOperandExprNode.h"
#include "FunctionExprNode.h"
#include "TableConstructorExprNode.h"
#include "TableFieldExprNode.h"

// Literal expression nodes
using IdExprNode = LiteralExprNode<std::string, ExpressionNode::Type::Id>;
using IntegerExprNode = LiteralExprNode<int64_t, ExpressionNode::Type::Integer>;
using FloatExprNode = LiteralExprNode<double, ExpressionNode::Type::Float>;
using StringExprNode = LiteralExprNode<std::string, ExpressionNode::Type::String>;
using BoolExprNode = LiteralExprNode<bool, ExpressionNode::Type::Boolean>;

// Nil and vararg expression nodes
using NilExprNode = ExpressionNodeOf<ExpressionNode::Type::Nil>;
using VarargExprNode = ExpressionNodeOf<ExpressionNode::Type::Vararg>;

// Two operands expression nodes
using SummationExprNode = TwoOperandsExprNode<ExpressionNode::Type::Summation>;
using SubtractionExprNode = TwoOperandsExprNode<ExpressionNode::Type::Subtraction>;
using MultiplicationExprNode = TwoOperandsExprNode<ExpressionNode::Type::Multiplication>;
using DivisionExprNode = TwoOperandsExprNode<ExpressionNode::Type::Division>;
using ModuloExprNode = TwoOperandsExprNode<ExpressionNode::Type::Modulo>;
using IntegerDivision = TwoOperandsExprNode<ExpressionNode::Type::IntegerDivision>;
using ExponentiationExprNode = TwoOperandsExprNode<ExpressionNode::Type::Exponentiation>;
using LessExprNode = TwoOperandsExprNode<ExpressionNode::Type::Less>;
using GreaterExprNode = TwoOperandsExprNode<ExpressionNode::Type::Greater>;
using EqualityExprNode = TwoOperandsExprNode<ExpressionNode::Type::Equality>;
using UnequalityExprNode = TwoOperandsExprNode<ExpressionNode::Type::Unequality>;
using LessEqualExprNode = TwoOperandsExprNode<ExpressionNode::Type::LessEqual>;
using GreaterEqualExprNode = TwoOperandsExprNode<ExpressionNode::Type::GreaterEqual>;
using OrExprNode = TwoOperandsExprNode<ExpressionNode::Type::Or>;
using AndExprNode = TwoOperandsExprNode<ExpressionNode::Type::And>;
using ConcatenationExprNode = TwoOperandsExprNode<ExpressionNode::Type::Concatenation>;

// One operand expression nodes
using LengthExprNode = OneOperandExprNode<ExpressionNode::Type::Length>;
using NegationExprNode = OneOperandExprNode<ExpressionNode::Type::Negation>;
using UnaryMinusExprNode = OneOperandExprNode<ExpressionNode::Type::UnaryMinuses>;

#endif //LUA_COMPILER_NODEMODULE_H