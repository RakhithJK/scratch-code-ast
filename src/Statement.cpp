/*
 *   Copyright 2016 sigalor
 *
 *   File: scratch-code-ast/src/Statement.cpp
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



#include <ast/Statement.hpp>



namespace ast
{
	const int Statement::uniqueId = 0x00000011;

	Statement::Statement(int newId) : Node(newId) { }
	Statement::Statement(int newId, std::shared_ptr<Node> newParent) : Node(newId, newParent) { }

	Statement::Statement() : Node(uniqueId) { }
	Statement::Statement(std::shared_ptr<Node> newParent) : Node(uniqueId, newParent) { }
}
