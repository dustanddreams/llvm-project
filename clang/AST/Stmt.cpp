//===--- Stmt.cpp - Statement AST Node Implementation ---------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file was developed by Chris Lattner and is distributed under
// the University of Illinois Open Source License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements the Stmt class and statement subclasses.
//
//===----------------------------------------------------------------------===//

#include "clang/AST/Stmt.h"
#include "clang/AST/Expr.h"
#include "clang/AST/StmtVisitor.h"
#include <iostream>
using namespace llvm;
using namespace clang;

void Stmt::dump() const {
  if (this == 0) {
    std::cerr << "<null>";
    return;
  }
  if (isExpr()) std::cerr << "(";
  dump_impl();
  if (isExpr()) std::cerr << ")";
}


void CompoundStmt::visit(StmtVisitor *V) { return V->VisitCompoundStmt(this); }
void IfStmt      ::visit(StmtVisitor *V) { return V->VisitIfStmt(this); }
void ReturnStmt  ::visit(StmtVisitor *V) { return V->VisitReturnStmt(this); }


void CompoundStmt::dump_impl() const {
  std::cerr << "{\n";
  for (unsigned i = 0, e = Body.size(); i != e; ++i) {
    Body[i]->dump();
    std::cerr << "\n";
  }
  std::cerr << "}";
}

void IfStmt::dump_impl() const {
  std::cerr << "if ";
  Cond->dump();
  std::cerr << " then\n";
  Then->dump();
  std::cerr << "\n else ";
  Else->dump();
}

void ReturnStmt::dump_impl() const {
  std::cerr << "return ";
  if (RetExpr)
    RetExpr->dump();
}
