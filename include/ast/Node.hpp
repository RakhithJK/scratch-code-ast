/*
 *   Copyright 2016 sigalor
 *
 *   File: scratch-code-ast/include/ast/Node.hpp
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */



#pragma once



#include <vector>
#include <algorithm>
#include <memory>
#include <type_traits>



namespace ast
{
	class Node
	{
		public:
			static const int									uniqueId;
	
		private:
			int													id;
			std::shared_ptr<Node>								parent;
		
		protected:
			Node(int newId);
			Node(int newId, std::shared_ptr<Node> newParent);
		
		public:
			Node();
			Node(std::shared_ptr<Node> newParent);
			virtual ~Node();																						//virtual member needed to make class polymorphic
			int													getId();
			std::shared_ptr<Node>								getParent();
			void												setParent(std::shared_ptr<Node> newParent);
			std::shared_ptr<Node>								searchParents(std::function<bool(std::shared_ptr<Node>)> condition, std::size_t* steps);
			
			//gets the mask of an id base, e.g. idBaseInQuestion==0x00032451 --> returns 0x000FFFFF or idBaseInQuestion==0x00000021 --> returns 0x000000FF)
			int getIdBaseMask(int idBaseInQuestion)
			{
				int idBaseOrig = idBaseInQuestion, idBaseMask = 0;
				while(idBaseOrig > 0)																				//I designed the different class IDs so that the less significant nibbles are the same across derived instances and become numbered, e.g. Node::uniqueId=0x00000001 --> Statement::uniqueId=0x00000011 and StatementList::uniqueId=0x00000021 and VariableDefinitionList::uniqueId=0x00000031 etc.   or   Operation::uniqueId=0x00003311 --> UnaryOperation::uniqueId=0x00013311 and BinaryOperation::uniqueId=0x00023311
				{																									//that's why just the "base size" of 'idBaseInQuestion' has to be calculated (as a bitmask) to check later instances (e.g. see lambda in "hasParentWithIdBase")
					idBaseMask = (idBaseMask << 4) | 0xF;
					idBaseOrig >>= 4;
				}
				return idBaseMask;
			}
			
			//checks if the current instance has the given id
			bool isA(int idInQuestion)
			{
				return (getId() == idInQuestion);
			}
			
			//like 'isA', but more comfortable because of template argument
			template<typename T>
			typename std::enable_if_t<std::is_base_of<Node, T>::value, bool>										//use std::is_base_of_v for C++17
			isA()
			{
				return isA(T::uniqueId);
			}
			
			//checks wheather the current instance's id is derived from the one given
			bool isABase(int idBaseInQuestion)
			{
				return ((getId() & getIdBaseMask(idBaseInQuestion)) == idBaseInQuestion);
			}
			
			//like 'isABase', but more comfortable because of template argument
			template<typename T>
			typename std::enable_if_t<std::is_base_of<Node, T>::value, bool>
			isABase()
			{
				return isABase(T::uniqueId);
			}
			
			//checks wheather 'parent' is one of the parents (i.e. not only direct parent, but also grandparent, grand-grandparent etc.) of 'subject'
			template<typename T>
			std::shared_ptr<T> hasParent(std::shared_ptr<Node> parentInQuestion, std::size_t* steps=nullptr)
			{
				//a simple comparison with == is possible, because shared_ptr's operator== just compares the stored pointers (the ones returned by shared_ptr::get()), NOT the instances pointed to!
				return std::static_pointer_cast<T>(searchParents([&](std::shared_ptr<Node> subject) -> bool { return (subject == parentInQuestion); }, steps));
			}
			
			//checks wheater one of the parents (defined like above) of 'subject' has one of the ids in 'idsInQuestion'
			template<typename T>
			std::shared_ptr<T> hasParentWithId(std::vector<int> idsInQuestion, std::size_t* steps=nullptr)
			{
				return std::static_pointer_cast<T>(searchParents([&](std::shared_ptr<Node> subject) -> bool { return (std::find(idsInQuestion.begin(), idsInQuestion.end(), subject->getId()) != idsInQuestion.end()); }, steps));
			}
			
			template<typename T>
			std::shared_ptr<T> hasParentWithId(int idInQuestion, std::size_t* steps=nullptr)
			{
				return std::static_pointer_cast<T>(searchParents([&](std::shared_ptr<Node> subject) -> bool { return (subject->getId() == idInQuestion); }, steps));
			}
			
			//shortcut for hasParentWithId, because   hasParentWithId<T>()   is the same like   hasParentWithId<T>(T::uniqueId)
			template<typename T>
			typename std::enable_if_t<std::is_base_of<Node, T>::value, std::shared_ptr<T>>							//from http://stackoverflow.com/a/5108738
			hasParentWithId(std::size_t* steps=nullptr)
			{
				return hasParentWithId<T>(T::uniqueId, steps);
			}
			
			//checks wheater one of the parents (defined like above) of 'subject' has an id beginning with 'id'. This is useful when any class derived from a base class is wanted, e.g. when WhileLoop and ForLoop are wanted, one can just pass ControllableLoop as T to this function, because WhileLoop and ForLoop are derived from ControllableLoop.
			template<typename T>
			std::shared_ptr<T> hasParentWithIdBase(int idBaseInQuestion, std::size_t* steps=nullptr)
			{
				int idBaseMask = getIdBaseMask(idBaseInQuestion);
				return std::static_pointer_cast<T>(searchParents([&](std::shared_ptr<Node> subject) -> bool { return ((subject->getId() & idBaseMask) == idBaseInQuestion); }, steps));
			}
			
			//shortcut for hasParentWithIdBase, like above with hasParentWithUniqueId
			template<typename T>
			typename std::enable_if_t<std::is_base_of<Node, T>::value, std::shared_ptr<T>>
			hasParentWithIdBase(std::size_t* steps=nullptr)
			{
				return hasParentWithIdBase<T>(T::uniqueId, steps);
			}
	};
}

