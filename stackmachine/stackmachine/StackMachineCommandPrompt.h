#pragma once
#include "MyStackMachine.h"

class StackMachineCommandPrompt
{
public:
    StackMachineCommandPrompt(std::istream & in, std::ostream & out);

    void Run();

private:

    enum class CommandType
    {
        Push,
        Pop,
        Add,
        Multiply,
        Substract,
        Divide,
        Dump,
        Exit,
        Null
    };

    struct Command
    {
        CommandType type;
        int argument;
    };

    void PrintCommandLineInvitation();
    Command ReadCommand();
    void ExecuteCommand(Command const& command);

    CommandType GetCommandTypeByName(std::string const& name) const;
    bool IsCommandNeedArgument(CommandType const& type) const;

    std::istringstream GetCommandLineStream();
    CommandType ParseCommandType(std::istream & in) const;
    int ParseCommandArgument(std::istream & in, CommandType const& type) const;

    MyStackMachine m_stackMachine;

    std::istream & m_in;
    std::ostream & m_out;
};

