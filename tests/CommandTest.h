// USED by unit tests, this file should not be modified

#pragma once

#include "mockos/AbstractCommand.h"
#include "mockos/AbstractFileSystem.h"
#include "mockos/AbstractFileFactory.h"

#include <iostream>
#include <string>
#include <algorithm>

enum commandTestResults {Success=0};

class CommandTest : public AbstractCommand {
	AbstractFileSystem* afs;
	
public:
	explicit CommandTest(AbstractFileSystem*);
	~CommandTest() override = default;
	int execute(std::string) override;
	void displayInfo() override;
};