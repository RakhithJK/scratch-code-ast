#pragma once



namespace ast
{
	class Node;											//0x00000001
		class Statement;								//0x00000011
			class VariableDefinition;					//0x00000111
			class FunctionDefinition;					//0x00000211
			class Value;								//0x00000311
				class LValue;							//0x00001311
				class RValue;							//0x00002311
					class RValueValue;					//0x00012311
					class FunctionCall;					//0x00022311
					class Operation;					//0x00032311
						class UnaryOperation;			//0x00132311
						class BinaryOperation;			//0x00232311
			class ControlFlowStatement;					//0x00000411
				class Conditional;						//0x00001411
				class ControllableLoop;					//0x00002411
					class ForLoop;						//0x00012411
					class WhileLoop;					//0x00022411
				class LoopControlStatement;				//0x00003411
				class ReturnStatement;					//0x00004411
		class StatementList;							//0x00000021
		class VariableDefinitionList;					//0x00000031
		class ValueList;								//0x00000041
}

#include "Node.hpp"
#include "Statement.hpp"
#include "VariableDefinition.hpp"
#include "FunctionDefinition.hpp"
#include "Value.hpp"
#include "LValue.hpp"
#include "RValue.hpp"
#include "RValueValue.hpp"
#include "FunctionCall.hpp"
#include "Operation.hpp"
#include "UnaryOperation.hpp"
#include "BinaryOperation.hpp"
#include "ControlFlowStatement.hpp"
#include "Conditional.hpp"
#include "ControllableLoop.hpp"
#include "ForLoop.hpp"
#include "WhileLoop.hpp"
#include "LoopControlStatement.hpp"
#include "ReturnStatement.hpp"
#include "StatementList.hpp"
#include "VariableDefinitionList.hpp"
#include "ValueList.hpp"

#include "RValueValueParseException.hpp"
#include "Stringifyer.hpp"
